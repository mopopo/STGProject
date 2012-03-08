#include "PCH.h"
#include "Manager.h"
#include "STG/Detail/Controller.h"
#include "STG/Detail/ReplayController.h"

using namespace Game;
using namespace Util::Input;
using namespace Selene;

namespace
{
	static Manager::PSTGController mpSTGController;
	static Manager::PSTGReplayController mpReplayController;
}


// �W���R���g���[���[�̎擾
Manager::PController Manager::GetController()
{
	return PController( GetSTGController() );
}

// �V���[�e�B���O�p�̃R���g���[���[�̎擾
Manager::PSTGController Manager::GetSTGController()
{
	if( !mpSTGController )
	{
		mpSTGController = 
			PSTGController( new STG::Detail::Controller() );
	}

	return mpSTGController;
}

// ���v���C�Đ��p�̃R���g���[���[�̎擾
Manager::PSTGReplayController Manager::GetReplayController()
{
	if( !mpReplayController )
	{
		mpReplayController = 
			PSTGReplayController( new STG::Detail::ReplayController() );
	}

	return mpReplayController;
}


// ���p�\�ȃW���C�X�e�B�b�N�̐����擾
Sint32 Manager::GetJoystickCount()
{
	return Core::Manager::GetInputManager()->GetJoystickCount();
}


// �R���g���[���[�̊J��
void Manager::Release()
{
	mpSTGController.reset();
	mpReplayController.reset();
}