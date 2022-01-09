#pragma once

#include "lib/bases/Subsystem.h"

#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {

class Intake : public Subsystem {

public:
    /** 
     * Constructs the intake subsystem 
     */
    Intake();

    enum class IntakeState {
        Deploy, /* Deploys the Intake */
        Retract /* Retracts the Intake */
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
     * Updates the intake subsystem 
     */
    void Update();

    /** 
     * Updates the intake subsystem in Smartdashboard
     */
    void DashboardUpdate();
  
private: 
    IntakeState m_intakeState;
};
  
} // namespace frc973
