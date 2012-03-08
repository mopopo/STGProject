#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IFont.h"
#include "Util/Font/Manager.h"


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
	class FontImpl
		: public IFont
	{
	public:
		// �t�H���g�f�[�^�̓ǂݍ���
		// fontFilePath�ɂ́ASFF�t�@�C���̃p�X���w�肷�邱��
		virtual Font::PFont LoadFont( const std::wstring &fontFilePath ) const
		{
			return Font::Manager::LoadFont( fontFilePath );
		}
	};
}
}
}
}