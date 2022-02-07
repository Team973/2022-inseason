#include "src/auto/commands/WaitCommand.h"

namespace frc973 {

WaitCommand::WaitCommand(uint32_t targetTime) : m_targetTime(targetTime) {
}

void WaitCommand::Init() {
    SetTargetMSec(m_targetTime);
}

void WaitCommand::Run() {
}

bool WaitCommand::IsCompleted() {
    return HasElapsed();
}
}