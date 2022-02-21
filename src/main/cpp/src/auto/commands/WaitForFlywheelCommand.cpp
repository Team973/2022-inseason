#include "src/auto/commands/WaitForFlywheelCommand.h"

namespace frc973 {

WaitForFlywheelCommand::WaitForFlywheelCommand(Shooter *shooter, u_int32_t targetTime)
        : m_shooter(shooter), m_targetTime(targetTime) {
}

void WaitForFlywheelCommand::Init() {
}

void WaitForFlywheelCommand::Run() {
}

bool WaitForFlywheelCommand::IsCompleted() {
    return m_shooter->IsAtSpeed();
}

void WaitForFlywheelCommand::PostExecute() {
}

}  // namespace frc973