#include "PCH.h"
#include "FadeOut.h"

#include "Defs/Util/Sprite/Sprite.h"

using namespace Defs::Mdl::STG::Actor;
using namespace Game::Util::STG;
using namespace Selene;

namespace
{
	static const unsigned INIT_FRAME_NUM = 60;
}


// �R���X�g���N�^
FadeOut::FadeOut( const Hit::RectI &validRect )
: Base( validRect )
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
FadeOut::DrawParameter FadeOut::GetDrawParameter() const
{
	return mDrawParam;
}

// �`��p�����[�^�̐ݒ�
void FadeOut::SetDrawParameter( const DrawParameter &param )
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

// ���P�[�^�̎擾
Locator::LinearF &FadeOut::GetLocator()
{
	return mLocator;
}


void FadeOut::OnUpdate()
{
	mLocator.Update();
}

void FadeOut::OnDraw() const
{
	DrawParameter dParam = mDrawParam;

	RectF dst = dParam.GetDst();
	dst = mLocator.GetPosition().MakeRect( dst.w, dst.h );
	dParam.SetDst( dst );

	ColorF color = dParam.GetColor();
	color.a = mMaxAlpha/GetFrameNum() * ( GetFrameNum() - GetFrameCount() );
	dParam.SetColor( color );

	Defs::Util::Sprite::Sprite::draw( dParam );
}

void FadeOut::OnErase()
{
}