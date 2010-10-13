/*
 *  mtlColorScene.cpp
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
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
        ofRect(0, 0, width, height);
        
        draw();
    }
    glPopMatrix();
}
