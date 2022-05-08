#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::uint8_t open_console( ) {
      if ( !n_nt::alloc_console( ) )
         return 0;

      return std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
          && std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
          && std::freopen( "conout$", "w", __acrt_iob_func( 2 ) );
   }

   const std::uint8_t close_console( ) {
      if ( std::fclose( __acrt_iob_func( 0 ) )
        || std::fclose( __acrt_iob_func( 1 ) )
        || std::fclose( __acrt_iob_func( 2 ) ) )
         return 0;

      return n_nt::free_console( );
   }
}
