#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/MyShot/Base.h"
#include "Util/STG/Locator/Trace.h"
#include "Util/Sprite/DrawParameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
namespace TypeA
{
	typedef Util::Ptr<class Missile>::Shared PMissile;

	class Missile
		: public MyShot::Base
	{
	public:
		// �R���X�g���N�^
		Missile( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, float circlingAngle, 
			Util::Sprite::PTexture pMissileTexture );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

	private:
		Util::STG::Locator::TraceF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnDestruct();
		virtual void OnDestruct( float hp );
		virtual void OnErase();
	};
}
}
}
}
}