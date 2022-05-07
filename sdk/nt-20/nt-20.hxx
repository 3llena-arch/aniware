#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <functional>
#include <cstdint>
#include <optional>

#include "include/library.hxx"
#include "include/tlhelp32.hxx"
#include "include/types.hxx"
#include "include/window.hxx"

/*
enum class snap_flag_t : std::uint8_t {
   process = 2,
   thread = 4,
   module = 8
};

const struct snap_process_t : process_entry_t {
   std::string_view m_file_name;
   std::vector< module_entry_t >m_modules;
   std::vector< thread_entry_t >m_threads;
};

[[ nodiscard ]]
const std::optional< std::vector< process_entry_t > >get_process_list( ) {
   const std::ptrdiff_t snap{ nt::create_toolhelp32_snapshot( snap_flag_t::process, 0 ) };
   if ( !snap )
      return std::nullopt;

   const process_entry_t entry{ .m_size = sizeof( process_entry_t ) };
   std::vector< process_entry_t >list{ };
   
   if ( nt::process32_first( snap, reinterpret_cast< std::ptrdiff_t >( &entry ) ) )
      list.emplace_back( entry );

   while ( nt::process32_next( snap, reinterpret_cast< std::ptrdiff_t >( &entry ) ) )
      list.emplace_back( entry );

   if ( !nt::close_handle( snap ) )
      return std::nullopt;

   return list.empty( ) ? std::nullopt : std::make_optional( std::move( list ) );
}

[[ nodiscard ]]
const std::optional< const std::vector< module_entry_t > >get_module_list(
   const process_entry_t pe
) {
   const std::ptrdiff_t snap{ nt::create_toolhelp32_snapshot( snap_flag_t::module, pe.m_process_id ) };
   if ( !snap )
      return std::nullopt;

   const module_entry_t entry{ .m_size = sizeof( module_entry_t ) };
   std::vector< module_entry_t >list{ };

   if ( nt::module32_first( snap, reinterpret_cast< std::ptrdiff_t >( &entry ) ) )
      list.emplace_back( entry );

   while ( nt::module32_next( snap, reinterpret_cast< std::ptrdiff_t >( &entry ) ) )
      list.emplace_back( entry );

   if ( !nt::close_handle( snap ) )
      return std::nullopt;

   return list.empty( ) ? std::nullopt : std::make_optional( std::move( list ) );
}

[[ nodiscard ]]
const std::optional< const std::vector< thread_entry_t > >get_thread_list(
   const process_entry_t pe
) {
   const std::ptrdiff_t snap{ nt::create_toolhelp32_snapshot( snap_flag_t::thread, pe.m_process_id ) };
   if ( !snap )
      return std::nullopt;

   const thread_entry_t entry{ .m_size = sizeof( thread_entry_t ) };
   std::vector< thread_entry_t >list{ };

   if ( nt::thread32_first( snap, reinterpret_cast< std::ptrdiff_t >( &entry ) ) )
      list.emplace_back( entry );

   while ( nt::thread32_next( snap, reinterpret_cast< std::ptrdiff_t >( &entry ) ) )
      list.emplace_back( entry );

   if ( !nt::close_handle( snap ) )
      return std::nullopt;
   
   return list.empty( ) ? std::nullopt : std::make_optional( std::move( list ) );
}

export const void enumerate(
   const std::function< void( const snap_process_t ) >&callback
) {
   const auto process_list = get_process_list( );
   if ( !process_list.has_value( ) )
      return;

   for ( auto it : process_list.value( ) ) {
      const snap_process_t ctx{ 
         .m_file_name = std::string_view{ reinterpret_cast< char* >( it.m_file_name ) },
         .m_modules = get_module_list( it ).value( ),
         .m_threads = get_thread_list( it ).value( )
      };
      callback( std::move( ctx ) );
   }
}
*/
