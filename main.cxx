#include <iostream>
#include <windows.h>
#include <optional>
#include <thread>

namespace n_nt {
   [[ nodiscard ]]
   const std::uint8_t free_library(
      const std::optional< std::ptrdiff_t >&instance
   ) {
      if ( !instance.has_value( ) || instance.value( ) == -1 )
         return 0;
      return reinterpret_cast< std::uint8_t( __stdcall* )( const std::ptrdiff_t instance ) >
         ( std::addressof( ::FreeLibrary ) )( instance.value( ) );
   }
}

const std::int32_t dll_main(
   std::ptrdiff_t instance
) {
   auto ctx = std::make_optional( instance );

   return std::int32_t{ n_nt::free_library( std::nullopt ) };
}
