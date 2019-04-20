#include "../include/ofApp.h"
#include <thread>

using namespace patapon;

void PataponGame::setup() {
    ofSetWindowTitle("Patapon");
    current_state_ = GameState::IN_PROGRESS;

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("Metronome.mp3");
    //beat_player_.load("TRIAL.mp3");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);
    //music_player_.load();

    pon_standing_.load("clearpon.png");
    
    pon_standing_.crop(420, 300, 650, 490);
    pon_standing_.resize(2*pon_standing_.getWidth() / 3, 2*pon_standing_.getHeight() / 3);

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
            //std::cout << ofGetElapsedTimeMillis() - last_beat_time_ << std::endl;
            std::cout << "BEATPLAYED: " << ofGetElapsedTimeMillis() << std::endl;
            last_beat_time_ = ofGetElapsedTimeMillis();

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
    if (current_state_ == GameState::IN_PROGRESS) {
        ofSetColor(ofColor::white);
        pon_standing_.draw(ofGetWindowWidth() - pon_standing_.getWidth(),
        ofGetWindowHeight() - pon_standing_.getHeight());
        //std::cout << "HERE" << ofGetElapsedTimeMillis() - last_beat_time_ << std::endl;
        if (ofGetElapsedTimeMillis() - last_beat_time_  <= 100) {
            drawBeatBorder();
            beat_drawn_ = true;
        }
        if (ofGetElapsedTimeMillis() - time_since_keypress_ <= 325) {
            drawDrumName();
            // TODO: Make the border feedback more in sync
            drawTempoFeedback();
        }
        
    } else if (current_state_ == GameState::FINISHED) {
        drawFinished();
    }
}

void PataponGame::drawDrumName() {
    ofSetColor(ofColor::black);
    ofPushMatrix();

    int x;
    int y;

    switch (drum_played_) {
        case OF_KEY_UP:
            x = (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(kChaka, 0, 0).getMaxX() / 2);
            y = ofGetWindowHeight() / 4;
            ofTranslate(x, y);
            ofRotateZDeg(30);
            font_.drawString(kChaka, 0, 0);
            break;

        case OF_KEY_RIGHT:
            x = (3 * ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(kPon, 0 ,0).getMaxX() / 2);
            y = ofGetWindowHeight() / 2;
            ofTranslate(x, y);
            ofRotateZDeg(30);
            font_.drawString(kPon, 0, 0);
            break;

        case OF_KEY_LEFT:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(kPata, 0, 0).getMaxX() / 2);
            y = ofGetWindowHeight() / 2;
            ofTranslate(x, y);
            ofRotateZDeg(30);
            font_.drawString(kPata, 0, 0);
            break;

        case OF_KEY_DOWN:
            x = (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(kDon, 0 ,0).getMaxX() / 2);
            y = 3 * ofGetWindowHeight() / 4;
            ofTranslate(x, y);
            ofRotateZDeg(30);
            font_.drawString(kDon, 0, 0);
            break;
    }
    ofPopMatrix();
}

void PataponGame::drawFinished() {
    ofSetColor(ofColor::black);
    
    font_.drawString("You lost :(", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void PataponGame::drawBeatBorder() {
    ofSetColor(ofColor::black);
    ofNoFill();

    ofDrawRectangle(ofGetWindowWidth() / 45, ofGetWindowHeight() / 30,
        ofGetWindowWidth() - (2*ofGetWindowWidth()/45),
        ofGetWindowHeight() - (2*ofGetWindowHeight()/30));

    ofDrawRectangle(ofGetWindowWidth() / 40, ofGetWindowHeight() / 25,
        ofGetWindowWidth() - (2*ofGetWindowWidth()/40),
        ofGetWindowHeight() - (2*ofGetWindowHeight()/25));

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
                    ofGetWindowWidth() - (2*ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2*ofGetWindowHeight()/38));
            }
            break;

        case Feedback::GOOD:
            output = "Good!";
            ofSetColor(ofColor::yellow);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2*ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2*ofGetWindowHeight()/38));
            }
            break;

        case Feedback::POOR:
            output = "Poor";     
            ofSetColor(ofColor::red);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2*ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2*ofGetWindowHeight()/38));
            }
            break;
    }
    //Subtracts half the length of the bounding box of the string to actually center it
    font_.drawString(output, ofGetWindowWidth() / 2 
        - (font_.getStringBoundingBox(output, 0, 0).getMaxX() / 2), ofGetWindowHeight() / 2); 
}

Feedback PataponGame::calculateTempoFeedback(int tempo_diff) {
    if (tempo_diff < 0 || tempo_diff > kNoPointTime) {
        return Feedback::POOR;
    } else if (tempo_diff < kMaxPointTime) {
        return Feedback::PERFECT;
    }
    
    return Feedback::GOOD;
}

size_t PataponGame::calculateScoreScalar(size_t tempo_diff) {
    size_t avg_diff = tempo_diff / 4;

    std::cout << "AVG: " << avg_diff << std::endl;
    if (avg_diff > 0 && avg_diff <= kMaxPointTime) {
        return kMaxPointMultiplier;
    } else if (avg_diff >= kNoPointTime) {
        return 0;
    }

    return kNormalPointMultiplier;
}

void PataponGame::keyPressed(const int key) {
    if (std::find(valid_keys_.begin(), valid_keys_.end(), key) != valid_keys_.end()) {
        drum_played_ = key;
        time_since_keypress_ = ofGetElapsedTimeMillis();
        std::cout << "KEYPRESS: " << time_since_keypress_ << std::endl;
        int tempo_diff = time_since_keypress_ - last_beat_time_;
        //std::cout << "TEMPO_DIFF: " << tempo_diff << std::endl;
        tempo_feedback_ = calculateTempoFeedback(tempo_diff);
        
        if (tempo_feedback_ == Feedback::POOR) {
            total_tempo_diff_ = 0;
            beat_count_ = 0;    
            display_scalar_ = false;
        } else {
            total_tempo_diff_ += tempo_diff;
            beat_count_++;
        }
        
        if (beat_count_ == 4) {
            score_scalar_ = calculateScoreScalar(total_tempo_diff_);
            display_scalar_ = true;
            beat_count_ = 0;
            total_tempo_diff_ = 0;
        }
        update();
    }
}

