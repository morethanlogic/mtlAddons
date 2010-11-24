#pragma once

/*
 *  Integrator.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

namespace mtl {
    
    //========================================================================
    class Integrator {
        
    public:
        virtual void    step(float _tick) {}
        
    };
    
}
