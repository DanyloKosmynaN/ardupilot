#include "mode.h"

#include "Tracker.h"

void ModeMAVLink::update()
{
    Parameters &g = tracker.g;

    const float yaw_deg = wrap_180(_target_yaw_deg + g.yaw_trim);
    const float pitch_deg = constrain_float(_target_pitch_deg + g.pitch_trim, g.pitch_min, g.pitch_max);

    float yaw = yaw_deg * 100; // target yaw in centidegrees
    float pitch = pitch_deg * 100; // target pitch in centidegrees

    const bool direction_reversed = get_ef_yaw_direction();

    calc_angle_error(pitch, yaw, direction_reversed);

    float bf_pitch;
    float bf_yaw;
    convert_ef_to_bf(pitch, yaw, bf_pitch, bf_yaw);

    tracker.update_pitch_servo(bf_pitch);
    tracker.update_yaw_servo(bf_yaw);
}
