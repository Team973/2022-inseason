#pragma once

#include "lib/bases/Subsystem.h"
#include "src/RobotInfo.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
#include <frc/Solenoid.h>

namespace frc973 {

class Intake : public Subsystem {

public:
    /** 
     * Constructs the intake subsystem 
     */
    Intake(TalonFX *intakeTalon, frc::Solenoid *intakeSolenoid);

    enum class IntakeState {
        Deploy, /* Deploys the Intake */
        Retract /* Retracts the Intake */
    };

    enum class IntakeMotorState {
        Off, /* Intake wheels don't run */
        FeedIn, /* Runs the intake wheels towards the conveyer */
        FeedOut, /* Runs the intake wheels away from the conveyer */
        Manual /* Driver controls the intake speed */
    };


     /** 
     * Deploys the Intake
     */
    void Deploy();

    /** 
     * Retracts the Intake
     */
    void Retract();

    /** 
     * Gets current intake stake 
     */
    Intake::IntakeState GetIntakeState();
    
   /** 
     * Sets current intake stake 
     */
    void SetIntakeState(IntakeState state);

    /** 
     * Changes the speed of the intake moves at
     */
    void SetPercentOutput(double speed);

    /** 
     * Updates the intake subsystem 
     */
    void Update();

    /** 
     * Updates the intake subsystem in Smartdashboard
     */
    void DashboardUpdate();
  
private: 
    double m_intakeSpeed;
    
    IntakeState m_intakeState;
    IntakeMotorState m_intakeMotorState;
    TalonFX *m_intakeTalon; 
    frc::Solenoid *m_intakeSolenoid;
};
  
} // namespace frc973
