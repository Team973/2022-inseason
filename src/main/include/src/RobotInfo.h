#pragma once

#include "lib/util/Constants.h"

namespace frc973 {
    
/**
 * Constants
 */
//Physical Dimensions - TODO: update
constexpr double DRIVE_WIDTH = 23.75;           //Drive base width in inches.
constexpr double DRIVE_WHEEL_DIAMETER = 4;  //Diameter of the drive train wheels in inches.
constexpr double MAX_FT_PER_SECOND = 1;     //Max speed of the robot in feet per second.
constexpr double DRIVE_GEAR_RATIO = (12 / 72) * (34 / 36); /**< The gear ratio of the drive train. */

//Movement
constexpr double DRIVE_CIRCUMFERENCE =
    Constants::PI * DRIVE_WHEEL_DIAMETER; /**< Circumference of the drive wheels in inches. */
constexpr double WHEEL_ROTATION_PER_ENCODER_TICK =
    DRIVE_GEAR_RATIO / Constants::TALON_FX_TICKS_PER_REV; /**< Wheel rotations per encoder tick. */
constexpr double DRIVE_INCHES_PER_TICK =
    WHEEL_ROTATION_PER_ENCODER_TICK * DRIVE_CIRCUMFERENCE; /**< Inches per encoder tick. */
constexpr double DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK =
    (DRIVE_INCHES_PER_TICK / Constants::TALON_FX_VELOCITY_UNIT_MS) *
    Constants::MSEC_PER_SEC; /**< Inches per second per encoder tick. */

constexpr double MAX_INCHES_PER_SECOND = MAX_FT_PER_SECOND * 12; /**< Max speed of the robot in feet per second. */
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
constexpr int RIGHT_DRIVE_TALON_A = 15;  /**< Can ID for the first right drive talon. */
constexpr int RIGHT_DRIVE_TALON_B = 14;  /**< Can ID for the second right drive talon. */
constexpr int RIGHT_DRIVE_TALON_C = 13;  /**< Can ID for the third right drive talon. */

} // namespace frc973
