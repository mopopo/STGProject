#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IEnemy.h"
#include "Mdl/STG/Actor/Base.h"
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
namespace Enemy
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public IEnemy
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const;
		// �j��
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HP�̎擾
		virtual float GetHP() const;
		// �����蔻��̎擾
		virtual Util::STG::Hit::RectI GetHitRect() const;

		// �����蔻��p�̔��a���擾
		virtual float GetHitRadius() const;

		// PrimalArmor����������Ă��邩���擾
		virtual bool IsPAGenerated() const;
		// PrimalArmor�̑��ʂ��擾
		virtual float GetMaxPAAmount() const;
		// PrimalArmor�̎c�ʂ��擾
		virtual float GetPAAmount() const;

	protected:
		// �R���X�g���N�^
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Hit::RectI &hit, float hp );
		const float mMaxHP;

		// HP�̐ݒ�
		void SetHP( float hp );
		// �����蔻��̐ݒ�
		void SetHitRect( const Util::STG::Hit::RectI &hit );

	private:
		Util::STG::Hit::RectI mHitRect;
		float mHP;

		// �X�V
		virtual void UpdateMiddle();

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) = 0;
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}