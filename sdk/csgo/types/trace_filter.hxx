#pragma once

namespace n_cs {
   const struct trace_filter_t {
      std::uint8_t m_pad0[4];
      n_cs::entity_t* m_skip;
   };
}