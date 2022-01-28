#include "src/auto/commands/WaitForFlywheelCommand.h"

namespace frc973 {

WaitForFlywheelCommand::WaitForFlywheelCommand(Shooter *shooter) : m_shooter(shooter) {
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