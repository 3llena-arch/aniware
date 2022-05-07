#pragma once

const struct module_entry_t {
   std::int32_t m_size, m_module_id, m_process_id;
   std::int32_t m_global_usage_count, m_process_usage_count;
   std::ptrdiff_t m_base_address;
   std::int32_t m_base_size;
   std::ptrdiff_t m_module_handle;
   std::int8_t m_file_name[ 256 ], m_file_path[ 260 ];
};
