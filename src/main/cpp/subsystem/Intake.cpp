#include "src/subsystems/Intake.h" 

namespace frc973 {
    
Intake::Intake()
    :m_intakeState(IntakeState::Retract) {
}

void Intake::Deploy() {
    m_intakeState = IntakeState::Deploy;
}

void Intake::Retract(){
}

void Intake::Update() {
}

void Intake::DashboardUpdate() {
    
}

} // namespace frc973

