#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <vector>


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
	class IFont
	{
	public:
		// �t�H���g�f�[�^�̓ǂݍ���
		// fontFilePath�ɂ́ASFF�t�@�C���̃p�X���w�肷�邱��
		virtual Font::PFont LoadFont( const std::wstring &fontFilePath ) const = 0;

		virtual ~IFont() {}
	};
}
}
}
}