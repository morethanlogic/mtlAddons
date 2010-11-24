#pragma once

/*
 *  RungeKuttaIntegrator.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ofxVec3f.h"
#include "Integrator.h"

namespace mtl {
    
    //========================================================================
    class ParticleSystem;
    
    //========================================================================
    class RungeKuttaIntegrator : public Integrator {
        
    public:
                        RungeKuttaIntegrator(ParticleSystem* _system);
        
        void            step(float _tick);
        
    private:
        ParticleSystem* system;
        
        vector<ofxVec3f>    originalPositions;
        vector<ofxVec3f>    originalVelocities;
        vector<ofxVec3f>    k1Forces;
        vector<ofxVec3f>    k1Velocities;
        vector<ofxVec3f>    k2Forces;
        vector<ofxVec3f>    k2Velocities;
        vector<ofxVec3f>    k3Forces;
        vector<ofxVec3f>    k3Velocities;
        vector<ofxVec3f>    k4Forces;
        vector<ofxVec3f>    k4Velocities;
        
    };
    
}