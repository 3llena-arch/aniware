#pragma once

namespace n_cs::client_prediction {
	static std::ptrdiff_t m_ptr;

	const std::uint8_t setup_move(
		const std::ptrdiff_t entity,
		n_cs::user_cmd_t* user_cmd,
		const std::ptrdiff_t helper,
		const std::ptrdiff_t data
	) {
		if ( !m_ptr || !entity || !user_cmd || !helper || !data )
			return 0;

		using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, std::ptrdiff_t, n_cs::user_cmd_t*, std::ptrdiff_t, std::ptrdiff_t );
		return !!ptr< call_t >( m_ptr, 20 )( m_ptr, entity, user_cmd, helper, data );
	}

	const std::uint8_t finish_move(
		const std::ptrdiff_t entity,
		n_cs::user_cmd_t* user_cmd,
		const std::ptrdiff_t data
	) {
		if ( !m_ptr || !entity || !user_cmd || !data )
			return 0;

		using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, std::ptrdiff_t, n_cs::user_cmd_t*, std::ptrdiff_t );
		return !!ptr< call_t >( m_ptr, 21 )( m_ptr, entity, user_cmd, data );
	}
}
