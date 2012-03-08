#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Random/IRandom.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Random
{
namespace Impl
{
	class SLN
		: public IRandom
	{
	public:
		// �R���X�g���N�^
		SLN( int seed = 0 );

		// ���������̎�̐ݒ�
		void SetSeed( int seed );

		// �w��͈͓��̐��������̎擾
		virtual int GetInt( int min, int max );
		virtual int GetInt( const boost::numeric::interval<int> &itv );
		// �w��͈͓��̕������������̎擾
		virtual float GetFloat( float min, float max );
		virtual float GetFloat( const boost::numeric::interval<float> &itv );
		// bool�l�̎擾
		virtual bool GetBool();

	private:
		Selene::Kernel::Math::Random mRandom;
	};
}
}
}
}