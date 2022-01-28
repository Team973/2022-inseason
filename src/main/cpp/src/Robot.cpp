// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

namespace frc973 {

void Robot::RobotInit() {
  m_gyroTalon = new TalonSRX(9);
  m_gyro = new Gyro(m_gyroTalon);
  m_gyro->Zero();

  m_limelight = new Limelight("limelight");

  m_operatorStick = new XboxController(1);
}

void Robot::RobotPeriodic() {
  SmartDashboard::PutNumber("pipeline", m_limelight->GetPipeline());
  SmartDashboard::PutNumber("x", m_limelight->GetXOffset());
  m_gyro->Update();
  m_gyro->DashboardUpdate();
}

} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif