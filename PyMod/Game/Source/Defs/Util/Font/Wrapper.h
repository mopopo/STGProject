#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Font/IFont.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Font
{
	class Wrapper
	{
	public:
		Wrapper( Game::Util::Font::PFont p )
			: mpFont( p )
		{}

		// �e�L�X�g�f�[�^�̕����T�C�Y�ݒ�
		void SetSize( Selene::Sint32 size )
		{
			mpFont->SetSize( size );
		}
		// �e�L�X�g�f�[�^�̃I���W�i���̕����T�C�Y�擾
		Selene::Sint32 GetOriginalSize() const
		{
			return mpFont->GetOriginalSize();
		}
		// �e�L�X�g�f�[�^�̕����T�C�Y�擾
		Selene::Sint32 GetSize() const
		{
			return mpFont->GetSize();
		}

		// �e�L�X�g�f�[�^�̕`��D��x��ݒ�
		void SetPriority( Selene::Sint32 priority )
		{
			mpFont->SetPriority( priority );
		}

		// �U���t���O�̎擾
		bool IsShakable() const
		{
			return mpFont->IsShakable();
		}
		// �U���t���O�̐ݒ�
		void SetShakable( bool shakable )
		{
			return mpFont->SetShakable( shakable );
		}

		// �e�L�X�g�f�[�^�̕����`��
		Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string )
		{
			return mpFont->Draw( position, color, string, -1 );
		}
		Selene::Point2DF Draw( const Selene::Point2DF &position, 
			const Selene::ColorF &color, const std::wstring &string, 
			Selene::Sint32 length )
		{
			return mpFont->Draw( position, color, string, length );
		}
		// �������e�L�X�g�f�[�^�̕����`��
		Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string )
		{
			return mpFont->DrawLeft( rect, offset, color, string, -1 );
		}
		Selene::Point2DF DrawLeft( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length )
		{
			return mpFont->DrawLeft( rect, offset, color, string, length );
		}
		// ���������e�L�X�g�f�[�^�̕����`��
		Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string )
		{
			return mpFont->DrawCenter( rect, offset, color, string, -1 );
		}
		Selene::Point2DF DrawCenter( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length )
		{
			return mpFont->DrawCenter( rect, offset, color, string, length );
		}
		// �E�����e�L�X�g�f�[�^�̕����`��
		Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string )
		{
			return mpFont->DrawRight( rect, offset, color, string, -1 );
		}
		Selene::Point2DF DrawRight( const Selene::RectF &rect, 
			const Selene::Point2DF &offset, const Selene::ColorF &color, 
			const std::wstring &string, Selene::Sint32 length )
		{
			return mpFont->DrawRight( rect, offset, color, string, length );
		}

	private:
		Game::Util::Font::PFont mpFont;
	};
}
}
}