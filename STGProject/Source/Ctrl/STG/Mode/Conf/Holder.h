#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Configuration/Data/MyShip.h"
#include "Ctrl/STG/Configuration/Data/StageSet.h"
#include "Ctrl/STG/Configuration/Data/Stage.h"


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
namespace Conf
{
	typedef Util::Ptr<Mdl::STG::Stage::StageSet::IStageSet>::Shared PStageSet;
	typedef Mdl::STG::Stage::StageSet::Parameter StageSetParam;
	typedef Configuration::Data::Stage StageData;
	typedef std::queue<StageData> StageDataQueue;
	typedef Mdl::STG::Stage::Stage::Parameter StageParam;
	typedef Util::Ptr<Mdl::STG::Stage::Stage::IStage>::Shared PStage;
	typedef Mdl::STG::MyShip::Parameter MyShipParam;

	class Holder
	{
	public:
		// �R���X�g���N�^
		Holder();

		// STG�\���I�u�W�F�N�g�̎擾
		Actors &GetActors();
		const Actors &GetActors() const;

		// �X�e�[�W�Z�b�g�̎擾
		PStageSet GetStageSet() const;
		// �X�e�[�W�Z�b�g�̐ݒ�
		void SetStageSet( PStageSet pStageSet );
		// �X�e�[�W�Z�b�g�̏�����
		void InitStageSet( const StageSetParam &param, 
			const Configuration::Data::StageSet::Id &stageSetId );

		// �X�e�[�W���L���[�̎擾
		StageDataQueue &GetStageDataQueue();
		// ���̃X�e�[�W���擾����
		PStage GetNextStage( const StageParam &param );
		// �X�e�[�W���L���[�̏�����
		void InitStageDataQueue( const Configuration::Data::StageSet::Id &stageSetId );
		// ���݂̃X�e�[�W�f�[�^�̎擾
		const StageData &GetCurrentStageData() const;

		// ���@�̏�����
		void InitMyShip( const MyShipParam &param, 
			const Configuration::Data::MyShip::Id &myShipId );

	private:
		Actors mActors;
		PStageSet mpStageSet;
		StageDataQueue mStageDataQueue;
		StageData mCurrentStageData;
	};
}
}
}
}
}