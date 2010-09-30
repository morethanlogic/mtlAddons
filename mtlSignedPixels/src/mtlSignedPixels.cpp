/*
 *  mtlSignedPixels.cpp
 *
 *  Created by Elie Zananiri on 10-09-28.
 *  Copyright 2010 more than logic. All rights reserved.
 *
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