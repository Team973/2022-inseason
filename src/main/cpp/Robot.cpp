// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "src/Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

void Robot::RobotInit() {
  m_shooterFlywheelMotorA = new TalonFX(FLYWHEEL_A_CAN_ID);
  m_shooterFlywheelMotorB = new TalonFX(FLYWHEEL_B_CAN_ID);
  m_shooterPrecharger = new TalonFX(PRECHARGER_CAN_ID);

  m_shooter = new Shooter(m_shooterFlywheelMotorA, m_shooterFlywheelMotorB, m_shooterPrecharger);
}

void Robot::RobotPeriodic() {
}

} // namespace frc973

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<frc973::Robot>();
}
#endif