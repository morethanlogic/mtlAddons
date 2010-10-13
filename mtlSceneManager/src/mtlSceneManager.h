#pragma once

/*
 *  mtlSceneManager.h
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxTween.h"
#include "mtlScene.h"

//========================================================================
enum mtlSceneTransition {
    mtlSceneTransitionNone,
    mtlSceneTransitionFade,
    mtlSceneTransitionPushLeft,
    mtlSceneTransitionPushRight,
    mtlSceneTransitionPushUp,
    mtlSceneTransitionPushDown,
    mtlSceneTransitionOverLeft,
    mtlSceneTransitionOverRight,
    mtlSceneTransitionOverUp,
    mtlSceneTransitionOverDown
};

//========================================================================
class mtlSceneManager {
    
    public:
        static mtlSceneManager*     getInstance();
        static void                 setTransitionDuration(unsigned _duration);
        
                                    mtlSceneManager();
                                    ~mtlSceneManager();
    
        void                        _update(ofEventArgs& _args);
        void                        _draw(ofEventArgs& _args);
    
        void                        addScene(const string& _name, mtlScene* _scene);
        bool                        switchToScene(const string& _name, mtlSceneTransition _transition = mtlSceneTransitionNone, bool _destroyLast = true);
        bool                        addAndSwitchToScene(const string& _name, mtlScene* _scene, mtlSceneTransition _transition = mtlSceneTransitionNone, bool _destroyLast = true);
        
        void                        onEnterCompleted(int& _status);
        void                        onExitCompleted(int& _status);
    
    private:
        static mtlSceneManager*     sceneManager;
        static unsigned             duration;
        
        map<string, mtlScene*>      scenes;
        string                      currName;
        mtlScene*                   currScene;
        string                      nextName;
        mtlScene*                   nextScene;
        mtlSceneTransition          nextTransition;
        bool                        destroyLast;
    
        ofxTween                    tween;
        ofxEasingQuad               easing;
        float                       target;
    
};