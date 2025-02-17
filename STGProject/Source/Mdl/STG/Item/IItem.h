#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Actor/IActor.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Item
{
	class IItem
		: virtual public Actor::IActor
	{
	public:
		// 自機ヘの当たり判定の半径の取得
		virtual float GetHitRadius() const = 0;
		// 当たり判定
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const = 0;

		virtual ~IItem() {}
	};
}
}
}
}