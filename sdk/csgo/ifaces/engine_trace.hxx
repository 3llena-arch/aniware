#pragma once

namespace n_cs::engine_trace {
	static std::ptrdiff_t m_ptr;

	[[ nodiscard ]]
	const std::int32_t point_contents(
		n_cs::vec3_t< std::float_t >&point,
		const std::int32_t content_mask
	) {
		if ( !m_ptr )
			return 0;
		
		using call_t = std::int32_t( __stdcall* )( n_cs::vec3_t< std::float_t >&, std::int32_t );
		return ptr< call_t >( m_ptr, 0 )( point, content_mask );
	}

	const std::uint8_t trace_ray(
		n_cs::trace_ray_t& ray,
		const std::uint32_t trace_mask,
		n_cs::trace_filter_t& filter,
		n_cs::trace_t& trace
	) {
		if ( !m_ptr || !trace_mask )
			return 0;

		using call_t = std::int32_t( __stdcall* )( n_cs::trace_ray_t&, std::uint32_t, n_cs::trace_filter_t&, n_cs::trace_t& );
		return !!ptr< call_t >( m_ptr, 5 )( ray, trace_mask, filter, trace );
	}
}
