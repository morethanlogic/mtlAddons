/*
 *  Attraction.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
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