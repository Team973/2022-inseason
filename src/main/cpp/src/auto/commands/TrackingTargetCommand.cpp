#include "src/auto/commands/TrackingTargetCommand.h"

namespace frc973 {

TrackingTargetCommand::TrackingTargetCommand(Limelight *limeLight, Turret *turret, Gyro *gyro, uint32_t targetTime)
        : m_limeLight(limeLight), m_turret(turret), m_gyro(gyro), m_targetTime(targetTime) {
}

void TrackingTargetCommand::Init() {
    if (-5.0 < m_limeLight->GetXOffset() < 5.0) {
        IsCompleted();
    } else {
        m_turret->CalcOutput(m_limeLight->GetXOffset(), m_gyro->GetAngularRate());
        Init();
    }
}

void TrackingTargetCommand::Run() {
}

bool TrackingTargetCommand::IsCompleted() {
    return true;
}

void TrackingTargetCommand::PostExecute() {
}

}  // namespace frc973