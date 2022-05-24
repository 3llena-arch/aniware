#pragma once

namespace cs {
   const struct interface_t {
      std::ptrdiff_t m_ptr;
      char* m_name; 
      cs::interface_t* m_next;
   };
}
