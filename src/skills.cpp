#include "main.hpp"


///
// Skills Auton
///
void skills() {
    chassis.set_angle(135);

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, 180, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-10, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, 75, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();

    catapult.move_velocity(catapultVelocity);
    pros::delay(45);

    chassis.set_swing_pid(ez::LEFT_SWING, 135, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(60, DRIVE_SPEED, true);
    chassis.wait_drive();


}
