#ifndef _Story__
#define _Story__
#include "cocos2d.h"
#include "Global.h"

USING_NS_CC;
class Story:public CCLayer
{
public:
	virtual bool init();

	CCSprite* dialogBox_bottom;
	CCSprite* dialogBox_top;
	CCSprite* crctorImage_bottom;
	CCSprite* crctorImage_top;

	CCSprite* text_bottom;
	CCSprite* text_top;

	void showAmysImage();
	void showNividasImage();
	void showNormansImage();
	bool state;											//��ǵ�ǰ�Ƿ���Դ�����ת����һ�¼�
	int count;												//�¼�ID���

	virtual void nextEvt();							//��ת����һ���¼��ĺ���
	void clear();											//�����������
	//������������������
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	CREATE_FUNC(Story);
};
#endif