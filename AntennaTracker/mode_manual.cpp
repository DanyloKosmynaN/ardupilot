#include "Tracker.h"

/*
 * Manual control mode
 */

/*
 * update_manual - runs the manual controller
 *  called at 50hz while control mode is 'MANUAL'
 */
void ModeManual::update()
{
    const float yaw_cmd = (rc().channel(CH_YAW)->get_radio_in() - 1500.0f) / 5.0f;
    const float pitch_cmd = (rc().channel(CH_PITCH)->get_radio_in() - 1500.0f) / 5.0f;

    tracker.set_motor_output(SRV_Channel::k_tracker_yaw, yaw_cmd);
    tracker.set_motor_output(SRV_Channel::k_tracker_pitch, pitch_cmd);
}
