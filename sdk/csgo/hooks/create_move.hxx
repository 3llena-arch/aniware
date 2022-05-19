#pragma once

using create_move_t = std::int32_t( __stdcall* )( std::float_t, n_cs::user_cmd_t* );
static create_move_t __create_move;

const std::int32_t create_move(
   const std::float_t sample_time [[ maybe_unused ]],
   n_cs::user_cmd_t* user_cmd
) {
   for ( std::size_t i{ 1 }; i <= 32; i++ ) {
      auto ctx{ n_cs::client_entities::by_index( i ) };
      if ( !ctx )
         continue;
      if ( !ctx->is_alive( ) )
         continue;

   }

   return __create_move( sample_time, user_cmd );
}
