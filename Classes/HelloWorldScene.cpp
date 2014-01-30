#include "HelloWorldScene.h"
#include "Map.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	Map* map = Map::create("Map.tmx", "base");
	map->setPosition(visibleSize/2 - map->getContentSize()/2);

	addChild(map);

	micropather::MicroPather* pather = new micropather::MicroPather(map);
	micropather::MPVector<void*> path;
	float totalCost = 0;

	CCPoint start = ccp(0,0);
	CCPoint end = ccp(9,9);
	int result = pather->Solve(&start, &end, &path, &totalCost);
	CCLOG("%d", result);

	for (int i = 0; i < path.size(); i++) {
		CCPoint* point = (CCPoint*)path[i];
		CCLOG("%d: (%f, %f)", i, point->x, point->y);
	}
    
    return true;
}
