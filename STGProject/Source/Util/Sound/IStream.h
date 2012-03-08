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
	// �X�g���[���T�E���h�Đ��p�����[�^�[
	typedef Selene::Engine::Sound::Resource::SPlayBlock PlayBlock;

	class IStream
	{
	public:
		// �Đ�
		virtual void Play() = 0;
		virtual void Play( Selene::Uint32 loopCount ) = 0;
		virtual void Play( const PlayBlock playBlocks[], Selene::Uint32 blockCount ) = 0;
		// ��~
		virtual void Stop() = 0;
		// �ꎞ��~/����
		virtual void Pause() = 0;
		// �Đ���Ԃ��`�F�b�N
		virtual bool IsPlay() = 0;
		// �{�����[���ύX
		virtual void SetVolume( float volume = 1.0f ) = 0;
		// �t�F�[�h�C������
		virtual void FadeIn( float second ) = 0;
		// �t�F�[�h�A�E�g����
		virtual void FadeOut( float second ) = 0;

		// SoundUtil�̃{�����[���ύX�̔��f
		virtual void UpdateVolume() = 0;

		// �f�X�g���N�^
		virtual ~IStream() {}
	};
}
}
}