#include "src/auto/commands/ShooterCommand.h"

namespace frc973 {

ShooterCommand::ShooterCommand(Shooter *shooter, u_int32_t targetTime) : m_shooter(shooter), m_targetTime(targetTime) {
}

void ShooterCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_shooter->EnableShooter();
}

void ShooterCommand::Run() {
}

bool ShooterCommand::IsCompleted() {
    return HasElapsed();
}

void ShooterCommand::PostExecute() {
    m_shooter->DisableShooter();
}
}  // namespace frc973