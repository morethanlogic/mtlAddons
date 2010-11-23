#pragma once

/*
 *  mtlBox2d.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ofMain.h"

#include <Box2D.h>
#include "mtlBox2dDebugDraw.h"

#define BOX2D_SCALE     30.f
#define FPS             30
#define TIMESTEP        1.f / FPS
#define VEL_ITERATIONS  8
#define POS_ITERATIONS  3

#define M2PIX(m)        (BOX2D_SCALE * m)
#define PIX2M(p)        ((1.f / BOX2D_SCALE) * p)
#define DEG2RAD(d)      (d * M_PI / 180.f)
#define RAD2DEG(r)      (r * 180.f / M_PI)

//========================================================================
// In order to deal with the two coordinate systems (pixels and meters),
// any data passed or returned to any mtlXXX object is assumed to be in
// pixels, unless the method has the "B2" suffix in its name. For 
// rotations, the data is assumed to be in degrees, or in radians if the
// method has the "B2" suffix.
class mtlBox2d {
    
    public:
                    mtlBox2d();
                    ~mtlBox2d();
    
        void        createBounds(float _x, float _y, float _width, float _height);
    
        void        update();
        void        debug();
        
        void        setGravity(const b2Vec2& _gravity);
        void        setGravityB2(const b2Vec2& _gravity);
        b2Vec2      getGravity() const;
        b2Vec2      getGravityB2() const;
        
        b2World*    getWorld();
        int			getBodyCount();
        int			getJointCount();
    
        void        enableMouseJoints();
        void        disableMouseJoints();
    
#ifdef TARGET_OF_IPHONE
        void        onPress(ofTouchEventArgs &args);
        void        onDrag(ofTouchEventArgs &args);
        void        onRelease(ofTouchEventArgs &args);
#else
        void        onPress(ofMouseEventArgs &args);
        void        onDrag(ofMouseEventArgs &args);
        void        onRelease(ofMouseEventArgs &args);
#endif
        
    private:
        b2World             *world;
        b2Body              *bounds;
        b2MouseJoint        *mouseJoint;
        mtlBox2dDebugDraw   debugDraw;

};

