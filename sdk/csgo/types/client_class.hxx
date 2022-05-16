#pragma once

namespace n_cs {
   const struct client_class_t {
      std::uint8_t m_pad0[8];
      char* m_name;
      std::ptrdiff_t m_recv;
      n_cs::client_class_t* m_next;
      std::uint32_t m_id;
   };
}
