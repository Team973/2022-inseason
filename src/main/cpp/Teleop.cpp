#include "src/Robot.h"
#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {
    m_lights->SetLightsState(Lights::LightsState::Climb);
}

void Robot::TeleopPeriodic() {
}

} // namespace frc973