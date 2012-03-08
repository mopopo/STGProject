#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Font/IFont.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Font
{
namespace Detail
{
	class SLNFont
		: public IFont
	{
	public:
		// �R���X�g���N�^
		SLNFont( PSLNFont pFont );

		// �e�L�X�g�f�[�^�̕����T�C�Y�ݒ�
		virtual void SetSize( Selene::Sint32 size );
		// �e�L�X�g�f�[�^�̃I���W�i���̕����T�C�Y�擾
		virtual Selene::Sint32 GetOriginalSize() const;
		// �e�L�X�g�f�[�^�̕����T�C�Y�擾
		virtual Selene::Sint32 GetSize() const;

		// �e�L�X�g�f�[�^�̕`��D��x��ݒ�
		virtual void SetPriority( Selene::Sint32 priority );

		// �U���t���O�̎擾
		virtual bool IsShakable() const;
		// �U���t���O�̐ݒ�
		virtual void SetShakable( bool shakable = true );

		// �e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string, 
			Selene::Sint32 length = -1 );
		// �������e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 );
		// ���������e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 );
		// �E�����e�L�X�g�f�[�^�̕����`��
		virtual Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length = -1 );

	private:
		PSLNFont mpFont;
		bool mShakable;
	};
}
}
}
}