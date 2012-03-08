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
namespace Ctrl
{
namespace STG
{
namespace Option
{
namespace Detail
{
	class SettingFile
	{
	public:
		// �ݒ�t�@�C����ǂݍ���
		static void Read( const std::string &path, Parameter &param );
		// �ݒ�t�@�C������������
		static void Write( const std::string &path, const Parameter &param );
	};
}
}
}
}
}