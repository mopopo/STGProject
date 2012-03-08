#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sound
{
	class IStatic
	{
	public:
		// �Đ�
		virtual void Play( bool isLoop = false ) = 0;
		virtual void Play( Selene::Uint32 layer, bool isLoop = false ) = 0;
		// ��~
		virtual void Stop() = 0;
		virtual void Stop( Selene::Uint32 layer ) = 0;
		// �ꎞ��~/����
		virtual void Pause() = 0;
		virtual void Pause( Selene::Uint32 layer ) = 0;
		// �ꎞ��~�`�F�b�N
		virtual bool IsPause() = 0;
		virtual bool IsPause( Selene::Uint32 layer ) = 0;
		// �Đ���Ԃ��`�F�b�N
		virtual bool IsPlay() = 0;
		virtual bool IsPlay( Selene::Uint32 layer ) = 0;
		// �{�����[���ύX
		virtual void SetVolume( float volume = 1.0f ) = 0;
		virtual void SetVolume( Selene::Uint32 layer, float volume = 1.0f ) = 0;
		// ���C���[�����ׂōĐ���Ԃ̎��ɑ҂��ǂ���
		virtual bool IsWaitingForPlay() const = 0;
		virtual void SetWaitingForPlay( bool waiting ) = 0;

		// SoundUtil�̃{�����[���ύX�̔��f
		virtual void UpdateVolume() = 0;

		// �f�X�g���N�^
		virtual ~IStatic() {}
	};
}
}
}