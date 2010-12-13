#pragma once

/*
 *  mtlBox2dBox.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dBaseShape.h"

//========================================================================
class mtlBox2dBox : public mtlBox2dBaseShape {
	
    public:
                        mtlBox2dBox();
                        ~mtlBox2dBox();
        void            setup(b2World* _world, float _x, float _y, float _width, float _height, float _angle = 0, bool _static = false);
        
        //void            debug();
        
    protected:
        float           width, height;
        GLfloat*        dir;
        GLfloat*        verts;
    
};