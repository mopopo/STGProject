#include "PCH.h"
#include "Resource.h"

using namespace Game;
using namespace Mdl::STG::MyShip::TypeA;
using namespace Util::STG;
using namespace Util::Sprite;
using namespace Selene;

const SrcDef Resource::MY_SHIP( L"MyShip/Triangle.dds", 0, 0, 64, 64 );
const SrcDef Resource::HIT_MARK( L"RedCircle.dds", 0, 0, 64, 64 );
const SrcDef Resource::OPTION( L"MyShip/VistaLogo.dds", 0, 0, 256, 256 );
const SrcDef Resource::LASER( L"BlueCircle.dds", 0, 0, 64, 64 );
const SrcDef Resource::BLUE_CIRCLE( L"BlueCircle.dds", 0, 0, 64, 64 );
const SrcDef Resource::MISSILE( L"MyShip/Mine.dds", 0, 0, 256, 256 );
const SrcDef Resource::EXPLOSION( L"Explode.dds", 0, 0, 96*8, 96*2 );


// �R���X�g���N�^
Resource::Resource()
{
	mpMyShip = Manager::LoadTexture( MY_SHIP.GetName() );
	mpHitMark = Manager::LoadTexture( HIT_MARK.GetName() );
	mpOption = Manager::LoadTexture( OPTION.GetName() );
	mpLaser = Manager::LoadTexture( LASER.GetName() );
	mpBlueCircle = Manager::LoadTexture( BLUE_CIRCLE.GetName() );
	mpMissile = Manager::LoadTexture( MISSILE.GetName() );
	mpExplosion = Manager::LoadTexture( EXPLOSION.GetName() );
}


// ���@�̉摜
PTexture Resource::GetMyShip() const
{
	return mpMyShip;
}

// ���@�̓����蔻��̉摜
PTexture Resource::GetHitMark() const
{
	return mpHitMark;
}

// ���@�I�v�V�����摜
PTexture Resource::GetOption() const
{
	return mpOption;
}

// ���@���[�U�[�̉摜
PTexture Resource::GetLaser() const
{
	return mpLaser;
}

// �ۂ̉摜
PTexture Resource::GetBlueCircle() const
{
	return mpBlueCircle;
}

// ���@�~�T�C���̉摜
PTexture Resource::GetMissile() const
{
	return mpMissile;
}

// �����̉摜�̒ǉ�
PTexture Resource::GetExplosion() const
{
	return mpExplosion;
}