#pragma once

/*
 *  Particle.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ofxVec3f.h"

namespace mtl {
    
    //========================================================================
    class Particle {
        
    public:
                    Particle(float _mass);
        
        float       distanceTo(Particle* _particle);
        
        void        makeFixed();
        bool        isFixed();
        void        makeFree();
        bool        isFree();
        
        ofxVec3f&   getPosition();
        ofxVec3f&   getVelocity();
        float       getMass();
        void        setMass(float _mass);
        ofxVec3f&   getForce();
        float       getAge();
        void        addAge(float _add);
        
        void        reset();
        
    protected:
        ofxVec3f    position;
        ofxVec3f    velocity;
        ofxVec3f    force;
        
        float       mass;
        float       age;
        bool        dead;
        
        bool        fixed;
        
    };
    
}