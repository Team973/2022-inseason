#include "src/Robot.h"

#include <iostream>

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
}

void Robot::DisabledPeriodic() {}

} // namespace frc973