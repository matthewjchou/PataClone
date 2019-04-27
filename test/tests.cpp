#include "catch.hpp"
#include "../include/patapon.hpp"

using namespace patapongame;

Patapon patapon = Patapon();

TEST_CASE("CalculateScoreScalar") {
    SECTION("Max multiplier") {
        REQUIRE(patapon.kMaxPointMultiplier == patapon.calculateScoreScalar(0));
        REQUIRE(patapon.kMaxPointMultiplier == patapon.calculateScoreScalar(100 * 4));
        REQUIRE(patapon.kMaxPointMultiplier == patapon.calculateScoreScalar(200 * 4));
    }

    SECTION("No multiplier") {
        REQUIRE(0 == patapon.calculateScoreScalar(425 * 4));
        REQUIRE(0 == patapon.calculateScoreScalar(499 * 4));
    }

    SECTION("Regular multiplier") {
        REQUIRE(1 == patapon.calculateScoreScalar(201 * 4));
        REQUIRE(1 == patapon.calculateScoreScalar(350 * 4));
        REQUIRE(1 == patapon.calculateScoreScalar(400 * 4));
        REQUIRE(1 == patapon.calculateScoreScalar(424 * 4));
    }
}

TEST_CASE("CalculateTempoFeedback") {
    patapon.can_play_ = true;
    
    SECTION("Perfect") {
        REQUIRE(Feedback::PERFECT == patapon.calculateTempoFeedback(0));
        REQUIRE(Feedback::PERFECT == patapon.calculateTempoFeedback(100));
        REQUIRE(Feedback::PERFECT == patapon.calculateTempoFeedback(200));
    }

    SECTION("Good") {
        REQUIRE(Feedback::GOOD == patapon.calculateTempoFeedback(201));
        REQUIRE(Feedback::GOOD == patapon.calculateTempoFeedback(300));
        REQUIRE(Feedback::GOOD == patapon.calculateTempoFeedback(424));
        REQUIRE(Feedback::GOOD == patapon.calculateTempoFeedback(500));
        REQUIRE(Feedback::GOOD == patapon.calculateTempoFeedback(550));
    }

    SECTION("Poor") {
        REQUIRE(Feedback::POOR == patapon.calculateTempoFeedback(425));
        REQUIRE(Feedback::POOR == patapon.calculateTempoFeedback(457));
        REQUIRE(Feedback::POOR == patapon.calculateTempoFeedback(499));
    }
}

TEST_CASE("Commands") {
    std::vector<Drum> combo;
    combo.clear();

    SECTION("MOVE") {
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PON);
        REQUIRE(Command::MOVE == patapon.determineCommand(combo));
    }

    SECTION("ATTACK") {
        combo.push_back(Drum::PON);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PON);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PON);
        REQUIRE(Command::ATTACK == patapon.determineCommand(combo));
    }

    SECTION("DEFEND") {
        combo.push_back(Drum::CHAKA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::CHAKA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PON);
        REQUIRE(Command::DEFEND == patapon.determineCommand(combo));
    }

    SECTION("CHARGE") {
        combo.push_back(Drum::PON);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PON);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::CHAKA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::CHAKA);
        REQUIRE(Command::CHARGE == patapon.determineCommand(combo));
    }

    SECTION("DANCE") {
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::PON);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::DON);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::CHAKA);
        REQUIRE(Command::DANCE == patapon.determineCommand(combo));
    }

    SECTION("FAIL") {
        combo.push_back(Drum::PATA);
        REQUIRE(Command::NOTHING == patapon.determineCommand(combo));
        combo.push_back(Drum::CHAKA);
        REQUIRE(Command::FAIL == patapon.determineCommand(combo));
    }
}
