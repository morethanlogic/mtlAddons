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
 *  mtlBox2dDebugDraw.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-11-22.
 *  Based on Box2d iPhone port by Simon Oliver: http://www.simonoliver.com
 */

#include "mtlBox2dDebugDraw.h"
#include "mtlBox2d.h"

//--------------------------------------------------------------
mtlBox2dDebugDraw::mtlBox2dDebugDraw() {
    SetFlags(1 * e_shapeBit | 
             1 * e_jointBit | 
             0 * e_aabbBit  |
             0 * e_pairBit  | 
             1 * e_centerOfMassBit);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    GLfloat	verts[vertexCount*2];
    for (int32 i = 0; i < vertexCount; i++) {
        verts[i*2+0] = M2PIX(vertices[i].x);
		verts[i*2+1] = M2PIX(vertices[i].y);
    }
    glVertexPointer(2, GL_FLOAT, 0, verts);
	
    glColor4f(color.r, color.g, color.b, 1.f);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    GLfloat	verts[vertexCount*2];
    for (int32 i = 0; i < vertexCount; i++) {
        verts[i*2+0] = M2PIX(vertices[i].x);
		verts[i*2+1] = M2PIX(vertices[i].y);
    }
    glVertexPointer(2, GL_FLOAT, 0, verts);
    
    glColor4f(color.r, color.g, color.b, .5f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    
    glColor4f(color.r, color.g, color.b, 1.f);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
    float ang = 0.f;
    GLfloat	verts[kCircleSegments*2];
    for (int32 i = 0; i < kCircleSegments; i++) {
        b2Vec2 v = M2PIX(center) + M2PIX(radius) * b2Vec2(cosf(ang), sinf(ang));
        verts[i*2+0] = v.x;
		verts[i*2+1] = v.y;
        ang += kCircleSlice;
    }
    glVertexPointer(2, GL_FLOAT, 0, verts);
	
    glColor4f(color.r, color.g, color.b, 1.f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, kCircleSegments);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
    float ang = 0.f;
    GLfloat	verts[kCircleSegments*2];
    for (int32 i = 0; i < kCircleSegments; i++) {
        b2Vec2 v = M2PIX(center) + M2PIX(radius) * b2Vec2(cosf(ang), sinf(ang));
        verts[i*2+0] = v.x;
		verts[i*2+1] = v.y;
        ang += kCircleSlice;
    }
    glVertexPointer(2, GL_FLOAT, 0, verts);

    glColor4f(color.r, color.g, color.b, .5f);
    glDrawArrays(GL_TRIANGLE_FAN, 0, kCircleSegments);
    
    glColor4f(color.r, color.g, color.b, 1.f);
	glDrawArrays(GL_LINE_LOOP, 0, kCircleSegments);
	
	// draw the axis line
	DrawSegment(center, center + radius*axis, color);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
    GLfloat	verts[] = { M2PIX(p1.x), M2PIX(p1.y), 
                        M2PIX(p2.x), M2PIX(p2.y) };
    glVertexPointer(2, GL_FLOAT, 0, verts);
	
    glColor4f(color.r, color.g, color.b, 1.f);
    glDrawArrays(GL_LINES, 0, 2);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawTransform(const b2Transform &xf) {
    b2Vec2 p1 = xf.position;
    b2Vec2 p2;
    
    p2 = p1 + kAxisScale * xf.R.col1;
	DrawSegment(p1, p2, b2Color(1, 0, 0));
	
	p2 = p1 + kAxisScale * xf.R.col2;
	DrawSegment(p1, p2, b2Color(0, 1, 0));
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) {
    GLfloat	verts[] = { M2PIX(p.x), M2PIX(p.y) };
    glVertexPointer(2, GL_FLOAT, 0, verts);
    
    glPointSize(size);
    glColor4f(color.r, color.g, color.b, 1.f);
    glDrawArrays(GL_POINTS, 0, 1);
    glPointSize(1.f);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawString(int x, int y, const char *string, ...) {
    //            char buffer[128];
    //            
    //            va_list arg;
    //            va_start(arg, string);
    //            vsprintf(buffer, string, arg);
    //            va_end(arg);
    //            
    //            glMatrixMode(GL_PROJECTION);
    //            glPushMatrix();
    //            glLoadIdentity();
    //            int w = glutGet(GLUT_WINDOW_WIDTH);
    //            int h = glutGet(GLUT_WINDOW_HEIGHT);
    //            gluOrtho2D(0, w, h, 0);
    //            glMatrixMode(GL_MODELVIEW);
    //            glPushMatrix();
    //            glLoadIdentity();
    //            
    //            glColor3f(0.9f, 0.6f, 0.6f);
    //            glRasterPos2i(x, y);
    //            int32 length = (int32)strlen(buffer);
    //            for (int32 i = 0; i < length; ++i)
    //            {
    //                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
    //            }
    //            
    //            glPopMatrix();
    //            glMatrixMode(GL_PROJECTION);
    //            glPopMatrix();
    //            glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawAABB(b2AABB *aabb, const b2Color &color) {
    GLfloat	verts[] = { M2PIX(aabb->lowerBound.x), M2PIX(aabb->lowerBound.y),
                        M2PIX(aabb->upperBound.x), M2PIX(aabb->lowerBound.y),
                        M2PIX(aabb->upperBound.x), M2PIX(aabb->upperBound.y),
                        M2PIX(aabb->lowerBound.x), M2PIX(aabb->upperBound.y) };
    glVertexPointer(2, GL_FLOAT, 0, verts);
	
    glColor4f(color.r, color.g, color.b, 1.f);
    glDrawArrays(GL_LINE_LOOP, 0, 8);
}


