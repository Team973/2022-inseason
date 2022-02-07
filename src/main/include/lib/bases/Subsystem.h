#pragma once

namespace frc973 {

class Subsystem {
public:
    /**
     * Update the subsystem, called in Periodic. ex: TeleopPeriodic
     */
    virtual void Update() = 0;

    /**
     * Update the subsystem prints in smartdashboard, called in RobotPeriodic
     */
    virtual void DashboardUpdate() = 0;
};

}  // namespace frc973