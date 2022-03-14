#include "src/subsystems/Intake.h"

namespace frc973 {

Intake::Intake(frc::PWMTalonFX *intakeTalon, frc::Solenoid *intakeSolenoid, frc::Solenoid *intakeSoftSolenoid)
        : m_intakeSpeed(0.0)
        , m_intakeTalon(intakeTalon)
        , m_intakeSolenoid(intakeSolenoid)
        , m_intakeSoftSolenoid(intakeSoftSolenoid)
        , m_intakeState(IntakeState::Retract)
        , m_intakeMotorState(IntakeMotorState::Off)
        , m_timer(0.0)
        , m_intakeStatus("off") {
}

void Intake::Deploy() {
    m_intakeState = IntakeState::Deploy;
}

void Intake::Retract() {
    m_intakeState = IntakeState::Retract;
}

Intake::IntakeState Intake::GetIntakeState() {
    return m_intakeState;
}

void Intake::SetIntakeState(IntakeState state) {
    m_intakeState = state;
}

void Intake::SetIntakeMotorState(IntakeMotorState state) {
    m_intakeMotorState = state;
}

void Intake::SetPercentOutput(double speed) {
    m_intakeSpeed = speed;
}

void Intake::Update() {
    switch (m_intakeState) {
        case IntakeState::Deploy:
            // if ((Util::GetMsecTime() - m_timer) > INTAKE_SOLENOID_DELAY) {
            //     m_intakeSoftSolenoid->Set(true);
            //     m_intakeSolenoid->Set(false);
            // } else {
                m_intakeSoftSolenoid->Set(false);
                m_intakeSolenoid->Set(true);
            // }
            break;
        case IntakeState::Retract:
            m_timer = Util::GetMsecTime();
            m_intakeSolenoid->Set(false);
            m_intakeSoftSolenoid->Set(false);
            break;
    }

    switch (m_intakeMotorState) {
        case IntakeMotorState::Off:
            m_intakeStatus = "Off";
            m_intakeSpeed = 0.0;
            break;
        case IntakeMotorState::FeedIn:
            m_intakeStatus = "FeedIn";
            m_intakeSpeed = 0.8;
            break;
        case IntakeMotorState::FeedOut:
            m_intakeStatus = "FeedOut";
            m_intakeSpeed = -0.2;
            break;
        case IntakeMotorState::Manual:
            m_intakeStatus = "Manual";
            break;
    }

    m_intakeSpeed = std::clamp(m_intakeSpeed, -0.8, 0.8);

    m_intakeTalon->Set(m_intakeSpeed);
}

void Intake::DashboardUpdate() {
    frc::SmartDashboard::PutString("I status", m_intakeStatus);
}

}  // namespace frc973
