#pragma once

namespace n_cs::engine_cvar {
	static std::ptrdiff_t m_ptr;

	[[ nodiscard ]]
	const n_cs::convar_t* by_name(
		const std::string_view& name
	) {
		if ( !m_ptr || name.empty( ) )
			return { };

		using call_t = n_cs::convar_t*( __stdcall* )( const char* );
		return ptr< call_t >( m_ptr, 15 )( name.data( ) );
	}
}
