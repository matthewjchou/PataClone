#include "../include/ofApp.h"
#include <thread>

using namespace patapon;

void PataponGame::setup() {
    ofSetWindowTitle("Patapon");
    current_state_ = GameState::IN_PROGRESS;

    can_play_ = true;

    srand(time(NULL));
    distr_ = std::uniform_int_distribution<>(-60, 60);

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("Metronome.mp3");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);
    //music_player_.load();

    pon_logo_.load("ClearPon.png");
    pon_logo_.crop(420, 300, 650, 490);
    pon_logo_.resize(2 * pon_logo_.getWidth() / 3, 2 * pon_logo_.getHeight() / 3);

    pon_standing_.load("Hatapon.png");
    pon_standing_.resize(1 * pon_standing_.getWidth() / 4, 1 * pon_standing_.getHeight() / 4);

    pon_walking_.load("HataponWalking.png");
    //pon_walking_.crop(30, 27, 254, 445);
    pon_walking_.resize(5 * pon_walking_.getWidth() / 4, 5 * pon_walking_.getHeight() / 4);

    beat_count_ = 0;
    total_tempo_diff_ = 0;

    last_beat_time_ = 0;
    std::thread t(&PataponGame::playRhythm, this);
    t.detach();
}

void PataponGame::playRhythm() {
    while(true) {
        if (current_state_ == GameState::IN_PROGRESS && (!beat_player_.isPlaying())) {
            beat_player_.play();
            last_beat_time_ = ofGetElapsedTimeMillis();
            can_play_ = true;

        } else if (current_state_ == GameState::FINISHED) {
            break;
        }
    }
}

void PataponGame::exit() {
    current_state_ = GameState::FINISHED;
    std::cout << "EXITING" << std::endl;
}

void PataponGame::update() {
    draw();
}

void PataponGame::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray, OF_GRADIENT_LINEAR);
    drawLogo();

    if (current_state_ == GameState::IN_PROGRESS) {
        drawPatapon();
        drawPataponWalking();
        if (ofGetElapsedTimeMillis() - last_beat_time_  <= 100) {
            drawBeatBorder();
            beat_drawn_ = true;
        }
        if (ofGetElapsedTimeMillis() - last_beat_time_ <= 200 
            && ofGetElapsedTimeMillis() - time_since_keypress_ <= kNoPointTime) {
            drawTempoFeedback();
        }
        if (ofGetElapsedTimeMillis() - time_since_keypress_ <= 325) {
            drawDrumName(should_rotate_);
            should_rotate_ = false;
        }
        
    } else if (current_state_ == GameState::FINISHED) {
        drawFinished();
    }
}

void PataponGame::drawDrumName(const bool should_rotate) {
    ofSetColor(ofColor::black);
    ofPushMatrix();

    int x;
    int y;
    if (should_rotate) {
        drum_theta_ = distr_(generator_);
    }
        
    switch (drum_played_) {
        case Drum::CHAKA:
            x = (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(kChaka, 0, 0).getMaxX() / 2);
            y = ofGetWindowHeight() / 4;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(kChaka, 0, 0);
            break;

        case Drum::PON:
            x = (3 * ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(kPon, 0 ,0).getMaxX() / 2);
            y = ofGetWindowHeight() / 2;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(kPon, 0, 0);
            break;

        case Drum::PATA:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(kPata, 0, 0).getMaxX() / 2);
            y = ofGetWindowHeight() / 2;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(kPata, 0, 0);
            break;

        case Drum::DON:
            x = (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(kDon, 0 ,0).getMaxX() / 2);
            y = 3 * ofGetWindowHeight() / 4;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            font_.drawString(kDon, 0, 0);
            break;
    }
    ofPopMatrix(); //Resets the coordinate system
}

void PataponGame::drawFinished() {
    ofSetColor(ofColor::black);
    
    font_.drawString("You lost :(", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void PataponGame::drawLogo() {
    ofSetColor(ofColor::white);
    pon_logo_.draw(ofGetWindowWidth() - pon_logo_.getWidth(),
        ofGetWindowHeight() - pon_logo_.getHeight());
}

void PataponGame::drawPatapon() {
    ofSetColor(ofColor::white);
    pon_standing_.draw((ofGetWindowWidth() / 2) - (pon_standing_.getWidth() / 2),
        (ofGetWindowHeight() / 2) - (pon_standing_.getHeight() / 2));
}

void PataponGame::drawPataponWalking() {
    ofSetColor(ofColor::white);
    pon_walking_.draw((ofGetWindowWidth() / 2) - (pon_walking_.getWidth()),
        (ofGetWindowHeight() / 2) - (pon_walking_.getHeight()));
}

void PataponGame::drawBeatBorder() {
    ofSetColor(ofColor::black);
    ofNoFill();

    ofDrawRectangle(ofGetWindowWidth() / 45, ofGetWindowHeight() / 30,
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 45),
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 30));

    ofDrawRectangle(ofGetWindowWidth() / 40, ofGetWindowHeight() / 25,
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 40),
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 25));

    beat_drawn_ = false;
}

void PataponGame::drawTempoFeedback() {
    std::string output;
    ofNoFill();
    switch (tempo_feedback_) {
        case Feedback::PERFECT:
            output = "Perfect!";
            ofSetColor(ofColor::green);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2 * ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2 * ofGetWindowHeight() / 38));
            }
            break;

        case Feedback::GOOD:
            output = "Good!";
            ofSetColor(ofColor::yellow);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2 * ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2 * ofGetWindowHeight() / 38));
            }
            break;

        case Feedback::POOR:
            output = "Poor";     
            ofSetColor(ofColor::red);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2 * ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2 * ofGetWindowHeight() / 38));
            }
            break;
    }
    //Subtracts half the length of the bounding box of the string to actually center it
    font_.drawString(output, ofGetWindowWidth() / 2 
        - (font_.getStringBoundingBox(output, 0, 0).getMaxX() / 2), ofGetWindowHeight() / 2); 
}

Feedback PataponGame::calculateTempoFeedback(const int tempo_diff) {  
    if (!can_play_ || tempo_diff < 0 || (tempo_diff > kNoPointTime && tempo_diff < kEarlyPointTime)) {
        return Feedback::POOR;
    } else if (tempo_diff < kMaxPointTime) {
        return Feedback::PERFECT;
    }
    
    return Feedback::GOOD;
}

size_t PataponGame::calculateScoreScalar(const size_t tempo_diff) {
    size_t avg_diff = tempo_diff / 4;

    std::cout << "AVG: " << avg_diff << std::endl;
    if (avg_diff > 0 && avg_diff <= kMaxPointTime) {
        return kMaxPointMultiplier;
    } else if (avg_diff >= kNoPointTime) {
        return 0;
    }

    return kNormalPointMultiplier;
}

Command PataponGame::isValidCommand(const std::vector<Drum> &combo) {
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

Command PataponGame::handleMechanics(const Feedback feedback, const Drum drum, const size_t tempo_diff) {
    if (feedback == Feedback::POOR) { //If beat is missed, reset the counter and the combo 
            total_tempo_diff_ = 0;
            beat_count_ = 0;    
            display_scalar_ = false;
            Drum drum_played_;
            combo_.clear();

        } else {
            total_tempo_diff_ += tempo_diff;
            beat_count_++;
            combo_.push_back(drum);
        }

        Command current_command = isValidCommand(combo_);  
        if (current_command == Command::FAIL) { //If the notes aren't part of a command, reset combo
            combo_.clear();
            total_tempo_diff_ = 0;
            beat_count_ = 0;
            std::cout << tempConvertCommand(current_command) << std::endl << std::endl;
        } else if (current_command != Command::NOTHING) {
            score_scalar_ = calculateScoreScalar(total_tempo_diff_);
            display_scalar_ = true;
            beat_count_ = 0;
            total_tempo_diff_ = 0;


            std::string toPrint;
            for (auto i : combo_) {
                toPrint += tempConvert(i);
                toPrint += " ";
            }
            toPrint += '\n';
            toPrint += tempConvertCommand(current_command);
            toPrint += '\n';

            std::cout << toPrint << std::endl;
            combo_.clear();
        }

    return Command::NOTHING;
}

void PataponGame::keyPressed(const int key) {
    auto it = kDrumMap.find(key);
    if (it != kDrumMap.end()) {
        drum_played_ = it->second;
        time_since_keypress_ = ofGetElapsedTimeMillis();
        std::cout << "KEYPRESS: " << time_since_keypress_ << std::endl;
        int tempo_diff = time_since_keypress_ - last_beat_time_;
        std::cout << "TIME DIFF: " << tempo_diff << std::endl;

        tempo_feedback_ = calculateTempoFeedback(tempo_diff);
        should_rotate_ = true;
        can_play_ = false;

        Command command = handleMechanics(tempo_feedback_, it->second, tempo_diff);
        
        update();

    }
}

