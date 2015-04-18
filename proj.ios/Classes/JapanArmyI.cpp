/*��д�˹�����������attack
���˵Ĺ��������������
*/
#include "JapanArmyI.h"
USING_NS_CC;
bool JapanArmyI::init()
{
	if (!Enemy::init())
	{
		return false;
	}
    setHP(100);
	view = 5*32;
	enemyState = STADINGBY;
	initSprite();				//��ʼ�����鶯��
	initViewRect();
	speedX = 1.5;
	return true;
}
void JapanArmyI::initBlock()
{
	m_block = CCRectMake(
		getPositionX(),
		getPositionY(),
		m_sprite->getContentSize().width - 5,
		m_sprite->getContentSize().height);

	//m_attack = m_block;				//��ʱ�����ﴴ����������
}
void JapanArmyI::initSprite()
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Xinfeng0.png", "Xinfeng0.plist", "Xinfeng.ExportJson");
	m_sprite = CCArmature::create("Xinfeng");							// ����ֱ��ʹ��Nivida ��������Ϣ������ Nivida.ExportJson �У����䴴������Ŀ�������Ӧ  
	m_sprite->getAnimation()->play("Stand");							// ���õ�ǰ���ж�����������һ�������̡����Խ����������
	m_sprite->setPosition(ccp(25,0));											// ����λ����Ϣ
	this->addChild(m_sprite);														// ��ӵ���������ǰ���еĳ���֮��
}
void JapanArmyI::hurt()
{
	if (this->getState() != HURT)
	{
		this->setState(HURT);
		velocityX = 0;
		if (inTheAir_flag)
		{
			airHurt();
		}
		else
		{
			float tempRand = CCRANDOM_0_1();
			if (tempRand < 0.5f)						//��ͷ�������͸�������֮�������һ��
			{
				headHurt();
			}
			else
			{
				flankHurt();
			}
		}
	}
}
void JapanArmyI::headHurt()
{
	m_sprite->getAnimation()->play("HeadHurt");
	this->scheduleOnce(schedule_selector(JapanArmyI::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(JapanArmyI::hurtCallBack));
}
void JapanArmyI::flankHurt()
{
	m_sprite->getAnimation()->play("FlankHurt");
	this->scheduleOnce(schedule_selector(JapanArmyI::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(JapanArmyI::hurtCallBack));
}
void JapanArmyI::airHurt()
{
	if (faceto)
	{
		velocityX = 2;
	}
	else
	{
		velocityX = -2;
	}
	velocityY = 5;
	m_sprite->getAnimation()->play("FlankHurt");
	this->scheduleOnce(schedule_selector(JapanArmyI::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(JapanArmyI::hurtCallBack));
}
void JapanArmyI::doHurt(float dt)
{
	setState(NORMAL);
	m_sprite->getAnimation()->play("Stand");
}
void JapanArmyI::hurtCallBack(CCArmature* armature, MovementEventType type, const char *name)
{
	if (strcmp(name,"FlankDefence") == 0 || strcmp(name,"HeadDefence") == 0)
	{
		switch (type)
		{
		case COMPLETE:
			setState(NORMAL);
			armature->getAnimation()->play("Stand");
			break;
		default:
			break;
		}
	}
}
void JapanArmyI::attack()
{
	if (getState() ==  NORMAL||getState() == WALKING)
	{
		if (getState() != ATTACKING)
		{
			setState(ATTACKING);
			if (this->enemyState != ATTACK)
			{
				enemyState = ATTACK;
			}
			velocityX = 0;
			if (inTheAir_flag)
			{
				airAttack();
			}
			else
			{
				groundAttack();
			}
		}
	}
}
void JapanArmyI::refresh(float dt)
{
	this->setState(NORMAL);
	enemyState = STADINGBY;
	m_sprite->getAnimation()->play("Stand");
	m_attack.isFinished = true;
}
void JapanArmyI::setAttackRect(float dt)
{
	if (faceto)
	{
		m_attack = AttackRect(CCRectMake(
			getPositionX() - 40,
			getPositionY() + 16,
			m_sprite->getContentSize().width - 10,
			m_sprite->getContentSize().height - 10),
			force,false);
	}
	else
	{
		m_attack = AttackRect(CCRectMake(
			getPositionX() + 40,
			getPositionY() + 16,
			m_sprite->getContentSize().width - 10,
			m_sprite->getContentSize().height - 10),
			force,false);
	}
}
void JapanArmyI::HeavyPunch()
{
	m_sprite->getAnimation()->play("HeavyPunch");
	force = 10;
	this->scheduleOnce(schedule_selector(JapanArmyI::setAttackRect),0.4f);
	scheduleOnce(schedule_selector(JapanArmyI::refresh),0.6f);
}
void JapanArmyI::Pistol()
{
	m_sprite->getAnimation()->play("Pistol");
	force = 20;
	this->scheduleOnce(schedule_selector(JapanArmyI::setAttackRect),0.4f);
	scheduleOnce(schedule_selector(JapanArmyI::refresh),0.6f);
}
void JapanArmyI::UpAttack()
{
	m_sprite->getAnimation()->play("UpAttack");
	force = 10;
	this->scheduleOnce(schedule_selector(JapanArmyI::setAttackRect),0.4f);
	scheduleOnce(schedule_selector(JapanArmyI::refresh),0.6f);
}
void JapanArmyI::BoxingPunch()
{
	m_sprite->getAnimation()->play("BoxingPunch");
	force = 15;
	this->scheduleOnce(schedule_selector(JapanArmyI::setAttackRect),0.4f);
	scheduleOnce(schedule_selector(JapanArmyI::refresh),0.6f);
}
void JapanArmyI::SuperPistol()
{
	m_sprite->getAnimation()->play("SuperPistol");
	force = 30;
	this->scheduleOnce(schedule_selector(JapanArmyI::setAttackRect),0.4f);
	scheduleOnce(schedule_selector(JapanArmyI::refresh),0.6f);
}
void JapanArmyI::airAttack()
{
	;
}
void JapanArmyI::groundAttack()
{
	CCLOG("IN JapanArmyI I attacked You");
	int attackIndex = CCRANDOM_0_1()*100;
	if (attackIndex <= 30)
	{
		HeavyPunch();
	}
	else if (attackIndex <= 55)
	{
		Pistol();

	}
	else if(attackIndex <= 65)	
	{
		UpAttack();
	}
	else if(attackIndex <= 75)
	{
		BoxingPunch();
	}
	else if(attackIndex <=90)
	{
		HeavyPunch();
	}
	else
	{
		SuperPistol();
	}
	//enemyState = STADINGBY;
}