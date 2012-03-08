#include "PCH.h"
#include "Particle.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Actor::Particle;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const float INIT_ZOOM_DEC_RATE = 0.01f;
	static const boost::numeric::interval<float> ZOOM_DEC_RATE_DOMAIN( 0.0f, 1.0f );
}


// �R���X�g���N�^
Particle::Particle( PMode pMode, const Vector2DF &pos, 
				   const Util::Sprite::DrawParameter &dParam )
: Base( pMode, Hit::RectI() )
, mLocator( pos, Vector2DF(), Vector2DF() )
, mDrawParam( dParam )
, mZoomDecRate( INIT_ZOOM_DEC_RATE )
, mZoomRateCount( ZOOM_DEC_RATE_DOMAIN.upper() )
, mAuxs( pMode )
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
Util::Sprite::DrawParameter Particle::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void Particle::SetDrawParameter( const Util::Sprite::DrawParameter &param )
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


void Particle::OnUpdate()
{
	mLocator.Update();

	mZoomRateCount -= mZoomDecRate;
	if( mZoomRateCount <= 0 )
	{
		Base::SetValid( false );
	}

	ModifyValidRect();
}

void Particle::OnDraw() const
{
	if( Base::IsValid() )
	{
		Util::Sprite::Manager::Draw( CreateDrawParam() );
	}
}

void Particle::OnErase()
{
	mAuxs.CreateFadeOut( CreateDrawParam () );
}


Util::Sprite::DrawParameter Particle::CreateDrawParam() const
{
	Util::Sprite::DrawParameter dParam = mDrawParam;
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