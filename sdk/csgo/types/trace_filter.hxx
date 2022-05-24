#pragma once

namespace cs {
   const struct trace_filter_t {
      std::uint8_t m_pad0[4];
      cs::entity_t* m_skip;
   };
}
