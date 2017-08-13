#include <gtest/gtest.h>
#include "SLScanner/DeterministicFiniteAutomaton.h"

using namespace Silly;

TEST(DeterministicFiniteAutomaton, SimpleTest) {
    DeterministicFiniteAutomaton::StateSet testStates;
    DeterministicFiniteAutomaton::AlphabetSet testAlphabets;
    DeterministicFiniteAutomaton::StateSet testAcceptingStates = {1, 2, 3, 4, 5, 6};
    DeterministicFiniteAutomaton::TransitionSet testTransitions;
    for (DeterministicFiniteAutomaton::State state = 0; state <= 6; ++state)
        testStates.insert(state);
    for (DeterministicFiniteAutomaton::Alphabet alphabet = '0'; alphabet <= '9'; ++alphabet) {
        testAlphabets.insert(alphabet);
        testTransitions[DeterministicFiniteAutomaton::Move(1, alphabet)] = 2;
        testTransitions[DeterministicFiniteAutomaton::Move(2, alphabet)] = 3;
        testTransitions[DeterministicFiniteAutomaton::Move(3, alphabet)] = 4;
        testTransitions[DeterministicFiniteAutomaton::Move(4, alphabet)] = 5;
        testTransitions[DeterministicFiniteAutomaton::Move(5, alphabet)] = 6;
    }
    for (DeterministicFiniteAutomaton::Alphabet alphabet = 'A'; alphabet <= 'Z'; ++alphabet) {
        testAlphabets.insert(alphabet);
        testTransitions[DeterministicFiniteAutomaton::Move(0, alphabet)] = 1;
    }
    for (DeterministicFiniteAutomaton::Alphabet alphabet = 'a'; alphabet <= 'z'; ++alphabet) {
        testAlphabets.insert(alphabet);
        testTransitions[DeterministicFiniteAutomaton::Move(0, alphabet)] = 1;
    }
    DeterministicFiniteAutomaton testAutomaton(testStates, testTransitions, testAlphabets, testAcceptingStates);
    EXPECT_EQ(testAutomaton("A12345"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("A"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("Z3910"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("Z99999"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("Z9999D"), testAutomaton.Trapped);
    EXPECT_EQ(testAutomaton(""), testAutomaton.Trapped);
    EXPECT_EQ(testAutomaton("3232"), testAutomaton.Trapped);
}

TEST(DeterministicFiniteAutomaton, FloatNumberTest) {
    DeterministicFiniteAutomaton::AlphabetSet testAlphabets = NumberAlphabets;
    DeterministicFiniteAutomaton::StateSet testStates;
    for (DeterministicFiniteAutomaton::State state = 0; state <= 9; ++state)
        testStates.insert(state);
    DeterministicFiniteAutomaton::StateSet testAcceptingStates = {2, 4, 7, 9};
    DeterministicFiniteAutomaton::TransitionSet testTransitions;
    testTransitions[DeterministicFiniteAutomaton::Move(0, '+')] = 1;
    testTransitions[DeterministicFiniteAutomaton::Move(0, '-')] = 1;
    testTransitions[DeterministicFiniteAutomaton::Move(0, '.')] = 3;
    testTransitions[DeterministicFiniteAutomaton::Move(2, '.')] = 3;
    testTransitions[DeterministicFiniteAutomaton::Move(4, 'e')] = 5;
    testTransitions[DeterministicFiniteAutomaton::Move(4, 'E')] = 5;
    testTransitions[DeterministicFiniteAutomaton::Move(2, 'e')] = 5;
    testTransitions[DeterministicFiniteAutomaton::Move(2, 'E')] = 5;
    testTransitions[DeterministicFiniteAutomaton::Move(5, '+')] = 6;
    testTransitions[DeterministicFiniteAutomaton::Move(5, '-')] = 6;
    testTransitions[DeterministicFiniteAutomaton::Move(5, '.')] = 8;
    testTransitions[DeterministicFiniteAutomaton::Move(7, '.')] = 8;
    for (DeterministicFiniteAutomaton::Alphabet alphabet = '0'; alphabet <= '9'; ++alphabet) {
        testTransitions[DeterministicFiniteAutomaton::Move(0, alphabet)] = 2;
        testTransitions[DeterministicFiniteAutomaton::Move(1, alphabet)] = 2;
        testTransitions[DeterministicFiniteAutomaton::Move(2, alphabet)] = 2;
        testTransitions[DeterministicFiniteAutomaton::Move(3, alphabet)] = 4;
        testTransitions[DeterministicFiniteAutomaton::Move(4, alphabet)] = 4;
        testTransitions[DeterministicFiniteAutomaton::Move(5, alphabet)] = 7;
        testTransitions[DeterministicFiniteAutomaton::Move(6, alphabet)] = 7;
        testTransitions[DeterministicFiniteAutomaton::Move(7, alphabet)] = 7;
        testTransitions[DeterministicFiniteAutomaton::Move(8, alphabet)] = 9;
        testTransitions[DeterministicFiniteAutomaton::Move(9, alphabet)] = 9;
    }
    DeterministicFiniteAutomaton testAutomaton(testStates, testTransitions, testAlphabets, testAcceptingStates);
    EXPECT_EQ(testAutomaton("0.13423231"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("0.1342E+213.4"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("+13"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("+13e-19"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("+13e-19"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton(".234144"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("32423eee3242"), testAutomaton.Trapped);
    EXPECT_EQ(testAutomaton(".234122.21310012."), testAutomaton.Trapped);
    EXPECT_EQ(testAutomaton(".234E"), testAutomaton.NotAccepted);
}

TEST(DeterministicFiniteAutomaton, CamelCaseTest) {
    DeterministicFiniteAutomaton::AlphabetSet testAlphabets = EnglishAlphabets;
    DeterministicFiniteAutomaton::StateSet testStates = {0, 1, 2};
    DeterministicFiniteAutomaton::StateSet testAcceptingStates = {2};
    DeterministicFiniteAutomaton::TransitionSet testTransitions;
    for (DeterministicFiniteAutomaton::Alphabet upper = 'A', lower = 'a'; upper <= 'Z' && lower <= 'z'; ++upper, ++lower) {
        testTransitions[DeterministicFiniteAutomaton::Move(0, upper)] = 1;
        testTransitions[DeterministicFiniteAutomaton::Move(1, lower)] = 2;
        testTransitions[DeterministicFiniteAutomaton::Move(2, lower)] = 2;
        testTransitions[DeterministicFiniteAutomaton::Move(2, upper)] = 1;
    }
    DeterministicFiniteAutomaton testAutomaton(testStates, testTransitions, testAlphabets, testAcceptingStates);
    EXPECT_EQ(testAutomaton("HelloWorld"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("GoodBoy"), testAutomaton.Accepted);
    EXPECT_EQ(testAutomaton("GoodB"), testAutomaton.NotAccepted);
    EXPECT_EQ(testAutomaton("GoodB8"), testAutomaton.Trapped);
}