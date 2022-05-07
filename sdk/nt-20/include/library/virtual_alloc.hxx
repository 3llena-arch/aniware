#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t virtual_alloc(
      const std::ptrdiff_t address,
      const std::ptrdiff_t size,
      const std::int32_t type,
      const std::int32_t protect
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )( 
         const std::ptrdiff_t address,
         const std::ptrdiff_t size,
         const std::int32_t type,
         const std::int32_t protect
      ) >( &VirtualAlloc )( address, size, type, protect );
   }
}
