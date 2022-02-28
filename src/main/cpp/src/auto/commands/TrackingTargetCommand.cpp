#include "src/auto/commands/TrackingTargetCommand.h"

namespace frc973 {

TrackingTargetCommand::TrackingTargetCommand(Drive *drive, Limelight *limelight, Turret *turret, Gyro *gyro, uint32_t targetTime)
        : m_drive(drive), m_limelight(limelight), m_turret(turret), m_gyro(gyro), m_targetTime(targetTime), m_endRun(false) {
}

void TrackingTargetCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_limelight->SetVisionCamera();
    m_turret->SetTurretState(TurretState::Tracking);
}

void TrackingTargetCommand::Run() {
    if (std::abs(m_limelight->GetXOffset()) < LIMELIGHT_ANGLE_TOLERANCE) {
        m_endRun = true;
    } else {
        m_endRun = false;
    }
}

bool TrackingTargetCommand::IsCompleted() {
    return m_endRun || HasElapsed();
}

void TrackingTargetCommand::PostExecute() {
}

}  // namespace frc973