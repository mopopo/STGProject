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
	// 画像の情報
	// 生成時や描画時に使用
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