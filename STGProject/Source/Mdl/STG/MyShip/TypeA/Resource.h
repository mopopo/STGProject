#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sprite/SrcDef.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
namespace TypeA
{
	class Resource
	{
	public:
		// �R���X�g���N�^
		Resource();

		// ���@�̉摜
		Util::Sprite::PTexture GetMyShip() const;
		static const Util::Sprite::SrcDef MY_SHIP;
		// ���@�̓����蔻��̉摜
		Util::Sprite::PTexture GetHitMark() const;
		static const Util::Sprite::SrcDef HIT_MARK;
		// ���@�I�v�V�����摜
		Util::Sprite::PTexture GetOption() const;
		static const Util::Sprite::SrcDef OPTION;
		// ���@���[�U�[�̉摜
		Util::Sprite::PTexture GetLaser() const;
		static const Util::Sprite::SrcDef LASER;
		// �ۂ̉摜
		Util::Sprite::PTexture GetBlueCircle() const;
		static const Util::Sprite::SrcDef BLUE_CIRCLE;
		// ���@�~�T�C���̉摜
		Util::Sprite::PTexture GetMissile() const;
		static const Util::Sprite::SrcDef MISSILE;
		// �����̉摜�̒ǉ�
		Util::Sprite::PTexture GetExplosion() const;
		static const Util::Sprite::SrcDef EXPLOSION;

	private:
		Util::Sprite::PTexture mpMyShip;
		Util::Sprite::PTexture mpHitMark;
		Util::Sprite::PTexture mpOption;
		Util::Sprite::PTexture mpLaser;
		Util::Sprite::PTexture mpBlueCircle;
		Util::Sprite::PTexture mpMissile;
		Util::Sprite::PTexture mpExplosion;
	};
}
}
}
}
}