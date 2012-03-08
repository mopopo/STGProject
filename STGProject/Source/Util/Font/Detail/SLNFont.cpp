#include "PCH.h"
#include "SLNFont.h"

using namespace Game;
using namespace Util::Font::Detail;
using namespace Selene;
using namespace std;


// �R���X�g���N�^
SLNFont::SLNFont( PSLNFont pFont )
: mpFont( pFont )
, mShakable( true )
{
}


// �e�L�X�g�f�[�^�̕����T�C�Y�ݒ�
void SLNFont::SetSize( Sint32 size )
{
	mpFont->SetDrawFontSize( size );
}

// �e�L�X�g�f�[�^�̃I���W�i���̕����T�C�Y�擾
Sint32 SLNFont::GetOriginalSize() const
{
	return mpFont->GetOriginalFontSize();
}

// �e�L�X�g�f�[�^�̕����T�C�Y�擾
Sint32 SLNFont::GetSize() const
{
	return mpFont->GetDrawFontSize();
}


// �e�L�X�g�f�[�^�̕`��D��x��ݒ�
void SLNFont::SetPriority( Sint32 priority )
{
	mpFont->SetPriority( priority );
}


// �U���t���O�̎擾
bool SLNFont::IsShakable() const
{
	return mShakable;
}

// �U���t���O�̐ݒ�
void SLNFont::SetShakable( bool shakable )
{
	mShakable = shakable;
}


// �e�L�X�g�f�[�^�̕����`��
Point2DF SLNFont::Draw( const Point2DF &position, const ColorF &color, 
					   const wstring &string, Sint32 length )
{
	Point2DF pos = position;
	if( mShakable )
	{
		pos += Sprite::Manager::GetCurrentShakeAmount();
	}

	return mpFont->DrawRequest( pos, color, string.c_str(), length );
}

// �������e�L�X�g�f�[�^�̕����`��
Point2DF SLNFont::DrawLeft( const RectF &rect, const Point2DF &offset, 
						   const ColorF &color, const wstring &string, 
						   Sint32 length )
{
	RectF baseRect = rect;
	if( mShakable )
	{
		Point2DF shakeAmount = 
			Sprite::Manager::GetCurrentShakeAmount();
		baseRect.x += shakeAmount.x;
		baseRect.y += shakeAmount.y;
	}

	return mpFont->DrawRequestLeft( 
		baseRect, offset, color, string.c_str(), length );
}

// ���������e�L�X�g�f�[�^�̕����`��
Point2DF SLNFont::DrawCenter( const RectF &rect, const Point2DF &offset, 
							 const ColorF &color, const wstring &string, 
							 Sint32 length )
{
	RectF baseRect = rect;
	if( mShakable )
	{
		Point2DF shakeAmount = 
			Sprite::Manager::GetCurrentShakeAmount();
		baseRect.x += shakeAmount.x;
		baseRect.y += shakeAmount.y;
	}

	return mpFont->DrawRequestCenter( 
		baseRect, offset, color, string.c_str(), length );
}

// �E�����e�L�X�g�f�[�^�̕����`��
Point2DF SLNFont::DrawRight( const RectF &rect, const Point2DF &offset, 
							const ColorF &color, const wstring &string, 
							Sint32 length )
{
	RectF baseRect = rect;
	if( mShakable )
	{
		Point2DF shakeAmount = 
			Sprite::Manager::GetCurrentShakeAmount();
		baseRect.x += shakeAmount.x;
		baseRect.y += shakeAmount.y;
	}

	return mpFont->DrawRequestRight( 
		baseRect, offset, color, string.c_str(), length );
}