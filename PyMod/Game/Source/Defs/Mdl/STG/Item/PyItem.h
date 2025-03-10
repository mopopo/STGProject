#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Mdl/STG/Item/IItem.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Item
{
#pragma warning( disable:4250 )
	class PyItem
		: public Actor::PyActor
		, public Game::Mdl::STG::Item::IItem
	{
	public:
		PyItem( const boost::python::object &object )
			: PyActor( object )
		{}

		// 自機ヘの当たり判定の半径の取得
		virtual float GetHitRadius() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hitRadius" ) );
		}

		// 当たり判定
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit" ) );
		}
	};
}
}
}
}