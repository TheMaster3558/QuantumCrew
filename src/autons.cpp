#include "main.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
// If this is 127 and the robot tries to heading correct, it's only correcting by
// making one side slower.  When this is 87%, it's correcting by making one side
// faster and one side slower, giving better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
    chassis.set_slew_min_power(80, 80);
    chassis.set_slew_distance(7, 7);
    chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
    chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
    chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
    chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
    chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
    chassis.set_slew_min_power(80, 80);
    chassis.set_slew_distance(7, 7);
    chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
    chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
    chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
    chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
    chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
    chassis.set_slew_min_power(80, 80);
    chassis.set_slew_distance(7, 7);
    chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
    chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
    chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
    chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
    chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
    chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
    chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
    chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
    chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
    chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
    chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


///
// Drive Example
///
void drive_example() {
    // The first parameter is target inches
    // The second parameter is max speed the robot will drive at
    // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
    // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(-12, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-12, DRIVE_SPEED);
    chassis.wait_drive();
}


///
// Turn Example
///
void turn_example() {
    // The first parameter is target degrees
    // The second parameter is max speed the robot will drive at


    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();
}


///
// Combining Turn + Drive
///
void drive_and_turn() {
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-24, DRIVE_SPEED, true);
    chassis.wait_drive();
}


///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
    // wait_until will wait until the robot gets to a desired position


    // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_until(6);
    chassis.set_max_speed(
            40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
    chassis.set_drive_pid(-24, DRIVE_SPEED, true);
    chassis.wait_until(-6);
    chassis.set_max_speed(
            40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
    chassis.wait_drive();
}


///
// Swing Example
///
void swing_example() {
    // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
    // The second parameter is target degrees
    // The third parameter is speed of the moving side of the drive


    chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_until(12);

    chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
    chassis.wait_drive();
}


///
// Auto that tests everything
///
void combining_movements() {
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-24, DRIVE_SPEED, true);
    chassis.wait_drive();
}


///
// Interference example
///
void tug(int attempts) {
    for (int i = 0; i < attempts - 1; i++) {
        // Attempt to drive backwards
        printf("i - %i", i);
        chassis.set_drive_pid(-12, 127);
        chassis.wait_drive();

        // If failsafed...
        if (chassis.interfered) {
            chassis.reset_drive_sensor();
            chassis.set_drive_pid(-2, 20);
            pros::delay(1000);
        }
            // If robot successfully drove back, return
        else {
            return;
        }
    }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
    chassis.set_drive_pid(24, DRIVE_SPEED, true);
    chassis.wait_drive();

    if (chassis.interfered) {
        tug(3);
        return;
    }

    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

///
// Do nothing
///
void doNothing() {

}


///
// Auton for when you are on the defensive side in qualifying
// 1. Move forward 6 inches
// 2. Turn on left flap
// 3. Move back 6.5 inches
// 4. Turn off flaps
// 5. Move forward 25 inches
// 6. Turn right 45 degrees from starting position
// 7. Move forward 4 inches and run intake in reverse
// 8. Move back 5 inches and spin around
// 9. Push back 10 inches and push ball in
// 10. Move forward 3 inches
// 11. Rotate back to starting position
// 12. Move back 35 inches
// 13. Turn left 45 degrees
// 14. Move back 15 inches
// 15. Turn on right flap to touch elevation bar
///
void defensiveQual() {
    chassis.set_angle(-45);

    chassis.set_drive_pid(6, DRIVE_SPEED);
    chassis.wait_drive();

    setFlaps(true, false);

    chassis.set_drive_pid(-6.5, DRIVE_SPEED, false);
    chassis.wait_drive();

    setFlaps(false, false);

    chassis.set_drive_pid(25, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(0, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(4, DRIVE_SPEED);
    intake.move_velocity(-200);
    chassis.wait_drive();
    intake.brake();

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(180, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-10, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_drive_pid(3, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(-45, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-35, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(-90, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(15, DRIVE_SPEED, true);
    chassis.wait_drive();

    setFlaps(false, true);
}


///
// Auton for when you are on the offensive side in qualifying
// 1. Move forward 48 inches
// 2. Turn right 90 degrees
// 3. Move forward 4 inches and run intake in reverse
// 4. Move back 5 inches
// 5. Turn right 150 degrees
// 6. Move forward 35 inches and suck balls in with intake
// 7. Move back 5 inches and turn 180 degrees around
// 8. Move 5 inches forward and suck intake outwards
// 9. Turn to the 45 degrees left from the starting position
// 10. Move forward 12 inches and suck balls in with intake
// 11. Turn to 90 degrees left of the original position
// 12. Open flaps and move back 30 inches
// 13. Move forward 3 inches and turn around 180 degrees
// 14. Outtake ball and push forward 3 inches then back 3 inches
// 15. Turn right 45 degrees of the starting position and move back 50 inches
// 16. Turn right 90 degrees of the starting position
// 17. Turn on right flap and move back 5 inches
///
void offensiveQual() {
    chassis.set_drive_pid(48, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(4, DRIVE_SPEED);
    intake.move_velocity(-200);
    chassis.wait_drive();
    intake.brake();

    chassis.set_drive_pid(-5, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_turn_pid(250, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(35, DRIVE_SPEED, true);
    intake.move_velocity(200);
    chassis.wait_drive();
    intake.brake();

    chassis.set_turn_pid(80, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(5, DRIVE_SPEED);
    intake.move_velocity(-200);
    chassis.wait_drive();
    intake.brake();

    chassis.set_turn_pid(-45, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(12, DRIVE_SPEED);
    intake.move_velocity(200);
    chassis.wait_drive();
    intake.brake();

    chassis.set_turn_pid(-90, TURN_SPEED);
    chassis.wait_drive();

    setFlaps(true, true);

    chassis.set_drive_pid(-30, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(3, DRIVE_SPEED);
    chassis.wait_drive();

    setFlaps(false, false);

    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(3, DRIVE_SPEED);
    intake.move_velocity(-200);
    chassis.wait_drive();
    intake.brake();

    chassis.set_drive_pid(-3, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(45, TURN_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-50, DRIVE_SPEED, true);
    chassis.wait_drive();

    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();

    setFlaps(false, false);

    chassis.set_drive_pid(-10, DRIVE_SPEED);
    chassis.wait_drive();
}
