/*
 *  mtlBox2d.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2d.h"

//--------------------------------------------------------------
ofColor mtlBox2d::debugBodyColor;
ofColor mtlBox2d::debugJointColor;
ofColor mtlBox2d::debugFixedColor;

//--------------------------------------------------------------
void mtlBox2d::setDebugColors(int _bodyR,  int _bodyG,  int _bodyB,  int _bodyA,
                              int _jointR, int _jointG, int _jointB, int _jointA,
                              int _fixedR, int _fixedG, int _fixedB, int _fixedA) {
    debugBodyColor.r  = _bodyR;
    debugBodyColor.g  = _bodyG;
    debugBodyColor.b  = _bodyB;
    debugBodyColor.a  = _bodyA;
    
    debugJointColor.r = _jointR;
    debugJointColor.g = _jointG;
    debugJointColor.b = _jointB;
    debugJointColor.a = _jointA;
    
    debugFixedColor.r = _fixedR;
    debugFixedColor.g = _fixedG;
    debugFixedColor.b = _fixedB;
    debugFixedColor.a = _fixedA;
}

//--------------------------------------------------------------
mtlBox2d::mtlBox2d() {
    // create the world
    world = new b2World(b2Vec2(0, 0), true);
    
    setDebugColors(204,   0,   0, 255, 
                   252, 213,  10, 255,
                   255, 255, 255, 255);
}

//--------------------------------------------------------------
mtlBox2d::~mtlBox2d() {
    delete world;
    world = NULL;
}

//--------------------------------------------------------------
void mtlBox2d::createBounds(float _x, float _y, float _width, float _height) {
    if (world == NULL) {
        ofLog(OF_LOG_WARNING, "mtlBox2d::createBounds() Must have a valid b2World");
		return;
    }
    
    b2BodyDef bd;
    bounds = world->CreateBody(&bd);
    
    b2PolygonShape shape;
    
    // bottom
    shape.SetAsEdge(b2Vec2(0,0), b2Vec2(PIX2M(_width),0));
    bounds->CreateFixture(&shape, 0.0f);
    
    // top
    shape.SetAsEdge(b2Vec2(0,PIX2M(_height)), b2Vec2(PIX2M(_width),PIX2M(_height)));
    bounds->CreateFixture(&shape, 0.0f);
    
    // left
    shape.SetAsEdge(b2Vec2(0,PIX2M(_height)), b2Vec2(0, 0));
    bounds->CreateFixture(&shape, 0.0f);
    
    // right
    shape.SetAsEdge(b2Vec2(PIX2M(_width),PIX2M(_height)), b2Vec2(PIX2M(_width),0));
    bounds->CreateFixture(&shape, 0.0f);
}

//--------------------------------------------------------------
void mtlBox2d::update() {
	world->Step(TIMESTEP, VEL_ITERATIONS, POS_ITERATIONS);
}

//--------------------------------------------------------------
void mtlBox2d::setGravity(const b2Vec2& _gravity) {
    world->SetGravity(PIX2M(_gravity));
}

//--------------------------------------------------------------
void mtlBox2d::setGravityB2(const b2Vec2& _gravity) {
    world->SetGravity(_gravity);
}

//--------------------------------------------------------------
b2Vec2 mtlBox2d::getGravity() const {
    return M2PIX(world->GetGravity());
}

//--------------------------------------------------------------
b2Vec2 mtlBox2d::getGravityB2() const {
    return world->GetGravity();
}

//--------------------------------------------------------------
void mtlBox2d::debug() {
}

//--------------------------------------------------------------
b2World* mtlBox2d::getWorld() {
    return world;
}

//--------------------------------------------------------------
int mtlBox2d::getBodyCount() { 
    return world->GetBodyCount();
}

//--------------------------------------------------------------
int mtlBox2d::getJointCount() { 
    return world->GetJointCount();
}
