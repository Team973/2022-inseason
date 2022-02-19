#include "src/SubsystemManager.h"

namespace frc973 {
SubsystemManager::SubsystemManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter,
                                   Limelight *limelight, Climb *climb, Gyro *gyro, Lights *lights)
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
    double dist = m_limelight->GetHorizontalDist();
    double tfAngle = std::fmod(m_gyro->GetWrappedAngle() + m_turret->GetTurretAngle() + 180.0, 360.0);
    if (tfAngle < 0.0) {
        tfAngle += 360.0;
    }
    tfAngle -= 180.0;
    double fieldAngle = std::fmod(tfAngle + 180.0 + 180.0, 360.0);
    if (fieldAngle < 0.0) {
        fieldAngle += 360.0;
    }
    fieldAngle -= 180.0;
    double x = dist = std::cos(Constants::RAD_PER_DEG * fieldAngle);
    double y = dist = std::sin(Constants::RAD_PER_DEG * fieldAngle);
    Pose2d pose{x,y,m_gyro->GetWrappedAngle()}
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
