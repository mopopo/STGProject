#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Actor/IActor.h"
#include "Util/STG/Hit/Rect.h"


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
	class Base
		: virtual public Game::Mdl::STG::Actor::IActor
	{
	public:
		// ��ӂȐ����l���擾
		virtual Selene::Uint64 GetId() const;

		// �X�V
		virtual void Update();
		// �`��
		virtual void Draw() const;

		// �L���t���O�̎擾
		virtual bool IsValid() const;
		// �L���t���O�̐ݒ�
		virtual void SetValid( bool flag );

		// ����
		virtual void Erase();

		// �L���̈攻��̎擾
		virtual Game::Util::STG::Hit::RectI GetValidRect() const;
		// �L���̈攻��̐ݒ�
		virtual void SetValidRect( const Game::Util::STG::Hit::RectI &rect );
		// �L���̈�̗]���̐ݒ�
		virtual void SetValidAreaMargin( int margin );
		// ���݂̃t���[���J�E���g���擾
		virtual unsigned GetFrameCount() const;
		// ���݂̃t���[���J�E���g��ݒ�
		virtual void SetFrameCount( unsigned count );
		// �L������t���[���J�E���g�̎擾
		virtual unsigned GetValidFrameNum() const;
		// �L������t���[���J�E���g�̐ݒ�
		virtual void SetValidFrameNum( unsigned frameNum );

	protected:
		// �R���X�g���N�^
		Base( const Game::Util::STG::Hit::RectI &validRect );

		// �t���[���J�E���g���邩�ǂ����擾
		bool IsFrameCounting() const;
		// �t���[���J�E���g���邩�ǂ����ݒ�
		void SetFrameCounting( bool counting );

	private:
		const Selene::Uint64 mId;
		bool mValidFlag;
		Game::Util::STG::Hit::RectI mValidArea, mValidRect;
		unsigned mValidFrameNum, mFrameCount;
		bool mFrameCounting;

		virtual void UpdateMiddle() {}
		virtual void DrawMiddle() const {}

		virtual void OnUpdate() = 0;
		virtual void OnDraw() const = 0;
		virtual void OnErase() = 0;
	};
}
}
}
}