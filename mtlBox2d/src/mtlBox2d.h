#pragma once

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
 *  mtlBox2d.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "ofMain.h"

#include <Box2D.h>
#include "mtlBox2dDebugDraw.h"

#define BOX2D_SCALE     30.f
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
        b2Body*     getBounds();
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

