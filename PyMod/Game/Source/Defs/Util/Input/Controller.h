#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Input
{
	class Controller
	{
	public:
		typedef Game::Util::Ptr<Game::Util::Input::STG::IController>::Shared 
			PController;
		Controller( PController p )
			: mpCtrl( p )
		{}

		// �t���[��Ԃ����擾
		bool IsFree( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsFree( key );
		}
		// �������u�Ԃ����擾
		bool IsPull( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsPull( key );
		}
		// �������u�Ԃ����擾
		bool IsPush( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsPush( key );
		}
		// �z�[���h��Ԃ����擾
		bool IsHold( Game::Util::Input::STG::KEY_ID key ) const
		{
			return mpCtrl->IsHold( key );
		}

		// �����̎擾
		Game::Util::STG::Vector2DF GetDirection() const
		{
			return mpCtrl->GetDirection();
		}

		PController GetPtr() const
		{
			return mpCtrl;
		}

	private:
		PController mpCtrl;
	};
}
}
}