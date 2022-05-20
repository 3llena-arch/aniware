#pragma once

using create_move_t = std::int32_t( __stdcall* )( std::float_t, n_cs::user_cmd_t* );
static create_move_t __create_move;

const std::int32_t create_move(
   const std::float_t sample_time [[ maybe_unused ]],
   n_cs::user_cmd_t* user_cmd
) {
   auto lp = n_cs::client_entities::by_index(n_cs::engine::local_index());
   if (!lp)
      return 0;
   for (int i = 1; i <= 32; i++) {
      auto ctx = n_cs::client_entities::by_index(i);
      if (!ctx || ctx->is_dead() || ctx->is_dormant() || ctx == lp)
         continue;
      auto e = ctx->origin();
      e.m_z += 64.f;
      auto d = n_cs::engine_debug::to_screen(e);
      list.push_back({ (unsigned int)d.m_x, (unsigned int)d.m_y });
   }
   return __create_move( sample_time, user_cmd );
}
