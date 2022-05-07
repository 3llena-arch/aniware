#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t module32_first(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t mod_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t mod_entry
      ) >( &Module32First )( handle, mod_entry );
   }
}
