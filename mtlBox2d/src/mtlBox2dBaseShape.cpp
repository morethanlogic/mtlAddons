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
 *  mtlBox2dBaseShape.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "mtlBox2dBaseShape.h"

//------------------------------------------------
mtlBox2dBaseShape::mtlBox2dBaseShape() {
    world = NULL;
    body  = NULL;
    
    bd.allowSleep = true;
}		

//------------------------------------------------ 
mtlBox2dBaseShape::~mtlBox2dBaseShape() {
    if (body) destroy();
}

//------------------------------------------------ 
bool mtlBox2dBaseShape::setWorld(b2World* _world) {
    if (!_world) {
		ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() Must have a valid b2World");
		return false;
	}
    
    world = _world;
    return true;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setPhysics(float _mass, float _friction, float _bounce) {
    fd.density     = _mass;
    fd.friction    = _friction;
    fd.restitution = _bounce;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setFilterData(const b2Filter _data) {
    if (fixture)
        fixture->SetFilterData(_data);
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setFixedRotation(bool _fixed) {
    if (body)
        body->SetFixedRotation(_fixed);
    else
        bd.fixedRotation = _fixed;
}

//------------------------------------------------ 
bool mtlBox2dBaseShape::isFixedRotation() {
    if (body)
        return body->IsFixedRotation();
    
    return bd.fixedRotation;
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setAngularDamping(float _damping) {
    if (body)
        body->SetAngularDamping(_damping);
    else
        bd.angularDamping = _damping;
}

//------------------------------------------------
float mtlBox2dBaseShape::getAngularDamping() {
    return body->GetAngularDamping();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setLinearDamping(float _damping) {
    if (body)
        body->SetLinearDamping(_damping);
    else
        bd.linearDamping = _damping;
}

//------------------------------------------------
float mtlBox2dBaseShape::getLinearDamping() {
    return body->GetLinearDamping();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setPosition(const b2Vec2& _pos) {
    body->SetTransform(PIX2M(_pos), 0);
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setPositionB2(const b2Vec2& _pos) {
    body->SetTransform(_pos, 0);
}
                
//------------------------------------------------ 
const b2Vec2 mtlBox2dBaseShape::getPosition() {
    return (BOX2D_SCALE * body->GetPosition());
}

//------------------------------------------------
const b2Vec2& mtlBox2dBaseShape::getPositionB2() {
    return body->GetPosition();
}

//------------------------------------------------
float mtlBox2dBaseShape::getRotation() {
    return RAD2DEG(body->GetAngle());
}

//------------------------------------------------
const float mtlBox2dBaseShape::getRotationB2() {
    return body->GetAngle();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setLinearVelocity(const b2Vec2& _vel) {
    body->SetLinearVelocity(PIX2M(_vel));
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setLinearVelocityB2(const b2Vec2& _vel) {
    body->SetLinearVelocity(_vel);
}

//------------------------------------------------ 
const b2Vec2 mtlBox2dBaseShape::getLinearVelocity() {
    return M2PIX(body->GetLinearVelocity());
}

//------------------------------------------------ 
const b2Vec2 mtlBox2dBaseShape::getLinearVelocityB2() {
    return body->GetLinearVelocity();
}

//------------------------------------------------ 
void mtlBox2dBaseShape::setAngularVelocity(float _vel) {
    body->SetAngularVelocity(_vel);
}

//------------------------------------------------ 
float mtlBox2dBaseShape::getAngularVelocity() {
    return body->GetAngularVelocity();
}

//------------------------------------------------
void mtlBox2dBaseShape::applyForce(b2Vec2 _pt, b2Vec2 _amount) {
    if (body)
        body->ApplyForce(PIX2M(_pt), _amount);
}

//------------------------------------------------
void mtlBox2dBaseShape::applyForceB2(b2Vec2 _pt, b2Vec2 _amount) {
    if (body)
        body->ApplyForce(_pt, _amount);
}

//------------------------------------------------
void mtlBox2dBaseShape::applyLinearImpulse(b2Vec2 _pt, b2Vec2 _amount) {
    if (body)
        body->ApplyLinearImpulse(PIX2M(_pt), _amount);
}

//------------------------------------------------
void mtlBox2dBaseShape::applyLinearImpulseB2(b2Vec2 _pt, b2Vec2 _amount) {
    if (body)
        body->ApplyLinearImpulse(_pt, _amount);
}

//------------------------------------------------
void mtlBox2dBaseShape::applyAngularImpulse(float _amount) {
    if (body)
        body->ApplyAngularImpulse(_amount);
}

//------------------------------------------------
void mtlBox2dBaseShape::destroy() {
    if (!world) {
        ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() Must have a valid b2World");
        return;
    } else if (!body) {
        ofLog(OF_LOG_WARNING, "mtlBox2dBaseShape::setWorld() NULL body");
        return;
    }
    
    world->DestroyBody(body);
    body  = NULL;
}

