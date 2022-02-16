#include "src/auto/commands/TrackingTargetCommand.h"

namespace frc973 {

TrackingTargetCommand::TrackingTargetCommand(Limelight *limeLight, Turret *turret, Gyro *gyro, uint32_t targetTime)
        : m_limeLight(limeLight), m_turret(turret), m_gyro(gyro), m_targetTime(targetTime), m_endRun(false) {
}

void TrackingTargetCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_turret->CalcOutput(m_limeLight->GetXOffset(), m_gyro->GetAngularRate());
}

void TrackingTargetCommand::Run() {
    if (m_limeLight->GetXOffset() == 0.0 || HasElapsed()) {
        m_endRun = true;
    } else {
        m_endRun = false;
    }
}

bool TrackingTargetCommand::IsCompleted() {
    return m_endRun;
}

void TrackingTargetCommand::PostExecute() {
}

}  // namespace frc973