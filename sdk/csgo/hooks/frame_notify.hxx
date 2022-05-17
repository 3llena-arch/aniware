#pragma once

using frame_notify_t = std::int32_t( __stdcall* )( std::int32_t );
static frame_notify_t __frame_notify;

const std::int32_t frame_notify(
   const std::int32_t frame_stage
) {
   return __frame_notify( frame_stage );
}
