#pragma once

/*
 *  mtlBox2dDebugDraw.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-11-22.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ofMain.h"
#include <Box2D.h>

#define kCircleSegments 16
#define kCircleSlice    M_TWO_PI / (float)kCircleSegments
#define kAxisScale      .4f

//========================================================================
class mtlBox2dDebugDraw : public b2DebugDraw {
    
    public:
                mtlBox2dDebugDraw();
    
        void    DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
        void    DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
        void    DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);
        void    DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
        void    DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
        void    DrawTransform(const b2Transform &xf);
        void    DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color);
        void    DrawString(int x, int y, const char *string, ...);
        void    DrawAABB(b2AABB *aabb, const b2Color &color);
        
};
