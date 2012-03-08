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
namespace Sprite
{
namespace Exception
{
	// �e�N�X�`���̃C���X�^���X�̐����Ɏ��s����
	class InvalidTexture
		: public Exception
	{
	public:
		// �R���X�g���N�^
		InvalidTexture( const std::wstring &name )
		{
			Exception::AddErrorInfo( L"\n�e�N�X�`�� \"" + 
				name + 
				L"\" �̐����Ɏ��s���܂���\n" );
		}
		InvalidTexture( const std::list<std::wstring> &names )
		{
			std::wstring info = L"\n�e�N�X�`��\n";

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
			return L"InvalidTextureException";
		}
	};
}
}
}
}