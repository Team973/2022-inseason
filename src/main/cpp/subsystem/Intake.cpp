#include "src/subsystems/Intake.h" 

namespace frc973 {
    
Intake::Intake(TalonFX *intakeTalon, frc::Solenoid *intakeSolenoid) 
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
            m_intakeSolenoid->Set(true);
            break;
        case IntakeState::Retract:
            m_intakeSolenoid->Set(false);
            break;
        
    }

     switch (m_intakeMotorState) {
        case IntakeMotorState::Off:
            m_intakeSpeed = 0.0;
            break;
        case IntakeMotorState::FeedIn:
            m_intakeSpeed = 0.8;
            break;  
        case IntakeMotorState::FeedOut:
            m_intakeSpeed = -0.2;
            break;
        case IntakeMotorState::Manual:
            //Controlled by Co-Driver, set in Teleop
            break;
    }


    m_intakeSpeed = std::clamp(m_intakeSpeed, -1.0, 1.0);

    m_intakeTalon->Set(ControlMode::PercentOutput, m_intakeSpeed);
}

void Intake::DashboardUpdate() {
    
}

} // namespace frc973

