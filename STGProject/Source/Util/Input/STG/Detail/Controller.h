#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"
#include <boost/bimap.hpp>
#include <boost/noncopyable.hpp>


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
namespace Detail
{
	enum AXIS_ID
	{
		AXIS_X_MINUS	= Selene::Engine::Input::CONTROLLER_AXIS_02_MINUIS, 
		AXIS_X_PLUS		= Selene::Engine::Input::CONTROLLER_AXIS_02_PLUS, 
		AXIS_Y_MINUS	= Selene::Engine::Input::CONTROLLER_AXIS_01_MINUIS, 
		AXIS_Y_PLUS		= Selene::Engine::Input::CONTROLLER_AXIS_01_PLUS, 
	};

	// ���͂��󂯎�鉼�z�I�ȃR���g���[���[
	class Controller
		: public IController
		, public boost::noncopyable
	{
	public:
		// �t���[��Ԃ����擾
		virtual bool IsFree( KEY_ID key ) const;
		// �������u�Ԃ����擾
		virtual bool IsPull( KEY_ID key ) const;
		// �������u�Ԃ����擾
		virtual bool IsPush( KEY_ID key ) const;
		// �z�[���h��Ԃ����擾
		virtual bool IsHold( KEY_ID key ) const;

		// �����̎擾
		virtual Util::STG::Vector2DF GetDirection() const;

		// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N���R���g���[���[�Ɋ��蓖�Ă�
		// �߂�l�́A���ݓ��͂���Ă���Q�[���p�b�h�̉��z�L�[
		// -1�łǂ�����͂���Ă��Ȃ����
		Selene::Sint32 SetAxis( AXIS_ID axis );
		// �Q�[���p�b�h�̃{�^�����R���g���[���[�Ɋ��蓖�Ă�
		// Axis�Ɋ��蓖�Ă��Ă��鉼�z�L�[�͖��������
		Selene::Sint32 SetButton( KEY_ID key );

		// ���蓖�Ă鉼�z�L�[���������Ă���ꍇ�͂�������g��
		void SetAxis( AXIS_ID axis, Selene::Uint32 virtualKey );
		void SetButton( KEY_ID key, Selene::Uint32 virtualKey );

		// ���蓖�Ă��Ă��鉼�z�L�[���擾����
		// ���蓖�Ă��Ă��Ȃ��ꍇ�A-1���Ԃ����
		Selene::Sint32 GetAxisVirtualKey( AXIS_ID axis ) const;
		Selene::Sint32 GetButtonVirtualKey( KEY_ID key ) const;

		// �R���X�g���N�^
		Controller();

	private:
		// �R���g���[���[�̃C���^�[�t�F�[�X
		typedef Ptr<Selene::Engine::Input::IInputController>::Intrusive 
			PController;
		PController mpController;

		// Axis�Ɋ��蓖�Ă��Ă��鉼�z�L�[�̏W��
		boost::bimap<AXIS_ID, Selene::Uint32> mAxisVKeyMap;
		typedef boost::bimap<AXIS_ID, Selene::Uint32>::value_type AVKMapValueType;
		// �L�[�Ɋ��蓖�Ă��Ă��鉼�z�L�[�̏W��
		boost::bimap<KEY_ID, Selene::Uint32> mKeyVKeyMap;
		typedef boost::bimap<KEY_ID, Selene::Uint32>::value_type KVKMapValueType;
	};
}
}
}
}
}