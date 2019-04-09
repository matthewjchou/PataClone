#include "../include/ofApp.h"
#include <thread>

using namespace patapon;

void PataponGame::setup() {
    ofSetWindowTitle("Patapon");

    font_.load("arial.ttf", 44);

    beat_player_.load("TrimmedMetronome.wav");
    beat_player_.setSpeed(0.4);
    //music_player_.load();

    std::thread t(&PataponGame::playRhythm, this);
    t.detach();
    }

void PataponGame::playRhythm() {
    while(true) {
        if (current_state_ == GameState::IN_PROGRESS && (!beat_player_.isPlaying())) {
            beat_player_.play();
        } else if (current_state_ == GameState::FINISHED) {
            break;
        }
    }
}

void PataponGame::update() {
    if (should_update_) {
        if (current_state_ == GameState::IN_PROGRESS) {
            draw();
        }
    }
}

void PataponGame::draw() {
    if (current_state_ == GameState::IN_PROGRESS) {
        
        if (ofGetElapsedTimef() - time_since_keypress_ <= 0.35f) {
            drawDrumName();
        }

    } else if (current_state_ == GameState::FINISHED) {
        drawFinished();
    }
}

void PataponGame::drawDrumName() {
    ofSetColor(0, 0, 0);

    switch (drum_played_) {
        case OF_KEY_UP:
            font_.drawString("CHAKA", ofGetWindowWidth() / 2, ofGetWindowHeight() / 4);
            break;

        case OF_KEY_RIGHT:
            font_.drawString("PON", 3 * ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);
            break;

        case OF_KEY_LEFT:
            font_.drawString("PATA", ofGetWindowWidth() / 4, ofGetWindowHeight() / 2);
            break;

        case OF_KEY_DOWN:
            font_.drawString("DON", ofGetWindowWidth() / 2, 3 * ofGetWindowHeight() / 4);
            break;
    }
}

void PataponGame::drawFinished() {
    ofSetColor(0, 0 ,0);
    
    font_.drawString("You lost :(", ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
}

void PataponGame::keyPressed(const int key) {

    if (key == OF_KEY_UP) {
        drum_played_ = key;
        should_update_ = false;
        time_since_keypress_ = ofGetElapsedTimef();
        update();

    } else if (key == OF_KEY_RIGHT) {
        drum_played_ = key;
        should_update_ = false;
        time_since_keypress_ = ofGetElapsedTimef();
        update();

    } else if (key == OF_KEY_LEFT) {
        drum_played_ = key;
        should_update_ = false;
        time_since_keypress_ = ofGetElapsedTimef();
        update();

    } else if (key == OF_KEY_DOWN) { 
        drum_played_ = key;
        should_update_ = false;
        time_since_keypress_ = ofGetElapsedTimef();
        update();
    }

    return;
}

