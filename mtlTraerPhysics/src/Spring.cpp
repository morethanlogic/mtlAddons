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
 *  Spring.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 */

#include "Spring.h"

namespace mtl {
    
    //--------------------------------------------------------------
    Spring::Spring(Particle* _a, Particle* _b, float _springConstant, float _damping, float _restLength) {
        a = _a;
        b = _b;
        
        springConstant = _springConstant;
        damping        = _damping;
        restLength     = _restLength;
        
        on = true;
    }
    
    //--------------------------------------------------------------
    void Spring::setA(Particle* _particle) {
        a = _particle;
    }
    
    //--------------------------------------------------------------
    Particle* Spring::getA() {
        return a;
    }
    
    //--------------------------------------------------------------
    void Spring::setB(Particle* _particle) {
        b = _particle;
    }
    
    //--------------------------------------------------------------
    Particle* Spring::getB() {
        return b;
    }
    
    //--------------------------------------------------------------
    void Spring::setSpringConstant(float _springConstant) {
        springConstant = _springConstant;
    }
    
    //--------------------------------------------------------------
    float Spring::getSpringConstant() {
        return springConstant;
    }
    
    //--------------------------------------------------------------
    void Spring::setDamping(float _damping) {
        damping = _damping;
    }
    
    //--------------------------------------------------------------
    float Spring::getDamping() {
        return damping;
    }
    
    //--------------------------------------------------------------
    void Spring::setRestLength(float _restLength) {
        restLength = _restLength;
    }
    
    //--------------------------------------------------------------
    float Spring::getRestLength() {
        return restLength;
    }
    
    //--------------------------------------------------------------
    float Spring::getCurrentLength() {
        return a->distanceTo(b);
    }
    
    //--------------------------------------------------------------
    void Spring::turnOn() {
        on = true;
    }
    
    //--------------------------------------------------------------
    void Spring::turnOff() {
        on = false;
    }
    
    //--------------------------------------------------------------
    bool Spring::isOn() {
        return on;
    }
    
    //--------------------------------------------------------------
    bool Spring::isOff() {
        return !on;
    }
    
    //--------------------------------------------------------------
    void Spring::apply() {
        if (on && (a->isFree() || b->isFree())) {
            ofxVec3f a2b = a->getPosition() - b->getPosition();
            
            float a2bDistance = a2b.length();
            if (a2bDistance == 0) {
                a2b = 0;
            } else {
                a2b.normalize();
            }
            
            // spring force is proportional to how much it stretched 
            float springForce = -1 * (a2bDistance - restLength) * springConstant;
            
            // we want velocity along line b/w a & b, damping force is proportional to this
            ofxVec3f vel = a->getVelocity() - b->getVelocity();
            float dampingForce = -damping * a2b.dot(vel);
            
            // force B is the same as force A in opposite direction
            a2b *= (springForce + dampingForce);
            
            // apply
            if (a->isFree()) {
                a->getForce() += a2b;
            }
            if (b->isFree()) {
                b->getForce() += (a2b * -1);
            }
        }
    }
    
}