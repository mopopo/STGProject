#include "PCH.h"
#include "Base.h"

#include "Defs/Ctrl/STG/STG.h"

using namespace Defs::Mdl::STG::Actor;
using namespace Game::Util::STG;
using namespace Game::Util::Consts;
using namespace Selene;


namespace
{
	// �L���̈�̗]��
	static const int VALIDAREA_MARGIN = 100;
	// �L���t���[����
	static const int VALID_FRAME_NUM = 60 * 10;

	typedef Defs::Ctrl::STG::STG STGControl;
}


// �R���X�g���N�^
Base::Base( const Hit::RectI &validRect )
: mId( STGControl::genObjectId() )
, mValidFlag( true )
, mValidArea( -VALIDAREA_MARGIN, -VALIDAREA_MARGIN, 
			 SCREEN_SIZE.x - STG_INFAREA_SIZE.x + VALIDAREA_MARGIN*2, 
			 SCREEN_SIZE.y + VALIDAREA_MARGIN*2, 
			 false )
, mValidRect( validRect )
, mValidFrameNum( VALID_FRAME_NUM )
, mFrameCount( 0 )
, mFrameCounting( true )
{
}


// ��ӂȐ����l���擾
Uint64 Base::GetId() const
{
	return mId;
}


// �X�V
void Base::Update()
{
	mValidRect.SetPosition( GetPosition() );

	if( !mValidRect.IsHit( mValidArea ) )
	{
		mValidFlag = false;
	}

	if( mFrameCount > mValidFrameNum )
	{
		Erase();
	}

	UpdateMiddle();

	OnUpdate();

	if( mFrameCount <= mValidFrameNum && 
		mFrameCounting )
	{
		mFrameCount++;
	}
}

// �`��
void Base::Draw() const
{
	DrawMiddle();

	OnDraw();
}


// �L���t���O�̎擾
bool Base::IsValid() const
{
	return mValidFlag;
}


// ����
void Base::Erase()
{
	mValidFlag = false;

	OnErase();
}


// �L���t���O�̐ݒ�
void Base::SetValid( bool flag )
{
	mValidFlag = flag;
}

// �L���̈攻��̎擾
Hit::RectI Base::GetValidRect() const
{
	return mValidRect;
}

// �L���̈攻��̐ݒ�
void Base::SetValidRect( const Hit::RectI &rect )
{
	mValidRect = rect;
}

// �L���̈�̗]���̐ݒ�
void Base::SetValidAreaMargin( int margin )
{
	mValidArea = Hit::RectI( 
		-margin, -margin, 
		SCREEN_SIZE.x - STG_INFAREA_SIZE.x + margin*2, 
		SCREEN_SIZE.y + margin*2, 
		false );
}

// ���݂̃t���[���J�E���g���擾
unsigned Base::GetFrameCount() const
{
	return mFrameCount;
}

// ���݂̃t���[���J�E���g��ݒ�
void Base::SetFrameCount( unsigned count )
{
	mFrameCount = count;
}

// �L������t���[���J�E���g�̎擾
unsigned Base::GetValidFrameNum() const
{
	return mValidFrameNum;
}

// �L������t���[���J�E���g�̐ݒ�
void Base::SetValidFrameNum( unsigned frameNum )
{
	mValidFrameNum = frameNum;
}


// �t���[���J�E���g���邩�ǂ����擾
bool Base::IsFrameCounting() const
{
	return mFrameCounting;
}

// �t���[���J�E���g���邩�ǂ����ݒ�
void Base::SetFrameCounting( bool counting )
{
	mFrameCounting = counting;
}