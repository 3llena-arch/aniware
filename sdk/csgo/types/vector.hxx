#pragma once

namespace n_cs {
   template< typename type_t >
   struct vec2_t { type_t m_x, m_y; };

   template< typename type_t >
   struct vec3_t : n_cs::vec2_t< type_t > { type_t m_z; };
}
