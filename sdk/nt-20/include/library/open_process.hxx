#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t open_process(
      const std::int32_t access,
      const std::int32_t inherit,
      const std::int32_t pid
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int32_t access,
         const std::int32_t inherit,
         const std::int32_t pid
      ) >( &OpenProcess )( access, inherit, pid );
   }
}
