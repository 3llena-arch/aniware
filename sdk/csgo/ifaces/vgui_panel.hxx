#pragma once

namespace cs::vgui_panel {
	static std::ptrdiff_t m_ptr;

	[[ nodiscard ]]
	const std::string name(
		const std::uint32_t panel_id
	) {
		if ( !panel_id )
			return { };
		using call_t = const char*( __thiscall* )( std::ptrdiff_t, std::uint32_t );
		return std::string{ ptr< call_t >( m_ptr, 36 )( m_ptr, panel_id ) };
	}
}
