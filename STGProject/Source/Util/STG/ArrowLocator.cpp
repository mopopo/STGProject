#include "PCH.h"
#include "ArrowLocator.h"
#include "Util/Input/STG/IController.h"

using namespace Game;
using namespace Util;
using namespace STG;
using namespace Selene;
using namespace boost::numeric;

namespace
{
	// ���������臒l
	static const interval<float> DIR_VAL_MARGIN( -0.3f, 0.3f );
}


// �R���X�g���N�^
ArrowLocator::ArrowLocator( PController pController, int initArrowPos, 
	int top, int bottom, bool loop, bool horizontal )
: mArrowPos( initArrowPos )
, mArwMovRepCnt1( 20.0f )
, mArwMovRepCnt2( 6.0f )
, mRep2Flag( false )
, mPosItv( top, bottom )
, mMoveCallback()
, mPrevDir()
, mDir()
, mLoopFlag( loop )
, mHorizontalFlag( horizontal )
, mpController( pController )
{
	assert( mpController );

	if( !in( mArrowPos, mPosItv ) )
	{
		mArrowPos = mPosItv.lower();
	}
}


// 1�t���[�����̏�ԍX�V
void ArrowLocator::UpdateState()
{
	UpdateDirection();

	if( IsPushUp() )
	{
		MoveUp();
	}
	else if( IsPushDown() )
	{
		MoveDown();
	}
	else if( IsHoldUp() )
	{
		if( !mRep2Flag )
		{
			mArwMovRepCnt1.UpdateState();

			if( mArwMovRepCnt1.GetRepeatCount() > 0 )
			{
				mRep2Flag = true;
			}
		}
		else
		{
			mArwMovRepCnt2.UpdateState();

			for( unsigned i = 0; i < mArwMovRepCnt2.GetRepeatCount(); i++ )
			{
				MoveUp();
			}
		}
	}
	else if( IsHoldDown() )
	{
		if( !mRep2Flag )
		{
			mArwMovRepCnt1.UpdateState();

			if( mArwMovRepCnt1.GetRepeatCount() > 0 )
			{
				mRep2Flag = true;
			}
		}
		else
		{
			mArwMovRepCnt2.UpdateState();

			for( unsigned i = 0; i < mArwMovRepCnt2.GetRepeatCount(); i++ )
			{
				MoveDown();
			}
		}
	}
	else
	{
		mArwMovRepCnt1.Reset();
		mArwMovRepCnt2.Reset();
		mRep2Flag = false;
	}
}


// ���̈ړ�
void ArrowLocator::MoveUp()
{
	if( mArrowPos == mPosItv.lower() )
	{
		if( mLoopFlag )
		{
			mArrowPos = mPosItv.upper();
		}
	}
	else
	{
		mArrowPos--;
	}

	if( mMoveCallback )
	{
		mMoveCallback();
	}
}
void ArrowLocator::MoveDown()
{
	if( mArrowPos == mPosItv.upper() )
	{
		if( mLoopFlag )
		{
			mArrowPos = mPosItv.lower();
		}
	}
	else
	{
		mArrowPos++;
	}

	if( mMoveCallback )
	{
		mMoveCallback();
	}
}


// �ʒu�̎擾
int ArrowLocator::GetPosition() const
{
	return mArrowPos;
}

// �ʒu�̐ݒ�
void ArrowLocator::SetPosition( int pos )
{
	if( in( pos, mPosItv ) )
	{
		mArrowPos = pos;
	}
}


// ����Ɖ����̐ݒ�
void ArrowLocator::SetInterval( int top, int bottom )
{
	mPosItv.assign( top, bottom );

	if( !in( mArrowPos, mPosItv ) )
	{
		mArrowPos = mPosItv.lower();
	}
}

// ����Ɖ����̎擾
const interval<int> &ArrowLocator::GetInterval() const
{
	return mPosItv;
}


// ������A�����E�̓��͂Ƃ���
bool ArrowLocator::GetHorizontal() const
{
	return mHorizontalFlag;
}

void ArrowLocator::SetHorizontal( bool flag )
{
	mHorizontalFlag = flag;
}


// ���s�[�g�҂��Ԋu�̎擾
float ArrowLocator::GetRepeatWait() const
{
	return mArwMovRepCnt1.GetInterval();
}

// ���s�[�g�҂��Ԋu�̐ݒ�
void ArrowLocator::SetRepeatWait( float wait )
{
	mArwMovRepCnt1.SetInterval( wait );
}

// ���s�[�g�Ԋu�̎擾
float ArrowLocator::GetRepeatInterval() const
{
	return mArwMovRepCnt2.GetInterval();
}

// ���s�[�g�Ԋu�̐ݒ�
void ArrowLocator::SetRepeatInterval( float itv )
{
	mArwMovRepCnt2.SetInterval( itv );
}


// ���̓R���g���[���[�̎擾
ArrowLocator::PController ArrowLocator::GetController() const
{
	return mpController;
}

// ���̓R���g���[���[�̐ݒ�
void ArrowLocator::SetController( PController pController )
{
	mpController = pController;
}


// �ړ��R�[���o�b�N�̐ݒ�
void ArrowLocator::SetMoveCallback( const boost::python::object &callback )
{
	mMoveCallback = callback;
}


void ArrowLocator::UpdateDirection()
{
	mPrevDir = mDir;

	mDir = mpController->GetDirection();
}

bool ArrowLocator::IsPushUp() const
{
	if( !mHorizontalFlag )
	{
		if( in( mPrevDir.y, DIR_VAL_MARGIN ) && 
			!in( mDir.y, DIR_VAL_MARGIN ) && 
			mDir.y < 0 )
		{
			return true;
		}
	}
	else
	{
		if( in( mPrevDir.x, DIR_VAL_MARGIN ) && 
			!in( mDir.x, DIR_VAL_MARGIN ) && 
			mDir.x < 0 )
		{
			return true;
		}
	}

	return false;
}

bool ArrowLocator::IsPushDown() const
{
	if( !mHorizontalFlag )
	{
		if( in( mPrevDir.y, DIR_VAL_MARGIN ) && 
			!in( mDir.y, DIR_VAL_MARGIN ) && 
			mDir.y > 0 )
		{
			return true;
		}
	}
	else
	{
		if( in( mPrevDir.x, DIR_VAL_MARGIN ) && 
			!in( mDir.x, DIR_VAL_MARGIN ) && 
			mDir.x > 0 )
		{
			return true;
		}
	}

	return false;
}

bool ArrowLocator::IsHoldUp() const
{
	if( !mHorizontalFlag )
	{
		if( !in( mPrevDir.y, DIR_VAL_MARGIN ) && 
			mDir.y < 0 )
		{
			return true;
		}
	}
	else
	{
		if( !in( mPrevDir.x, DIR_VAL_MARGIN ) && 
			mDir.x < 0 )
		{
			return true;
		}
	}

	return false;
}

bool ArrowLocator::IsHoldDown() const
{
	if( !mHorizontalFlag )
	{
		if( !in( mPrevDir.y, DIR_VAL_MARGIN ) && 
			mDir.y > 0 )
		{
			return true;
		}
	}
	else
	{
		if( !in( mPrevDir.x, DIR_VAL_MARGIN ) && 
			mDir.x > 0 )
		{
			return true;
		}
	}

	return false;
}