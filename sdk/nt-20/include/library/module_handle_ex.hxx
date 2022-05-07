#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t module_handle_ex(
      const std::int32_t flags,
      const std::int8_t* module_name,
      const std::ptrdiff_t handle
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::int32_t flags,
         const std::int8_t * module_name,
         const std::ptrdiff_t handle
      ) >( &GetModuleHandleExA )( flags, module_name, handle );
   }
}
