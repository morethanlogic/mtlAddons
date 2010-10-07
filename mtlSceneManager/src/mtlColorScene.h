#pragma once

/*
 *  mtlColorScene.h
 *  mtlSceneManager
 *
 *  Created by Elie Zananiri on 10-10-07.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "mtlScene.h"

class mtlColorScene : public mtlScene {
    
    public:
                mtlColorScene(int _hex);
                mtlColorScene(int _r, int _g, int _b);
        
        void	draw();
    
    protected:
        int     r, g, b;
    
};
