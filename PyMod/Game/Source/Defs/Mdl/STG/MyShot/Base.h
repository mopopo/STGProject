#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/MyShot/IMyShot.h"
#include "Defs/Mdl/STG/Actor/Base.h"
#include "Defs/Mdl/STG/Auxs.h"
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
namespace MyShot
{
#pragma warning( disable:4250 )
	class Base
		: public Actor::Base
		, public Game::Mdl::STG::MyShot::IMyShot
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const;
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const;
		// �j��
		virtual void Destruct();
		virtual void Destruct( float hp );

		// �ő�HP�̎擾
		float GetMaxHP() const;
		// �ő�HP�̐ݒ�
		void SetMaxHP( float hp );
		// HP�̎擾
		virtual float GetHP() const;
		// HP�̐ݒ�
		void SetHP( float hp );
		// �����蔻��̔��a�̎擾
		virtual float GetHitRadius() const;
		// �����蔻��̔��a�̐ݒ�
		void SetHitRadius( int radius );

		// �G�ւ̃_���[�W�̎擾
		virtual float GetDamage() const;
		// PrimalArmor�ւ̃_���[�W���擾
		virtual float GetPADamage() const;
		// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ������擾
		virtual bool IsForcibleForPA() const;
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

	protected:
		Auxs mAuxs;

		// �R���X�g���N�^
		Base( const Game::Util::STG::Vector2DF &pos, int radius, float baseDamage );

		// �����蔻��̈ʒu�̍X�V
		void UpdateHitPos();

		const Game::Util::STG::Hit::CircleI &GetHitCircle() const;
		const Game::Util::STG::Hit::RectI &GetHitRect() const;

	private:
		Game::Util::STG::Hit::CircleI mHitCircle;
		Game::Util::STG::Hit::RectI mHitRect;
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