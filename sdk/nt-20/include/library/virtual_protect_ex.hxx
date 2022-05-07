#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t virtual_protect_ex(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t address,
      const std::ptrdiff_t size,
      const std::int32_t protect,
      const std::ptrdiff_t old
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )( 
         const std::ptrdiff_t handle,
         const std::ptrdiff_t address,
         const std::ptrdiff_t size,
         const std::int32_t protect,
         const std::ptrdiff_t old
      ) >( &VirtualProtectEx )( handle, address, size, protect, old );
   }
}
