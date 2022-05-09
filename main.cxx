#include "sdk/sdk.hxx"

[[ nodiscard ]]
const std::int32_t initial_thread(
   const std::ptrdiff_t instance
) {
#ifdef __debug
   using ef = n_nt::entry_flag_t;
   n_nt::modify_console( ef::process_attach );
#endif
   n_nt::m_image_map = n_nt::module_list( );

   // 2. query ifaces
   // 3. query hook sigs
   // 4. hook
   // 5. run feats

   while ( !n_nt::key_state( 0x23 ) )
      std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

#ifdef __debug
   n_nt::modify_console( ef::process_detach );
#endif
   n_nt::free_library_exit_thread( instance );
   return 0;
}

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const std::int32_t call_reason,
   const std::ptrdiff_t unused [[ maybe_unused ]]
) {
   using ef = n_nt::entry_flag_t;
   if ( ef{ call_reason } == ef::process_attach ) {
      const auto ctx{ n_nt::create_thread( &initial_thread, instance ) };
      if ( ctx )
         n_nt::close_handle( ctx );
   }
   return 1;
}
