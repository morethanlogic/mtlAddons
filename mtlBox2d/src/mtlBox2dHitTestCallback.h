#pragma once

/*
 *  mtlBox2dHitTestCallback.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-11-22.
 *  Copyright 2010 silentlyCrashing::net. All rights reserved.
 *
 */

#include <Box2D.h>

//========================================================================
class mtlBox2dHitTestCallback : public b2QueryCallback {
    
    public:
        //------------------------------------------------
        mtlBox2dHitTestCallback(const b2Vec2& _point) {
            point   = _point;
            fixture = NULL;
        }
        
        //------------------------------------------------
        bool ReportFixture(b2Fixture *_fixture) {
            b2Body* body = _fixture->GetBody();
            if (body->GetType() == b2_dynamicBody) {
                if (_fixture->TestPoint(point)) {
                    fixture = _fixture;
                    
                    // done, terminate the query
                    return false;
                }
            }
            
            // continue the query
            return true;
        }
        
        //------------------------------------------------
        b2Vec2      point;
        b2Fixture   *fixture;
    
};
