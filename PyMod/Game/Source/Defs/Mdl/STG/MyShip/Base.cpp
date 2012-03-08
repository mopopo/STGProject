#include "PCH.h"
#include "Base.h"

#include "Defs/Ctrl/STG/STG.h"

using namespace Defs::Mdl::STG::MyShip;
using namespace Game::Util::STG;
using namespace Game::Util::Consts;

namespace
{
	// �����c�@��
	static const unsigned INIT_REMAINDER_NUM = 3;
	// �����ʒu
	static const Vector2DF INIT_POS( 
		( SCREEN_SIZE.x - STG_INFAREA_SIZE.x ) / 2.0f, 
		SCREEN_SIZE.y * 0.8f );

	// ���@�j�󎞂̎��@�����t���[����
	static const unsigned DISAPPEAR_FRAME_NUM = 60;
	// ���@���A���̖��G�t���[����
	static const unsigned BARRIER_FRAME_NUM = 90;

	// �G�e�����蔻�蔼�a
	static const int HIT_RADIUS = 1;
	// �A�C�e���z���񂹓����蔻�蔼�a
	static const int HIT_RADIUS_ITEM_RETRIEVE = 64;
	// �A�C�e�������蔻�蔼�a
	static const int HIT_RADIUS_ITEM = 16;

	typedef Defs::Ctrl::STG::STG STGControl;
}


Base::Base()
: mLocator()
, mHitCircle( INIT_POS, HIT_RADIUS )
, mItemRetrieveHitCircle( INIT_POS, HIT_RADIUS_ITEM_RETRIEVE )
, mItemHitCircle( INIT_POS, HIT_RADIUS_ITEM )
, mInitRemainder( INIT_REMAINDER_NUM )
, mRemainder( INIT_REMAINDER_NUM )
, mBarrierCount( 0 )
, mDisappearCount( 0 )
, mMoveForbidFlag( false )
, mShotForbidFlag( false )
, mSpecialAttackForbidFlag( false )
{
	mLocator.GetPosition() = INIT_POS;
}


// �t���[�����̍X�V
void Base::Update()
{
	if( !IsDisappeared() )
	{
		auto pBullets = STGControl::getActors()->DetectBulletHitAll( mHitCircle );
		if( !pBullets->empty() )
		{
			foreach( Game::Mdl::STG::Bullet::PBullet pBullet, *pBullets )
			{
				pBullet->Destruct();
			}

			Destruct();
		}
	}

	if( IsDisappeared() )
	{
		mDisappearCount--;

		if( !IsDisappeared() )
		{
			if( GetRemainder() > 0 )
			{
				mLocator.GetPosition() = INIT_POS;

				OnRevival();
			}
			else
			{
				mDisappearCount++;
			}
		}
	}
	else if( IsBarriered() )
	{
		mBarrierCount--;
	}

	Input();

	mHitCircle.SetCenter( mLocator.GetPosition() );
	mItemRetrieveHitCircle.SetCenter( mLocator.GetPosition() );
	mItemHitCircle.SetCenter( mLocator.GetPosition() );
	if( IsBarriered() )
	{
		mHitCircle.SetRadius( GetBarrierRadius() );
	}
	else
	{
		mHitCircle.SetRadius( HIT_RADIUS );
	}
	mItemRetrieveHitCircle.SetRadius( GetItemRetrieveRadius() );

	OnUpdate();
}

void Base::Input()
{
	if( !IsDisappeared() )
	{
		auto controller = STGControl::getController();

		if( !mMoveForbidFlag )
		{
			mLocator.GetSpeed() = 
				controller.GetDirection() * GetMoveSpeed();

			mLocator.Update();

			Vector2DF 
				&pos = mLocator.GetPosition(), 
				size = GetShipSize();
			int rightBorder = 
				SCREEN_SIZE.x - STG_INFAREA_SIZE.x;
			int bottomBorder = SCREEN_SIZE.y;
			if( pos.x - size.x/2 < 0 )
			{
				pos.x = size.x/2;
			}
			else if( pos.x + size.x/2 > rightBorder )
			{
				pos.x = rightBorder - size.x/2;
			}
			if( pos.y - size.y/2 < 0 )
			{
				pos.y = size.y/2;
			}
			else if( pos.y + size.y/2 > bottomBorder )
			{
				pos.y = bottomBorder - size.y/2;
			}
		}

		if( !mShotForbidFlag && 
			controller.IsHold( Game::Util::Input::STG::KEY_Z ) )
		{
			Shot();
		}

		if( !mSpecialAttackForbidFlag && 
			controller.IsPush( Game::Util::Input::STG::KEY_X ) )
		{
			SpecialAttack();
		}
	}
}

// �t���[�����̕`��
void Base::Draw() const
{
	if( !IsDisappeared() )
	{
		OnDraw();
	}
}


// �G�e�����蔻��
bool Base::IsHit( const Hit::CircleI &bulletHit ) const
{
	if( !IsDisappeared() )
	{
		return mHitCircle.IsHit( bulletHit );
	}

	return false;
}

// �A�C�e���z���񂹓����蔻��
bool Base::IsHit_ItemRetrieve( const Hit::CircleI &itemHit ) const
{
	if( !IsDisappeared() )
	{
		return mItemRetrieveHitCircle.IsHit( itemHit );
	}

	return false;
}

// �A�C�e���擾�����蔻��
bool Base::IsHit_GetItem( const Hit::CircleI &itemHit ) const
{
	if( !IsDisappeared() )
	{
		return mItemHitCircle.IsHit( itemHit );
	}

	return false;
}

// ���@�̔j��
void Base::Destruct()
{
	if( !IsDisappeared() && !IsBarriered() )
	{
		mRemainder--;

		mDisappearCount = DISAPPEAR_FRAME_NUM;
		mBarrierCount = BARRIER_FRAME_NUM;

		OnDestruction();
	}
}


// ���G��Ԕ���
bool Base::IsBarriered() const
{
	return mBarrierCount > 0;
}

// ���G��ԃt���[���J�E���g�̎擾
unsigned Base::GetBarrierCount() const
{
	return mBarrierCount;
}

// �j���̏�����Ԕ���
bool Base::IsDisappeared() const
{
	return mDisappearCount > 0;
}


// ���݈ʒu�̎擾
Vector2DF Base::GetPosition() const
{
	return mLocator.GetPosition();
}

// ���݈ʒu�̐ݒ�
void Base::SetPosition( const Vector2DF &position )
{
	mLocator.SetPosition( position );
}

// �O�͂̓K�p
Vector2DF Base::ApplyExternalForce( const Vector2DF &vec )
{
	if( !IsDisappeared() )
	{
		return mLocator.ApplyExternalForce( vec );
	}

	return Vector2DF();
}


// �c�@�̎擾
unsigned Base::GetRemainder() const
{
	return mRemainder;
}

// �c�@�̒ǉ�
void Base::AddRemainder( unsigned num )
{
	mRemainder += num;
}


// �R���e�B�j���[���̏���
void Base::Continue()
{
	mRemainder = mInitRemainder;

	OnContinue();
}


// �ړ��֎~�ݒ�
void Base::SetMoveForbidFlag( bool flag )
{
	mMoveForbidFlag = flag;
}

// �V���b�g�֎~�ݒ�
void Base::SetShotForbidFlag( bool flag )
{
	mShotForbidFlag = flag;
}

// ����U���֎~�ݒ�
void Base::SetSpecialAttackForbidFlag( bool flag )
{
	mSpecialAttackForbidFlag = flag;
}


// �����c�@���̐ݒ�
void Base::SetInitRemainder( unsigned num )
{
	assert( num > 0 );

	mInitRemainder = num;
	mRemainder = num;
}

// ���G��Ԃ̐ݒ�
void Base::SetBarrier( unsigned frameNum )
{
	mBarrierCount = frameNum;
}