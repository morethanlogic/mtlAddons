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
 *  RungeKuttaIntegrator.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 */

#include "RungeKuttaIntegrator.h"

#include "Particle.h"
#include "ParticleSystem.h"

namespace mtl {
    
    //--------------------------------------------------------------
    RungeKuttaIntegrator::RungeKuttaIntegrator(ParticleSystem* _system) {
        system = _system;
    }
    
    //--------------------------------------------------------------
    void RungeKuttaIntegrator::step(float _tick) {
        // allocate particles
        while (system->getNumParticles() > originalPositions.size()) {
            ofxVec3f v;
            originalPositions.push_back(v);
            originalVelocities.push_back(v);
            k1Forces.push_back(v);
            k1Velocities.push_back(v);
            k2Forces.push_back(v);
            k2Velocities.push_back(v);
            k3Forces.push_back(v);
            k3Velocities.push_back(v);
            k4Forces.push_back(v);
            k4Velocities.push_back(v);
        }
        
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                // save original positions and velocities
                originalPositions[i].set(p->getPosition());
                originalVelocities[i].set(p->getVelocity());
            }
            
            // clear the forces
            p->getForce() = 0;
        }
        
        // get the k1 values
        system->applyForces();
        
        // save the intermediate forces
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                k1Forces[i].set(p->getForce());
                k1Velocities[i].set(p->getVelocity());
            }
            
            // clear the forces
            p->getForce() = 0;
        }
        
        // get the k2 values
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                p->getPosition() = originalPositions[i] + (k1Velocities[i] * (.5f * _tick));
                p->getVelocity() = originalVelocities[i] + (k1Forces[i] * (.5f * _tick / p->getMass()));
            }
        }
        
        system->applyForces();
        
        // save the intermediate forces
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                k2Forces[i].set(p->getForce());
                k2Velocities[i].set(p->getVelocity());
            }
            
            // clear the forces
            p->getForce() = 0;
        }
        
        // get the k3 values
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                p->getPosition() = originalPositions[i] + (k2Velocities[i] * (.5f * _tick));
                p->getVelocity() = originalVelocities[i] + (k2Forces[i] * (.5f * _tick / p->getMass()));
            }
        }
        
        system->applyForces();
        
        // save the intermediate forces
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                k3Forces[i].set(p->getForce());
                k3Velocities[i].set(p->getVelocity());
            }
            
            // clear the forces
            p->getForce() = 0;
        }
        
        // get the k4 values
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                p->getPosition() = originalPositions[i] + (k3Velocities[i] * _tick);
                p->getVelocity() = originalVelocities[i] + (k3Forces[i] * (_tick / p->getMass()));
            }
        }
        
        system->applyForces();
        
        // save the intermediate forces
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            if (p->isFree()) {
                k4Forces[i].set(p->getForce());
                k4Velocities[i].set(p->getVelocity());
            }
        }
        
        // put it all together
        for (int i=0; i < system->getNumParticles(); i++) {
            Particle* p = system->getParticleAt(i);
            p->addAge(_tick);
            
            if (p->isFree()) {
                p->getPosition() = originalPositions[i] + _tick / 6.f * (k1Velocities[i] + k2Velocities[i] * 2.f + k3Velocities[i] * 2.f + k4Velocities[i]);
                p->getVelocity() = originalVelocities[i] + _tick / (6.f * p->getMass()) * (k1Forces[i] + k2Forces[i] * 2.f + k3Forces[i] * 2.f + k4Forces[i]);
            }
        }
    }
    
}