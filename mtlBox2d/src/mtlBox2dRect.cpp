/*
 *  mtlBox2dRect.cpp
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-10-06.
 *  Based on ofxBox2d by Todd Vanderlin: http://code.google.com/p/vanderlin/
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include "mtlBox2dRect.h"

//------------------------------------------------
mtlBox2dRect::mtlBox2dRect() {
    verts = new GLfloat[b2_maxPolygonVertices * 2];
}

//------------------------------------------------
mtlBox2dRect::~mtlBox2dRect() {
    delete [] verts;
}

//------------------------------------------------
void mtlBox2dRect::setup(b2World* _world, float _x, float _y, float _width, float _height, float _ang, bool _fixed) {
    if (!setWorld(_world)) return;
    
    rect.SetAsBox(_width / BOX2D_SCALE, _height / BOX2D_SCALE);
    fixed = _fixed;
    
    if (fixed) {
        rect.density		= 0;
        rect.restitution    = 0;
        rect.friction		= 0;
    } else {
        rect.density		= mass;
        rect.restitution    = bounce;
        rect.friction		= friction;
    }
    bodyDef.position.Set(_x / BOX2D_SCALE, _y / BOX2D_SCALE);
    bodyDef.angle = _ang;
    
    body = world->CreateBody(&bodyDef);
    body->SetLinearVelocity(b2Vec2(0.0, 0.0));
    body->CreateShape(&rect);
    body->SetMassFromShapes();
}

//------------------------------------------------
void mtlBox2dRect::draw() {
    if (dead && !body) return;
    
    // wow this is a pain
    b2Shape* s = body->GetShapeList();
    const b2XForm& xf = body->GetXForm();
    b2PolygonShape* poly = (b2PolygonShape*)s;
    int count = poly->GetVertexCount();
    const b2Vec2* localVertices = poly->GetVertices();
    b2Assert(count <= b2_maxPolygonVertices);
    b2Vec2 currVert;
    for (int i=0; i < count; i++) {
        currVert = BOX2D_SCALE * b2Mul(xf, localVertices[i]);
        verts[i*2 + 0] = currVert.x;
        verts[i*2 + 1] = currVert.y;
    }
    
    ofNoFill();
    if (fixed) {
        ofSetColor(mtlBox2d::debugFixedColor.r, mtlBox2d::debugFixedColor.g, mtlBox2d::debugFixedColor.b, mtlBox2d::debugFixedColor.a);
    } else {
        ofSetColor(mtlBox2d::debugBodyColor.r, mtlBox2d::debugBodyColor.g, mtlBox2d::debugBodyColor.b, mtlBox2d::debugBodyColor.a);
    }
    
    glEnableClientState(GL_VERTEX_ARRAY);		
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glDrawArrays(GL_LINE_LOOP, 0, count);
}
