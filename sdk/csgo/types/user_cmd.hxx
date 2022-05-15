#pragma once

namespace n_cs {
   const struct user_cmd_t {
		std::int8_t pad0[8];
		std::int32_t m_tick_count;
		n_cs::vec3_t< std::float_t >m_view_angles, m_aim_direction;
		std::float_t m_forward, m_side, m_up;
		std::int32_t m_buttons;
		std::int8_t pad1[9];
		std::int32_t m_seed;
		std::int8_t pad2[29];
   };
}
