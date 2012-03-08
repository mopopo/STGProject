#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Base.h"


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
	class StageSelect
		: public Base
	{
	public:
		// �R���X�g���N�^
		StageSelect( PScene pScene, const Conf::StageSelect &conf );

		// ���̃X�e�[�W���擾����
		virtual PStage GetNextStage();
		// ����������̎擾
		virtual PRandom GetRandom() const;
		// �V�[���̍ċN��
		virtual void Restart() const;

	private:
		PRandom mpRandom;

		// �X�V���̏���
		virtual void OnUpdate();
		// �`�掞�̏���
		virtual void OnDraw() const;
	};
}
}
}
}