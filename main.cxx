#include "sdk/sdk.hxx"

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const std::int32_t call_reason,
   const std::ptrdiff_t reserved
) {
   ( instance, call_reason, reserved );



   return n_nt::free_library( std::ref( instance ) );
}
