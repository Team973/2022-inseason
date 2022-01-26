// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>

#include <ctre/Phoenix.h>

#include "lib/sensors/Limelight.h"
#include "src/subsystems/Gyro.h"

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
  TalonSRX* m_gyroTalon;
  Gyro* m_gyro;

  Limelight *m_limelight;

  XboxController *m_operatorStick;
};

} //namespace frc973