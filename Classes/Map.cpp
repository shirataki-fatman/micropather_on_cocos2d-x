//
//  Map.cpp
//  Pather
//
//  Created by ooshiro teigi on 2014/01/30.
//
//

#include "Map.h"

using namespace cocos2d;

Map::Map(const char* hitLayerName) : CCTMXTiledMap(), hitLayerName(hitLayerName) {
}

Map* Map::create(const char* fileName, const char* hitLayerName) {
	Map* map = new Map(hitLayerName);
	if (map && map->initWithTMXFile(fileName) && map->init()) {
		map->autorelease();
		return map;
	}

	CC_SAFE_DELETE(map);

	return NULL;
}

float Map::LeastCostEstimate( void* stateStart, void* stateEnd ) {
	CCPoint* start = (CCPoint*)stateStart;
	CCPoint* end = (CCPoint*)stateEnd;

	return ccpDistance(*start, *end);
}

void Map::AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent ) {
	CCAssert(state == NULL, "state is null");

	float dx[] = {0, 1,  0, -1};
	float dy[] = {1, 0, -1,  0};

	CCPoint* point = (CCPoint*)state;

	for (int i = 0; i < 4; i++) {
		float nx = point->x + dx[i];
		float ny = point->y + dy[i];
		CCPoint nextPoint = ccp(nx, ny);
		CCDictionary* objectProperty = this->getObject(nextPoint);

		if(objectProperty && objectProperty->valueForKey("pass")->boolValue()) {
			micropather::StateCost cost;
			cost.state = (void*)(&nextPoint);
			cost.cost = objectProperty->valueForKey("cost")->floatValue();

			adjacent->push_back(cost);
		}
	}
}

CCDictionary* Map::getObject(CCPoint point) {
	CCTMXLayer* layer = this->layerNamed("base");
	unsigned int gid = layer->tileGIDAt(point);

	return this->propertiesForGID(gid);

		//return NULL;
}