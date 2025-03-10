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
	// 当たり判定の半径
	static const int HIT_RADIUS = 16;
	// 最大旋回角度
	static const float MAX_CIRCLING_ANGLE = 90.0f;
	// アイテムのサイズ
	static const Vector2DI ITEM_SIZE( 32, 32 );
	// 初期速度
	static const float INIT_SPEED = 1.5f;
}


// コンストラクタ
Base::Base( Actor::Base::PMode pMode, const Vector2DF &pos, float angle )
: Actor::Base( pMode, Hit::RectI( pos, ITEM_SIZE ) )
, mHitCircle( pos, HIT_RADIUS )
, mLocator( MAX_CIRCLING_ANGLE )
{
	mLocator.SetTracing( false );
	mLocator.GetPosition() = pos;
	SetAngle( angle );
}


// 更新
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


// 位置の取得
Vector2DF Base::GetPosition() const
{
	return mLocator.GetPosition();
}

// 外力の適用
Vector2DF Base::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}

// 自機ヘの当たり判定の半径の取得
float Base::GetHitRadius() const
{
	return static_cast<float>( mHitCircle.GetRadius() );
}

// 当たり判定
bool Base::IsHit( const Hit::CircleI &hit ) const
{
	return mHitCircle.IsHit( hit );
}

// 位置の設定
void Base::SetPosition( const Vector2DF &pos )
{
	mLocator.GetPosition() = pos;
	mHitCircle.SetCenter( pos );
	Actor::Base::SetValidRect( 
		Hit::RectI( pos, 
		mHitCircle.GetRadius() * 2, mHitCircle.GetRadius() * 2 ) );
}

// 自機ヘの当たり判定の設定
void Base::SetHitRadius( int radius )
{
	Actor::Base::SetValidRect( 
		Hit::RectI( mLocator.GetPosition(), radius * 2, radius * 2 ) );
	mHitCircle.SetRadius( radius );
}

// 速度ベクトルの方向の設定
void Base::SetAngle( float angle )
{
	mLocator.GetSpeed().SetUnitVector( angle ) *= INIT_SPEED;
}


// 共通リソースの取得
Base::PCommonResource Base::GetCommonResource() const
{
	return Actor::Base::GetMode()->GetScene()->GetResource();
}