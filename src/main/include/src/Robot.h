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
#include "ctre/phoenix/led/RainbowAnimation.h"
#include "RobotInfo.h"

#include "lib/sensors/Limelight.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Gyro.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Climb.h"
#include "src/subsystems/Shooter.h"
#include "src/subsystems/Conveyor.h"
#include "src/subsystems/Lights.h"

#include "src/subsystems/Turret.h"
#include "lib/util/Util.h"
#include "lib/helpers/StickController.h"



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
  //Drive
  WPI_TalonFX *m_leftDriveTalonA;
  WPI_TalonFX *m_leftDriveTalonB;
  WPI_TalonFX *m_leftDriveTalonC;
  WPI_TalonFX *m_rightDriveTalonA;
  WPI_TalonFX *m_rightDriveTalonB; 
  WPI_TalonFX *m_rightDriveTalonC;  
  Drive *m_drive; 
    
  //Intake
  TalonFX *m_intakeTalon;
  Solenoid *m_intakeSolenoid;
  Intake *m_intake;

  //Conveyor
  TalonSRX *m_conveyorFloorMotor;
  TalonSRX *m_conveyorTowerMotorA;
  TalonSRX *m_conveyorTowerMotorB;
  Conveyor *m_conveyor;

  //Turret
  WPI_TalonFX *m_turretTalon;
  Turret *m_turret;
    
  //Shooter
  WPI_TalonFX *m_shooterFlywheelMotorA;
  WPI_TalonFX *m_shooterFlywheelMotorB;
  WPI_TalonFX *m_shooterPrecharger;
  Shooter *m_shooter;

  //Limelight
  Limelight *m_limelight;

  //Climb
  DigitalInput *m_bottomLeftSensor;
  DigitalInput *m_bottomRightSensor;
  DigitalInput *m_topLeftSensor;
  DigitalInput *m_topRightSensor;
  WPI_TalonFX *m_climbTalonA;
  WPI_TalonFX *m_climbTalonB;
  Climb *m_climb;
    
  //Gyro
  TalonSRX* m_gyroTalon;
  Gyro* m_gyro;

  //Lights
  CANdle *m_CANdle;
  Lights *m_lights;

  //joysticks
  StickController *m_driverStick;
  StickController *m_operatorStick;
};

} //namespace frc973