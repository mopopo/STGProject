#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Base.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/DrawParameter.h"
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
	class FadeOut
		: public Base
	{
	public:
		// �R���X�g���N�^
		FadeOut( const Game::Util::STG::Hit::RectI &validRect );

		// �ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// �`��p�����[�^�̎擾
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		DrawParameter GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const DrawParameter &param );
		// ��������܂ł̑��t���[�����̎擾
		unsigned GetFrameNum() const;
		// ��������܂ł̑��t���[�����̐ݒ�
		void SetFrameNum( unsigned num );
		// �t���[���J�E���g�̎擾
		unsigned GetFrameCount() const;
		// �t���[���J�E���g�̐ݒ�
		void SetFrameCount( unsigned count );
		// ���P�[�^�̎擾
		Game::Util::STG::Locator::LinearF &GetLocator();

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		Game::Util::Sprite::DrawParameter mDrawParam;
		float mMaxAlpha;

		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnErase();

		friend ActorDefs;
	};
}
}
}
}