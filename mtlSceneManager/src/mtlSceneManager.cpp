/*
 *  mtlSceneManager.cpp
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
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
    ofAddListener(ofEvents.update, this, &mtlSceneManager::update);
    ofAddListener(ofEvents.draw,   this, &mtlSceneManager::draw);
    
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
void mtlSceneManager::update(ofEventArgs& _args) {
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
        currScene->enter();
    }
}

//--------------------------------------------------------------
void mtlSceneManager::draw(ofEventArgs& _args) {
    if (currScene) {
        currScene->pushScene();
        currScene->draw();
        currScene->popScene();
    }
    if (nextScene) {
        nextScene->pushScene();
        nextScene->draw();
        nextScene->popScene();
    }
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
        currScene->exit();
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

