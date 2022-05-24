#pragma once

namespace cs {
   const struct client_class_t {
      std::uint8_t m_pad0[8];
      char* m_name;
      std::ptrdiff_t m_recv;
      cs::client_class_t* m_next;
      std::int32_t m_id;
   };
}
