#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/Animation.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
	class Animation
		: public Base
	{
	public:
		// �R���X�g���N�^
		Animation( PMode pMode, const Util::STG::Hit::RectI &validRect, 
			const Util::Sprite::Animation &animation );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// �A�j���[�V�����ݒ�̎擾
		Util::Sprite::Animation &GetAnimation();

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::Animation mAnimation;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
	};
}
}
}
}