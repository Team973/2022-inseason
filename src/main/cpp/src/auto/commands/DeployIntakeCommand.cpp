#include "src/auto/commands/DeployIntakeCommand.h"

namespace frc973 {

DeployIntakeCommand::DeployIntakeCommand(Intake *intake) : m_intake(intake) {
}

void DeployIntakeCommand::Init() {
}

void DeployIntakeCommand::Run() {
    m_intake->Deploy();
}

bool DeployIntakeCommand::IsCompleted() {
    return true;
}

void DeployIntakeCommand::PostExecute() {
}
}