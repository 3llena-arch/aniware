#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t open_thread(
      const std::int32_t access,
      const std::int32_t inherit,
      const std::int32_t tid
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int32_t access,
         const std::int32_t inherit,
         const std::int32_t tid
      ) >( &OpenThread )( access, inherit, tid );
   }
}
