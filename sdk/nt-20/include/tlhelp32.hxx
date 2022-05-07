#pragma once

namespace n_nt {
   [[ nodiscard ]]
   const std::optional< std::ptrdiff_t >create_tlhelp32_snapshot(
      const std::optional< std::int32_t >&flags,
      const std::optional< std::int32_t >&pid = std::make_optional( 0 )
   ) {
      if ( !flags.has_value( ) || flags.value( ) <= 0 )
         return std::nullopt;

      using call_t = std::ptrdiff_t( __stdcall* )( std::int32_t, std::int32_t );
      return std::make_optional( reinterpret_cast< call_t >
         ( std::addressof( ::CreateToolhelp32Snapshot ) )( flags.value( ), pid.value( ) ) );
   }

   [[ nodiscard ]]
   const std::uint8_t module32_first(
      const std::optional< std::ptrdiff_t >&handle,
      std::optional< n_nt::module_entry_t >&entry
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, n_nt::module_entry_t* );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::Module32First ) )( handle.value( ), &entry.value( ) );
   }

   [[ nodiscard ]]
   const std::uint8_t module32_next(
      const std::optional< std::ptrdiff_t >&handle,
      std::optional< n_nt::module_entry_t >&entry
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, n_nt::module_entry_t* );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::Module32Next ) )( handle.value( ), &entry.value( ) );
   }

   [[ nodiscard ]]
   const std::uint8_t process32_first(
      const std::optional< std::ptrdiff_t >&handle,
      std::optional< n_nt::process_entry_t >&entry
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, n_nt::process_entry_t* );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::Process32First ) )( handle.value( ), &entry.value( ) );
   }

   [[ nodiscard ]]
   const std::uint8_t process32_next(
      const std::optional< std::ptrdiff_t >&handle,
      std::optional< n_nt::process_entry_t >&entry
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, n_nt::process_entry_t* );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::Process32Next ) )( handle.value( ), &entry.value( ) );
   }

   [[ nodiscard ]]
   const std::uint8_t thread32_first(
      const std::optional< std::ptrdiff_t >&handle,
      std::optional< n_nt::thread_entry_t >&entry
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, n_nt::thread_entry_t* );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::Thread32First ) )( handle.value( ), &entry.value( ) );
   }

   [[ nodiscard ]]
   const std::uint8_t thread32_next(
      const std::optional< std::ptrdiff_t >&handle,
      std::optional< n_nt::thread_entry_t >&entry
   ) {
      if ( !handle.has_value( ) || handle.value( ) <= 0 )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, n_nt::thread_entry_t* );
      return !!reinterpret_cast< call_t >
         ( std::addressof( ::Thread32Next ) )( handle.value( ), &entry.value( ) );
   }
}
