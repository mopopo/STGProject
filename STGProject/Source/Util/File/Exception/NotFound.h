#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Exception.h"
#include "Util/Common.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
namespace Exception
{
	// �J�����Ƃ����t�@�C�������݂��Ȃ�
	class NotFound
		: public Exception
	{
	public:
		// �R���X�g���N�^
		NotFound( const std::wstring &filePath )
		{
			Exception::AddErrorInfo( L"\n�t�@�C�� \"" + 
				filePath + 
				L"\" ���J���܂���ł���\n" );
		}
		NotFound( const std::list<std::wstring> &filePathList )
		{
			std::wstring info = L"\n�t�@�C��\n";

			foreach( const std::wstring &path, filePathList )
			{
				info += L"\t\"" + path + L"\"\n";
			}

			info += L"���J���܂���ł���\n";

			Exception::AddErrorInfo( info );
		}

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"FileNotFoundException";
		}
	};
}
}
}
}