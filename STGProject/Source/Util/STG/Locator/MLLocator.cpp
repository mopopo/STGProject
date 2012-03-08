#include "PCH.h"
#include "MLLocator.h"

using namespace Game;
using namespace Util::STG;
using namespace Locator;

const double MLLocator::DEFAULT_RANK = 0.1;

namespace
{
	static const double DEFAULT_SPEED = 4.0;
}


// �R���X�g���N�^
MLLocator::MLLocator( PBMLParser bp, const Vector2DF &pos, 
	Util::Random::PRandom pRandom )
	: BulletMLRunner( bp.get() )
	, mLocator( pos )
	, mpBMLParser( bp )
	, mRank( DEFAULT_RANK )
	, mFrameCount( 0 )
	, mAngle( -90.0f )
	, mAimAngle( -90.0f )
	, mpRandom( pRandom )
	, mVanished( false )
{
}


// ��Ԃ̍X�V
void MLLocator::Update()
{
	BulletMLRunner::run();

	mLocator.Update();
	if( mLocator.GetSpeed().GetAbs() > 0 )
	{
		mAngle = mLocator.GetSpeed().GetAngle();
	}

	mFrameCount++;
}


// �ʒu�̎擾
Vector2DF MLLocator::GetPosition() const
{
	return mLocator.GetPosition();
}

Vector2DF &MLLocator::GetPosition()
{
	return mLocator.GetPosition();
}

// �ʒu�̐ݒ�
void MLLocator::SetPosition( const Vector2DF &pos )
{
	mLocator.SetPosition( pos );
}

// ���x�x�N�g���̎擾
Vector2DF MLLocator::GetSpeed() const
{
	return mLocator.GetSpeed();
}

Vector2DF &MLLocator::GetSpeed()
{
	return mLocator.GetSpeed();
}

// ���x�x�N�g���̐ݒ�
void MLLocator::SetSpeed( const Vector2DF &sp )
{
	mLocator.SetSpeed( sp );
}

// �����x�x�N�g���̎擾
Vector2DF MLLocator::GetAccel() const
{
	return mLocator.GetAccel();
}

Vector2DF &MLLocator::GetAccel()
{
	return mLocator.GetAccel();
}

// �����x�x�N�g���̐ݒ�
void MLLocator::SetAccel( const Vector2DF &ac )
{
	mLocator.SetAccel( ac );
}

// �O�͂̓K�p
Vector2DF MLLocator::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ���s���I�����Ă��邩�ǂ���
bool MLLocator::IsEnd() const
{
	return BulletMLRunner::isEnd() || mVanished;
}

// �_���p�x�̎擾
float MLLocator::GetAimAngle() const
{
	return mAimAngle;
}

// �_���p�x�̐ݒ�
void MLLocator::SetAimAngle( float angle )
{
	mAimAngle = angle;
}

// �����N�̎擾
double MLLocator::GetRank() const
{
	return mRank;
}

// �����N�̐ݒ�
void MLLocator::SetRank( double rank )
{
	assert( rank >= 0 && rank <= 1 );

	mRank = rank;
}


/// ���̒e�̊p�x�����߂�
// �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
double MLLocator::getBulletDirection()
{
	return mAngle + 90;
}

/// ���̒e���玩�@��_���p�x�����߂�
// �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
double MLLocator::getAimDirection()
{
	return mAimAngle + 90;
}

/// ���̒e�̑��x�����߂�
double MLLocator::getBulletSpeed()
{
	return mLocator.GetSpeed().GetAbs();
}

/// �f�t�H���g�̑��x�����߂�
double MLLocator::getDefaultSpeed()
{
	return DEFAULT_SPEED;
}

/// �����N�����߂�
// 0 ���� 1 �܂ł̎���
double MLLocator::getRank()
{
	return mRank;
}

/// �e�̊�ƂȂ�^�[���̒l��Ԃ��A�ʏ�̓t���[����
int MLLocator::getTurn()
{
	return mFrameCount;
}

/// ����
void MLLocator::doVanish()
{
	mVanished = true;
}

/// �e�̕������w�肵�������ɕύX����
void MLLocator::doChangeDirection( double dir )
{
	mAngle = static_cast<float>( dir - 90 );
	float speed = mLocator.GetSpeed().GetAbs();

	mLocator.GetSpeed().SetUnitVector( mAngle ) *= speed;
}

/// �e�̑��x���w�肵���l�ɕύX����
void MLLocator::doChangeSpeed( double speed )
{
	mLocator.GetSpeed().SetUnitVector( mAngle ) *= 
		static_cast<float>( speed );
}

/// accel �ɑ΂���C���^�[�t�F�C�X
void MLLocator::doAccelX( double accelX )
{
	mLocator.GetAccel().x = static_cast<float>( accelX );
}

void MLLocator::doAccelY( double accelY )
{
	mLocator.GetAccel().y = static_cast<float>( accelY );
}

/// �e�̑����� X ����������Ԃ��܂�
double MLLocator::getBulletSpeedX()
{
	return mLocator.GetSpeed().x;
}

/// �e�̑����� Y ����������Ԃ��܂�
double MLLocator::getBulletSpeedY()
{
	return mLocator.GetSpeed().y;
}

/// ������Ԃ�
double MLLocator::getRand()
{
	return mpRandom->GetFloat( 0, 1 );
}