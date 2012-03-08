#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Defs/Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Linear.h"
#include "Defs/Util/Sprite/Animation/Manager.h"
#include "ActorDefs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
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
		Animation( const Game::Util::STG::Hit::RectI &validRect, 
			const Util::Sprite::Animation::Manager &animationManager );

		// �ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// �A�j���[�V�����ݒ�̎擾
		Util::Sprite::Animation::Manager &GetAnimationManager();
		// ���P�[�^�̎擾
		Game::Util::STG::Locator::LinearF &GetLocator();

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		Util::Sprite::Animation::Manager mAnimationManager;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		friend ActorDefs;
	};
}
}
}
}