#include "src/auto/commands/CenterTurretCommand.h"

namespace frc973 {

CenterTurretCommand::CenterTurretCommand(Limelight *limeLight, Turret *turret, Gyro *gyro, uint32_t targetTime)
        : m_limeLight(limeLight), m_turret(turret), m_gyro(gyro), m_targetTime(targetTime) {
}

void CenterTurretCommand::Init() {
    if (!(-5.0 < m_limeLight->GetXOffset() < 5.0)) {
        IsCompleted();
    } else {
        m_turret->CalcOutput(m_limeLight->GetXOffset(), m_gyro->GetAngularRate());
        Init();
    }
}

void CenterTurretCommand::Run() {
}

bool CenterTurretCommand::IsCompleted() {
}

void CenterTurretCommand::PostExecute() {
}

}  // namespace frc973