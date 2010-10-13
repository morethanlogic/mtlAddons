#pragma once

/*
 *  mtlBox2dCircle.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dBaseShape.h"

//========================================================================
class mtlBox2dCircle : public mtlBox2dBaseShape {
	
    public:
                    mtlBox2dCircle();
                    ~mtlBox2dCircle();
        void        setup(b2World* _world, float _x, float _y, float _size, float _ang = 0, bool _fixed = false);
    
        void        draw();
    
        float       getRadius();
        float       getRotation();
        void        disableCollision();
        void        setRadius(float _radius);
    
    protected:
        b2CircleDef circle;
        GLfloat*    dirVector;
    
};
