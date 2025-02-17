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
namespace Random
{
	class IRandom
	{
	public:
		// 指定範囲内の整数乱数の取得
		virtual int GetInt( int min, int max ) = 0;
		virtual int GetInt( const boost::numeric::interval<int> &itv ) = 0;
		// 指定範囲内の浮動小数乱数の取得
		virtual float GetFloat( float min, float max ) = 0;
		virtual float GetFloat( const boost::numeric::interval<float> &itv ) = 0;
		// bool値の取得
		virtual bool GetBool() = 0;
	};
}
}
}