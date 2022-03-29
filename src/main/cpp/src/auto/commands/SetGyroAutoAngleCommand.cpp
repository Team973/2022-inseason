#include "src/auto/commands/SetGyroAutoAngleCommand.h"

namespace frc973 {

SetGyroAutoAngleCommand::SetGyroAutoAngleCommand(Gyro *gyro, double autoAngle)
        : m_gyro(gyro), m_autoAngle(autoAngle) {
}

void SetGyroAutoAngleCommand::Init() {
    m_gyro->SetAutoOffset(m_autoAngle);
}

void SetGyroAutoAngleCommand::Run() {}

bool SetGyroAutoAngleCommand::IsCompleted() {
    return true;
}

void SetGyroAutoAngleCommand::PostExecute() {
}
}