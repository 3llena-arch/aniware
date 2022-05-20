#pragma once

namespace n_cs::engine_debug {
   static std::ptrdiff_t m_ptr;

   [[ nodiscard ]]
   const n_cs::vec3_t< std::float_t >to_screen(
      const n_cs::vec3_t< std::float_t >&src
   ) {
      n_cs::vec3_t< std::float_t >dst{ };
      
      using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, const n_cs::vec3_t< std::float_t >&, n_cs::vec3_t< std::float_t >& );
      return ( ptr< call_t >( m_ptr, 13 )( m_ptr, src, dst ) != 1 ? dst : n_cs::vec3_t< std::float_t >{ 800.f, 900.f } );
   }
}
