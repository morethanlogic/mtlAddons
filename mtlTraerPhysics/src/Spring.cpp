/*
 *  Spring.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
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