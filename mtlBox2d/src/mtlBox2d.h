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
        
    private:
        b2AABB      worldAABB;
        b2World*    world;
        b2Body*		bounds;

};

