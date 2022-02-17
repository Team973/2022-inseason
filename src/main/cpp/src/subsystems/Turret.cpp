#include "src/subsystems/Turret.h"

namespace frc973 {

Turret::Turret(WPI_TalonFX *turretMotor, DigitalInput *turretSensor)
        : m_turretMotor(turretMotor)
        , m_turretSensor(turretSensor)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 40, 80, 0.05))
        , m_limelightPID(0.04, 0.0, 0.0, 0)
        , m_limelightToMotorPower(0.0)
        , m_turretState(TurretState::Manual)
        , m_checkStatus(0)
        , m_leftSensorChecked(false)
        , m_rightSensorChecked(false)
        , m_centerSensorChecked(false)
        , m_leftSideTurnSensor(0.0)
        , m_rightSideTurnSensor(0.0) {
    m_turretMotor->ConfigFactoryDefault();

    m_turretMotor->SetInverted(TalonFXInvertType::Clockwise);

    m_turretMotor->SetNeutralMode(NeutralMode::Coast);

    m_turretMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    m_turretMotor->ConfigClosedloopRamp(0.1);

    m_turretMotor->ConfigNominalOutputForward(0, 30);
    m_turretMotor->ConfigNominalOutputReverse(0, 30);
    m_turretMotor->ConfigPeakOutputForward(1.0, 30);
    m_turretMotor->ConfigPeakOutputReverse(-1.0, 30);

    m_turretMotor->Config_kP(0, 0.0975, 30);
    m_turretMotor->Config_kI(0, 0.0, 30);
    m_turretMotor->Config_kD(0, 0.0, 30);
    m_turretMotor->Config_kF(0, 0.0, 30);

    m_turretMotor->SetSelectedSensorPosition(0, 0, 0);

    m_turretMotor->ConfigSupplyCurrentLimit(m_currentLimit);
    m_turretMotor->ConfigStatorCurrentLimit(m_statorLimit);

    m_limelightPID.SetTarget(0.0);
}

void Turret::Turn(double angleInDegrees, double gyroOffset) {
    // 2048 ticks per rotation and gear ratio of 1:TURRET_GEAR_RATIO
    m_tickPosition = angleInDegrees * TURRET_TICKS_PER_DEGREE;

    switch (PassedSuperSoft()) {
        case 0:
            m_turretMotor->Set(ControlMode::Position, (angleInDegrees - gyroOffset) * TURRET_TICKS_PER_DEGREE);
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

void Turret::CalcOutput(double limelightXOffset, double angularVelocity, double translationalAngularRate) {
    // double output;
    m_limelightPID.SetTarget(0);
    double output = m_limelightPID.CalcOutput(limelightXOffset);

    output +=
        (-angularVelocity * Constants::GYRO_CONSTANT) + (translationalAngularRate * Constants::TRANSLATION_CONSTANT);

    m_limelightToMotorPower = output;

    m_turretMotor->Set(ControlMode::PercentOutput, output);
}

double Turret::GetTurretAngle() {
    return m_currentAngleInDegrees;
}

double Turret::CalcTransitionalCompensations(double driveVelocity, double distanceFromTarget) {
    // The position 100ms into the future calculated by current drive velocity converted into inches into the future
    double futurePosition = driveVelocity;

    double futureDistance = 0.0;
    double futureAngle = 0.0;

    // futureDistance = sqrt(pow(36, 2) + pow(5, 2) - (2.0 * 36 * 5 * (cos(86.018 * Constants::PI / 180.0))));
    futureDistance =
        sqrt(pow(distanceFromTarget, 2) + pow(futurePosition, 2) -
             (2.0 * distanceFromTarget * futurePosition * (cos(m_currentAngleInDegrees * Constants::PI / 180.0))));

    // futureAngle = 180.0 - ((acos(((pow(36, 2) + pow(5, 2) - pow(36, 2)) / (2.0 * 36 * 5)))) * 180 / Constants::PI);
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

int Turret::SensorCalibrate() {
    // looks for center sensor first
    if (!m_turretSensor->Get() || (m_centerSensorChecked == true)) {
        m_centerSensorChecked = true;

        // looks for the left sensor second
        if (m_turretMotor->IsRevLimitSwitchClosed() || (m_leftSensorChecked == true)) {
            m_leftSensorChecked = true;

            // looks for the right sensor third
            if (m_turretMotor->IsFwdLimitSwitchClosed() || (m_rightSensorChecked == true)) {
                m_rightSensorChecked = true;

                // sets the right sensor only if it is the first time seeing it,
                if (m_checkStatus == 2) {
                    m_checkStatus = 3;
                    m_rightSideTurnSensor = m_turretMotor->GetSelectedSensorPosition() -
                                            (Constants::TURRET_SOFT_OFFSET * TURRET_TICKS_PER_DEGREE);
                    return m_checkStatus;
                }

                // looks for the center sensor again for the 4th check, and locks the brake once it finds it and sethome
                if (!m_turretSensor->Get() && m_checkStatus == 3) {
                    m_checkStatus = 4;

                    SetNeutralMode(NeutralMode::Brake);
                    return m_checkStatus;
                }
                return m_checkStatus;
            }

            // left sensor is found, makes sure to set the sensor only if it is the first time seeing it
            if (m_checkStatus == 1) {
                m_checkStatus = 2;
                m_leftSideTurnSensor = m_turretMotor->GetSelectedSensorPosition() +
                                       (Constants::TURRET_SOFT_OFFSET * TURRET_TICKS_PER_DEGREE);
                return m_checkStatus;
            } else {
                return m_checkStatus;
            }
        }

        // center sensor is triggered, but makes sure that it only sets home angle if it is the first time seeing it
        if (m_checkStatus == 0) {
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

void Turret::Update() {
    m_currentAngleInDegrees = m_turretMotor->GetSelectedSensorPosition() / TURRET_TICKS_PER_DEGREE;

    switch (m_turretState) {
        case TurretState::Off:
            break;
        case TurretState::Manual:
            break;
        case TurretState::AutoAim:
            break;
    }
}

void Turret::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("T CurrAngle", m_currentAngleInDegrees);
    frc::SmartDashboard::PutNumber("T ticksPosition", m_tickPosition);
    frc::SmartDashboard::PutNumber("T ActualTickPosition", m_turretMotor->GetSelectedSensorPosition());
    frc::SmartDashboard::PutNumber("T turretStatorCurrent", m_turretMotor->GetStatorCurrent());
    frc::SmartDashboard::PutNumber("T turretSupplyCurrent", m_turretMotor->GetSupplyCurrent());

    SmartDashboard::PutBoolean("T turret digital input", m_turretSensor->Get());
    SmartDashboard::PutBoolean("T turret fwd sensor", m_turretMotor->IsFwdLimitSwitchClosed());
    SmartDashboard::PutBoolean("T turret rev sensor", m_turretMotor->IsRevLimitSwitchClosed());

    SmartDashboard::PutBoolean("T digital input", m_turretSensor->Get());
    // right side limit switch
    SmartDashboard::PutBoolean("T fwd sensor", m_turretMotor->IsFwdLimitSwitchClosed());
    // left side limit switch
    SmartDashboard::PutBoolean("T rev sensor", m_turretMotor->IsRevLimitSwitchClosed());

    SmartDashboard::PutNumber("T checkstatus", m_checkStatus);
}

}  // namespace frc973