/*
 *  Particle.cpp
 *  mtlTraerPhysics
 *
 *  Created by Elie Zananiri on 10-11-23.
 *  oF port of the traer.physics Processing library: http://www.cs.princeton.edu/~traer/physics/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
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
