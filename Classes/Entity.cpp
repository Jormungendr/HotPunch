#include "Entity.h"
USING_NS_CC;
bool Entity::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	m_attack = AttackRect(-1000,-1000,1,1,0,false);			/////�����������õ���Զ�ĵط�
	m_attack.isFinished = true;
	state = NORMAL;			//��ʼ��״̬
	HP = SP  = 0;				//��ʼ������
	velocityX = 0;
	velocityY = 0;				//��ʼ��ˮƽ����ֱ������ٶ�
	force = 0;
	finished = false;
	faceto = false;
	inTheAir_flag = true;
	jumpMainFlag = true;
	return true;
}
void Entity::initSprite()//��ʱ������Ϊ��
{
	
}
CCRect Entity::getRect()
{
	return m_block;
}
HeroState Entity::getState()
{
	return state;
}
void Entity::setState(HeroState a)
{
	state = a;
}
void Entity::initBlock()
{
	m_block = CCRectMake(getPositionX() + 20,getPositionY(),28 , 91);
}
void Entity::setHP(int a)
{
	HP = a;
}
void Entity::setSP(int a)
{
	SP = a;
}
void Entity::run()
{
	setState(WALKING);
	if (faceto == false)
		this->velocityX = 1.5;
	else
		this->velocityX = -1.5;
}
void Entity::setDirection(bool a)
{
	faceto = a;
	if (a == true)		//������
		m_sprite->setScaleX(-1.0f);
	else
		m_sprite->setScaleX(1.0f);
}
void Entity::changeDirection()
{
	if (faceto)
	{
		faceto = false;
		m_sprite->setScaleX(1.0f);
	}
	else
	{
		faceto = true;
		m_sprite->setScaleX(-1.0f);
	}
}
void Entity::jump()
{
	if (inTheAir_flag == false && finished == false)
	{
		finished = true;
		m_sprite->getAnimation()->play("Jump");
		this->scheduleOnce(schedule_selector(Entity::doJump),0.33f);
	}
}
void Entity::doJump(float dt)
{
	int temp = getPositionY();
	m_sprite->getAnimation()->play("Up");
	setPositionY(temp + 10);
	initBlock();
	inTheAir_flag = true;
	finished = false;
	jumpMainFlag = false;		//�ڴ˴�ȷ��������������
	velocityY = 14;
	setState(NORMAL);
}
//
void Entity::standUpCallBack(CCArmature* armature, MovementEventType type, const char * name)
{
	CCLOG("movement callback name:%s \n",name);
	if (strcmp(name,"Down") == 0)
	{
		switch (type)
		{
		case COMPLETE:
			//setState(NORMAL);
			armature->getAnimation()->play("Stand");
			break;
		default:
			break;
		}
	}
}
//
void Entity::jumpCallBack(CCArmature* armature,MovementEventType type,const char *name)
{
	CCLOG("movement callback name:%s \n",name);
	if (strcmp(name,"Jump") == 0)
	{
		switch (type)
		{
		case COMPLETE:
			setState(NORMAL);
			armature->getAnimation()->play("Up");
			break;
		default:
			break;
		}
	}
}
void Entity::hurt()
{
	setState(HURT);
	if (inTheAir_flag)								//���յĻ��ͳ���������
	{
		airHurt();
	}
	else
	{
		float tempRand = CCRANDOM_0_1();
		if (tempRand < 0.5f)						//��ͷ�����˺͸�������֮�������һ��
		{
			headHurt();
		}
		else
		{
			flankHurt();
		}
	}
}
//�������������ڲ�ͬ���������в�ͬ��ʵ�֣����������ֻ������
void Entity::headHurt()
{
	CCLOG("Oh,my head!\n");
	setState(NORMAL);
}
void Entity::flankHurt()
{
	CCLOG("Oh,my baby!\n");
	setState(NORMAL);
}
void Entity::airHurt()
{
	CCLOG("I want to fly so high\n");
	setState(NORMAL);
}
void Entity::refresh(float dt)
{
	this->setState(NORMAL);
	m_attack.isFinished = true;
	m_sprite->getAnimation()->play("Stand");
}