#include "src/auto/commands/RetractIntakeCommand.h"

namespace frc973 {

RetractIntakeCommand::RetractIntakeCommand(Intake *intake) : m_intake(intake) {
}

void RetractIntakeCommand::Init() {
    m_intake->SetIntakeState(Intake::IntakeState::Retract);
}

void RetractIntakeCommand::Run() {
}

bool RetractIntakeCommand::IsCompleted() {
    return true;
}

void RetractIntakeCommand::PostExecute() {
}
}