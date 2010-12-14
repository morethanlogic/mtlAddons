#pragma once

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
 *  mtlBox2dHitTestCallback.h
 *  mtlBox2d
 *
 *  Created by Elie Zananiri on 10-11-22.
 *  Based on Box2D by Erin Catto: http://www.gphysics.com
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
