//
//  Ninja.h
//  HelloCpp
//
//  Created by ����ͩ on 14-8-21.
//
//

#ifndef _Ninja_h
#define _Ninja_h

#include "Enemy.h"
USING_NS_CC;
class Ninja : public Enemy
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
	void Dart();
	void Hurt_in_theAir();
	void Boomerang();
	CREATE_FUNC(Ninja);
};


#endif
