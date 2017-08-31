#include <iostream>
#include "SLScanner/DeterministicFiniteAutomaton.hpp"

Silly::DeterministicFiniteAutomaton::State
Silly::DeterministicFiniteAutomaton::transite(Silly::DeterministicFiniteAutomaton::Alphabet input) {
    if (isFinished) {
        reboot();
        isFinished = false;
    }
    if (alphabets.find(input) != alphabets.end() && transitions.find(Move(currentState, input)) != transitions.end()) {
        State nextState = transitions[Move(currentState, input)];
        currentState = nextState;
        currentAlphabet = input;
        return nextState;
    } else {
        currentState = TrapState;
        return TrapState;
    }
}

Silly::DeterministicFiniteAutomaton::State Silly::DeterministicFiniteAutomaton::match(std::string str) {
    int i;
    for (i = 0; str[i] != 0; ++i)
        transite(str[i]);
    isFinished = true;
    return currentState;
}

Silly::DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(Silly::DeterministicFiniteAutomaton::StateSet states_,
                                                                  Silly::DeterministicFiniteAutomaton::TransitionSet transitions_,
                                                                  Silly::DeterministicFiniteAutomaton::AlphabetSet alphabets_,
                                                                  Silly::DeterministicFiniteAutomaton::StateSet acceptingStates_) {
    states = states_;
    transitions = transitions_;
    alphabets = alphabets_;
    acceptingStates = acceptingStates_;
    for (Alphabet a : alphabets) {
        transitions[Move(TrapState, a)] = TrapState;
    }
    currentState = StartState;
    currentAlphabet = EmptyAlphabet;
    isFinished = false;
}

Silly::DeterministicFiniteAutomaton::StateType Silly::DeterministicFiniteAutomaton::operator()(std::string str) {
    return checkState(match(str));
}