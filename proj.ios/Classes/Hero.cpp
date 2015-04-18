#include "Hero.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
Hero::Hero()
	 {
		 m_map = NULL;
	 }
 Hero::~Hero()
	 {
		 CC_SAFE_RELEASE(m_map);
	 }
bool Hero::init()
{
	if (!Entity::init())
	{
		return false;
	}
	setState(NORMAL);					//��ʼ��״̬
	setHP(100);
	setSP(100);
	TP = 0;										//��ʼ����������
	m_mode = SHIELD;					//��ʼ��ģʽ״̬
	velocityY = 0;							//��ʼ��ˮƽ����ֱ������ٶ�
	faceto = false;
	inTheAir_flag = true;
	initSprite();								//��ʼ������
	initBlock();									//��ʼ����ײ��


	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/Cloak.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/Clock.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/e.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/ea.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/en.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/haaaaa.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/heng.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/kale.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/maxArmor.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/seiya.ogg");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Audio/souyuken.ogg");



	return true;
}
void Hero::initSprite()
{
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Nivida0.png", "Nivida0.plist", "Nivida.ExportJson");
	m_sprite = CCArmature::create("Nivida");								// ����ֱ��ʹ��Nivida ��������Ϣ������ Nivida.ExportJson �У����䴴������Ŀ�������Ӧ  
	m_sprite->getAnimation()->playByIndex(0);							// ���õ�ǰ���ж�����������һ�������̡����Խ����������
	m_sprite->setPosition(ccp(25,0));											// ����λ����Ϣ
	this->addChild(m_sprite);														// ��ӵ���������ǰ���еĳ���֮��
}
void Hero::setTiledMap(CCTMXTiledMap* map)
{
	CC_SAFE_RETAIN(map);
	CC_SAFE_RELEASE(m_map);
	this->m_map = map;
}
void Hero::initBlock()
{
	m_block = CCRectMake(
		getPositionX(),
		getPositionY(),
		m_sprite->getContentSize().width - 5,
		m_sprite->getContentSize().height);
}
CCPoint Hero::getViewPointByPlayer()
{
	CCLayer* parent = (CCLayer*)getParent();							//��ȡ���ڵ㣬Ҳ�����ڸ�GameLayerͼ��
	CCSize mapTiledNum = m_map->getMapSize();				//��ȡ��ǰ��ͼ��ͼ����
	CCSize tiledSize = m_map->getTileSize();
	CCSize mapSize = CCSizeMake(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);						//��ȡ��ͼ�ĳߴ�
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint spritePos = getPosition();									//���ǵ�����
	//������ǵ�����С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���ǵ����� 
	float x = get_max(spritePos.x,visibleSize.width/2);
	float y = get_max(spritePos.y,visibleSize.height/2);
	//���X��Y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ
	//���õ�ͼ������Ļ��ɳ��ֺڱߵļ������꣩
	x = get_min(x,mapSize.width - visibleSize.width / 2);
	y = get_min(y,mapSize.height - visibleSize.height / 2);
	
	CCPoint destPos = ccp(x,y);																		//Ŀ���
	CCPoint centerPos = ccp(visibleSize.width/2,visibleSize.height/2);				//��Ļ�е�
	//������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ���
	CCPoint viewPos = ccpSub(centerPos,destPos);

	return viewPos;
}
void Hero::run()
{
	if (inTheAir_flag)			//�ڿ��е�ʱ��ʲôҲ����
	{
		;
	}
	else								//���ڿ��У��ж��ǲ�������״̬
	{
		if (getState() == NORMAL)
		{
			if (getMode() == LIGHTBLADE)
			{
				m_sprite->getAnimation()->play("SB_Walk");
			}
			else
				m_sprite->getAnimation()->playByIndex(1);
			setState(WALKING);
		}
	}
	if (getState() == NORMAL ||getState() == WALKING)
	{
		if (getMode() != CLOCKUP)
		{
			if (m_mode == INVISIBLE)
			{
				SP -= 0.6f;
			}
			if (faceto == false)
				this->velocityX = 2;
			else
				this->velocityX = -2;
		}
		else
		{
			SP -= 0.7f;
			if (faceto == false)
				this->velocityX = 10;
			else
				this->velocityX = -10;
		}
	}
}
HeroMode Hero::getMode()
{
	return m_mode;
}
void Hero::setMode(HeroMode a)
{
	m_mode = a;
}
void Hero::hurt()
{
 	if (this->getState() != HURT)
 	{
		this->setState(HURT);
		if (m_mode == SHIELD)					//����ģʽ�£��������˶������������������
		{
			if (inTheAir_flag)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/ea.ogg");
				airHurt();		//��Ϊû�п��з������������������
			}
			else
			{
				float tempRand = CCRANDOM_0_1();
				if (tempRand < 0.5f)						//��ͷ�������͸�������֮�������һ��
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/e.ogg");
					headDefence();
				}
				else
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/en.ogg");
					flankDefence();
				}
			}
		}
		else if (m_mode == LIGHTBLADE)		//�⽣ģʽ�м������е����˶���
		{
			if (inTheAir_flag)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/e.ogg");
				SB_FlankHurt();		//��Ϊû�п��з������������������
			}
			else
			{
				float tempRand = CCRANDOM_0_1();
				if (tempRand < 0.5f)						//��ͷ�������͸�������֮�������һ��
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/ea.ogg");
					SB_HeadHurt();
				}
				else
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/en.ogg");
					SB_FlankHurt();
				}
			}
		}
		else													//����ģʽ
		{
			if (inTheAir_flag)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/e.ogg");
				airHurt();
			}
			else
			{
				float tempRand = CCRANDOM_0_1();
				if (tempRand < 0.5f)						//��ͷ�������͸�������֮�������һ��
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/en.ogg");
					headHurt();
				}
				else
				{
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/ea.ogg");
					flankHurt();
				}
			}
		}
	}
}
void Hero::headDefence()
{
	m_sprite->getAnimation()->play("HeadDefence");
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::flankDefence()
{
	m_sprite->getAnimation()->play("FlankDefence");
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::headHurt()
{
	m_sprite->getAnimation()->play("HeadHurt");
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::flankHurt()
{
	m_sprite->getAnimation()->play("FlankHurt");
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::SB_FlankHurt()
{
	m_sprite->getAnimation()->play("SB_FlankHurt");
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::SB_HeadHurt()
{
	m_sprite->getAnimation()->play("SB_HeadHurt");
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::airHurt()
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
	this->scheduleOnce(schedule_selector(Hero::doHurt),0.33f);
	m_sprite->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Hero::hurtCallBack));
}
void Hero::doHurt(float dt)
{
	CCActionInterval* temp;
	if (faceto)
	{
		temp = CCMoveBy::create(0.1f,ccp(10,0));
	}
	else
	{
		temp = CCMoveBy::create(0.1f,ccp(-10,0));
	}
	this->runAction(temp);
	setState(NORMAL);
}
void Hero::hurtCallBack(CCArmature* armature, MovementEventType type, const char *name)
{
	CCLOG("movement callback name:%s \n",name);
	if (strcmp(name,"FlankDefence") == 0 || strcmp(name,"HeadDefence") == 0||strcmp(name,"HeadHurt") == 0||strcmp(name,"FlankHurt") == 0)
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
	if (strcmp(name,"SB_FlankHurt") == 0 || strcmp(name,"SB_FlankHurt") == 0)
	{
		switch (type)
		{
		case COMPLETE:
			setState(NORMAL);
			armature->getAnimation()->play("SB_Stand");
			break;
		default:
			break;
		}
	}
}
void Hero::attack()
{
	if (getMode() != LIGHTBLADE)
	{
		normalAttack();
	}
	else
	{
		bladeAttack();
	}
}
void Hero::bladeAttack()
{

	if (getState() ==  NORMAL||getState() == WALKING)
	{
		setState(ATTACKING);
		if (inTheAir_flag)
		{
			airAttack();
		}
		else
		{
			groundBladeAttack();
		}
	}
}
void Hero::normalAttack()
{
	if (getState() ==  NORMAL||getState() == WALKING)
	{
		setState(ATTACKING);
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
void Hero::airAttack()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/seiya.ogg");
	if (getMode() == LIGHTBLADE)
	{
		m_sprite->getAnimation()->play("RiderSting");
		force = 25;
		if (faceto)
			velocityX = -5;
		else		
			velocityX = 5;
		this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
		this->scheduleOnce(schedule_selector(Hero::refresh),0.5f);
	}
	else
	{
		m_sprite->getAnimation()->play("RiderKick");
		if (faceto)
			velocityX = -5;
		else		
		velocityX = 5;
		force = 20;
		this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
		this->scheduleOnce(schedule_selector(Hero::refresh),0.5f);
	}
	
	setState(NORMAL);
}
void Hero::groundAttack()
{
	int temp = CCRANDOM_0_1() * 4 + 1;
	switch (temp)
	{
	case 1:
		heavyPunch();
		break;
	case 2:
		upAttack();
		break;
	case 3:
		heavyKick();
		break;
	default:
		terminateAttack();
		break;
	}
}
void Hero::terminateAttack()
{
	int temp = CCRANDOM_0_1() * 100;
	if (temp < 50)
	{
		drangonPunch();
	}
	else
	{
		cycloneKick();
	}
}
void Hero::groundBladeAttack()
{
	int temp = CCRANDOM_0_1() * 4 + 1;
	switch (temp)
	{
	case 1:
		SB_Attack1();
		break;
	case 2:
		SB_Attack2();
		break;
	case 3:
		SB_Attack3();
		break;
	default:
		SB_Attack4();
		break;
	}
}
void Hero::heavyPunch()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/hea.ogg");
	m_sprite->getAnimation()->play("HeavyPunch");
	force = 20;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
	this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}
void Hero::upAttack()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/heng.ogg");
	m_sprite->getAnimation()->play("UpAttack");
	force = 20;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
	this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}
void Hero::heavyKick()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/heng.ogg");
	m_sprite->getAnimation()->play("HeavyKick");
	force = 20;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
	this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}

void Hero::SB_Attack1()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/heng.ogg");
	m_sprite->getAnimation()->play("Saber1");
	force = 28;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
    this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}
void Hero::SB_Attack2()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/heng.ogg");
	m_sprite->getAnimation()->play("Saber2");
	force = 28;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
    this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}
void Hero::SB_Attack3()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/heng.ogg");
	m_sprite->getAnimation()->play("Saber3");
	force = 30;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
    this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}
void Hero::SB_Attack4()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/heng.ogg");
	m_sprite->getAnimation()->play("Saber4");
	force = 35;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
    this->scheduleOnce(schedule_selector(Hero::refresh),0.4f);
}
void Hero::drangonPunch()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/souyuken.ogg");
	int temp = getPositionY();
	setPositionY(temp + 10);
	setState(NORMAL);
	inTheAir_flag = true;
	initBlock();
 	velocityY = 10;
 	if(faceto)
 		velocityX = -2;
 	else
 		velocityX = 2;
	m_sprite->getAnimation()->play("DrangonPunch");
	force = 120;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.1f);
	this->scheduleOnce(schedule_selector(Hero::refresh),0.6f);
}
void Hero::cycloneKick()
{
	m_sprite->getAnimation()->play("CycloneKick");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/kale.ogg");
	force = 135;
	this->scheduleOnce(schedule_selector(Hero::setAttackRect),0.3f);
	this->scheduleOnce(schedule_selector(Hero::refresh),0.6f);
}
void Hero::refresh(float dt)
{
	this->setState(NORMAL);
	m_attack.isFinished = true;
	velocityX = 0;
	if (getMode() == LIGHTBLADE)
	{
		m_sprite->getAnimation()->play("SB_Stand");
	}
	else
		m_sprite->getAnimation()->play("Stand");
}
void Hero::setAttackRect(float dt)
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
void Hero::handBlade()
{
	if (inTheAir_flag)
	{
		if (getMode() == LIGHTBLADE)
		{
			setMode(SHIELD);
		}
		else
			setMode(LIGHTBLADE);
	}
	else
	{
		if (getMode() == LIGHTBLADE)
		{
			m_sprite->getAnimation()->play("Stand");
			setMode(SHIELD);
		}
		else
		{
			setState(FORCED);
			m_sprite->getAnimation()->playByIndex(13);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/haaaaa.ogg");
			scheduleOnce(schedule_selector(Hero::afterHandBlade),1.0f);
		}
	}
}
void Hero::afterHandBlade(float dt)
{
	setMode(LIGHTBLADE);
	setState(NORMAL);
	m_sprite->getAnimation()->playByIndex(18);
	m_sprite->setOpacity(255);
	m_sprite->setColor(ccc3(255,255,255));
}
void Hero::jump()
{
	if (inTheAir_flag == false && finished == false)
	{
		finished = true;
		if (getMode() == LIGHTBLADE)
		{
			m_sprite->getAnimation()->play("SB_Jump");
		}
		else
			m_sprite->getAnimation()->play("Jump");
		this->scheduleOnce(schedule_selector(Hero::doJump),0.33f);
	}
}
void Hero::doJump(float dt)
{
	int temp = getPositionY();
	if (getMode() == LIGHTBLADE)
	{
		m_sprite->getAnimation()->play("SB_Up");
	}
	else
		m_sprite->getAnimation()->play("Up");
	setState(NORMAL);
	setPositionY(temp + 10);
	initBlock();
	inTheAir_flag = true;
	finished = false;
	jumpMainFlag = false;		//�ڴ˴�ȷ��������������
	velocityY = 14;
}
void Hero::modeShield()
{
	setMode(SHIELD);
	setState(NORMAL);
	m_sprite->setOpacity(255);
	m_sprite->setColor(ccc3(255,255,255));
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/maxArmor.ogg");
	m_sprite->getAnimation()->play("Stand");
}
void Hero::modeIvisible()
{
	if (inTheAir_flag)
	{
		setMode(INVISIBLE);
		scheduleOnce(schedule_selector(Hero::afterModeIvisible),0.6f);
	}
	else
	{
		if (getMode() != INVISIBLE)
		{
			setState(FORCED);
			m_sprite->getAnimation()->play("ModeChange");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/Cloak.ogg");
			scheduleOnce(schedule_selector(Hero::afterModeIvisible),0.6f);
		}
	}
}
void Hero::afterModeIvisible(float dt)
{
	setMode(INVISIBLE);
	setState(NORMAL);
	m_sprite->setOpacity(50);
	m_sprite->setColor(ccc3(0,0,200));
	m_sprite->getAnimation()->play("Stand");
}
void Hero::modeClockUp()
{
	if (inTheAir_flag)
	{
		setMode(CLOCKUP);
		scheduleOnce(schedule_selector(Hero::afterModeClockUp),0.6f);
	}
	else
	{
		if (getMode() != CLOCKUP)
		{
			setState(FORCED);
			m_sprite->getAnimation()->play("ModeChange");
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Audio/Clock.ogg");
			scheduleOnce(schedule_selector(Hero::afterModeClockUp),0.6f);
		}
	}
}
void Hero::afterModeClockUp(float dt)
{
	setMode(CLOCKUP);
	setState(NORMAL);
	m_sprite->setColor(ccc3(30,255,40));
	m_sprite->setOpacity(255);
	m_sprite->getAnimation()->play("Stand");
}