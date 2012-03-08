#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Input
{
namespace STG
{
	enum KEY_ID
	{
		KEY_Z		= Selene::Engine::Input::CONTROLLER_BUTTON_01, 
		KEY_X		= Selene::Engine::Input::CONTROLLER_BUTTON_02, 
		KEY_C		= Selene::Engine::Input::CONTROLLER_BUTTON_03, 
		KEY_LSHIFT	= Selene::Engine::Input::CONTROLLER_BUTTON_04, 
		KEY_SPACE	= Selene::Engine::Input::CONTROLLER_BUTTON_05, 
	};

	// �V���[�e�B���O�p�̃R���g���[���[�̃C���^�[�t�F�[�X
	class IController
	{
	public:
		// �t���[��Ԃ����擾
		virtual bool IsFree( KEY_ID key ) const = 0;
		// �������u�Ԃ����擾
		virtual bool IsPull( KEY_ID key ) const = 0;
		// �������u�Ԃ����擾
		virtual bool IsPush( KEY_ID key ) const = 0;
		// �z�[���h��Ԃ����擾
		virtual bool IsHold( KEY_ID key ) const = 0;

		// �����̎擾
		virtual Util::STG::Vector2DF GetDirection() const = 0;

		// �f�X�g���N�^
		virtual ~IController() {}
	};
}
}
}
}