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
