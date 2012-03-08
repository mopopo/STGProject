#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IBullet.h"
#include "Mdl/STG/Actor/Base.h"
#include "Util/Sprite/DrawParameter.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Hit/Rect.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
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
		, public IBullet
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const;
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const;
		// �j��
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HP�̎擾
		virtual float GetHP() const;
		// �����蔻��̔��a�̎擾
		virtual float GetHitRadius() const;

	protected:
		// �R���X�g���N�^
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, int radius );

		// HP�̐ݒ�
		void SetHP( float hp );
		// �����蔻��̔��a�̐ݒ�
		void SetHitRadius( int radius );

		// �����蔻��̈ʒu�̍X�V
		void UpdateHitPos();

	private:
		Util::STG::Hit::CircleI mHitCircle;
		Util::STG::Hit::RectI mHitRect;
		float mHP;
		Util::Sprite::DrawParameter mDamagedDrawParam;

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