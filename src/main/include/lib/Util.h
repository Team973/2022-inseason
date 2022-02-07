#pragma once

#include <frc/RobotController.h>
#include <math.h>

#include "Constants.h"

using namespace frc;

namespace frc973 {

namespace Util {

/**
 * Gets 0 if |x| is within +/- |threshold|, otherwise return |x|. Useful for
 * joysticks that aren't quite centered at zero.
 * @param x
 * @param threshold
 * @return 0 if |x| is within +/- |threshold|, otherwise return |x|.
 */
inline double deadband(double x, double threshold = 0.05) {
    if (std::fabs(x) > threshold) {
        return x;
    }
    else {
        return 0.0;
    }
}
    
/**
 * Get the current time in microseconds.
 * @return The current time.
 */
inline uint64_t GetUsecTime() {
    return RobotController::GetFPGATime();
}

/**
 * Get the current time in milliseconds.
 * @return The current time.
 */
inline uint32_t GetMsecTime() {
    return GetUsecTime() * Constants::MSEC_PER_USEC;
}

} // namespace Util
} // namespace frc973