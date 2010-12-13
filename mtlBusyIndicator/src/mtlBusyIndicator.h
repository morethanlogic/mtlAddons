#pragma once

/*
 *  mtlBusyIndicator.h
 *
 *  Created by Elie Zananiri on 10-09-16.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#import <UIKit/UIKit.h>

#include "ofMain.h"
#include "ofxiPhoneExtras.h"

//----------------------------------------------------------------
//----------------------------------------------------------------
class mtlBusyIndicator {

    public:
                mtlBusyIndicator();
                ~mtlBusyIndicator();
    
        void    setPos(int _x, int _y);
        void    setStyle(UIActivityIndicatorViewStyle _style);
    
        void    start();
        void    stop();

    protected:
        UIActivityIndicatorView*    indicator;
        
};
