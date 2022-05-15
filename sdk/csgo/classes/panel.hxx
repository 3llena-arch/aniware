#pragma once

namespace n_cs::panel {
	static std::ptrdiff_t m_ptr;

	const std::string name(
		const std::uint32_t panel,
		const std::uint8_t class_name = 0
	) {
		if ( !m_ptr || !panel )
			return { };
		using call_t = const char*( __thiscall* )( std::ptrdiff_t, std::uint32_t );
		return std::string{ ptr< call_t >
			( m_ptr, class_name ? 37 : 36 )( m_ptr, panel ) };
	}
}
