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
 *  mtlBox2dCircle.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
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

