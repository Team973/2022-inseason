#include "src/Robot.h"

#include <iostream>

namespace frc973 {
    
void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    m_turret->Turn(m_operatorStick->GetRawAxis(4));
}

} // namespace frc973