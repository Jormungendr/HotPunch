#ifndef _GameOverLayer__
#define _GameOverLayer__
#include "cocos2d.h"
USING_NS_CC;
/************************************************************************/
/* GameOverLayer:��Ϸ��������
/*����һ������ͼƬ��һ�����ص����⡱�İ�ť���л�����ҳ���ʱ��Ქ������
/**/
/************************************************************************/
class GameOverLayer : public CCLayer
{
public:
	virtual bool init();									//��ʼ������
	static CCScene* Scene();
	CREATE_FUNC(GameOverLayer);

	//Button Callback Functions:
	void retryBtnCallBack(CCObject* pSender);
private:
	CCMenuItemImage* retryBtn;
	CCSprite* sp_Background;
};

#endif