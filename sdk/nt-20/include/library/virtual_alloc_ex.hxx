#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t virtual_alloc_ex(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t address,
      const std::ptrdiff_t size,
      const std::int32_t type,
      const std::int32_t protect
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )( 
         const std::ptrdiff_t handle,
         const std::ptrdiff_t address,
         const std::ptrdiff_t size,
         const std::int32_t type,
         const std::int32_t protect
      ) >( &VirtualAllocEx )( handle, address, size, type, protect );
   }
}
