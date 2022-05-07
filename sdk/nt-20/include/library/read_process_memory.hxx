#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t read_process_memory(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t address,
      const std::ptrdiff_t buffer,
      const std::ptrdiff_t size,
      const std::ptrdiff_t read
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle, 
         const std::ptrdiff_t address, 
         const std::ptrdiff_t buffer, 
         const std::ptrdiff_t size, 
         const std::ptrdiff_t read
      ) >( &ReadProcessMemory )( handle, address, buffer, size, read );
   }
}
