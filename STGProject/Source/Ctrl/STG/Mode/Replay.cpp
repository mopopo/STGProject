#include "PCH.h"
#include "Replay.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Ctrl/STG/Configuration/Manager.h"
#include "Mdl/STG/MyShip/Parameter.h"
#include "Mdl/STG/Stage/Stage/Parameter.h"
#include "Mdl/STG/Stage/StageSet/Parameter.h"

using namespace Game;
using namespace Ctrl::STG::Mode;


// �R���X�g���N�^
Replay::Replay( PScene pScene, const Conf::Replay &conf )
	: Base( pScene, conf.GetStageSetId() )
	, mpRandom( new Util::Random::Impl::SLN() )
	, mpReplayController( Util::Input::Manager::GetReplayController() )
{
	{
		Conf::MyShipParam param;
		param.SetMode( this );
		param.SetController( mpReplayController );
		Base::SetController( mpReplayController );

		Base::GetConfHolder().InitMyShip( param, conf.GetMyShipId() );
	}

	{
		Conf::StageSetParam param;
		param.SetMode( this );
		param.SetStageSetId( conf.GetStageSetId() );

		Base::GetConfHolder().InitStageSet( param, conf.GetStageSetId() );
	}

	if( conf.GetPlayAllFlag() )
	{
		Base::GetConfHolder().InitStageDataQueue( conf.GetStageSetId() );
	}
	else
	{
		while( !Base::GetConfHolder().GetStageDataQueue().empty() )
		{
			Base::GetConfHolder().GetStageDataQueue().pop();
		}

		Base::GetConfHolder().GetStageDataQueue().push( 
			Configuration::Manager::GetStageData( conf.GetStageId() ) );
	}
}

// ���̃X�e�[�W���擾����
IMode::PStage Replay::GetNextStage()
{
	assert( Base::GetConfHolder().GetStageSet() );

	Conf::StageParam param;
	param.SetStageSet( Base::GetConfHolder().GetStageSet().get() );

	return Base::GetConfHolder().GetNextStage( param );
}

// ����������̎擾
IMode::PRandom Replay::GetRandom() const
{
	return mpRandom;
}

// �V�[���̍ċN��
void Replay::Restart() const
{
	auto conf = boost::get<Conf::Replay>( Base::GetScene()->GetConf() );
	Scene::Manager::ChangeScene( 
		Util::Ptr<Scene::IScene>::Shared( new Scene::STG::STG( conf ) ) );
}


// �X�V���̏���
void Replay::OnUpdate()
{
}

// �`�掞�̏���
void Replay::OnDraw() const
{
}