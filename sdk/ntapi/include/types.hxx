#pragma once

namespace nt {
   enum class snap_flag_t : std::uint8_t {
      process = 2,
      thread = 4,
      module = 8
   };

   enum class entry_flag_t : std::int32_t {
      process_detach,
      process_attach,
      thread_attach,
      thread_detach
   };

   const struct ldr_entry_t {
      nt::ldr_entry_t* m_next;
      std::uint8_t m_pad0[12];
      std::ptrdiff_t m_ptr;
      std::uint8_t m_pad1[16];
      std::uint16_t m_length;
      std::uint8_t m_pad2[2];
      wchar_t* m_name;
   };
}
