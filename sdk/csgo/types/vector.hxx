#pragma once

namespace cs {
   template< typename type_t >
   struct vec2_t { type_t m_x, m_y; };

   template< typename type_t >
   struct vec3_t : cs::vec2_t< type_t > { type_t m_z; };

   template< typename type_t >
   struct vec4_t : cs::vec3_t< type_t > { type_t m_w; };
}
