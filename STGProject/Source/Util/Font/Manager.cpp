#include "PCH.h"
#include "Manager.h"
#include "Detail/SLNFont.h"
#include "Detail/TextureLoader.h"
#include "IFont.h"

using namespace Game;
using namespace Util::Font;
using namespace Selene;
using namespace std;
using namespace Util::Consts::Font;

namespace
{
	// �e�N�X�`���p�p�����[�^�[
	static const Engine::Graphics::STextureLoadParameter LOAD_PARAM = { true };

	// �t�H���g���\�[�X�ǂݍ��ݗp�p�X�̎擾
	static wstring GetResourcePath( const wstring &fontFilePath )
	{
		// fontFilePath��'/'��'\'�ŕ���
		vector<wstring> fontPathTokenList;
		Util::Tokenize( fontFilePath, L"/\\", fontPathTokenList );

		wstring resourcePath;
		for( auto itr = fontPathTokenList.begin(); 
			itr != fontPathTokenList.end() - 1; 
			itr++ )
		{
			resourcePath += *itr + L"/";
		}

		return resourcePath;
	}
}


// �t�H���g�f�[�^�̓ǂݍ���
PFont Manager::LoadFont( const wstring &fontFilePath )
{
	wstring resourcePath = GetResourcePath( fontFilePath );
	File::PFile pResourceFile;
	pair<wstring, File::PFile *> resourcePair( resourcePath, &pResourceFile );

	File::PFile pFontFile = File::Manager::Open( LOAD_TOP_PATH + fontFilePath );

	Detail::TextureLoader loader;
	Detail::PSLNFont pSLNFont = MakeIntrusivePtr( 
		Core::Manager::GetGraphicsManager()->CreateText(
			pFontFile->GetData(),		// �t�@�C���f�[�^
			pFontFile->GetSize(),		// �t�@�C���T�C�Y
			pFontFile->GetFileName(),	// �t�@�C����
			LOAD_PARAM,					// �e�N�X�`�������p�p�����[�^�[
			&loader,					// ���\�[�X�ǂݍ��ݗp���X�i�[
			&resourcePair ) );			// ���[�U�[�f�[�^�iResource::IFileLoadListener��pUserSetData�����j

	if( !pSLNFont )
	{
		THROW( Exception::Invalid( fontFilePath ) );
	}
	else
	{
		pSLNFont->SetDrawSprite( Core::Manager::GetSpriteRenderer().get() );
		pSLNFont->SetScissorRect( RectI( 0, 0, Consts::SCREEN_SIZE.x, Consts::SCREEN_SIZE.y ) );
	}

	return PFont( new Detail::SLNFont( pSLNFont ) );
}

void Manager::LoadFont( const vector<wstring> &fontFilePathList, FontMap &fonts )
{
	fonts.clear();

	list<wstring> invalidFontList;
	Detail::TextureLoader loader;

	File::FileMap fontFiles;
	vector<wstring> pathList;
	foreach( const wstring &path, fontFilePathList )
	{
		pathList.push_back( LOAD_TOP_PATH + path );
	}
	File::Manager::Open( pathList, fontFiles );

	foreach( const File::FileMapElemType &fontPair, fontFiles )
	{
		wstring resourcePath = GetResourcePath( fontPair.first );
		File::PFile pResourceFile;
		pair<wstring, File::PFile *> resourcePair( resourcePath, &pResourceFile );

		Detail::PSLNFont pSLNFont = MakeIntrusivePtr( 
			Core::Manager::GetGraphicsManager()->CreateText(
				fontPair.second->GetData(),		// �t�@�C���f�[�^
				fontPair.second->GetSize(),		// �t�@�C���T�C�Y
				fontPair.second->GetFileName(),	// �t�@�C����
				LOAD_PARAM,						// �e�N�X�`�������p�p�����[�^�[
				&loader,						// ���\�[�X�ǂݍ��ݗp���X�i�[
				&resourcePair ) );				// ���[�U�[�f�[�^�iResource::IFileLoadListener��pUserSetData�����j

		if( !pSLNFont )
		{
			invalidFontList.push_back( fontPair.first );
		}
		else
		{
			pSLNFont->SetDrawSprite( Core::Manager::GetSpriteRenderer().get() );
			pSLNFont->SetScissorRect( 
				RectI( 0, 0, Consts::SCREEN_SIZE.x, Consts::SCREEN_SIZE.y ) );

			fonts[ fontPair.first ] = PFont( new Detail::SLNFont( pSLNFont ) );
		}
	}

	if( !invalidFontList.empty() )
	{
		THROW( Exception::Invalid( invalidFontList ) );
	}
}