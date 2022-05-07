#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <functional>
#include <optional>

namespace n_nt {
   [[ nodiscard ]]
   const std::ptrdiff_t create_toolhelp32_snapshot(
      const std::int32_t flags,
      const std::int32_t pid
   ) {
      return reinterpret_cast< const std::ptrdiff_t( __stdcall* )(
         const std::int32_t flags,
         const std::int32_t pid
      ) >( &CreateToolhelp32Snapshot )( flags, pid );
   }

   [[ nodiscard ]]
   const std::int32_t module32_first(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t mod_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t mod_entry
      ) >( &Module32First )( handle, mod_entry );
   }

   [[ nodiscard ]]
   const std::int32_t module32_next(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t mod_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t mod_entry
      ) >( &Module32Next )( handle, mod_entry );
   }

   [[ nodiscard ]]
   const std::int32_t process32_first(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t pe_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t pe_entry
      ) >( &Process32First )( handle, pe_entry );
   }

   [[ nodiscard ]]
   const std::int32_t process32_next(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t pe_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t pe_entry
      ) >( &Process32Next )( handle, pe_entry );
   }

   [[ nodiscard ]]
   const std::int32_t thread32_first(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t th_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t th_entry
      ) >( &Thread32First )( handle, th_entry );
   }

   [[ nodiscard ]]
   const std::int32_t thread32_next(
      const std::ptrdiff_t handle,
      const std::ptrdiff_t th_entry
   ) {
      return reinterpret_cast< const std::int32_t( __stdcall* )(
         const std::ptrdiff_t handle,
         const std::ptrdiff_t th_entry
      ) >( &Thread32Next )( handle, th_entry );
   }
}