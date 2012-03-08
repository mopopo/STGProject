#include "PCH.h"
#include "MLActor.h"

#include "Defs/Ctrl/STG/STG.h"
#include "Defs/Mdl/STG/Bullet/Simple.h"
#include "Defs/Util/Sprite/Sprite.h"
#include "Mdl/STG/MyShip/IMyShip.h"

using namespace Defs::Mdl::STG;
using namespace Bullet::BulletML;
using namespace Game::Util::STG;

const double MLActor::DEFAULT_RANK = 0.1;

namespace
{
	static const double DEFAULT_SPEED = 4.0;

	typedef Defs::Ctrl::STG::STG STGControl;
}


MLActor::MLActor( PBMLParser bp, 
	const Vector2DF &pos )
	: Base( pos, 0 )
	, BulletMLRunner( bp.get() )
	, mLocator( pos )
	, mDrawParam()
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
	Actor::Base::SetFrameCounting( false );
}

MLActor::MLActor( PBMLParser bp, 
	const Locator::LinearF &locator, int hitRadius, 
	const DrawParameter &drawParam )
	: Base( locator.GetPosition(), hitRadius )
	, BulletMLRunner( bp.get() )
	, mLocator( locator )
	, mDrawParam( drawParam )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mCreateParamList()
	, mAngle( -90.0f )
	, mpBMLParser( bp )
{
}

MLActor::MLActor( PBMLParser bp, BulletMLState *bs, 
	const Locator::LinearF &locator, int hitRadius, 
	const DrawParameter &drawParam, 
	const CreateParamList &createParamList, 
	float angle )
	: Base( locator.GetPosition(), hitRadius )
	, BulletMLRunner( bs )
	, mLocator( locator )
	, mDrawParam( drawParam )
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

const MLActor::DrawParameter &MLActor::GetDrawParameter() const
{
	return mDrawParam;
}

void MLActor::SetDrawParameter( const DrawParameter &drawParam )
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
	Defs::Util::Sprite::Sprite::draw( mDrawParam );
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
	auto pMyShip = STGControl::getActors()->GetMyShip();

	return mLocator.GetPosition().GetAngle( pMyShip->GetPosition() ) + 90;
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
		STGControl::getActors()->GetBulletList().push_back( 
			Game::Mdl::STG::Bullet::PBullet( 
			new Linear( locator, 
			static_cast<int>( Base::GetHitRadius() ), mDrawParam ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );

		PLinear pBullet( 
			new Linear( locator, hitRadius, dParam ) );
		pBullet->SetHP( mCreateParamList.front().GetHP() );

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		STGControl::getActors()->GetBulletList().push_back( pBullet );
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
		STGControl::getActors()->GetBulletList().push_back( 
			Game::Mdl::STG::Bullet::PBullet( 
			new MLActor( mpBMLParser, state, 
			locator, static_cast<int>( Base::GetHitRadius() ), mDrawParam, 
			mCreateParamList, angle ) ) );
	}
	else
	{
		int hitRadius = mCreateParamList.front().GetHitRadius();
		DrawParameter dParam = 
			mCreateParamList.front().GetDrawParameter();
		dParam.SetDst( mLocator.GetPosition().MakeRect( 
			dParam.GetDst().w, dParam.GetDst().h ) );
		float hp = mCreateParamList.front().GetHP();

		if( mCreateParamList.front().IsPopped() )
		{
			mCreateParamList.pop_front();
		}

		PMLActor pBullet( 
			new MLActor( mpBMLParser, state, 
			locator, hitRadius, dParam, 
			mCreateParamList, angle ) );
		pBullet->SetHP( hp );

		STGControl::getActors()->GetBulletList().push_back( pBullet );
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
	return STGControl::getRandom()->GetFloat( 0, 1 );
}