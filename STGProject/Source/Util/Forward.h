#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "StdFwd.h"
#include "SLNFwd.h"
#include "Delegate/Forward.h"
#include "STG/Forward.h"
#include "Input/STG/Forward.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	class Console;
	class Exception;
	class FunctionList;
	class FunctionQueue;
	template <class ElemType>
	class Pager;
	template <class Type>
	class Pool;
	class RepeatCounter;
	template <class Type>
	class SafeUpdateObject;

	template <class T>
	struct Ptr
	{
		typedef boost::shared_ptr<T> Shared;
		typedef boost::weak_ptr<T> Weak;
		typedef boost::intrusive_ptr<T> Intrusive;
	};

	namespace Core
	{
		// �R�A�̃C���^�[�t�F�C�X
		typedef Ptr<Selene::Engine::ICore>::Intrusive PCore;
		// �X�v���C�g�p�C���^�[�t�F�C�X
		typedef Ptr<Selene::Engine::Graphics::Simple::ISpriteRenderer>::Intrusive 
			PSpriteRenderer;
		// �O���t�B�N�X�}�l�[�W���[�̃C���^�[�t�F�C�X
		typedef Selene::Engine::Graphics::IManager *PGraphicsManager;
		// �t�@�C���}�l�[�W���[�̃C���^�[�t�F�C�X
		typedef Selene::Engine::File::IManager *PFileManager;
		// �T�E���h�}�l�[�W���[�̃C���^�[�t�F�C�X
		typedef Selene::Engine::Sound::IManager *PSoundManager;
		// �C���v�b�g�}�l�[�W���[�̃C���^�[�t�F�C�X
		typedef Selene::Engine::Input::IManager *PInputManager;

		class Manager;
	}

	namespace File
	{
		// �t�@�C���̃C���^�[�t�F�C�X
		typedef Ptr<Selene::Engine::File::IFile>::Intrusive PFile;
		// �p�b�N�t�@�C���̃C���^�[�t�F�C�X
		typedef Ptr<Selene::Engine::File::IPackFile>::Intrusive PPackFile;
		// �t�@�C���p�X��PFile�̃}�b�v
		typedef std::map<std::wstring, PFile, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PFile>>> 
			FileMap;
		typedef std::pair<std::wstring, PFile> FileMapElemType;

		typedef std::map<std::string, std::string, 
			std::less<std::string>, 
			std::allocator<std::pair<const std::string, std::string>>> 
			PropertyMap;
		typedef std::pair<std::string, std::string> PropMapElem;

		class Manager;
		class Property;
		class IDynamicFile;

		namespace Detail
		{
			class DeviceOfDynamicFile;
			class DynamicFile;
			class ICrypt;
			class SourceOfFile;
			class SyncFile;
		}

		namespace Exception
		{
			class NotFound;
		}
	}

	namespace Font
	{
		class Manager;
		class IFont;

		// �t�H���g�f�[�^
		typedef Ptr<IFont>::Shared PFont;
		// �t�@�C���̃p�X��IFont�̃}�b�v
		typedef std::map<std::wstring, PFont, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PFont>>> FontMap;
		typedef std::pair<std::wstring, PFont> FontMapElemType;

		namespace Detail
		{
			class TextureLoader;
			class SLNFont;

			typedef Ptr<Selene::Engine::Graphics::Resource::Text::ITextData>::Intrusive 
				PSLNFont;
		}

		namespace Exception
		{
			class Invalid;
		}
	}

	namespace Input
	{
		class Manager;
	}

	namespace Random
	{
		class IRandom;

		namespace Impl
		{
			class SLN;

			typedef Ptr<SLN>::Shared PSLN;
		}

		typedef Ptr<IRandom>::Shared PRandom;
	}

	namespace Resource
	{
		class Manager;

		namespace Exception
		{
			class Duplicate;
			class NotFound;
		}
	}

	namespace Sound
	{
		class Manager;
		class IStatic;
		class IStream;

		namespace Detail
		{
			class Static;
			class Stream;
		}

		namespace Exception
		{
			class Invalid;
			class InvalidLayer;
		}

		typedef Ptr<IStatic>::Shared PStatic;
		typedef Ptr<IStream>::Shared PStream;

		// �t�@�C���̃p�X�ƃT�E���h�̃��C�����̃}�b�v
		typedef std::map<std::wstring, Selene::Uint32, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, Selene::Uint32>>> 
			StaticSrcMap;
		typedef std::pair<std::wstring, Selene::Uint32> StaticSrcMapElemType;
		// �t�@�C���̃p�X��IStaticSound�̃}�b�v
		typedef std::map<std::wstring, PStatic, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PStatic>>> 
			StaticMap;
		typedef std::pair<std::wstring, PStatic> StaticMapElemType;

		// �t�@�C���̃p�X�ƃ������R�s�[�t���O�̃}�b�v
		typedef std::map<std::wstring, bool, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, bool>>> 
			StreamSrcMap;
		typedef std::pair<std::wstring, bool> StreamSrcMapElemType;
		// �t�@�C���̃p�X��IStreamSound�̃}�b�v
		typedef std::map<std::wstring, PStream, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PStream>>> 
			StreamMap;
		typedef std::pair<std::wstring, PStream> StreamMapElemType;
	}

	namespace Sprite
	{
		class Manager;
		class DrawParameter;
		class SrcDef;
		class Animation;

		namespace Exception
		{
			class InvalidTexture;
		}

		// �e�N�X�`��
		typedef Ptr<Selene::Engine::Graphics::Resource::ITexture>::Intrusive PTexture;

		// �t�@�C���̃p�X�Ɠ��ߐF�̃}�b�v
		typedef std::map<std::wstring, Selene::ColorF, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, Selene::ColorF>>> 
			TextureSrcMap;
		typedef std::pair<std::wstring, Selene::ColorF> TextureSrcMapElemType;
		// �t�@�C���̃p�X��ITexture�̃}�b�v
		typedef std::map<std::wstring, PTexture, 
			std::less<std::wstring>, 
			std::allocator<std::pair<const std::wstring, PTexture>>> 
			TextureMap;
		typedef std::pair<std::wstring, PTexture> TextureMapElemType;
	}
}
}