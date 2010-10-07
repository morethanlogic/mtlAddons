#pragma once

/*
 *  mtlBox2dRect.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dBaseShape.h"

//========================================================================
class mtlBox2dRect : public mtlBox2dBaseShape {
	
    public:
                        mtlBox2dRect();
                        ~mtlBox2dRect();
        void            setup(b2World* _world, float _x, float _y, float _width, float _height, float _ang = 0, bool _fixed = false);
        
        void            draw();
        
    protected:
        b2PolygonDef    rect;
        GLfloat*        verts;
    
};