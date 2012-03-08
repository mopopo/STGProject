#include "PCH.h"
#include "Manager.h"
#include "Detail/Cache.h"
#include "Detail/DynamicFile.h"

using namespace Game;
using namespace Game::Util::File;
using namespace Selene;
using namespace boost;
using namespace std;

namespace
{
	static const wchar_t CRYPT_PLUGIN_PATH[] = L"Plugin/File/Crypt.dll";

	// Selene�t���̈Í����v���O�C��
	static ::HMODULE mhCryptModule = NULL;
}


// 1�̃t�@�C����ǂݍ���
PFile Manager::Open( const wstring &filePath, bool cache, bool throwException )
{
	if( cache )
	{
		PFile pFile = Detail::Cache::Get( filePath );

		if( pFile )
		{
			return pFile;
		}
	}
	else
	{
		Detail::Cache::Erase( filePath );
	}

	Core::PFileManager pFManager = Core::Manager::GetFileManager();

	PFile pFile = 
		MakeIntrusivePtr( pFManager->OpenSyncFile( filePath.c_str() ) );

	if( throwException && !pFile )
	{
		THROW( Exception::NotFound( filePath ) );
	}

	if( cache )
	{
		Detail::Cache::Put( filePath, pFile );
	}

	return pFile;
}

// 1�̃t�@�C����񓯊��œǂݍ���
PFile Manager::OpenASync( const wstring &filePath, bool cache, bool throwException )
{
	if( cache )
	{
		PFile pFile = Detail::Cache::Get( filePath );

		if( pFile )
		{
			return pFile;
		}
	}
	else
	{
		Detail::Cache::Erase( filePath );
	}

	Core::PFileManager pFManager = Core::Manager::GetFileManager();

	PFile pFile = 
		MakeIntrusivePtr( pFManager->OpenASyncFile( filePath.c_str() ) );

	if( throwException && !pFile )
	{
		THROW( Exception::NotFound( filePath ) );
	}

	if( cache )
	{
		Detail::Cache::Put( filePath, pFile );
	}

	return pFile;
}

// filePathList�ɂ���t�@�C������x�ɂ��ׂēǂݍ���
void Manager::Open( const vector<wstring> &filePathList, FileMap &files, 
				   bool cache, bool throwException )
{
	Core::PFileManager pFManager = Core::Manager::GetFileManager();
	list<wstring> notOpenedFileList;

	files.clear();

	foreach( const wstring &filePath, filePathList )
	{
		if( cache )
		{
			PFile pFile = Detail::Cache::Get( filePath );

			if( pFile )
			{
				files[ filePath ] = pFile;
				continue;
			}
		}
		else
		{
			Detail::Cache::Erase( filePath );
		}

		PFile pFile = 
			MakeIntrusivePtr( pFManager->OpenSyncFile( filePath.c_str() ) );

		if( throwException && !pFile )
		{
			notOpenedFileList.push_back( filePath );
		}
		else if( pFile )
		{
			files[ filePath ] = pFile;

			if( cache )
			{
				Detail::Cache::Put( filePath, pFile );
			}
		}
	}

	if( throwException && !notOpenedFileList.empty() )
	{
		THROW( Exception::NotFound( notOpenedFileList ) );
	}
}


// �p�b�N�t�@�C���̃C���^�[�t�F�C�X�𐶐�
PPackFile Manager::CreatePackFile( PFile pFile )
{
	return MakeIntrusivePtr( 
		Core::Manager::GetFileManager()->CreatePackFile( pFile.get() ) );
}


// DynamicFile�̍쐬
Util::Ptr<IDynamicFile>::Shared Manager::CreateDynamicFile()
{
	return Ptr<IDynamicFile>::Shared( 
		new Detail::DynamicFile( mhCryptModule ) );
}

Util::Ptr<IDynamicFile>::Shared Manager::CreateDynamicFile( PFile pFile )
{
	return Ptr<IDynamicFile>::Shared( 
		new Detail::DynamicFile( mhCryptModule, pFile ) );
}


// �t�@�C���̏�������
namespace
{
	static void CreateDirectories( const boost::filesystem::path &dirPath )
	{
		namespace fs = boost::filesystem;
		if( !fs::exists( dirPath ) )
		{
			fs::create_directories( dirPath );
		}
		else if( !fs::is_directory( dirPath ) )
		{
			fs::remove( dirPath );
			fs::create_directories( dirPath );
		}
	}
}
bool Manager::Write( const wstring &dirPath, const wstring &fileName, PFile pFile )
{
	namespace fs = boost::filesystem;
	fs::path dPath( dirPath );
	CreateDirectories( dPath );

	fs::ofstream out( dPath/fileName, ios::out | ios::trunc | ios::binary );

	if( out.is_open() )
	{
		out.write( static_cast<const char *>( pFile->GetData() ), pFile->GetSize() );

		out.close();

		return true;
	}

	return false;
}

bool Manager::Write( const wstring &dirPath, const wstring &fileName, 
					Util::Ptr<IDynamicFile>::Shared pDynamicFile )
{
	namespace fs = boost::filesystem;
	fs::path dPath( dirPath );
	CreateDirectories( dPath );

	fs::ofstream out( dPath/fileName, ios::out | ios::trunc | ios::binary );

	if( out.is_open() )
	{
		for( IDynamicFile::Iterator itr = pDynamicFile->GetBegin(); 
			itr != pDynamicFile->GetEnd(); 
			itr++ )
		{
			out.write( reinterpret_cast<const char *>( &*itr ), sizeof( unsigned char ) );
		}

		out.close();

		return true;
	}

	return false;
}


// �w�肵���p�X��������Ȃ���΁A�p�X�̐擪��"../"��ǉ�����
wstring Manager::ConvertPath( const wstring &pathStr )
{
	namespace fs = boost::filesystem;

	if( fs::exists( fs::path( pathStr ) ) )
	{
		return pathStr;
	}
	else if( fs::exists( fs::path( L"../" + pathStr ) ) )
	{
		return L"../" + pathStr;
	}
	else
	{
		list<wstring> pathList;
		pathList.push_back( pathStr );
		pathList.push_back( L"../" + pathStr );

		THROW( Exception::NotFound( pathList ) );
	}

	return wstring();
}


// �L���b�V���T�C�Y�̎擾
unsigned Manager::GetCacheSize()
{
	return Detail::Cache::GetSize();
}

// �ő�L���b�V���T�C�Y�̎擾
unsigned Manager::GetMaxCacheSize()
{
	return Detail::Cache::GetMaxSize();
}

// �ő�L���b�V���T�C�Y�̐ݒ�
void Manager::SetMaxCacheSize( unsigned size )
{
	Detail::Cache::SetMaxSize( size );
}


// �L���b�V���̏���
void Manager::EraseCache( const wstring &path )
{
	Detail::Cache::Erase( path );
}

// �L���b�V���̑S�N���A
void Manager::ClearCache()
{
	Detail::Cache::Clear();
}


// ����������
void Manager::Initialize()
{
	// �Í������p�v���O�C��
	//		�t�@�C�����Í������ăp�b�N���Ă���ꍇ��
	//		�Í������ɗ��p����v���O�C���Ɖ����p�̃p�X���[�h���w��
	//		�Í����̓f�[�^�̒��g���B���ړI�Ƃ��Ă͗L�p����
	//		���R�ǂݍ��ݑ��x���]���ɂ���̂Ŏg���ǂ���ɒ��ӁB
	Core::Manager::GetFileManager()->SetCryptPlugin( 
		CRYPT_PLUGIN_PATH, Consts::File::CRYPT_PASS );

	{
		namespace py = boost::python;

		py::object config = py::import( "Config" );
		py::list pathList( config.attr( "filePathList" ) );
		vector<wstring> pathStrVector;
		for( int i = 0; i < py::len( pathList ); i++ )
		{
			pathStrVector.push_back( 
				py::extract<wstring>( pathList[ i ] ) );
		}

		size_t size = pathStrVector.size();
		scoped_array<const wchar_t *> pathStrArray( 
			new const wchar_t *[ size + 1 ] );
		for( size_t i = 0; i < size; i++ )
		{
			pathStrArray[ i ] = pathStrVector[ i ].c_str();
		}
		pathStrArray[ size ] = NULL;

		Core::Manager::GetFileManager()->UpdateRootPath( 
			pathStrArray.get() );
	}

	mhCryptModule = ::LoadLibrary( CRYPT_PLUGIN_PATH );
	if( mhCryptModule == NULL )
	{
		THROW( Exception::NotFound( CRYPT_PLUGIN_PATH ) );
	}
}

// ��n������
void Manager::Release()
{
	Detail::Cache::Clear();

	::FreeLibrary( mhCryptModule );
	mhCryptModule = NULL;
}