#pragma once

namespace n_cs::vgui_panel {
	static std::ptrdiff_t m_ptr;

	const std::string name(
		const std::int32_t& panel
	) {
		if ( !m_ptr || !panel )
			return { };
		using call_t = const char*( __thiscall* )( std::ptrdiff_t, std::int32_t );
		return std::string{ ptr< call_t >
			( m_ptr, 36 )( m_ptr, panel ) };
	}
}
