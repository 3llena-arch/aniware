#pragma once

namespace n_cs {
   const struct entity_t {
      [[ nodiscard ]]
      n_cs::vec3_t< std::float_t >* origin( ) {
         return ptr< n_cs::vec3_t* >( this + 0x138 );
      }

      [[ nodiscard ]]
      const std::uint8_t is_dormant( ) {
         return *ptr< std::uint8_t* >( this + 0xed );
      }

      [[ nodiscard ]]
      const std::uint8_t is_dead( ) {
         return *ptr< std::uint8_t* >( this + 0x25f );
      }

      [[ nodiscard ]]
      const std::uint8_t health( ) {
         return *ptr< std::uint8_t* >( this + 0x100 );
      }

      [[ nodiscard ]]
      const std::uint8_t team( ) {
         return *ptr< std::uint8_t* >( this + 0xf4 );
      }
   };
}
