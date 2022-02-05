// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <fmt/core.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/Solenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

#include "RobotInfo.h"
#include "src/subsystems/Gyro.h"
#include "subsystems/Intake.h"
#include "subsystems/Climb.h"
#include "subsystems/Shooter.h"
#include "subsystems/Conveyor.h"

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
  // Climb
  DigitalInput *m_bottomLeftSensor;
  DigitalInput *m_bottomRightSensor;
  DigitalInput *m_topLeftSensor;
  DigitalInput *m_topRightSensor;
  WPI_TalonFX *m_climbTalonA;
  WPI_TalonFX *m_climbTalonB;
  Climb *m_climb;

  //Conveyor
  TalonSRX *m_conveyorFloorMotor;
  TalonSRX *m_conveyorTowerMotorA;
  TalonSRX *m_conveyorTowerMotorB;
  Conveyor *m_conveyor;

  //Gyro
  TalonSRX* m_gyroTalon;
  Gyro* m_gyro;

  //Intake
  TalonFX *m_intakeTalon;
  Solenoid *m_intakeSolenoid;
  Intake *m_intake;

  //Shooter
  TalonFX *m_shooterFlywheelMotorA;
  TalonFX *m_shooterFlywheelMotorB;
  TalonFX *m_shooterPrecharger;
  Shooter *m_shooter;

};

} //namespace frc973