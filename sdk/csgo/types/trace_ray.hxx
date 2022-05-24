#pragma once

namespace cs {
   const struct trace_ray_t {
      cs::vec3_t< std::float_t >m_src;
      std::uint8_t m_pad0[4];
      cs::vec3_t< std::float_t >m_dst;
      std::uint8_t m_pad1[40];
      std::uint8_t m_is_ray, m_is_swept;
   };
}
