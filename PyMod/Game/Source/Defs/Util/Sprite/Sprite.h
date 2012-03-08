#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Sprite/DrawParameter.h"
#include "Defs/Util/File/FileObject.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sprite
{
	class Sprite
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );

		// �l�p�`�̕`��
		static void draw( const Game::Util::Sprite::DrawParameter &param );

		// �e�N�X�`�����t�@�C������ǂݍ���
		static Game::Util::Sprite::PTexture loadTexture( const std::wstring &path );
		static Game::Util::Sprite::PTexture loadTexture( 
			const std::wstring &path, 
			bool mipmap 
			);
		static Game::Util::Sprite::PTexture loadTexture( 
			const std::wstring &path, 
			bool mipmap, 
			const Selene::ColorF &transColor 
			);
		static Game::Util::Sprite::PTexture loadTexture( 
			const File::FileObject &fileObject );
		static Game::Util::Sprite::PTexture loadTexture( 
			const File::FileObject &fileObject, 
			bool mipmap 
			);
		static Game::Util::Sprite::PTexture loadTexture( 
			const File::FileObject &fileObject, 
			bool mipmap, 
			const Selene::ColorF &transColor 
			);

		// ��ʂ̐U���̐ݒ�
		static void setShake( float amount );
		static void setShake( float amount, float decAmount );
		static void setShake( const Selene::Point2DF &amount );
		static void setShake( const Selene::Point2DF &amount, float decAmount );
		// �U���̈ꎞ��~
		static void stopShake();
		// �U���̍ĊJ
		static void startShake();
		// �U���̃��Z�b�g
		static void resetShake();
		// �U���ʂ̎擾
		static Selene::Point2DF getCurrentShakeAmount();
	};
}
}
}