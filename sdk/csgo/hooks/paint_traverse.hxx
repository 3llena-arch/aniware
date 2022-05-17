#pragma once

using paint_traverse_t = std::int32_t( __fastcall* )( std::ptrdiff_t, std::ptrdiff_t, std::int32_t, std::uint8_t, std::uint8_t );
static paint_traverse_t __paint_traverse;

const std::int32_t __fastcall paint_traverse(
   const std::ptrdiff_t ecx [[ maybe_unused ]],
   const std::ptrdiff_t edx [[ maybe_unused ]],
   const std::int32_t panel,
   const std::uint8_t repaint,
   const std::uint8_t active
) {
   if ( n_cs::vgui_panel::name( panel ) == "FocusOverlayPanel" ) {
      n_cs::vgui_surface::set_color( 255, 255, 255 );
      n_cs::vgui_surface::draw_line({ 200, 200 }, { 600, 600 });
   }

   return __paint_traverse( ecx, edx, panel, repaint, active );
}
