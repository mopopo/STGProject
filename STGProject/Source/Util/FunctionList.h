#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Delegate/Delegate.h"
#include <list>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	// �ǉ������֐������ׂĎ��s����
	// �֐��̈�����0�A�߂�l��bool�łȂ���΂Ȃ�Ȃ�
	// �߂�l��false�ɂȂ�ƁA���̊֐���pop�����
	class FunctionList
	{
	public:
		typedef Delegate::Delegate0<bool> Delegate;

		// �R���X�g���N�^
		FunctionList()
			: mFuncList()
			, mDefaultFunc()
		{}
		FunctionList( const std::list<Delegate> &list )
			: mFuncList( list )
			, mDefaultFunc()
		{}

		// �֐������s����
		void Call()
		{
			if( !IsEmpty() )
			{
				for( std::list<Delegate>::iterator itr = mFuncList.begin(); 
					itr != mFuncList.end(); )
				{
					if( !itr->Call() )
					{
						mFuncList.erase( itr++ );
					}
					else
					{
						itr++;
					}
				}

				if( !mOnlyEmptyFlag )
				{
					if( !mDefaultFunc.IsEmpty() && !mDefaultFunc() )
					{
						mDefaultFunc.Reset();
					}
				}
			}
			else
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

		// �֐���ǉ�
		void Add( const Delegate &func )
		{
			mFuncList.push_back( func );
		}

		// �֐���S�폜
		void Clear()
		{
			mFuncList.clear();
		}

		// �֐��̗L���𒲂ׂ�
		bool IsEmpty() const
		{
			return mFuncList.empty();
		}

		// �֐��̐��𒲂ׂ�
		std::list<Delegate>::size_type GetSize() const
		{
			return mFuncList.size();
		}

		// ��̎��Ɏ��s����֐��̐ݒ�
		// onlyEmpty��false�ɂ���ƁA��łȂ��������s�����
		// �֐���false��Ԃ��Ɛݒ肪���������
		void SetDefaultFunction( const Delegate &func, bool onlyEmpty = true )
		{
			mDefaultFunc = func;
			mOnlyEmptyFlag = onlyEmpty;
		}

	private:
		std::list<Delegate> mFuncList;
		Delegate mDefaultFunc;
		// mDefaultFunc��mFuncList����̎��������s���Ȃ��t���O
		bool mOnlyEmptyFlag;
	};
}
}