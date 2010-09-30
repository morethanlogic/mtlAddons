#pragma once

/*
 *  mtlSignedPixels.h
 *
 *  Created by Elie Zananiri on 10-09-28.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "ofMain.h"

class mtlSignedPixels {
  
    public:
                mtlSignedPixels();
                ~mtlSignedPixels();
    
        void    allocate(int _width, int _height, int _glType);
        void    set(unsigned char* _pixels);
        void    clear();
        
        void    operator =  (mtlSignedPixels& _other);
        void    operator += (mtlSignedPixels& _other);
        void    operator -= (mtlSignedPixels& _other);
        void    operator *= (mtlSignedPixels& _other);
    
        void    operator =  (float _scalar);
        void    operator += (float _scalar);
        void    operator -= (float _scalar);
        void    operator *= (float _scalar);
    
        int*    getPixels();
        unsigned char*    getUnsignedPixels();
    
        int     getWidth();
        int     getHeight();
        int     getBpp();
    
        bool    matches(mtlSignedPixels& _other);
    
    private:
        int*    pixels;
        int     width;
        int     height;
        int     bpp;
        int     n;
    
        unsigned char*  uPixels;
        bool            dirtyPixels;
    
};