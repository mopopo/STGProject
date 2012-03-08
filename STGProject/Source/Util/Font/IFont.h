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
namespace Font
{
	class IFont
	{
	public:
		// �e�L�X�g�f�[�^�̕����T�C�Y�ݒ�
		virtual void SetSize( Selene::Sint32 size ) = 0;
		// �e�L�X�g�f�[�^�̃I���W�i���̕����T�C�Y�擾
		virtual Selene::Sint32 GetOriginalSize() const = 0;
		// �e�L�X�g�f�[�^�̕����T�C�Y�擾
		virtual Selene::Sint32 GetSize() const = 0;

		// �e�L�X�g�f�[�^�̕`��D��x��ݒ�
		virtual void SetPriority( Selene::Sint32 priority ) = 0;

		// �U���t���O�̎擾
		virtual bool IsShakable() const = 0;
		// �U���t���O�̐ݒ�
		virtual void SetShakable( bool shakable = true ) = 0;

		// �e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string, 
			Selene::Sint32 length = -1 ) = 0;
		// �������e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 ) = 0;
		// ���������e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 ) = 0;
		// �E�����e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 ) = 0;

		virtual ~IFont() {}
	};
}
}
}