#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/Base.h"
#include "Defs/Mdl/STG/Actor/ActorDefs.h"
#include "Defs/Mdl/STG/Auxs.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/DrawParameter.h"


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
namespace Particle
{
	class Particle
		: public Base
	{
	public:
		// �R���X�g���N�^
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		Particle( const Game::Util::STG::Vector2DF &pos, 
			const DrawParameter &dParam );

		// �ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// ���P�[�^�̎擾
		Game::Util::STG::Locator::LinearF &GetLocator();
		// �`��p�����[�^�̎擾
		DrawParameter GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const DrawParameter &param );
		// �g�嗦�̎擾
		float GetZoomRate() const;
		// �g�嗦�̐ݒ�
		void SetZoomRate( float rate );
		// �g�嗦�̌������̎擾
		float GetZoomDecRate() const;
		// �g�嗦�̌������̐ݒ�
		void SetZoomDecRate( float rate );
		// ��]���x�̎擾
		float GetRotSpeed() const;
		// ��]���x�̐ݒ�
		void SetRotSpeed( float speed );

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		DrawParameter mDrawParam;
		float mZoomDecRate, mZoomRateCount;
		float mRotSpeed;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		DrawParameter CreateDrawParam() const;
		void ModifyValidRect();

		friend ActorDefs;
	};
}
}
}
}
}