#include <string>
#include <vector>    
#include <array>
#include <map>
#include <iostream>

namespace patapongame {    
    enum class Drum {
        PATA,
        PON,
        CHAKA,
        DON 
    };

    enum class Feedback {
        PERFECT,
        GOOD,
        POOR
    };

    enum class Command {
        ATTACK,
        DEFEND,
        MOVE,
        CHARGE,
        JUMP,
        RUNAWAY,
        DANCE,
        NOTHING,
        FAIL
    };

    class Patapon {
        const std::array<Drum, 4> kMoveCommand = 
            {Drum::PATA, Drum::PATA, Drum::PATA, Drum::PON};
        const std::array<Drum, 4> kAttackCommand = 
            {Drum::PON, Drum::PON, Drum::PATA, Drum::PON};
        const std::array<Drum, 4> kDefendCommand = 
            {{Drum::CHAKA, Drum::CHAKA, Drum::PATA, Drum::PON}};
        const std::array<Drum, 4> kChargeCommand = 
            {{Drum::PON, Drum::PON, Drum::CHAKA, Drum::CHAKA}};

        std::vector<Drum> combo_;

        friend class Game;
    public:
        const double kMaxPointTime = 200;
        const double kEarlyPointTime = 500;
        const double kNoPointTime = 425;
        const size_t kMaxPointMultiplier = 2;
        const size_t kNormalPointMultiplier = 1;

        const std::string kChaka = "CHAKA";
        const std::string kPata = "PATA";
        const std::string kPon = "PON";
        const std::string kDon = "DON";   

        std::string tempConvert(Drum d) {
            if (d == Drum::CHAKA) return kChaka;
            if (d == Drum::PATA) return kPata;
            if (d == Drum::PON) return kPon;
            if (d == Drum::DON) return kDon;

            return "";
        }

        std::string tempConvertCommand(Command c) {
            if (c == Command::ATTACK) return "ATTACK";  
            if (c == Command::DEFEND) return "DEFEND";
            if (c == Command::MOVE) return "MOVE";
            if (c == Command::CHARGE) return "CHARGE";
            if (c == Command::DANCE) return "DANCE";
            if (c == Command::RUNAWAY) return "RUNAWAY";
            if (c == Command::NOTHING) return "NOTHING";
            if (c == Command::FAIL) return "FAIL";

            return "";
        }

        bool can_play_;
        bool display_scalar_;

        size_t input_count_;
        size_t total_tempo_diff_;
        size_t score_scalar_;

        size_t calculateScoreScalar(const size_t total_tempo_diff);
        Feedback calculateTempoFeedback(const int tempo_diff);
        Command determineCommand(const std::vector<Drum> &combo);
        Command handleMechanics(const Feedback feedback, const Drum drum, const size_t tempo_diff);

    };


}//namespace patapon
