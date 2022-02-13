#include <iostream>

#include "src/Robot.h"

namespace frc973 {

void Robot::TeleopInit() {
    m_intake->SetIntakeMotorState(Intake::IntakeMotorState::Manual);
}

void Robot::TeleopPeriodic() {
    if(m_operatorStick->GetLeftTriggerAxis() >= 0.8) {
        m_intake->Deploy();
    } else {
        m_intake->Retract();
    }
    m_intake->SetPercentOutput(m_operatorStick->GetRawAxisWithDeadband(0, false, 0.12)); // left stick x-axis for co-driver
} 

}  // namespace frc973
