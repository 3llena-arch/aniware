#pragma once

using frame_notify_t = std::int32_t( __fastcall* )( std::ptrdiff_t, std::ptrdiff_t, std::int32_t );
static frame_notify_t __frame_notify;

const std::int32_t frame_notify(
   const std::ptrdiff_t ecx [[ maybe_unused ]],
   const std::ptrdiff_t edx [[ maybe_unused ]],
   const std::int32_t frame_stage
) {
   return __frame_notify( ecx, edx, frame_stage );
}
