#include "TitleLayer.h"
#include "Scene.h"
#include "SimpleAudioEngine.h"
#include "GameOverLayer.h"
USING_NS_CC;

bool TitleLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Audio/00-Title.mp3",true);
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//����ͼ�������㣬��Ϊ��̬�����´��봴��֮
	CCSprite* sp_Background1 = CCSprite::create("menu_back.png");
	//sp_Background1->setScale(0.8);
	CCSprite* sp_Background2 = CCSprite::create("menu_back.png");
	//sp_Background2->setScale(0.8);
	sp_Background1->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	sp_Background2->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));

	this->addChild(sp_Background1,0);			//���ò�ι�ϵ��1����2������
	this->addChild(sp_Background2,1);
	//������³�����ƴ�����Logo���飺
	CCSprite* sp_QiluLogo = CCSprite::create("sp_logo.png");
	sp_QiluLogo->setPosition(ccp(origin.x+visibleSize.width-sp_QiluLogo->getContentSize().width/2+2,visibleSize.height-sp_QiluLogo->getContentSize().height/2-2));
	/*
	/�ڴ��ڼ䴴��һ�������������ͼ��һֱ��������С���䶯
	*/
	CCScaleTo* logoScale = CCScaleTo::create(0.4f,1.12f,1.12f);  
	CCScaleTo* logoScaler = CCScaleTo::create(0.4f,1,1);
	CCSequence* logosqce = CCSequence::create(logoScale,logoScaler,NULL);
	CCRepeatForever* logoRepeat = CCRepeatForever::create(logosqce);
	this->addChild(sp_QiluLogo,5);
	sp_QiluLogo->runAction(logoRepeat);
	/*
	/�ڴ˴������ĸ���ť��������ˣ�Ȼ�󴴽�һ��CCMenu���������������
	/��ʾ��ͼ������ȥ
	*/
	//////newgame
	CCMenuItemImage* pNewGame =  CCMenuItemImage::create("new_game.png",
		"new_gameP.png",
		this,menu_selector(TitleLayer::newGmeBtnCallBack));
	pNewGame->setPosition(ccp(-visibleSize.width/2+pNewGame->getContentSize().width,
		-visibleSize.height/2+2.75*pNewGame->getContentSize().height));//menuIamge��Ĭ������ԭ������Ļ�е�
//////////	continue game
	CCMenuItemImage* pContGame =  CCMenuItemImage::create("con_game.png",
		"con_gameP.png",
		this,menu_selector(TitleLayer::ctnGmeBtnCallBack));
	pContGame->setPosition(ccp(-visibleSize.width/2+4.8*pContGame->getContentSize().width/2,
		-visibleSize.height/2+2.75*pContGame->getContentSize().height));
	/////////////team
	CCMenuItemImage* pTeamGame =  CCMenuItemImage::create("team_game.png",
		"team_gameP.png",
		this,menu_selector(TitleLayer::tmStudBtnCallBack));
	pTeamGame->setPosition(ccp(-visibleSize.width/2+pTeamGame->getContentSize().width,
		-visibleSize.height/2+1.2*pTeamGame->getContentSize().height));
	///////////////quit game
	CCMenuItemImage* pQuitGame =  CCMenuItemImage::create("quit_game.png",
		"quit_gameP.png",
		this,menu_selector(TitleLayer::quitGmeBtnCallBack));
	pQuitGame->setPosition(ccp(-visibleSize.width/2+4.8*pNewGame->getContentSize().width/2,
		-visibleSize.height/2+1.2*pQuitGame->getContentSize().height));
	//�˵�newgame�Ķ�̬Ч��ʵ��
	/*
    menuActionForever(pNewGame);
	menuActionForever(pContGame);
	menuActionForever(pTeamGame);
	menuActionForever(pQuitGame);
	*/
	CCMenu* pMenuGame = CCMenu::create(pNewGame,pContGame,pTeamGame,pQuitGame,NULL);
	pMenuGame->setPosition(ccp(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
	this->addChild(pMenuGame,5);
	return true;
};
void TitleLayer::menuActionForever(CCMenuItemImage* pImage)
{
	CCScaleTo* pImageGameScale = CCScaleTo::create(0.4f,1.05f,1.05f);  
	CCScaleTo* pImageGameScaler = CCScaleTo::create(0.4f,1,1);
	CCSequence* pImageGamesqce = CCSequence::create(pImageGameScale,pImageGameScaler,NULL);
	CCRepeatForever* pImageGameRepeat = CCRepeatForever::create(pImageGamesqce);
	pImage->runAction(pImageGameRepeat);
}
//////////////////��ť�Ļص�����/////////////////////////////////////
void TitleLayer::newGmeBtnCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f,Scene::story00()));
}
void TitleLayer::ctnGmeBtnCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f,Scene::ctnLayer()));
}
void TitleLayer::tmStudBtnCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2f,Scene::aboutScene()));
}
void TitleLayer::quitGmeBtnCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}