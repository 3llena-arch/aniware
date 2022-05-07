#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t find_window_ex(
      const std::ptrdiff_t parent,
      const std::ptrdiff_t child,
      const std::int8_t* window_class,
      const std::int8_t* window_title
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::ptrdiff_t parent,
         const std::ptrdiff_t child,
         const std::int8_t* window_class,
         const std::int8_t* window_title
      ) >( &FindWindowExA )( parent, child, window_class, window_title );
   }
}
