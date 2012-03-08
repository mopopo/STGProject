#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <cassert>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	template <class Type>
	class SafeUpdateObject
	{
	public:
		// ������shared_ptr�̃R�s�[��n���Ă������ƂŁAUpdateState()����
		// ���̃I�u�W�F�N�g���Q�Ƃ��Ă���shared_ptr�����ׂĔj������悤�ɂ��Ă�
		// Update()�̃X�R�[�v�𔲂���܂ł͂��̃I�u�W�F�N�g���j������Ȃ��悤�ɂ���
		void Update( typename Ptr<Type>::Shared p )
		{
			assert( p );

			UpdateState();
		}

		virtual ~SafeUpdateObject() {}

	private:
		virtual void UpdateState() = 0;
	};
}
}