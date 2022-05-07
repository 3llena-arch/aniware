#pragma once

export const struct thread_entry_t {
   std::int32_t m_size, m_usage_count, m_thread_id, m_owner_process_id;
   std::int32_t m_base_priority, m_delta_priority, m_flags;
};
