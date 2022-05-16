#pragma once

#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>

#include <functional>
#include <iostream>
#include <codecvt>
#include <locale>
#include <thread>
#include <mutex>
#include <map>

#ifdef __ptr
   template< typename type_t >
   type_t ptr( auto addr, std::int32_t fn = 0 ) {
      if ( fn )
         return ( *( type_t** )addr )[ fn ];
      return ( type_t )addr;
   };
#endif

#include "minhook/minhook.hxx"
#include "ntapi/ntapi.hxx"
#include "csgo/csgo.hxx"
