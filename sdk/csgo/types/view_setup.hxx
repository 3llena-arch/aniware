#pragma once

namespace n_cs {
   const struct view_setup_t {
		std::int8_t pad0[176];
		std::float_t m_fov, m_viewmodel_fov;
		n_cs::vec3_t< std::float_t >m_origin, m_view_angles;
		std::int8_t pad1[124];
   };
}
