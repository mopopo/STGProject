#include "PCH.h"
#include "Linear.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Bullet;
using namespace Util::STG;


// �R���X�g���N�^
Linear::Linear( PMode pMode, const Locator::LinearF &locator, int hitRadius, 
			   const Util::Sprite::DrawParameter &drawParam )
: Base( pMode, locator.GetPosition(), hitRadius )
, mLocator( locator )
, mDrawParam( drawParam )
, mAuxs( pMode )
{
}


// �ʒu�̎擾
Vector2DF Linear::GetPosition() const
{
	return mLocator.GetPosition();
}

// �O�͂̓K�p
Vector2DF Linear::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ���P�[�^�̎擾
Locator::LinearF &Linear::GetLocator()
{
	return mLocator;
}

// �`��p�����[�^�̎擾
const Util::Sprite::DrawParameter &Linear::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void Linear::SetDrawParameter( const Util::Sprite::DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


void Linear::OnUpdate()
{
	mLocator.Update();

	mDrawParam.SetDst( 
		mLocator.GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void Linear::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Linear::OnDestruct()
{
	mAuxs.CreateParticle( mDrawParam );
}

void Linear::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Linear::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}