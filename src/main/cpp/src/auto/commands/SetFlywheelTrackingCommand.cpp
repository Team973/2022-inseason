#include "src/auto/commands/SetFlywheelTrackingCommand.h"

namespace frc973 {

SetFlywheelTrackingCommand::SetFlywheelTrackingCommand(Shooter *shooter, u_int32_t targetTime) 
    : m_shooter(shooter), m_targetTime(targetTime) {
}

void SetFlywheelTrackingCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_shooter->SetShooterState(Shooter::ShooterState::Tracking);
}

void SetFlywheelTrackingCommand::Run() {
}

bool SetFlywheelTrackingCommand::IsCompleted() {
    return HasElapsed();
}

void SetFlywheelTrackingCommand::PostExecute() {
}
}  // namespace frc973