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
namespace Enemy
{
	class IEnemy
		: virtual public Actor::IActor
	{
	public:
		// �����蔻��
		virtual bool IsHit( const Util::STG::Hit::RectI &hit ) const = 0;
		// �j��(�G�t�F�N�g����)
		virtual void Destruct() = 0;
		virtual void Destruct( float hp ) = 0;

		// HP�̎擾
		virtual float GetHP() const = 0;
		// �����蔻��̎擾
		virtual Util::STG::Hit::RectI GetHitRect() const = 0;

		// �����蔻��p�̔��a���擾
		virtual float GetHitRadius() const = 0;

		// PrimalArmor����������Ă��邩���擾
		virtual bool IsPAGenerated() const = 0;
		// PrimalArmor�̑��ʂ��擾
		virtual float GetMaxPAAmount() const = 0;
		// PrimalArmor�̎c�ʂ��擾
		virtual float GetPAAmount() const = 0;

		virtual ~IEnemy() {}
	};
}
}
}
}