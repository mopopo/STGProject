#include "PCH.h"
#include "FadeOut.h"

using namespace Game;
using namespace Mdl::STG::Actor;
using namespace Util::STG;
using namespace Selene;

namespace
{
	static const unsigned INIT_FRAME_NUM = 60;
}


// �R���X�g���N�^
FadeOut::FadeOut( PMode pMode, const Hit::RectI &validRect )
: Base( pMode, validRect )
, mLocator()
, mDrawParam()
{
	Base::SetValidFrameNum( INIT_FRAME_NUM );
	mLocator.GetPosition() = Base::GetValidRect().GetPosition();
}


// �ʒu�̎擾
Vector2DF FadeOut::GetPosition() const
{
	return mLocator.GetPosition();
}

// �O�͂̓K�p
Vector2DF FadeOut::ApplyExternalForce( const Vector2DF &vec )
{
	return mLocator.ApplyExternalForce( vec );
}


// �`��p�����[�^�̎擾
Util::Sprite::DrawParameter FadeOut::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void FadeOut::SetDrawParameter( const Util::Sprite::DrawParameter &param )
{
	mDrawParam = param;

	mMaxAlpha = param.GetColor().a;
}

// ��������܂ł̑��t���[�����̎擾
unsigned FadeOut::GetFrameNum() const
{
	return Base::GetValidFrameNum();
}

// ��������܂ł̑��t���[�����̐ݒ�
void FadeOut::SetFrameNum( unsigned num )
{
	Base::SetValidFrameNum( num );
}

// �t���[���J�E���g�̎擾
unsigned FadeOut::GetFrameCount() const
{
	return Base::GetFrameCount();
}

// �t���[���J�E���g�̐ݒ�
void FadeOut::SetFrameCount( unsigned count )
{
	Base::SetFrameCount( count );
}


void FadeOut::OnUpdate()
{
	mLocator.Update();
}

void FadeOut::OnDraw() const
{
	Util::Sprite::DrawParameter dParam = mDrawParam;

	RectF dst = dParam.GetDst();
	dst = mLocator.GetPosition().MakeRect( dst.w, dst.h );
	dParam.SetDst( dst );

	ColorF color = dParam.GetColor();
	color.a = mMaxAlpha/GetFrameNum() * ( GetFrameNum() - GetFrameCount() );
	dParam.SetColor( color );

	Util::Sprite::Manager::Draw( dParam );
}

void FadeOut::OnErase()
{
}