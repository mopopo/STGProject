#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sound/IStream.h"
#include <boost/noncopyable.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Sound
{
namespace Detail
{
	typedef Ptr<Selene::Engine::Sound::Resource::IStreamSound>::Intrusive 
		PStreamSound;

	class Stream
		: public IStream
		, public boost::noncopyable
	{
	public:
		// �Đ�
		virtual void Play();
		virtual void Play( Selene::Uint32 loopCount );
		virtual void Play( const PlayBlock playBlocks[], Selene::Uint32 blockCount );
		// ��~
		virtual void Stop();
		// �ꎞ��~/����
		virtual void Pause();
		// �Đ���Ԃ��`�F�b�N
		virtual bool IsPlay();
		// �{�����[���ύX
		virtual void SetVolume( float volume = 1.0f );
		// �t�F�[�h�C������
		virtual void FadeIn( float second );
		// �t�F�[�h�A�E�g����
		virtual void FadeOut( float second );

		// SoundUtil�̃{�����[���ύX�̔��f
		virtual void UpdateVolume();

		// �R���X�g���N�^
		Stream( PStreamSound pStreamSound, const std::wstring &name );

	private:
		// Selene��IStaticSound
		PStreamSound mpStreamSound;
		// �{�����[��
		float mVolume;
		// �t�F�[�h�C��/�A�E�g�������t���O
		bool mFading;
	};
}
}
}
}