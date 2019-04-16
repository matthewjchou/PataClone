#include "../include/ofApp.h"
#include <thread>

using namespace patapon;

void PataponGame::setup() {
    ofSetWindowTitle("Patapon");

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("BoostedTrimmedMetronome.mp3");
    //beat_player_.load("TRIAL.mp3");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);
    //music_player_.load();

    pon_standing_.load("clearpon.png");
    std::cout << "HEIGHT" << pon_standing_.getHeight() << std::endl;
    std::cout << "Width" << pon_standing_.getWidth() << std::endl;
    pon_standing_.crop(420, 300, 650, 490);
    pon_standing_.resize(2*pon_standing_.getWidth() / 3, 2*pon_standing_.getHeight() / 3);


    std::thread t(&PataponGame::playRhythm, this);
    t.detach();
}

void PataponGame::playRhythm() {
    while(true) {
        if (current_state_ == GameState::IN_PROGRESS && (!beat_player_.isPlaying())) {
            beat_player_.play();
            last_beat_time_ = ofGetElapsedTimeMillis();

        } else if (current_state_ == GameState::FINISHED) {
            break;
        }
    }
}

void PataponGame::update() {
    draw();
}

void PataponGame::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray, OF_GRADIENT_LINEAR);
    if (current_state_ == GameState::IN_PROGRESS) {
        ofSetColor(ofColor::white);
        pon_standing_.draw(ofGetWindowWidth() - pon_standing_.getWidth(), ofGetWindowHeight() - pon_standing_.getHeight());

        if (ofGetElapsedTimeMillis() - last_beat_time_  <= 200) {
            drawBeatBorder();
            beat_drawn_ = true;
        }
        if (ofGetElapsedTimeMillis() - time_since_keypress_ <= 325) {
            drawDrumName();
            drawTempoFeedback();
        }
        
    } else if (current_state_ == GameState::FINISHED) {
        drawFinished();
    }
}

void PataponGame::drawDrumName() {
    ofSetColor(ofColor::black);

    switch (drum_played_) {
        case OF_KEY_UP:
            font_.drawString(kChaka, (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(kChaka, 0, 0).getMaxX() / 2), ofGetWindowHeight() / 4);
            break;

        case OF_KEY_RIGHT:
            font_.drawString(kPon, (3 * ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(kPon, 0 ,0).getMaxX() / 2), ofGetWindowHeight() / 2);
            break;

        case OF_KEY_LEFT:
            font_.drawString(kPata, (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(kPata, 0, 0).getMaxX() / 2), ofGetWindowHeight() / 2);
            break;

        case OF_KEY_DOWN:
            font_.drawString(kDon, (ofGetWindowWidth() / 2) 
                - (font_.getStringBoundingBox(kDon, 0 ,0).getMaxX() / 2), 3 * ofGetWindowHeight() / 4);
            break;
    }
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
    switch (scoreScalar_) {
        case kMaxPointMultiplier:
            output = "Perfect!";
            ofSetColor(ofColor::green);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2*ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2*ofGetWindowHeight()/38));
            }
            break;

        case kNormalPointMultiplier:
            output = "Good!";
            ofSetColor(ofColor::yellow);
            if (beat_drawn_) {
                ofDrawRectangle(ofGetWindowWidth() / 53, ofGetWindowHeight() / 38, 
                    ofGetWindowWidth() - (2*ofGetWindowWidth() / 53), 
                    ofGetWindowHeight() - (2*ofGetWindowHeight()/38));
            }
            break;

        case 0:
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

size_t PataponGame::calculateScoreScalar() {
    if (tempoDiff_ > 0 && tempoDiff_ <= kMaxPointTime) {
        return kMaxPointMultiplier;
    } else if (tempoDiff_ >= kNoPointTime) {
        return 0;
    }

    return kNormalPointMultiplier;
}

void PataponGame::keyPressed(const int key) {
    if (std::find(valid_keys_.begin(), valid_keys_.end(), key) != valid_keys_.end()) {
        drum_played_ = key;
        time_since_keypress_ = ofGetElapsedTimeMillis();
        tempoDiff_ = time_since_keypress_ - last_beat_time_;
        std::cout << tempoDiff_ << std::endl;
        scoreScalar_ = calculateScoreScalar();
        update();
    }
}

