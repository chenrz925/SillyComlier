#include <gtest/gtest.h>
#include <SLScanner/NondeterministicFiniteAutomaton.h>

using namespace Silly;

TEST(NondeterministicFiniteAutomaton, BaseFunctionTest) {
    NondeterministicFiniteAutomaton::StateSet testStates;
    NondeterministicFiniteAutomaton::TransitionSet testTransitions;
    NondeterministicFiniteAutomaton::ETransitionSet testETransitions;
    NondeterministicFiniteAutomaton::AlphabetSet testAlphabets = EnglishAlphabets;
    NondeterministicFiniteAutomaton::StateSet testAcceptingStates = {9};
    testTransitions[NondeterministicFiniteAutomaton::Move(0, 'a')] = 1;
    testTransitions[NondeterministicFiniteAutomaton::Move(4, 'b')] = 5;
    testTransitions[NondeterministicFiniteAutomaton::Move(6, 'c')] = 7;
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(1, 2));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(2, 3));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(2, 9));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(3, 4));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(3, 6));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(5, 8));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(7, 8));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(8, 3));
    testETransitions.insert(NondeterministicFiniteAutomaton::ETransition(8, 9));
    for (NondeterministicFiniteAutomaton::State s = 0; s <= 9; ++s)
        testStates.insert(s);
    NondeterministicFiniteAutomaton testAutomaton(testStates, testTransitions, testETransitions, testAlphabets, testAcceptingStates);
    EXPECT_EQ(testAutomaton.eClosure(1), NondeterministicFiniteAutomaton::StateSet({2, 3, 4, 6, 9}));
    EXPECT_EQ(testAutomaton.eClosure({0, 1, 5}), NondeterministicFiniteAutomaton::StateSet({2, 3, 4, 6, 8, 9}));
    EXPECT_EQ(testAutomaton.delta(0, 'a'), NondeterministicFiniteAutomaton::StateSet({1}));
    EXPECT_EQ(testAutomaton.delta(NondeterministicFiniteAutomaton::StateSet({4}), 'b'), NondeterministicFiniteAutomaton::StateSet({5}));
    EXPECT_EQ(testAutomaton.delta(6, 'c'), NondeterministicFiniteAutomaton::StateSet({7}));

}