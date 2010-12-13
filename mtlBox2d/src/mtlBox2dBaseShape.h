#pragma once

/*
 *  mtlBox2dBaseShape.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
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