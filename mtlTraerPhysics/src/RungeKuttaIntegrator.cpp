/*
 *  RungeKuttaIntegrator.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
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