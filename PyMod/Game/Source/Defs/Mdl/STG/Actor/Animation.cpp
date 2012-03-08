#include "PCH.h"
#include "Animation.h"

using namespace Defs::Mdl::STG::Actor;
using namespace Game::Util::STG;
using namespace Selene;


// �R���X�g���N�^
Animation::Animation( const Hit::RectI &validRect, 
	const Defs::Util::Sprite::Animation::Manager &animationManager )
: Base( validRect )
, mAnimationManager( animationManager )
{
	mLocator.GetPosition() = Base::GetValidRect().GetPosition();

	mAnimationManager.Play();
}


// �ʒu�̎擾
Vector2DF Animation::GetPosition() const
{
	return mLocator.GetPosition();
}

// �O�͂̓K�p
Vector2DF Animation::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// �A�j���[�V�����ݒ�̎擾
Defs::Util::Sprite::Animation::Manager &Animation::GetAnimationManager()
{
	return mAnimationManager;
}

// ���P�[�^�̎擾
Locator::LinearF &Animation::GetLocator()
{
	return mLocator;
}


void Animation::OnUpdate()
{
	mLocator.Update();

	mAnimationManager.Update();

	if( !mAnimationManager.IsPlaying() )
	{
		Base::SetValid( false );
	}

	{
		auto frameHolder = mAnimationManager.GetFrameHolder();
		auto drawParam = frameHolder->GetDrawParameter();

		RectF dst = drawParam.GetDst();
		drawParam.SetDst( mLocator.GetPosition().MakeRect( dst.w, dst.h ) );

		frameHolder->SetDrawParameter( drawParam );
	}
}

void Animation::OnDraw() const
{
	mAnimationManager.Draw();
}

void Animation::OnErase()
{
	mAuxs.CreateFadeOut( 
		mAnimationManager.GetFrameHolder()->GetDrawParameter() );
}