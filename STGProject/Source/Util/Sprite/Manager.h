#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sprite
{
	// �X�v���C�g�֘A�̑���
	class Manager
	{
	public:
		// �t���[�����̍X�V
		static void Update();

		// �l�p�`�̕`��
		static void Draw( const Sprite::DrawParameter &param );

		// �e�N�X�`�����t�@�C������ǂݍ���
		static PTexture LoadTexture( 
			const std::wstring &fileName, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			);
		static PTexture LoadTexture( 
			File::PFile pFile, 
			bool mipmap = true, 
			const Selene::ColorF &transColor = Selene::ColorF( 0, 0, 0, 0 ) 
			);
		static void LoadTexture( const TextureSrcMap &srcFilePathMap, 
			TextureMap &textures );

		// ��ʂ̐U���̐ݒ�
		static void SetShake( float amount, float decAmount = 1.0f );
		static void SetShake( const Selene::Point2DF &amount, float decAmount = 1.0f );
		// �U���̈ꎞ��~
		static void StopShake();
		// �U���̍ĊJ
		static void StartShake();
		// �U���̃��Z�b�g
		static void ResetShake();
		// �U���ʂ̎擾
		static Selene::Point2DF GetCurrentShakeAmount();
	};
}
}
}