#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <boost/noncopyable.hpp>
#include "../IDynamicFile.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace File
{
namespace Detail
{
	class DynamicFile
		: public IDynamicFile
		, public boost::noncopyable
	{
	public:
		// �R���X�g���N�^
		DynamicFile( ::HMODULE hCryptModule );
		DynamicFile( ::HMODULE hCryptModule, PFile pFile );

		// �ǂݎ��p�̃C�e���[�^�̎擾
		virtual Iterator GetBegin() const;
		virtual Iterator GetEnd() const;
		// �T�C�Y�̎擾
		virtual Size GetSize() const;
		// �C�ӂ̏ꏊ�ɏ�������
		virtual void Write( unsigned char value, Size offset = 0 );
		virtual void Write( const unsigned char *pData, Size size, Size offset = 0 );

		// ���e�ɑ΂���xor���Z������
		virtual void Xor( unsigned value );
		// ������̃n�b�V���l��xor���Z������
		virtual void Xor( const std::string &str );
		// Selene�t����CryptPlugin�ňÍ�������
		virtual void Encrypt( const std::string &pass );
		// Selene�t����CryptPlugin�ŕ���������
		virtual void Decrypt( const std::string &pass );

		// �R�s�[���쐬����
		virtual PDynamicFile CreateClone() const;
		// Selene�̃t�@�C���C���^�[�t�F�C�X���쐬����
		virtual PFile CreateSLNFile( const std::wstring &name ) const;

	private:
		Container mContainer;
		::HMODULE mhCryptModule;
		Selene::Plugin::File::CreateCryptInterfaceProc mCreateCryptInterface;
		typedef Ptr<Selene::Plugin::File::ICrypt>::Intrusive PCrypt;
		typedef std::map<std::string, PCrypt> CryptMap;
		CryptMap mCryptMap;

		void Init();

		PCrypt GetCrypt( const std::string &pass );
	};
}
}
}
}