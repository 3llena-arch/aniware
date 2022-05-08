#include "sdk/sdk.hxx"

[[ nodiscard ]]
const std::int32_t initial_thread(
   const std::ptrdiff_t instance
) {

   n_nt::free_library_exit_thread( instance );
   return 0;
}

const std::int32_t DllMain(
   const std::int32_t instance,
   const std::int32_t reason,
   const std::int32_t unused [[ maybe_unused ]]
) {
   using ef = n_nt::entry_flag_t;
   if ( ef{ reason } == ef::process_attach ) {
      const auto ctx{ n_nt::create_thread( &initial_thread, instance ) };
      if ( ctx )
         n_nt::close_handle( ctx );
   }
   return 1;
}
