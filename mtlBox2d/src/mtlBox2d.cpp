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
 *  mtlBox2d.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "mtlBox2d.h"
#include "mtlBox2dHitTestCallback.h"

//--------------------------------------------------------------
mtlBox2d::mtlBox2d() {
    // create the world
    world = new b2World(b2Vec2(0, 0), true);
    world->SetDebugDraw(&debugDraw);
}

//--------------------------------------------------------------
mtlBox2d::~mtlBox2d() {
    delete world;
    world = NULL;
}

//--------------------------------------------------------------
void mtlBox2d::createBounds(float _x, float _y, float _width, float _height) {
    if (!world) {
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
void mtlBox2d::update(float _fps) {
	world->Step(1 / _fps, VEL_ITERATIONS, POS_ITERATIONS);
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
    world->DrawDebugData();
}

//--------------------------------------------------------------
b2World* mtlBox2d::getWorld() {
    return world;
}

//--------------------------------------------------------------
b2Body* mtlBox2d::getBounds() {
    return bounds;
}

//--------------------------------------------------------------
int mtlBox2d::getBodyCount() { 
    return world->GetBodyCount();
}

//--------------------------------------------------------------
int mtlBox2d::getJointCount() { 
    return world->GetJointCount();
}

//--------------------------------------------------------------
void mtlBox2d::enableMouseJoints() {
#ifdef TARGET_OF_IPHONE
	ofAddListener(ofEvents.touchDown,  this, &mtlBox2d::onPress);
	ofAddListener(ofEvents.touchMoved, this, &mtlBox2d::onDrag);
	ofAddListener(ofEvents.touchUp,    this, &mtlBox2d::onRelease);
#else
	ofAddListener(ofEvents.mousePressed,  this, &mtlBox2d::onPress);
	ofAddListener(ofEvents.mouseDragged,  this, &mtlBox2d::onDrag);
	ofAddListener(ofEvents.mouseReleased, this, &mtlBox2d::onRelease);
#endif
}

//--------------------------------------------------------------
void mtlBox2d::disableMouseJoints() {
#ifdef TARGET_OF_IPHONE
	ofRemoveListener(ofEvents.touchDown,  this, &mtlBox2d::onPress);
	ofRemoveListener(ofEvents.touchMoved, this, &mtlBox2d::onDrag);
	ofRemoveListener(ofEvents.touchUp,    this, &mtlBox2d::onRelease);
#else
	ofRemoveListener(ofEvents.mousePressed,  this, &mtlBox2d::onPress);
	ofRemoveListener(ofEvents.mouseDragged,  this, &mtlBox2d::onDrag);
	ofRemoveListener(ofEvents.mouseReleased, this, &mtlBox2d::onRelease);
#endif
}

//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void mtlBox2d::onPress(ofTouchEventArgs &args) {
#else
void mtlBox2d::onPress(ofMouseEventArgs &args) {
#endif
    if (mouseJoint) return;
    
    b2Vec2 mousePt = PIX2M(b2Vec2(args.x, args.y));
    
	// make a small box
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = mousePt - d;
	aabb.upperBound = mousePt + d;
    
	// query the world for overlapping shapes
	mtlBox2dHitTestCallback callback(mousePt);
	world->QueryAABB(&callback, aabb);
    
	if (callback.fixture) {
		b2Body* hitBody = callback.fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = bounds;
		md.bodyB = hitBody;
		md.target = mousePt;
		md.maxForce = 1000.0f * hitBody->GetMass();
		mouseJoint = (b2MouseJoint *)world->CreateJoint(&md);
		hitBody->SetAwake(true);
	}   
}
    
//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void mtlBox2d::onDrag(ofTouchEventArgs &args) {
#else
void mtlBox2d::onDrag(ofMouseEventArgs &args) {
#endif
    if (mouseJoint) {
        b2Vec2 mousePt = PIX2M(b2Vec2(args.x, args.y));
		mouseJoint->SetTarget(mousePt);
	}
}
    
//--------------------------------------------------------------
#ifdef TARGET_OF_IPHONE
void mtlBox2d::onRelease(ofTouchEventArgs &args) {
#else
void mtlBox2d::onRelease(ofMouseEventArgs &args) {
#endif
    if (mouseJoint) {
		world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
}
