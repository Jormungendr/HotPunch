#ifndef _ControlLayer__
#define _ControlLayer__
#include "cocos2d.h"
#include "Scene.h"
#include "Hero.h"
USING_NS_CC;
class ControlLayer:public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(ControlLayer);
	virtual void update(float delta);

	void JmpBtnCallBack(CCObject* pSender);
	void AtkBtnCallBack(CCObject* pSender);
	void BladeBtnCallBack(CCObject* pSender);
	void ShieldBtnCallBack(CCObject* pSender);
	void CloakBtnCallBack(CCObject* pSender);
	void ClockUPBtnCallBack(CCObject* pSender);
	void pauseBtnCallBack(CCObject* pSender);
	//������������������
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
public:
	//�����������ߵİ�ť��������������Ծ������ʵ�İ�ť
	CCSprite* LeftBtn;
	CCSprite* RightBtn;
	CCMenuItemImage* JmpBtn;
	CCMenuItemImage* AtkBtn;
	//CCMenuItemImage* 
	Hero* hero;		//ȡ�ö����ǵĲ���Ȩ�����׵ģ�

	bool is_lftBtnPressed;
	bool is_rgtBtnPressed;
	bool is_ModeChangeItemPressed;			//������
	//����״̬����ʾ��
	CCSprite* imageItemSide;
	CCSprite* imageItem;
	CCSprite* hp_Bar;
	CCSprite* sp_Bar;
	CCSprite* tp_Bar;
};
#endif