#include "PCH.h"
#include "Static.h"

using namespace Game;
using namespace Util::Sound::Detail;
using namespace Selene;
using namespace std;
using namespace boost;


// �R���X�g���N�^
Static::Static( PStaticSound pStaticSound, const wstring &name, Uint32 layerCount )
: mpStaticSound( pStaticSound )
, mIndividualVolumes( layerCount, Consts::Sound::VOLUME_ITV.upper() )
, mLayerItv( Uint32( 0 ), layerCount )
, mName( name )
, mWaitingForPlay( false )
{
	if( !mpStaticSound )
	{
		THROW( 
			Exception::Invalid( mName ) );
	}
}


// �Đ�
void Static::Play( bool isLoop )
{
	for( Uint32 i = 0; i < mLayerItv.upper(); i++ )
	{
		if( !IsPlay( i ) )
		{
			mpStaticSound->Play( i, isLoop );
			return;
		}
	}

	if( !mWaitingForPlay )
	{
		mpStaticSound->Play( 0 );
	}
}

void Static::Play( Uint32 layer, bool isLoop )
{
	if( numeric::in( layer, mLayerItv ) )
	{
		if( !mWaitingForPlay )
		{
			mpStaticSound->Play( layer, isLoop );
		}
	}
	else
	{
		THROW( 
			Exception::InvalidLayer( mName, layer ) );
	}
}


// ��~
void Static::Stop()
{
	mpStaticSound->Stop( -1 );
}

void Static::Stop( Uint32 layer )
{
	if( numeric::in( layer, mLayerItv ) )
	{
		mpStaticSound->Stop( layer );
	}
	else
	{
		THROW( 
			Exception::InvalidLayer( mName, layer ) );
	}
}


// �ꎞ��~/����
void Static::Pause()
{
	mpStaticSound->Pause( -1 );
}

void Static::Pause( Uint32 layer )
{
	if( numeric::in( layer, mLayerItv ) )
	{
		mpStaticSound->Pause( layer );
	}
	else
	{
		THROW( 
			Exception::InvalidLayer( mName, layer ) );
	}
}


// �ꎞ��~�`�F�b�N
bool Static::IsPause()
{
	for( Uint32 i = 0; i < mLayerItv.upper(); i++ )
	{
		if( mpStaticSound->IsPause( i ) )
		{
			return true;
		}
	}

	return false;
}

bool Static::IsPause( Uint32 layer )
{
	if( numeric::in( layer, mLayerItv ) )
	{
		return mpStaticSound->IsPause( layer );
	}
	else
	{
		THROW( 
			Exception::InvalidLayer( mName, layer ) );
	}

	return false;
}


// �Đ���Ԃ��`�F�b�N
bool Static::IsPlay()
{
	for( Uint32 i = 0; i < mLayerItv.upper(); i++ )
	{
		if( mpStaticSound->IsPlay( i ) )
		{
			return true;
		}
	}

	return false;
}

bool Static::IsPlay( Uint32 layer )
{
	if( numeric::in( layer, mLayerItv ) )
	{
		return mpStaticSound->IsPlay( layer );
	}
	else
	{
		THROW( 
			Exception::InvalidLayer( mName, layer ) );
	}

	return false;
}


// �{�����[���ύX
void Static::SetVolume( float volume )
{
	if( numeric::in( volume, Consts::Sound::VOLUME_ITV ) )
	{
		mIndividualVolumes.assign( mIndividualVolumes.size(), volume );
	}
	else if( volume > Consts::Sound::VOLUME_ITV.upper() )
	{
		mIndividualVolumes.assign( mIndividualVolumes.size(), Consts::Sound::VOLUME_ITV.upper() );
	}
	else if( volume < Consts::Sound::VOLUME_ITV.lower() )
	{
		mIndividualVolumes.assign( mIndividualVolumes.size(), Consts::Sound::VOLUME_ITV.lower() );
	}

	UpdateVolume();
}

void Static::SetVolume( Uint32 layer, float volume )
{
	if( boost::numeric::in( layer, mLayerItv ) )
	{
		if( boost::numeric::in( volume, Consts::Sound::VOLUME_ITV ) )
		{
			mIndividualVolumes.at( layer ) = volume;
		}
		else if( volume > Consts::Sound::VOLUME_ITV.upper() )
		{
			mIndividualVolumes.at( layer ) = Consts::Sound::VOLUME_ITV.upper();
		}
		else if( volume < Consts::Sound::VOLUME_ITV.lower() )
		{
			mIndividualVolumes.at( layer ) = Consts::Sound::VOLUME_ITV.lower();
		}

		UpdateVolume();
	}
	else
	{
		THROW( 
			Exception::InvalidLayer( mName, layer ) );
	}
}


// ���C���[�����ׂōĐ���Ԃ̎��ɑ҂��ǂ���
bool Static::IsWaitingForPlay() const
{
	return mWaitingForPlay;
}

void Static::SetWaitingForPlay( bool waiting )
{
	mWaitingForPlay = waiting;
}


// SoundUtil�̃{�����[���ύX�̔��f
void Static::UpdateVolume()
{
	for( Uint32 i = 0; i < mLayerItv.upper(); i++ )
	{
		mpStaticSound->SetVolume( i, 
			mIndividualVolumes.at( i ) * Manager::GetStaticVolumes() * 100.0f );
	}
}