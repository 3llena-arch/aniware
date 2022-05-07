#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t window_thread_pid(
      const std::ptrdiff_t window,
      const std::ptrdiff_t pid
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t window,
         const std::ptrdiff_t pid
      ) >( &GetWindowThreadProcessId )( window, pid );
   }
}
