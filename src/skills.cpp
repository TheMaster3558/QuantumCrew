#include "main.hpp"


///
// Skills Auton
///
void skills() {
    // TODO: Run right flap

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(6, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-20, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_drive();

    catapult.move_velocity(catapultVelocity);
    pros::delay(50000);
    catapult.brake();

    chassis.set_turn_pid(-80, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-10, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, -100, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(10, DRIVE_SPEED);
    chassis.wait_drive();
}
