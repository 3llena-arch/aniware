#pragma once

using create_move_t = std::int32_t( __stdcall* )( std::float_t, cs::user_cmd_t* );
static create_move_t __create_move;

const std::int32_t create_move(
   const std::float_t sample_time [[ maybe_unused ]],
   cs::user_cmd_t* user_cmd
) {
   return __create_move( sample_time, user_cmd );
}
