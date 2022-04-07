#include "src/subsystems/Turret.h"

namespace frc973 {

Turret::Turret(TalonFX *turretMotor, DigitalInput *turretSensor)
        : m_turretMotor(turretMotor)
        , m_turretSensor(turretSensor)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 80, 100, 0.05))
        , m_limelightPID(0.025, 0.0, 0.0, 0)
        , m_turretState(TurretState::Off)
        , m_checkStatus(0)
        , m_leftSensorChecked(false)
        , m_rightSensorChecked(false)
        , m_centerSensorChecked(false)
        , m_leftSideTurnSensor(-TURRET_SENSOR_SOFT)
        , m_rightSideTurnSensor(TURRET_SENSOR_SOFT)
        , m_wrappingToLeftSensor(false)
        , m_wrappingToRightSensor(false)
        , m_wrappingInProgress(false)
        , m_gyroSnapshotWrapping(0.0)
        , m_angleInDegrees(0.0)
        , m_limelightXOffset(0.0)
        , m_angularRate(0.0)
        , m_translationalValue(0.0) {
    m_turretMotor->ConfigFactoryDefault();

    m_turretMotor->SetInverted(TalonFXInvertType::Clockwise);

    m_turretMotor->SetNeutralMode(NeutralMode::Coast);

    m_turretMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    m_turretMotor->ConfigClosedloopRamp(0.1);

    m_turretMotor->ConfigNominalOutputForward(0, 30);
    m_turretMotor->ConfigNominalOutputReverse(0, 30);
    m_turretMotor->ConfigPeakOutputForward(1.0, 30);
    m_turretMotor->ConfigPeakOutputReverse(-1.0, 30);

    m_turretMotor->ConfigVoltageCompSaturation(12.0);
    m_turretMotor->EnableVoltageCompensation(true);

    m_turretMotor->Config_kP(0, 0.06, 30);
    m_turretMotor->Config_kI(0, 0.0, 30);
    m_turretMotor->Config_kD(0, 0.0, 30);
    m_turretMotor->Config_kF(0, 0.0, 30);

    m_turretMotor->SetSelectedSensorPosition(0, 0, 0);

    m_turretMotor->ConfigSupplyCurrentLimit(m_currentLimit);
    m_turretMotor->ConfigStatorCurrentLimit(m_statorLimit);

    m_limelightPID.SetTarget(0.0);
}

void Turret::SetTurretState(TurretState state) {
    m_turretState = state;
}

void Turret::SetTurnValue(double angle) {
    m_angleInDegrees = angle;
}

void Turret::Turn(double angleInDegrees) {
    // 2048 ticks per rotation and gear ratio of 1:TURRET_GEAR_RATIO
    m_tickPosition = angleInDegrees * TURRET_TICKS_PER_DEGREE;

    switch (PassedSuperSoft()) {
        case 0:
            m_turretMotor->Set(ControlMode::Position, angleInDegrees * TURRET_TICKS_PER_DEGREE);
            break;
        case 1:
            m_turretMotor->Set(ControlMode::Position, m_rightSideTurnSensor);
            break;
        case 2:
            m_turretMotor->Set(ControlMode::Position, m_leftSideTurnSensor);
            break;

        default:
            break;
    }
}

double Turret::CalcJoystickAngleInDegrees(double x, double y) {
    double angleInDegrees;
    double distance;

    // deadband
    distance = sqrt(pow(x, 2.0) + pow(y, 2.0));
    if (distance < 0.5) {
        return 0.0;
    }

    // converts radians to degrees after setting the location of the wrap around point.

    angleInDegrees = atan2(y, x) * 180 / Constants::PI;

    return angleInDegrees;
}

void Turret::SetTrackingValues(double xOffset, double angularRate, double translationalValue) {
    m_limelightXOffset = xOffset;
    m_angularRate = angularRate;
    m_translationalValue = translationalValue;
}

void Turret::CalcOutput(double limelightXOffset, double angularVelocity, double translationalAngularRate) {
    m_tickPosition = m_turretMotor->GetSelectedSensorPosition();

    // double output;
    m_limelightPID.SetTarget(0);
    double output;
    std::clamp(output, -1.0, 1.0);
    output = m_limelightPID.CalcOutput(limelightXOffset);

    output += (-angularVelocity * Constants::GYRO_CONSTANT);

    if (m_wrappingToRightSensor == true) {
        if (PassedSuperSoft() == 1) {
            m_wrappingToRightSensor = false;
            m_gyroSnapshotWrapping = m_gyroAngle;
            m_wrappingInProgress = false;
        } else {
            m_turretMotor->Set(ControlMode::Position, m_rightSideTurnSensor);
        }
    } else if (m_wrappingToLeftSensor == true) {
        if (PassedSuperSoft() == 2) {
            m_wrappingToLeftSensor = false;
            m_gyroSnapshotWrapping = m_gyroAngle;
            m_wrappingInProgress = false;
        } else {
            m_turretMotor->Set(ControlMode::Position, m_leftSideTurnSensor);
        }
    } else {
        if (PassedSuperSoft() == 2) {
            output = std::clamp(output, 0.0, 1.0);
            if (m_wrappingInProgress == false) {
                m_gyroSnapshotWrapping = m_gyroAngle;
                m_wrappingInProgress = true;
            } else {
                if (std::abs(m_gyroAngle - m_gyroSnapshotWrapping) > 70) {
                    m_wrappingToRightSensor = true;
                }
            }
        } else if (PassedSuperSoft() == 1) {
            output = std::clamp(output, -1.0, 0.0);
            if (m_wrappingInProgress == false) {
                m_gyroSnapshotWrapping = m_gyroAngle;
                m_wrappingInProgress = true;
            } else {
                if (std::abs(m_gyroAngle - m_gyroSnapshotWrapping) > 70) {
                    m_wrappingToLeftSensor = true;
                }
            }
        } else {
            m_wrappingInProgress = false;
            m_gyroSnapshotWrapping = m_gyroAngle;
        }
        m_turretMotor->Set(ControlMode::PercentOutput, output);
    }
}

double Turret::GetTurretAngle() {
    return m_currentAngleInDegrees;
}

double Turret::CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget) {
    // The position 100ms into the future calculated by current drive velocity converted into inches into the future
    double futurePosition = driveVelocity;

    double futureDistance = 0.0;
    double futureAngle = 0.0;

    futureDistance =
        sqrt(pow(distanceFromTarget, 2) + pow(futurePosition, 2) -
             (2.0 * distanceFromTarget * futurePosition * (cos(m_currentAngleInDegrees * Constants::PI / 180.0))));

    futureAngle = 180.0 - ((acos(((pow(futureDistance, 2) + pow(futurePosition, 2) - pow(distanceFromTarget, 2)) /
                                  (2.0 * futureDistance * futurePosition)))) *
                           180.0 / Constants::PI);
    SmartDashboard::PutNumber("Future Angle", futureAngle);

    // result is the rate of turning due to transitional change from per100ms to per1sec
    SmartDashboard::PutNumber("Future Distance", futureDistance);
    SmartDashboard::PutNumber("Future Position", futurePosition);
    return (futureAngle - m_currentAngleInDegrees) / 0.1;
}

void Turret::SetNeutralMode(NeutralMode mode) {
    m_turretMotor->SetNeutralMode(mode);
}

void Turret::SetTurretAngle(double angle) {
    m_turretMotor->SetSelectedSensorPosition(angle * TURRET_TICKS_PER_DEGREE);
}

void Turret::SetHomeOffset() {
    Turret::SetTurretAngle(Constants::TURRET_HOME_OFFSET);
}

void Turret::CheckedSensorsToFalse() {
    m_leftSensorChecked = false;
    m_rightSensorChecked = false;
    m_centerSensorChecked = false;
    m_checkStatus = 0;

    m_wrappingInProgress = false;
    m_wrappingToLeftSensor = false;
    m_wrappingToRightSensor = false;
}

int Turret::SensorCalibrate() {
    // looks for center sensor first
    if (!m_turretSensor->Get() || (m_centerSensorChecked == true)) {
        m_centerSensorChecked = true;

        // center sensor is triggered, but makes sure that it only sets home angle if it is the first time seeing it
        if (m_checkStatus == 0) {
            SetNeutralMode(NeutralMode::Brake);
            m_checkStatus = 1;
            SetHomeOffset();
            return m_checkStatus;
        } else {
            return m_checkStatus;
        }
    }

    return m_checkStatus;
}

int Turret::PassedSuperSoft() {
    if (m_tickPosition > m_rightSideTurnSensor) {
        return 1;  // right limit passed
    } else if (m_tickPosition < m_leftSideTurnSensor) {
        return 2;  // left limit passed
    } else {
        return 0;  // no limits passed
    }
}

bool Turret::StickMoved(double x, double y) {
    double distance = 0;
    distance = sqrt(pow(x, 2.0) + pow(y, 2.0));
    if (distance < 0.5) {
        return false;
    } else {
        return true;
    }
}

void Turret::UpdateValues(double gyroAngle) {
    m_gyroAngle = gyroAngle;
}

bool Turret::GetWrappedState() {
    if (m_wrappingToLeftSensor || m_wrappingToRightSensor) {
        return true;
    } else {
        return false;
    }
}

bool Turret::GetRightSensor() {
    return m_turretMotor->IsRevLimitSwitchClosed();
}

bool Turret::GetLeftSensor() {
    return m_turretMotor->IsFwdLimitSwitchClosed();
}

bool Turret::GetMiddleSensor() {
    return !m_turretSensor->Get();
}

void Turret::Update() {
    m_currentAngleInDegrees = m_turretMotor->GetSelectedSensorPosition() / TURRET_TICKS_PER_DEGREE;

    switch (m_turretState) {
        case TurretState::Off:
            break;
        case TurretState::Manual:
            Turn(m_angleInDegrees);
            break;
        case TurretState::Tracking:
            CalcOutput(m_limelightXOffset, m_angularRate, m_translationalValue);
            break;
    }

    SensorCalibrate();
}

void Turret::DashboardUpdate() {
    SmartDashboard::PutNumber("T CurrAngle", m_currentAngleInDegrees);
    SmartDashboard::PutBoolean("T digital input", m_turretSensor->Get());
    // right side limit switch
    SmartDashboard::PutBoolean("T fwd sensor", m_turretMotor->IsFwdLimitSwitchClosed());
    // left side limit switch
    SmartDashboard::PutBoolean("T rev sensor", m_turretMotor->IsRevLimitSwitchClosed());
}

}  // namespace frc973