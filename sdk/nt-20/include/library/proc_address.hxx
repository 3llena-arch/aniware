#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t proc_address(
      const std::ptrdiff_t module,
      const std::int8_t* proc_name
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::ptrdiff_t module,
         const std::int8_t* proc_name
      ) >( &GetProcAddress )( module, proc_name );
   }
}
