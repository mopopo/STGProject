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
namespace Font
{
	// �t�H���g�֌W�̏���
	class Manager
	{
	public:
		// �t�H���g�f�[�^�̓ǂݍ���
		// fontFilePath�ɂ́ASFF�t�@�C���̃p�X���w�肷�邱��
		static PFont LoadFont( const std::wstring &fontFilePath );
		static void LoadFont( const std::vector<std::wstring> &fontFilePathList, 
			FontMap &fonts );
	};
}
}
}