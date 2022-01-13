#include "src/subsystems/Intake.h" 

namespace frc973 {
    
Intake::Intake(TalonFX *intakeTalon)
    : m_intakeSpeed(0.0)
    , m_intakeState(IntakeState::Retract) 
    , m_intakeTalon(intakeTalon) {
}

void Intake::Deploy() {
    m_intakeState = IntakeState::Deploy;
}

void Intake::Retract(){
    m_intakeState = IntakeState::Retract;
}

Intake::IntakeState Intake::GetIntakeState() {
    return m_intakeState;
}

void Intake::SetIntakeState(IntakeState state) {
    m_intakeState = state;
}

void Intake::SetPercentOutput(double speed) {
    m_intakeSpeed = speed;
}


void Intake::Update() {
    switch (m_intakeState) {
        case IntakeState::Deploy:
            //Deploys intake
            break;
        case IntakeState::Retract:
            //brings back intake
            break;
    }

    m_intakeSpeed = std::clamp(m_intakeSpeed, -1.0, 1.0);

  //  m_intakeTalon->(m_intakeSpeed);
}

void Intake::DashboardUpdate() {
    
}

} // namespace frc973

