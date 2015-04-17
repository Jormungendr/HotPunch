#ifndef _Enemy__
#define _Enemy__
#include "Entity.h"
USING_NS_CC;
class Enemy : public Entity
{
public:
	int view;

	CCRect m_ViewRect;											//��Ұ����
	virtual void initViewRect();									//��ʼ����������Ұ����
	virtual void initBlock();
	EnemyState enemyState;									//����״̬��ö��
	virtual void attack();											//����
	virtual void useSkill();										//ʩ�÷�������ͬ����ʩ�÷����ĳ��Ͼ���ͬ��
	virtual void changeDirection();							//��д���ຯ��
	void patrol();														//Ѳ��
	virtual void run();												//��д���ຯ��
	virtual void jump();											//��д�����ĺ���

	int count;															//Ѳ�߲���
	int speedX;														//���˵�ˮƽ�ƶ��ٶ�
	virtual bool init();
	CREATE_FUNC(Enemy);
};
#endif