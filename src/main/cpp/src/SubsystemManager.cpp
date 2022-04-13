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
        , m_lights(lights)
        , m_robotPose(units::meter_t(0.0), units::meter_t(0.0), units::radian_t(0.0))
        , m_dumpZone(units::meter_t(0.0 * Constants::METERS_PER_INCH),
                     units::meter_t(-300.0 * Constants::METERS_PER_INCH))
        , m_suspendCalcPose(false)
        , m_targetLossedFlag(false) {
}

void SubsystemManager::TurretCalibration() {
    switch (m_turret->SensorCalibrate()) {
        case 0:
            m_lights->SetLightsState(Lights::LightsState::Middle);
            break;
        case 1:
            m_lights->SetLightsState(Lights::LightsState::Initialization);
            break;
        default:
            m_lights->SetLightsState(Lights::LightsState::Off);
            break;
    }
}

Pose2d SubsystemManager::CalcPose() {
    double dist = m_limelight->GetHorizontalDist2();
    double gyroAngle = m_gyro->GetWrappedAngle();
    double tfAngle = std::fmod(gyroAngle + m_turret->GetTurretAngle() - m_limelight->GetXOffset() + 180.0, 360.0);
    if (tfAngle < 0.0) {
        tfAngle += 360.0;
    }
    tfAngle -= 180.0;

    double fieldAngle = std::fmod(tfAngle + 180.0 + 180.0, 360.0);
    if (fieldAngle < 0.0) {
        fieldAngle += 360.0;
    }
    fieldAngle -= 180.0;

    double x = Constants::METERS_PER_INCH * dist * std::cos(Constants::RAD_PER_DEG * fieldAngle);
    double y = Constants::METERS_PER_INCH * dist * std::sin(Constants::RAD_PER_DEG * fieldAngle);

    Pose2d pose{units::meter_t(x), units::meter_t(y), units::radian_t(Constants::RAD_PER_DEG * gyroAngle)};
    return pose;
}

void SubsystemManager::SuspendCalcPose(bool suspend) {
    m_suspendCalcPose = suspend;
}

double SubsystemManager::CalcFlywheelRPM() {
    double dist = m_limelight->GetHorizontalDist2();
    double flywheelRPM = 0.0;

    if (dist >= FLY_DIST_CLOSE) {
        flywheelRPM =
            (FLY_RPM_FAR - FLY_RPM_CLOSE) / (FLY_DIST_FAR - FLY_DIST_CLOSE) * (dist - FLY_DIST_CLOSE) + FLY_RPM_CLOSE;
    } else {
        flywheelRPM = FLY_RPM_CLOSE;
    }

    return flywheelRPM;
}

double SubsystemManager::CalcShoopRPM() {
    double dist = m_dumpZone.Distance(m_robotPose.Translation()).value() * Constants::INCHES_PER_METER;
    frc::SmartDashboard::PutNumber("shoop Distance", dist);
    double shoopRPM = 0.0;
    shoopRPM = (SHOOP_RPM_FAR - SHOOP_RPM_CLOSE) / (SHOOP_DIST_FAR - SHOOP_DIST_CLOSE) * (dist - SHOOP_DIST_CLOSE) +
               SHOOP_RPM_CLOSE;
    if (shoopRPM > SHOOP_RPM_FAR) {
        shoopRPM = SHOOP_RPM_FAR;
    }
    if (shoopRPM < SHOOP_RPM_CLOSE) {
        shoopRPM = SHOOP_RPM_CLOSE;
    }
    frc::SmartDashboard::PutNumber("shoop RPM", shoopRPM);
    return shoopRPM;
}

double SubsystemManager::CalcTargetTurretAngle() {
    double turretAngle = 0.0;
    double poseX = m_robotPose.X().value();
    double poseY = m_robotPose.Y().value();
    double poseHeading = m_robotPose.Rotation().Degrees().value();
    double dumpX = m_dumpZone.X().value();
    double dumpY = m_dumpZone.Y().value();
    double heading = Constants::DEG_PER_RAD * atan2((dumpY - poseY), (dumpX - poseX));
    turretAngle = std::fmod(heading - poseHeading + 180, 360.0);
    if (turretAngle < 0) {
        turretAngle += 360;
    }
    turretAngle -= 180;
    return turretAngle;
}

void SubsystemManager::SetDumpZone(Translation2d dumpZone) {
    m_dumpZone = dumpZone;
}

bool SubsystemManager::ReadyToShoot() {
    double distance = m_limelight->GetHorizontalDist2();
    if (m_shooter->IsAtSpeed() && m_turret->IsAtAngle()) {
        if (m_shooter->GetShooterState() == Shooter::ShooterState::Tracking) {
            return ((distance > TOO_CLOSE_LOCKOUT) && (distance < TOO_FAR_LOCKOUT));
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void SubsystemManager::Update() {
    // Update Pose Calculation
    if (m_limelight->isTargetValid()) {
        m_targetLossedFlag = false;
        if (!m_suspendCalcPose) {
            m_robotPose = CalcPose();
        }
    } else {
        if (!m_targetLossedFlag) {
            m_targetLossedFlag = true;
            m_drive->SetPose(m_robotPose);
        }
        m_robotPose = m_drive->GetPose();
    }
    frc::SmartDashboard::PutNumber("POSE X", m_robotPose.X().value() * Constants::INCHES_PER_METER);
    frc::SmartDashboard::PutNumber("POSE Y", m_robotPose.Y().value() * Constants::INCHES_PER_METER);
    frc::SmartDashboard::PutNumber("POSE Theta", m_robotPose.Rotation().Degrees().value());

    // Update Drive Values
    m_drive->SetAngle(m_gyro->GetWrappedAngle());
    m_drive->SetAngularRate(m_gyro->GetAngularRate());

    // Calculate Turret values
    m_turret->UpdateValues(m_gyro->GetAngle());
    if (m_limelight->isTargetValid()) {
        if (m_turret->GetWrappedState()) {
            m_turret->CheckedSensorsToFalse();
        }

        m_turret->SetTrackingValues(
            m_limelight->GetXOffset(), m_gyro->GetAngularRate(),
            m_turret->CalcTransitionalCompensations(m_drive->GetVelocity(), m_limelight->GetHorizontalDist()));
    } else {
        m_turret->SetTrackingValues(m_limelight->GetXOffset(), m_gyro->GetAngularRate(), 0.0);
    }

    // Shooter flywheel calculation values
    m_shooter->SetTrackingFlywheelRPM(CalcFlywheelRPM());
    m_shooter->SetShoopFlywheelRPM(CalcShoopRPM());

    /**
     * Ready to shoot checks
     */
    if (ReadyToShoot()) {
        m_lights->SetLightsState(Lights::LightsState::ReadyToShoot);
        m_conveyor->SetReadyToShoot(true);
    } else {
        m_lights->SetLightsState(Lights::LightsState::NotReadyToShoot);
        m_conveyor->SetReadyToShoot(false);
    }
}

}  // namespace frc973
