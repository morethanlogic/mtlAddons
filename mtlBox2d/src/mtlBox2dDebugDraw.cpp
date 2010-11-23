/*
 *  mtlBox2dDebugDraw.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-11-22.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dDebugDraw.h"
#include "mtlBox2d.h"

//--------------------------------------------------------------
mtlBox2dDebugDraw::mtlBox2dDebugDraw() {
    SetFlags(1 * e_shapeBit | 
             0 * e_jointBit | 
             0 * e_aabbBit  |
             1 * e_pairBit  | 
             1 * e_centerOfMassBit);
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertexCount; i++) {
        glVertex2f(M2PIX(vertices[i].x), M2PIX(vertices[i].y));
    }
    glEnd();
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
    glColor4f(color.r, color.g, color.b, .5f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < vertexCount; i++) {
        glVertex2f(M2PIX(vertices[i].x), M2PIX(vertices[i].y));
    }
    glEnd();
    
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < vertexCount; ++i) {
        glVertex2f(M2PIX(vertices[i].x), M2PIX(vertices[i].y));
    }
    glEnd();
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) {
    float ang = 0.f;
    
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < kCircleSegments; i++) {
        b2Vec2 v = M2PIX(center) + M2PIX(radius) * b2Vec2(cosf(ang), sinf(ang));
        glVertex2f(v.x, v.y);
        ang += kCircleSlice;
    }
    glEnd();
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) {
    float ang = 0.f;
    
    glColor4f(color.r, color.g, color.b, .5f);
//    ofCircle(M2PIX(center.x), M2PIX(center.y), M2PIX(radius));
    glBegin(GL_TRIANGLE_FAN);
    for (int32 i = 0; i < kCircleSegments; i++) {
        b2Vec2 v = M2PIX(center) + M2PIX(radius) * b2Vec2(cosf(ang), sinf(ang));
        glVertex2f(v.x, v.y);
        ang += kCircleSlice;
    }
    glEnd();
    
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < kCircleSegments; i++) {
        b2Vec2 v = M2PIX(center) + M2PIX(radius) * b2Vec2(cosf(ang), sinf(ang));
        glVertex2f(v.x, v.y);
        ang += kCircleSlice;
    }
    glEnd();

    // TODO: Fix this axis thing, it's rendering funny
//    b2Vec2 p = M2PIX(center + radius * axis);
//    glBegin(GL_LINES);
//    {
//        glVertex2f(center.x, center.y);
//        glVertex2f(p.x, p.y);
//    }
//    glEnd();
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) {
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINES);
    {
        glVertex2f(M2PIX(p1.x), M2PIX(p1.y));
        glVertex2f(M2PIX(p2.x), M2PIX(p2.y));
    }
    glEnd();
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawTransform(const b2Transform &xf) {
    b2Vec2 p1 = M2PIX(xf.position);
    b2Vec2 p2;
    
    glBegin(GL_LINES);
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(p1.x, p1.y);
        p2 = p1 + M2PIX(kAxisScale * xf.R.col1);
        glVertex2f(p2.x, p2.y);
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(p1.x, p1.y);
        p2 = p1 + M2PIX(kAxisScale * xf.R.col2);
        glVertex2f(p2.x, p2.y);
    }
    glEnd();
}

//--------------------------------------------------------------
void mtlBox2dDebugDraw::DrawPoint(const b2Vec2 &p, float32 size, const b2Color &color) {
    glColor3f(color.r, color.g, color.b);
    glPointSize(size);
    glBegin(GL_POINTS);
    {
        glVertex2f(M2PIX(p.x), M2PIX(p.y));
    }
    glEnd();
    glPointSize(1.0f);
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
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    {
        glVertex2f(M2PIX(aabb->lowerBound.x), M2PIX(aabb->lowerBound.y));
        glVertex2f(M2PIX(aabb->upperBound.x), M2PIX(aabb->lowerBound.y));
        glVertex2f(M2PIX(aabb->upperBound.x), M2PIX(aabb->upperBound.y));
        glVertex2f(M2PIX(aabb->lowerBound.x), M2PIX(aabb->upperBound.y));
    }
    glEnd();
}


