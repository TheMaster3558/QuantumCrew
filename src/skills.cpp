#include "skills.h"


///
// Skills Auton
///
void skills() {
    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(6, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-20, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_drive();

    catapult.move_velocity(catapultVelocity);
    pros::delay(40000);
    catapult.brake();

    chassis.set_turn_pid(70, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(9.5, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(-7, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(7, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(-15, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(180, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(32, true);
    chassis.wait_drive();
}
