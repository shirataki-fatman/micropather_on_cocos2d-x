//
//  Map.h
//  Pather
//
//  Created by ooshiro teigi on 2014/01/30.
//
//

#ifndef __Pather__Map__
#define __Pather__Map__

#include "cocos2d.h"
#include "micropather.h"

class Map : public cocos2d::CCTMXTiledMap, public micropather::Graph {
private:
	const char* hitLayerName;

	Map(const char* hitLayerName);
public:
	static Map* create(const char* fileName, const char* hitLayerName);

	virtual float LeastCostEstimate( void* stateStart, void* stateEnd );
	virtual void AdjacentCost( void* state, MP_VECTOR< micropather::StateCost > *adjacent );
	virtual void  PrintStateInfo( void* state ){}

	cocos2d::CCDictionary* getObject(cocos2d::CCPoint point);
};

#endif /* defined(__Pather__Map__) */
