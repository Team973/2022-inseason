#include "src/auto/commands/PositionDriveCommand.h"

namespace frc973 {
PositionDriveCommand::PositionDriveCommand(Drive *drive, uint32_t targetTime)
        : m_drive(drive), m_targetTime(targetTime) {
}

void PositionDriveCommand::Init() {
    m_drive->Zero();
    // set drivemode to position
    // set position target
    // clamp speed
    // set target time
}

void PositionDriveCommand::Run() {
    // check if on target /w tolerance
}

bool PositionDriveCommand::IsCompleted() {
    // return on target /w tolerance (m_endRun)
}

void PositionDriveCommand::PostExecute() {
    // clamp speed to teleop drive limit
}

}  // namespace frc973