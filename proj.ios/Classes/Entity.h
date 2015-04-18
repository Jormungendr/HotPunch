#ifndef _Entity__
#define _Entity__
/************************************************************************/
/* Entity�࣬��Ϊ�����ڵ�ͼ����ʾ������Ķ���ĸ������
��Enemy��Hero��ĸ���*/
/************************************************************************/
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Global.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Entity:public CCNode
{
public:
	virtual bool init();
	virtual void initBlock();										//��ʼ����ײ��
	CCRect getRect();												//��ȡ������ײ����
	virtual void initSprite();										//��ʼ�����鶯��������bindSprite�ã�
	HeroState getState();										//��ȡ��ҵ�״̬
	void setHP(int a);												//�޸�HP
	void setSP(int a);												//�޸�SP
	void setState(HeroState a);								//�޸���ҵ�״̬
public:
	CCArmature* m_sprite;				//�µ����Ǿ���
	CCRect m_block;						//��ɫ����ײ��
	AttackRect m_attack;				//��ɫ�Ĺ�����
	float velocityY;							//��ֱ�����ٶ�
	int force;									//������
	bool inTheAir_flag;					//���ձ�־
	bool faceto;								//��ɫ��������Ϊtrue��Ϊfalse
	bool finished;							//��û�гɹ�������Ծ���ı�־
	bool jumpMainFlag;					//���������������õ�һ����־
	float velocityX;							//ˮƽ�����ٶ�

	CREATE_FUNC(Entity);
	//��eclips�õ���������
	float get_max(float a,float b)
	{
		return (a > b ? a : b);
	}
	float get_min(float a,float b)
	{
		return (a < b ? a : b);
	}
private:
		HeroState state;						//State of the hero
	//////////////////////
public:
    float HP,SP;
	//////////////���ֶ���////////////////
	virtual void refresh(float dt);			//��������
	virtual void run();											//���ߣ����ǵĽ����ǲ��Ŷ�������ͬ�����ƶ��ٶ�������
	void setDirection(bool a);								//���÷���ͨ�ã�
	void changeDirection();									//�ı䷽��
	virtual void jump();										//��Ծ����ͬ�ĸ߶Ȳ�ͬ��
	void doJump(float dt);									//��Ծ�Ļص�

	virtual void hurt();											//����
	virtual void headHurt();									//ͷ������
	virtual void flankHurt();									//��������
	virtual void airHurt();										//��������
	virtual void standUpCallBack(CCArmature* armature, MovementEventType type, const char * name);						//���¶�վ��ִ����Ϻ�Ļص�����
	virtual void jumpCallBack(CCArmature* armature,MovementEventType type,const char *name);								//��Ծ����������Ϻ�Ļص�����
};
#endif