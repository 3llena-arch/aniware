#pragma once

#include "include/types.hxx"
#include "include/library.hxx"
#include "include/tlhelp32.hxx"

namespace n_nt {
   static std::optional< std::unordered_map< std::string, std::ptrdiff_t > >process_list{ };
   static std::optional< std::unordered_map< std::string, std::ptrdiff_t > >module_list{ };

   [[ nodiscard ]]
   const std::optional< std::unordered_map< std::string, std::ptrdiff_t > >query_process_list( ) {
      const auto snap{ n_nt::create_tlhelp32_snapshot( n_nt::snap_flag_t::process ) };
      if ( !snap.has_value( ) )
         return std::nullopt;

      auto ctx{ std::make_optional( n_nt::process_entry_t{ .m_size = sizeof n_nt::process_entry_t } ) };
      static std::unordered_map< std::string, std::ptrdiff_t >list{ };

      if ( n_nt::process32_first( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value( ).m_process_id );

      while ( n_nt::process32_next( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value( ).m_process_id );
      return ( !n_nt::close_handle( snap ) || list.empty( ) ? std::nullopt : std::make_optional( list ) );
   }

   [[ nodiscard ]]
   const std::optional< std::unordered_map< std::string, std::ptrdiff_t > >query_module_list( ) {
      const auto snap{ n_nt::create_tlhelp32_snapshot( n_nt::snap_flag_t::module ) };
      if ( !snap.has_value( ) )
         return std::nullopt;

      auto ctx{ std::make_optional( n_nt::module_entry_t{ .m_size = sizeof n_nt::module_entry_t } ) };
      static std::unordered_map< std::string, std::ptrdiff_t >list{ };

      if ( n_nt::module32_first( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value( ).m_base_address );

      while ( n_nt::module32_next( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value( ).m_base_address );
      return ( !n_nt::close_handle( snap ) || list.empty( ) ? std::nullopt : std::make_optional( list ) );
   }

#ifdef __debug
   const std::uint8_t modify_console(
      const std::optional < n_nt::entry_flag_t >&flag
   ) {
      if ( !flag.has_value( ) )
         return 0;

      if ( flag.value( ) == n_nt::entry_flag_t::process_attach ) {
         if ( !n_nt::alloc_console( ) )
            return 0;

         return std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 2 ) );
      }

      if ( flag.value( ) == n_nt::entry_flag_t::process_detach ) {
         if ( std::fclose( __acrt_iob_func( 0 ) )
           || std::fclose( __acrt_iob_func( 1 ) )
           || std::fclose( __acrt_iob_func( 2 ) ) )
            return 0;

         return n_nt::free_console( );
      }
      return 0;
   }
#endif
}
