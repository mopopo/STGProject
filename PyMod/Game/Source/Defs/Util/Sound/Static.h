#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Sound/IStatic.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace Sound
{
	class Static
	{
	public:
		typedef Game::Util::Sound::PStatic PStatic;
		Static( PStatic p )
			: mpStatic( p )
		{}

		// �Đ�
		void Play()
		{
			mpStatic->Play();
		}
		void Play( bool isLoop )
		{
			mpStatic->Play( isLoop );
		}
		// ��~
		void Stop()
		{
			mpStatic->Stop();
		}
		// �ꎞ��~/����
		void Pause()
		{
			mpStatic->Pause();
		}
		// �ꎞ��~�`�F�b�N
		bool IsPause()
		{
			return mpStatic->IsPause();
		}
		// �Đ���Ԃ��`�F�b�N
		bool IsPlay()
		{
			return mpStatic->IsPlay();
		}
		// �{�����[���ύX
		void SetVolume( float volume )
		{
			mpStatic->SetVolume( volume );
		}
		// ���C���[�����ׂōĐ���Ԃ̎��ɑ҂��ǂ���
		bool IsWaitingForPlay()
		{
			return mpStatic->IsWaitingForPlay();
		}
		void SetWaitingForPlay( bool waiting )
		{
			mpStatic->SetWaitingForPlay( waiting );
		}

	private:
		Game::Util::Sound::PStatic mpStatic;
	};
}
}
}