#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
	class Manager
	{
	public:
		// 1�t���[�����̏�ԍX�V
		static void UpdateState();

		// �V�[���̐؂�ւ�
		static void ChangeScene( Util::Ptr<Scene::IScene>::Shared pNextScene );
		static void ChangeScene( const boost::python::object &obj );

		// �Q�[���̏I��
		static void End();
		// �I���t���O�̎擾
		static bool IsEnd();

		typedef Util::Delegate::Delegate0<bool> Delegate;
		// 1�t���[�����ɌĂяo���֐���ǉ�
		// ������0�A�߂�l��bool�ł���֐���ǉ��ł���
		// �߂�l��false�ɂȂ�ƁA���̊֐��͍폜�����
		static void AddUpdateFunction( const Delegate &func );
		// �ǉ������X�V�֐����N���A����
		// ���荞�݂�����ꍇ�͕��A����
		static void ClearUpdateFunction();
		// ��ԍX�V�����Ɋ��荞��
		static void Interrupt( const Delegate &func );
		// ���荞�܂�Ă��邩�ǂ������ׂ�
		static bool IsInterrupted();
		// ���荞�݂��畜�A����
		static void Return();
		// ���ׂĂ̊��荞�݂��畜�A����
		static void ReturnAll();

		// �V�[���̊J��
		// �I�����̌�n���p
		static void Release();
	};
}
}
}