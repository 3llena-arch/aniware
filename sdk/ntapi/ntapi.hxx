#pragma once

#include "include/types.hxx"
#include "include/library.hxx"

namespace nt {
#ifdef __debug
   const std::uint8_t modify_console(
      const nt::entry_flag_t& flag
   ) {
      if ( flag == nt::entry_flag_t::process_attach ) {
         if ( !nt::alloc_console( ) )
            return 0;
         return std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 2 ) );
      }

      if ( flag == nt::entry_flag_t::process_detach ) {
         if ( std::fclose( __acrt_iob_func( 0 ) )
           || std::fclose( __acrt_iob_func( 1 ) )
           || std::fclose( __acrt_iob_func( 2 ) ) )
            return 0;
         return nt::free_console( );
      }
      return 0;
   }
#endif
   [[ nodiscard ]]
   const std::ptrdiff_t fetch_ldr_head( ) {
      _asm mov eax, fs:24       ; get teb
      _asm mov eax, [eax + 48]  ; peb
      _asm mov eax, [eax + 12]  ; get ldr
      _asm add eax, 20          ; loaded list
   }

   [[ nodiscard ]]
   const std::unordered_map< std::wstring, std::ptrdiff_t >fetch_images( ) {
      const auto head{ ptr< nt::ldr_entry_t* >( nt::fetch_ldr_head( ) ) };
      if ( !head )
         return { };

      std::unordered_map< std::wstring, std::ptrdiff_t >map{ };
      for ( auto ctx{ head->m_next }; ctx != head; ctx = ctx->m_next ) {
         if ( !ctx->m_name )
            continue;
         map.emplace( std::wstring{ ctx->m_name, 
            ptr< std::size_t >( ctx->m_length >> 1 ) }, ctx->m_ptr );
      }
      return map;
   }

   [[ nodiscard ]]
   const __declspec( naked ) std::ptrdiff_t alloc_stub(
      const std::ptrdiff_t wow64
   ) {
      _asm mov eax, 24      ; index
      _asm mov edx, wow64   ; translation
      _asm call edx         ; make call
      _asm retn 24          ; add esp
   }

   [[ nodiscard ]]
   const std::ptrdiff_t mem_alloc(
      const std::ptrdiff_t wow64,
      const std::size_t size,
      const std::ptrdiff_t addr = 0
   ) {
      using call_t = std::int32_t( __stdcall* )( std::ptrdiff_t, const std::ptrdiff_t*,
         std::uint32_t, const std::size_t*, std::uint32_t, std::uint32_t );

      ptr< call_t >( &alloc_stub )( -1, &addr, 0, &size, 0x3000, 0x40 );
      return addr;
   }

   template< std::uint32_t id, typename... arg_t >
   const std::uint8_t create_call(
      const std::ptrdiff_t wow64,
      const arg_t... args
   ) {
      std::uint8_t bytes[15] = {
         0xb8, 0x00, 0x00, 0x00, 0x00, 
         0xba, 0x00, 0x00, 0x00, 0x00, 
         0xff, 0xd2, 
         0xc2, 0x00, 0x00
      };

      auto ctx{ mem_alloc( wow64, sizeof bytes ) };
      if ( !ctx )
         return 0;

      *ptr< std::uint32_t* >( &bytes[0x1] ) = id;
      *ptr< std::uint32_t* >( &bytes[0x6] ) = wow64;
      *ptr< std::uint16_t* >( &bytes[0xd] ) = ( sizeof( arg_t ) + ... );

      for ( std::size_t i{ }; i < sizeof bytes ; i++ )
         ptr< std::uint8_t* >( ctx )[ i ] = bytes[ i ];

      return ptr< std::int32_t( __stdcall* )( arg_t... ) >( ctx )( args... );
   }

   [[ nodiscard ]]
   const std::ptrdiff_t wow64_translation(
      const std::ptrdiff_t module
   ) {
      auto ctx{ ptr< std::uint8_t* >( module ) };
      if ( !ctx )
         return 0;

      while ( ctx[ 10 ] != 0xb8 
            || ctx[ 15 ] != 0xba
            || ctx[ 20 ] != 0xff 
            || ctx[ 21 ] != 0xd2 )
         ctx++;

      return *ptr< std::ptrdiff_t* >( ctx + 0x10 );
   }
}
