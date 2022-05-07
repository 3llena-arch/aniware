#pragma once

export const struct process_entry_t {
   std::int32_t m_size, m_usage_count, m_process_id;
   std::ptrdiff_t m_default_heap_id;
   std::int32_t m_module_id, m_thread_count, m_parent_process_id;
   std::int32_t m_priority_class, m_flags;
   std::int8_t m_file_name[ 260 ];
};
