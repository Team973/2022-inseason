#include "src/auto/commands/PositionDriveCommand.h"

namespace frc973 {
PositionDriveCommand::PositionDriveCommand(Drive *drive, double minSpeed, double maxSpeed, uint32_t targetTime)
        : m_drive(drive), m_minSpeed(minSpeed), m_maxSpeed(maxSpeed), m_targetTime(targetTime), m_endRun(false) {
}

void PositionDriveCommand::Init() {
    m_drive->Zero();
    m_drive->SetDriveMode(Drive::DriveMode::position);
    m_drive->SetPositionTarget(1.0, 1.0);
    m_drive->ClampSpeed(m_minSpeed, m_maxSpeed);
    SetTargetMSec(m_targetTime);
}

void PositionDriveCommand::Run() {
    std::array<bool, 2> &endRun = m_drive->PositionOnTarget();

    m_endRun = endRun[Drive::Target::dist] && endRun[Drive::Target::angle];
}

bool PositionDriveCommand::IsCompleted() {
    return m_endRun;
}

void PositionDriveCommand::PostExecute() {
    m_drive->ClampSpeed(-DRIVE_TELEOP_LIMIT, DRIVE_TELEOP_LIMIT)
}

}  // namespace frc973