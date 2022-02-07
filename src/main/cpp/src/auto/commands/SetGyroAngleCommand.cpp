#include "src/auto/commands/SetGyroAngleCommand.h"

namespace frc973 {

SetGyroAngleCommand::SetGyroAngleCommand(Gyro *gyro, double setAngle, u_int32_t targetTime)
        : m_gyro(gyro), m_setAngle(setAngle), m_targetTime(targetTime) {
}

void SetGyroAngleCommand::Init() {
    m_gyro->SetAngle(m_setAngle);
}

void SetGyroAngleCommand::Run() {
}

bool SetGyroAngleCommand::IsCompleted() {
    return HasElapsed();
}

void SetGyroAngleCommand::PostExecute() {
}
}