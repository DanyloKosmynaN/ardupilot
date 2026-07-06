#include "Tracker.h"

/*
 * GCS controlled servo test mode
 */

/*
 * set_servo - sets the yaw or pitch servo pwm directly
 *  servo_num are 1 for yaw, 2 for pitch
 */
bool ModeServoTest::set_servo(uint8_t servo_num, uint16_t pwm)
{
    // convert servo_num from 1~2 to 0~1 range
    servo_num--;

    // exit immediately if servo_num is invalid
    if (servo_num != CH_YAW && servo_num != CH_PITCH) {
        return false;
    }

    hal.rcout->cork();

    // set yaw motor command and send output over SBUS
    if (servo_num == CH_YAW) {
        const float yaw_cmd = (static_cast<float>(pwm) - 1500.0f) / 5.0f;
        tracker.set_motor_output(SRV_Channel::k_tracker_yaw, yaw_cmd);
    }

    // set pitch motor command and send output over SBUS
    if (servo_num == CH_PITCH) {
        const float pitch_cmd = (static_cast<float>(pwm) - 1500.0f) / 5.0f;
        tracker.set_motor_output(SRV_Channel::k_tracker_pitch, pitch_cmd);
    }

    SRV_Channels::calc_pwm();
    SRV_Channels::output_ch_all();

    hal.rcout->push();

    // return success
    return true;
}
