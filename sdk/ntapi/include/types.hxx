#pragma once

namespace n_nt {
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
      ldr_entry_t* m_flink;
      ldr_entry_t* m_blink;
      std::int8_t pad0[ 8 ];
      std::ptrdiff_t m_base_address;
      std::int8_t pad1[ 16 ];
      std::int16_t m_length, m_max_length;
      wchar_t* m_full_name;
      std::int8_t pad2[ 28 ];
   };

   const struct module_entry_t {
      std::int32_t m_size, m_module_id, m_process_id;
      std::int32_t m_global_usage_count, m_process_usage_count;
      std::ptrdiff_t m_base_address;
      std::int32_t m_base_size;
      std::ptrdiff_t m_module_handle;
      char m_file_name[ 256 ], m_file_path[ 260 ];
   };

   const struct process_entry_t {
      std::int32_t m_size, m_usage_count, m_process_id;
      std::ptrdiff_t m_default_heap_id;
      std::int32_t m_module_id, m_thread_count, m_parent_process_id;
      std::int32_t m_priority_class, m_flags;
      char m_file_name[ 260 ];
   };

   const struct thread_entry_t {
      std::int32_t m_size, m_usage_count, m_thread_id, m_owner_process_id;
      std::int32_t m_base_priority, m_delta_priority, m_flags;
   };
}
