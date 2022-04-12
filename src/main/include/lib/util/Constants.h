#pragma once

#include <cstdint>

namespace frc973 {

namespace Constants {

constexpr uint32_t PID_SPEED_CTRL = 0x00000001; /**< Integrate the output of helpers/PID */

constexpr double PI = 3.141592653589793;                 /**< Pi.*/
constexpr double FEET_PER_METER = 3.280839895;           /**< ft/m.*/
constexpr double METERS_PER_FOOT = 1.0 / FEET_PER_METER; /**< m/ft.*/
constexpr double GRAVITY_CONSTANT = 9.80665;             /**< Gravity constant meter/sq(sec).*/
constexpr double GRAVITY_CONSTANT_INCHES =
    GRAVITY_CONSTANT * FEET_PER_METER * 12.0;                 /**< Gravity constant in/sq(sec). */
constexpr double USEC_PER_MSEC = 1000.0;                      /**< Microseconds/millisecond.*/
constexpr double MSEC_PER_USEC = 1.0 / USEC_PER_MSEC;         /**< Milliseconds/microseconds.*/
constexpr double MSEC_PER_SEC = 1000.0;                       /**< Milliseconds/seconds.*/
constexpr double SEC_PER_MSEC = 1.0 / MSEC_PER_SEC;           /**< Seconds/milliseconds.*/
constexpr double USEC_PER_SEC = USEC_PER_MSEC * MSEC_PER_SEC; /**< Microseconds/second.*/
constexpr double SEC_PER_USEC = 1.0 / USEC_PER_SEC;           /**< Microseconds/milliseconds.*/
constexpr double MIN_PER_SEC = 1.0 / 60.0;                    /**< Minutes/seconds.*/
constexpr double SEC_PER_MIN = 60.0;                          /**< Seconds/minute.*/
constexpr double RAD_PER_DEG = 2 * PI / 360.0;                /**< Radians/degrees.*/
constexpr double DEG_PER_RAD = 1.0 / RAD_PER_DEG;             /**< Degrees/Radians.*/

constexpr double TALON_FX_TICKS_PER_REV = 2048.0;   /**< Encoder ticks/revolution of TalonFX motor. */
constexpr double TALON_FX_VELOCITY_UNIT_MS = 100.0; /**< Ticks/100ms. */

constexpr double TALON_FX_VELOCITY_RPM =
    (MSEC_PER_SEC * SEC_PER_MIN) /
    (TALON_FX_TICKS_PER_REV * TALON_FX_VELOCITY_UNIT_MS); /**< Standard TalonFX RPM (multiply by Ticks/100ms). */

// for limelight tracking
constexpr double GYRO_CONSTANT = 0.0021; //0.003
constexpr double TRANSLATION_CONSTANT = 0.0025;

// turret home angle
constexpr double TURRET_HOME_OFFSET = -1.0;
constexpr double TURRET_SOFT_OFFSET = 5.0;

}  // namespace Constants

}  // namespace frc973
