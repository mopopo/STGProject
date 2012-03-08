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
namespace MyShot
{
	class IMyShot
		: virtual public Actor::IActor
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::CircleI &hit ) const = 0;
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const = 0;
		// �j��
		virtual void Destruct() = 0;
		virtual void Destruct( float hp ) = 0;

		// HP�̎擾
		virtual float GetHP() const = 0;
		// �����蔻��̔��a�̎擾
		virtual float GetHitRadius() const = 0;

		// PrimalArmor�ւ̃_���[�W���擾
		virtual float GetPADamage() const = 0;
		// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ������擾
		virtual bool IsForcibleForPA() const = 0;

		virtual ~IMyShot() {}
	};
}
}
}
}