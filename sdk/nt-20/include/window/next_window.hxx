#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t next_window(
      const std::ptrdiff_t handle,
      const std::int32_t flag
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::int32_t flag
      ) >( &GetWindow )( handle, flag );
   }
}
