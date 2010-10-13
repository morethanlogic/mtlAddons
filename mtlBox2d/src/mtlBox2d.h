#pragma once

#include "ofMain.h"
#include "Box2D.h"

#define BOX2D_SCALE     30.f
#define FPS             30
#define TIMESTEP        1.f / FPS
#define VEL_ITERATIONS  4
#define POS_ITERATIONS  1

//========================================================================
class mtlBox2d {
    
    public:
                    mtlBox2d();
                    ~mtlBox2d();
    
        void        createBounds(float _x, float _y, float _width, float _height);
            
        void        update();
        void        debug();
        
        b2Vec2      getGravity() const;
        void        setGravity(const b2Vec2& gravity);
        
        b2World*    getWorld();
        int			getBodyCount();
        int			getJointCount();
    
        static ofColor debugBodyColor;
        static ofColor debugJointColor;
        static ofColor debugFixedColor;
        static void setDebugColors(int _bodyR,  int _bodyG,  int _bodyB,  int _bodyA,
                                   int _jointR, int _jointG, int _jointB, int _jointA,
                                   int _fixedR, int _fixedG, int _fixedB, int _fixedA);
        
    private:
        b2AABB      worldAABB;
        b2World*    world;
        b2Body*		bounds;

};

