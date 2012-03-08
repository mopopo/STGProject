#include "PCH.h"
#include "Holder.h"

#include "Ctrl/STG/Configuration/Manager.h"

using namespace Game;
using namespace Ctrl::STG;
using namespace Mode::Conf;


// �R���X�g���N�^
Holder::Holder()
	: mActors( Selene::RectF( 
	0, 0, 
	static_cast<float>( Util::Consts::SCREEN_SIZE.x - Util::Consts::STG_INFAREA_SIZE.x ), 
	static_cast<float>( Util::Consts::SCREEN_SIZE.y ) ) )
	, mCurrentStageData( 0 )
{
}


// STG�\���I�u�W�F�N�g�̎擾
Actors &Holder::GetActors()
{
	return mActors;
}

const Actors &Holder::GetActors() const
{
	return mActors;
}


// �X�e�[�W�Z�b�g�̎擾
PStageSet Holder::GetStageSet() const
{
	return mpStageSet;
}

// �X�e�[�W�Z�b�g�̐ݒ�
void Holder::SetStageSet( PStageSet pStageSet )
{
	mpStageSet = pStageSet;
}

// �X�e�[�W�Z�b�g�̏�����
void Holder::InitStageSet( const StageSetParam &param, 
						  const Configuration::Data::StageSet::Id &stageSetId )
{
	mpStageSet = Configuration::Manager::GetStageSet( stageSetId, param );

	assert( mpStageSet );
}


// �X�e�[�W���L���[�̎擾
StageDataQueue &Holder::GetStageDataQueue()
{
	return mStageDataQueue;
}

// ���̃X�e�[�W���擾����
PStage Holder::GetNextStage( const StageParam &param )
{
	if( !mStageDataQueue.empty() )
	{
		PStage pStage = Configuration::Manager::GetStage( 
			mStageDataQueue.front().GetId(), param );
		assert( pStage );

		mCurrentStageData = mStageDataQueue.front();

		mStageDataQueue.pop();

		return pStage;
	}
	else
	{
		return PStage();
	}
}

// �X�e�[�W���L���[�̏�����
void Holder::InitStageDataQueue( const Configuration::Data::StageSet::Id &stageSetId )
{
	while( !mStageDataQueue.empty() )
	{
		mStageDataQueue.pop();
	}

	Configuration::Manager::StageDataSet dataSet;
	Configuration::Manager::GetStageDataSet( stageSetId, dataSet );
	assert( !dataSet.empty() );

	foreach( const Configuration::Data::Stage &data, dataSet )
	{
		mStageDataQueue.push( data );
	}
}

// ���݂̃X�e�[�W�f�[�^�̎擾
const StageData &Holder::GetCurrentStageData() const
{
	return mCurrentStageData;
}


// ���@�̏�����
void Holder::InitMyShip( const MyShipParam &param, 
						const Configuration::Data::MyShip::Id &myShipId )
{
	mActors.SetMyShip( 
		Configuration::Manager::GetMyShip( myShipId, param ) );

	assert( mActors.GetMyShip() );
}