#pragma once

namespace n_cs::vgui_surface {
	static std::ptrdiff_t m_ptr;

	const std::uint8_t set_color(
		const std::uint32_t r,
		const std::uint32_t g,
		const std::uint32_t b,
		const std::uint32_t a = 255
	) {
		if ( !m_ptr )
			return 0;

		using call_t = std::int32_t( __stdcall* )( std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t );
		return !!ptr< call_t >( m_ptr, 15 )( r, g, b, a );
	}

	const std::uint8_t draw_line(
		const n_cs::vec2_t< std::uint32_t >src,
		const n_cs::vec2_t< std::uint32_t >dst
	) {
		if ( !m_ptr )
			return 0;

		using call_t = std::int32_t( __stdcall* )( std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t );
		return !!ptr< call_t >( m_ptr, 19 )( src.m_x, src.m_y, dst.m_x, dst.m_y );
	}
}
