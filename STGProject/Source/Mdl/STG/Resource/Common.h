#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/noncopyable.hpp>
#include "Util/Font/Manager.h"
#include "Util/Sprite/Manager.h"
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
namespace Resource
{
	class Common
		: public boost::noncopyable
	{
	public:
		// �R���X�g���N�^
		Common();

		// �����`��p�t�H���g�̎擾
		Util::Font::PFont GetFont16( Selene::Sint32 priority, 
			bool shakable = true, 
			Selene::Sint32 size = 16 ) const;
		Util::Font::PFont GetFont32( Selene::Sint32 priority, 
			bool shakable = true, 
			Selene::Sint32 size = 32 ) const;

		// ���\���̈�̔w�i�摜
		static const Util::Sprite::SrcDef INFAREA_BACK;
		Util::Sprite::PTexture GetInfAreaBack() const;

		// 1UP�A�C�e���̉摜
		static const Util::Sprite::SrcDef ITEM_EXTEND;
		Util::Sprite::PTexture GetItemExtend() const;
		// ����p���[�A�b�v�̉摜
		static const Util::Sprite::SrcDef ITEM_POWERUP;
		Util::Sprite::PTexture GetItemPowerUp() const;
		// ����U���⋋�A�C�e���̉摜
		static const Util::Sprite::SrcDef ITEM_SPATTACK;
		Util::Sprite::PTexture GetItemSpAttack() const;

		// �����̃A�j���[�V�����摜
		static const Util::Sprite::SrcDef EXPLOSION;
		Util::Sprite::PTexture GetExplosion() const;

		// �G�e�̉摜
		static const Util::Sprite::SrcDef BULLET_RED;
		Util::Sprite::PTexture GetBulletRed() const;
		static const Util::Sprite::SrcDef BULLET_GREEN;
		Util::Sprite::PTexture GetBulletGreen() const;
		static const Util::Sprite::SrcDef BULLET_BLUE;
		Util::Sprite::PTexture GetBulletBlue() const;
		static const Util::Sprite::SrcDef BULLET_WHITE;
		Util::Sprite::PTexture GetBulletWhite() const;
		static const Util::Sprite::SrcDef BULLET_PURPLE;
		Util::Sprite::PTexture GetBulletPurple() const;

		// �G�e�_���[�W�G�t�F�N�g�̉摜
		static const Util::Sprite::SrcDef BULLET_DAMAGED_EFFECT;
		Util::Sprite::PTexture GetBulletDamagedEffect() const;

		// HP�Q�[�W�̉摜
		static const Util::Sprite::SrcDef HP_GAUGE;
		Util::Sprite::PTexture GetHPGauge() const;

	private:
		// �����`��p�t�H���g
		Util::Font::PFont mpFont16;
		Util::Font::PFont mpFont32;

		// ���\���̈�̔w�i�摜
		Util::Sprite::PTexture mpInfAreaBack;

		// 1UP�A�C�e���̉摜
		Util::Sprite::PTexture mpItemExtend;
		// ����p���[�A�b�v�̉摜
		Util::Sprite::PTexture mpItemPowerUp;
		// ����U���⋋�A�C�e���̉摜
		Util::Sprite::PTexture mpItemSpAttack;

		// �����̃A�j���[�V�����摜
		Util::Sprite::PTexture mpExplosion;

		// �G�e�̉摜
		Util::Sprite::PTexture mpBulletRed;
		Util::Sprite::PTexture mpBulletGreen;
		Util::Sprite::PTexture mpBulletBlue;
		Util::Sprite::PTexture mpBulletWhite;
		Util::Sprite::PTexture mpBulletPurple;

		// �G�e�_���[�W�G�t�F�N�g�̉摜
		Util::Sprite::PTexture mpBulletDamagedEffect;

		// HP�Q�[�W�̉摜
		Util::Sprite::PTexture mpHPGauge;
	};
}
}
}
}