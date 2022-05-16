#pragma once

namespace n_cs {
   const struct trace_filter_t {
      std::uint8_t m_pad0[4];
      std::ptrdiff_t m_skip;
   };
}
