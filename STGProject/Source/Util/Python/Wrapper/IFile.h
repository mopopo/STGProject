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
	class IFile
	{
	public:
		// 1�̃t�@�C����ǂݍ���
		virtual File::PFile Open( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const = 0;
		// 1�̃t�@�C����񓯊��œǂݍ���
		virtual File::PFile OpenASync( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const = 0;

		// �L���b�V���T�C�Y�̎擾
		virtual unsigned GetCacheSize() const = 0;
		// �ő�L���b�V���T�C�Y�̎擾
		virtual unsigned GetMaxCacheSize() const = 0;
		// �ő�L���b�V���T�C�Y�̐ݒ�
		virtual void SetMaxCacheSize( unsigned size ) const = 0;

		// �L���b�V���̏���
		virtual void EraseCache( const std::wstring &path ) const = 0;
		// �L���b�V���̑S�N���A
		virtual void ClearCache() const = 0;

		virtual ~IFile() {}
	};
}
}
}
}