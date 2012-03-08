#pragma once


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	class RepeatCounter
	{
	public:
		RepeatCounter()
			: mInterval( 1.0f )
			, mIntervalCount( 0 )
			, mRepeatCount( 0 )
		{}
		RepeatCounter( float itv )
			: mInterval( itv )
			, mIntervalCount( 0 )
			, mRepeatCount( 0 )
		{}

		// 1�t���[�����̏�ԍX�V
		void UpdateState()
		{
			mRepeatCount = 0;

			mIntervalCount += 1.0f;

			while( mIntervalCount >= mInterval )
			{
				mIntervalCount -= mInterval;

				mRepeatCount++;
			}
		}

		// �J��Ԃ��񐔂̎擾
		// ���UpdateState()���Ăяo���Ă�������
		unsigned GetRepeatCount() const
		{
			return mRepeatCount;
		}

		// ��Ԃ����Z�b�g
		void Reset()
		{
			mIntervalCount = 0;
			mRepeatCount = 0;
		}

		// �J��Ԃ��Ԋu�̎擾
		float GetInterval() const
		{
			return mInterval;
		}
		// �J��Ԃ��Ԋu�̐ݒ�
		void SetInterval( float itv )
		{
			mInterval = itv;
		}

	private:
		float mInterval;
		float mIntervalCount;
		unsigned mRepeatCount;
	};
}
}