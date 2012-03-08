#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IMyShot.h"
#include "Mdl/STG/Actor/Base.h"
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
namespace MyShot
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public IMyShot
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const;
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const;
		// �j��
		virtual void Destruct();
		virtual void Destruct( float hp );

		// �ő�HP�̎擾
		float GetMaxHP() const;
		// HP�̎擾
		virtual float GetHP() const;
		// �����蔻��̔��a�̎擾
		virtual float GetHitRadius() const;

		// �G�ւ̃_���[�W�̎擾
		virtual float GetDamage() const;
		// PrimalArmor�ւ̃_���[�W���擾
		virtual float GetPADamage() const;
		// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ������擾
		virtual bool IsForcibleForPA() const;

	protected:
		// �R���X�g���N�^
		Base( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, int radius, float baseDamage );

		// �ő�HP�̐ݒ�
		void SetMaxHP( float hp );
		// HP�̐ݒ�
		void SetHP( float hp );

		// �����蔻��̈ʒu�̍X�V
		void UpdateHitPos();
		// �����蔻��̔��a�̐ݒ�
		void SetHitRadius( int radius );

		const Util::STG::Hit::CircleI &GetHitCircle() const;
		const Util::STG::Hit::RectI &GetHitRect() const;

		// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ�����ݒ�
		void SetForcibleForPA( bool forcible );
		// �_���[�W���󂯂Ȃ����ǂ������擾
		bool IsNoDamage() const;
		// �_���[�W���󂯂Ȃ����ǂ�����ݒ�
		void SetNoDamage( bool noDamage );
		// ��{�_���[�W�̎擾
		float GetBaseDamage() const;
		// ��{�_���[�W�̐ݒ�
		void SetBaseDamage( float damage );
		// PrimalArmor�ւ̊�{�_���[�W���擾
		float GetPABaseDamage() const;
		// PrimalArmor�ւ̊�{�_���[�W��ݒ�
		void SetPABaseDamage( float damage );
		// �_���[�W�L�����̎擾
		float GetDamageRate() const;
		// �_���[�W�L�����̐ݒ�
		void SetDamageRate( float rate );
		// �_���[�W�L�����̌������̎擾
		float GetDamageRateDec() const;
		// �_���[�W�L�����̌������̐ݒ�
		void SetDamageRateDec( float dec );
		// �_���[�W�L�����̍ŏ��l�̎擾
		float GetDamageRateMin() const;
		// �_���[�W�L�����̍ŏ��l�̐ݒ�
		void SetDamageRateMin( float min );

	private:
		Util::STG::Hit::CircleI mHitCircle;
		Util::STG::Hit::RectI mHitRect;
		float mMaxHP, mHP;
		bool mNoDamage;
		float mBaseDamage, mDamageRate, mDamageRateDec, mDamageRateMin;
		float mPABaseDamage;
		bool mForcibleForPA;

		// �X�V
		virtual void UpdateMiddle();
		// �G�Ƀ_���[�W��^���鏈��
		virtual void ApplyDamageToEnemy();

		virtual void OnDestruct() = 0;
		virtual void OnDamaged( float damage ) {}
		virtual void OnDestruct( float hp ) = 0;
	};
}
}
}
}