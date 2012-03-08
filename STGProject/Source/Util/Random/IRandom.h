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
		// �w��͈͓��̐��������̎擾
		virtual int GetInt( int min, int max ) = 0;
		virtual int GetInt( const boost::numeric::interval<int> &itv ) = 0;
		// �w��͈͓��̕������������̎擾
		virtual float GetFloat( float min, float max ) = 0;
		virtual float GetFloat( const boost::numeric::interval<float> &itv ) = 0;
		// bool�l�̎擾
		virtual bool GetBool() = 0;
	};
}
}
}