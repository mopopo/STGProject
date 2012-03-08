#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"


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
	class IInput
	{
	public:
		// �V���[�e�B���O�p�̃R���g���[���[�̎擾
		typedef Ptr<Input::STG::IController>::Shared PController;
		virtual PController GetController() const = 0;

		// ���p�\�ȃW���C�X�e�B�b�N�̐����擾
		virtual Selene::Sint32 GetJoystickCount() const = 0;

		// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N���R���g���[���[�Ɋ��蓖�Ă�
		// �߂�l�́A���ݓ��͂���Ă���Q�[���p�b�h�̉��z�L�[
		// -1�łǂ�����͂���Ă��Ȃ����
		virtual Selene::Sint32 SetAxis( Input::STG::Detail::AXIS_ID axis ) = 0;
		// �Q�[���p�b�h�̃{�^�����R���g���[���[�Ɋ��蓖�Ă�
		// Axis�Ɋ��蓖�Ă��Ă��鉼�z�L�[�͖��������
		virtual Selene::Sint32 SetButton( Input::STG::KEY_ID key ) = 0;

		// ���蓖�Ă鉼�z�L�[���������Ă���ꍇ�͂�������g��
		virtual void SetAxis( Input::STG::Detail::AXIS_ID axis, Selene::Uint32 virtualKey ) = 0;
		virtual void SetButton( Input::STG::KEY_ID key, Selene::Uint32 virtualKey ) = 0;

		// ���蓖�Ă��Ă��鉼�z�L�[���擾����
		// ���蓖�Ă��Ă��Ȃ��ꍇ�A-1���Ԃ����
		virtual Selene::Sint32 GetAxisVirtualKey( Input::STG::Detail::AXIS_ID axis ) const = 0;
		virtual Selene::Sint32 GetButtonVirtualKey( Input::STG::KEY_ID key ) const = 0;

		virtual ~IInput() {}
	};
}
}
}
}