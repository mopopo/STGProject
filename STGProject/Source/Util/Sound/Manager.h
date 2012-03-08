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
namespace Sound
{
	/*
		�T�E���h�֘A�̑���

		�����ł̑���́ALoadStatic/Stream()�ō쐬�����S�ẴC���X�^���X�ɓK�p�����

		�����T�E���h�t�@�C���ŃC���X�^���X�����ƁA
		�I������SELENE���ŗ�O"out_of_range"���o����ۂ�
	*/
	class Manager
	{
	public:
		// ���ʉ��p�̃T�E���h�t�@�C���̓ǂݍ���
		static PStatic LoadStatic( const std::wstring &fileName, 
			Selene::Uint32 layerCount = 1 );
		static PStatic LoadStatic( File::PFile pFile, 
			Selene::Uint32 layerCount = 1 );
		static void LoadStatic( const StaticSrcMap &srcMap, 
			StaticMap &statics );

		// BGM�p�̃T�E���h�t�@�C���̓ǂݍ���
		static PStream LoadStream( const std::wstring &fileName, 
			bool isMemoryCopy = true );
		static PStream LoadStream( File::PFile pFile, 
			bool isMemoryCopy = true );
		static void LoadStream( const StreamSrcMap &srcMap, 
			StreamMap &streams );

		// ���ʉ��̃{�����[���̕ύX
		static void SetStaticVolumes( float volume = 1.0f );
		// ���ʉ��̃{�����[���̎擾
		static float GetStaticVolumes();
		// BGM�̃{�����[���̕ύX
		static void SetStreamVolumes( float volume = 1.0f );
		// BGM�̃{�����[���̎擾
		static float GetStreamVolumes();

		// ���ʉ��̒�~
		static void StopStatics();
		// BGM�̒�~
		static void StopStreams();

		// ���ʉ��̈ꎞ��~/����
		static void PauseStatics();
		// BGM�̈ꎞ��~/����
		static void PauseStreams();

		// ���ʉ��̍Đ���ԃ`�F�b�N
		static bool IsPlayStatics();
		// BGM�̍Đ���ԃ`�F�b�N
		static bool IsPlayStreams();

		// BGM�̃t�F�[�h�C��
		static void FadeInStreams( float second );
		// BGM�̃t�F�[�h�A�E�g
		static void FadeOutStreams( float second );
	};
}
}
}