#pragma once

/*
 *  Spring.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "Force.h"
#include "Particle.h"

namespace mtl {
    
    //========================================================================
    class Spring : public Force {
        
    public: 
                    Spring(Particle* _a, Particle* _b, float _springConstant, float _damping, float _restLength);
        
        void        setA(Particle* _particle);
        Particle*   getA();
        void        setB(Particle* _particle);
        Particle*   getB();
        
        void        setSpringConstant(float _springConstant);
        float       getSpringConstant();
        
        void        setDamping(float _damping);
        float       getDamping();
        
        void        setRestLength(float _restLength);
        float       getRestLength();
        
        float       getCurrentLength();
        
        void        turnOn();
        void        turnOff();
        bool        isOn();
        bool        isOff();
        
        void        apply();
        
    private:
        Particle*   a;
        Particle*   b;
        float       springConstant;
        float       damping;
        float       restLength;
        bool        on;
        
    };
    
}

