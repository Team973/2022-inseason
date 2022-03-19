#pragma once

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "lib/bases/Subsystem.h"

namespace frc973 {
class Gyro : public PigeonIMU {
public:

    double GetWrappedAngle();

    double GetAngle();

    double GetAngularRate();

    void SetAngle(double degrees);

    void Zero();

    void Update();

    void DashboardUpdate();

private:
    PigeonIMU m_gyro;

    double m_wrappedAngle;
    double m_currentAngle;
};
}  // namespace frc973