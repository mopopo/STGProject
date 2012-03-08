#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Mdl/STG/Actor/IActor.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Item
{
	class IItem
		: virtual public Actor::IActor
	{
	public:
		// ���@�w�̓����蔻��̔��a�̎擾
		virtual float GetHitRadius() const = 0;
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const = 0;

		virtual ~IItem() {}
	};
}
}
}
}