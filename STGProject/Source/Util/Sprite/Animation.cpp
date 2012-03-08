#include "PCH.h"
#include "Animation.h"

using namespace Game;
using namespace Util::Sprite;
using namespace Selene;


// �R���X�g���N�^
Animation::Animation()
{
}

Animation::Animation( const Point2DI &frameSize, unsigned frameNum, float frameInterval, 
					 const DrawParameter &param )
					 : mFrameSize( frameSize )
					 , mFrameNum( frameNum )
					 , mDrawParam( param )
					 , mCounter( frameInterval )
					 , mFrameCount( 0 )
					 , mPlayFlag( false )
{
	assert( mFrameSize.x > 0 );
	assert( mFrameSize.y > 0 );
	assert( mFrameNum > 0 );
	assert( mDrawParam.GetTexture() );
	assert( mDrawParam.GetTexture()->GetTextureSize().x % mFrameSize.x == 0 );
	assert( mDrawParam.GetTexture()->GetTextureSize().y % mFrameSize.y == 0 );
	assert( ( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) * 
		( mDrawParam.GetTexture()->GetTextureSize().y / mFrameSize.y ) 
		>= static_cast<int>( mFrameNum ) );
}


// �t���[���̍X�V
void Animation::Update()
{
	if( mPlayFlag && mFrameCount < mFrameNum )
	{
		mFrameCount += mCounter.GetRepeatCount();
		mCounter.UpdateState();

		mDrawParam.SetSrc( GetCurrentTextureSrc() );

		if( mFrameCount == mFrameNum )
		{
			mPlayFlag = false;
		}
	}
}

// �t���[���̕`��
void Animation::Draw() const
{
	if( mFrameCount < mFrameNum )
	{
		Manager::Draw( mDrawParam );
	}
}


// �t���[���T�C�Y�̎擾
Point2DI Animation::GetFrameSize() const
{
	return mFrameSize;
}

// �t���[���T�C�Y�̐ݒ�
void Animation::SetFrameSize( const Point2DI &size )
{
	mFrameSize = size;
}

// ���t���[�����̎擾
unsigned Animation::GetFrameNum() const
{
	return mFrameNum;
}

// ���t���[�����̐ݒ�
void Animation::SetFrameNum( unsigned num )
{
	mFrameNum = num;
}

// ���݂̃t���[���ʒu�̎擾
unsigned Animation::GetFramePos() const
{
	return mFrameCount;
}

// �t���[���ʒu�̐ݒ�
void Animation::SetFramePos( unsigned framePos )
{
	assert( framePos < mFrameNum );

	if( framePos < mFrameNum )
	{
		mFrameCount = framePos;
	}
	else
	{
		mFrameCount = mFrameNum - 1;
	}

	mDrawParam.SetSrc( GetCurrentTextureSrc() );
}


// �A�j���[�V�����J�n
void Animation::Play( unsigned framePos )
{
	SetFramePos( framePos );

	mPlayFlag = true;
}

// �A�j���[�V������~
void Animation::Stop()
{
	mPlayFlag = false;
}

// �A�j���[�V�����J�n�t���O�̎擾
bool Animation::IsPlay() const
{
	return mPlayFlag;
}


// �t���[���Ԋu�̎擾
float Animation::GetFrameInterval() const
{
	return mCounter.GetInterval();
}

// �t���[���Ԋu�̐ݒ�
void Animation::SetFrameInterval( float interval )
{
	mCounter.SetInterval( interval );
}


// �`��p�����[�^�̎擾
const DrawParameter &Animation::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void Animation::SetDrawParameter( const DrawParameter &param )
{
	PTexture pTexture = mDrawParam.GetTexture();

	mDrawParam = param;

	assert( mDrawParam.GetTexture() );
	assert( mDrawParam.GetTexture() == pTexture );
}

// �`���̐ݒ�
void Animation::SetDst( const RectF &dst )
{
	mDrawParam.SetDst( dst );
}

// �`��D��x�̐ݒ�
void Animation::SetPriority( Sint32 priority )
{
	mDrawParam.SetPriority( priority );
}

// �A���t�@�u�����h�̎�ނ̐ݒ�
void Animation::SetAlphaBlend( Util::Sprite::AlphaBlend alphaBlend )
{
	mDrawParam.SetAlphaBlend( alphaBlend );
}

// ��]�p�x�̐ݒ�
void Animation::SetRotDegree( float degree )
{
	mDrawParam.SetRotDegree( degree );
}

// ��]���̒��S����̃I�t�Z�b�g�̐ݒ�
void Animation::SetRotOffset( const Point2DF &rotOffset )
{
	mDrawParam.SetRotOffset( rotOffset );
}

// �`��F�̐ݒ�
void Animation::SetColor( const ColorF &color )
{
	mDrawParam.SetColor( color );
}


// �`�悷��e�N�X�`���ʒu�̎擾
RectF Animation::GetCurrentTextureSrc() const
{
	RectF src;
	src.x = static_cast<float>( mFrameSize.x ) * 
		( mFrameCount % 
		( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) );
	src.y = static_cast<float>( mFrameSize.y ) * 
		( mFrameCount / 
		( mDrawParam.GetTexture()->GetTextureSize().x / mFrameSize.x ) );
	src.w = static_cast<float>( mFrameSize.x );
	src.h = static_cast<float>( mFrameSize.y );

	return src;
}