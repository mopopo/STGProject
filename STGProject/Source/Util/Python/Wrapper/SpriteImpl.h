#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ISprite.h"
#include "Util/Sprite/Manager.h"


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
	class SpriteImpl
		: public ISprite
	{
	public:
		// �l�p�`�̕`��
		virtual void Draw( const Sprite::DrawParameter &param )
		{
			Sprite::Manager::Draw( param );
		}

		// �e�N�X�`�����t�@�C������ǂݍ���
		virtual Sprite::PTexture LoadTexture( 
			const std::wstring &fileName, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			)
		{
			return Sprite::Manager::LoadTexture( fileName, mipmap, transColor );
		}
		virtual Sprite::PTexture LoadTexture( 
			File::PFile pFile, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			)
		{
			return Sprite::Manager::LoadTexture( pFile, mipmap, transColor );
		}

		// ��ʂ̐U���̐ݒ�
		virtual void SetShake( float amount, float decAmount = 1.0f )
		{
			Sprite::Manager::SetShake( amount, decAmount );
		}
		virtual void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f )
		{
			Sprite::Manager::SetShake( amount, decAmount );
		}
		// �U���̈ꎞ��~
		virtual void StopShake()
		{
			Sprite::Manager::StopShake();
		}
		// �U���̍ĊJ
		virtual void StartShake()
		{
			Sprite::Manager::StartShake();
		}
		// �U���̃��Z�b�g
		virtual void ResetShake()
		{
			Sprite::Manager::ResetShake();
		}
		// �U���ʂ̎擾
		virtual Selene::Point2DF GetCurrentShakeAmount()
		{
			return Sprite::Manager::GetCurrentShakeAmount();
		}
	};
}
}
}
}