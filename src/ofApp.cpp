#include "../include/ofApp.h"
#include <thread>

using namespace patapongame;

void Game::setup() {
    ofSetWindowTitle("Patapon");
    current_state_ = GameState::IN_PROGRESS;

    box2d.init();
    box2d.enableEvents();
    box2d.setGravity(35, 6);
    ofRectangle bounding_box(0, 0, ofGetWindowWidth(), (int) std::get<0>(ground_points_).y);
    box2d.createGround(std::get<0>(ground_points_), std::get<1>(ground_points_));
    box2d.createBounds(bounding_box);
    box2d.setFPS(60);

    collision_ = false;

    ofAddListener(box2d.contactStartEvents, this, &Game::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &Game::contactEnd);

    executing_command_ = false;

    srand(time(NULL));
    distr_ = std::uniform_int_distribution<>(-60, 60);
    norm_distr_ = std::normal_distribution<>((ofGetWindowHeight() / 3) + 50, 150);

    font_.load("arial.ttf", kFontSize);

    beat_player_.load("Sounds/Metronome.mp3");
    beat_player_.setSpeed(kBeatSpeed);
    beat_player_.setVolume(kBeatVolume);

    music_player_.load("Music/Infectious.mp3");
    music_player_.setSpeed(0.9);
    music_player_.setVolume(0.3);

    win_player_.load("Sounds/FireCrackers.mp3");
    win_player_.setVolume(0.6);

    impact_player_.load("Sounds/MirrorShatter.mp3");

    background_image_.load("Images/PataponBackground.jpg");
    background_image_.resize(2.7 * background_image_.getWidth(), 2.14 * background_image_.getHeight());

    pon_logo_.load("Images/PataponLogo.png");
    pon_logo_.crop(420, 300, 650, 490);
    pon_logo_.resize(1 * pon_logo_.getWidth() / 3, 1 * pon_logo_.getHeight() / 3);

    pon_standing_.load("Sprites/Hatapon.png");
    pon_standing_.resize(1 * pon_standing_.getWidth() / 4, 1 * pon_standing_.getHeight() / 4);

    //pon_walking_.load("HataponWalking.png");
    //pon_walking_.crop(30, 27, 254, 445);
    //pon_walking_.resize(3 * pon_walking_.getWidth() / 2, 3 * pon_walking_.getHeight() / 2);
    boss_ = Boss("Gigantus", 100, 200, "Sprites/Gigantus.png");
    boss_.getImage().resize(2 * boss_.getImage().getWidth(), 2 * boss_.getImage().getHeight());
    boss_.getIcon().resize(boss_.getIcon().getWidth() / 4.5, boss_.getIcon().getWidth() / 6);
    boss_.getHitbox().setup(box2d.getWorld(), ofGetWindowWidth() - 450
        , ofGetWindowHeight() - 650, 750, 650);

    patapon.input_count_ = 0;
    patapon.total_tempo_diff_ = 0;

    last_beat_time_ = 0;
    std::thread t(&Game::playRhythm, this);
    t.detach();
}

void Game::playRhythm() {
    size_t beat_count = 0;

    while(true) {
        if (!beat_player_.isPlaying()) {
            beat_player_.play();
            last_beat_time_ = ofGetElapsedTimeMillis();
            if (executing_command_) {
                beat_count++;

                std::cout << "BEAT COUNT: " << std::to_string(beat_count) << std::endl;

                if (beat_count == 5) {
                    beat_count = 0;
                    executing_command_ = false;
                }
            }

        } else if (current_state_ == GameState::FINISHED && !executing_command_) {
            break;
        }
        if (!music_player_.isPlaying()) {
            music_player_.play();
        }
    }
}

void Game::playWinSound() {
    if (!win_player_.isPlaying()) {
        win_player_.play();
    }
}

void Game::exit() {
    current_state_ = GameState::FINISHED;
    std::cout << "EXITING" << std::endl;
}

void Game::update() {
    if (!executing_command_ && ofGetElapsedTimeMillis() - time_since_keypress_ > 1200) {
        patapon.resetCombo();
    }
    box2d.update();
    draw();
}

void Game::draw() {    
    if (current_state_ == GameState::IN_PROGRESS || executing_command_) {
        drawBackgroundImage();
        ofSetColor(ofColor::white);
        drawLogo();    
        drawBoss();
        drawBossIcon();
        drawBossHealthBar();
        drawGround();

        drawPatapon();
        // drawPataponWalking();
        if (executing_command_) {
            if (current_command_ == Command::ATTACK) {
                drawVolley();
            }
        }

        if (ofGetElapsedTimeMillis() - last_beat_time_  <= 100) {
            drawBeatBorder();
            beat_drawn_ = true;
        }
        if (ofGetElapsedTimeMillis() - last_beat_time_ <= 200 
            && ofGetElapsedTimeMillis() - time_since_keypress_ <= patapon.kNoPointTime) {
            drawTempoFeedback();
        }
        if (ofGetElapsedTimeMillis() - time_since_keypress_ <= 325) {
            drawDrumName(should_rotate_);
            should_rotate_ = false;
        }
        
    } else if (current_state_ == GameState::FINISHED && !executing_command_) {
        ofBackgroundGradient(ofColor::blanchedAlmond, ofColor::red, OF_GRADIENT_CIRCULAR);
        drawFinished();
    }
}

void Game::drawDrumName(const bool should_rotate) {
    ofSetColor(ofColor::black);
    ofPushMatrix();

    int x;
    int y;
    if (should_rotate) {
        drum_theta_ = distr_(generator_);
    }
        
    switch (drum_played_) {
        case Drum::CHAKA:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kChaka, 0, 0).getMaxX() / 2);
            y = (ofGetWindowHeight() / 2) + 25;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::springGreen);
            font_.drawString(patapon.kChaka, 0, 0);
            break;

        case Drum::PON:
            x = (ofGetWindowWidth() / 4) 
                + (font_.getStringBoundingBox(patapon.kPon, 0 ,0).getMaxX() / 2) + 50;
            y = (2 * ofGetWindowHeight() / 3);
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::cyan);
            font_.drawString(patapon.kPon, 0, 0);
            break;

        case Drum::PATA:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kPata, 0, 0).getMaxX() / 2) - 200;
            y = (2 * ofGetWindowHeight() / 3);
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::orangeRed);
            font_.drawString(patapon.kPata, 0, 0);
            break;

        case Drum::DON:
            x = (ofGetWindowWidth() / 4) 
                - (font_.getStringBoundingBox(patapon.kDon, 0 ,0).getMaxX() / 2);
            y = (ofGetWindowHeight() / 2) + 450;
            ofTranslate(x, y);
            ofRotateZDeg(drum_theta_);
            ofSetColor(ofColor::gold);
            font_.drawString(patapon.kDon, 0, 0);
            break;
    }
    ofPopMatrix(); //Resets the coordinate system
}

void Game::drawFinished() {
    ofSetColor(ofColor::black);
    font_.load("Fonts/Kaushan.ttf", 3 * kFontSize);
    std::string win_message = "Congratulations!";
    font_.drawString(win_message, (ofGetWindowWidth() / 2) 
        - (font_.getStringBoundingBox(win_message, 0, 0).getMaxX() / 2)
        , ofGetWindowHeight() / 2);
    std::thread t(&Game::playWinSound, this);
    t.detach();
}

void Game::drawLogo() {
    ofSetColor(ofColor::white);
    pon_logo_.draw(0, 0);
}

void Game::drawBackgroundImage() {
    ofSetColor(ofColor::white);
    background_image_.draw(0, 0);
}

void Game::drawBoss() {
    ofSetColor(ofColor::white);
    boss_.getImage().draw(1275, 337);

    ofEnableAlphaBlending();
    ofSetColor(ofColor::grey, kHitboxTransparency);
    ofNoFill();
    boss_.getHitbox().draw();
}

void Game::drawBossIcon() {
    ofSetColor(ofColor::black);
    ofNoFill();
    ofSetLineWidth(10);
    ofDrawCircle(ofGetWindowWidth() - 155, 200, 85);
    ofSetColor(ofColor::white);
    ofFill();
    ofDrawCircle(ofGetWindowWidth() - 155, 200, 85);
    ofSetColor(ofColor::white);
    boss_.getIcon().draw(ofGetWindowWidth() - 235, 140);
}

void Game::drawBossHealthBar() {
    ofSetColor(ofColor::black);
    ofNoFill();
    ofSetLineWidth(10);
    ofRectangle health_bar_outline = ofRectangle(ofGetWindowWidth() - 250, 55, 190, 35);
    ofDrawRectRounded(health_bar_outline, 10);

    ofSetColor(ofColor::white);
    ofFill();
    ofRectangle health_bar_background = ofRectangle(ofGetWindowWidth() - 250, 60, 190, 25);
    ofDrawRectRounded(health_bar_background, 10);

    ofSetColor(ofColor::green);
    ofRectangle health_bar = ofRectangle(ofGetWindowWidth() - 250, 60, 190 / ((boss_.getMaxHealth() + 0.1) / boss_.getHealth()), 25);
    ofDrawRectRounded(health_bar, 10);
}

void Game::drawGround() {
    ofSetColor(ofColor::black);
    ofFill();
    ofDrawRectangle(std::get<0>(ground_points_), ofGetWindowWidth(), 2000);
}

void Game::drawPatapon() {
    ofSetColor(ofColor::white);
    pon_standing_.draw((ofGetWindowWidth() / 4) - (pon_standing_.getWidth() / 2),
        (ofGetWindowHeight() / 2) - (pon_standing_.getHeight() / 2));
}

void Game::drawPataponWalking() {
    ofSetColor(ofColor::white);
    pon_walking_.draw((ofGetWindowWidth() / 2) - (pon_walking_.getWidth()),
        (ofGetWindowHeight() / 2) - (pon_walking_.getHeight()));
}

void Game::drawBeatBorder() {
    ofSetLineWidth(2);
    ofSetColor(ofColor::white);
    ofNoFill();

    ofDrawRectangle(ofGetWindowWidth() / 95, ofGetWindowHeight() / 70,
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 95),
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 70));

    ofDrawRectangle(ofGetWindowWidth() / 78, ofGetWindowHeight() / 55,
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 78),
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 55));

    beat_drawn_ = false;
}

void Game::drawTempoFeedback() {
    std::string output;
    ofNoFill();
    switch (tempo_feedback_) {
        case Feedback::PERFECT:
            output = "Perfect!";
            ofSetColor(ofColor::green);
            if (beat_drawn_) {
                drawTempoFeedbackBorder();
            }
            break;

        case Feedback::GOOD:
            output = "Good!";
            ofSetColor(ofColor::yellow);
            if (beat_drawn_) {
                drawTempoFeedbackBorder();
            }
            break;

        case Feedback::POOR:
            output = "Poor";     
            ofSetColor(ofColor::red);
            if (beat_drawn_) {
                drawTempoFeedbackBorder();
            }
            break;
    }
    //Subtracts half the length of the bounding box of the string to actually center it
   font_.drawString(output, ofGetWindowWidth() / 2 
        - (font_.getStringBoundingBox(output, 0, 0).getMaxX() / 2), ofGetWindowHeight() / 2); 
}

void Game::drawTempoFeedbackBorder() {
    ofSetLineWidth(2);
    ofDrawRectangle(ofGetWindowWidth() / 60, ofGetWindowHeight() / 40, 
        ofGetWindowWidth() - (2 * ofGetWindowWidth() / 60), 
        ofGetWindowHeight() - (2 * ofGetWindowHeight() / 40));
}

void Game::drawVolley() {
    int transparency_level = 255;
    if (collision_) {
        transparency_level -= transparency_tick_;
        transparency_tick_ += 10;

        if (transparency_tick_ > 220) {
            collision_ = false;
            destroyVolley();
        }
    }

    for (size_t i = 0; i < circles_.size(); i++) {
        ofFill();
        ofSetColor(ofColor::black, transparency_level);
        circles_.at(i)->draw();

        ofNoFill();
        ofSetLineWidth(5);
        ofSetColor(ofColor::white, transparency_level);
        ofDrawCircle(circles_.at(i)->getPosition(), 25);
    }
}

void Game::executeCommand(const Command command) {
    executing_command_ = true;
    current_command_ = command;

    switch(command) {
        case Command::ATTACK:
            int augmented_damage;
            createVolley(patapon.score_scalar_, charge_scalar_);
            augmented_damage = pon_.getStrength() * patapon.score_scalar_;

            if (std::get<0>(charge_scalar_)) {
                augmented_damage *= std::get<1>(charge_scalar_);
                charge_scalar_ = std::make_tuple(false, 1);
            }

            if (!boss_.takeDamage(augmented_damage)) {
                current_state_ = GameState::FINISHED;
            }   

            break;
        
        case Command::CHARGE:
            if (patapon.score_scalar_ == patapon.kMaxPointMultiplier) {
                charge_scalar_ = std::make_tuple(true, 3);
            } else if (patapon.score_scalar_ == patapon.kNormalPointMultiplier) {
                charge_scalar_ = std::make_tuple(true, 2);
            } else {
                charge_scalar_ = std::make_tuple(false, 1);
            }
            break;

        default:
            break;
    }
}

void Game::contactStart(ofxBox2dContactArgs &e) {
    
}

void Game::contactEnd(ofxBox2dContactArgs &e) {
    if (e.a != nullptr && e.b != nullptr) {
        transparency_tick_ = 10;
        collision_ = true;
        impact_player_.play();
    }   
}

void Game::createVolley(size_t score_scalar, std::tuple<bool, size_t> charge_scalar) {
    int volley_size = 0;
    circles_.clear();

    if (score_scalar == patapon.kMaxPointMultiplier) {
        volley_size += 2;
    } else {
        volley_size += 1;
    }

    if (std::get<0>(charge_scalar)) {
        volley_size += std::get<1>(charge_scalar);
    }

    for (int i = 0; i < volley_size; i++) {
        auto circle = std::make_shared<ofxBox2dCircle>();
        int random_pos = norm_distr_(generator_);
        circle.get()->setPhysics(3, 0.3, 0.5);
        circle.get()->setup(box2d.getWorld(), 60, random_pos, 25);
        circles_.push_back(circle);
    }
}

void Game::destroyVolley() {
    circles_.clear();
}

void Game::keyPressed(const int key) {
    auto it = kDrumMap.find(key);
    if (it != kDrumMap.end() && !executing_command_) {
        std::cout << "KEYPRESSED" << std::endl;
        drum_played_ = it->second;
        time_since_keypress_ = ofGetElapsedTimeMillis();
        int tempo_diff = time_since_keypress_ - last_beat_time_;

        tempo_feedback_ = patapon.calculateTempoFeedback(tempo_diff);
        should_rotate_ = true;

        Command command = patapon.handleMechanics(tempo_feedback_, it->second, tempo_diff);

        if (command != Command::NOTHING && command != Command::FAIL) {
            executeCommand(command);
        }
        
        update();
    }
}

