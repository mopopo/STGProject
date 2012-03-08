#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Item/IItem.h"
#include "Defs/Mdl/STG/Actor/Base.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Locator/Trace.h"
#include "Defs/Mdl/STG/Auxs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Item
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public Game::Mdl::STG::Item::IItem
	{
	public:
		// �ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );
		// ���@�w�̓����蔻��̔��a�̎擾
		virtual float GetHitRadius() const;
		// �����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const;

	protected:
		Auxs mAuxs;

		// �R���X�g���N�^
		Base( const Game::Util::STG::Vector2DF &pos, float angle = -90.0f );

		// �ʒu�̐ݒ�
		void SetPosition( const Game::Util::STG::Vector2DF &pos );
		// ���@�w�̓����蔻��̔��a�̐ݒ�
		void SetHitRadius( int radius );
		// ���x�x�N�g���̕����̐ݒ�
		void SetAngle( float angle );

	private:
		Game::Util::STG::Hit::CircleI mHitCircle;
		Game::Util::STG::Locator::TraceF mLocator;

		// �X�V
		virtual void UpdateMiddle();

		virtual void Effect() const = 0;
	};
}
}
}
}