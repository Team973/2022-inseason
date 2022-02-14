#include "src/subsystems/Drive.h"

namespace frc973 {

Drive::Drive(WPI_TalonFX *leftDriveTalonA, WPI_TalonFX *leftDriveTalonB, WPI_TalonFX *leftDriveTalonC,
             WPI_TalonFX *rightDriveTalonA, WPI_TalonFX *rightDriveTalonB, WPI_TalonFX *rightDriveTalonC)
        : m_leftDriveTalonA(leftDriveTalonA)
        , m_leftDriveTalonB(leftDriveTalonB)
        , m_leftDriveTalonC(leftDriveTalonC)
        , m_rightDriveTalonA(rightDriveTalonA)
        , m_rightDriveTalonB(rightDriveTalonB)
        , m_rightDriveTalonC(rightDriveTalonC)
        , m_leftOutput(0.0)
        , m_rightOutput(0.0)
        , m_throttle(0.0)
        , m_turn(0.0)
        , m_currentLimit(SupplyCurrentLimitConfiguration(true, 40, 50, 0.05))
        , m_statorLimit(StatorCurrentLimitConfiguration(true, 80, 100, 0.05))
        , m_isQuickTurn(false)
        , m_driveMode(DriveMode::arcade)
        , m_xPos(0.0)
        , m_yPos(0.0)
        , m_theta(0.0)
        , m_translation2D(m_xPos, m_yPos)
        , m_rotation2D(m_theta)
        , m_drivePose(m_translation2D, m_rotation2D)
        , m_driveWidth(23.75 * 0.254)
        , m_driveKinimatics(m_driveWidth)
        , m_driveChassisSpeeds()
        , m_driveWheelSpeeds()
        , m_driveOdometry(m_rotation2D, m_drivePose)
        , m_positionPID(0.0, 0.0, 0.0)
        , m_turnPID(0.0, 0.0, 0.0) {
    // Factory Default
    m_leftDriveTalonA->ConfigFactoryDefault();
    m_leftDriveTalonB->ConfigFactoryDefault();
    m_leftDriveTalonC->ConfigFactoryDefault();
    m_rightDriveTalonA->ConfigFactoryDefault();
    m_rightDriveTalonB->ConfigFactoryDefault();
    m_rightDriveTalonC->ConfigFactoryDefault();

    // Neutral Mode
    m_leftDriveTalonA->SetNeutralMode(Coast);
    m_leftDriveTalonB->SetNeutralMode(Coast);
    m_leftDriveTalonC->SetNeutralMode(Coast);
    m_rightDriveTalonA->SetNeutralMode(Coast);
    m_rightDriveTalonB->SetNeutralMode(Coast);
    m_rightDriveTalonC->SetNeutralMode(Coast);

    // Motor Directions
    m_leftDriveTalonA->SetInverted(TalonFXInvertType::Clockwise);
    m_leftDriveTalonB->SetInverted(TalonFXInvertType::Clockwise);
    m_leftDriveTalonC->SetInverted(TalonFXInvertType::Clockwise);
    m_rightDriveTalonA->SetInverted(TalonFXInvertType::CounterClockwise);
    m_rightDriveTalonB->SetInverted(TalonFXInvertType::CounterClockwise);
    m_rightDriveTalonC->SetInverted(TalonFXInvertType::CounterClockwise);

    // Current Limits
    m_leftDriveTalonA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_leftDriveTalonB->ConfigSupplyCurrentLimit(m_currentLimit);
    m_leftDriveTalonC->ConfigSupplyCurrentLimit(m_currentLimit);
    m_leftDriveTalonA->ConfigStatorCurrentLimit(m_statorLimit);
    m_leftDriveTalonB->ConfigStatorCurrentLimit(m_statorLimit);
    m_leftDriveTalonC->ConfigStatorCurrentLimit(m_statorLimit);

    m_rightDriveTalonA->ConfigSupplyCurrentLimit(m_currentLimit);
    m_rightDriveTalonB->ConfigSupplyCurrentLimit(m_currentLimit);
    m_rightDriveTalonC->ConfigSupplyCurrentLimit(m_currentLimit);
    m_rightDriveTalonA->ConfigStatorCurrentLimit(m_statorLimit);
    m_rightDriveTalonB->ConfigStatorCurrentLimit(m_statorLimit);
    m_rightDriveTalonC->ConfigStatorCurrentLimit(m_statorLimit);

    // Deadband
    m_leftDriveTalonA->ConfigNeutralDeadband(0.01);
    m_leftDriveTalonB->ConfigNeutralDeadband(0.01);
    m_leftDriveTalonC->ConfigNeutralDeadband(0.01);

    m_rightDriveTalonA->ConfigNeutralDeadband(0.01);
    m_rightDriveTalonB->ConfigNeutralDeadband(0.01);
    m_rightDriveTalonC->ConfigNeutralDeadband(0.01);

    // Set motors to follow A
    m_leftDriveTalonB->Follow(*m_leftDriveTalonA);
    m_leftDriveTalonC->Follow(*m_leftDriveTalonA);

    m_rightDriveTalonB->Follow(*m_rightDriveTalonA);
    m_rightDriveTalonC->Follow(*m_rightDriveTalonA);

    // Ramp Output
    m_leftDriveTalonA->ConfigClosedloopRamp(0.0);
    m_rightDriveTalonA->ConfigClosedloopRamp(0.0);

    // Voltage Compensation
    m_leftDriveTalonA->ConfigVoltageCompSaturation(12.0);
    m_rightDriveTalonA->ConfigVoltageCompSaturation(12.0);

    // Closed loop
    m_leftDriveTalonA->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);
    m_rightDriveTalonA->ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, 0, 30);

    m_leftDriveTalonA->Config_kP(0, 0.25, 30);
    m_leftDriveTalonA->Config_kI(0, 0.0, 30);
    m_leftDriveTalonA->Config_kD(0, 0.0, 30);
    m_leftDriveTalonA->Config_kF(0, 0.033, 30);

    m_rightDriveTalonA->Config_kP(0, 0.25, 30);
    m_rightDriveTalonA->Config_kI(0, 0.0, 30);
    m_rightDriveTalonA->Config_kD(0, 0.0, 30);
    m_rightDriveTalonA->Config_kF(0, 0.033, 30);
}

void Drive::Update() {
    switch (m_driveMode) {
        case DriveMode::arcade:
            ArcadeCalcOutput();
            break;
        case DriveMode::cheesy:
            CheesyCalcOutput();
            break;
        case DriveMode::position:
            PositionCalcOutput();
            break;
        default:
            break;
    }

    // m_leftDriveTalonA->Set(ControlMode::Velocity, (m_leftOutput * MAX_TICKS_PER_100_MS));
    // m_rightDriveTalonA->Set(ControlMode::Velocity, (m_rightOutput * MAX_TICKS_PER_100_MS));

    m_leftDriveTalonA->Set(ControlMode::PercentOutput, (m_leftOutput));
    m_rightDriveTalonA->Set(ControlMode::PercentOutput, (m_rightOutput));
}

void Drive::DashboardUpdate() {
    frc::SmartDashboard::PutNumber("D turn", m_turn);
    frc::SmartDashboard::PutNumber("D throttle", m_throttle);
    frc::SmartDashboard::PutNumber("D leftOutput", m_leftOutput);
    frc::SmartDashboard::PutNumber("D rightOutput", m_rightOutput);
    frc::SmartDashboard::PutNumber("D left supply current",
                                   (m_leftDriveTalonA->GetSupplyCurrent() + m_leftDriveTalonB->GetSupplyCurrent() +
                                    m_leftDriveTalonC->GetSupplyCurrent()) /
                                       3.0);
    frc::SmartDashboard::PutNumber("D Right supply current",
                                   (m_rightDriveTalonA->GetSupplyCurrent() + m_rightDriveTalonB->GetSupplyCurrent() +
                                    m_rightDriveTalonC->GetSupplyCurrent()) /
                                       3.0);
    frc::SmartDashboard::PutNumber("D left stator current",
                                   (m_leftDriveTalonA->GetStatorCurrent() + m_leftDriveTalonB->GetStatorCurrent() +
                                    m_leftDriveTalonC->GetStatorCurrent()) /
                                       3.0);
    frc::SmartDashboard::PutNumber("D right stator current",
                                   (m_rightDriveTalonA->GetStatorCurrent() + m_rightDriveTalonB->GetStatorCurrent() +
                                    m_rightDriveTalonC->GetStatorCurrent()) /
                                       3.0);
    frc::SmartDashboard::PutNumber(
        "D velocity",
        (m_leftDriveTalonA->GetSelectedSensorVelocity() + m_rightDriveTalonA->GetSelectedSensorVelocity()) / 2.0);
}

void Drive::ArcadeCalcOutput() {
    m_throttle = std::clamp(m_throttle, -1.0, 1.0);
    m_turn = std::clamp(m_turn, -1.0, 1.0);
    m_turn *= 1.2;
    if (!m_isQuickTurn) {
        m_turn *= std::abs(m_throttle);
    }

    double maxInput = std::copysign(std::max(std::abs(m_throttle), std::abs(m_turn)), m_throttle);
    if (m_throttle >= 0.0) {
        if (m_turn >= 0.0) {
            // Quadrant 1
            m_leftOutput = maxInput;
            m_rightOutput = m_throttle - m_turn;
        } else {
            // Quadrant 2
            m_leftOutput = m_throttle + m_turn;
            m_rightOutput = maxInput;
        }
    } else {
        if (m_turn >= 0.0) {
            // Quadrant 4
            m_rightOutput = maxInput;
            m_leftOutput = m_throttle + m_turn;
        } else {
            // Quadrant 3
            m_rightOutput = m_throttle - m_turn;
            m_leftOutput = maxInput;
        }
    }
}

void Drive::CheesyCalcOutput() {
    // NEEDS VERIFICATION! TODO
    double throttle = Util::deadband(m_throttle, 0.04);
    double wheel = Util::deadband(m_turn, 0.04);
    double kWheelGain = 0.05;
    double kWheelNonlinearity = 0.05;
    double denominator = sin(Constants::PI / 2.0 * kWheelNonlinearity);
    // Apply a sin function that's scaled to make it feel better.
    if (!m_isQuickTurn) {
        wheel = sin(Constants::PI / 2.0 * kWheelNonlinearity * wheel);
        wheel = sin(Constants::PI / 2.0 * kWheelNonlinearity * wheel);
        wheel = wheel / (denominator * denominator) * std::abs(throttle);
    }
    wheel *= kWheelGain;
    ChassisSpeeds driveChassisSpeed{units::meters_per_second_t(throttle * MAX_METERS_PER_SECOND), 0.0_mps,
                                    units::radians_per_second_t(wheel * MAX_RADIANS_PER_SECOND)};
    m_driveWheelSpeeds = m_driveKinimatics.ToWheelSpeeds(driveChassisSpeed);
    m_leftOutput = m_driveWheelSpeeds.left();
    m_rightOutput = m_driveWheelSpeeds.right();
}

void Drive::PositionCalcOutput() {
    m_positionPID.SetTarget(m_targetPos);
    m_positionPID.SetTarget(m_targetAngle);
    m_currentPos =
        (m_leftDriveTalonA->GetSelectedSensorPosition() + m_rightDriveTalonA->GetSelectedSensorPosition()) / 2.0;
    if (abs((m_currentAngle - m_targetAngle)) > 1.0) {
        SetThrottleTurn(0.0, m_turnPID.CalcOutput(m_currentAngle));
    } else {
        SetThrottleTurn(m_positionPID.CalcOutput(m_currentPos), m_turnPID.CalcOutput(m_currentAngle));
    }
    SetQuickTurn(true);
    ArcadeCalcOutput();
}

void Drive::SetThrottleTurn(double throttle, double turn) {
    m_throttle = throttle;
    m_turn = turn;
}

void Drive::SetAngle(double angle) {
    m_currentAngle = angle;
}

void Drive::SetPosition(double position) {
    m_currentPos = position;
}

void Drive::SetQuickTurn(bool QT) {
    m_isQuickTurn = QT;
}

double Drive::GetRightOuput() {
    return m_rightOutput;
}

double Drive::GetLeftOuput() {
    return m_leftOutput;
}

void Drive::ZeroDriveMotors() {
    m_leftDriveTalonA->SetSelectedSensorPosition(0.0, 0, 30);
    m_rightDriveTalonA->SetSelectedSensorPosition(0.0, 0, 30);
}

double Drive::GetVelocity() {
    double speed;
    speed = (m_leftDriveTalonA->GetSelectedSensorVelocity() + m_rightDriveTalonA->GetSelectedSensorVelocity()) / 2;
    return speed;
}

}  // namespace frc973
