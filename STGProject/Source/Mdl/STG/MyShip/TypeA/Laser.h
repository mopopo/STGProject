#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/MyShot/Base.h"
#include "Util/STG/Locator/Linear.h"
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
	typedef Util::Ptr<class Laser>::Shared PLaser;

	class Laser
		: public MyShot::Base
	{
	public:
		// �R���X�g���N�^
		Laser( Actor::Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, 
			Util::Sprite::PTexture pLaserTexture, 
			Util::Sprite::PTexture pParticleTexture );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Util::Sprite::PTexture mpParticleTexture;
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