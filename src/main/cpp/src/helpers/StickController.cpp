#include "lib/helpers/StickController.h"

namespace frc973 {
StickController::StickController(int port) : XboxController(port), m_port(port) {
    m_type = GetType();
}

bool StickController::IsPoofsStick() const {
    return m_type == 20;  // frc::GenericHID::HIDType::kHIDJoystick; Used to work, fix to 20
}

float StickController::GetRawAxisWithDeadband(int axis, bool fSquared, double threshold) const {
    if (IsPoofsStick()) {  // Poofs remap
        axis = ReMapAxisToStick(axis);
    }

    float value = Util::deadband(GetRawAxis(axis), threshold);

    if (fSquared) {
        value = Util::signSquare(value);
    }

    return value * GetRealValueSign(axis);  // -Y axis of xbox, but not X for example
}

bool StickController::GetRawButton(int button) {
    if (IsPoofsStick()) {
        switch (button) {
            case Stick::LeftTriggerAxis:
                return LeftTriggerAxis();
            case Stick::RightTriggerAxis:
                return RightTriggerAxis();
        }
    }

    return GenericHID::GetRawButton(button);
}

bool StickController::GetRawButtonReleased(int button) {
    if (IsPoofsStick()) {
        switch (button) {
            case Stick::LeftTriggerAxis:
                return LeftTriggerAxis();
            case Stick::RightTriggerAxis:
                return RightTriggerAxis();
        }
    }

    return GenericHID::GetRawButtonReleased(button);
}

bool StickController::LeftTriggerAxis() {
    return GetRawAxis(Stick::LeftTriggerAxis) > 0.5;
}

bool StickController::RightTriggerAxis() {
    return GetRawAxis(Stick::RightTriggerAxis) > 0.5;
}

bool StickController::GetDPadUpVirtButton() {
    if (IsPoofsStick()) {
        return false;
    }

    int pov = GetPOV();
    bool pressed = pov == 0 || pov == 315 || pov == 45;

    return pressed;
}

bool StickController::GetDPadDownVirtButton() {
    if (IsPoofsStick()) {
        return false;
    }

    int pov = GetPOV();
    bool pressed = pov == 180 || pov == 225 || pov == 135;

    return pressed;
}

bool StickController::GetDPadLeftVirtButton() {
    if (IsPoofsStick()) {
        return false;
    }

    int pov = GetPOV();
    bool pressed = pov == 270 || pov == 315 || pov == 225;

    return pressed;
}

bool StickController::GetDPadRightVirtButton() {
    if (IsPoofsStick()) {
        return false;
    }

    int pov = GetPOV();
    bool pressed = pov == 90 || pov == 135 || pov == 45;

    return pressed;
}

int StickController::ReMapAxisToStick(int axis) const {
    switch (axis) {
        case Stick::RightXAxis:
            axis = Stick::PoofsRightXAxis;
            break;
        case Stick::RightYAxis:
            axis = Stick::PoofsRightYAxis;
            break;
    }

    return axis;
}

float StickController::GetRealValueSign(int axis) const {
    float sign = 1.0;

    switch (axis) {
        case Stick::LeftYAxis:
            sign = -1.0;
            break;
        case Stick::RightYAxis:
            sign = -1.0;
            break;
    }

    return sign;
}
}  // namespace frc973
