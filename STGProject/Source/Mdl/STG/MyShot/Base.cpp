#include "PCH.h"
#include "Base.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Enemy/IEnemy.h"

using namespace Game;
using namespace Mdl::STG;
using namespace MyShot;
using namespace Util::STG;

namespace
{
	// ����HP
	static const float INIT_HP = 100.0f;
}


// �R���X�g���N�^
Base::Base( Actor::Base::PMode pMode, const Vector2DF &pos, int radius, float baseDamage )
: Actor::Base( pMode, Hit::RectI( pos, radius * 2, radius * 2 ) )
, mHitCircle( pos, radius )
, mHitRect( pos, radius * 2, radius * 2 )
, mMaxHP( INIT_HP )
, mHP( INIT_HP )
, mNoDamage( false )
, mBaseDamage( baseDamage )
, mDamageRate( 1.0f )
, mDamageRateDec( 0.0f )
, mDamageRateMin( 1.0f )
, mPABaseDamage( baseDamage )
, mForcibleForPA( false )
{
}


// �X�V
void Base::UpdateMiddle()
{
	UpdateHitPos();

	if( mHP <= 0 )
	{
		Destruct();
	}
	else
	{
		if( mDamageRate > mDamageRateMin )
		{
			mDamageRate -= mDamageRateDec;
		}
		else
		{
			mDamageRate = mDamageRateMin;
		}

		ApplyDamageToEnemy();
	}
}

// �G�Ƀ_���[�W��^���鏈��
void Base::ApplyDamageToEnemy()
{
	std::set<Enemy::PEnemy> enemies;
	GetActors().DetectEnemyHitAll( mHitRect, enemies );
	if( !enemies.empty() )
	{
		foreach( Enemy::PEnemy pEnemy, enemies )
		{
			pEnemy->Destruct( GetDamage() );
		}

		Destruct();
	}
}


// �����蔻��
bool Base::IsHit( const Hit::CircleI &hit ) const
{
	return mHitCircle.IsHit( hit );
}

bool Base::IsHit( const Hit::RectI &hit ) const
{
	return mHitRect.IsHit( hit );
}

// �j��
void Base::Destruct()
{
	if( Actor::Base::IsValid() )
	{
		Actor::Base::SetValid( false );

		OnDestruct();
	}
}

void Base::Destruct( float hp )
{
	if( Actor::Base::IsValid() )
	{
		if( !mNoDamage )
		{
			mHP -= hp;
		}
		OnDamaged( hp );

		if( mHP <= 0 )
		{
			Actor::Base::SetValid( false );

			OnDestruct( hp );
		}
	}
}


// �ő�HP�̎擾
float Base::GetMaxHP() const
{
	return mMaxHP;
}

// �ő�HP�̐ݒ�
void Base::SetMaxHP( float hp )
{
	mMaxHP = hp;
	if( mHP > mMaxHP )
	{
		mHP = mMaxHP;
	}
}

// HP�̎擾
float Base::GetHP() const
{
	return mHP;
}

// HP�̐ݒ�
void Base::SetHP( float hp )
{
	mHP = hp;
}

// �����蔻��̔��a�̎擾
float Base::GetHitRadius() const
{
	return static_cast<float>( mHitCircle.GetRadius() );
}

// �����蔻��̔��a�̐ݒ�
void Base::SetHitRadius( int radius )
{
	mHitCircle.SetRadius( radius );
	mHitRect.SetWidthHeight( radius * 2, radius * 2 );
	Actor::Base::SetValidRect( mHitRect );
}


const Hit::CircleI &Base::GetHitCircle() const
{
	return mHitCircle;
}

const Hit::RectI &Base::GetHitRect() const
{
	return mHitRect;
}


// �����蔻��̈ʒu�̍X�V
void Base::UpdateHitPos()
{
	mHitCircle.SetCenter( GetPosition() );
	mHitRect.SetPosition( GetPosition() );
}


// �G�ւ̃_���[�W�̎擾
float Base::GetDamage() const
{
	return mBaseDamage * mHP/mMaxHP * mDamageRate;
}

// PrimalArmor�ւ̃_���[�W���擾
float Base::GetPADamage() const
{
	return mPABaseDamage * mDamageRate;
}

// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ������擾
bool Base::IsForcibleForPA() const
{
	return mForcibleForPA;
}

// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ�����ݒ�
void Base::SetForcibleForPA( bool forcible )
{
	mForcibleForPA = forcible;
}

// �_���[�W���󂯂Ȃ����ǂ������擾
bool Base::IsNoDamage() const
{
	return mNoDamage;
}

// �_���[�W���󂯂Ȃ����ǂ�����ݒ�
void Base::SetNoDamage( bool noDamage )
{
	mNoDamage = noDamage;
}

// ��{�_���[�W�̎擾
float Base::GetBaseDamage() const
{
	return mBaseDamage;
}

// ��{�_���[�W�̐ݒ�
void Base::SetBaseDamage( float damage )
{
	mBaseDamage = damage;
}

// PrimalArmor�ւ̊�{�_���[�W���擾
float Base::GetPABaseDamage() const
{
	return mPABaseDamage;
}

// PrimalArmor�ւ̊�{�_���[�W��ݒ�
void Base::SetPABaseDamage( float damage )
{
	mPABaseDamage = damage;
}

// �_���[�W�L�����̎擾
float Base::GetDamageRate() const
{
	return mDamageRate;
}

// �_���[�W�L�����̐ݒ�
void Base::SetDamageRate( float rate )
{
	if( rate < mDamageRateMin )
	{
		mDamageRate = mDamageRateMin;
	}
	else
	{
		mDamageRate = rate;
	}
}

// �_���[�W�L�����̌������̎擾
float Base::GetDamageRateDec() const
{
	return mDamageRateDec;
}

// �_���[�W�L�����̌������̐ݒ�
void Base::SetDamageRateDec( float dec )
{
	mDamageRateDec = dec;
}

// �_���[�W�L�����̍ŏ��l�̎擾
float Base::GetDamageRateMin() const
{
	return mDamageRateMin;
}

// �_���[�W�L�����̍ŏ��l�̐ݒ�
void Base::SetDamageRateMin( float min )
{
	mDamageRateMin = min;

	if( mDamageRate < min )
	{
		mDamageRate = min;
	}
}