#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t create_toolhelp32_snapshot(
      const std::int32_t flags,
      const std::int32_t pid
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int32_t flags,
         const std::int32_t pid
      ) >( &CreateToolhelp32Snapshot )( flags, pid );
   }
}
