#pragma once

#include "include/types.hxx"
#include "include/library.hxx"
#include "include/tlhelp32.hxx"

namespace n_nt {
   [[ nodiscard ]]
   const std::optional< std::unordered_map< std::string, std::ptrdiff_t > >module_list( ) {
      PPEB peb{ };
      _asm mov eax, fs:0x18
      _asm mov eax, [eax+0x30]
      _asm mov peb, eax
#pragma warning (disable: 6011 4244)
      auto cur = &peb->Ldr->InMemoryOrderModuleList;
      std::unordered_map< std::string, std::ptrdiff_t >list{ };
      for ( auto entry = cur->Flink->Flink->Flink->Flink; entry != cur; entry = entry->Flink ) {
         auto data_table = reinterpret_cast< PLDR_DATA_TABLE_ENTRY >( entry );
         list.emplace( std::string{ data_table->FullDllName.Buffer, data_table->FullDllName.Buffer + (data_table->FullDllName.Length / 2) }, reinterpret_cast< std::ptrdiff_t >( *data_table->Reserved2 ) );
      }
      return list.empty( ) ? std::nullopt : std::make_optional( list );
   }

#ifdef __debug
   const std::uint8_t modify_console(
      const std::optional < n_nt::entry_flag_t >&flag
   ) {
      if ( !flag.has_value( ) )
         return 0;

      if ( flag.value( ) == n_nt::entry_flag_t::process_attach ) {
         if ( !n_nt::alloc_console( ) )
            return 0;

         return std::freopen( "conin$", "r", __acrt_iob_func( 0 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 1 ) )
             && std::freopen( "conout$", "w", __acrt_iob_func( 2 ) );
      }

      if ( flag.value( ) == n_nt::entry_flag_t::process_detach ) {
         if ( std::fclose( __acrt_iob_func( 0 ) )
           || std::fclose( __acrt_iob_func( 1 ) )
           || std::fclose( __acrt_iob_func( 2 ) ) )
            return 0;

         return n_nt::free_console( );
      }
      return 0;
   }
#endif
}
