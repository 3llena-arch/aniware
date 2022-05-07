#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t process32_next(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t pe_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t pe_entry
      ) >( &Process32Next )( handle, pe_entry );
   }
}
