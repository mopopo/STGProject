#include "PCH.h"
#include "Rotate.h"

using namespace Game;
using namespace Mdl::STG;
using namespace Bullet;
using namespace Util::STG;


 // �R���X�g���N�^
Rotate::Rotate( PMode pMode, const Locator::RotateF &locator, int hitRadius, 
			   const Util::Sprite::DrawParameter &drawParam )
: Base( pMode, locator.GetPosition(), hitRadius )
, mLocator( locator )
, mDrawParam( drawParam )
, mAuxs( pMode )
{
}


// �ʒu�̎擾
Vector2DF Rotate::GetPosition() const
{
	return mLocator.GetPosition();
}

// �O�͂̓K�p
Vector2DF Rotate::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// ���P�[�^�̎擾
Locator::RotateF &Rotate::GetLocator()
{
	return mLocator;
}

// �`��p�����[�^�̎擾
const Util::Sprite::DrawParameter &Rotate::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void Rotate::SetDrawParameter( const Util::Sprite::DrawParameter &drawParam )
{
	mDrawParam = drawParam;
}


void Rotate::OnUpdate()
{
	mLocator.Update();

	mDrawParam.SetDst( 
		mLocator.GetPosition().MakeRect( 
		mDrawParam.GetDst().w, mDrawParam.GetDst().h ) );
}

void Rotate::OnDraw() const
{
	Util::Sprite::Manager::Draw( mDrawParam );
}

void Rotate::OnDestruct()
{
	mAuxs.CreateParticle( mDrawParam );
}

void Rotate::OnDestruct( float hp )
{
	mAuxs.CreateFadeOut( mDrawParam );
}

void Rotate::OnErase()
{
	mAuxs.CreateFadeOut( mDrawParam );
}