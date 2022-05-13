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
   const std::ptrdiff_t fetch_ldr_head( ) {
      _asm mov eax, fs:24       ; get teb
      _asm mov eax, [eax + 48]  ; peb
      _asm mov eax, [eax + 12]  ; get ldr
      _asm add eax, 20          ; loaded list
   }

   [[ nodiscard ]]
   const std::unordered_map< std::wstring, std::ptrdiff_t >fetch_images( ) {
      const auto head{ ptr< n_nt::ldr_entry_t* >( n_nt::fetch_ldr_head( ) ) };
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
}
