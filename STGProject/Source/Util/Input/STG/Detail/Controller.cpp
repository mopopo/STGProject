#include "PCH.h"
#include "Controller.h"

using namespace Game;
using namespace Util::STG;
using namespace Util::Input::STG;
using namespace Detail;
using namespace Selene;
using namespace boost;


// �R���X�g���N�^
Controller::Controller()
: mpController( MakeIntrusivePtr( Core::Manager::GetInputManager()->CreateInputController( 0 ) ) )
, mAxisVKeyMap()
, mKeyVKeyMap()
{
	// ��1�̃}�C�i�X�i��j�փJ�[�\���L�[�́����A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_01_MINUIS, Engine::Input::KEY_UP );
	// ��1�̃v���X�i���j�փJ�[�\���L�[�́����A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_01_PLUS, Engine::Input::KEY_DOWN );
	// ��2�̃}�C�i�X�i���j�փJ�[�\���L�[�́����A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_02_MINUIS, Engine::Input::KEY_LEFT );
	// ��2�̃v���X�i�E�j�փJ�[�\���L�[�́����A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_AXIS_02_PLUS, Engine::Input::KEY_RIGHT );

	// �{�^��1��Z�L�[���A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_01, Engine::Input::KEY_Z );
	// �{�^��2��X�L�[���A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_02, Engine::Input::KEY_X );
	// �{�^��3��C�L�[���A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_03, Engine::Input::KEY_C );
	// �{�^��4��LShift�L�[���A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_04, Engine::Input::KEY_LSHIFT );
	// �{�^��5��Space�L�[���A�^�b�`
	mpController->AttachKeyboard( Engine::Input::CONTROLLER_BUTTON_05, Engine::Input::KEY_SPACE );
}


// �t���[��Ԃ����擾
bool Controller::IsFree( KEY_ID key ) const
{
	return mpController->IsFree( static_cast<Engine::Input::eControllerButton>( key ) );
}

// �������u�Ԃ����擾
bool Controller::IsPull( KEY_ID key ) const
{
	return mpController->IsPull( static_cast<Engine::Input::eControllerButton>( key ) );
}

// �������u�Ԃ����擾
bool Controller::IsPush( KEY_ID key ) const
{
	return mpController->IsPush( static_cast<Engine::Input::eControllerButton>( key ) );
}

// �z�[���h��Ԃ����擾
bool Controller::IsHold( KEY_ID key ) const
{
	return mpController->IsHold( static_cast<Engine::Input::eControllerButton>( key ) );
}


// �����̎擾
Vector2DF Controller::GetDirection() const
{
	Vector2DF direction;

	direction.y = -mpController->GetPower( Engine::Input::CONTROLLER_AXIS_01_MINUIS );
	direction.y = direction.y + mpController->GetPower( Engine::Input::CONTROLLER_AXIS_01_PLUS );
	direction.x = -mpController->GetPower( Engine::Input::CONTROLLER_AXIS_02_MINUIS );
	direction.x = direction.x + mpController->GetPower( Engine::Input::CONTROLLER_AXIS_02_PLUS );

	if( direction.GetAbs() > 1.0f )
	{
		direction.Normalize();
	}

	return direction;
}


// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N���R���g���[���[�Ɋ��蓖�Ă�
// �߂�l�́A���ݓ��͂���Ă���Q�[���p�b�h�̉��z�L�[
// -1�łǂ�����͂���Ă��Ȃ����
Sint32 Controller::SetAxis( AXIS_ID axis )
{
	Engine::Input::IJoystick *pJStick = 
		Core::Manager::GetInputManager()->GetJoystick( 0 );

	if( pJStick )
	{
		for( Uint32 vKey = 0; vKey < JOYSTICK_VIRTUAL_BUTTON_MAX; vKey++ )
		{
			if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_PUSH )
			{
				SetAxis( axis, vKey );

				return numeric_cast<Sint32>( vKey );
			}
			else if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_HOLD )
			{
				return numeric_cast<Sint32>( vKey );
			}
		}
	}

	return -1;
}

// �Q�[���p�b�h�̃{�^�����R���g���[���[�Ɋ��蓖�Ă�
// Axis�Ɋ��蓖�Ă��Ă��鉼�z�L�[�͖��������
Sint32 Controller::SetButton( KEY_ID key )
{
	Engine::Input::IJoystick *pJStick = 
		Core::Manager::GetInputManager()->GetJoystick( 0 );

	if( pJStick )
	{
		for( Uint32 vKey = 0; vKey < JOYSTICK_VIRTUAL_BUTTON_MAX; vKey++ )
		{
			if( mAxisVKeyMap.right.find( vKey ) != mAxisVKeyMap.right.end() )
			{
				continue;
			}
			else if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_PUSH )
			{
				SetButton( key, vKey );

				return numeric_cast<Sint32>( vKey );
			}
			else if( pJStick->GetVirtualButtonState( vKey ) == Engine::Input::BUTTON_STATE_HOLD )
			{
				return numeric_cast<Sint32>( vKey );
			}
		}
	}

	return -1;
}


// ���蓖�Ă鉼�z�L�[���������Ă���ꍇ�͂�������g��
void Controller::SetAxis( AXIS_ID axis, Uint32 virtualKey )
{
	{
		Uint32 prevVKey;

		{
			auto itr = mAxisVKeyMap.left.find( axis );
			if( itr != mAxisVKeyMap.left.end() )
			{
				prevVKey = itr->second;

				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->first ), 
					itr->second );
				mAxisVKeyMap.left.erase( itr );
			}
		}

		{
			auto itr = mAxisVKeyMap.right.find( virtualKey );
			if( itr != mAxisVKeyMap.right.end() )
			{
				AXIS_ID axisId = itr->second;
				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->second ), 
					itr->first );
				mAxisVKeyMap.right.erase( itr );

				mAxisVKeyMap.insert( AVKMapValueType( axisId, prevVKey ) );

				mpController->AttachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( axisId ), 
					prevVKey );
			}
		}
	}

	mpController->AttachGamepadVirtualButton( 
		static_cast<Engine::Input::eControllerButton>( axis ), 
		virtualKey );

	mAxisVKeyMap.insert( AVKMapValueType( axis, virtualKey ) );
}

void Controller::SetButton( KEY_ID key, Uint32 virtualKey )
{
	{
		Uint32 prevVKey;

		{
			auto itr = mKeyVKeyMap.left.find( key );
			if( itr != mKeyVKeyMap.left.end() )
			{
				prevVKey = itr->second;

				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->first ), 
					itr->second );
				mKeyVKeyMap.left.erase( itr );
			}
		}

		{
			auto itr = mKeyVKeyMap.right.find( virtualKey );
			if( itr != mKeyVKeyMap.right.end() )
			{
				KEY_ID keyId = itr->second;
				mpController->DetachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( itr->second ), 
					itr->first );
				mKeyVKeyMap.right.erase( itr );

				mKeyVKeyMap.insert( KVKMapValueType( keyId, prevVKey ) );

				mpController->AttachGamepadVirtualButton( 
					static_cast<Engine::Input::eControllerButton>( keyId ), 
					prevVKey );
			}
		}
	}

	mpController->AttachGamepadVirtualButton( 
		static_cast<Engine::Input::eControllerButton>( key ), 
		virtualKey );

	mKeyVKeyMap.insert( KVKMapValueType( key, virtualKey ) );
}


// ���蓖�Ă��Ă��鉼�z�L�[���擾����
// ���蓖�Ă��Ă��Ȃ��ꍇ�A-1���Ԃ����
Sint32 Controller::GetAxisVirtualKey( AXIS_ID axis ) const
{
	auto aItr = mAxisVKeyMap.left.find( axis );
	if( aItr != mAxisVKeyMap.left.end() )
	{
		return numeric_cast<Sint32>( aItr->second );
	}

	return -1;
}

Sint32 Controller::GetButtonVirtualKey( KEY_ID key ) const
{
	auto kItr = mKeyVKeyMap.left.find( key );
	if( kItr != mKeyVKeyMap.left.end() )
	{
		return numeric_cast<Sint32>( kItr->second );
	}

	return -1;
}