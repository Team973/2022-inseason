#pragma once
//#include <frc/PneumaticsModuleType.h>
#include "lib/util/Constants.h"
namespace frc973 {

/**
 * Drive Subsystem.
 */
constexpr int LEFT_DRIVE_FX_A_ID = 0;   /**< CAN ID for the first left drive falcon. */
constexpr int LEFT_DRIVE_FX_B_ID = 1;   /**< CAN ID for the second left drive falcon. */
constexpr int LEFT_DRIVE_FX_C_ID = 2;   /**< CAN ID for the third left drive falcon. */
constexpr int RIGHT_DRIVE_FX_A_ID = 15; /**< CAN ID for the first right drive falcon. */
constexpr int RIGHT_DRIVE_FX_B_ID = 14; /**< CAN ID for the second right drive falcon. */
constexpr int RIGHT_DRIVE_FX_C_ID = 13; /**< CAN ID for the third right drive falcon. */
// Physical Dimensions
constexpr double DRIVE_GEAR_RATIO = (11.0 / 72.0) * (34.0 / 36.0); /** The gear ratio of the drive train. */
constexpr double DRIVE_WIDTH = 23.75 * 0.0254;                     /** Drive base width in meters. */
constexpr double DRIVE_WHEEL_DIAMETER = 4.0;                       /** Diameter of the drive train wheels in inches. */
// Movement
constexpr double DRIVE_INCHES_PER_TICK = (Constants::PI * DRIVE_WHEEL_DIAMETER) * DRIVE_GEAR_RATIO /
                                         Constants::TALON_FX_TICKS_PER_REV; /** Inches per encoder tick. */
constexpr double DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK =
    (DRIVE_INCHES_PER_TICK / Constants::TALON_FX_VELOCITY_UNIT_MS) *
    Constants::MSEC_PER_SEC;                 /** Inches per second per encoder tick. */
constexpr double MAX_FT_PER_SECOND = 16.225; /** Max speed of the robot in feet per second. 20,158 ticks/100ms. */
constexpr double MAX_INCHES_PER_SECOND = MAX_FT_PER_SECOND * 12.0; /** Max speed of the robot in feet per second. */
constexpr double MAX_METERS_PER_SECOND =
    MAX_FT_PER_SECOND / Constants::FEET_PER_METER; /** Max speed of the robot in meters per second. */
constexpr double MAX_TICKS_PER_100_MS =
    MAX_INCHES_PER_SECOND /
    DRIVE_VELOCITY_INCHES_PER_SEC_PER_TICK;    /** Max robot speed in encoder ticks per 100 milliseconds. */
constexpr double MAX_DEGREES_PER_SECOND = 600; /** Max robot angular speed in degrees per second. */
constexpr double MAX_RADIANS_PER_SECOND =
    MAX_DEGREES_PER_SECOND * Constants::PI / 180; /** Max robot angular speed in radians per second. */
constexpr double DRIVE_TELEOP_LIMIT = 1.0;        /** The max speed we want to run constantly in teleop. */

/**
 * Intake Subsystem.
 */
constexpr int INTAKE_FX_PWM_ID = 0;    /**< PWM ID for the intake talon. */
constexpr int INTAKE_SOLENOID_ID = 15; /**< Channel for the intake Solenoid. */

/**
 * Conveyor Subsystem.
 */
constexpr int CONVEYOR_FLOOR_SRX_ID = 10;   /**< CAN ID for the floor talon. */
constexpr int CONVEYOR_TOWER_A_SRX_ID = 11; /**< CAN ID for the first tower talon. */
constexpr int CONVEYOR_TOWER_B_SRX_ID = 4;  /**< CAN ID for the second tower talon. */

/**
 * Turret Subsystem.
 */
constexpr int TURRET_FX_ID = 8;            /**< CAN ID for the turret falcon. */
constexpr int TURRET_HOME_SENSOR = 0;      /** DIO channel for homing hall sensor. */
constexpr double TURRET_GEAR_RATIO = ((7.0 / 1.0) * (128.0 / 10.0)); /** The gear ratio of the turret. */
constexpr double TURRET_TICKS_PER_DEGREE = 1.0 / 360.0 * 2048.0 * TURRET_GEAR_RATIO; /** Ticks per degree of the turret */

/**
 * Shooter Subsystem.
 */
constexpr int FLYWHEEL_FX_A_ID = 6;                   /**< CAN ID for the left flywheel falcon. */
constexpr int FLYWHEEL_FX_B_ID = 9;                   /**< CAN ID for the right flywheel falcon. */
constexpr double FLYWHEEL_GEAR_RATIO = (12.0 / 18.0); /** The gear ratio of the turret. */
constexpr double FLYWHEEL_VELOCITY_RPM =
    Constants::TALON_FX_VELOCITY_RPM * FLYWHEEL_GEAR_RATIO;    /** Convert RPM to ticks per 100msec. */
static constexpr double TARMAC_FLYWHEEL_RPM_SETPOINT = 2600.0; /** Flywheel RPM to shoot from the edge of the tarmac. */

/**
 * Climb Subsystem.
 */
constexpr int CLIMB_FX_A_ID = 3;  /**< CAN ID for a climb Falcon.*/
constexpr int CLIMB_FX_B_ID = 12; /**< CAN ID for a climb Falcon.*/

constexpr int CLIMB_BOTTOM_LEFT_SENSOR = 4;  /** DIO channel for the bottom left climb hall sensor. */
constexpr int CLIMB_BOTTOM_RIGHT_SENSOR = 1; /** DIO channel for the bottom right climb hall sensor. */
constexpr int CLIMB_TOP_LEFT_SENSOR = 3;     /** DIO channel for the top left climb hall sensor. */
constexpr int CLIMB_TOP_RIGHT_SENSOR = 2;    /** DIO channel for the top right climb hall sensor. */

constexpr double CLIMB_PINION = 8.0;          /** Tooth count of the pinion gear on climb. */
constexpr double CLIMB_GEAR = 70.0;           /** Tooth count of the spur gear on climb. */
constexpr double CLIMB_SPOOL_DIAMETER = 0.75; /** Working diameter of the spool on climb. */
constexpr double CLIMB_SPOOL_CIRCUMFERENCE =
    CLIMB_SPOOL_DIAMETER * Constants::PI; /** Circumference of the spool on climb. */
constexpr double CLIMB_INCHES_PER_TICK =
    ((CLIMB_PINION / CLIMB_GEAR) * CLIMB_SPOOL_CIRCUMFERENCE) / 2048; /** Inches per encoder tick. */

/**
 * Gyro
 */
constexpr int GYRO_SRX_ID = 4;      /**< CAN ID for the SRX that the gyro is plugged in to. */
constexpr double P1_ANGLE = -156.0;      /**< The angle to set when robot is in position 1. */
constexpr double P2_ANGLE = -178.5; /**< The angle to set when robot is in position 2. */
constexpr double P3_ANGLE = 114.0;    /**< The angle to set when robot is in position 3. */
constexpr double P4_ANGLE = 114.0;      /**< The angle to set when robot is in position 4. */
constexpr double P5_ANGLE = 46.5;   /**< The angle to set when robot is in position 5. */
constexpr double P6_ANGLE = 24.0;      /**< The angle to set when robot is in position 6. */

/**
 * Lights
 */
constexpr int CANDLE_ID = 1; /**< CAN ID for the Candle light. */

/**
 * Pneumatics
 */
constexpr int PNEU_HUB_CAN_ID = 1; /**< CAN ID for the pneumatics hub. */

/**
 * Controller Sticks
 */
constexpr int DRIVER_STICK = 0;   /** Driver stick usb slot. */
constexpr int OPERATOR_STICK = 1; /** Operator stick usb slot. */
constexpr int TEST_STICK = 2;     /** Test stick usb slot. */

/**
 * Tolerances In in/sec - TODO: update, currently 2020 values
 */
static constexpr double DIST_TOLERANCE = 10.0;
static constexpr double DIST_RATE_TOLERANCE = 20.0;
static constexpr double ANGLE_TOLERANCE = 8.0;
static constexpr double ANGLE_RATE_TOLERANCE = 20.0;

}  // namespace frc973
