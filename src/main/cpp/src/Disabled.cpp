#include "src/Robot.h"

#include <iostream>

namespace frc973 {

void Robot::DisabledInit() {
    m_turret->SetNeutralMode(NeutralMode::Coast);
}

void Robot::DisabledPeriodic() {
    double funnynumber = 180.0 - ((acos(((pow(35, 2) + pow(2, 2) - pow(35, 2)) / (2.0 * 35 * 2)))) * 180.0 / Constants::PI);
    SmartDashboard::PutNumber("funnynumber", funnynumber);
}

} // namespace frc973