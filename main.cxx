#include "sdk/sdk.hxx"

[[ nodiscard ]]
const std::uint8_t open_console( ) {
   if ( !n_nt::alloc_console( ) )
      return 0;
   
   if ( !std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
     || !std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
     || !std::freopen( "conout$", "w", __acrt_iob_func( 2 ) ) )
      return 0;

   return std::cout.good( ) && std::cerr.good( ) && std::cin.good( );
}

[[ nodiscard ]]
const std::uint8_t close_console( ) {
   if ( std::fclose( __acrt_iob_func( 0 ) )
     || std::fclose( __acrt_iob_func( 1 ) )
     || std::fclose( __acrt_iob_func( 2 ) ) )
      return 0;

   if ( !n_nt::free_console( ) )
      return 0;

   return std::cout.bad( ) && std::cerr.bad( ) && std::cin.bad( );
}

[[ nodiscard ]]
const std::int32_t initial_thread(
   const std::ptrdiff_t instance
) {
   return n_nt::free_library( instance );
}

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const n_nt::entry_flag_t call,
   const std::ptrdiff_t reserved
) {
   if ( call == n_nt::entry_flag_t::process_attach )
      n_nt::close_handle( n_nt::create_thread( &initial_thread, instance ) );
   return 1;
}
