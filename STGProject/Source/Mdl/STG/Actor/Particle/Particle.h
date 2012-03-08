#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "../Base.h"
#include "Mdl/STG/Auxs.h"
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
namespace Actor
{
namespace Particle
{
	class Particle
		: public Base
	{
	public:
		// �R���X�g���N�^
		Particle( Base::PMode pMode, 
			const Util::STG::Vector2DF &pos, 
			const Util::Sprite::DrawParameter &dParam );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// ���P�[�^�̎擾
		Util::STG::Locator::LinearF &GetLocator();
		// �`��p�����[�^�̎擾
		Util::Sprite::DrawParameter GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const Util::Sprite::DrawParameter &param );
		// �g�嗦�̎擾
		float GetZoomRate() const;
		// �g�嗦�̐ݒ�
		void SetZoomRate( float rate );
		// �g�嗦�̌������̎擾
		float GetZoomDecRate() const;
		// �g�嗦�̌������̐ݒ�
		void SetZoomDecRate( float rate );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		float mZoomDecRate, mZoomRateCount;
		Auxs mAuxs;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		Util::Sprite::DrawParameter CreateDrawParam() const;
		void ModifyValidRect();
	};
}
}
}
}
}