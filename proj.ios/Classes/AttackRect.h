#ifndef _AttackRect__
#define _AttackRect__
#include "cocos2d.h"
USING_NS_CC;
class AttackRect : public CCRect
{
public:
	bool isFinished;			//�Ƿ��Ѿ�������־
	bool isCanFly;			//�Ƿ���ɻ���
	int m_force;				//����������

	AttackRect& operator=(const AttackRect& other);

	AttackRect();

	AttackRect(float x,float y,float width,float height,int force,bool t_isCanFly);
	AttackRect(CCRect a,int force,bool t_isCanFly);
	AttackRect(AttackRect &temp);
};
#endif
