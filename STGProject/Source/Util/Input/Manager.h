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
namespace Input
{
	// ���͂Ɋւ��鏈��
	class Manager
	{
	public:
		// �W���R���g���[���[�̎擾
		typedef Util::Ptr<STG::IController>::Shared 
			PController;
		static PController GetController();
		// �V���[�e�B���O�p�̃R���g���[���[�̎擾
		typedef Util::Ptr<STG::Detail::Controller>::Shared 
			PSTGController;
		static PSTGController GetSTGController();
		// ���v���C�Đ��p�̃R���g���[���[�̎擾
		typedef Util::Ptr<STG::Detail::ReplayController>::Shared 
			PSTGReplayController;
		static PSTGReplayController GetReplayController();

		// ���p�\�ȃW���C�X�e�B�b�N�̐����擾
		static Selene::Sint32 GetJoystickCount();

		// �R���g���[���[�̊J��
		// ��n���p
		static void Release();
	};
}
}
}