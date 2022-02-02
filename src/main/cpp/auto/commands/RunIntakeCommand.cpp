#include "src/auto/commands/RunIntakeCommand.h"

namespace frc973 {

RunIntakeCommand::RunIntakeCommand(Intake *intake, double speed, uint32_t targetTime)
        : m_intake(intake), m_speed(speed), m_targetTime(targetTime) {
}

void RunIntakeCommand::Init() {
    SetTargetMSec(m_targetTime);
}

void RunIntakeCommand::Run() {
    m_intake->SetPercentOutput(m_speed);
}

bool RunIntakeCommand::IsCompleted() {
    return HasElapsed();
}

void RunIntakeCommand::PostExecute() {
    m_intake->SetPercentOutput(0.0);
}
}