#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Ctrl/Scene/IScene.h"
#include <boost/noncopyable.hpp>
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
namespace STG
{
	class Title
		: public IScene
		, public boost::noncopyable
	{
	public:
		// 1�t���[�����̏�ԍX�V
		virtual void UpdateState();

		// �R���X�g���N�^
		Title();
	private:
		// ���݂̃^�C�g�����
		boost::python::object currentView;
	};
}
}
}
}