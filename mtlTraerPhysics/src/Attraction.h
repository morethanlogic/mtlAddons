#pragma once

/*
 *  Attraction.h
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
    class Attraction : public Force {
        
    public: 
                    Attraction(Particle* _a, Particle* _b, float _strength, float _minDistance);
        
        void        setA(Particle* _particle);
        Particle*   getA();
        void        setB(Particle* _particle);
        Particle*   getB();
        
        void        setMinDistance(float _minDistance);
        float       getMinDistance();
        
        void        setStrength(float _strength);
        float       getStrength();
        
        void        turnOn();
        void        turnOff();
        bool        isOn();
        bool        isOff();
        
        void        apply();
        
    private:
        Particle*   a;
        Particle*   b;
        float       strength;
        bool        on;
        float       minDistance;
        float       minDistanceSquared;
        
    };
    
}