//
// Created by 陈润泽 on 2017/8/11.
//

#include "SLScanner/FiniteAutomaton.h"


void Silly::FiniteAutomaton::reboot() {
    currentState = StartState;
    currentAlphabet = EmptyAlphabet;
}

Silly::FiniteAutomaton::StateType Silly::FiniteAutomaton::checkState(Silly::FiniteAutomaton::State state) const {
    if (acceptingStates.find(state) != acceptingStates.end()) return Accepted;
    else if (state == -1) return Trapped;
    else return NotAccepted;
}