#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/Sound/IStatic.h"
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
	typedef Ptr<Selene::Engine::Sound::Resource::IStaticSound>::Intrusive 
		PStaticSound;

	class Static
		: public IStatic
		, public boost::noncopyable
	{
	public:
		// �Đ�
		virtual void Play( bool isLoop = false );
		virtual void Play( Selene::Uint32 layer, bool isLoop = false );
		// ��~
		virtual void Stop();
		virtual void Stop( Selene::Uint32 layer );
		// �ꎞ��~/����
		virtual void Pause();
		virtual void Pause( Selene::Uint32 layer );
		// �ꎞ��~�`�F�b�N
		virtual bool IsPause();
		virtual bool IsPause( Selene::Uint32 layer );
		// �Đ���Ԃ��`�F�b�N
		virtual bool IsPlay();
		virtual bool IsPlay( Selene::Uint32 layer );
		// �{�����[���ύX
		virtual void SetVolume( float volume = 1.0f );
		virtual void SetVolume( Selene::Uint32 layer, float volume = 1.0f );
		// ���C���[�����ׂōĐ���Ԃ̎��ɑ҂��ǂ���
		virtual bool IsWaitingForPlay() const;
		virtual void SetWaitingForPlay( bool waiting );

		// SoundUtil�̃{�����[���ύX�̔��f
		virtual void UpdateVolume();

		// �R���X�g���N�^
		Static( PStaticSound pStaticSound, const std::wstring &name, 
			Selene::Uint32 layerCount = 32 );

	private:
		// Selene��IStaticSound
		PStaticSound mpStaticSound;
		// �X�̃��C���[�̃{�����[��
		std::vector<float> mIndividualVolumes;
		// ���C���[�̔ԍ��̒�`��
		const boost::numeric::interval<Selene::Uint32> mLayerItv;
		// ��O�̍\�z�Ɏg�p
		const std::wstring mName;
		// ���C���[�����ׂōĐ���Ԃ̎��ɑ҂��ǂ���
		bool mWaitingForPlay;
	};
}
}
}
}