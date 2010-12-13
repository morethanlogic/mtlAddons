#pragma once

/*
 *  ParticleSystem.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "Attraction.h"
#include "Force.h"
#include "Integrator.h"
#include "ModifiedEulerIntegrator.h"
#include "Particle.h"
#include "RungeKuttaIntegrator.h"
#include "Spring.h"

namespace mtl {
    
    #define kRungeKutta     0
    #define kModifiedEuler  1
        
    #define kDefaultGravity 0.f
    #define kDefaultDrag    .001f;
    
    //========================================================================
    class ParticleSystem {
        
    public:
                            ParticleSystem();
                            ParticleSystem(float _gravityY, float _drag);
                            ParticleSystem(float _gravityX, float _gravityY, float _gravityZ, float _drag);
        
                            ~ParticleSystem();
        
        void                setIntegrator(int i);
        void                setGravity(float _gravityX, float _gravityY, float _gravityZ);
        void                setGravity(float _gravityY);
        void                setDrag(float _drag);
        
        void                step(float _tick = 1);
        
        Particle*           makeParticle(float _mass = 1.f, float _x = 0.f, float _y = 0.f, float _z = 0.f);
        int                 getNumParticles();
        Particle*           getParticleAt(int i);
        void                removeParticleAt(int i);
        
        Spring*             makeSpring(Particle* _a, Particle* _b, float _springConstant, float _damping);
        Spring*             makeSpring(Particle* _a, Particle* _b, float _springConstant, float _damping, float _restLength);
        int                 getNumSprings();
        Spring*             getSpringAt(int i);
        void                removeSpringAt(int i);
        
        Attraction*         makeAttraction(Particle* _a, Particle* _b, float _strength, float _minDistance);
        int                 getNumAttractions();
        Attraction*         getAttractionAt(int i);
        void                removeAttractionAt(int i);
        
        void                addCustomForce(Force* _force);
        int                 getNumCustomForces();
        Force*              getCustomForceAt(int i);
        void                removeCustomForceAt(int i);
        
        void                clear();
        
        void                applyForces();
        void                clearForces();
        
    private:
        vector<Particle*>   particles;
        vector<Spring*>     springs;
        vector<Attraction*> attractions;
        vector<Force*>      customForces;
        
        Integrator*         integrator;
        
        ofxVec3f            gravity;
        float               drag;
        
        bool                hasDeadParticles;
        
    };
    
}