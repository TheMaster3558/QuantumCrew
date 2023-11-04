#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


pros::ADIDigitalIn bumperSwitch('A');

pros::Motor catapultLeft(6, pros::E_MOTOR_GEAR_RED);
pros::Motor catapultRight(7, pros::E_MOTOR_GEAR_RED, true);
pros::MotorGroup catapult({catapultLeft, catapultRight});

pros::Motor intake(1, pros::E_MOTOR_GEAR_GREEN);


int catapult_top = 0;


void moveAndWait(pros::Motor motor, int position, int velocity) {
    motor.move_absolute(position, velocity);
    while (!((motor.get_position() < position + 10) && (motor.get_position() > position - 10))) {
        pros::delay(2);
    }
    catapult_top = motor.get_position();
}


void waitForPress() {
    while (!bumperSwitch.get_value()) {
        pros::delay(5);
    }
}


void updateCatapult() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        pros::Task task{[=] {
            waitForPress();
            catapult.brake();
        }};
        catapult.move_velocity(-600);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
        pros::Task task{[=] {
            waitForPress();
            catapult.move_relative(500, 600);
        }};
        catapult.move_velocity(600);
    }
}


void updateIntake() {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intake.move_velocity(200);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intake.move_velocity(-200);
    }
    else {
        intake.brake();
    }
}


void updateDisplay() {
    static int count = 0;
    if (++count % (50 / ez::util::DELAY_TIME) != 0) {
        return;
    }

    ez::print_to_screen(to_string(bumperSwitch.get_value()));
}


// Chassis constructor
Drive chassis(
        // Left Chassis Ports (negative port will reverse it!)
        //   the first port is the sensored port (when trackers are not used!)
        {-4, -5}

        // Right Chassis Ports (negative port will reverse it!)
        //   the first port is the sensored port (when trackers are not used!)
        , {2, 3}

        // IMU Port
        , 21

        // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
        //    (or tracking wheel diameter)
        , 4.125

        // Cartridge RPM
        //   (or tick per rotation if using tracking wheels)
        , 257

        // External Gear Ratio (MUST BE DECIMAL)
        //    (or gear ratio of tracking wheel)
        // eg. if you.r drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
        // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
        , 2.333

        // Uncomment if using tracking wheels
        /*
        // Left Tracking Wheel Ports (negative port will reverse it!)
        // ,{1, 2} // 3 wire encoder
        // ,8 // Rotation sensor

        // Right Tracking Wheel Ports (negative port will reverse it!)
        // ,{-3, -4} // 3 wire encoder
        // ,-9 // Rotation sensor
        */

        // Uncomment if tracking wheels are plugged into a 3 wire expander
        // 3 Wire Port Expander Smart Port
        // ,1
);


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::delay(500); // Stop the user from doing anything while legacy ports configure.

    // Configure your chassis controls
    chassis.toggle_modify_curve_with_controller(
            false);
    chassis.set_active_brake(0.1);
    chassis.set_curve_default(3,
                              5);
    default_constants();
    exit_condition_defaults();

    catapult.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);

    // Autonomous Selector using LLEMU
    ez::as::auton_selector.add_autons(
            {
                Auton("test auton", test_drive)
            }
    );

    // Initialize chassis and auton selector
    chassis.initialize();
    ez::as::initialize();
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    // . . .
}


/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    // . . .
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    chassis.reset_pid_targets(); // Resets PID targets to 0
    chassis.reset_gyro(); // Reset gyro position to 0
    chassis.reset_drive_sensor(); // Reset drive sensors to 0
    chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

    ez::as::auton_selector.print_selected_auton();
    ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    // This is preference to what you like to drive on.
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);

    while (true) {

        // chassis.tank(); // Tank control
        chassis.arcade_standard(ez::SPLIT); // Standard split arcade
        // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
        // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
        // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

        updateCatapult();
        updateIntake();
        updateDisplay();

        pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
    }
}
