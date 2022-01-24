#pragma once

#include <math.h>
#include <frc/XboxController.h>
#include <frc/DriverStation.h>

#include "lib/util/Util.h"

namespace frc973 {
namespace Stick {
// XBox HIDType = 1.0
const unsigned int BtnA = 1; /**< Button A. */
const unsigned int BtnB = 2; /**< Button B. */
const unsigned int BtnX = 3; /**< Button X. */
const unsigned int BtnY = 4; /**< Button Y. */

const unsigned int LeftBumper = 5;  /**< Left Bumper Button. */
const unsigned int RightBumper = 6; /**< Right Bumper Button. */

const unsigned int Back = 7;  /**< Back Button. */
const unsigned int Start = 8; /**< Start Button. */

const unsigned int LJoystickBtn = 9;  /**< Left Joystick Button. */
const unsigned int RJoystickBtn = 10; /**< Right Joystick Button. */

const unsigned int DPadUpVirtBtn = 11;    /**< DPad Up Button. */
const unsigned int DPadDownVirtBtn = 12;  /**< DPad Down Button. */
const unsigned int DPadLeftVirtBtn = 13;  /**< DPad Left Button. */
const unsigned int DPadRightVirtBtn = 14; /**< DPad Right Button. */

const unsigned int LeftXAxis = 0;        /**< Left Joystick X Axis ID. */
const unsigned int LeftYAxis = 1;        /**< Left Joystick Y Axis ID. */
const unsigned int LeftTriggerAxis = 2;  /**< Left Trigger Button Axis ID. */
const unsigned int RightTriggerAxis = 3; /**< Right Trigger Button Axis ID. */
const unsigned int RightXAxis = 4;       /**< Right Joystick X Axis ID. */
const unsigned int RightYAxis = 5;       /**< Right Joystick Y Axis ID. */

// Poofs ... HIDType = 20.0
const unsigned int PoofsRightXAxis = 2; /**< Right X Axis ID. */
const unsigned int PoofsRightYAxis = 3; /**< Right Y Axis ID. */

const unsigned int LeftTrigger = 7;  /**< Left Trigger. */
const unsigned int RightTrigger = 8; /**< Left Trigger. */
}  // namespace Stick

/**
 * This class provides a unified joystick wrapper with helper methods for button pressed checks as well as buttons being
 * released. Also lets you use a joystick axis as a button in an easy way. Lastly it handles deadband in axis checks and
 * the consistent sign of the value from a given axis. Currently we handle custom sticks, xbox, 3rd party, and dual
 * action sticks. Up + Down - Left - Right +
 */
class StickController : public frc::XboxController {
public:
    /**
     * Create an instance of a StickController object. Requires the port information to instantiate the underlying
     * WPI-Joystick,
     * @param port The joystick port.
     */
    StickController(int port);

    /**
     * Tests if the controller used is a poof stick (joystick).
     */
    bool IsPoofsStick() const;

    /**
     * Get the value of the given axis with deadband.
     * @param axis Specifies the axis to get the value of.
     * @param fSquared Specifies whether the joystick input should be squared.
     * @param threshold Specifies the deadband threshold.
     */
    float GetRawAxisWithDeadband(int axis, bool fSquared = false, double threshold = DEADBAND_INPUT_THRESHOLD) const;

    /**
     * Returns the state of the button, true for pressed and false for not pressed.
     * @param button The button you want to know the state of (ex. Stick::BtnA).
     * @return true for pressed.
     */
    bool GetRawButton(int button);

    /**
     * Returns the state of the button, true for released and false for pressed.
     * @param button The button you want to know the state of (ex. Stick::BtnX).
     * @return true for released.
     */
    bool GetRawButtonReleased(int button);

    /**
     * Test the left trigger as a button.
     * @return true if the trigger is depressed.
     */
    bool LeftTriggerAxis();

    /**
     * Test the right trigger as a button.
     * @return true if the trigger is depressed.
     */
    bool RightTriggerAxis();

    /**
     *  DPad Up Virtual button.
     * @return Whether the DPad's up button is pressed.
     */
    bool GetDPadUpVirtButton();

    /**
     *  DPad Down Virtual button.
     * @return Whether the DPad's down button is pressed.
     */
    bool GetDPadDownVirtButton();

    /**
     * DPad Leftt Virtual button.
     * @return Whether the DPad's left button is pressed.
     */
    bool GetDPadLeftVirtButton();

    /**
     * DPad Right Virtual button.
     * @return Whether the DPad's right button is pressed.
     */
    bool GetDPadRightVirtButton();

    /**
     * Sets the GenericHID type, overriding the constructor discovered type.
     * @param type the new type
     */
    void SetTypeTo(int type) {
        m_type = type;
    }

    /**
     * Returns the discovered GenericHID type.
     * @return the type
     */
    int GetDiscoveredType() const {
        return m_type;
    }

    static constexpr double DEADBAND_INPUT_THRESHOLD = 0.05; /**< The deadband threshold on the joysticks. */

private:
    /**
     * Remaps a given axis to poofs.
     * @param axis The axis to remap.
     * @return The remapped axis.
     */
    int ReMapAxisToStick(int axis) const;

    /**
     * Flips axis signs.
     * @param axis Axis to swap signs for.
     * @return The new sign for that axis.
     */
    float GetRealValueSign(int axis) const;

    /**
     * Remaps a given button to poofs.
     * @param button The button to remap.
     * @return The remapped button.
     */
    int ReMapButtonToStick(int button) const;

    int m_port;
    int m_type; /**< The GenericHID type */
};

}  // namespace frc973
