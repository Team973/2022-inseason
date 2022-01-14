#pragma once

#include "lib/Constants.h"

namespace frc973 {
    
/**
 * Constants
 */
//Physical Dimensions - TODO: update
constexpr double DRIVE_WIDTH = 0;           //Drive base width in inches.
constexpr double DRIVE_PINION = 0;          //Teeth on drive pinion gear.
constexpr double DRIVE_GEAR = 0;            //Teeth on the main drive gear.
constexpr double DRIVE_WHEEL_DIAMETER = 0;  //Diameter of the drive train wheels in inches.
constexpr double MAX_FT_PER_SECOND = 0;     //Max speed of the robot in feet per second.

//Movement
// constexpr double DRIVE_GEAR_RATIO = DRIVE_PINION / DRIVE_GEAR; /**< The gear ratio of the drive train. */
// constexpr double DRIVE_CIRCUMFERENCE =
//     Constants::PI * DRIVE_WHEEL_DIAMETER; /**< Circumference of the drive wheels in inches. */
// constexpr double WHEEL_ROTATION_PER_ENCODER_TICK =
//     DRIVE_GEAR_RATIO / Constants::TALON_FX_TICKS_PER_REV; /**< Wheel rotations per encoder tick. */
// constexpr double DRIVE_INCHES_PER_TICK =
//     WHEEL_ROTATION_PER_ENCODER_TICK * DRIVE_CIRCUMFERENCE; /**< Inches per encoder tick. */
// constexpr double DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK =
//     (DRIVE_INCHES_PER_TICK / Constants::TALON_FX_VELOCITY_UNIT_MS) *
//     Constants::MSEC_PER_SEC; /**< Inches per second per encoder tick. */

// constexpr double MAX_INCHES_PER_SECOND = MAX_FT_PER_SECOND * 12; /**< Max speed of the robot in feet per second. */
// constexpr double MAX_TICKS_PER_100_MS =
//     MAX_INCHES_PER_SECOND /
//     DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK; /**< Max robot speed in encoder ticks per 100 milliseconds. */
// constexpr double DRIVE_TELEOP_LIMIT = 1.0;  /**< The max speed we want to run constantly in teleop. */

/**
 * Drive Subsystem.
 */
constexpr int LEFT_DRIVE_TALON_A = 0;   /**< Can ID for the first left drive talon. */
constexpr int LEFT_DRIVE_TALON_B = 0;   /**< Can ID for the second left drive talon. */
constexpr int LEFT_DRIVE_TALON_C = 0;   /**< Can ID for the third left drive talon. */
constexpr int RIGHT_DRIVE_TALON_A = 0;  /**< Can ID for the first right drive talon. */
constexpr int RIGHT_DRIVE_TALON_B = 0;  /**< Can ID for the second right drive talon. */
constexpr int RIGHT_DRIVE_TALON_C = 0;  /**< Can ID for the third right drive talon. */

/**
 * Shooter Subsystem.
 */
constexpr int FLYWHEEL_A_CAN_ID = 0;  /**< Left flywheel TalonFX CAN ID. */
constexpr int FLYWHEEL_B_CAN_ID = 0; /**< Right flywheel TalonFX CAN ID. */
constexpr int PRECHARGER_CAN_ID = 0;  /**< Precharger TalonFX CAN ID. */
constexpr double FLYWHEEL_MOTOR_PULLEY = 1.0; /**< To do: This number is a placeholder please change it later */
constexpr double FLYWHEEL_DIRECT_PULLEY = 1.0; /**< To do: This number is a placeholder please change it later */
static constexpr double FLYWHEEL_RPM_SETPOINT = 3400.0; /**< To do: This number is a placeholder please change it later */   
static constexpr double PRECHARGER_RPM_SETPOINT = 3400.0; /**< To do: This number is a placeholder please change it later */
constexpr double PRECHARGER_VELOCITY_RPM = Constants::TALON_FX_VELOCITY_RPM;
constexpr double FLYWHEEL_GEAR_RATIO = FLYWHEEL_MOTOR_PULLEY / FLYWHEEL_DIRECT_PULLEY;
constexpr double FLYWHEEL_VELOCITY_RPM = Constants::TALON_FX_VELOCITY_RPM * FLYWHEEL_GEAR_RATIO;


} // namespace frc973
