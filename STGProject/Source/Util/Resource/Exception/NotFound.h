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
	// �擾���悤�Ƃ������\�[�X��������Ȃ�����
	class NotFound
		: public Exception
	{
	public:
		// �R���X�g���N�^
		NotFound( const std::wstring &resourceName )
		{
			Exception::AddErrorInfo( std::wstring( L"���\�[�X \"" ) + 
				resourceName + 
				std::wstring( L"\" �͌�����܂���ł���" ) );
		}

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"ResourceNotFoundException";
		}
	};
}
}
}
}