#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <string>
#include <Selene.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sprite
{
	// �摜�̏��
	// ��������`�掞�Ɏg�p
	class SrcDef
	{
	public:
		const std::wstring &GetName() const
		{
			return mName;
		}

		const Selene::RectF &GetRect() const
		{
			return mRect;
		}

		SrcDef( const std::wstring &name, 
			float upperLeftX, float upperLeftY, float width, float height )
			: mName( name )
			, mRect( upperLeftX, upperLeftY, width, height )
		{}

	private:
		const std::wstring mName;
		const Selene::RectF mRect;
	};
}
}
}