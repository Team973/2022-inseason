#include "src/subsystems/Drive.h"

namespace frc973{

void Drive::Update() {


    switch (m_driveMode) {
        case DriveMode::arcade:

            break;
        case DriveMode::position:
           
            break;
        case DriveMode::cheesyDrive:
           
            break;
        default:

    }
}

void Drive::DashboardUpdate() {

}

double GetLeftPosition() {

}

double GetRightPosition() {

}

double GetPos() {

}

void Zero() {

}

double GetLeftRate() {

}

double GetRightRate() {

}

double GetRate() {

}

double GetAngularRate() {

}



void Drive::SetPositionTarget(double linearPositionTarget, double anglePositionTarget) {
    switch (m_driveMode) {
        case DriveMode::arcade:
            break;
        case DriveMode::position:
            break;
        default:
            break;
    }
}

void SetDrivePositionInches(double inches) {

}

void SetPercentOutput(double leftOutput, double rightOutput) {

}

void SetVelocity(double leftOutput, double rightOutput) {

}

void Drive::EnableBrakeMode() {

}

void Drive::EnableCoastMode() {

}

void SetThrottleAndTurn(const double throttle, const double turn) {

}

void Drive::SetDriveMode(DriveMode mode) {
    if (m_driveMode != mode) {
        m_driveMode = mode;
    }
}

bool OnTarget() {

}

void SetQuickTurn(bool state) {

}

void SetHighGear(bool state) {

}

bool LimelightOnTargetWithinTolerance(double tolerance) {

}

void Drive::CheckForIsNaN() {

}

void ClampSpeed(double minSpeed, double maxSpeed) {

}

bool IsLimelightDead() {

}



} //namespace frc973 
