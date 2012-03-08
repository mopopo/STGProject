#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Base.h"
#include "Util/Input/STG/Detail/ReplayController.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
	class Replay
		: public Base
	{
	public:
		// �R���X�g���N�^
		Replay( PScene pScene, const Conf::Replay &conf );

		// ���̃X�e�[�W���擾����
		virtual PStage GetNextStage();
		// ����������̎擾
		virtual PRandom GetRandom() const;
		// �V�[���̍ċN��
		virtual void Restart() const;

	private:
		PRandom mpRandom;
		typedef Util::Ptr<Util::Input::STG::Detail::ReplayController>::Shared 
			PReplayController;
		PReplayController mpReplayController;

		// �X�V���̏���
		virtual void OnUpdate();
		// �`�掞�̏���
		virtual void OnDraw() const;
	};
}
}
}
}