#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <stdint.h>
#include "Fwd.h"
#include "FileObject.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace File
{
	class File
	{
	public:
		static void Configurate();

		static void _setInstance( uintptr_t p );

		// 1�̃t�@�C����ǂݍ���
		static boost::python::object open( const std::wstring &filePath );
		static boost::python::object open( const std::wstring &filePath, 
			bool cache );
		static boost::python::object open( const std::wstring &filePath, 
			bool cache, bool throwException );
		// 1�̃t�@�C����񓯊��œǂݍ���
		static boost::python::object openASync( const std::wstring &filePath );
		static boost::python::object openASync( const std::wstring &filePath, 
			bool cache );
		static boost::python::object openASync( const std::wstring &filePath, 
			bool cache, bool throwException );

		// �L���b�V���T�C�Y�̎擾
		static unsigned getCacheSize();
		// �ő�L���b�V���T�C�Y�̎擾
		static unsigned getMaxCacheSize();
		// �ő�L���b�V���T�C�Y�̐ݒ�
		static void setMaxCacheSize( unsigned size );

		// �L���b�V���̏���
		static void eraseCache( const std::wstring &path );
		// �L���b�V���̑S�N���A
		static void clearCache();
	};
}
}
}