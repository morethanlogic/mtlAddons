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
