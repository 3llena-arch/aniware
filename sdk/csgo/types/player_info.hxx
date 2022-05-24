#pragma once

namespace cs {
   const struct player_info_t {
      std::uint64_t m_version, m_xuid;
      char m_name[128];
      std::int32_t m_user_id;
      std::uint8_t m_pad0[168], m_fake, m_hltv, m_pad1[20];
   };
}
