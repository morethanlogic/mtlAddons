#pragma once

/*
 *  mtlBaseScene.h
 *  mtlSceneManager
 *
 *  Created by Hugues Bruyere on 10-09-19.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "ofMain.h"

//========================================================================
class mtlScene {
	
    public:
                        mtlScene();
        virtual         ~mtlScene();
            
                void    _enter();
                void    _exit();
        virtual void    _draw();
    
        virtual void	enter()  {}
        virtual void	exit()   {}
        virtual void	update() {}
        virtual void	draw()   {}
    
                void    enableTouchEvents();
                void    disableTouchEvents();
    
        virtual void    touchDown(ofTouchEventArgs& _touch) {}
        virtual void    touchMoved(ofTouchEventArgs& _touch) {}
        virtual void    touchUp(ofTouchEventArgs& _touch) {}
        virtual void    touchDoubleTap(ofTouchEventArgs& _touch) {}    
        
        // events
        ofEvent<int>    enterCompleted;
        ofEvent<int>    exitCompleted;
    
        int             status;
    
        float           x;
        float           y;
        float           width;
        float           height;
        float           alpha;
	
};