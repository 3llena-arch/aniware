#pragma once

namespace cs::client_entities {
   static std::ptrdiff_t m_ptr;

   [[ nodiscard ]]
   cs::entity_t* by_index(
      const std::uint32_t ent_index
   ) {
      return ptr< cs::entity_t** >( m_ptr )[ 0xffff7ffc + ent_index * 4 ];
   }
}
