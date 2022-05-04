#include "sdk/sdk.hxx"

namespace n_nt {
   using bool_t = std::bitset< 1 >;
   [[ nodiscard ]]
   const n_nt::bool_t free_library( 
      const std::optional< std::ptrdiff_t >&instance 
   ) {
      if ( !instance.has_value( ) )
         return n_nt::bool_t{ 0 };
      return reinterpret_cast< std::int32_t( __stdcall* )( std::ptrdiff_t ) >
         ( std::addressof( ::FreeLibrary ) )( instance.value( ) );
   }
}

std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const std::int32_t call_reason,
   const std::ptrdiff_t reserved
) {
   ( instance, call_reason, reserved );

   return n_nt::free_library( std::optional< std::ptrdiff_t >{ instance } ).none( );
}
