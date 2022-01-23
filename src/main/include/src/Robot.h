// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <fmt/core.h>

#include <ctre/Phoenix.h>
#include "subsystems/Shooter.h"
#include "RobotInfo.h"

using namespace frc;
namespace frc973 {
class Robot : public TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;

 private:

 TalonFX *m_shooterFlywheelMotorA;
 TalonFX *m_shooterFlywheelMotorB;
 TalonFX *m_shooterPrecharger;

 Shooter *m_shooter;

};

} //namespace frc973