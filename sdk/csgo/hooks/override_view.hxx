#pragma once

using override_view_t = std::int32_t( __stdcall* )( n_cs::view_setup_t* );
static override_view_t __override_view;

float dd = 10.f;

const std::int32_t override_view(
   n_cs::view_setup_t* view_setup
) {
   return __override_view( view_setup );
}
