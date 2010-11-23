/*
 *  mtlBox2dCircle.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dCircle.h"

//------------------------------------------------
mtlBox2dCircle::mtlBox2dCircle() : mtlBox2dBaseShape() {
    dir = new GLfloat[4];
}

//------------------------------------------------
mtlBox2dCircle::~mtlBox2dCircle() {
    delete [] dir;
}

//------------------------------------------------
void mtlBox2dCircle::setup(b2World* _world, float _x, float _y, float _radius, float _angle, bool _static) {
    if (!setWorld(_world)) return;
    
    // create a body and add it to the world
    bd.type = _static? b2_staticBody : b2_dynamicBody;
    bd.position.Set(PIX2M(_x), PIX2M(_y));
    bd.angle = _angle;
    
    body = world->CreateBody(&bd);
    
    // add collision shapes to that body
    radius = _radius;
    b2CircleShape m_circle;
    m_circle.m_radius = PIX2M(radius);

    fd.shape = &m_circle;
    fixture = body->CreateFixture(&fd);
}

//------------------------------------------------
void mtlBox2dCircle::debug() {
    if (!body) return;
    
    pos = getPosition();
    
    // draw the shape
    if (fixed) {
        ofSetColor(mtlBox2d::debugFixedColor.r, mtlBox2d::debugFixedColor.g, mtlBox2d::debugFixedColor.b, mtlBox2d::debugFixedColor.a);
    } else {
        ofSetColor(mtlBox2d::debugBodyColor.r, mtlBox2d::debugBodyColor.g, mtlBox2d::debugBodyColor.b, mtlBox2d::debugBodyColor.a);
    }
    ofCircle(pos.x, pos.y, radius);

    // draw the angle vector
    ang = getRotationB2();

    dir[0] = pos.x;
    dir[1] = pos.y;
    dir[2] = pos.x + radius * cosf(ang);
    dir[3] = pos.y + radius * sinf(ang);
    
    ofSetColor(mtlBox2d::debugJointColor.r, mtlBox2d::debugJointColor.g, mtlBox2d::debugJointColor.b, mtlBox2d::debugJointColor.a);
    glEnableClientState(GL_VERTEX_ARRAY);		
    glVertexPointer(2, GL_FLOAT, 0, dir);
    glDrawArrays(GL_LINES, 0, 2);
}

//------------------------------------------------
float mtlBox2dCircle::getRadius() {
    return radius;
}

//------------------------------------------------
void mtlBox2dCircle::setRadius(float _radius) {
    // save the transform parameters
    bd.position = getPosition();
    bd.angle    = getRotation();
    
    // destroy the current body
    world->DestroyBody(body);
    
    // create a body and add it to the world
    body = world->CreateBody(&bd);
    
    // add collision shapes to that body
    radius = _radius;
    b2CircleShape m_circle;
    m_circle.m_radius = PIX2M(radius);
    
    fd.shape = &m_circle;
    fixture = body->CreateFixture(&fd);
}

