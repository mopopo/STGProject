#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
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
	class FadeOut
		: public Base
	{
	public:
		// �R���X�g���N�^
		FadeOut( PMode pMode, const Util::STG::Hit::RectI &validRect );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// �`��p�����[�^�̎擾
		Util::Sprite::DrawParameter GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const Util::Sprite::DrawParameter &param );
		// ��������܂ł̑��t���[�����̎擾
		unsigned GetFrameNum() const;
		// ��������܂ł̑��t���[�����̐ݒ�
		void SetFrameNum( unsigned num );
		// �t���[���J�E���g�̎擾
		unsigned GetFrameCount() const;
		// �t���[���J�E���g�̐ݒ�
		void SetFrameCount( unsigned count );

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		float mMaxAlpha;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();
	};
}
}
}
}