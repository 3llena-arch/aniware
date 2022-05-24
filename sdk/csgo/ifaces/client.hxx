#pragma once

namespace cs::client {
	static std::ptrdiff_t m_ptr;

   [[ nodiscard ]]
	const std::vector< cs::client_class_t >classes( ) {
      auto head{ ptr< std::ptrdiff_t >( m_ptr, 8 ) };
      if ( !head )
         return { };
      std::vector< cs::client_class_t >map{ };

      for ( auto it{ **ptr< cs::client_class_t*** >( head + 1 ) }; it; it = it->m_next ) {
         if ( !it->m_name )
            continue;
         map.push_back( { .m_name = it->m_name, .m_recv = it->m_recv, .m_id = it->m_id } );
      }
      return map;
	}
}
