#pragma once

#include "types/vector.hxx"
#include "types/view_setup.hxx"
#include "types/user_cmd.hxx"

#include "ifaces/client_prediction.hxx"
#include "ifaces/studio_render.hxx"
#include "ifaces/engine_render.hxx"
#include "ifaces/engine_sound.hxx"
#include "ifaces/engine_trace.hxx"
#include "ifaces/vgui_surface.hxx"
#include "ifaces/engine_cvar.hxx"
#include "ifaces/vgui_panel.hxx"
#include "ifaces/engine.hxx"
#include "ifaces/client.hxx"

#include "hooks/paint_traverse.hxx"
#include "hooks/override_view.hxx"
#include "hooks/create_move.hxx"
#include "hooks/frame_notify.hxx"

namespace n_cs {
   [[ nodiscard ]]
   const std::unordered_map< std::string, std::ptrdiff_t >fetch_interfaces( ) {
      const auto images{ n_nt::fetch_images( ) };
      if ( images.empty( ) )
         return { };
      std::unordered_map< std::string, std::ptrdiff_t >map{ };

      for ( auto& [key, val] : images ) {
         auto delim{ n_nt::proc_address( val, "CreateInterface" ) };
         if ( !delim || key.find( L"crashhandler.dll" ) != std::wstring::npos )
            continue;

         auto ctx{ ptr< std::uint8_t* >( val ) };
         if ( !ctx )
            continue;

         while ( ctx[4] != 0x57
              || ctx[5] != 0x85
              || ctx[6] != 0xf6
              || ctx[7] != 0x74
              || ctx[8] != 0x38 )
            ctx++;

         struct iter_t { std::ptrdiff_t m_ptr; 
            char* m_name; iter_t* m_next; };

         for ( auto it{ **ptr< iter_t*** >( ctx ) }; it; it = it->m_next ) {
            if ( !it->m_name )
               continue;
            using call_t = std::int32_t( __stdcall* )( );
            map.emplace( it->m_name, ptr< call_t >( it->m_ptr )( ) );
         }
      }
      return map;
   }

   [[ nodiscard ]]
   const std::uint8_t modify_retaddr(
      const n_nt::entry_flag_t& flag
   ) {
      auto images{ n_nt::fetch_images( ) };
      if ( images.empty( ) )
         return 0;

      std::vector< std::ptrdiff_t >list{ 
         images[L"client.dll"],
         images[L"engine.dll"],
         images[L"studiorender.dll"],
         images[L"materialsystem.dll"]
      };

      for ( std::size_t i{ }; i < list.size( ); i++ ) {
         auto ctx{ ptr< std::uint8_t* >( list[ i ] ) };
         if ( !ctx )
            continue;

         auto it{ ptr< std::ptrdiff_t >( ctx ) + 0xd0 + ( 0xd * i ) };
         if ( !it )
            continue;

         auto head_flag{ n_nt::mem_protect( it, 0x40, 13 ) };
         if ( !head_flag )
            continue;

         if ( flag == n_nt::entry_flag_t::process_attach ) {
            while ( ctx[2] != 0xec
                 || ctx[3] != 0x56
                 || ctx[4] != 0x8b
                 || ctx[5] != 0xf1
                 || ctx[6] != 0x33
                 || ctx[7] != 0xc0
                 || ctx[8] != 0x57 )
               ctx++;

            auto fn{ ptr< std::ptrdiff_t >( ctx ) };
            if ( !fn )
               continue;

            const std::uint8_t buf[9]{ 
               0x55, 0x89, 0xe5, 
               0xb0, 0x01, 0x5d, 
               0xc2, 0x04, 0x00 
            };

            auto old_flag{ n_nt::mem_protect( fn, 0x40, 9 ) };
            if ( !old_flag )
               continue;

            if ( !std::memcpy( ptr< void* >( it + 4 ), ctx, 9 )
              || !std::memcpy( ptr< void* >( it ), &fn, 4 ) 
              || !std::memcpy( ptr< void* >( fn ), buf, 9 ) )
               continue;

            n_nt::mem_protect( fn, old_flag, 9 );
         }

         if ( flag == n_nt::entry_flag_t::process_detach ) {
            auto fn{ *ptr< std::ptrdiff_t* >( it ) };
            if ( !fn )
               continue;

            std::uint8_t buf[9]{ };
            if ( !std::memcpy( buf, ptr< void* >( it + 4 ), 9 ) )
               continue;

            auto old_flag{ n_nt::mem_protect( fn, 0x40, 9 ) };
            if ( !old_flag )
               continue;

            if ( !std::memcpy( ptr< void* >( fn ), buf, 9 )
              || !std::memset( ptr< void* >( it ), 0, 13 ) )
               continue;

            n_nt::mem_protect( fn, old_flag, 9 );
         }
         n_nt::mem_protect( it, head_flag, 13 );
      }
      return 1;
   }

   const std::uint8_t setup_ifaces( ) {
      auto ifaces{ n_cs::fetch_interfaces( ) };
      if ( ifaces.empty( ) )
         return 0;

      n_cs::client_prediction::m_ptr = ifaces["VClientPrediction001"];
      n_cs::engine_render::m_ptr = ifaces["VEngineRenderView014"];
      n_cs::engine_sound::m_ptr = ifaces["IEngineSoundClient003"];
      n_cs::engine_trace::m_ptr = ifaces["EngineTraceClient004"];
      n_cs::studio_render::m_ptr = ifaces["VStudioRender026"];

      n_cs::vgui_surface::m_ptr = ifaces["VGUI_Surface031"];
      n_cs::engine_cvar::m_ptr = ifaces["VEngineCvar007"];
      n_cs::vgui_panel::m_ptr = ifaces["VGUI_Panel009"];
      n_cs::engine::m_ptr = ifaces["VEngineClient014"];
      n_cs::client::m_ptr = ifaces["VClient018"];

      return 1;
   }

   const std::uint8_t modify_hooks(
      const n_nt::entry_flag_t& flag
   ) {
      auto images{ n_nt::fetch_images( ) };
      if ( images.empty( ) )
         return 0;

      if ( !n_cs::modify_retaddr( flag ) )
         return 0;

      if ( flag == n_nt::entry_flag_t::process_attach ) {
         if ( !n_cs::setup_ifaces( ) )
            return 0;

         n_mh::hook( ptr< std::ptrdiff_t >( n_cs::vgui_panel::m_ptr, 41 ), &paint_traverse, &__paint_traverse );
         n_mh::hook( ptr< std::ptrdiff_t >( n_cs::client::m_ptr, 37 ), &frame_notify, &__frame_notify );

         n_mh::hook( images[L"client.dll"] + 0x26c4d0, &override_view, &__override_view );
         n_mh::hook( images[L"client.dll"] + 0x26c480, &create_move, &__create_move );
      }

      if ( flag == n_nt::entry_flag_t::process_detach ) {
         n_mh::unhook( ptr< std::ptrdiff_t >( n_cs::vgui_panel::m_ptr, 41 ) );
         n_mh::unhook( ptr< std::ptrdiff_t >( n_cs::client::m_ptr, 37 ) );

         n_mh::unhook( images[L"client.dll"] + 0x26c4d0 );
         n_mh::unhook( images[L"client.dll"] + 0x26c480 );
      }
      return 0;
   }
}
