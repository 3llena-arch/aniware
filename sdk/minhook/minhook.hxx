#pragma once

#include "include/minhook.h"

namespace n_mh {
   const std::uint8_t hook(
      const std::ptrdiff_t& address,
      const auto& detour,
      const auto& original
   ) {
      if ( !address || !detour || !original )
         return 0;
      return MH_CreateHook( ptr< void* >( address ), 
         ptr< void* >( detour ), ptr< void** >( original ) );
   }

   const std::uint8_t unhook(
      const std::ptrdiff_t& address
   ) {
      if ( !address )
         return 0;
      return MH_DisableHook( 0 );
   }
}
