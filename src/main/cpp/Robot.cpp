// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

void Robot::RobotInit() {
  //Joystick
  m_driverStick = new Joystick(1);
  m_operatorStick = new XboxController(0);

  //Drive
  m_leftDriveTalonA = new WPI_TalonFX(LEFT_DRIVE_TALON_A);
  m_leftDriveTalonB = new WPI_TalonFX(LEFT_DRIVE_TALON_B);
  m_leftDriveTalonC = new WPI_TalonFX(LEFT_DRIVE_TALON_C);
  m_rightDriveTalonA = new WPI_TalonFX(RIGHT_DRIVE_TALON_A);
  m_rightDriveTalonB = new WPI_TalonFX(RIGHT_DRIVE_TALON_B);
  m_rightDriveTalonC = new WPI_TalonFX(RIGHT_DRIVE_TALON_C);

  m_drive = new Drive(m_leftDriveTalonA, m_leftDriveTalonB, m_leftDriveTalonC, 
                      m_rightDriveTalonA, m_rightDriveTalonB, m_rightDriveTalonC);
}

void Robot::RobotPeriodic() {
  m_drive->DashboardUpdate();


}

} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif