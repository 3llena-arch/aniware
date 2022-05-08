#include "sdk/sdk.hxx"

const std::int32_t DllMain(
   const std::ptrdiff_t instance,
   const std::int32_t call_reason,
   const std::ptrdiff_t reserved
) {
   ( instance, call_reason, reserved );

   return 0;
}

#include <chrono>

using namespace std::string_view_literals;
using namespace std::string_literals;

const std::int32_t __cdecl main(
   const std::int32_t argc,
   const std::int8_t* argv[ ]
) {
   ( argc, argv );

   int processes{ }, threads{ }, modules{ };
   int extra{ };

   auto clock = std::chrono::high_resolution_clock::now( );
   n_nt::for_every_process( [ & ]( const n_nt::snap_process_t& ctx ) {
      processes++;
      if ( !ctx.m_threads.has_value( ) || !ctx.m_modules.has_value( ) ) {
         std::cerr << "* no threads or modules in process " 
            << ctx.m_name.value_or( "**error**" ) << std::endl;
         return;
      }

      threads += std::make_optional( ctx.m_threads.value( ).size( ) ).value_or( 0 );
      modules += std::make_optional( ctx.m_modules.value( ).size( ) ).value_or( 0 );

      if ( ctx.m_name == "devenv.exe"s ) {
         const auto mods = ctx.m_modules.value( );
         if ( mods.empty( ) )
            return;
         std::for_each( mods.begin( ), mods.end( ), 
         [ ]( const std::pair< std::string, n_nt::module_entry_t >&ent ){
            std::cout << ent.first << std::endl;
         });
      }
      return;
   });
   std::cout << "\nqueried\n\t" << processes << "\tprocesses\n\t" << modules << "\tmodules\n\t"
      << threads << "\tthreads\n\textra" << extra << "\n";

   std::cout << "in " << std::chrono::duration_cast< std::chrono::milliseconds >
      ( std::chrono::high_resolution_clock::now( ) - clock ) << "ms" << std::endl;
}

