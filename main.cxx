#include "sdk/sdk.hxx"

namespace n_nt {
   [[ nodiscard ]]
   const std::int32_t free_library(
      const std::ptrdiff_t& instance
   ) {
      if ( !instance || instance == -1 )
         return 0;
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t );
      return reinterpret_cast< call_t >
         ( std::addressof( ::FreeLibrary ) )( instance );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t get_module_handle(
      const std::string_view& module
   ) {
      if ( !&module || module.empty( ) )
         return 0;
      using call_t = std::ptrdiff_t( __stdcall* )( const char* );
      return reinterpret_cast< call_t >
         ( std::addressof( ::GetModuleHandleA ) )( module.data( ) );
   }
}

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const std::int32_t call_reason,
   const std::ptrdiff_t reserved
) {
   ( instance, call_reason, reserved );
   return n_nt::free_library( instance );
}
