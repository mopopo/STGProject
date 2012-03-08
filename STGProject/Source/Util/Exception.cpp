#include "PCH.h"
#include "Exception.h"

using namespace Game;
using namespace std;


// �G���[���̒ǉ�
void Util::Exception::AddErrorInfo( const wstring &errInfo )
{
	*this << errmsg_info( 
		"\n\n--- Error Infomation ---\n" + Util::ToMultiByte( errInfo ) );
}


// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̎擾
wstring Util::Exception::GetErrorMessageBoxInfo() const
{
	return mErrMBoxInfo;
}

// �G���[���b�Z�[�W�{�b�N�X�ŕ\�����镶����̐ݒ�
void Util::Exception::SetErrorMessageBoxInfo( const wstring &info )
{
	mErrMBoxInfo = info;
}