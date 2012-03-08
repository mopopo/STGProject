#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "IConsole.h"
#include "Util/Console.h"


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
	class ConsoleImpl
		: public IConsole
	{
	public:
		// �R���\�[���E�B���h�E���쐬����
		virtual bool Create() const
		{
			return Util::Console::Create();
		}
		// �R���\�[���E�B���h�E�ɏ�������
		virtual bool Write( const std::wstring &str ) const
		{
			return Util::Console::Write( str );
		}
		virtual bool WriteLine( const std::wstring &str ) const
		{
			return Util::Console::WriteLine( str );
		}
		// �R���\�[����j������
		virtual bool Delete() const
		{
			return Util::Console::Delete();
		}
	};
}
}
}
}