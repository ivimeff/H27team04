#include "Effect.h"

Effect::Effect(char* _textureName, GamePlayBundle* _GamePlayBundle, def::Vector2 _position, def::Vector2 _size, def::AnimBase _aBase) :
Character(_GamePlayBundle, _position, _size), textureName(_textureName), aBase(_aBase)
{

}

Effect::~Effect() {}

void Effect::init()
{

}

void Effect::update()
{
	if(aBase.update()) deadFlg = true;
}

void Effect::draw()
{
	def::Vector2 cPos = camera->getPosition(),
		dPos = position - cPos - halfSize;
	def::Rect srcRect = aBase.getAniRect(size);
	int layer = mapData->getLayer(getRect().bottom - 1);
	renderer->addDrawOrder(
		def::DRAWORDER(
		textureName, dPos, aBase.getAniRect(size)
		), layer
		);


}