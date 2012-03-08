#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
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
namespace Bullet
{
	class Linear
		: public Base
	{
	public:
		// �R���X�g���N�^
		Linear( PMode pMode, 
			const Util::STG::Locator::LinearF &locator, int hitRadius, 
			const Util::Sprite::DrawParameter &drawParam );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// ���P�[�^�̎擾
		Util::STG::Locator::LinearF &GetLocator();
		// �`��p�����[�^�̎擾
		const Util::Sprite::DrawParameter &GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const Util::Sprite::DrawParameter &drawParam );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Auxs mAuxs;

	protected:
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