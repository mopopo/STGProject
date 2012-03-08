#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>
#include <boost/lexical_cast.hpp>
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
	// ������StaticSound�̃��C���[�ԍ����w�肵��
	class InvalidLayer
		: public Exception
	{
	public:
		// �R���X�g���N�^
		InvalidLayer( const std::wstring &name, Selene::Uint32 layer )
		{
			Exception::AddErrorInfo( L"\nStaticSound \"" + 
				name + 
				L"\" �̃��C���[ \"" + 
				boost::lexical_cast<std::wstring>( layer ) + 
				L"\" �͖����ł�\n" );
		}

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo()
		{
			return L"InvalidSoundLayerException";
		}
	};
}
}
}
}