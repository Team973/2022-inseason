#include "src/auto/commands/SetFlywheelRPMCommand.h"

namespace frc973 {

SetFlywheelRPMCommand::SetFlywheelRPMCommand(Shooter *shooter, double setpoint, u_int32_t targetTime) : m_shooter(shooter), m_targetTime(targetTime) {
}

void SetFlywheelRPMCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_shooter->SetFlywheelRPM(m_setpoint);
    m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
}

void SetFlywheelRPMCommand::Run() {
}

bool SetFlywheelRPMCommand::IsCompleted() {
    return HasElapsed();
}

void SetFlywheelRPMCommand::PostExecute() {
}
}  // namespace frc973