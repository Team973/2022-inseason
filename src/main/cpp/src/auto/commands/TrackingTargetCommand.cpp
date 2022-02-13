#include "src/auto/commands/TrackingTargetCommand.h"

namespace frc973 {

TrackingTargetCommand::TrackingTargetCommand(Limelight *limeLight, Turret *turret, Gyro *gyro, uint32_t targetTime)
        : m_limeLight(limeLight), m_turret(turret), m_gyro(gyro), m_targetTime(targetTime), m_hasElapsed(false) {
}

void TrackingTargetCommand::Init() {
    m_turret->CalcOutput(m_limeLight->GetXOffset(), m_gyro->GetAngularRate());
}

void TrackingTargetCommand::Run() {
    if (-5.0 < m_limeLight->GetXOffset() < 5.0) {
        m_hasElapsed = true;
    } else {
        m_hasElapsed = false;
    }
}

bool TrackingTargetCommand::IsCompleted() {
    return m_hasElapsed;
}

void TrackingTargetCommand::PostExecute() {
}

}  // namespace frc973