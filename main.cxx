#include "sdk/sdk.hxx"

[[ nodiscard ]]
const std::int32_t initial_thread(
   const std::ptrdiff_t instance
) {
   n_nt::free_library_exit_thread( instance );
   return 0;
}

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const n_nt::entry_flag_t call,
   const std::ptrdiff_t reserved [[ maybe_unused ]]
) {
   return 1;
}
