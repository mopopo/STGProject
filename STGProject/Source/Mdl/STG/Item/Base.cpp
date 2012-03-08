#include "PCH.h"
#include "Base.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/MyShip/IMyShip.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Item;
using namespace Util::STG;

namespace
{
	// �����蔻��̔��a
	static const int HIT_RADIUS = 16;
	// �ő����p�x
	static const float MAX_CIRCLING_ANGLE = 90.0f;
	// �A�C�e���̃T�C�Y
	static const Vector2DI ITEM_SIZE( 32, 32 );
	// �������x
	static const float INIT_SPEED = 1.5f;
}


// �R���X�g���N�^
Base::Base( Actor::Base::PMode pMode, const Vector2DF &pos, float angle )
: Actor::Base( pMode, Hit::RectI( pos, ITEM_SIZE ) )
, mHitCircle( pos, HIT_RADIUS )
, mLocator( MAX_CIRCLING_ANGLE )
{
	mLocator.SetTracing( false );
	mLocator.GetPosition() = pos;
	SetAngle( angle );
}


// �X�V
void Base::UpdateMiddle()
{
	if( !GetActors().GetMyShip()->IsDisappeared() )
	{
		mLocator.GetTargetPosition() = 
			GetActors().GetMyShip()->GetPosition();
	}
	mLocator.Update();

	mHitCircle.SetCenter( GetPosition() );

	if( GetActors().GetMyShip()->IsHit_GetItem( mHitCircle ) )
	{
		Effect();

		Actor::Base::SetValid( false );
	}

	if( !mLocator.IsTracing() )
	{
		if( mLocator.GetSpeed().y >= 3.0f )
		{
			mLocator.GetSpeed().SetXY( mLocator.GetSpeed().x, 3.0f );
		}
		else
		{
			mLocator.ApplyExternalForce( Vector2DF( 0, 0.03f ) );
		}

		if( !GetActors().GetMyShip()->IsDisappeared() && 
			mLocator.GetSpeed().y >= 0 && 
			GetActors().GetMyShip()->IsHit_ItemRetrieve( mHitCircle ) )
		{
			mLocator.SetTracing( true );
		}
	}
	else
	{
		if( !GetActors().GetMyShip()->IsDisappeared() )
		{
			if( mLocator.GetSpeed().GetAbs() < 10.0f )
			{
				float angle = mLocator.GetPosition().GetAngle( 
					mLocator.GetTargetPosition() );
				mLocator.GetAccel().SetUnitVector( angle ) *= 1.0f;
			}
			else
			{
				mLocator.GetSpeed().Normalize() *= 10.0f;
				mLocator.GetAccel() = 0;
			}
		}
		else
		{
			mLocator.SetTracing( false );
			mLocator.GetAccel() = 0;
			mLocator.GetSpeed() = 0;
		}
	}
}


// �ʒu�̎擾
Vector2DF Base::GetPosition() const
{
	return mLocator.GetPosition();
}

// �O�͂̓K�p
Vector2DF Base::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}

// ���@�w�̓����蔻��̔��a�̎擾
float Base::GetHitRadius() const
{
	return static_cast<float>( mHitCircle.GetRadius() );
}

// �����蔻��
bool Base::IsHit( const Hit::CircleI &hit ) const
{
	return mHitCircle.IsHit( hit );
}

// �ʒu�̐ݒ�
void Base::SetPosition( const Vector2DF &pos )
{
	mLocator.GetPosition() = pos;
	mHitCircle.SetCenter( pos );
	Actor::Base::SetValidRect( 
		Hit::RectI( pos, 
		mHitCircle.GetRadius() * 2, mHitCircle.GetRadius() * 2 ) );
}

// ���@�w�̓����蔻��̐ݒ�
void Base::SetHitRadius( int radius )
{
	Actor::Base::SetValidRect( 
		Hit::RectI( mLocator.GetPosition(), radius * 2, radius * 2 ) );
	mHitCircle.SetRadius( radius );
}

// ���x�x�N�g���̕����̐ݒ�
void Base::SetAngle( float angle )
{
	mLocator.GetSpeed().SetUnitVector( angle ) *= INIT_SPEED;
}


// ���ʃ��\�[�X�̎擾
Base::PCommonResource Base::GetCommonResource() const
{
	return Actor::Base::GetMode()->GetScene()->GetResource();
}