/*
 *  ParticleSystem.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "ParticleSystem.h"

namespace mtl {

    //--------------------------------------------------------------
    ParticleSystem::ParticleSystem() {
        clear();
        integrator = new RungeKuttaIntegrator(this);
        gravity.set(0, kDefaultGravity, 0);
        drag = kDefaultDrag;
    }
    
    //--------------------------------------------------------------
    ParticleSystem::ParticleSystem(float _gravityY, float _drag) {
        clear();
        integrator = new RungeKuttaIntegrator(this);
        gravity.set(0, _gravityY, 0);
        drag = _drag;
    }
    
    //--------------------------------------------------------------
    ParticleSystem::ParticleSystem(float _gravityX, float _gravityY, float _gravityZ, float _drag) {
        clear();
        integrator = new RungeKuttaIntegrator(this);
        gravity.set(_gravityX, _gravityY, _gravityZ);
        drag = _drag;
    }
    
    //--------------------------------------------------------------
    ParticleSystem::~ParticleSystem() {
        clear();
    }

    //--------------------------------------------------------------
    void ParticleSystem::setIntegrator(int i) {
        if (integrator) delete integrator;
        switch (i) {
            case kRungeKutta:
                integrator = new RungeKuttaIntegrator(this);
                break;
            case kModifiedEuler:
                integrator = new ModifiedEulerIntegrator(this);
                break;
        }
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::setGravity(float _gravityX, float _gravityY, float _gravityZ) {
        gravity.set(_gravityX, _gravityY, _gravityZ);
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::setGravity(float _gravityY) {
        gravity.set(0, _gravityY, 0);
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::setDrag(float _drag) {
        drag = _drag;
    }

    //--------------------------------------------------------------
    void ParticleSystem::step(float _tick) {
        integrator->step(_tick);
    }

    //--------------------------------------------------------------
    Particle* ParticleSystem::makeParticle(float _mass, float _x, float _y, float _z) {
        Particle* p = new Particle(_mass);
        p->getPosition().set(_x, _y, _z);
        particles.push_back(p);
        return p;
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::getNumParticles() {
        return particles.size();
    }
    
    //--------------------------------------------------------------
    Particle* ParticleSystem::getParticleAt(int i) {
        return particles[i];
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeParticleAt(int i) {
        delete particles[i];
        particles.erase(particles.begin() + i);
    }

    //--------------------------------------------------------------
    Spring* ParticleSystem::makeSpring(Particle* _a, Particle* _b, float _springConstant, float _damping, float _restLength) {
        Spring* s = new Spring(_a, _b, _springConstant, _damping, _restLength);
        springs.push_back(s);
        return s;
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::getNumSprings() {
        return springs.size();
    }
    
    //--------------------------------------------------------------
    Spring* ParticleSystem::getSpringAt(int i) {
        return springs[i];
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeSpringAt(int i) {
        delete springs[i];
        springs.erase(springs.begin() + i);
    }
    
    //--------------------------------------------------------------
    Attraction* ParticleSystem::makeAttraction(Particle* _a, Particle* _b, float _strength, float _minDistance) {
        Attraction* a = new Attraction(_a, _b, _strength, _minDistance);
        attractions.push_back(a);
        return a;
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::getNumAttractions() {
        return attractions.size();
    }
    
    //--------------------------------------------------------------
    Attraction* ParticleSystem::getAttractionAt(int i) {
        return attractions[i];
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeAttractionAt(int i) {
        delete attractions[i];
        attractions.erase(attractions.begin() + i);
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::addCustomForce(Force* _force) {
        customForces.push_back(_force);
    }
    
    //--------------------------------------------------------------
    int ParticleSystem::getNumCustomForces() {
        return customForces.size();
    }
    
    //--------------------------------------------------------------
    Force* ParticleSystem::getCustomForceAt(int i) {
        return customForces[i];
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::removeCustomForceAt(int i) {
        delete customForces[i];
        customForces.erase(customForces.begin() + i);
    }

    //--------------------------------------------------------------
    void ParticleSystem::clear() {
        for (int i=0; i < particles.size(); i++)
            delete particles[i];
        particles.clear();
        
        for (int i=0; i < springs.size(); i++)
            delete springs[i];
        springs.clear();
        
        for (int i=0; i < attractions.size(); i++)
            delete attractions[i];
        attractions.clear();
        
        for (int i=0; i < customForces.size(); i++)
            delete customForces[i];
        customForces.clear();
    }

    //--------------------------------------------------------------
    void ParticleSystem::applyForces() {
        // apply gravity
        if (!(gravity.x == 0 && gravity.y == 0 && gravity.z == 0)) {
            for (int i=0; i < particles.size(); i++) {
                particles[i]->getForce() += gravity;
            }
        }
        
        // apply drag
        for (int i=0; i < particles.size(); i++) {
            particles[i]->getForce() += (particles[i]->getVelocity() * -drag);
        }
        
        // apply springs
        for (int i=0; i < springs.size(); i++) {
            springs[i]->apply();
        }
        
        // apply attractions
        for (int i=0; i < attractions.size(); i++) {
            attractions[i]->apply();
        }
        
        // apply custom forces
        for (int i=0; i < customForces.size(); i++) {
            customForces[i]->apply();
        }
    }
    
    //--------------------------------------------------------------
    void ParticleSystem::clearForces() {
        for (int i=0; i < particles.size(); i++) {
            particles[i]->getForce() = 0;
        }
    }

}