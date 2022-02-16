#include "src/subsystems/AutoManager.h"

namespace frc973 {

AutoManager::AutoManager(Intake *intake, Shooter *shooter, Conveyor *conveyor, Gyro *gyro)
        : m_currentAuto(DoNothing)
        , m_intake(intake)
        , m_shooter(shooter)
        , m_conveyor(conveyor)
        , m_gyro(gyro)
        , m_autoName("Do Nothing")
        // clang-format off

/*< DoNothing >*/
, m_doNothing(AutoMode({}))

/*< Position 2, 2 Ball >*/
, m_p2_2Ball(AutoMode({}))

/*< Position 3, 2 Ball >*/
, m_p3_2Ball(AutoMode({}))

/*< Position 5, 2 Ball >*/
, m_p5_2Ball(AutoMode({}))

/*< Position 2, 3 Ball >*/
, m_p2_3Ball(AutoMode({}))

/*< Position 5, 4 Ball >*/
, m_p5_4Ball(AutoMode({}))

        // clang-format on
        , m_currentMode(m_doNothing)
        , m_autoIndex(1) {
}

void AutoManager::Update() {
    if (m_currentMode.IsCompleted()) {
        return;
    }

    m_currentMode.Run();
}

void AutoManager::DashboardUpdate() {
    switch (m_currentAuto) {
        case DoNothing:
            m_autoName = "Do Nothing";
            break;
        case P2_2Ball:
            m_autoName = "Position 2, 2 Ball";
            break;
        case P3_2Ball:
            m_autoName = "Position 3, 2 Ball";
            break;
        case P5_2Ball:
            m_autoName = "Position 5, 2 Ball";
            break;
        case P2_3Ball:
            m_autoName = "Position 2, 3 Ball";
            break;
        case P5_4Ball:
            m_autoName = "Position 5, 4 Ball";
            break;
    }

    frc::SmartDashboard::PutString(
        "Auto Info", "Mode: " + m_autoName + " Index: " + std::to_string(m_currentMode.GetCurrentCommandIndex()));
    frc::SmartDashboard::PutString("DB/String 0", "Mode: " + m_autoName);
}

void AutoManager::UpdateAutoMode() {
    switch (m_currentAuto) {
        case DoNothing:
            m_currentMode = m_doNothing;
            break;
        case P2_2Ball:
            m_currentMode = m_p2_2Ball;
            break;
        case P3_2Ball:
            m_currentMode = m_p3_2Ball;
            break;
        case P5_2Ball:
            m_currentMode = m_p5_2Ball;
            break;
        case P2_3Ball:
            m_currentMode = m_p2_3Ball;
            break;
        case P5_4Ball:
            m_currentMode = m_p5_4Ball;
            break;
    }
}

void AutoManager::IndexAutoMode(bool next) {
    if (next) {
        m_autoIndex += 1;
    }
    else {
        m_autoIndex -= 1;
    }

    if (m_autoIndex == -1) {
        m_autoIndex = 7;    // amount of autos we have +1
    }

    if (m_autoIndex == 8) { //amount of autos we have +2
        m_autoIndex = 0;
    }

    m_currentAuto = AutoName(m_autoIndex);
    UpdateAutoMode();
}
}