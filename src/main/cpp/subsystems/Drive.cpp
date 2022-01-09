#include "src/subsystems/Drive.h"

namespace frc973{

void Drive::Update() {
    array<double, 4> outputs;

    switch (m_driveMode) {
        case DriveMode::arcade:

            break;
        case DriveMode::position:
           
            break;
        case DriveMode::cheesyDrive:
           
            break;
        default:
            outputs = {0.0, 0.0};
    }

    m_leftOutput = std::clamp(outputs[Outputs::leftThrottle] + outputs[Outputs::leftTurn], m_minSpeed, m_maxSpeed);
    m_rightOutput = std::clamp(outputs[Outputs::rightThrottle] + outputs[Outputs::rightTurn], m_minSpeed, m_maxSpeed);

    m_leftOutput *= MAX_TICKS_PER_100_MS;
    m_rightOutput *= MAX_TICKS_PER_100_MS;

    CheckForIsNaN();

    SetVelocity(m_leftOutput, m_rightOutput);
    SmartDashboard::PutNumber("Left Distance", GetLeftPosition());
    SmartDashboard::PutNumber("Right Distance", GetRightPosition());
}





} //namespace frc973 
