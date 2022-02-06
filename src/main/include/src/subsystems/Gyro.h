#pragma once

#include <ctre/Phoenix.h>
#include "lib/bases/Subsystem.h"
#include <frc/smartdashboard/SmartDashboard.h>

namespace frc973 {
    class Gyro : public Subsystem {
    public:
        Gyro(TalonSRX *gyroTalon);  

        double GetWrappedAngle();
        
        double GetAngle();
        
        double GetAngularRate();

        void Update() override; 
        
        void DashboardUpdate() override;
        
        void SetAngle(double degrees);

        void Zero();
        

    private:
        PigeonIMU m_gyro;

        double m_wrappedAngle;
        double m_currentAngle;

    };
}