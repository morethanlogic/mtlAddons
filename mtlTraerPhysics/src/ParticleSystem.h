#pragma once

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
 *  ParticleSystem.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
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