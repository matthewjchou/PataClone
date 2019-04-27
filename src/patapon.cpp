#include "../include/patapon.hpp"

using namespace patapongame;

Feedback Patapon::calculateTempoFeedback(const int tempo_diff) {  
    if (!can_play_ || tempo_diff < 0 || (tempo_diff >= kNoPointTime && tempo_diff < kEarlyPointTime)) {
        return Feedback::POOR;
    } else if (tempo_diff <= kMaxPointTime) {
        return Feedback::PERFECT;
    }
    
    return Feedback::GOOD;
}

size_t Patapon::calculateScoreScalar(const size_t total_tempo_diff) {
    size_t avg_diff = total_tempo_diff / 4;

    std::cout << "AVG: " << avg_diff << std::endl;
    if (avg_diff >= 0 && avg_diff <= kMaxPointTime) {
        return kMaxPointMultiplier;
    } else if (avg_diff >= kNoPointTime) {
        return 0;
    }

    return kNormalPointMultiplier;
}

Command Patapon::determineCommand(const std::vector<Drum> &combo) {
    try {
        if (combo.at(0) == Drum::PATA) {
            if (combo.at(1) == Drum::PATA) {
                if (combo.at(2) == Drum::PATA) {
                    if (combo.at(3) == Drum::PON) {
                        return Command::MOVE;
                    }
                }
            } else if (combo.at(1) == Drum::PON) {
                if (combo.at(2) == Drum::DON) {
                    if (combo.at(3) == Drum::CHAKA) {
                        return Command::DANCE;
                    }
                }
            }
        } else if (combo.at(0) == Drum::PON) {
            if (combo.at(1) == Drum::PON) {
                if (combo.at(2) == Drum::PATA) {
                    if (combo.at(3) == Drum::PON) {
                        return Command::ATTACK;
                    }
                } else if (combo.at(2) == Drum::CHAKA) {
                    if (combo.at(3) == Drum::CHAKA) {
                        return Command::CHARGE;
                    }
                }
            } else if (combo.at(1) == Drum::PATA) {
                if (combo.at(2) == Drum::PON) {
                    if (combo.at(3) == Drum::PATA) {
                        return Command::RUNAWAY;
                    }
                }
            }
        } else if (combo.at(0) == Drum::CHAKA) {
            if (combo.at(1) == Drum::CHAKA) {
                if (combo.at(2) == Drum::PATA) {
                    if (combo.at(3) == Drum::PON) {
                        return Command::DEFEND;
                    }
                }
            }
        }
    } catch (...) {
        return Command::NOTHING;
    }

    return Command::FAIL;
}

Command Patapon::handleMechanics(const Feedback feedback, const Drum drum, const size_t tempo_diff) {
    if (feedback == Feedback::POOR) { //If beat is missed, reset the counter and the combo 
            resetCombo();

        } else {
            total_tempo_diff_ += tempo_diff;
            input_count_++;
            combo_.push_back(drum);
        }

        Command current_command = determineCommand(combo_);  
        if (current_command == Command::FAIL) { //If the notes aren't part of a command, reset combo
            resetCombo();
            std::cout << tempConvertCommand(current_command) << std::endl << std::endl;
        } else if (current_command != Command::NOTHING) {
            score_scalar_ = calculateScoreScalar(total_tempo_diff_);
    
            std::string toPrint;
            for (auto i : combo_) {
                toPrint += tempConvert(i);
                toPrint += " ";
            }
            toPrint += '\n';
            toPrint += tempConvertCommand(current_command);
            toPrint += '\n';

            std::cout << toPrint << std::endl;

            resetCombo();

            return current_command;
        }

    return Command::NOTHING;
}

void Patapon::executeCommand(const Command command) {
    
}

void Patapon::resetCombo() {
    combo_.clear();
    total_tempo_diff_ = 0;
    input_count_ = 0;

    std::cout << "RESETTING COMBO" << std::endl;
}
