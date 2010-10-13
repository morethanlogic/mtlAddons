/*
 *  mtlBox2dCircle.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dCircle.h"

//------------------------------------------------
mtlBox2dCircle::mtlBox2dCircle() {
    dirVector = new GLfloat[4];
}

//------------------------------------------------
mtlBox2dCircle::~mtlBox2dCircle() {
    delete [] dirVector;
}

//------------------------------------------------
void mtlBox2dCircle::setup(b2World* _world, float _x, float _y, float _size, float _ang, bool _fixed) {
    if (!setWorld(_world)) return;
    
    circle.radius   = _size / BOX2D_SCALE;
    fixed           = _fixed;
    
    if (fixed) {
        circle.density		= 0;
        circle.restitution  = 0;
        circle.friction		= 0;
    } else {
        circle.density		= mass;
        circle.restitution  = bounce;
        circle.friction		= friction;
    }
    bodyDef.position.Set(_x / BOX2D_SCALE, _y / BOX2D_SCALE);	
    
    body = world->CreateBody(&bodyDef);
    body->SetLinearVelocity(b2Vec2(0.0, 0.0));
    body->SetAngularVelocity(_ang * M_PI / 180.f);
    body->CreateShape(&circle);
    body->SetMassFromShapes();
}

//------------------------------------------------
void mtlBox2dCircle::draw() {
    if (dead && !body) return;
    
    float radius = getRadius();
    
    glPushMatrix();
    {
        glTranslatef(getPosition().x, getPosition().y, 0);
        
        ofNoFill();
        if (fixed) {
            ofSetColor(mtlBox2d::debugFixedColor.r, mtlBox2d::debugFixedColor.g, mtlBox2d::debugFixedColor.b, mtlBox2d::debugFixedColor.a);
        } else {
            ofSetColor(mtlBox2d::debugBodyColor.r, mtlBox2d::debugBodyColor.g, mtlBox2d::debugBodyColor.b, mtlBox2d::debugBodyColor.a);
        }
        ofCircle(0, 0, radius);	
    }
    glPopMatrix();
    
    const b2XForm& xf   = body->GetXForm();
    b2Vec2	center		= body->GetPosition();
    b2Vec2	axis		= xf.R.col1;
    b2Vec2	p			= center + radius / BOX2D_SCALE * axis;
    
    ofSetColor(mtlBox2d::debugJointColor.r, mtlBox2d::debugJointColor.g, mtlBox2d::debugJointColor.b, mtlBox2d::debugJointColor.a);
    dirVector[0] = getPosition().x;
    dirVector[1] = getPosition().y;
    dirVector[2] = p.x * BOX2D_SCALE;
    dirVector[3] = p.y * BOX2D_SCALE;
    
    glEnableClientState(GL_VERTEX_ARRAY);		
    glVertexPointer(2, GL_FLOAT, 0, dirVector);
    glDrawArrays(GL_LINES, 0, 2);
}

//------------------------------------------------
float mtlBox2dCircle::getRadius() {
    if (body) {
        return (((b2CircleShape*)(body->GetShapeList()))->GetRadius() * BOX2D_SCALE);
    }
    return 0;
}


//------------------------------------------------
float mtlBox2dCircle::getRotation() {
    const  b2XForm& xf	= body->GetXForm();
    float  r			= getRadius() / BOX2D_SCALE;
    b2Vec2 a			= xf.R.col1;
    b2Vec2 p1			= body->GetPosition();
    b2Vec2 p2			= p1 + r * a;
    
    float dx = p2.x+r/2 - p1.x+r/2;
    float dy = p2.y - p1.y;
    return ofRadToDeg(atan2(dy, dx));
}

//------------------------------------------------ 
void mtlBox2dCircle::disableCollision() {
    circle.filter.maskBits = 0x0;		
}

//------------------------------------------------
void mtlBox2dCircle::setRadius(float _radius) {
    // destroy the current shape
    for (b2Shape* s = body->GetShapeList(); s; s = s->GetNext()) {
        body->DestroyShape(s);
    }
    
    // rebuild the new circle shape
    circle.radius = _radius / BOX2D_SCALE;
    if (fixed) {
        circle.density		= 0;
        circle.restitution  = 0;
        circle.friction		= 0;
    } else {
        circle.density		= mass;
        circle.restitution  = bounce;
        circle.friction		= friction;
    }
    
    body->SetLinearVelocity(b2Vec2(0.0, 0.0));
    body->CreateShape(&circle);
    body->SetMassFromShapes();
}

