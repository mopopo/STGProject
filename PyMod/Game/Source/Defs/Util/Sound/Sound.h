#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Static.h"
#include "Stream.h"
#include "Defs/Util/File/FileObject.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sound
{
	class Sound
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );

		// ���ʉ��p�̃T�E���h�t�@�C���̓ǂݍ���
		static Static loadStatic( const std::wstring &path );
		static Static loadStatic( const std::wstring &path, Selene::Sint32 layerCount );
		static Static loadStatic( const File::FileObject &fileObject );
		static Static loadStatic( const File::FileObject &fileObject, Selene::Sint32 layerCount );
		// BGM�p�̃T�E���h�t�@�C���̓ǂݍ���
		static Stream loadStream( const std::wstring &path );
		static Stream loadStream( const File::FileObject &fileObject );

		// ���ʉ��̃{�����[���̕ύX
		static void setStaticVolumes( float volume );
		// ���ʉ��̃{�����[���̎擾
		static float getStaticVolumes();
		// BGM�̃{�����[���̕ύX
		static void setStreamVolumes( float volume );
		// BGM�̃{�����[���̎擾
		static float getStreamVolumes();

		// ���ʉ��̒�~
		static void stopStatics();
		// BGM�̒�~
		static void stopStreams();

		// ���ʉ��̈ꎞ��~/����
		static void pauseStatics();
		// BGM�̈ꎞ��~/����
		static void pauseStreams();

		// ���ʉ��̍Đ���ԃ`�F�b�N
		static bool isPlayStatics();
		// BGM�̍Đ���ԃ`�F�b�N
		static bool isPlayStreams();

		// BGM�̃t�F�[�h�C��
		static void fadeInStreams( float second );
		// BGM�̃t�F�[�h�A�E�g
		static void fadeOutStreams( float second );
	};
}
}
}