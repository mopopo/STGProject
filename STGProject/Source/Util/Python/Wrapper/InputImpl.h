#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IInput.h"
#include "Util/Input/Manager.h"
#include "Util/Input/STG/Detail/Controller.h"


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
	class InputImpl
		: public IInput
	{
	public:
		// �V���[�e�B���O�p�̃R���g���[���[�̎擾
		virtual PController GetController() const
		{
			return Input::Manager::GetController();
		}

		// ���p�\�ȃW���C�X�e�B�b�N�̐����擾
		virtual Selene::Sint32 GetJoystickCount() const
		{
			return Input::Manager::GetJoystickCount();
		}

		// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N���R���g���[���[�Ɋ��蓖�Ă�
		// �߂�l�́A���ݓ��͂���Ă���Q�[���p�b�h�̉��z�L�[
		// -1�łǂ�����͂���Ă��Ȃ����
		virtual Selene::Sint32 SetAxis( Input::STG::Detail::AXIS_ID axis )
		{
			return Input::Manager::GetSTGController()->SetAxis( axis );
		}
		// �Q�[���p�b�h�̃{�^�����R���g���[���[�Ɋ��蓖�Ă�
		// Axis�Ɋ��蓖�Ă��Ă��鉼�z�L�[�͖��������
		virtual Selene::Sint32 SetButton( Input::STG::KEY_ID key )
		{
			return Input::Manager::GetSTGController()->SetButton( key );
		}

		// ���蓖�Ă鉼�z�L�[���������Ă���ꍇ�͂�������g��
		virtual void SetAxis( Input::STG::Detail::AXIS_ID axis, Selene::Uint32 virtualKey )
		{
			Input::Manager::GetSTGController()->SetAxis( axis, virtualKey );
		}
		virtual void SetButton( Input::STG::KEY_ID key, Selene::Uint32 virtualKey )
		{
			Input::Manager::GetSTGController()->SetButton( key, virtualKey );
		}

		// ���蓖�Ă��Ă��鉼�z�L�[���擾����
		// ���蓖�Ă��Ă��Ȃ��ꍇ�A-1���Ԃ����
		virtual Selene::Sint32 GetAxisVirtualKey( Input::STG::Detail::AXIS_ID axis ) const
		{
			return Input::Manager::GetSTGController()->GetAxisVirtualKey( axis );
		}
		virtual Selene::Sint32 GetButtonVirtualKey( Input::STG::KEY_ID key ) const
		{
			return Input::Manager::GetSTGController()->GetButtonVirtualKey( key );
		}
	};
}
}
}
}