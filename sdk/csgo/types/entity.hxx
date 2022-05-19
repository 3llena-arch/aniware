#pragma once

namespace n_cs {
   const struct entity_t {
      [[ nodiscard ]]
      const std::uint8_t is_player( ) {
         if ( !this )
            return 0;
         using call_t = std::uint8_t( __thiscall* )( n_cs::entity_t* );
         return !!ptr< call_t >( this, 158 )( this );
      }

      [[ nodiscard ]]
      const std::int32_t health( ) {
         if ( !this )
            return 0;
         using call_t = std::int32_t( __thiscall* )( n_cs::entity_t* );
         return ptr< call_t >( this, 122 )( this );
      }
   };
}
