#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::uint8_t alloc_console( ) {
      using call_t = std::int32_t( __stdcall* )( );
      return !!reinterpret_cast< call_t >( std::addressof( ::AllocConsole ) )( );
   }

   [[ nodiscard ]]
   const std::uint8_t free_console( ) {
      using call_t = std::int32_t( __stdcall* )( );
      return !!reinterpret_cast< call_t >( std::addressof( ::FreeConsole ) )( );
   }

   [[ nodiscard ]]
   const std::uint8_t close_handle(
      const std::optional< std::ptrdiff_t >&handle
   ) {
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t );

      return reinterpret_cast<const std::int32_t(__stdcall*)(
         const std::ptrdiff_t handle
         )>(&CloseHandle)(handle);
   }

   [[ nodiscard ]]
   const std::ptrdiff_t load_library(
      const std::int8_t* module_name
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int8_t* module_name
      ) >( &LoadLibraryA )( module_name );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t load_library_ex(
      const std::int8_t* module_name,
      const std::ptrdiff_t file,
      const std::int32_t flags
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int8_t* module_name,
         const std::ptrdiff_t file,
         const std::int32_t flags
      ) >( &LoadLibraryExA )( module_name, file, flags );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t module_handle(
      const std::int8_t* module_name
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int8_t* module_name
      ) >( &GetModuleHandleA )( module_name );
   }


}

