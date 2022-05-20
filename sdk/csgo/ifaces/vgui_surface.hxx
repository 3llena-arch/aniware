#pragma once

namespace n_cs::vgui_surface {
	static std::ptrdiff_t m_ptr;

	const std::uint8_t set_color(
		const std::uint8_t r,
		const std::uint8_t g,
		const std::uint8_t b,
		const std::uint8_t a = 255
	) {
		auto ctx{ ptr< std::uint8_t* >( m_ptr + 0x2c ) };
		if ( !ctx )
			return 0;

		ctx[ 0 ] = r;
		ctx[ 1 ] = g;
		ctx[ 2 ] = b;
		ctx[ 3 ] = a;

		return 1;
	}

	const std::uint8_t draw_line(
		const n_cs::vec2_t< std::uint32_t >&src,
		const n_cs::vec2_t< std::uint32_t >&dst
	) {
		using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t );
		return !!ptr< call_t >( m_ptr, 19 )( m_ptr, src.m_x, src.m_y, dst.m_x, dst.m_y );
	}
}
