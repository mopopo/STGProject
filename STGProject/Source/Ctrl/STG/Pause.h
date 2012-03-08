#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
	class Pause
	{
	public:
		typedef Util::Ptr<View::STG::Pause::IPause>::Shared PView;
		typedef Util::Delegate::Delegate0<> UpdateFunc;

		// �R���X�g���N�^
		Pause( const UpdateFunc &func, PView pView );
		// �X�V�֐�
		bool Update();
		bool Update_Continue();

	private:
		// ���݂̃|�[�Y���
		PView mpView;
		// �|�[�Y�������s����֐�(��ɕ`��)
		UpdateFunc mUpdateFunc;
	};
}
}
}