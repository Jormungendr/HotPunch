#ifndef _JapanArmyI__
#define _JapanArmyI__
#include "Enemy.h"
USING_NS_CC;
class JapanArmyI : public Enemy
{
public:
	void setAttackRect(float dt);
	virtual void refresh(float dt);
	virtual void attack();
	virtual bool init();
	virtual void initBlock();										//��ʼ����ײ��
	virtual void initSprite();
	virtual void hurt();												//�̳���үү��
	void headHurt();												//ͷ������
	void flankHurt();												//��������
	void airHurt();													//��������
	void hurtCallBack(CCArmature* armature,
		MovementEventType type,
		const char *name);											//���˶���������ɺ�Ļص�
	void doHurt(float dt);											//���˺����ƶ��Ļص�
	//	virtual void initViewRect();
	void airAttack();
	void groundAttack();
	//����������ʵ�ֺ���
	void HeavyPunch();
	void Pistol();
	void UpAttack();
	void BoxingPunch();
	void SuperPistol();
	CREATE_FUNC(JapanArmyI);
};
#endif