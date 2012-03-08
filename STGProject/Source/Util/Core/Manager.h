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
namespace Core
{
	class Manager
	{
	public:
		// �G���W���̏�����
		// �K���ŏ��ɌĂяo������
		static bool InitEngine();

		// �R�A�̎擾
		static PCore GetCore();
		// �X�v���C�g�p�C���^�[�t�F�C�X�̎擾
		static PSpriteRenderer GetSpriteRenderer();
		// �O���t�B�N�X�}�l�[�W���[�̎擾
		static PGraphicsManager GetGraphicsManager();
		// �t�@�C���}�l�[�W���[�̎擾
		static PFileManager GetFileManager();
		// �T�E���h�}�l�[�W���[�̎擾
		static PSoundManager GetSoundManager();
		// �C���v�b�g�}�l�[�W���[�̎擾
		static PInputManager GetInputManager();

		// �R�A�̊J��
		// ��n���p
		static void Release();
	};
}
}
}