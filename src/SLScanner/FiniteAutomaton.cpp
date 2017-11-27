#include "SLScanner/FiniteAutomaton.hpp"


void Silly::FiniteAutomaton::reboot() {
    currentState = StartState;
    currentAlphabet = EmptyAlphabet;
    offset = 0;
}

Silly::FiniteAutomaton::StateType Silly::FiniteAutomaton::checkState(Silly::FiniteAutomaton::State state) const {
    if (acceptingStates.find(state) != acceptingStates.end()) {return Accepted;}
    else if (state == -1) return Trapped;
    else return NotAccepted;
}