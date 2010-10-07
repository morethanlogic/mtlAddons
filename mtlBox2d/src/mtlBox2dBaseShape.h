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
                        ~mtlBox2dBaseShape();
    
        bool            setWorld(b2World* _world);
        void            setPhysics(float _mass, float _bounce, float _friction);
        void            setFilterData(b2FilterData _data);
    
        void            enableGravity(bool b);
        void            setFixedRotation(bool b);
    
        void            setRotationFriction(float f);
        void            setDamping(float f);
    
        void            setPosition(b2Vec2 pt);
        void            setPosition(float x, float y);
        const b2Vec2    getPosition();
        const b2Vec2&   getB2DPosition();
    
        void            setVelocity(const b2Vec2& v);
        void            setVelocity(float x, float y);
        const b2Vec2&   getVelocity();
    
        void            setAngularVelocity(float v);
        float           getAngularVelocity();
    
        void            addDamping(float fx, float fy);
        void            addDamping(float f);
        void            addForce(b2Vec2 pt, b2Vec2 amt);
        void            addImpulseForce(b2Vec2 pt, b2Vec2 amt);
        void            addAttractionPoint(b2Vec2 pt, float amt, float minDist = 0);
        void            addAttractionPoint(float x, float y, float amt, float minDist = 0);
    
        void            destroyShape();
    
        virtual void    update() {}
        virtual void    draw() {}
    
        b2World*        world;
        b2Body*         body;
    
    protected:
        b2BodyDef       bodyDef;
        
        bool            dead;
        bool            alive;
        bool            fixed;
        
        float           mass;
        float           bounce;
        float           friction;
	
};