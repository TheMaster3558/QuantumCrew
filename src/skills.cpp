#include "main.hpp"


///
// Skills Auton
///
void skills() {
    catapult.move_relative(500, 600);

    pros::delay(13000);
    chassis.set_drive_pid(-25, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(25.5, DRIVE_SPEED, true);
    chassis.wait_drive();

    pros::delay(13000);
    chassis.set_drive_pid(-25, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(25.5, DRIVE_SPEED, true);
    chassis.wait_drive();

    pros::delay(13000);
    chassis.set_drive_pid(-30, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::LEFT_SWING, -45, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-15, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::LEFT_SWING, -20, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();
}
