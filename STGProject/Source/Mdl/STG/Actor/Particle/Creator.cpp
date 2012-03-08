#include "PCH.h"
#include "Creator.h"
#include "Particle.h"

#include "Ctrl/STG/Actors.h"
#include "Ctrl/STG/Mode/IMode.h"

using namespace Game;
using namespace Mdl::STG::Actor::Particle;
using namespace Util::STG;


// �R���X�g���N�^
Creator::Creator( PMode pMode, const Parameter &param )
: mpMode( pMode )
, mParam( param )
{
}


// �p�����[�^�̎擾
const Parameter &Creator::GetParameter() const
{
	return mParam;
}

// �p�����[�^�̐ݒ�
void Creator::SetParameter( const Parameter &param )
{
	mParam = param;
}


// �p�[�e�B�N������
void Creator::Create( unsigned num ) const
{
	Create( num, mParam );
}

void Creator::Create( unsigned num, const Parameter &param ) const
{
	for( unsigned i = 0; i < num; i++ )
	{
		Vector2DF pos( 
			mpMode->GetRandom()->GetFloat( param.GetPositionXDomain() ), 
			mpMode->GetRandom()->GetFloat( param.GetPositionYDomain() ) );
		float 
			angle = mpMode->GetRandom()->GetFloat( param.GetAngleDomain() ), 
			speed = mpMode->GetRandom()->GetFloat( param.GetSpeedDomain() ), 
			accel = mpMode->GetRandom()->GetFloat( param.GetAccelDomain() ), 
			zoomRate = mpMode->GetRandom()->GetFloat( param.GetZoomRateDomain() ), 
			zoomDecRate = mpMode->GetRandom()->GetFloat( param.GetZoomDecRateDomain() );

		Vector2DF speedVec, accelVec;
		speedVec.SetUnitVector( angle ) *= speed;
		accelVec.SetUnitVector( angle ) *= accel;

		PParticle pParticle( 
			new Particle( mpMode, pos, param.GetDrawParameter() ) );
		pParticle->GetLocator().GetSpeed() = speedVec;
		pParticle->GetLocator().GetAccel() = accelVec;
		pParticle->SetZoomRate( zoomRate );
		pParticle->SetZoomDecRate( zoomDecRate );

		mpMode->GetActors().GetActors().push_back( PActor( pParticle ) );
	}
}