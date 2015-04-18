#ifndef _GameLayer__
#define _GameLayer__

#include "cocos2d.h"

#include "Hero.h"
#include "JapanArmyI.h"
#include "JapanArmyII.h"
#include "Ninja.h"
#include "Liuhai.h"

#include "Global.h"
USING_NS_CC;
class GameLayer: public cocos2d::CCLayer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();  
	virtual void initGroundRect();				//��ʼ����ǰ��ͼ��������ײ����
	virtual void initEnemyArr();					//��ʼ����������
	void updateNORMAL();				//����ƽ������µ����ǵ�ˢ��
	void updateHURT();					//������������µ����ǵ�ˢ��
	void updateMap();					//��ͼ��ˢ��

	void updateEnemy();					//���˵ĸ���
	void AIMonster();						//���˵���Ϊ

	int blockCount;
	int maxWidth;							//��ͼ�����
	CREATE_FUNC(GameLayer);
	virtual void update(float delta);
public:
	CCTMXTiledMap* map;
	int tileCountX,tileCountY;
	Hero* hero;
	CCRect grdBlkArry[100];
	CCPoint thisPosition;

	CCArray* enemyArr;					//��������

private:
};
#endif