#pragma once

/*
 *  ModifiedEulerIntegrator.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "Integrator.h"

namespace mtl {
    
    //========================================================================
    class ParticleSystem;
    
    //========================================================================
    class ModifiedEulerIntegrator : public Integrator {
        
    public:
                        ModifiedEulerIntegrator(ParticleSystem* _system);
        
        void            step(float _tick);
        
    private:
        ParticleSystem* system;
        
    };
    
}