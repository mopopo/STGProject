#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>
#include <memory>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sprite
{
	class Sprite;
}
}
}

namespace Game
{
namespace Util
{
namespace Sprite
{
	// �P�F�h��Ԃ��p�̃e�N�X�`��
	static const PTexture NULL_TEXTURE = PTexture();

	// �A���t�@�u�����f�B���O
	enum AlphaBlend
	{
		AB_OPACITY = Selene::Engine::Graphics::State::AB_OPACITY,	// �s����
		AB_BLEND = Selene::Engine::Graphics::State::AB_BLEND,		// ����
		AB_ADD = Selene::Engine::Graphics::State::AB_ADD,			// ���Z
		AB_SUB = Selene::Engine::Graphics::State::AB_SUB,			// ���Z
		AB_MUL = Selene::Engine::Graphics::State::AB_MUL,			// ��Z
		AB_SCREEN = Selene::Engine::Graphics::State::AB_SCREEN,		// �X�N���[��
	};

	// �l�p�`�`��̃p�����[�^
	class DrawParameter
	{
	public:
		// �R���X�g���N�^
		DrawParameter()
			: mpTexture( NULL_TEXTURE )
			, mSrc()
			, mDst()
			, mPriority()
			, mAlphaBlend( AB_BLEND )
			, mFiltering( true )
			, mRotDegree()
			, mRotOffset()
			, mColor()
			, mShakable( true )
			, mFlipedX( false )
			, mFlipedY( false )
		{}
		DrawParameter( PTexture pTexture, 
			const Selene::RectF &src, 
			const Selene::RectF &dst, 
			Selene::Sint32 priority, 
			AlphaBlend alphaBlend = AB_BLEND, 
			bool filtering = true, 
			float rotDegree = 0, 
			const Selene::Point2DF &rotOffset = Selene::Point2DF(), 
			const Selene::ColorF &color = Selene::ColorF(), 
			bool shakable = true )
			: mpTexture( pTexture )
			, mSrc( src )
			, mDst( dst )
			, mPriority( priority )
			, mAlphaBlend( alphaBlend )
			, mFiltering( filtering )
			, mRotDegree( rotDegree )
			, mRotOffset( rotOffset )
			, mColor( color )
			, mShakable( shakable )
			, mFlipedX( false )
			, mFlipedY( false )
		{}

		PTexture GetTexture() const { return mpTexture; }
		void SetTexture( PTexture pTexture = NULL_TEXTURE ) { mpTexture = pTexture; }
		Selene::RectF GetSrc() const { return mSrc; }
		void SetSrc( const Selene::RectF &src ) { mSrc = src; }
		Selene::RectF GetDst() const { return mDst; }
		void SetDst( const Selene::RectF &dst ) { mDst = dst; }
		Selene::Sint32 GetPriority() const { return mPriority; }
		void SetPriority( Selene::Sint32 priority ) { mPriority = priority; }
		AlphaBlend GetAlphaBlend() const { return mAlphaBlend; }
		void SetAlphaBlend( AlphaBlend alphaBlend = AB_BLEND ) { mAlphaBlend = alphaBlend; }
		bool IsFiltering() const { return mFiltering; }
		void SetFiltering( bool filtering = true ) { mFiltering = filtering; }
		float GetRotDegree() const { return mRotDegree; }
		void SetRotDegree( float rotDegree = 0 ) { mRotDegree = rotDegree; }
		Selene::Point2DF GetRotOffset() const { return mRotOffset; }
		void SetRotOffset( const Selene::Point2DF &rotOffset = Selene::Point2DF() ) { mRotOffset = rotOffset; }
		Selene::ColorF GetColor() const { return mColor; }
		void SetColor( const Selene::ColorF &color = Selene::ColorF() ) { mColor = color; }
		bool IsShakable() const { return mShakable; }
		void SetShakable( bool shakable = true ) { mShakable = shakable; }

		bool IsFlipedX() const { return mFlipedX; }
		void FlipX() { mFlipedX = !mFlipedX; }
		bool IsFlipedY() const { return mFlipedY; }
		void FlipY() { mFlipedY = !mFlipedY; }

	private:
		// �`��e�N�X�`���iNULL��Color�P�F�h��Ԃ��j
		PTexture mpTexture;
		// �`�挳
		Selene::RectF mSrc;
		// �`���
		Selene::RectF mDst;
		// �`��D��x�i�l���傫������O�ɕ`�悳���j
		Selene::Sint32 mPriority;
		// �A���t�@�u�����h�̎��
		AlphaBlend mAlphaBlend;
		// �t�B���^�̓K�p
		bool mFiltering;
		// ��]�p�x
		float mRotDegree;
		// ��]���̒��S����̃I�t�Z�b�g
		Selene::Point2DF mRotOffset;
		// �`��F�i�e�N�X�`���̐F�ɏ�Z�j
		Selene::ColorF mColor;
		// �U���t���O
		bool mShakable;
		// ���]�t���O
		bool mFlipedX, mFlipedY;

		friend class ::Defs::Util::Sprite::Sprite;
	};
}
}
}