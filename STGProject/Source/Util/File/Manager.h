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
namespace File
{
	// �t�@�C���Ɋւ��鏈��
	class Manager
	{
	public:
		// 1�̃t�@�C����ǂݍ���
		static PFile Open( const std::wstring &filePath, 
			bool cache = true, bool throwException = true );
		// 1�̃t�@�C����񓯊��œǂݍ���
		static PFile OpenASync( const std::wstring &filePath, 
			bool cache = true, bool throwException = true );
		// filePathList�ɂ���t�@�C������x�ɂ��ׂēǂݍ���
		static void Open( const std::vector<std::wstring> &filePathList, 
			FileMap &files, bool cache = true, bool throwException = true );

		// �p�b�N�t�@�C���̃C���^�[�t�F�C�X�𐶐�
		static PPackFile CreatePackFile( PFile pFile );

		// DynamicFile�̍쐬
		static Ptr<IDynamicFile>::Shared CreateDynamicFile();
		static Ptr<IDynamicFile>::Shared CreateDynamicFile( PFile pFile );

		// �t�@�C���̏�������
		// dirPath�����݂��Ȃ���΍쐬����
		// dirPath���f�B���N�g���łȂ�������A�폜���ăf�B���N�g�����쐬����
		static bool Write( const std::wstring &dirPath, const std::wstring &fileName, 
			PFile pFile );
		static bool Write( const std::wstring &dirPath, const std::wstring &fileName, 
			Ptr<IDynamicFile>::Shared pDynamicFile );

		// �w�肵���p�X��������Ȃ���΁A�p�X�̐擪��"../"��ǉ�����
		static std::wstring ConvertPath( const std::wstring &pathStr );

		// �L���b�V���T�C�Y�̎擾
		static unsigned GetCacheSize();
		// �ő�L���b�V���T�C�Y�̎擾
		static unsigned GetMaxCacheSize();
		// �ő�L���b�V���T�C�Y�̐ݒ�
		static void SetMaxCacheSize( unsigned size );

		// �L���b�V���̏���
		static void EraseCache( const std::wstring &path );
		// �L���b�V���̑S�N���A
		static void ClearCache();

		// ����������
		static void Initialize();
		// ��n������
		static void Release();
	};
}
}
}