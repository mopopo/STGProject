#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>
#include "Util/Exception.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sound
{
namespace Exception
{
	// �T�E���h�̃C���X�^���X�̐����Ɏ��s����
	class Invalid
		: public Exception
	{
	public:
		// �R���X�g���N�^
		Invalid( const std::wstring &name )
		{
			Exception::AddErrorInfo( L"\n�T�E���h \"" + 
				name + 
				L"\" �̐����Ɏ��s���܂���\n" );
		}

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"InvalidSoundException";
		}
	};
}
}
}
}