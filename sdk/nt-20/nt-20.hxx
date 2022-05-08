#pragma once

#include "include/library.hxx"
#include "include/types.hxx"
#include "include/tlhelp32.hxx"
#include "include/console.hxx"

namespace n_nt {
   [[ nodiscard ]]
   const std::optional< std::map< std::string, n_nt::process_entry_t > >process_list( ) {
      const auto snap{ n_nt::create_tlhelp32_snapshot( n_nt::snap_flag_t::process ) };
      if ( !snap.has_value( ) || snap.value( ) <= 0 )
         return std::nullopt;

      auto ctx{ std::make_optional( n_nt::process_entry_t{ .m_size = sizeof n_nt::process_entry_t } ) };
      std::map< std::string, n_nt::process_entry_t >list{ };
      
      if ( n_nt::process32_first( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value_or( n_nt::process_entry_t{ } ) );

      while ( n_nt::process32_next( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value_or( n_nt::process_entry_t{ } ) );

      return ( n_nt::close_handle( snap ) && list.empty( ) )
         ? std::nullopt : std::make_optional( list );
   }

   [[ nodiscard ]]
   const std::optional< std::map< std::string, n_nt::module_entry_t > >module_list(
      const std::optional< n_nt::process_entry_t >&entry
   ) {
      const auto snap{ n_nt::create_tlhelp32_snapshot( n_nt::snap_flag_t::module, 
         std::make_optional( entry.value( ).m_process_id ) ) };
      if ( !snap.has_value( ) || snap.value( ) <= 0 )
         return std::nullopt;

      auto ctx{ std::make_optional( n_nt::module_entry_t{ .m_size = sizeof n_nt::module_entry_t } ) };
      std::map< std::string, n_nt::module_entry_t >list{ };

      if ( n_nt::module32_first( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value_or( n_nt::module_entry_t{ } ) );

      while ( n_nt::module32_next( snap, ctx ) )
         list.emplace( ctx.value( ).m_file_name, ctx.value_or( n_nt::module_entry_t{ } ) );

      return ( n_nt::close_handle( snap ) && list.empty( ) )
         ? std::nullopt : std::make_optional( list );
   }

   [[ nodiscard ]]
   const std::optional< std::vector< n_nt::thread_entry_t > >thread_list(
      const std::optional< n_nt::process_entry_t >&entry
   ) {
      const auto snap{ n_nt::create_tlhelp32_snapshot( n_nt::snap_flag_t::thread,
         std::make_optional( entry.value( ).m_process_id ) ) };
      if ( !snap.has_value( ) || snap.value( ) <= 0 )
         return std::nullopt;

      auto ctx{ std::make_optional( n_nt::thread_entry_t{ .m_size = sizeof n_nt::thread_entry_t } ) };
      std::vector< n_nt::thread_entry_t >list{ };

      if ( n_nt::thread32_first( snap, ctx ) )
         list.push_back( ctx.value_or( n_nt::thread_entry_t{ } ) );

      while ( n_nt::thread32_next( snap, ctx ) )
         list.push_back( ctx.value_or( n_nt::thread_entry_t{ } ) );

      return ( n_nt::close_handle( snap ) && list.empty( ) )
         ? std::nullopt : std::make_optional( list );
   }

   const std::uint8_t for_every_process(
      const std::function< void( const n_nt::snap_process_t& ) >&callback
   ) {
      const auto list{ n_nt::process_list( ) };
      if ( !list.has_value( ) || list.value( ).empty( ) )
         return 0;

      for ( const auto [ key, val ] : list.value( ) ) {
         if ( key.empty( ) || !val.m_size )
            continue;
         const n_nt::snap_process_t ctx{
            .m_name = std::make_optional( val.m_file_name ),
            .m_modules = n_nt::module_list( std::make_optional( val ) ),
            .m_threads = n_nt::thread_list( std::make_optional( val ) )
         };
         std::invoke( callback, ctx );
      }
      return 1;
   }
}
