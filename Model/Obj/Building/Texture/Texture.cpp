#include"Texture.h"
Texture::Texture() {

}
void Texture::init() {
	this->bCover = false;
	switch ((Type)this->type)
	{
	case Texture::Type::GREEN:

		this->bAttack = false;
		this->bAttackPicChange = false;
		this->bMove = false;
		this->bMovePicChange = false;
		this->bStand = true;
		this->bStandPicChange = false;
		this->bOnce = true;
		this->high = 0;
		this->start_high = 0;
		this->bShowProgress = false;
		break;
	default:
		break;
	}

	Building::init();
}
Texture::Texture(int type, int x, int y, bool bAI) {
	Texture((Type)type, x, y, bAI);
}
Texture::Texture(Type type, int x, int y, bool bAI) {
	this->X = x;
	this->Y = y;
	this->type = (int)type;
	this->bAI = true;
	this->status = Status::STAND;
	this->fx = Direction::DOWN;
	this->init();

}
//��ɫ����
void Texture::die() {}

int Texture::GetZOrderY() {
	switch (this->type)
	{
	case (int)Texture::Type::GREEN:
		return this->Y + 100;
		break;
	default:
		break;
	}
}
//��ɫ �
void Texture::run(int tid) {
	Building::run(tid);
}//��������
 //��¶�ĵ��ö��󷽷��Ľӿ�
void* Texture::Method(std::string methName, void* param) {

	return Building::Method(methName, param);
}