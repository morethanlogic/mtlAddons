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
 *  mtlColorScene.cpp
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 */

#include "mtlColorScene.h"

//--------------------------------------------------------------
mtlColorScene::mtlColorScene(int _hex) : mtlScene() {
    r = (_hex >> 16) & 0xFF;
    g = (_hex >>  8) & 0xFF;
    b = (_hex >>  0) & 0xFF;
}

//--------------------------------------------------------------
mtlColorScene::mtlColorScene(int _r, int _g, int _b) {
    r = _r;
    g = _g;
    b = _b;
}

//--------------------------------------------------------------
void mtlColorScene::_draw() {
    glPushMatrix();
    glTranslatef(x, y, 0);
    {
        // draw the background fill
        ofSetColor(r, g, b, alpha);
        ofFill();
        if (ofGetRectMode() == OF_RECTMODE_CORNER) {
            ofRect(0, 0, width, height);
        } else {
            ofRect(width/2, height/2, width, height);
        }
        
        draw();
    }
    glPopMatrix();
}
