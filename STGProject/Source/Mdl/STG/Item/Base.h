#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IItem.h"
#include "Mdl/STG/Actor/Base.h"
#include "Util/STG/Hit/Circle.h"
#include "Util/STG/Locator/Trace.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
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
		, public IItem
	{
	public:
		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );
		// ���@�w�̓����蔻��̔��a�̎擾
		virtual float GetHitRadius() const;
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const;

	protected:
		// �R���X�g���N�^
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, float angle = 270.0f );

		// ���ʃ��\�[�X�̎擾
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PCommonResource;
		PCommonResource GetCommonResource() const;

		// �ʒu�̐ݒ�
		void SetPosition( const Util::STG::Vector2DF &pos );
		// ���@�w�̓����蔻��̔��a�̐ݒ�
		void SetHitRadius( int radius );
		// ���x�x�N�g���̕����̐ݒ�
		void SetAngle( float angle );

	private:
		Util::STG::Hit::CircleI mHitCircle;
		Util::STG::Locator::TraceF mLocator;

		// �X�V
		virtual void UpdateMiddle();

		virtual void Effect() const = 0;
	};
}
}
}
}