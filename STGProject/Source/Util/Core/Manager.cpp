#include "PCH.h"
#include "Manager.h"

using namespace Game;
using namespace Util::Core;
using namespace Selene;

namespace
{
	// �R�A�̕ێ�
	static PCore mpCore;
	// �X�v���C�g�p�C���^�[�t�F�C�X�̕ێ�
	static PSpriteRenderer mpSpriteRenderer;
}


// �G���W���̏�����
bool Manager::InitEngine()
{
#ifdef SLN_DEVELOP
	if ( !Selene::InitializeEngine( L"Selene.Develop.dll" ) )
#else // SLN_DEVELOP
#ifdef SLN_DEBUG
	if ( !Selene::InitializeEngine( L"Selene.Debug.dll" ) )
#else // SLN_DEBUG
	if ( !Selene::InitializeEngine( L"Selene.dll" ) )
#endif // SLN_DEBUG
#endif // SLN_DEVELOP
	{
		return false;
	}

	mpCore = MakeIntrusivePtr( CreateCore() );

	const std::wstring appName = 
		boost::python::extract<std::wstring>( 
		boost::python::import( "Config" ).attr( "appName" ) );
	if ( !mpCore->Initialize( appName.c_str(), Consts::SCREEN_SIZE, true, true ) )
	{
		return false;
	}

	// �e��}�l�[�W���[�̐���
	if( !mpCore->CreateGraphicsManager() || 
		!mpCore->CreateFileManager() || 
		!mpCore->CreateSoundManager() || 
		!mpCore->CreateInputManager() )
	{
		return false;
	}
	if( !( mpSpriteRenderer = 
		Util::MakeIntrusivePtr( mpCore->GetGraphicsManager()->CreateSpriteRenderer() ) ) )
	{
		return false;
	}

	// �T�E���h�̃f�R�[�h�p�̃v���O�C����
	// �����Ă���f�B���N�g���̏ꏊ�B
	mpCore->GetSoundManager()->SetPluginDirectory( L"Plugin/Sound" );

	// �^�C�g���o�[�̃e�L�X�g�ݒ�
	mpCore->GetWindow()->SetTitleText( appName.c_str() );

	// �J�[�\���\��ON/OFF
	mpCore->GetWindow()->SetShowCursor( false );

	File::Manager::Initialize();

	return true;
}


// �R�A�̎擾
PCore Manager::GetCore()
{
	assert( mpCore );

	return mpCore;
}

// �X�v���C�g�p�C���^�[�t�F�C�X�̎擾
PSpriteRenderer Manager::GetSpriteRenderer()
{
	assert( mpSpriteRenderer );

	return mpSpriteRenderer;
}

// �O���t�B�N�X�}�l�[�W���[�̎擾
PGraphicsManager Manager::GetGraphicsManager()
{
	assert( mpCore );

	return mpCore->GetGraphicsManager();
}

// �t�@�C���}�l�[�W���[�̎擾
PFileManager Manager::GetFileManager()
{
	assert( mpCore );

	return mpCore->GetFileManager();
}

// �T�E���h�}�l�[�W���[�̎擾
PSoundManager Manager::GetSoundManager()
{
	assert( mpCore );

	return mpCore->GetSoundManager();
}

// �C���v�b�g�}�l�[�W���[�̎擾
PInputManager Manager::GetInputManager()
{
	assert( mpCore );

	return mpCore->GetInputManager();
}


// �R�A�̊J��
void Manager::Release()
{
	mpSpriteRenderer.reset();
	mpCore.reset();
}