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

        // clang-format on
        , m_currentMode(m_doNothing)
        , m_autoIndex(0) {
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
        m_autoIndex = 8;    // amount of autos we have -1
    }

    if (m_autoIndex == 9) { //amount of autos we have -1 +1
        m_autoIndex = 0;
    }

    m_currentAuto = AutoName(m_autoIndex);
    UpdateAutoMode();
}
}