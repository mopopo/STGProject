#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Input/STG/IController.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Input
{
namespace STG
{
namespace Detail
{
	// ���v���C�Đ����Ƀ��v���C��񂩂���͏����擾����
	class ReplayController
		: public IController
	{
	public:
		// �t���[��Ԃ����擾
		virtual bool IsFree( KEY_ID key ) const;
		// �������u�Ԃ����擾
		virtual bool IsPull( KEY_ID key ) const;
		// �������u�Ԃ����擾
		virtual bool IsPush( KEY_ID key ) const;
		// �z�[���h��Ԃ����擾
		virtual bool IsHold( KEY_ID key ) const;

		// �����̎擾
		virtual Util::STG::Vector2DF GetDirection() const;

	private:
	};
}
}
}
}
}