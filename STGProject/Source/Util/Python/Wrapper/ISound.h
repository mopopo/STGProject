#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


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
	class ISound
	{
	public:
		// ���ʉ��p�̃T�E���h�t�@�C���̓ǂݍ���
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName ) = 0;
		virtual Sound::PStatic LoadStatic( const std::wstring &fileName, Selene::Sint32 layerCount ) = 0;
		virtual Sound::PStatic LoadStatic( File::PFile pFile ) = 0;
		virtual Sound::PStatic LoadStatic( File::PFile pFile, Selene::Sint32 layerCount ) = 0;
		// BGM�p�̃T�E���h�t�@�C���̓ǂݍ���
		virtual Sound::PStream LoadStream( const std::wstring &fileName ) = 0;
		virtual Sound::PStream LoadStream( File::PFile pFile ) = 0;

		// ���ʉ��̃{�����[���̕ύX
		virtual void SetStaticVolumes( float volume ) = 0;
		// ���ʉ��̃{�����[���̎擾
		virtual float GetStaticVolumes() = 0;
		// BGM�̃{�����[���̕ύX
		virtual void SetStreamVolumes( float volume ) = 0;
		// BGM�̃{�����[���̎擾
		virtual float GetStreamVolumes() = 0;

		// ���ʉ��̒�~
		virtual void StopStatics() = 0;
		// BGM�̒�~
		virtual void StopStreams() = 0;

		// ���ʉ��̈ꎞ��~/����
		virtual void PauseStatics() = 0;
		// BGM�̈ꎞ��~/����
		virtual void PauseStreams() = 0;

		// ���ʉ��̍Đ���ԃ`�F�b�N
		virtual bool IsPlayStatics() = 0;
		// BGM�̍Đ���ԃ`�F�b�N
		virtual bool IsPlayStreams() = 0;

		// BGM�̃t�F�[�h�C��
		virtual void FadeInStreams( float second ) = 0;
		// BGM�̃t�F�[�h�A�E�g
		virtual void FadeOutStreams( float second ) = 0;

		virtual ~ISound() {}
	};
}
}
}
}