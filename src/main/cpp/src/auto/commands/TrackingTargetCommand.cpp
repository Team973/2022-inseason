#include "src/auto/commands/TrackingTargetCommand.h"

namespace frc973 {

TrackingTargetCommand::TrackingTargetCommand(Drive *drive, Limelight *limelight, Turret *turret, Gyro *gyro, uint32_t targetTime)
        : m_drive(drive), m_limelight(limelight), m_turret(turret), m_gyro(gyro), m_targetTime(targetTime), m_endRun(false) {
}

void TrackingTargetCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_turret->CalcOutput(m_limelight->GetXOffset(), m_gyro->GetAngularRate(), m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), m_limelight->GetHorizontalDist()));
}

void TrackingTargetCommand::Run() {
    if (m_limelight->GetXOffset() == 0.0 || HasElapsed()) {
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