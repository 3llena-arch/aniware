#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t thread32_next(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t th_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t th_entry
      ) >( &Thread32Next )( handle, th_entry );
   }
}
