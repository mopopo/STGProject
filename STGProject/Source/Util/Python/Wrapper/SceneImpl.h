#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IScene.h"
#include "Ctrl/Scene/Manager.h"
#include "Ctrl/Scene/STG/Title.h"
#include "Ctrl/Scene/STG/STG.h"


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
	class SceneImpl
		: public IScene
	{
	public:
		// �V�[���̐؂�ւ�
		virtual void ChangeScene( const boost::python::object &obj )
		{
			Ctrl::Scene::Manager::ChangeScene( obj );
		}

		// �Q�[���̏I��
		virtual void End()
		{
			Ctrl::Scene::Manager::End();
		}
		// �I���t���O�̎擾
		virtual bool IsEnd()
		{
			return Ctrl::Scene::Manager::IsEnd();
		}

		typedef Util::Ptr<Ctrl::Scene::IScene>::Shared PScene;
		// STG�^�C�g���V�[���֐؂�ւ�
		virtual void ChangeToSTGTitle()
		{
			Ctrl::Scene::Manager::ChangeScene( 
				PScene( new Ctrl::Scene::STG::Title() ) );
		}
		// STG�V�[���֐؂�ւ�
		virtual void ChangeToSTG( int stageSetId, int myShipId )
		{
			Ctrl::STG::Mode::Conf::Regular conf( stageSetId, myShipId );
			Ctrl::Scene::Manager::ChangeScene( 
				PScene( new Ctrl::Scene::STG::STG( conf ) ) );
		}
	};
}
}
}
}