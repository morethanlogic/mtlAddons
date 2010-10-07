/*
 *  mtlBox2dBaseShape.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dBaseShape.h"

//------------------------------------------------
mtlBox2dBaseShape::mtlBox2dBaseShape() {
    dead  = false;
    alive = false;
    fixed = false;
    
    world = NULL;
    body  = NULL;
    
    mass     = 0.0;
    bounce   = 0.0;
    friction = 0.0;
    bodyDef.allowSleep = true;
}		

//------------------------------------------------ 
mtlBox2dBaseShape::~mtlBox2dBaseShape() {
    if (alive) destroyShape();
}

//------------------------------------------------ 
bool mtlBox2dBaseShape::setWorld(b2World* _world) {
    if (_world == NULL) {
		ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() Must have a valid b2World");
		return false;
	}
    
    world = _world;
    return true;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setPhysics(float _mass, float _bounce, float _friction) {
    mass     = _mass; 
    bounce   = _bounce; 
    friction = _friction;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setFilterData(b2FilterData _data) {
    for (b2Shape* s = body->GetShapeList(); s; s = s->GetNext()) {
        s->SetFilterData(_data);
        world->Refilter(s);
    }
}

//------------------------------------------------ 
void mtlBox2dBaseShape::enableGravity(bool b) {
    bodyDef.isGravitated = b;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setFixedRotation(bool b) {
    bodyDef.fixedRotation = b;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setRotationFriction(float f) {
    bodyDef.angularDamping = f;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setDamping(float f) {
    body->SetLinearDamping(f);
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setPosition(b2Vec2 pt) {
    body->SetXForm(pt, 0);
    body->WakeUp();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setPosition(float x, float y) {
    setPosition(b2Vec2(x / BOX2D_SCALE, y / BOX2D_SCALE));
}
                
//------------------------------------------------ 
const b2Vec2 mtlBox2dBaseShape::getPosition() {
    return (BOX2D_SCALE * body->GetPosition());
}

//------------------------------------------------
const b2Vec2& mtlBox2dBaseShape::getB2DPosition() {
    return body->GetPosition();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setVelocity(const b2Vec2& v) {
    if (body != NULL) {
        body->SetLinearVelocity(v);
    }
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setVelocity(float x, float y) {
    setVelocity(b2Vec2(x, y));
}

//------------------------------------------------ 
const b2Vec2& mtlBox2dBaseShape::getVelocity() {
    return body->GetLinearVelocity();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setAngularVelocity(float v) {
    if(body != NULL) {
        body->SetAngularVelocity(v);
    }
}

//------------------------------------------------ 
float mtlBox2dBaseShape::getAngularVelocity() {
    return body->GetAngularVelocity();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::addDamping(float fx, float fy) {
    if (body != NULL) {
        b2Vec2 v = body->GetLinearVelocity();
        v.x *= fx;	
        v.y *= fy;
        body->SetLinearVelocity(v);
    }
}

//------------------------------------------------
void mtlBox2dBaseShape::addDamping(float f) {
    addDamping(f, f);
}

//------------------------------------------------
void mtlBox2dBaseShape::addForce(b2Vec2 pt, b2Vec2 amt) {
    if (body != NULL) {
        body->ApplyForce(b2Vec2(pt.x / BOX2D_SCALE, pt.y / BOX2D_SCALE), amt);
    }
}

//------------------------------------------------
void mtlBox2dBaseShape::addImpulseForce(b2Vec2 pt, b2Vec2 amt) {
    if (body != NULL) {
        body->ApplyImpulse(b2Vec2(pt.x / BOX2D_SCALE, pt.y / BOX2D_SCALE), amt);
    }
}

//------------------------------------------------
void mtlBox2dBaseShape::addAttractionPoint(b2Vec2 pt, float amt, float minDist) {
    if (body != NULL) {
        b2Vec2 P(pt.x / BOX2D_SCALE, pt.y / BOX2D_SCALE);
        b2Vec2 D = P - body->GetPosition(); 
        if (D.LengthSquared() < minDist) {
            P.Normalize();
            b2Vec2 F = amt * D;
            body->ApplyForce(F, P);
        }
    }
}

//------------------------------------------------
void mtlBox2dBaseShape::addAttractionPoint(float x, float y, float amt, float minDist) {
    addAttractionPoint(b2Vec2(x, y), amt, minDist);
}

//------------------------------------------------
void mtlBox2dBaseShape::destroyShape() {
    if (world == NULL) {
        ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() Must have a valid b2World");
        return;
    } else if (!body) {
        ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() NULL body");
        return;
    } else if (dead) {
        ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() Already dead");
        return;
    }
    
    for (b2Shape* s = body->GetShapeList(); s; s = s->GetNext()) {
        body->DestroyShape(s);
    }
    
    world->DestroyBody(body);
    body  = NULL;
    dead  = true;
    alive = false;
}

