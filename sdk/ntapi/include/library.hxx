#pragma once

namespace nt {
#ifdef __debug
   [[ nodiscard ]]
   const std::uint8_t alloc_console( ) {
      using call_t = std::int32_t( __stdcall* )( );
      return !!ptr< call_t >
         ( std::addressof( ::AllocConsole ) )( );
   }

   [[ nodiscard ]]
   const std::uint8_t free_console( ) {
      using call_t = std::int32_t( __stdcall* )( );
      return !!ptr< call_t >
         ( std::addressof( ::FreeConsole ) )( );
   }
#endif
   [[ nodiscard ]]
   const std::ptrdiff_t create_thread(
      const auto& callback,
      const std::ptrdiff_t& parameter
   ) {
      if ( !callback || !parameter )
         return 0;

      const auto ctx{ ptr< std::ptrdiff_t >( callback ) };
      if ( !ctx )
         return 0;

      using call_t = std::ptrdiff_t( __stdcall* )( std::ptrdiff_t, std::ptrdiff_t, 
         std::ptrdiff_t, std::ptrdiff_t, std::int32_t, std::ptrdiff_t );
      return ptr< call_t >
         ( std::addressof( ::CreateThread ) )( 0, 0, ctx, parameter, 0, 0 );
   }

   [[ nodiscard ]]
   const std::uint8_t disable_thread_calls(
      const std::ptrdiff_t& module
   ) {
      if ( !module || module == -1 )
         return 0;
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t );
      return !!ptr< call_t >
         ( std::addressof( ::DisableThreadLibraryCalls ) )( module );
   }

   [[ nodiscard ]]
   const std::uint8_t key_state(
      const std::int32_t& key
   ) {
      if ( !key )
         return 0;
      using call_t = std::int16_t( __stdcall* )( std::int32_t );
      return !!ptr< call_t >
         ( std::addressof( ::GetAsyncKeyState ) )( key );
   }

   const std::uint8_t close_handle(
      const std::ptrdiff_t& handle
   ) {
      if ( !handle || handle == -1 )
         return 0;
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t );
      return !!ptr< call_t >
         ( std::addressof( ::CloseHandle ) )( handle );
   }

   [[ nodiscard ]]
   const std::uint8_t free_library(
      const std::ptrdiff_t& module
   ) {
      if ( !module || module == -1 )
         return 0;
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t );
      return !!ptr< call_t >
         ( std::addressof( ::FreeLibrary ) )( module );
   }

   const std::uint8_t free_library_exit_thread(
      const std::ptrdiff_t& module,
      const std::int32_t& flags = 0
   ) {
      if ( !module || module == -1 )
         return 0;
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, std::int32_t );
      return !!ptr< call_t >
         ( std::addressof( ::FreeLibraryAndExitThread ) )( module, flags );
   }
   
   [[ nodiscard ]]
   const std::ptrdiff_t load_library(
      const std::string_view& module
   ) {
      if ( module.empty( ) )
         return 0;
      using call_t = std::ptrdiff_t( __stdcall* )( const char* );
      return ptr< call_t >
         ( std::addressof( ::LoadLibraryA ) )( module.data( ) );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t load_library_ex(
      const std::string_view& module,
      const std::int32_t& flags = 0
   ) {
      if ( module.empty( ) )
         return 0;
      using call_t = std::ptrdiff_t( __stdcall* )( const char*, std::ptrdiff_t, std::int32_t );
      return ptr< call_t >
         ( std::addressof( ::LoadLibraryExA ) )( module.data( ), 0, flags );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t module_handle(
      const std::string_view& module
   ) {
      if ( module.empty( ) )
         return 0;
      using call_t = std::ptrdiff_t( __stdcall* )( const char* );
      return ptr< call_t >
         ( std::addressof( ::GetModuleHandleA ) )( module.data( ) );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t proc_address(
      const std::ptrdiff_t& module,
      const std::string_view& function
   ) {
      if ( !module || module == -1 || function.empty( ) )
         return 0;
      using call_t = std::ptrdiff_t( __stdcall* )( std::ptrdiff_t, const char* );
      return ptr< call_t >
         ( std::addressof( ::GetProcAddress ) )( module, function.data( ) );
   }

   const std::int32_t mem_protect(
      const std::ptrdiff_t& address,
      const std::int32_t& flag,
      const std::size_t& size
   ) {
      if ( !address || !flag || !size )
         return 0;
      std::int32_t old{ };
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, std::size_t, std::int32_t, std::int32_t* );
      return !!ptr< call_t >
         ( std::addressof( ::VirtualProtect ) )( address, size, flag, &old ) ? old : 0;

   }
}
