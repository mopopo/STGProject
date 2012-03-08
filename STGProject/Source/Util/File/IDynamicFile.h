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
	class IDynamicFile
	{
	public:
		typedef std::vector<unsigned char> Container;
		typedef Container::const_iterator Iterator;
		typedef Container::size_type Size;

		// �ǂݎ��p�̃C�e���[�^�̎擾
		virtual Iterator GetBegin() const = 0;
		virtual Iterator GetEnd() const = 0;
		// �T�C�Y�̎擾
		virtual Size GetSize() const = 0;
		// �C�ӂ̏ꏊ�ɏ�������
		virtual void Write( unsigned char value, Size offset = 0 ) = 0;
		virtual void Write( const unsigned char *pData, Size size, Size offset = 0 ) = 0;

		// ���e�ɑ΂���xor���Z������
		virtual void Xor( unsigned value ) = 0;
		// ������̃n�b�V���l��xor���Z������
		virtual void Xor( const std::string &str ) = 0;
		// Selene�t����CryptPlugin�ňÍ�������
		virtual void Encrypt( const std::string &pass ) = 0;
		// Selene�t����CryptPlugin�ŕ���������
		virtual void Decrypt( const std::string &pass ) = 0;

		// �R�s�[���쐬����
		typedef Ptr<IDynamicFile>::Shared PDynamicFile;
		virtual PDynamicFile CreateClone() const = 0;
		// Selene�̃t�@�C���C���^�[�t�F�C�X���쐬����
		virtual PFile CreateSLNFile( const std::wstring &name ) const = 0;

		// �f�X�g���N�^
		virtual ~IDynamicFile() {}
	};
}
}
}