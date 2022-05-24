#include "sdk/sdk.hxx"

[[ nodiscard ]]
const std::int32_t initial_thread(
   const std::ptrdiff_t instance
) {
   while ( !nt::module_handle( "serverbrowser.dll" ) )
      std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
#ifdef __debug
   using ef = nt::entry_flag_t;
   nt::modify_console( ef::process_attach );
#endif
   cs::modify_hooks( ef::process_attach );
   while ( !nt::key_state( 0x23 ) )
      std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );
   cs::modify_hooks( ef::process_detach );
#ifdef __debug
   nt::modify_console( ef::process_detach );
#endif
   nt::free_library_exit_thread( instance );
   return 0;
}

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const std::int32_t call_reason,
   const std::ptrdiff_t unused [[ maybe_unused ]]
) {
   using ef = nt::entry_flag_t;
   if ( ef{ call_reason } == ef::process_attach ) {
      const auto ctx{ nt::create_thread( &initial_thread, instance ) };
      if ( ctx )
         nt::close_handle( ctx );
   }
   return 1;
}
