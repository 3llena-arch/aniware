#pragma once

#include "include/types.hxx"
#include "include/library.hxx"

namespace n_nt {
#ifdef __debug
   const std::uint8_t modify_console(
      const n_nt::entry_flag_t& flag
   ) {
      if ( flag == n_nt::entry_flag_t::process_attach ) {
         if ( !n_nt::alloc_console( ) )
            return 0;
         return std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 2 ) );
      }

      if ( flag == n_nt::entry_flag_t::process_detach ) {
         if ( std::fclose( __acrt_iob_func( 0 ) )
           || std::fclose( __acrt_iob_func( 1 ) )
           || std::fclose( __acrt_iob_func( 2 ) ) )
            return 0;
         return n_nt::free_console( );
      }
      return 0;
   }
#endif
   [[ nodiscard ]]
   const std::unordered_map< std::string, std::ptrdiff_t >fetch_modules( ) {
      const n_nt::ldr_entry_t* src{ };

      _asm mov eax, fs:24       ; get teb
      _asm mov eax, [eax + 48]  ; peb
      _asm mov eax, [eax + 12]  ; get ldr
      _asm add eax, 20          ; loaded list
      _asm mov src, eax         ; ret

      if ( !src )
         return { };

      std::unordered_map< std::string, std::ptrdiff_t >list{ };
      for ( auto ctx{ src->m_flink }; ctx != src; ctx = ctx->m_flink ) {

         const std::wstring dll{ ctx->m_full_name, ctx->m_full_name + ( ctx->m_length / 2 ) };
         if ( dll.empty( ) )
            continue;

         std::wstring_convert< std::codecvt_utf8_utf16< wchar_t > >conv{ };
         std::string out{ conv.to_bytes( dll ) };
         for ( auto &i : out )
            i = static_cast< char >( std::tolower( i ) );

         list.emplace( std::string{ out.begin( ), out.begin( ) 
            + ( out.length( ) - 4 ) }, ctx->m_base_address );
      }
      return list;
   }
}
