#pragma once

#include <frc/RobotController.h>
#include <math.h>

#include "Constants.h"

using namespace frc;

namespace frc973 {

namespace Util {
    
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