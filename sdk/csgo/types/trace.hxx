#pragma once

namespace cs {
   const struct trace_t {
      cs::vec3_t< std::float_t >m_src, m_dst;
      std::uint8_t m_pad0[20];
      std::float_t m_fraction;
      std::int32_t m_contents;
      std::uint16_t m_disp_flags;
      std::uint8_t m_solid, m_start_solid;
      std::uint8_t m_pad1[4];
      char* m_name;
      std::uint16_t m_surface_props, m_flags;
      std::int32_t m_hit_group;
      std::uint8_t m_pad2[4];
      cs::entity_t* m_entity;
      std::int32_t m_hitbox;
   };
}
