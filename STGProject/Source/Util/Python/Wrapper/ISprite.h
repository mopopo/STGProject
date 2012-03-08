#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <Selene.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Python
{
namespace Wrapper
{
	class ISprite
	{
	public:
		// �l�p�`�̕`��
		virtual void Draw( const Sprite::DrawParameter &param ) = 0;

		// �e�N�X�`�����t�@�C������ǂݍ���
		virtual Sprite::PTexture LoadTexture( 
			const std::wstring &fileName, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			) = 0;
		virtual Sprite::PTexture LoadTexture( 
			File::PFile pFile, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			) = 0;

		// ��ʂ̐U���̐ݒ�
		virtual void SetShake( float amount, float decAmount = 1.0f ) = 0;
		virtual void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f ) = 0;
		// �U���̈ꎞ��~
		virtual void StopShake() = 0;
		// �U���̍ĊJ
		virtual void StartShake() = 0;
		// �U���̃��Z�b�g
		virtual void ResetShake() = 0;
		// �U���ʂ̎擾
		virtual Selene::Point2DF GetCurrentShakeAmount() = 0;

		virtual ~ISprite() {}
	};
}
}
}
}