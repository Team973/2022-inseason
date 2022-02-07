#include "src/auto/commands/ConcurrentCommand.h"

namespace frc973 {
ConcurrentCommand::ConcurrentCommand(std::vector<Command*> cmdList) : m_cmdList(cmdList), m_allDone(true) {
}

void ConcurrentCommand::Init() {
    for (Command* cmd : m_cmdList) {
        cmd->Init();
    }
}

void ConcurrentCommand::Run() {
    m_allDone = true;  // assume all will concurently complete in this periodic.

    for (Command* cmd : m_cmdList) {
        cmd->Run();

        if (cmd->IsCompleted()) {
            continue;
        }

        m_allDone = false;  // need another periodic to complete.
    }
}

bool ConcurrentCommand::IsCompleted() {
    return m_allDone;
}

void ConcurrentCommand::PostExecute() {
    for (Command* cmd : m_cmdList) {
        cmd->PostExecute();
    }
}
}