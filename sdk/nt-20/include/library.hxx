#pragma once

#include <iostream>
#include <optional>
#include <functional>
#include <windows.h>
#include <string_view>
#include <string>

namespace n_nt {
   [[ nodiscard ]]
   const std::uint8_t alloc_console( ) {
      using call_t = std::int32_t( __stdcall* )( );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::AllocConsole ) )( );
   }

   [[ nodiscard ]]
   const std::uint8_t free_console( ) {
      using call_t = std::int32_t( __stdcall* )( );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::FreeConsole ) )( );
   }

   [[ nodiscard ]]
   const std::uint8_t close_handle(
      const std::optional< std::ptrdiff_t >&handle
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::CloseHandle ) )( handle.value( ) );
   }
   
   [[ nodiscard ]]
   const std::optional< std::ptrdiff_t >load_library(
      const std::optional< std::string_view >&module
   ) {
      if ( !module.has_value( ) || module.value( ).empty( ) )
         return std::nullopt;

      using call_t = std::ptrdiff_t( __stdcall* )( const char* );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::LoadLibraryA ) )( module.value( ).data( ) ) );
   }

   [[ nodiscard ]]
   const std::optional< std::ptrdiff_t >load_library_ex(
      const std::optional< std::string_view >&module,
      const std::optional< std::int32_t >&flags
   ) {
      if ( !module.has_value( ) || module.value( ).empty( ) )
         return std::nullopt;

      if ( !flags.has_value( ) || flags.value( ) <= 0 )
         return std::nullopt;

      using call_t = std::ptrdiff_t( __stdcall* )( const char*, std::ptrdiff_t, std::int32_t );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::LoadLibraryExA ) )( module.value( ).data( ), 0, flags.value( ) ) );
   }

   [[ nodiscard ]]
   const std::optional< std::ptrdiff_t >module_handle(
      const std::optional< std::string_view >&module
   ) {
      if ( !module.has_value( ) || module.value( ).empty( ) )
         return std::nullopt;

      using call_t = std::ptrdiff_t( __stdcall* )( const char* );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::GetModuleHandleA ) )( module.value( ).data( ) ) );
   }

   [[ nodiscard ]]
   const std::optional< std::ptrdiff_t >module_handle_ex(
      const std::optional< std::string_view >&module,
      const std::optional< std::int32_t >&flags
   ) {
      if ( !module.has_value( ) || module.value( ).empty( ) )
         return std::nullopt;

      if ( !flags.has_value( ) || flags.value( ) <= 0 )
         return std::nullopt;

      std::ptrdiff_t ctx{ };
      using call_t = std::int32_t( __stdcall* )( std::int32_t, const char*, std::ptrdiff_t* );
      reinterpret_cast< call_t >
         ( std::addressof( ::GetModuleHandleExA ) )( flags.value( ), module.value( ).data( ), &ctx );

      return ( !ctx || ctx <= 0 ) 
         ? std::nullopt : std::make_optional( ctx );
   }

   const std::optional< std::ptrdiff_t >open_process(
      const std::optional< std::int32_t >&access,
      const std::optional< std::int32_t >&pid,
      const std::optional< std::int32_t >&inherit = std::make_optional( 0 )
   ) {
      if ( !pid.has_value( ) || pid.value( ) <= 0 )
         return std::nullopt;

      if ( !access.has_value( ) || access.value( ) <= 0 )
         return std::nullopt;
      
      using call_t = std::ptrdiff_t( __stdcall* )( std::int32_t, std::int32_t, std::int32_t );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::OpenProcess ) )( access.value( ), inherit.value( ), pid.value( ) ) );
   }

   const std::optional< std::ptrdiff_t >open_thread(
      const std::optional< std::int32_t >&access,
      const std::optional< std::int32_t >&tid,
      const std::optional< std::int32_t >&inherit = std::make_optional( 0 )
   ) {
      if ( !tid.has_value( ) || tid.value( ) <= 0 )
         return std::nullopt;

      if ( !access.has_value( ) || access.value( ) <= 0 )
         return std::nullopt;
      
      using call_t = std::ptrdiff_t( __stdcall* )( std::int32_t, std::int32_t, std::int32_t );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::OpenThread ) )( access.value( ), inherit.value( ), tid.value( ) ) );
   }

   [[ nodiscard ]]
   const std::optional< std::ptrdiff_t >proc_address(
      const std::optional< std::ptrdiff_t >&module,
      const std::optional< std::string_view >&function
   ) {
      if ( !module.has_value( ) || module.value( ) <= 0 )
         return std::nullopt;

      if ( !function.has_value( ) || function.value( ).empty( ) )
         return std::nullopt;

      using call_t = std::ptrdiff_t( __stdcall* )( std::ptrdiff_t, const char* );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::GetProcAddress ) )( module.value( ), function.value( ).data( ) ) );
   }
}
