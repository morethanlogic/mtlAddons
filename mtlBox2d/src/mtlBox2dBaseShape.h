#pragma once

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
 *  mtlBox2dBaseShape.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 */

#include "mtlBox2d.h"

//========================================================================
class mtlBox2dBaseShape {
    
    public:
                        mtlBox2dBaseShape();
        virtual         ~mtlBox2dBaseShape();
    
        bool            setWorld(b2World* _world);
        void            setPhysics(float _mass, float _friction, float _bounce);
        void            setFilterData(const b2Filter _data);
    
        void            setFixedRotation(bool _fixed);
        bool            isFixedRotation();
    
        void            setAngularDamping(float _damping);
        float           getAngularDamping();
        void            setLinearDamping(float _damping);
        float           getLinearDamping();
        
        void            setPosition(const b2Vec2& _pos);
        void            setPositionB2(const b2Vec2& _pos);
        const b2Vec2    getPosition();
        const b2Vec2&   getPositionB2();
    
        float           getRotation();
        const float     getRotationB2();
    
        void            setLinearVelocity(const b2Vec2& _vel);
        void            setLinearVelocityB2(const b2Vec2& _vel);
        const b2Vec2    getLinearVelocity();
        const b2Vec2    getLinearVelocityB2();
    
        void            setAngularVelocity(float _vel);
        float           getAngularVelocity();
    
        void            applyForce(b2Vec2 _pt, b2Vec2 _amount);
        void            applyForceB2(b2Vec2 _pt, b2Vec2 _amount);
        void            applyLinearImpulse(b2Vec2 _pt, b2Vec2 _amount);
        void            applyLinearImpulseB2(b2Vec2 _pt, b2Vec2 _amount);
        void            applyAngularImpulse(float _amount);
        
        void            destroy();
    
        virtual void    update() {}
        virtual void    draw() {}
    
        b2World*        world;
        b2Body*         body;
        b2Fixture*      fixture;
    
    protected:
        // cached structs
        b2BodyDef       bd;
        b2FixtureDef    fd;
        b2Vec2          pos;
        float           ang;
	
};