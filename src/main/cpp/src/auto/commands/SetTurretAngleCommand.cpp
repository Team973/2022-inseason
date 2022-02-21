#include "src/auto/commands/SetTurretAngleCommand.h"

namespace frc973 {

SetTurretAngleCommand::SetTurretAngleCommand(Turret *turret, double setAngle, u_int32_t targetTime)
        : m_turret(turret), m_setAngle(setAngle), m_targetTime(targetTime) {
}

void SetTurretAngleCommand::Init() {
    m_turret->Turn(m_setAngle, 0.0);
}

void SetTurretAngleCommand::Run() {
}

bool SetTurretAngleCommand::IsCompleted() {
    return HasElapsed();
}

void SetTurretAngleCommand::PostExecute() {
}
}