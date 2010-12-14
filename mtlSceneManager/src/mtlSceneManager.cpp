/***********************************************************************
 *
 * Copyright (c) 2010 Elie Zananiri, Hugues Bruyère
 * more than logic http://www.morethanlogic.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of "more than logic" nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. 
 *
 * ***********************************************************************/

/*
 *  mtlSceneManager.cpp
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 */

#include "mtlSceneManager.h"

//--------------------------------------------------------------
mtlSceneManager* mtlSceneManager::sceneManager = NULL;
unsigned         mtlSceneManager::duration     = 1000;

//--------------------------------------------------------------
mtlSceneManager* mtlSceneManager::getInstance() {
    if (!sceneManager) {
        sceneManager = new mtlSceneManager();
    }
    return sceneManager;
}

//--------------------------------------------------------------
void mtlSceneManager::setTransitionDuration(unsigned _duration) {
    duration = _duration;
}

//--------------------------------------------------------------
mtlSceneManager::mtlSceneManager() {
    ofAddListener(ofEvents.update, this, &mtlSceneManager::_update);
    ofAddListener(ofEvents.draw,   this, &mtlSceneManager::_draw);
    
    currName  = "";
    currScene = NULL;
    nextName  = "";
    nextScene = NULL;
}

//--------------------------------------------------------------
mtlSceneManager::~mtlSceneManager() {
     // delete all the scenes
}

//--------------------------------------------------------------
void mtlSceneManager::_update(ofEventArgs& _args) {
    if (currScene) currScene->update();
    if (nextScene) nextScene->update();
    
    if (tween.isCompleted()) return;
    
    target = tween.update();
    
    switch (nextTransition) {
        case mtlSceneTransitionFade:
            nextScene->alpha = 255 * target;
            break;
            
        case mtlSceneTransitionPushLeft:
            if (currScene) {
                currScene->x = currScene->width * (target - 1);
            }
        case mtlSceneTransitionOverLeft: 
            nextScene->x = nextScene->width * target;
            break;
            
        case mtlSceneTransitionPushRight:
            if (currScene) {
                currScene->x = currScene->width * (target + 1);
            }
        case mtlSceneTransitionOverRight:    
            nextScene->x = nextScene->width * target;
            break;
            
        case mtlSceneTransitionPushUp:
            if (currScene) {
                currScene->y = currScene->height * (target - 1);
            }
        case mtlSceneTransitionOverUp:    
            nextScene->y = nextScene->height * target;
            break;
            
        case mtlSceneTransitionPushDown:
            if (currScene) {
                currScene->y = currScene->height * (target + 1);
            }
        case mtlSceneTransitionOverDown:    
            nextScene->y = nextScene->height * target;
            break;
    }
    
    if (tween.isCompleted()) {
        if (destroyLast && currScene) {
            scenes.erase(currName);
            delete currScene;
        }
        currName  = nextName;
        currScene = nextScene;
        
        // enter the current scene
        ofAddListener(currScene->enterCompleted, this, &mtlSceneManager::onEnterCompleted);
        currScene->_enter();
    }
}

//--------------------------------------------------------------
void mtlSceneManager::_draw(ofEventArgs& _args) {
    if (currScene)
        currScene->_draw();
    
    if (nextScene)
        nextScene->_draw();
}

//--------------------------------------------------------------
void mtlSceneManager::addScene(const string& _name, mtlScene* _scene) {
    map<string, mtlScene*>::iterator it = scenes.find(_name);
    if (it != scenes.end()) {
        ofLog(OF_LOG_ERROR, "mtlSceneManager::addScene() Scene '" + _name + "' already exists");
        return;
    }
    
    scenes[_name] = _scene;
}

//--------------------------------------------------------------
bool mtlSceneManager::switchToScene(const string& _name, mtlSceneTransition _transition, bool _destroyLast) {
    if (!tween.isCompleted()) {
        ofLog(OF_LOG_WARNING, "mtlSceneManager::switchToScene() ignored as there is already a switch in progress");
        return false;
    }
    
    map<string, mtlScene*>::iterator it = scenes.find(_name);
    if (it == scenes.end()) {
        ofLog(OF_LOG_ERROR, "mtlSceneManager::switchToScene() Scene '" + _name + "' does not exist");
        return false;
    }
    
    // set up the transition
    nextName       = it->first;
    nextScene      = it->second;
    nextTransition = _transition;
    destroyLast    = _destroyLast;
    
    // set the next scene params based on the transition type
    switch (nextTransition) {
        case mtlSceneTransitionFade:
            nextScene->alpha = 0;
            break;
            
        case mtlSceneTransitionPushLeft:
        case mtlSceneTransitionOverLeft:    
            nextScene->x = nextScene->width;
            break;
            
        case mtlSceneTransitionPushRight:
        case mtlSceneTransitionOverRight:    
            nextScene->x = -nextScene->width;
            break;
            
        case mtlSceneTransitionPushUp:
        case mtlSceneTransitionOverUp:    
            nextScene->y = nextScene->height;
            break;
            
        case mtlSceneTransitionPushDown:
        case mtlSceneTransitionOverDown:    
            nextScene->y = -nextScene->height;
            break;
    }
    
    if (currScene) {
        // exit the current scene
        ofAddListener(currScene->exitCompleted, this, &mtlSceneManager::onExitCompleted);
        currScene->_exit();
    } else {
        // call the exit completed callback manually
        int status = 0;
        onExitCompleted(status);
    }
    
    return true;
}

//--------------------------------------------------------------
bool mtlSceneManager::addAndSwitchToScene(const string& _name, mtlScene* _scene, mtlSceneTransition _transition, bool _destroyLast) {
    if (!tween.isCompleted()) {
        ofLog(OF_LOG_WARNING, "mtlSceneManager::addAndSwitchToScene() ignored as there is already a switch in progress");
        return false;
    }
    
    addScene(_name, _scene);
    return switchToScene(_name, _transition, _destroyLast);
}

//--------------------------------------------------------------
void mtlSceneManager::onEnterCompleted(int& _status) {
    // remove the enter scene listener
    ofRemoveListener(currScene->enterCompleted, this, &mtlSceneManager::onEnterCompleted);
    
    // the transition is done at this point, wait for a new request
}

//--------------------------------------------------------------
void mtlSceneManager::onExitCompleted(int& _status) {
    if (currScene) {
        // remove the exit scene listener
        ofRemoveListener(currScene->exitCompleted, this, &mtlSceneManager::onExitCompleted);
    }
    
    // start the transition
    switch (nextTransition) {
        case mtlSceneTransitionNone:
            tween.setParameters(easing, ofxTween::easeOut, 0, 1, 1, 0);
            break;
            
        case mtlSceneTransitionFade:
            tween.setParameters(easing, ofxTween::easeOut, 0, 1, duration, 0);
            break;
         
        case mtlSceneTransitionPushLeft:
        case mtlSceneTransitionOverLeft:
        case mtlSceneTransitionPushUp:
        case mtlSceneTransitionOverUp:  
            tween.setParameters(easing, ofxTween::easeOut, 1, 0, duration, 0);
            break;
            
        case mtlSceneTransitionPushRight:
        case mtlSceneTransitionOverRight:    
        case mtlSceneTransitionPushDown:
        case mtlSceneTransitionOverDown:    
            tween.setParameters(easing, ofxTween::easeOut, -1, 0, duration, 0);
            break;  
    }
    
    tween.start();
}

