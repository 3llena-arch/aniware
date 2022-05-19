#pragma once

namespace n_cs::client_entities {
   static std::ptrdiff_t m_ptr;

   [[ nodiscard ]]
   n_cs::entity_t* by_index(
      const std::uint32_t ent_index
   ) {
      return ptr< n_cs::entity_t** >( m_ptr )[ 0xffff7ffc + ent_index * 4 ];
   }
}
