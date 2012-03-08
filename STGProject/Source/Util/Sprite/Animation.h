#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>
#include "DrawParameter.h"
#include "Util/RepeatCounter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sprite
{
	class Animation
	{
	public:
		// �R���X�g���N�^
		Animation();
		Animation( const Selene::Point2DI &frameSize, unsigned frameNum, float frameInterval, 
			const DrawParameter &param );

		// �t���[���̍X�V
		void Update();
		// �t���[���̕`��
		void Draw() const;

		// �t���[���T�C�Y�̎擾
		Selene::Point2DI GetFrameSize() const;
		// �t���[���T�C�Y�̐ݒ�
		void SetFrameSize( const Selene::Point2DI &size );
		// ���t���[�����̎擾
		unsigned GetFrameNum() const;
		// ���t���[�����̐ݒ�
		void SetFrameNum( unsigned num );
		// �t���[���ʒu�̎擾
		unsigned GetFramePos() const;
		// �t���[���ʒu�̐ݒ�
		void SetFramePos( unsigned framePos );

		// �A�j���[�V�����J�n
		void Play( unsigned framePos = 0 );
		// �A�j���[�V������~
		void Stop();
		// �A�j���[�V�����J�n�t���O�̎擾
		bool IsPlay() const;

		// �t���[���Ԋu�̎擾
		float GetFrameInterval() const;
		// �t���[���Ԋu�̐ݒ�
		void SetFrameInterval( float interval );

		// �`��p�����[�^�̎擾
		const DrawParameter &GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const DrawParameter &param );
		// �`���̐ݒ�
		void SetDst( const Selene::RectF &dst );
		// �`��D��x�̐ݒ�
		void SetPriority( Selene::Sint32 priority );
		// �A���t�@�u�����h�̎�ނ̐ݒ�
		void SetAlphaBlend( AlphaBlend alphaBlend = AB_BLEND );
		// ��]�p�x�̐ݒ�
		void SetRotDegree( float degree );
		// ��]���̒��S����̃I�t�Z�b�g�̐ݒ�
		void SetRotOffset( const Selene::Point2DF &rotOffset = Selene::Point2DF() );
		// �`��F�̐ݒ�
		void SetColor( const Selene::ColorF &color = Selene::ColorF() );

		// �`�悷��e�N�X�`���ʒu�̎擾
		Selene::RectF GetCurrentTextureSrc() const;

	private:
		Selene::Point2DI mFrameSize;
		unsigned mFrameNum;
		DrawParameter mDrawParam;

		Util::RepeatCounter mCounter;
		unsigned mFrameCount;
		bool mPlayFlag;
	};
}
}
}