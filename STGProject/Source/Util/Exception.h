#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/exception/all.hpp>
#include <exception>
#include <string>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// ��{�I�ȗ�O�N���X
	class Exception
		: public std::exception
		, public boost::exception
	{
	public:
		// string�^�̃G���[���
		typedef boost::error_info<struct tag_errmsg, std::string> errmsg_info;

		// �G���[���̒ǉ�
		virtual void AddErrorInfo( const std::wstring &errInfo );

		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
		virtual std::wstring GetErrorMessageBoxInfo() const;
		// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̐ݒ�
		// �ڍׂȏ��� AddErrorInfo �Œǉ����邱��
		virtual void SetErrorMessageBoxInfo( const std::wstring &info );

		// �f�X�g���N�^
		virtual ~Exception() {}

	protected:
		std::wstring mErrMBoxInfo;
	};
}
}