#pragma once

namespace n_cs {
   const std::uint8_t modify_retaddr(
      const n_nt::entry_flag_t& flag
   ) {
      auto images{ n_nt::fetch_images( ) };
      if ( images.empty( ) )
         return 0;

      std::vector< std::ptrdiff_t >list{ 
         images[L"client.dll"],
         images[L"engine.dll"],
         images[L"studiorender.dll"],
         images[L"materialsystem.dll"]
      };

      for ( std::size_t i{ }; i < list.size( ); i++ ) {
         auto ctx{ ptr< std::uint8_t* >( list[ i ] ) };
         if ( !ctx )
            continue;

         auto it{ ptr< std::ptrdiff_t >( ctx ) + 0xd0 + ( 0xd * i ) };
         if ( !it )
            continue;

         auto head_flag{ n_nt::mem_protect( it, 0x40, 13 ) };
         if ( !head_flag )
            continue;

         if ( flag == n_nt::entry_flag_t::process_attach ) {
            while ( ctx[2] != 0xec
                 || ctx[3] != 0x56
                 || ctx[4] != 0x8b
                 || ctx[5] != 0xf1
                 || ctx[6] != 0x33
                 || ctx[7] != 0xc0
                 || ctx[8] != 0x57 )
               ctx++;

            auto fn{ ptr< std::ptrdiff_t >( ctx ) };
            if ( !fn )
               continue;

            const std::uint8_t buf[9]{ 
               0x55, 0x89, 0xe5, 
               0xb0, 0x01, 0x5d, 
               0xc2, 0x04, 0x00 
            };

            auto old_flag{ n_nt::mem_protect( fn, 0x40, 9 ) };
            if ( !old_flag )
               continue;

            if ( !std::memcpy( ptr< void* >( it + 4 ), ctx, 9 )
              || !std::memcpy( ptr< void* >( it ), &fn, 4 ) 
              || !std::memcpy( ptr< void* >( fn ), buf, 9 ) )
               continue;

            n_nt::mem_protect( fn, old_flag, 9 );
         }

         if ( flag == n_nt::entry_flag_t::process_detach ) {
            auto fn{ *ptr< std::ptrdiff_t* >( it ) };
            if ( !fn )
               continue;

            std::uint8_t buf[9]{ };
            if ( !std::memcpy( buf, ptr< void* >( it + 4 ), 9 ) )
               continue;

            auto old_flag{ n_nt::mem_protect( fn, 0x40, 9 ) };
            if ( !old_flag )
               continue;

            if ( !std::memcpy( ptr< void* >( fn ), buf, 9 )
              || !std::memset( ptr< void* >( it ), 0, 13 ) )
               continue;

            n_nt::mem_protect( fn, old_flag, 9 );
         }
         n_nt::mem_protect( it, head_flag, 13 );
      }
      return 1;
   }
}