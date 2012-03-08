#include "PCH.h"
#include "Regular.h"

#include "Ctrl/Scene/STG/STG.h"
#include "Mdl/STG/MyShip/Parameter.h"
#include "Mdl/STG/Stage/Stage/Parameter.h"
#include "Mdl/STG/Stage/StageSet/Parameter.h"

using namespace Game;
using namespace Ctrl::STG::Mode;


// �R���X�g���N�^
Regular::Regular( PScene pScene, const Conf::Regular &conf )
	: Base( pScene, conf.GetStageSetId() )
	, mpRandom( new Util::Random::Impl::SLN( static_cast<int>( ::time( NULL ) ) ) )
{
	{
		Conf::MyShipParam param;
		param.SetMode( this );
		param.SetController( Util::Input::Manager::GetController() );
		Base::SetController( param.GetController() );

		Base::GetConfHolder().InitMyShip( param, conf.GetMyShipId() );
	}

	{
		Conf::StageSetParam param;
		param.SetMode( this );
		param.SetStageSetId( conf.GetStageSetId() );

		Base::GetConfHolder().InitStageSet( param, conf.GetStageSetId() );
	}

	{
		Base::GetConfHolder().InitStageDataQueue( conf.GetStageSetId() );
	}
}

// ���̃X�e�[�W���擾����
IMode::PStage Regular::GetNextStage()
{
	assert( Base::GetConfHolder().GetStageSet() );

	Conf::StageParam param;
	param.SetStageSet( Base::GetConfHolder().GetStageSet().get() );

	return Base::GetConfHolder().GetNextStage( param );
}

// ����������̎擾
IMode::PRandom Regular::GetRandom() const
{
	return mpRandom;
}

// �V�[���̍ċN��
void Regular::Restart() const
{
	auto conf = boost::get<Conf::Regular>( Base::GetScene()->GetConf() );
	Scene::Manager::ChangeScene(
		Util::Ptr<Scene::IScene>::Shared( new Scene::STG::STG( conf ) ) );
}


// �X�V���̏���
void Regular::OnUpdate()
{
}

// �`�掞�̏���
void Regular::OnDraw() const
{
}