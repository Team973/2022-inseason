#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
    m_lights->ClearOffFlag();
}

void Robot::DisabledPeriodic() {
    // if (m_lights->GetLightsState() == Lights::LightsState::Off) {
    //     m_lights->SetLightsState(Lights::LightsState::Climb);
    // } else if (m_lights->GetOffFlag()){
    //     m_lights->SetLightsState(Lights::LightsState::Off);
    // } 
    if (m_lights->GetOffFlag()){
    m_lights->SetLightsState(Lights::LightsState::Middle);
    } else {
        m_lights->SetLightsState(Lights::LightsState::Off);
    }
}
}  // namespace frc973