#pragma once

/*
 *  Force.h
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

namespace mtl {
    
    //========================================================================
    class Force {
        
    public:
        virtual void    turnOn()  {}
        virtual void    turnOff() {}
        virtual bool    isOn()    {}
        virtual bool    isOff()   {}
        
        virtual void    apply()   {}
    
    };
    
}