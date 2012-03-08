#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"
#include <queue>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// �ŏ��ɒǉ������֐�������s���Ă���
	// �֐��̈�����0�A�߂�l��bool�łȂ���΂Ȃ�Ȃ�
	// �߂�l��false�ɂȂ�ƁA�擪�̊֐���pop�����
	class FunctionQueue
	{
	public:
		typedef Delegate::Delegate0<bool> Delegate;

		// �R���X�g���N�^
		FunctionQueue()
			: mFuncQueue()
			, mDefaultFunc()
		{}
		FunctionQueue( const std::queue<Delegate> &queue )
			: mFuncQueue( queue )
			, mDefaultFunc()
		{}

		// �擪�̊֐������s����
		void Call()
		{
			if( !IsEmpty() && 
				!mFuncQueue.front()() )
			{
				mFuncQueue.pop();
			}
			else if( IsEmpty() )
			{
				if( !mDefaultFunc.IsEmpty() && !mDefaultFunc() )
				{
					mDefaultFunc.Reset();
				}
			}
		}
		void operator () ()
		{
			Call();
		}

		// �֐��𖖔��ɒǉ�
		void Push( const Delegate &f )
		{
			mFuncQueue.push( f );
		}

		// �擪�̊֐����폜
		void Pop()
		{
			mFuncQueue.pop();
		}

		// �֐���S�폜
		void Clear()
		{
			while( !mFuncQueue.empty() )
			{
				mFuncQueue.pop();
			}
		}

		// �֐��̗L��
		bool IsEmpty() const
		{
			return mFuncQueue.empty();
		}

		// �֐��̐�
		std::queue<Delegate>::size_type GetSize() const
		{
			return mFuncQueue.size();
		}

		// ��̎��Ɏ��s����֐��̐ݒ�
		// �֐���false��Ԃ��Ɛݒ肪���������
		void SetDefaultFunction( const Delegate &func )
		{
			mDefaultFunc = func;
		}

	private:
		std::queue<Delegate> mFuncQueue;
		Delegate mDefaultFunc;
	};
}
}