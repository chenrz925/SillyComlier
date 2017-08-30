#include <queue>
#include <iostream>
#include "SLScanner/NondeterministicFiniteAutomaton.h"

Silly::NondeterministicFiniteAutomaton::NondeterministicFiniteAutomaton(StateSet states_, TransitionSet transitions_,
                                                                        ETransitionSet etransitions_,
                                                                        AlphabetSet alphabets_,
                                                                        StateSet acceptingStates_) {
    nStates = states_;
    nAlphabets = alphabets_;
    nTransitions = transitions_;
    nETransitions = etransitions_;
    nAcceptingStates = acceptingStates_;
    constructed = false;
    currentState = 1;
}

Silly::NondeterministicFiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::eClosure(State input) {
    std::queue<State> working;
    StateSet closure;
    closure.insert(input);
    working.push(input);
    while (!working.empty()) {
        State state = working.front();
        working.pop();
        for (auto it = nETransitions.find(state); it != nETransitions.end(); ++it) {
            if (it->first == state) {
                closure.insert(it->second);
                bool isNewState = false;
                for (auto fn = nETransitions.find(it->second); fn != nETransitions.end(); ++fn) {
                    if (fn->first == it->second && closure.find(fn->second) == closure.end()) {
                        isNewState = true;
                        break;
                    }
                }
                if (isNewState)
                    working.push(it->second);
            }
        }
    }
    return closure;
}

Silly::NondeterministicFiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::eClosure(StateSet inputs) {
    StateSet closure;
    for (auto it = inputs.begin(); it != inputs.end(); ++it) {
        StateSet output = eClosure(*it);
        closure.insert(output.begin(), output.end());
    }
    return closure;
}

Silly::FiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::delta(State inputState,
                                                                               Alphabet inputAlphabet) {
    StateSet target;
    if (nTransitions.find(Move(inputState, inputAlphabet)) != nTransitions.end())
        target.insert(nTransitions[Move(inputState, inputAlphabet)]);
    return target;
}

Silly::FiniteAutomaton::StateSet Silly::NondeterministicFiniteAutomaton::delta(StateSet inputStates,
                                                                               Alphabet inputAlphabet) {
    StateSet target;
    for (auto it = inputStates.begin(); it != inputStates.end(); ++it) {
        auto dt = delta(*it, inputAlphabet);
        target.insert(dt.begin(), dt.end());
    }
    return target;
}

void Silly::NondeterministicFiniteAutomaton::construct() {
    if (constructed)
        return;
    StateSet q0 = eClosure(StartState);
    std::set<StateSet> Q = {q0};
    std::queue<StateSet> working;
    working.push(q0);
    std::map<std::pair<StateSet, Alphabet>, StateSet> T;
    while (!working.empty()) {
        StateSet q = dynamic_cast<StateSet &&>(working.front());
        working.pop();
        for (auto it = nAlphabets.begin(); it != nAlphabets.end(); ++it) {
            auto t = eClosure(delta(q, *it));
            T[std::pair<StateSet, Alphabet>(q, *it)] = t;
            if (Q.find(t) == Q.end()) {
                Q.insert(t);
                working.push(t);
            }
        }
    }
    std::map<StateSet, State> stateMap;
    State st = 0;
    for (auto it = Q.begin(); it != Q.end(); ++it) {
        states.insert(st);
        stateMap[*it] = st++;
    }
    for (auto it = T.begin(); it != T.end(); ++it) {
        transitions[Move(stateMap[it->first.first], it->first.second)] = stateMap[it->second];
        //std::cout << "(" << stateMap[it->first.first] << ", " << it->first.second << ")->" << stateMap[it->second] << '\n';
    }
    for (auto it = Q.begin(); it != Q.end(); ++it) {
        bool isAccepting = false;
        for (auto si = it->begin(); si != it->end(); ++si) {
            if (nAcceptingStates.find(*si) != nAcceptingStates.end())
                isAccepting = true;
        }
        if (isAccepting) {
            acceptingStates.insert(stateMap[*it]);
        }
    }
    /**for (auto it = acceptingStates.begin(); it != acceptingStates.end(); ++it) {
        if (it == acceptingStates.begin())
            std::cout << *it;
        else std::cout << ", " << *it;
    }
    std::cout << "\n";*/
    alphabets = nAlphabets;
    constructed = true;
#if SL_GTEST_NO_CLEAN_NFA
#else
    nAlphabets.clear();
    nAcceptingStates.clear();
    nStates.clear();
    nTransitions.clear();
    nETransitions.clear();
#endif
}

Silly::FiniteAutomaton::State Silly::NondeterministicFiniteAutomaton::match(std::string str) {
    construct();
    reboot();
    return DeterministicFiniteAutomaton::match(str);
}

Silly::FiniteAutomaton::StateType Silly::NondeterministicFiniteAutomaton::operator()(std::string str) {
    return checkState(NondeterministicFiniteAutomaton::match(str));
}

void Silly::NondeterministicFiniteAutomaton::reboot() {
    currentAlphabet = EmptyAlphabet;
    currentState = 1;
    isFinished = false;
}