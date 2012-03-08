#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Delegate/Delegate.h"


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
	class IMode
	{
	public:
		// �t���[�����̍X�V
		virtual void Update() = 0;
		// �t���[�����̕`��
		virtual void Draw() const = 0;

		// �V�[���̎擾
		typedef Ctrl::Scene::STG::STG *PScene;
		virtual PScene GetScene() const = 0;
		// ���̃X�e�[�W���擾����
		typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
		virtual PStage GetNextStage() = 0;
		// ���݂̃X�e�[�W�f�[�^�̎擾
		typedef Configuration::Data::Stage StageData;
		virtual const StageData &GetCurrentStageData() const = 0;
		// STG�\���I�u�W�F�N�g�̎擾
		virtual Actors &GetActors() = 0;
		virtual const Actors &GetActors() const = 0;
		// �R���g���[���̎擾
		typedef Util::Ptr<Util::Input::STG::IController>::Shared PController;
		virtual PController GetController() const = 0;
		// ����������̎擾
		typedef Util::Random::PRandom PRandom;
		virtual PRandom GetRandom() const = 0;
		// �f�o�b�O��񕶎���\���t���O�̎擾
		virtual bool GetDebugStrFlag() const = 0;
		// �f�o�b�O��񕶎���\���t���O�̐ݒ�
		virtual void SetDebugStrFlag( bool flag ) = 0;
		// �V�[���̍ċN��
		virtual void Restart() const = 0;
		// �I�u�W�F�N�g�p�̈�ӂȐ����l�̐���
		virtual Selene::Uint64 GenObjectId() = 0;

		virtual ~IMode() {}
	};
}
}
}
}