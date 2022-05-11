#pragma once

namespace n_cs {
   [[ nodiscard ]]
   const std::unordered_map< std::string, std::ptrdiff_t >fetch_interfaces( ) {
      const auto images{ n_nt::fetch_images( ) };
      if ( images.empty( ) )
         return { };
      std::unordered_map< std::string, std::ptrdiff_t >map{ };

      for ( auto& [key, val] : images ) {
         auto delim{ n_nt::proc_address( val, "CreateInterface" ) };
         if ( !delim || key.find( L"crashhandler.dll" ) != std::wstring::npos )
            continue;

         auto ctx{ ptr< std::uint8_t* >( val ) };
         if ( !ctx )
            continue;

         while ( ctx[4] != 0x57
              || ctx[5] != 0x85
              || ctx[6] != 0xf6
              || ctx[7] != 0x74
              || ctx[8] != 0x38 )
            ctx++;
         
         struct iter_t { std::ptrdiff_t m_ptr; 
            char* m_name; iter_t* m_next; };

         for ( auto it{ **ptr< iter_t*** >( ctx ) }; it; it = it->m_next ) {
            if ( !it->m_name )
               continue;
            map.emplace( it->m_name, it->m_ptr );
         }
      }
      return map;
   }
}
