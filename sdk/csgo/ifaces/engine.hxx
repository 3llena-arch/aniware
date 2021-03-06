#pragma once

namespace cs::engine {
   static std::ptrdiff_t m_ptr;

	[[ nodiscard ]]
	const cs::client_state_t* client_state( ) {
		return *ptr< cs::client_state_t** >( m_ptr + 0x1ce8 );
	}

	[[ nodiscard ]]
	const std::uint16_t local_index( ) {
		auto ctx{ cs::engine::client_state( ) };
		if ( !ctx )
			return 0;
		return ctx->m_player_index + 1;
	}

	[[ nodiscard ]]
	const std::uint16_t max_clients( ) {
		auto ctx{ cs::engine::client_state( ) };
		if ( !ctx )
			return 0;
		return ctx->m_max_clients;
	}
}
