#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t is_window(
      const std::ptrdiff_t handle
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle
      ) >( &IsWindow )( handle );
   }
}
