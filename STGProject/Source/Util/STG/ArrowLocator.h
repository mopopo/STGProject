#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/RepeatCounter.h"
#include <boost/numeric/interval.hpp>
#include "Util/STG/Vector2D.h"
#include <boost/python.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
	class ArrowLocator
	{
	public:
		// �R���X�g���N�^
		typedef Ptr<Input::STG::IController>::Shared PController;
		ArrowLocator( PController pController, int initArrowPos, 
			int top, int bottom, bool loop = true, bool horizontal = false );

		// 1�t���[�����̏�ԍX�V
		void UpdateState();

		// �ʒu�̎擾
		int GetPosition() const;
		// �ʒu�̐ݒ�
		void SetPosition( int pos );

		// ����Ɖ����̐ݒ�
		void SetInterval( int top, int bottom );
		// ����Ɖ����̎擾
		const boost::numeric::interval<int> &GetInterval() const;

		// ������A�����E�̓��͂Ƃ���
		bool GetHorizontal() const;
		void SetHorizontal( bool flag = false );

		// ���s�[�g�҂��Ԋu�̎擾
		float GetRepeatWait() const;
		// ���s�[�g�҂��Ԋu�̐ݒ�
		void SetRepeatWait( float wait = 20.0f );
		// ���s�[�g�Ԋu�̎擾
		float GetRepeatInterval() const;
		// ���s�[�g�Ԋu�̐ݒ�
		void SetRepeatInterval( float itv = 6.0f );

		// ���̓R���g���[���[�̎擾
		PController GetController() const;
		// ���̓R���g���[���[�̐ݒ�
		void SetController( PController pController );

		// �ړ��R�[���o�b�N�̐ݒ�
		void SetMoveCallback( const boost::python::object &callback );

	private:
		// ���̈ʒu
		int mArrowPos;
		// ���s�[�g�Ԋu
		Util::RepeatCounter mArwMovRepCnt1;
		Util::RepeatCounter mArwMovRepCnt2;
		bool mRep2Flag;
		// ����Ɖ���
		boost::numeric::interval<int> mPosItv;
		// ���̈ړ�
		void MoveUp();
		void MoveDown();
		// �ړ��R�[���o�b�N
		boost::python::object mMoveCallback;

		// ���͂��Ă������
		Vector2DF mPrevDir, mDir;
		void UpdateDirection();
		bool mLoopFlag;
		bool mHorizontalFlag;
		bool IsPushUp() const;
		bool IsPushDown() const;
		bool IsHoldUp() const;
		bool IsHoldDown() const;

		// ���̓R���g���[���[
		PController mpController;
	};
}
}
}