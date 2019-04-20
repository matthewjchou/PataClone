#include "catch.hpp"
#include "../include/ofApp.h"
#include "../../../libs/openFrameworks/ofMain.h"

patapon::PataponGame game = patapon::PataponGame();

TEST_CASE("CalculateScoreScalar") {
    SECTION("Max multiplier") {
        REQUIRE(patapon::kMaxPointMultiplier, game.calculateScoreScalar(100, 200));
    }

    SECTION("No multiplier") {
        REQUIRE(0, game.calculateScoreScalar(100, 700));
    }

    SECTION("Too early, no multiplier") {
        REQUIRE(0, game.calculateScoreScalar(600, 599));
    }

    SECTION("Regular multiplier") {
        REQUIRE(1, game.calculateScoreScalar(300, 400));
    }
}
