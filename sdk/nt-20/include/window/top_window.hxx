#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t top_window(
      const std::ptrdiff_t handle
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::ptrdiff_t handle
      ) >( &GetTopWindow )( handle );
   }
}
