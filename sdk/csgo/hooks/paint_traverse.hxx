#pragma once

using paint_traverse_t = std::int32_t( __fastcall* )( std::int32_t, std::int32_t, std::uint32_t, std::int8_t, std::int8_t );
static paint_traverse_t __paint_traverse;

const std::int32_t __fastcall paint_traverse(
   const std::int32_t ecx [[ maybe_unused ]],
   const std::int32_t edx [[ maybe_unused ]],
   const std::uint32_t panel,
   const std::int8_t repaint,
   const std::int8_t active
) {
   return __paint_traverse( ecx, edx, panel, repaint, active );
}
