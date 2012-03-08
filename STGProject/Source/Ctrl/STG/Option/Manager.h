#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Parameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Option
{
	class Manager
	{
	public:
		// Setting.txt����ǂݍ���
		static void Read();
		// Setting.txt�֏�������
		static void Write();

		// ���݂̐ݒ���擾
		static const Parameter &GetParameter();

		// �X�N���[�����[�h�̐ݒ�
		static void SetScreenMode( const Parameter &param );
		// BGM�{�����[���̐ݒ�
		static void SetBGMVolume( const Parameter &param );
		// SE�{�����[���̐ݒ�
		static void SetSEVolume( const Parameter &param );
		// �R���g���[���[�̃A�i���O�X�e�B�b�N�̐ݒ�
		static void SetAxis();
		// �R���g���[���[�̃{�^���̐ݒ�
		static void SetButton();
		// �ő�t�@�C���L���b�V���T�C�Y�̐ݒ�
		static void SetMaxFileCacheSize( const Parameter &param );
		// �f�t�H���g�̐ݒ�̓K�p
		static void SetDefault();
	};
}
}
}
}