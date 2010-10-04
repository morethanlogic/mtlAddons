/*
 *  mtlBusyIndicator.cpp
 *
 *  Created by Elie Zananiri on 10-09-16.
 *  Copyright 2010 more than logic. All rights reserved.
 *
 */

#include "mtlBusyIndicator.h"

//--------------------------------------------------------------
mtlBusyIndicator::mtlBusyIndicator() {
	indicator = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
    [iPhoneGetGLView() addSubview:indicator];
    setPos(ofGetWidth()/2, ofGetHeight()/2);
}

//--------------------------------------------------------------
mtlBusyIndicator::~mtlBusyIndicator() {
    [indicator release];
}

//--------------------------------------------------------------
void mtlBusyIndicator::setPos(int _x, int _y) {
    if (iPhoneGetOrientation() == OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT) {
        indicator.center = CGPointMake(_y, ofGetWidth() - _x);
    } else if (iPhoneGetOrientation() == OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT) {
        indicator.center = CGPointMake(ofGetHeight() - _y, _x);
    } else if (iPhoneGetOrientation() == OFXIPHONE_ORIENTATION_UPSIDEDOWN) {
        indicator.center = CGPointMake(ofGetWidth() - _x, ofGetHeight() - _y);
    } else {
        indicator.center = CGPointMake(_x, _y);
    }
}

//--------------------------------------------------------------
void mtlBusyIndicator::setStyle(UIActivityIndicatorViewStyle _style) {
    indicator.activityIndicatorViewStyle = _style;
}

//--------------------------------------------------------------
void mtlBusyIndicator::start() {
    [indicator startAnimating];
}

//--------------------------------------------------------------
void mtlBusyIndicator::stop() {
    [indicator stopAnimating];
}
