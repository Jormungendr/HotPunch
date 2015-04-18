#ifndef _TitleLayer__
#define _TitleLayer__
#include "cocos2d.h"
/************************************************************************/
/* TitleLayer:���������࣬������ʾ�������
��Ϸ���������ĵ�һ�����棬��Ҫ����������Ϸ������������Ϸ�����������顱�����˳���Ϸ�ĸ�ѡ��
��Ϸ�����Ͻ���Ҫ��һ������³�����ƴ������ı�־*/
/************************************************************************/
USING_NS_CC;
class TitleLayer : public CCLayer
{
public:
	void menuActionForever(CCMenuItemImage* pImage);//����ʵ�ֲ˵��Ķ�̬Ч��
	virtual bool init();									//��ʼ������
	CREATE_FUNC(TitleLayer);

	//Button Callback Functions:
	void newGmeBtnCallBack(CCObject* pSender);
	void ctnGmeBtnCallBack(CCObject* pSender);
	void tmStudBtnCallBack(CCObject* pSender);
	void quitGmeBtnCallBack(CCObject* pSender);
private:
	CCMenuItemImage* newGmeBtn;		//NweGameButton
	CCMenuItemImage* ctnGmeBtn;			//ContinueGameButton
	CCMenuItemImage* tmStudBtn;			//TeamStudioGameButton
	CCMenuItemImage* quitGmeBtn;			//QuitGameButton
};
#endif