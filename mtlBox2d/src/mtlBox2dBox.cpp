/*
 *  mtlBox2dBox.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dBox.h"

//------------------------------------------------
mtlBox2dBox::mtlBox2dBox() {
    dir   = new GLfloat[4];
    verts = new GLfloat[4 * 2];
}

//------------------------------------------------
mtlBox2dBox::~mtlBox2dBox() {
    delete [] dir;
    delete [] verts;
}

//------------------------------------------------
void mtlBox2dBox::setup(b2World* _world, float _x, float _y, float _width, float _height, float _angle, bool _static) {
    if (!setWorld(_world)) return;
    
    // create a body and add it to the world
    bd.type = _static? b2_staticBody : b2_dynamicBody;
    bd.position.Set(PIX2M(_x), PIX2M(_y));
    bd.angle = _angle;
    
    body = world->CreateBody(&bd);
    
    // add collision shapes to that body
    width  = _width;
    height = _height;
    b2PolygonShape m_box;
    m_box.SetAsBox(PIX2M(width/2), PIX2M(height/2));
    
    fd.shape = &m_box;
    fixture = body->CreateFixture(&fd);
}
