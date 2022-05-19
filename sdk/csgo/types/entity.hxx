#pragma once

#define OFFSET( type, name, offset ) type name( ) { return *ptr< type* >( this + offset ); }

namespace n_cs {
   const struct entity_t {
      OFFSET( n_cs::vec3_t< std::float_t >, origin, 0x138 )
      OFFSET( std::uint8_t, is_dormant, 0xed )
      OFFSET( std::uint8_t, is_alive, 0x25f )
      OFFSET( std::uint32_t, health, 0x100 )
      OFFSET( std::uint8_t, team, 0xf4 )
   };
}
