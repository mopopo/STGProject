#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Ctrl/Scene/IScene.h"
#include <boost/noncopyable.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
	// �ŏ��Ɏ��s�����V�[��
	// �e�평�����Ǝ��̃V�[���ւ̈ڍs���s��
	class Initialize
		: public IScene
		, public boost::noncopyable
	{
	public:
		// 1�t���[�����̏�ԍX�V
		virtual void UpdateState();

	private:
	};
}
}
}