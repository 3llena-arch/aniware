#pragma once

#include "minhook.h"

namespace n_mh {
   const std::uint8_t create_hook(
      const auto& address,
      const auto& detour,
      const auto& original
   ) {
      auto mh_address{ *ptr< std::ptrdiff_t* >( &address ) };
      auto mh_detour{ *ptr< std::ptrdiff_t* >( &detour ) };
      auto mh_original{ *ptr< std::ptrdiff_t* >( &original ) };

      return !!MH_CreateHook( 
         ptr< void* >( mh_address ), 
         ptr< void* >( mh_detour ), 
         ptr< void** >( mh_original ) 
      );
   }

   const std::uint8_t restore_hook(
      const auto& address
   ) {
      auto mh_address{ *ptr< std::ptrdiff_t* >( &address ) };

      return !!MH_DisableHook( 0 ) && !!MH_Uninitialize( );
   }
}
