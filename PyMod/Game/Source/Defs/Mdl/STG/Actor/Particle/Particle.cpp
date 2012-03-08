#include "PCH.h"
#include "Particle.h"

#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Mdl::STG;
using namespace Actor::Particle;
using namespace Game::Util::STG;
using namespace Selene;

namespace
{
	static const float INIT_ZOOM_DEC_RATE = 0.01f;
	static const boost::numeric::interval<float> ZOOM_DEC_RATE_DOMAIN( 0.0f, 1.0f );
}


// �R���X�g���N�^
Particle::Particle( const Vector2DF &pos, const DrawParameter &dParam )
: Base( Hit::RectI() )
, mLocator( pos, Vector2DF(), Vector2DF() )
, mDrawParam( dParam )
, mZoomDecRate( INIT_ZOOM_DEC_RATE )
, mZoomRateCount( ZOOM_DEC_RATE_DOMAIN.upper() )
, mRotSpeed()
{
	ModifyValidRect();
}


// �ʒu�̎擾
Vector2DF Particle::GetPosition() const
{
	return mLocator.GetPosition();
}

// �O�͂̓K�p
Vector2DF Particle::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ���P�[�^�̎擾
Locator::LinearF &Particle::GetLocator()
{
	return mLocator;
}

// �`��p�����[�^�̎擾
Particle::DrawParameter Particle::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void Particle::SetDrawParameter( const DrawParameter &param )
{
	mDrawParam = param;

	ModifyValidRect();
}

// �g�嗦�̎擾
float Particle::GetZoomRate() const
{
	return mZoomRateCount;
}

// �g�嗦�̐ݒ�
void Particle::SetZoomRate( float rate )
{
	mZoomRateCount = rate;

	ModifyValidRect();
}

// �g�嗦�̌������̎擾
float Particle::GetZoomDecRate() const
{
	return mZoomDecRate;
}

// �g�嗦�̌������̐ݒ�
void Particle::SetZoomDecRate( float rate )
{
	assert( boost::numeric::in( rate, ZOOM_DEC_RATE_DOMAIN ) );

	mZoomDecRate = rate;
}

// ��]���x�̎擾
float Particle::GetRotSpeed() const
{
	return mRotSpeed;
}

// ��]���x�̐ݒ�
void Particle::SetRotSpeed( float speed )
{
	mRotSpeed = speed;
}


void Particle::OnUpdate()
{
	mLocator.Update();

	mZoomRateCount -= mZoomDecRate;
	if( mZoomRateCount <= 0 )
	{
		Base::SetValid( false );
	}

	mDrawParam.SetRotDegree( mDrawParam.GetRotDegree() + mRotSpeed );
	if( mDrawParam.GetRotDegree() >= 180 )
	{
		mDrawParam.SetRotDegree( mDrawParam.GetRotDegree() - 180 );
	}
	else if( mDrawParam.GetRotDegree() <= -180 )
	{
		mDrawParam.SetRotDegree( mDrawParam.GetRotDegree() + 180 );
	}

	ModifyValidRect();
}

void Particle::OnDraw() const
{
	if( Base::IsValid() )
	{
		Defs::Util::Sprite::Sprite::draw( CreateDrawParam() );
	}
}

void Particle::OnErase()
{
	mAuxs.CreateFadeOut( CreateDrawParam () );
}


Particle::DrawParameter Particle::CreateDrawParam() const
{
	DrawParameter dParam = mDrawParam;
	RectF dst = dParam.GetDst();
	dst.w *= mZoomRateCount;
	dst.h *= mZoomRateCount;
	dst = mLocator.GetPosition().MakeRect( dst.w, dst.h );
	dParam.SetDst( dst );

	return dParam;
}

void Particle::ModifyValidRect()
{
	Hit::RectI validRect;
	validRect.SetPosition( mLocator.GetPosition() );
	validRect.SetWidthHeight( 
		mDrawParam.GetDst().w * mZoomRateCount, 
		mDrawParam.GetDst().h * mZoomRateCount );
	Base::SetValidRect( validRect );
}