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
namespace Font
{
namespace Detail
{
	// �t�H���g�X�v���C�g�̃��[�_�[�N���X
	class TextureLoader
		: public Selene::Engine::Graphics::Resource::IFileLoadListener		// �t�@�C���ǂݍ��ݗp�̃��X�i�[
	{
	private:
		//
		// IFileLoadListener�p
		// ���\�[�X�ǂݍ��ݎ��̃R�[���o�b�N
		// ��������true��Ԃ����B
		//
		// pFileName	[in]	�t�@�C����
		// pFileBuffer	[out]	�t�@�C���̃o�b�t�@
		// FileSize		[out]	�t�@�C���T�C�Y
		// pUserData	[out]	���[�U�[���C�ӂɊi�[�ł���f�[�^
		// pUserSetData	[in]	CreateText()���̎w�肵�� pUserSetData ����
		//
		virtual bool OnLoad( const wchar_t* pFileName, const void*& pFileBuffer, 
			Selene::Sint32& fileSize, void*& pUserData, void* pUserSetData );

		//
		// IFileLoadListener�p
		// ���\�[�X�ǂݍ��ݏI�����̃R�[���o�b�N
		//
		// pFileBuffer	[in]	�t�@�C���̃o�b�t�@
		// FileSize		[in]	�t�@�C���T�C�Y
		// pUserData	[in]	OnLoad()���ɓn�������[�U�[���C�ӂɊi�[�ł���f�[�^
		// pUserSetData	[in]	CreateText()���̎w�肵�� pUserSetData ����
		//
		virtual void OnRelease( const void* pFileBuffer, Selene::Sint32 fileSize, 
			void* pUserData, void* pUserSetData );
	};
}
}
}
}