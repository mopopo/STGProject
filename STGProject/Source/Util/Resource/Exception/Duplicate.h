#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Exception.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Resource
{
namespace Exception
{
	// ���\�[�X��ǉ����悤�Ƃ����Ƃ��ɁA���łɓ������O�̃��\�[�X�����݂��Ă���
	class Duplicate
		: public Exception
	{
	public:
		// �R���X�g���N�^
		Duplicate( const std::wstring &resourceName )
		{
			Exception::AddErrorInfo( std::wstring( L"���\�[�X \"" ) + 
				resourceName + 
				std::wstring( L"\" �͊��ɑ��݂��܂�" ) );
		}

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"ResourceDuplicateException";
		}
	};
}
}
}
}