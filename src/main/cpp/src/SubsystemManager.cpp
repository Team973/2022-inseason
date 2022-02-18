#include "src/SubsystemManager.h"

namespace frc973 {
SubsystemManager::SubsystemManager(Drive *drive, Intake *intake, Conveyor *conveyor, Turret *turret, Shooter *shooter,
                                   Climb *climb, Gyro *gyro, Lights *lights)
        : m_drive(drive)
        , m_intake(intake)
        , m_conveyor(conveyor)
        , m_turret(turret)
        , m_shooter(shooter)
        , m_climb(climb)
        , m_gyro(gyro)
        , m_lights(lights) {
}

void SubsystemManager::Update() {
    // turret -> limelight, gyro, drive
    // lights -> shooter, turret, climb
    // turret calibration + light to signal the side needed

    /**
     * Turret calibration and CANdle switching
     */ 
    // waiting for leo to create proper functions
    // SmartDashboard::PutBoolean("Left Switch", m_turret->IsRevLimitSwitchClosed());
    // SmartDashboard::PutBoolean("Right Switch", m_turret->IsFwdLimitSwitchClosed());
    // SmartDashboard::PutBoolean("Middle Switch", !m_turret->Get());

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
