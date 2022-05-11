#pragma once

#include "include/types.hxx"
#include "include/library.hxx"

namespace n_nt {
#ifdef __debug
   const std::uint8_t modify_console(
      const n_nt::entry_flag_t& flag
   ) {
      if ( flag == n_nt::entry_flag_t::process_attach ) {
         if ( !n_nt::alloc_console( ) )
            return 0;
         return std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 2 ) );
      }

      if ( flag == n_nt::entry_flag_t::process_detach ) {
         if ( std::fclose( __acrt_iob_func( 0 ) )
           || std::fclose( __acrt_iob_func( 1 ) )
           || std::fclose( __acrt_iob_func( 2 ) ) )
            return 0;
         return n_nt::free_console( );
      }
      return 0;
   }
#endif
   [[ nodiscard ]]
   const std::ptrdiff_t fetch_ldr_head( ) {
      _asm mov eax, fs:24       ; get teb
      _asm mov eax, [eax + 48]  ; peb
      _asm mov eax, [eax + 12]  ; get ldr
      _asm add eax, 20          ; loaded list
   }

   [[ nodiscard ]]
   const std::unordered_map< std::wstring, std::ptrdiff_t >fetch_images( ) {
      const auto head{ ptr< n_nt::ldr_entry_t* >( n_nt::fetch_ldr_head( ) ) };
      if ( !head )
         return { };
      std::unordered_map< std::wstring, std::ptrdiff_t >map{ };
      for ( auto ctx{ head->m_next }; ctx != head; ctx = ctx->m_next ) {
         if ( !ctx->m_name )
            continue;
         map.emplace( std::wstring{ ctx->m_name, ctx->m_length }, ctx->m_ptr );
      }
      return map;
   }

   [[ nodiscard ]]
   const std::pair< std::ptrdiff_t, std::uint8_t* >hook_fn(
      const auto& original,
      const auto& callback
   ) {
      auto orig_fn{ ptr< const std::ptrdiff_t >( original ) };
      auto call_fn{ ptr< const std::ptrdiff_t >( callback ) };

      if ( !orig_fn || !call_fn )
         return { };

      if ( auto old_flag{ n_nt::mem_protect( orig_fn, 0x40, 6 ) }; old_flag ) {
         static std::uint8_t src[5], dst[5] = { 0xe9, 0x00, 0x00, 0x00, 0x00 };

         auto new_ptr{ ptr< std::ptrdiff_t* >( call_fn - orig_fn - 5 ) };
         if ( !new_ptr )
            return { };

         if ( !std::memcpy( src, ptr< std::ptrdiff_t* >( orig_fn ), 5 )
           || !std::memcpy( &dst[ 1 ], &new_ptr, 4 )
           || !std::memcpy( ptr< std::ptrdiff_t* >( orig_fn ), dst, 5 ) )
            return { };
          
         n_nt::mem_protect( orig_fn, old_flag, 6 );
         return std::make_pair( orig_fn, src );
      }
      return { };
   }

   const std::uint8_t unhook_fn(
      const std::pair< std::ptrdiff_t, std::uint8_t* >&pair
   ) {
      if ( !pair.first || !pair.second )
         return 0;

      if ( auto old_flag{ n_nt::mem_protect( pair.first, 0x40, 6 ) }; old_flag ) {
         auto new_ptr{ ptr< std::ptrdiff_t* >( pair.first ) };
         if ( !new_ptr )
            return 0;

         return std::memcpy( new_ptr, pair.second, 5 ) 
            && n_nt::mem_protect( pair.first, old_flag, 6 );
      }
      return 0;
   }
}
