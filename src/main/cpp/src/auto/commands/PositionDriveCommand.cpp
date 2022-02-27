#include "src/auto/commands/PositionDriveCommand.h"

namespace frc973 {
PositionDriveCommand::PositionDriveCommand(Drive *drive, double targetDist, double targetAngle, double speed,
                                           uint32_t targetTime)
        : m_drive(drive)
        , m_targetDist(targetDist)
        , m_targetAngle(targetAngle)
        , m_speed(speed)
        , m_targetTime(targetTime)
        , m_endRun(false) {
}

void PositionDriveCommand::Init() {
    SetTargetMSec(m_targetTime);
    m_drive->SetDriveMode(Drive::DriveMode::position);
    m_drive->ClampSpeed(-m_speed, m_speed);
    m_drive->Zero();
    m_drive->SetPositionTarget(m_targetDist, m_targetAngle);
}

void PositionDriveCommand::Run() {
    m_drive->ClampSpeed(-m_speed, m_speed);
    std::array<bool, 2> &endRun = m_drive->PositionOnTarget();

    m_endRun = endRun[Drive::Target::dist] && endRun[Drive::Target::angle];
}

bool PositionDriveCommand::IsCompleted() {
    return m_endRun || HasElapsed();
}

void PositionDriveCommand::PostExecute() {
    m_drive->ClampSpeed(-DRIVE_TELEOP_LIMIT, DRIVE_TELEOP_LIMIT);
    m_drive->SetDriveMode(Drive::DriveMode::arcade);
    m_drive->SetThrottleTurn(0.0, 0.0);
}

}  // namespace frc973