#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ISound.h"
#include "Util/Sound/Manager.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Python
{
namespace Wrapper
{
	class SoundImpl
		: public ISound
	{
	public:
		// ���ʉ��p�̃T�E���h�t�@�C���̓ǂݍ���
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName )
		{
			return Sound::Manager::LoadStatic( fileName );
		}
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName, Selene::Sint32 layerCount )
		{
			return Sound::Manager::LoadStatic( fileName, layerCount );
		}
		virtual Sound::PStatic LoadStatic( File::PFile pFile )
		{
			return Sound::Manager::LoadStatic( pFile );
		}
		virtual Sound::PStatic LoadStatic( File::PFile pFile, Selene::Sint32 layerCount )
		{
			return Sound::Manager::LoadStatic( pFile, layerCount );
		}
		// BGM�p�̃T�E���h�t�@�C���̓ǂݍ���
		virtual Sound::PStream LoadStream( const std::wstring &fileName )
		{
			return Sound::Manager::LoadStream( fileName );
		}
		virtual Sound::PStream LoadStream( File::PFile pFile )
		{
			return Sound::Manager::LoadStream( pFile );
		}

		// ���ʉ��̃{�����[���̕ύX
		virtual void SetStaticVolumes( float volume )
		{
			Sound::Manager::SetStaticVolumes( volume );
		}
		// ���ʉ��̃{�����[���̎擾
		virtual float GetStaticVolumes()
		{
			return Sound::Manager::GetStaticVolumes();
		}
		// BGM�̃{�����[���̕ύX
		virtual void SetStreamVolumes( float volume )
		{
			Sound::Manager::SetStreamVolumes( volume );
		}
		// BGM�̃{�����[���̎擾
		virtual float GetStreamVolumes()
		{
			return Sound::Manager::GetStreamVolumes();
		}

		// ���ʉ��̒�~
		virtual void StopStatics()
		{
			Sound::Manager::StopStatics();
		}
		// BGM�̒�~
		virtual void StopStreams()
		{
			Sound::Manager::StopStreams();
		}

		// ���ʉ��̈ꎞ��~/����
		virtual void PauseStatics()
		{
			Sound::Manager::PauseStatics();
		}
		// BGM�̈ꎞ��~/����
		virtual void PauseStreams()
		{
			Sound::Manager::PauseStreams();
		}

		// ���ʉ��̍Đ���ԃ`�F�b�N
		virtual bool IsPlayStatics()
		{
			return Sound::Manager::IsPlayStatics();
		}
		// BGM�̍Đ���ԃ`�F�b�N
		virtual bool IsPlayStreams()
		{
			return Sound::Manager::IsPlayStreams();
		}

		// BGM�̃t�F�[�h�C��
		virtual void FadeInStreams( float second )
		{
			Sound::Manager::FadeInStreams( second );
		}
		// BGM�̃t�F�[�h�A�E�g
		virtual void FadeOutStreams( float second )
		{
			Sound::Manager::FadeOutStreams( second );
		}
	};
}
}
}
}