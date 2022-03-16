#pragma once

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/bases/Subsystem.h"

namespace frc973 {
class Gyro : public Subsystem {
public:
    Gyro(TalonSRX *gyroTalon);

    double GetWrappedAngle();

    double GetAngle();

    double GetAngularRate();

    void SetAngle(double degrees);

    void Zero();

    double GetPitchAngle();

    double GetRollAngle();

    void Update() override;

    void DashboardUpdate() override;

private:
    PigeonIMU m_gyro;

    double m_wrappedAngle;
    double m_currentAngle;
};
}  // namespace frc973