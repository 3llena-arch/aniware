#pragma once

namespace n_cs {
   const struct vec2_t { std::float_t m_x, m_y; };
   const struct vec3_t : vec2_t { std::float_t m_z; };
}
