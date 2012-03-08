#include "PCH.h"
#include "Animation.h"

using namespace Game;
using namespace Mdl::STG::Actor;
using namespace Util::STG;
using namespace Selene;


// �R���X�g���N�^
Animation::Animation( PMode pMode, const Hit::RectI &validRect, 
					 const Util::Sprite::Animation &animation )
: Base( pMode, validRect )
, mAnimation( animation )
, mAuxs( pMode )
{
	mLocator.GetPosition() = Base::GetValidRect().GetPosition();

	mAnimation.Play();
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
Util::Sprite::Animation &Animation::GetAnimation()
{
	return mAnimation;
}


void Animation::OnUpdate()
{
	mLocator.Update();

	mAnimation.Update();

	if( !mAnimation.IsPlay() )
	{
		Base::SetValid( false );
	}

	{
		RectF dst = mAnimation.GetDrawParameter().GetDst();
		mAnimation.SetDst( mLocator.GetPosition().MakeRect( dst.w, dst.h ) );
	}
}

void Animation::OnDraw() const
{
	mAnimation.Draw();
}

void Animation::OnErase()
{
	mAuxs.CreateFadeOut( mAnimation.GetDrawParameter() );
}