#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Hit/Rect.h"
#include "Util/STG/Vector2D.h"


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
	class IActor
	{
	public:
		// ��ӂȐ����l���擾
		virtual Selene::Uint64 GetId() const = 0;

		// �X�V
		virtual void Update() = 0;
		// �`��
		virtual void Draw() const = 0;

		// �L���t���O�̎擾
		virtual bool IsValid() const = 0;
		// �L���t���O�̐ݒ�
		virtual void SetValid( bool flag ) = 0;

		// ����
		virtual void Erase() = 0;

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const = 0;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec ) = 0;
		// �L���̈攻��̎擾
		virtual Util::STG::Hit::RectI GetValidRect() const = 0;
		// �L���̈攻��̐ݒ�
		virtual void SetValidRect( const Util::STG::Hit::RectI &rect ) = 0;
		// �L���̈�̗]���̐ݒ�
		virtual void SetValidAreaMargin( int margin ) = 0;
		// ���݂̃t���[���J�E���g���擾
		virtual unsigned GetFrameCount() const = 0;
		// ���݂̃t���[���J�E���g��ݒ�
		virtual void SetFrameCount( unsigned count ) = 0;
		// �L������t���[���J�E���g�̎擾
		virtual unsigned GetValidFrameNum() const = 0;
		// �L������t���[���J�E���g�̐ݒ�
		virtual void SetValidFrameNum( unsigned frameNum ) = 0;

		virtual ~IActor() {}
	};
}
}
}
}