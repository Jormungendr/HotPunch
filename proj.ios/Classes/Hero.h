#ifndef _Hero__
#define _Hero__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Entity.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Hero:public Entity
{
public:
	Hero();
	~Hero();
	float TP;//ŭ��ֵ
	void setTiledMap(CCTMXTiledMap* map);				//set the tiled map
	virtual bool init();
	virtual void initBlock();											//��ʼ����ײ��
	virtual void initSprite();
//	virtual void initSprite();  										//�պ���Ҫ��д�˺���	
	CCPoint getViewPointByPlayer();
	virtual void run();
	HeroMode getMode();											//��ȡ���ģʽ״̬
	void setMode(HeroMode a);									//�޸����ģʽ״̬
	//��д��������������˺���
	virtual void hurt();
	virtual void headHurt();
	virtual void flankHurt();
	virtual void airHurt();
	void headDefence();												//ͷ������
	void flankDefence();												//��������
	void SB_HeadHurt();
	void SB_FlankHurt();
	void hurtCallBack(CCArmature* armature,
		MovementEventType type,
		const char *name);											//���˶���������ɺ�Ļص�
	void doHurt(float dt);											//���˺����ƶ��Ļص�

	////////////////���ֶ���//////////////////
	void attack();							//�ܹ�������
	void normalAttack();				//���ý��Ĺ�������
	void bladeAttack();				//�ý��Ĺ�������
	void airAttack();					//���й��������ķ�֧
	void groundAttack();				//���湥���ķ�֧
	void groundBladeAttack();		//����⽣�����ķ�֧
	void terminateAttack();
	//�����÷���Ķ���
	void heavyPunch();
	void upAttack();
	void heavyKick();

	void SB_Attack1();
	void SB_Attack2();
	void SB_Attack3();
	void SB_Attack4();
	//�����սἼ
	void drangonPunch();
	void cycloneKick();
	/////////////////////////////////////////
	virtual void refresh(float dt);			//��������
	void setAttackRect(float dt);
	///////////////////////////////////////
	void handBlade();
	void afterHandBlade(float dt);
	void modeShield();
	void modeIvisible();
	void afterModeIvisible(float dt);
	void modeClockUp();
	void afterModeClockUp(float dt);
	///////////////////////////////////////
	virtual void jump();
	virtual void doJump(float dt);
	//�����
public:
	CREATE_FUNC(Hero);
private:
	CCTMXTiledMap* m_map;		//to opreate the TiledMap
	HeroMode m_mode;					//ģʽ״̬
	//////////////////////
};
#endif
