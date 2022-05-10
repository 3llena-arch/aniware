#pragma once

namespace n_cs {
   const std::optional< std::unordered_map< std::string, std::ptrdiff_t > >fetch_interfaces(
      const std::vector< std::string >&delim
   ) {
      const auto modules{ n_nt::fetch_modules( ) };
      if ( !modules.has_value( ) || delim.empty( ) )
         return std::nullopt;

      std::unordered_map< std::string, std::ptrdiff_t >list{ };
      for ( auto [ key, val ] : modules.value( ) ) {
         if ( std::find( delim.begin( ), delim.end( ), key ) == delim.end( ) )
            continue;

         auto ctx{ reinterpret_cast< std::uint8_t* >( val ) };
         while ( ctx[ 4 ] != 0x57
              || ctx[ 5 ] != 0x85
              || ctx[ 6 ] != 0xf6
              || ctx[ 7 ] != 0x74
              || ctx[ 8 ] != 0x38 )
            ctx++;

         const struct iface_t{ std::ptrdiff_t m_ptr; char* m_name; iface_t* m_next; };
         auto it{ **reinterpret_cast< iface_t*** >( ctx ) };
         if ( !it )
            continue;

         for ( ; it; it = it->m_next ) {
            if ( !it->m_name )
               continue;

            std::string out{ };
            for ( std::size_t i{ }; i < std::strlen( it->m_name ) - 3; i++ )
               out += static_cast< char >( std::tolower( it->m_name[ i ] ) );
            list.emplace( out, it->m_ptr );
         }
      }
      return list.empty( ) ? std::nullopt : std::make_optional( list );
   }
   static std::optional< std::unordered_map< std::string, std::ptrdiff_t > >m_interfaces{ };
}