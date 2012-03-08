#include "PCH.h"
#include "SLN.h"

using namespace Game;
using namespace Util;
using namespace Random::Impl;
using namespace Selene;
using namespace boost::numeric;


// �R���X�g���N�^
SLN::SLN( int seed )
: mRandom( seed )
{
}


// ���������̎�̐ݒ�
void SLN::SetSeed( int seed )
{
	mRandom.Seed( seed );
}


// �w��͈͓��̐��������̎擾
int SLN::GetInt( int min, int max )
{
	return mRandom.GetInt( min, max );
}

int SLN::GetInt( const interval<int> &itv )
{
	return mRandom.GetInt( itv.lower(), itv.upper() );
}

// �w��͈͓��̕������������̎擾
float SLN::GetFloat( float min, float max )
{
	return mRandom.GetFloat( min, max );
}

float SLN::GetFloat( const interval<float> &itv )
{
	return mRandom.GetFloat( itv.lower(), itv.upper() );
}

// bool�l�̎擾
bool SLN::GetBool()
{
	return GetInt( 0, 1 ) != 0;
}