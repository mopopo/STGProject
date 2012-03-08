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
namespace Util
{
namespace Python
{
namespace Wrapper
{
	class IScene
	{
	public:
		// �V�[���̐؂�ւ�
		virtual void ChangeScene( const boost::python::object &obj ) = 0;

		// �Q�[���̏I��
		virtual void End() = 0;
		// �I���t���O�̎擾
		virtual bool IsEnd() = 0;

		// STG�^�C�g���V�[���֐؂�ւ�
		virtual void ChangeToSTGTitle() = 0;
		// STG�V�[���֐؂�ւ�
		virtual void ChangeToSTG( int stageSetId, int myShipId ) = 0;

		virtual ~IScene() {}
	};
}
}
}
}