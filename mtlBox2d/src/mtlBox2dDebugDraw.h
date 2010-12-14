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
 *  mtlBox2dDebugDraw.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-11-22.
 *  Based on Box2d iPhone port by Simon Oliver: http://www.simonoliver.com
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
