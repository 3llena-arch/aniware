#pragma once

namespace cs {
#pragma pack(1)
   const struct client_state_t {
      std::uint8_t m_pad0[367];
      std::uint32_t m_server_tick, m_client_tick, m_delta_tick;
      std::uint8_t m_pad1[5];
      std::uint16_t m_player_index;
      std::uint8_t m_pad2[264];
      char m_level_name[40];
      std::uint8_t m_pad3[214];
      std::uint16_t m_max_clients;
      std::uint8_t m_pad4[18946];
      cs::vec3_t< std::float_t >m_view_angles;
   };
}
