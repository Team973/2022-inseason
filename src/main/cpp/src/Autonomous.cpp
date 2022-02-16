#include <iostream>

#include "src/Robot.h"

namespace frc973 {

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
    m_gyro->Zero();
    m_drive->Zero();
}

void Robot::AutonomousPeriodic() {
    /* Pre periodic */
    /* End pre periodic */

    /* Post periodic, drive should update here last */
    m_autoManager->Update();
    m_conveyor->Update();
    m_intake->Update();
    m_shooter->Update();
    m_lights->Update();
    m_drive->Update();
    /* End post periodic*/
}
} // namespace frc973