#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Bullet/IBullet.h"
#include "Defs/Mdl/STG/Actor/Base.h"
#include "Defs/Mdl/STG/Auxs.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Hit/Rect.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public Game::Mdl::STG::Bullet::IBullet
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const;
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const;
		// �j��
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HP�̎擾
		virtual float GetHP() const;
		// HP�̐ݒ�
		void SetHP( float hp );
		// �����蔻��̔��a�̎擾
		virtual float GetHitRadius() const;
		// �����蔻��̔��a�̐ݒ�
		void SetHitRadius( int radius );

	protected:
		// �R���X�g���N�^
		Base( const Game::Util::STG::Vector2DF &pos, int radius );

		// �����蔻��̈ʒu�̍X�V
		void UpdateHitPos();

	private:
		Game::Util::STG::Hit::CircleI mHitCircle;
		Game::Util::STG::Hit::RectI mHitRect;
		float mHP;
		Game::Util::Sprite::DrawParameter mDamagedDrawParam;
	protected:
		Auxs mAuxs;

		// �X�V
	public:
		virtual void Update();
	private:
		virtual void UpdateMiddle();
		virtual void UpdateDamagedDraw();
		virtual void DrawMiddle() const;

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) {}
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}