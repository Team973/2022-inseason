#pragma once
#include <frc/PneumaticsModuleType.h>
#include "lib/util/Constants.h"
namespace frc973 {
/**
 * Constants
 */
// Physical Dimensions - TODO: update
constexpr double DRIVE_WIDTH = 23.75;         // Drive base width in inches.
constexpr double DRIVE_PINION = 1;            // Teeth on drive pinion gear.
constexpr double DRIVE_GEAR = 1;              // Teeth on the main drive gear.
constexpr double DRIVE_WHEEL_DIAMETER = 4.0;  // Diameter of the drive train wheels in inches.
constexpr double MAX_FT_PER_SECOND = 14.2;    // Max speed of the robot in feet per second.

// Movement
constexpr double DRIVE_GEAR_RATIO = (12.0 / 72.0) * (34.0 / 36.0); /**< The gear ratio of the drive train. */
constexpr double DRIVE_CIRCUMFERENCE =
    Constants::PI * DRIVE_WHEEL_DIAMETER; /**< Circumference of the drive wheels in inches. */
constexpr double WHEEL_ROTATION_PER_ENCODER_TICK =
    DRIVE_GEAR_RATIO / Constants::TALON_FX_TICKS_PER_REV; /**< Wheel rotations per encoder tick. */
constexpr double DRIVE_INCHES_PER_TICK =
    WHEEL_ROTATION_PER_ENCODER_TICK * DRIVE_CIRCUMFERENCE; /**< Inches per encoder tick. */
constexpr double DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK =
    (DRIVE_INCHES_PER_TICK / Constants::TALON_FX_VELOCITY_UNIT_MS) *
    Constants::MSEC_PER_SEC;                                       /**< Inches per second per encoder tick. */
constexpr double MAX_INCHES_PER_SECOND = MAX_FT_PER_SECOND * 12.0; /**< Max speed of the robot in feet per second. */
constexpr double MAX_TICKS_PER_100_MS =
    MAX_INCHES_PER_SECOND /
    DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK; /**< Max robot speed in encoder ticks per 100 milliseconds. */
constexpr double DRIVE_TELEOP_LIMIT = 1.0;  /**< The max speed we want to run constantly in teleop. */

/**
 * Drive Subsystem.
 */
constexpr int LEFT_DRIVE_TALON_A = 0;   /**< Can ID for the first left drive talon. */
constexpr int LEFT_DRIVE_TALON_B = 1;   /**< Can ID for the second left drive talon. */
constexpr int LEFT_DRIVE_TALON_C = 2;   /**< Can ID for the third left drive talon. */
constexpr int RIGHT_DRIVE_TALON_A = 15; /**< Can ID for the first right drive talon. */
constexpr int RIGHT_DRIVE_TALON_B = 14; /**< Can ID for the second right drive talon. */
constexpr int RIGHT_DRIVE_TALON_C = 13; /**< Can ID for the third right drive talon. */

/**
 * Conveyor Subsystem.
 */
constexpr int CONVEYOR_TOWER_A_TALON_SRX = 21; /**< Can ID for the first tower talon. */
constexpr int CONVEYOR_TOWER_B_TALON_SRX = 22; /**< Can ID for the second tower talon. */
constexpr int CONVEYOR_FLOOR_TALON_SRX = 23;   /**< Can ID for the floor talon. */

/**
 * Turret Subsystem.
 */
constexpr int TURRET_TALON = 8;

/**
 * Shooter Subsystem.
 */
constexpr int FLYWHEEL_A_CAN_ID = 24;           /**< Left flywheel TalonFX CAN ID. */
constexpr int FLYWHEEL_B_CAN_ID = 25;           /**< Right flywheel TalonFX CAN ID. */
constexpr double FLYWHEEL_MOTOR_PULLEY = 12.0;  /**< To do: This number is a placeholder please change it later */
constexpr double FLYWHEEL_DIRECT_PULLEY = 18.0; /**< To do: This number is a placeholder please change it later */
constexpr double FLYWHEEL_GEAR_RATIO = FLYWHEEL_MOTOR_PULLEY / FLYWHEEL_DIRECT_PULLEY;
constexpr double FLYWHEEL_VELOCITY_RPM = Constants::TALON_FX_VELOCITY_RPM * FLYWHEEL_GEAR_RATIO;
static constexpr double FLYWHEEL_RPM_SETPOINT =
    3400.0; /**< To do: This number is a placeholder please change it later */

/**
 * Climb Subsystem.
 */
constexpr int CLIMB_FALCON_A_ID = 26;        /**< Can ID for a climb Falcon motor controller.*/
constexpr int CLIMB_FALCON_B_ID = 27;        /**< Can ID for a climb Falcon motor controller.*/
constexpr int CLIMB_SOLENOID_ID = 28;        /**< Can ID for the climb locking solenoids. */
constexpr int CLIMB_BOTTOM_LEFT_SENSOR = 3;  /**< Can ID for the bottom left climb sensor */
constexpr int CLIMB_BOTTOM_RIGHT_SENSOR = 4; /**< Can ID for the bottom right climb sensor */
constexpr int CLIMB_TOP_LEFT_SENSOR = 6;     /**< Can ID for the top left climb sensor */
constexpr int CLIMB_TOP_RIGHT_SENSOR = 7;    /**< Can ID for the top right climb sensor */
constexpr double CLIMB_PINION = 1.0;
constexpr double CLIMB_GEAR = 1.0;
constexpr double CLIMB_SPOOL_DIAMETER = 1.0;
constexpr double CLIMB_SPOOL_CIRCUMFERENCE = CLIMB_SPOOL_DIAMETER * Constants::PI;
constexpr double CLIMB_INCHES_PER_TICK = ((CLIMB_PINION / CLIMB_GEAR) * CLIMB_SPOOL_CIRCUMFERENCE) / 2048;

/**
 * PCM
 */
constexpr int PCM_ID = 20;

/**
 * Gyro
 */
constexpr int GYRO_TALON = 9;

/**
 * Lights
 */
constexpr int CANDLE_ID = 5;

/**
 * Intake Subsystem
 */
constexpr int INTAKE_FALCON = 29;     /**< Can ID for the intake talon. */
constexpr int INTAKE_SOLENOID_ID = 9; /**< Can ID for the intake Solenoid. */

/**
 * Controller Sticks
 */
constexpr int DRIVER_STICK = 0;
constexpr int OPERATOR_STICK = 1;

}  // namespace frc973
