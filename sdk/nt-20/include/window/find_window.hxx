#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t find_window(
      const std::int8_t* window_class,
      const std::int8_t* window_title
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int8_t* window_class,
         const std::int8_t* window_title
      ) >( &FindWindowA )( window_class, window_title );
   }
}
