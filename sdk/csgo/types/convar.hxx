#pragma once

namespace cs {
   const struct convar_t {
      std::uint8_t m_pad0[28];
      cs::convar_t* m_parent;
      char* m_default;
      char* m_string;
      std::uint8_t m_pad1[48];
   };
}
