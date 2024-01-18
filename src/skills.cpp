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

    catapult.move_velocity(catapult_velocity);
    pros::delay(45000);

    if (catapult_angle() < CATAPULT_HOLD_ANGLE) {
        pros::Task task{[=] {
            while (catapultPID.exit_condition(catapult) == ez::RUNNING) {
                catapult.move(catapultPID.compute(catapult_angle()));
                pros::delay(ez::util::DELAY_TIME);
            }
        }};
    }

    chassis.set_swing_pid(ez::LEFT_SWING, 135, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(60, DRIVE_SPEED, true);
    chassis.wait_drive();


}
