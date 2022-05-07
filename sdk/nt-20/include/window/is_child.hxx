#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t is_child(
      const std::ptrdiff_t parent,
      const std::ptrdiff_t handle
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t parent,
         const std::ptrdiff_t handle
      ) >( &IsWindowEnabled )( parent, handle );
   }
}
