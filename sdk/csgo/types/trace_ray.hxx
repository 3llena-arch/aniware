#pragma once

namespace n_cs {
   const struct trace_ray_t {
      n_cs::vec3_t< std::float_t >m_src;
      std::uint8_t m_pad0[4];
      n_cs::vec3_t< std::float_t >m_dst;
      std::uint8_t m_pad1[40];
      std::uint8_t m_is_ray, m_is_swept;
   };
}
