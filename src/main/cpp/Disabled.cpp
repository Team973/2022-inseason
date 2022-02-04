#include "src/Robot.h"

#include <iostream>

namespace frc973 {

void Robot::DisabledInit() {
    m_lights->SetLightsState(Lights::LightsState::Left);
}

void Robot::DisabledPeriodic() {}

} // namespace frc973