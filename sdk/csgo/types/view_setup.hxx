#pragma once

namespace n_cs {
   const struct view_setup_t {
		std::uint8_t m_pad0[176];
		std::float_t m_fov, m_viewmodel_fov;
		n_cs::vec3_t< std::float_t >m_origin, m_view_angles;
		std::uint8_t m_pad1[124];
   };
}
