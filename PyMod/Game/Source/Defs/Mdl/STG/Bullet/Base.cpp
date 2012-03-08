#include "PCH.h"
#include "Base.h"

#include "View/STG/DrawPriority.h"

#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Mdl::STG;
using namespace Bullet;
using namespace Game::Util::STG;
using namespace Selene;
namespace py = boost::python;

namespace
{
	// ����HP
	static const float INIT_HP = 100.0f;
}


// �R���X�g���N�^
Base::Base( const Vector2DF &pos, int radius )
: Actor::Base( Hit::RectI( pos, radius * 2, radius * 2 ) )
, mHitCircle( pos, radius )
, mHitRect( pos, radius * 2, radius * 2 )
, mHP( INIT_HP )
{
	mDamagedDrawParam.SetTexture( 
		py::extract<Game::Util::Sprite::PTexture>( 
		mAuxs.GetCommonResource().attr( "get" )( "bulletDamagedEffect" ) ) );
	mDamagedDrawParam.SetSrc( RectF( 0, 0, 64.0f, 64.0f ) );
	mDamagedDrawParam.SetDst( pos.MakeRect( GetHitRadius()*4, GetHitRadius()*4 ) );
	mDamagedDrawParam.SetPriority( Game::View::STG::PRI_ENEMYBULLET_DAMAGED );
	mDamagedDrawParam.SetColor( ColorF( 1.0f, 1.0f, 1.0f, 0 ) );
	mDamagedDrawParam.SetAlphaBlend( Game::Util::Sprite::AB_ADD );
}


// �X�V
void Base::Update()
{
	Actor::Base::Update();
	UpdateDamagedDraw();
}

void Base::UpdateMiddle()
{
	UpdateHitPos();

	if( mHP <= 0 )
	{
		Destruct();
	}
}

void Base::UpdateDamagedDraw()
{
	mDamagedDrawParam.SetDst( 
		GetPosition().MakeRect( GetHitRadius()*4, GetHitRadius()*4 ) );
	{
		ColorF color = mDamagedDrawParam.GetColor();
		if( color.a > 0 )
		{
			color.a -= 0.01f;
		}
		else
		{
			color.a = 0;
		}
		mDamagedDrawParam.SetColor( color );
	}
}

void Base::DrawMiddle() const
{
	if( mDamagedDrawParam.GetColor().a > 0 )
	{
		Defs::Util::Sprite::Sprite::draw( mDamagedDrawParam );
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
	if( mHP > 0 )
	{
		Actor::Base::SetValid( false );

		OnDestruct();
	}
}

void Base::Destruct( float hp )
{
	if( mHP > 0 )
	{
		mHP -= hp;
		OnDamaged( hp );
		{
			static const float MAX_ALPHA = 0.4f;
			auto color = mDamagedDrawParam.GetColor();
			if( color.a < MAX_ALPHA )
			{
				color.a += 0.1f;
			}
			else
			{
				color.a = MAX_ALPHA;
			}
			mDamagedDrawParam.SetColor( color );
		}

		if( mHP <= 0 )
		{
			Actor::Base::SetValid( false );

			OnDestruct( hp );
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


// �����蔻��̈ʒu�̍X�V
void Base::UpdateHitPos()
{
	mHitCircle.SetCenter( GetPosition() );
	mHitRect.SetPosition( GetPosition() );
}