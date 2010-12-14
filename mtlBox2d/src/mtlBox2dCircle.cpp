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

