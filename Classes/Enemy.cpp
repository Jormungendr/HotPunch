#include "Enemy.h"
USING_NS_CC;
bool Enemy::init()
{	//�󲿷����ݶ����ڻ�����������������ʼ���ģ����������ʼ�������ͱȽ�ˮ����
	if (!Entity::init())
	{
		return false;
	}
	view = 0;
	enemyState = STADINGBY;
	count = 0;
	speedX = 1.5;
	return true;
}
void Enemy::initViewRect()
{
	if (faceto == true)					////	//face to the Left,x may be - view
		m_ViewRect = CCRectMake(
		getPositionX() - view - 20,
		getPositionY() - 80,
		view + 20,
		m_sprite->getContentSize().height * 2);
	else
		m_ViewRect = CCRectMake(
		getPositionX() - 20,
		getPositionY() - 80,
		view + 20,
		m_sprite->getContentSize().height * 2);
}
void Enemy::attack()
{
	CCLOG("I attacked you");
}
void Enemy::useSkill()
{
	CCLOG("Byu!");
}
void Enemy::patrol()
{
	if (this->enemyState == PATROLING)
	{
		count++;
		this->run();
		if (count == 100 || getPositionX() <= 10)
		{
			this->changeDirection();
		}
	}
}
void Enemy::initBlock()
{
	;					//��Ϊ��������Ϊ���麯��������ֻ���������ú���û��ʵ������
}
void Enemy::changeDirection()			//��ɸ��ද�������㲽������õ����߾���ʽѲ��
{
	Entity::changeDirection();
	count = 0;
}
void Enemy::run()
{
	if (inTheAir_flag)			//�ڿ��е�ʱ��ʲôҲ����
	{
		;
	}
	else								//���ڿ��У��ж��ǲ�������״̬
	{
		if (getState() == NORMAL)
		{
			m_sprite->getAnimation()->play("Walk");
			setState(WALKING);
		}
	}
	if (getState() == WALKING || getState() == NORMAL)
	{
		if (faceto == false)
			velocityX = speedX;
		else
			velocityX = -speedX;
	}
	else
	{
		velocityX = 0;
	}
}
void Enemy::jump()
{
	if (getState() == NORMAL||getState() == WALKING)
	{
		if (inTheAir_flag == false && finished == false)
		{
			finished = true;
			m_sprite->getAnimation()->play("Jump");
			this->scheduleOnce(schedule_selector(Entity::doJump),0.33f);
		}
	}
}