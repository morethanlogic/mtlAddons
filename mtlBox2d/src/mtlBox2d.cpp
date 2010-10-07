#include "mtlBox2d.h"

//--------------------------------------------------------------
mtlBox2d::mtlBox2d() {
    // create the world
    worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set( 100.0f,  100.0f);
    world = new b2World(worldAABB, b2Vec2(0, 0), true);
}

//--------------------------------------------------------------
mtlBox2d::~mtlBox2d() {
    // TODO make sure this is proper
    delete world;
    world = NULL;
}

//--------------------------------------------------------------
void mtlBox2d::createBounds(float _x, float _y, float _width, float _height) {
    if (world == NULL) {
        ofLog(OF_LOG_WARNING, "mtlBox2d::createBounds() Must have a valid b2World");
		return;
    }
	
	b2BodyDef bd;
	bd.position.Set(0, 0);
	bounds = world->CreateBody(&bd);	
	b2PolygonDef sd;
	sd.filter.groupIndex = 1;
	sd.density     = 0.f;
	sd.restitution = 0.f;
	sd.friction    = 0.6f;
    
	float thickness = 2.f / BOX2D_SCALE;
	//right
	sd.SetAsBox(thickness, 
                (_height / BOX2D_SCALE) / 2.f, 
                b2Vec2((_width / BOX2D_SCALE), (_height / BOX2D_SCALE) / 2.f), 
                0.0);
	bounds->CreateShape(&sd);
	//left
	sd.SetAsBox(thickness, 
                (_height / BOX2D_SCALE) / 2.f, 
                b2Vec2(0, (_height / BOX2D_SCALE) / 2.f), 
                0.0);
	bounds->CreateShape(&sd);
	//top
	sd.SetAsBox((_width/BOX2D_SCALE) / 2.f, 
                thickness, 
                b2Vec2((_width / BOX2D_SCALE) / 2.f, 0), 
                0.0);
	bounds->CreateShape(&sd);
	//bottom
	sd.SetAsBox((_width / BOX2D_SCALE) / 2.f, 
                thickness, 
                b2Vec2((_width / BOX2D_SCALE) / 2.f, _height / BOX2D_SCALE), 
                0.0);
	bounds->CreateShape(&sd);
}

//--------------------------------------------------------------
void mtlBox2d::update() {
	world->Step(TIMESTEP, VEL_ITERATIONS, POS_ITERATIONS);
	world->Validate();
}

//--------------------------------------------------------------
b2Vec2 mtlBox2d::getGravity() const {
    return world->GetGravity();
}

//--------------------------------------------------------------
void mtlBox2d::setGravity(const b2Vec2& gravity) {
    world->SetGravity(gravity);
}

//--------------------------------------------------------------
void mtlBox2d::debug() {
}

//--------------------------------------------------------------
b2World* mtlBox2d::getWorld() {
    return world;
}

//--------------------------------------------------------------
int mtlBox2d::getBodyCount() { 
    return world->GetBodyCount();
}

//--------------------------------------------------------------
int mtlBox2d::getJointCount() { 
    return world->GetJointCount();
}
