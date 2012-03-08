#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Common.h"
#include "Util/Exception.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Font
{
namespace Exception
{
	// �t�H���g�̃C���X�^���X�̐����Ɏ��s����
	class Invalid
		: public Exception
	{
	public:
		// �R���X�g���N�^
		Invalid( const std::wstring &name )
		{
			Exception::AddErrorInfo( L"\n�t�H���g \"" + 
				name + 
				L"\" �̐����Ɏ��s���܂���\n" );
		}
		Invalid( const std::list<std::wstring> &names )
		{
			std::wstring info = L"\n�t�H���g\n";

			foreach( const std::wstring &name, names )
			{
				info += L"\t\"" + name + L"\"\n";
			}

			info += L"�̐����Ɏ��s���܂���\n";

			Exception::AddErrorInfo( info );
		}

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"InvalidFontException";
		}
	};
}
}
}
}