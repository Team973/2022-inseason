#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
    m_lights->SetLightsState(Lights::LightsState::Off);
}

void Robot::DisabledPeriodic() {
    bool foundHome = false;

    if(foundHome == false) {
        if(!m_turretSensor->Get()) {
            foundHome = true;
            m_turret->SetHomeOffset();
            m_lights->SetLightsState(Lights::LightsState::Middle);
            m_turret->SetNeutralMode(NeutralMode::Brake);
        }
    }

    
    
}
}  // namespace frc973