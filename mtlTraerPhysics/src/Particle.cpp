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
 *  Particle.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 */

#include "Particle.h"

namespace mtl {
    
    //--------------------------------------------------------------
    Particle::Particle(float _mass) {
        mass  = _mass;
        fixed = false;
        age   = 0;
        dead  = false;
    }

    //--------------------------------------------------------------
    float Particle::distanceTo(Particle* _particle) {
        return position.distance(_particle->getPosition());
    }

    //--------------------------------------------------------------
    void Particle::makeFixed() {
        fixed    = true;
        velocity = 0;
    }

    //--------------------------------------------------------------
    bool Particle::isFixed() {
        return fixed;
    }

    //--------------------------------------------------------------
    void Particle::makeFree() {
        fixed = false;
    }

    //--------------------------------------------------------------
    bool Particle::isFree() {
        return !fixed;
    }

    //--------------------------------------------------------------
    ofxVec3f& Particle::getPosition() {
        return position;
    }

    //--------------------------------------------------------------
    ofxVec3f& Particle::getVelocity() {
        return velocity;
    }

    //--------------------------------------------------------------
    float Particle::getMass() {
        return mass;
    }

    //--------------------------------------------------------------
    void Particle::setMass(float _mass) {
        mass = _mass;
    }

    //--------------------------------------------------------------
    ofxVec3f& Particle::getForce() {
        return force;
    }

    //--------------------------------------------------------------
    float Particle::getAge() {
        return age;
    }
    
    //--------------------------------------------------------------
    void Particle::addAge(float _add) {
        age += _add;
    }

    //--------------------------------------------------------------
    void Particle::reset() {
        age      = 0;
        dead     = false;
        position = 0;
        velocity = 0;
        force    = 0;
        mass     = 1.f;
    }
    
}
