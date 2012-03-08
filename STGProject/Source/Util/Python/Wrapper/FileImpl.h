#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/intrusive_ptr.hpp>
#include "IFile.h"
#include "Util/File/Manager.h"


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
	class FileImpl
		: public IFile
	{
	public:
		// 1�̃t�@�C����ǂݍ���
		virtual File::PFile Open( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const
		{
			return File::Manager::Open( filePath, cache, throwException );
		}
		// 1�̃t�@�C����񓯊��œǂݍ���
		virtual File::PFile OpenASync( const std::wstring &filePath, 
			bool cache = true, bool throwException = true ) const
		{
			return File::Manager::OpenASync( filePath, cache, throwException );
		}

		// �L���b�V���T�C�Y�̎擾
		virtual unsigned GetCacheSize() const
		{
			return File::Manager::GetCacheSize();
		}
		// �ő�L���b�V���T�C�Y�̎擾
		virtual unsigned GetMaxCacheSize() const
		{
			return File::Manager::GetMaxCacheSize();
		}
		// �ő�L���b�V���T�C�Y�̐ݒ�
		virtual void SetMaxCacheSize( unsigned size ) const
		{
			File::Manager::SetMaxCacheSize( size );
		}

		// �L���b�V���̏���
		virtual void EraseCache( const std::wstring &path ) const
		{
			File::Manager::EraseCache( path );
		}
		// �L���b�V���̑S�N���A
		virtual void ClearCache() const
		{
			File::Manager::ClearCache();
		}
	};
}
}
}
}