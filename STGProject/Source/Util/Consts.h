#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/numeric/interval.hpp>


//----------------------------------------------------------------------------------
//	Const Values
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Consts
{
	// ��ʂ̃T�C�Y
	static const Selene::Point2DI SCREEN_SIZE( 640, 480 );
	// STG��ʂ̏��\���̈�̃T�C�Y
	static const Selene::Point2DI STG_INFAREA_SIZE( 200, 480 );

	namespace Sound
	{
		// �T�E���h�̃{�����[���̒�`��
		static const boost::numeric::interval<float> VOLUME_ITV( 0.0f, 1.0f );

		// �Đ����Ԏ����ݒ�
		static const float PLAY_TIME_AUTO = -1.0f;

		// �ǂݍ��݌��p�X
		static const std::wstring LOAD_TOP_PATH_SE = L"SE/";
		static const std::wstring LOAD_TOP_PATH_BGM = L"BGM/";
	}

	namespace Sprite
	{
		// �ǂݍ��݌��p�X
		static const std::wstring LOAD_TOP_PATH = L"Graphics/";
	}

	namespace File
	{
		// �������pPass
		static const char CRYPT_PASS[] = "qawsedrftgyhujikolp";
	}

	namespace Font
	{
		// �ǂݍ��݌��p�X
		static const std::wstring LOAD_TOP_PATH = L"Font/";
	}
}
}
}