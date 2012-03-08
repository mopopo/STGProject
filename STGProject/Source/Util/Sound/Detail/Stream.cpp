#include "PCH.h"
#include "Stream.h"

using namespace Game;
using namespace Util::Sound::Detail;
using namespace Selene;
using namespace std;
using namespace boost;


// �R���X�g���N�^
Stream::Stream( PStreamSound pStreamSound, const wstring &name )
: mpStreamSound( pStreamSound )
, mVolume( Consts::Sound::VOLUME_ITV.upper() )
, mFading( false )
{
	if( !mpStreamSound )
	{
		THROW( 
			Exception::Invalid( name ) );
	}
}


// �Đ�
void Stream::Play()
{
	mpStreamSound->Play( -1 );

	mFading = false;
}

void Stream::Play( Uint32 loopCount )
{
	mpStreamSound->Play( loopCount );

	mFading = false;
}

void Stream::Play( const Util::Sound::PlayBlock playBlocks[], Uint32 blockCount )
{
	mpStreamSound->Play( playBlocks, blockCount );

	mFading = false;
}


// ��~
void Stream::Stop()
{
	mpStreamSound->Stop();

	mFading = false;
}


// �ꎞ��~/����
void Stream::Pause()
{
	mpStreamSound->Pause();
}


// �Đ���Ԃ��`�F�b�N
bool Stream::IsPlay()
{
	return mpStreamSound->IsPlay();
}


// �{�����[���ύX
void Stream::SetVolume( float volume )
{
	if( numeric::in( volume, Consts::Sound::VOLUME_ITV ) )
	{
		mVolume = volume;
	}
	else if( volume > Consts::Sound::VOLUME_ITV.upper() )
	{
		mVolume = Consts::Sound::VOLUME_ITV.upper();
	}
	else if( volume < Consts::Sound::VOLUME_ITV.lower() )
	{
		mVolume = Consts::Sound::VOLUME_ITV.lower();
	}

	UpdateVolume();
}


// �t�F�[�h�C������
void Stream::FadeIn( float second )
{
	mpStreamSound->FadeIn( second, mVolume * Manager::GetStreamVolumes() * 100.0f );

	//mFading = true;
}

// �t�F�[�h�A�E�g����
void Stream::FadeOut( float second )
{
	mpStreamSound->FadeOut( second );

	mFading = true;
}


// SoundUtil�̃{�����[���ύX�̔��f
void Stream::UpdateVolume()
{
	if( !mFading )
	{
		mpStreamSound->SetVolume( mVolume * Manager::GetStreamVolumes() * 100.0f );
	}
}