#ifndef _Global__
#define _Global__
#include "cocos2d.h"
#include "AttackRect.h"
USING_NS_CC;

#define LftBtnPsnX		60
#define LftBtnPsnY		64				//���а�ť����
#define RgtBtnPsnX		124
#define RgtBtnPsnY 		64				//���а�ť����
#define JmpBtnPsnX		485
#define JmpBtnPsnY		64				//��Ծ��ť����
#define AtkBtnPsnX		550
#define AtkBtnPsnY		115				//������ť����

#define BladeBtnPsnX	230				//�⽣��ť����
#define BladeBtnPsnY	40

typedef enum{
	NORMAL = 0,			//����״̬
	WALKING,				//����״̬
	ATTACKING,				//����״̬
	HURT,						//����״̬
	FORCED					//ǿ��״̬
}HeroState;					//�������״̬

typedef enum{
	PATROLING = 0,		//Ѳ����
	REACHING,				//�ӽ�������
	ATTACK,					//�����У���HeroState��һ���£�������HeroState��ATTACKING�������ã�
	FORCE,						//ǿ��״̬����HeroState��һ���£�������HeroState��FORCED�������ã�
	STADINGBY,				//�����У���������״̬�Ľ�����Ѳ��״̬�Ŀ���
	DYING,						//����״̬��������ʾ�������� �����HPΪ0ʱ�������������ڲ����궯������ΪDIE
	DIE							//�ӹ��������н��˶���ɾ���ı�־
}EnemyState;
typedef enum
{
	SHIELD = 0,				//����ģʽ
	CLOCKUP,				//����ģʽ
	INVISIBLE,				//Ǳ��ģʽ
	FORCECONTROL,		//��������ģʽ
	LIGHTBLADE,			//�⽣״̬
	PISTOL,					//��ǹ״̬
	SHOTPUT,				//����״̬
	RPG							//RPG�����״̬
}HeroMode;
#define GRAVITY			0.7f				//�������ٶ�
#define  VelocityX			5					//ˮƽ��������ٶ�
#define  maxVelocityY	15				//��ֱ��������ٶ�

static CCPoint TMXPoint2GLPoint(CCPoint p)					//ͼ������ת��Ϊ��Ϸ����
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	return ccp(p.x * 16,visibleSize.height - (p.y * 16));
}
static CCPoint GLPoint2TMXPoint(CCPoint p)					//��Ϸ����ת��Ϊͼ������
{
	;}
#endif
