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
namespace Python
{
namespace Wrapper
{
	class IConsole
	{
	public:
		// �R���\�[���E�B���h�E���쐬����
		virtual bool Create() const = 0;
		// �R���\�[���E�B���h�E�ɏ�������
		virtual bool Write( const std::wstring &str ) const = 0;
		virtual bool WriteLine( const std::wstring &str ) const = 0;
		// �R���\�[����j������
		virtual bool Delete() const = 0;

		virtual ~IConsole() {}
	};
}
}
}
}