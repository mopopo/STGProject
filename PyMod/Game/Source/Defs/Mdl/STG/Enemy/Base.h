#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Enemy/IEnemy.h"
#include "Defs/Mdl/STG/Actor/Base.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------
namespace Defs
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
		, public Game::Mdl::STG::Enemy::IEnemy
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const;
		// �j��
		virtual void Destruct();
		virtual void Destruct( float hp );

		// HP�̎擾
		virtual float GetHP() const;
		// HP�̐ݒ�
		void SetHP( float hp );
		// �����蔻��̎擾
		virtual Game::Util::STG::Hit::RectI GetHitRect() const;
		// �����蔻��̐ݒ�
		void SetHitRect( const Game::Util::STG::Hit::RectI &hit );

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
		Base( const Game::Util::STG::Hit::RectI &hit, float hp );

	private:
		Game::Util::STG::Hit::RectI mHitRect;
		float mHP;
		const float mMaxHP;

		// �X�V
		virtual void UpdateMiddle();

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) {}
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}