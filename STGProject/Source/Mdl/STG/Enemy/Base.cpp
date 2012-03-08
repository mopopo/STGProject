#include "PCH.h"
#include "Base.h"

#include "Ctrl/STG/Mode/IMode.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Enemy;
using namespace Util::STG;

namespace
{
	// �L���̈�̗]��
	static const int VALIDAREA_MARGIN = 300;
	// �_���[�W���󂯂�̈�
	static const Hit::RectI DAMAGED_AREA( 0, 0, 
		Util::Consts::SCREEN_SIZE.x - Util::Consts::STG_INFAREA_SIZE.x, 
		Util::Consts::SCREEN_SIZE.y, false );
}


// �R���X�g���N�^
Base::Base( PMode pMode, const Hit::RectI &hit, float hp )
: Actor::Base( pMode, hit )
, mHP( hp )
, mMaxHP( hp )
, mHitRect( hit )
{
	assert( mHP > 0 );

	Actor::Base::SetFrameCounting( false );
	Actor::Base::SetValidAreaMargin( VALIDAREA_MARGIN );
}


// �X�V
void Base::UpdateMiddle()
{
	mHitRect.SetPosition( GetPosition() );

	if( mHP <= 0 )
	{
		Destruct();
	}
}


// �����蔻��
bool Base::IsHit( const Hit::RectI &hit ) const
{
	return mHitRect.IsHit( hit );
}

// �j��
void Base::Destruct()
{
	if( mHP > 0 )
	{
		Actor::Base::SetValid( false );

		OnDestruct();
	}
}

void Base::Destruct( float hp )
{
	if( mHP > 0 && mHitRect.IsHit( DAMAGED_AREA ) )
	{
		mHP -= hp;
		OnDamaged( hp );

		if( mHP <= 0 )
		{
			Actor::Base::SetValid( false );

			OnDestruct( hp );
		}
		else if( mHP > mMaxHP )
		{
			mHP = mMaxHP;
		}
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


// �����蔻��̎擾
Hit::RectI Base::GetHitRect() const
{
	return mHitRect;
}

// �����蔻��̐ݒ�
void Base::SetHitRect( const Hit::RectI &hit )
{
	mHitRect = hit;
	Actor::Base::SetValidRect( hit );
}


// �����蔻��p�̔��a�̎擾
float Base::GetHitRadius() const
{
	Vector2DF widthHeight( mHitRect.GetWidthHeight() );
	return sqrt( Util::Pow( widthHeight.x ) + Util::Pow( widthHeight.y ) ) / 2;
}


// PrimalArmor����������Ă��邩���擾
bool Base::IsPAGenerated() const
{
	return false;
}

// PrimalArmor�̑��ʂ��擾
float Base::GetMaxPAAmount() const
{
	return 0;
}

// PrimalArmor�̎c�ʂ��擾
float Base::GetPAAmount() const
{
	return 0;
}