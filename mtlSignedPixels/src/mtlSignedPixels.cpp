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
 *  mtlSignedPixels.cpp
 *  mtlSignedPixels
 *
 *  Created by Elie Zananiri on 10-09-28.
 */

#include "mtlSignedPixels.h"

//--------------------------------------------------------------
mtlSignedPixels::mtlSignedPixels() {
    pixels  = NULL;
    uPixels = NULL;
    
    dirtyPixels = false;
}

//--------------------------------------------------------------
mtlSignedPixels::~mtlSignedPixels() {
    clear();
}

//--------------------------------------------------------------
void mtlSignedPixels::allocate(int _width, int _height, int _glType) {
    clear();
    
    width   = _width;
    height  = _height;
    
    switch (_glType) {
        case GL_RGB:
            bpp = 3;
            break;
        case GL_RGBA:
            bpp = 4;
            break;
        case GL_LUMINANCE:
            bpp = 1;
            break;
        case GL_LUMINANCE_ALPHA:
            bpp = 2;
            break;
    }
    
    n       = width * height * bpp;
    pixels  = new int[n];
    uPixels = new unsigned char[n];
}

//--------------------------------------------------------------
void mtlSignedPixels::set(unsigned char* _pixels) {
    for (int i=0; i < n; i++) {
        pixels[i] = _pixels[i];
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------
void mtlSignedPixels::clear() {
    if (pixels != NULL) 
        delete [] pixels;
    
    if (uPixels != NULL) 
        delete [] uPixels;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator = (mtlSignedPixels& _other) {
    if (!matches(_other)) {
        ofLog(OF_LOG_WARNING, "mtlSignedPixels mismatch!");
        return;
    }
    
    int* otherPixels = _other.getPixels();
    for (int i=0; i < n; i++) {
        pixels[i] = otherPixels[i];
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator += (mtlSignedPixels& _other) {
    if (!matches(_other)) {
        ofLog(OF_LOG_WARNING, "mtlSignedPixels mismatch!");
        return;
    }
    
    int* otherPixels = _other.getPixels();
    for (int i=0; i < n; i++) {
        pixels[i] += otherPixels[i];
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator -= (mtlSignedPixels& _other) {
    if (!matches(_other)) {
        ofLog(OF_LOG_WARNING, "mtlSignedPixels mismatch!");
        return;
    }
    
    int* otherPixels = _other.getPixels();
    for (int i=0; i < n; i++) {
        pixels[i] -= otherPixels[i];
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator *= (mtlSignedPixels& _other) {
    if (!matches(_other)) {
        ofLog(OF_LOG_WARNING, "mtlSignedPixels mismatch!");
        return;
    }
    
    int* otherPixels = _other.getPixels();
    for (int i=0; i < n; i++) {
        pixels[i] *= otherPixels[i];
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator = (float _scalar) {
    for (int i=0; i < n; i++) {
        pixels[i] = _scalar;
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator += (float _scalar) {
    for (int i=0; i < n; i++) {
        pixels[i] += _scalar;
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator -= (float _scalar) {
    for (int i=0; i < n; i++) {
        pixels[i] -= _scalar;
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------------------------
void mtlSignedPixels::operator *= (float _scalar) {
    for (int i=0; i < n; i++) {
        pixels[i] *= _scalar;
    }
    dirtyPixels = true;
}

//--------------------------------------------------------------
int* mtlSignedPixels::getPixels() {
    return pixels;
}

//--------------------------------------------------------------
unsigned char* mtlSignedPixels::getUnsignedPixels() {
    if (dirtyPixels) {
        for (int i=0; i < n; i++) {
            uPixels[i] = pixels[i];
        }
        
        dirtyPixels = false;
    }
    return uPixels;
}

//--------------------------------------------------------------
int mtlSignedPixels::getWidth() {
    return width;
}

//--------------------------------------------------------------
int mtlSignedPixels::getHeight() {
    return height;
}

//--------------------------------------------------------------
int mtlSignedPixels::getBpp() {
    return bpp;
}

//--------------------------------------------------------------
bool mtlSignedPixels::matches(mtlSignedPixels& _other) {
    if (width == _other.getWidth() && height == _other.getHeight() && bpp == _other.getBpp())
        return true;
    return false;
}