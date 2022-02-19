#include "src/SubsystemManager.h"

namespace frc973 {
SubsystemManager::SubsystemManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter, Limelight *limelight,
                                   Climb *climb, Gyro *gyro, Lights *lights)
        : m_drive(drive)
        , m_intake(intake)
        , m_conveyor(conveyor)
        , m_turret(turret)
        , m_shooter(shooter)
        , m_limelight(limelight)
        , m_climb(climb)
        , m_gyro(gyro)
        , m_lights(lights) {
}

double SubsystemManager::CalcPose() {
    double x_dist = m_limelight->GetHorizontalDist();
}

double SubsystemManager::CalcFlywheelRPM() {
    double x_dist = m_limelight->GetHorizontalDist();
}

bool SubsystemManager::ReadyToShoot() {
    if (m_shooter->IsAtSpeed()) {
        if (m_conveyor->GetFloorVelocity() > 0.0 && m_conveyor->GetTowerVelocity() > 0.0) {
            return true;
        }
    }
    return false;
}

void SubsystemManager::Update() {
    /**
     * Turret calibration and CANdle switching
     */
    // waiting for leo to create proper functions
    SmartDashboard::PutBoolean("Left Switch", m_turret->GetLeftSensor());
    SmartDashboard::PutBoolean("Right Switch", m_turret->GetRightSensor());
    SmartDashboard::PutBoolean("Middle Switch", m_turret->GetMiddleSensor());

    switch (m_turret->SensorCalibrate()) {
        case 0:
            m_lights->SetLightsState(Lights::LightsState::Middle);
            break;
        case 1:
            m_lights->SetLightsState(Lights::LightsState::Left);
            break;
        case 2:
            m_lights->SetLightsState(Lights::LightsState::Right);
            break;
        case 3:
            m_lights->SetLightsState(Lights::LightsState::Middle);
            break;
        case 4:
            m_lights->SetLightsState(Lights::LightsState::Initialization);
            break;
        default:
            m_lights->SetLightsState(Lights::LightsState::Off);
            break;
    }
}

}  // namespace frc973
