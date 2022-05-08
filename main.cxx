#include "sdk/sdk.hxx"

[[ nodiscard ]]
const std::int32_t initial_thread(
   const std::ptrdiff_t instance
) {
   if ( n_nt::open_console( ) ) {
      std::cout << "scratch my balls" << std::endl;
      // setup shit
      // mhmhmhmhmh  do shit
      while ( !::GetAsyncKeyState( 0x23 ) )
		   std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
      n_nt::close_console( );
   }
   return n_nt::free_library_exit_thread( instance );
}

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const n_nt::entry_flag_t call,
   const std::ptrdiff_t reserved
) {
   if ( call == n_nt::entry_flag_t::process_attach ) {
      auto ctx{ n_nt::create_thread( std::addressof( initial_thread ), instance ) };
      if ( ctx.has_value( ) )
         n_nt::close_handle( ctx );
   }
   return 1;
}
