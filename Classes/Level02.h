#ifndef _Level02__
#define _Level02__
#include "cocos2d.h"
#include "Scene.h"
#include "GameLayer.h"

USING_NS_CC;
class Level02 : public GameLayer
{
public:
	virtual bool init();
	virtual void initGroundRect();				//��ʼ����ǰ��ͼ��������ײ����
	virtual void initEnemyArr();					//��ʼ����������
	virtual void update(float delta);
	CREATE_FUNC(Level02);
};
#endif