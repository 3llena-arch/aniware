#pragma once

namespace n_cs::engine {
   static std::ptrdiff_t m_ptr;

   [[ nodiscard ]]
   const n_cs::vec2_t< std::size_t >screen_size( ) {
      if ( !m_ptr )
         return { };
      n_cs::vec2_t< std::size_t >size{ };
      
      using call_t = std::int32_t( __stdcall* )( std::uint32_t*, std::uint32_t* );
      ptr< call_t >( m_ptr, 5 )( &size.m_x, &size.m_y );
      return size;
   }

   [[ nodiscard ]]
   const n_cs::player_info_t player_info(
      const std::int32_t& ent_index
   ) {
      if ( !m_ptr )
         return { };
      n_cs::player_info_t info{ };

      using call_t = std::uint8_t( __stdcall* )( std::int32_t, n_cs::player_info_t& );
      ptr< call_t >( m_ptr, 8 )( ent_index, info );
      return info;
   }

   [[ nodiscard ]]
   const std::int32_t player_by_uid(
      const std::int32_t user_id
   ) {
      if ( !m_ptr || !user_id )
         return 0;

      using call_t = std::int32_t( __stdcall* )( std::int32_t );
      return ptr< call_t >( m_ptr, 9 )( user_id );
   }

   [[ nodiscard ]]
   const n_cs::vec3_t< std::float_t >get_angles( ) {
      if ( !m_ptr )
         return { };
      n_cs::vec3_t< std::float_t >angles{ };

      using call_t = std::int32_t( __stdcall* )( n_cs::vec3_t< std::float_t >& );
      ptr< call_t >( m_ptr, 18 )( angles );
      return angles;
   }

   const std::uint8_t set_angles(
      const n_cs::vec3_t< std::float_t >&angles
   ) {
      if ( !m_ptr )
         return 0;
      
      using call_t = std::int32_t( __stdcall* )( n_cs::vec3_t< std::float_t > );
      return !!ptr< call_t >( m_ptr, 19 )( angles );
   }

   [[ nodiscard ]]
   const std::int32_t max_clients( ) {
      if ( !m_ptr )
         return 0;

      using call_t = std::int32_t( __stdcall* )( );
      return ptr< call_t >( m_ptr, 20 )( );
   }

   [[ nodiscard ]]
   const std::uint8_t is_in_game( ) {
      if ( !m_ptr )
         return 0;

      using call_t = std::uint8_t( __stdcall* )( );
      return !!ptr< call_t >( m_ptr, 26 )( );
   }

   [[ nodiscard ]]
   const std::uint8_t is_connected( ) {
      if ( !m_ptr )
         return 0;

      using call_t = std::uint8_t( __stdcall* )( );
      return !!ptr< call_t >( m_ptr, 27 )( );
   }
}
