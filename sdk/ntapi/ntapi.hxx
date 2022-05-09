#pragma once

#include "include/types.hxx"
#include "include/library.hxx"
#include "include/tlhelp32.hxx"

namespace n_nt {
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
