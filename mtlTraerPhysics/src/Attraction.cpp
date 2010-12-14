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
 *  Attraction.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 */

#include "Attraction.h"

namespace mtl {
    
    //--------------------------------------------------------------
    Attraction::Attraction(Particle* _a, Particle* _b, float _strength, float _minDistance) {
        a = _a;
        b = _b;
        
        strength = _strength;
        
        minDistance = _minDistance;
        minDistanceSquared = minDistance * minDistance;
        
        on = true;
    }
    
    //--------------------------------------------------------------
    void Attraction::setA(Particle* _particle) {
        a = _particle;
    }
    
    //--------------------------------------------------------------
    Particle* Attraction::getA() {
        return a;
    }
    
    //--------------------------------------------------------------
    void Attraction::setB(Particle* _particle) {
        b = _particle;
    }
    
    //--------------------------------------------------------------
    Particle* Attraction::getB() {
        return b;
    }
    
    //--------------------------------------------------------------
    void Attraction::setMinDistance(float _minDistance) {
        minDistance = _minDistance;
        minDistanceSquared = minDistance * minDistance;
    }
    
    //--------------------------------------------------------------
    float Attraction::getMinDistance() {
        return minDistance;
    }
    
    //--------------------------------------------------------------
    void Attraction::setStrength(float _strength) {
        strength = _strength;
    }
    
    //--------------------------------------------------------------
    float Attraction::getStrength() {
        return strength;
    }
    
    //--------------------------------------------------------------
    void Attraction::turnOn() {
        on = true;
    }
    
    //--------------------------------------------------------------
    void Attraction::turnOff() {
        on = false;
    }
    
    //--------------------------------------------------------------
    bool Attraction::isOn() {
        return on;
    }
    
    //--------------------------------------------------------------
    bool Attraction::isOff() {
        return !on;
    }
    
    //--------------------------------------------------------------
    void Attraction::apply() {
        if (on && (a->isFree() || b->isFree())) {
            ofxVec3f a2b = a->getPosition() - b->getPosition();
            
            float a2bDistanceSquared = a2b.lengthSquared();
            if (a2bDistanceSquared < minDistanceSquared) {
                a2bDistanceSquared = minDistanceSquared;
            }
            
            // make unit vector
            a2b.normalize();
            
            // multiply by force
            float force = strength * a->getMass() * b->getMass() / a2bDistanceSquared;
            a2b *= force;
            
            // apply
            if (a->isFree()) {
                a->getForce() += (a2b * -1);
            }
            if (b->isFree()) {
                b->getForce() += a2b;
            }
        }
    }
    
}