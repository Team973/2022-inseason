#pragma once

#include <frc/geometry/Translation2d.h>

namespace frc973 {

namespace FieldLocations {
/**
 * Field locations
 */
const frc::Translation2d CLOSE_STATION{units::inch_t(0.0), units::inch_t(-300.0)};
const frc::Translation2d FAR_STATION{units::inch_t(0.0), units::inch_t(300.0)};
const frc::Translation2d CLOSE_HANGAR{units::inch_t(-105.0), units::inch_t(-260.0)};
const frc::Translation2d FAR_HANGAR{units::inch_t(105.0), units::inch_t(260.0)};
const frc::Translation2d HUB{units::inch_t(0.0), units::inch_t(0.0)};

}  // namespace FieldLocations

}  // namespace frc973
