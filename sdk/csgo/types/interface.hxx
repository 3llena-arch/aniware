#pragma once

namespace n_cs {
   const struct interface_t {
      std::ptrdiff_t m_ptr;
      char* m_name; 
      n_cs::interface_t* m_next;
   };
}
