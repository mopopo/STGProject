#include "PCH.h"
#include "MLActor.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"
#include "Mdl/STG/Bullet/Linear.h"
#include "Mdl/STG/MyShip/IMyShip.h"


using namespace Game;
using namespace Mdl::STG;
using namespace Bullet::BulletML;
using namespace Util::STG;

const double MLActor::DEFAULT_RANK = 0.1;

namespace
{
	static const double DEFAULT_SPEED = 4.0;
}


MLActor::MLActor( PMode pMode, PBMLParser bp, 
	const Vector2DF &pos )
	: Base( pMode, pos, 0 )
	, BulletMLRunner( bp.get() )
	, mLocator( pos )
	, mDrawParam()
	, mAuxs( pMode )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
	Actor::Base::SetFrameCounting( false );
}

MLActor::MLActor( PMode pMode, PBMLParser bp, 
	const Locator::LinearF &locator, int hitRadius, 
	const Util::Sprite::DrawParameter &drawParam )
	: Base( pMode, locator.GetPosition(), hitRadius )
	, BulletMLRunner( bp.get() )
	, mLocator( locator )
	, mDrawParam( drawParam )
	, mAuxs( pMode )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
}

MLActor::MLActor( PMode pMode, PBMLParser bp, BulletMLState *bs, 
	const Locator::LinearF &locator, int hitRadius, 
	const Util::Sprite::DrawParameter &drawParam, 
	const CreateParamList &createParamList, 
	float angle )
	: Base( pMode, locator.GetPosition(), hitRadius )
	, BulletMLRunner( bs )
	, mLocator( locator )
	, mDrawParam( drawParam )
	, mAuxs( pMode )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList( createParamList )
	, mAngle( angle )
	, mpBMLParser( bp )
{
}


Vector2DF MLActor::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF MLActor::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


Locator::LinearF &MLActor::GetLocator()
{
	return mLocator;
}

const Util::Sprite::DrawParameter &MLActor::GetDrawParameter() const
{
	return mDrawParam;
}

void MLActor::SetDrawParameter( const Util::Sprite::DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


double MLActor::GetRank() const
{
	return mRank;
}

void MLActor::SetRank( double rank )
{
	assert( rank >= 0 && rank <= 1 );

	mRank = rank;
}

MLActor::CreateParamList &MLActor::GetCreateParamList()
{
	return mCreateParamList;
}


void MLActor::OnUpdate()
{
	BulletMLRunner::run();

	mLocator.Update();
	if( mLocator.GetSpeed().GetAbs() > 0 )
	{
		mAngle = mLocator.GetSpeed().GetAngle();
	}

	mDrawParam.SetDst( 
		mLocator.GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );

	mFrameCount++;

	//if( BulletMLRunner::isEnd() )
	//{
	//	Actor::Base::Erase();
	//}
}

void MLActor::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void MLActor::OnDestruct()
{
	mAuxs.CreateParticle( mDrawParam );
}

void MLActor::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void MLActor::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}


/// ���̒e�̊p�x�����߂�
// �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
double MLActor::getBulletDirection()
{
	return mAngle + 90;
}

/// ���̒e���玩�@��_���p�x�����߂�
// �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
double MLActor::getAimDirection()
{
	return mLocator.GetPosition().GetAngle( 
		Actor::Base::GetActors().GetMyShip()->GetPosition() ) + 90;
}

/// ���̒e�̑��x�����߂�
double MLActor::getBulletSpeed()
{
	return mLocator.GetSpeed().GetAbs();
}

/// �f�t�H���g�̑��x�����߂�
double MLActor::getDefaultSpeed()
{
	return DEFAULT_SPEED;
}

/// �����N�����߂�
// 0 ���� 1 �܂ł̎���
double MLActor::getRank()
{
	return mRank;
}

/// action �������Ȃ��e�����
void MLActor::createSimpleBullet( double direction, double speed )
{
	Locator::LinearF locator( mLocator.GetPosition() );
	locator.GetSpeed().SetUnitVector( 
		static_cast<float>( direction - 90 ) ) *= static_cast<float>( speed );

	if( mCreateParamList.empty() )
	{
		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new Linear( Actor::Base::GetMode(), 
			locator, static_cast<int>( Base::GetHitRadius() ), mDrawParam ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		Util::Sprite::DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new Linear( Actor::Base::GetMode(), 
			locator, hitRadius, dParam ) ) );
	}
}

/// action �����e�����
void MLActor::createBullet( BulletMLState *state, 
	double direction, double speed )
{
	float angle = static_cast<float>( direction - 90 );

	Locator::LinearF locator( mLocator.GetPosition() );
	locator.GetSpeed().SetUnitVector( angle ) *= static_cast<float>( speed );

	if( mCreateParamList.empty() )
	{
		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new MLActor( Actor::Base::GetMode(), 
			mpBMLParser, state, 
			locator, static_cast<int>( Base::GetHitRadius() ), mDrawParam, 
			mCreateParamList, angle ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		Util::Sprite::DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		Actor::Base::GetActors().GetBullets().push_back( 
			PBullet( new MLActor( Actor::Base::GetMode(), 
			mpBMLParser, state, 
			locator, hitRadius, dParam, 
			mCreateParamList, angle ) ) );
	}
}

/// �e�̊�ƂȂ�^�[���̒l��Ԃ��A�ʏ�̓t���[����
int MLActor::getTurn()
{
	return mFrameCount;
}

/// ����
void MLActor::doVanish()
{
	//Base::Destruct();

	Actor::Base::SetValid( false );
}

/// �e�̕������w�肵�������ɕύX����
void MLActor::doChangeDirection( double dir )
{
	mAngle = static_cast<float>( dir - 90 );
	float speed = mLocator.GetSpeed().GetAbs();

	mLocator.GetSpeed().SetUnitVector( mAngle ) *= speed;
}

/// �e�̑��x���w�肵���l�ɕύX����
void MLActor::doChangeSpeed( double speed )
{
	mLocator.GetSpeed().SetUnitVector( mAngle ) *= 
		static_cast<float>( speed );
}

/// accel �ɑ΂���C���^�[�t�F�C�X
void MLActor::doAccelX( double accelX )
{
	mLocator.GetAccel().x = static_cast<float>( accelX );
}

void MLActor::doAccelY( double accelY )
{
	mLocator.GetAccel().y = static_cast<float>( accelY );
}

/// �e�̑����� X ����������Ԃ��܂�
double MLActor::getBulletSpeedX()
{
	return mLocator.GetSpeed().x;
}

/// �e�̑����� Y ����������Ԃ��܂�
double MLActor::getBulletSpeedY()
{
	return mLocator.GetSpeed().y;
}

/// ������Ԃ�
double MLActor::getRand()
{
	return Actor::Base::GetMode()->GetRandom()->GetFloat( 0, 1 );
}