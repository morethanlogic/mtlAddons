/*
 *  mtlScene.cpp
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "mtlScene.h"

//--------------------------------------------------------------
mtlScene::mtlScene() {
    x      = 0;
    y      = 0;
    width  = ofGetWidth();
    height = ofGetHeight();
    alpha  = 255;
    
    status = 0;
}

//--------------------------------------------------------------
mtlScene::~mtlScene() {
    disableTouchEvents();
}

//--------------------------------------------------------------
void mtlScene::_enter() {
    enter();
    ofNotifyEvent(enterCompleted, status, this); 
}

//--------------------------------------------------------------
void mtlScene::_exit() {
    exit();
    ofNotifyEvent(exitCompleted, status, this); 
}

//--------------------------------------------------------------
void mtlScene::_draw() {
    glPushMatrix();
    glTranslatef(x, y, 0);
    {
        draw();
    }
    glPopMatrix();
}

//--------------------------------------------------------------
void mtlScene::enableTouchEvents() { 
    ofRegisterTouchEvents(this);
}

//--------------------------------------------------------------
void mtlScene::disableTouchEvents() { 
    ofUnregisterTouchEvents(this);
}


