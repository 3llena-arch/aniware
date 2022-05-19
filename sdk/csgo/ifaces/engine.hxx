#pragma once

namespace n_cs::engine {
   static std::ptrdiff_t m_ptr;

   [[ nodiscard ]]
   const n_cs::vec2_t< std::size_t >screen_size( ) {
      if ( !m_ptr )
         return { };
      n_cs::vec2_t< std::size_t >size{ };
      
      using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, std::uint32_t*, std::uint32_t* );
      ptr< call_t >( m_ptr, 5 )( m_ptr, &size.m_x, &size.m_y );
      return size;
   }

   [[ nodiscard ]]
   const n_cs::player_info_t player_info(
      const std::uint32_t& ent_index
   ) {
      if ( !m_ptr )
         return { };
      n_cs::player_info_t info{ };

      using call_t = std::uint8_t( __thiscall* )( std::ptrdiff_t, std::uint32_t, n_cs::player_info_t& );
      ptr< call_t >( m_ptr, 8 )( m_ptr, ent_index, info );
      return info;
   }

   [[ nodiscard ]]
   const std::int32_t player_by_uid(
      const std::uint32_t& user_id
   ) {
      if ( !m_ptr || !user_id )
         return 0;

      using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, std::uint32_t );
      return ptr< call_t >( m_ptr, 9 )( m_ptr, user_id );
   }

   [[ nodiscard ]]
   const n_cs::vec3_t< std::float_t >get_angles( ) {
      if ( !m_ptr )
         return { };
      n_cs::vec3_t< std::float_t >angles{ };

      using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, n_cs::vec3_t< std::float_t >& );
      ptr< call_t >( m_ptr, 18 )( m_ptr, angles );
      return angles;
   }

   const std::uint8_t set_angles(
      const n_cs::vec3_t< std::float_t >&angles
   ) {
      if ( !m_ptr )
         return 0;
      
      using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t, n_cs::vec3_t< std::float_t > );
      return !!ptr< call_t >( m_ptr, 19 )( m_ptr, angles );
   }

   [[ nodiscard ]]
   const std::int32_t max_clients( ) {
      if ( !m_ptr )
         return 0;

      using call_t = std::int32_t( __thiscall* )( std::ptrdiff_t );
      return ptr< call_t >( m_ptr, 20 )( m_ptr );
   }

   [[ nodiscard ]]
   const std::uint8_t is_in_game( ) {
      if ( !m_ptr )
         return 0;

      using call_t = std::uint8_t( __thiscall* )( std::ptrdiff_t );
      return !!ptr< call_t >( m_ptr, 26 )( m_ptr );
   }

   [[ nodiscard ]]
   const std::uint8_t is_connected( ) {
      if ( !m_ptr )
         return 0;

      using call_t = std::uint8_t( __thiscall* )( std::ptrdiff_t );
      return !!ptr< call_t >( m_ptr, 27 )( m_ptr );
   }
}
