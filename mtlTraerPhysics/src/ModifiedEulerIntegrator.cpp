/*
 *  ModifiedEulerIntegrator.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ModifiedEulerIntegrator.h"

#include "Particle.h"
#include "ParticleSystem.h"

namespace mtl {
    
    //--------------------------------------------------------------
    ModifiedEulerIntegrator::ModifiedEulerIntegrator(ParticleSystem* _system) {
        system = _system;
    }
    
    //--------------------------------------------------------------
    void ModifiedEulerIntegrator::step(float _tick) {
        system->clearForces();
        system->applyForces();
        
        float halftt = .5f * _tick * _tick;
        
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                ofxVec3f a = p->getForce();
                a /= p->getMass();
                
                p->getPosition() += (p->getVelocity() / _tick);
                p->getPosition() += (a * halftt);
                p->getVelocity() += (a / _tick);
            }
        }
    }
    
}

