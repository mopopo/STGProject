#include "PCH.h"

using namespace Selene;
using namespace Game;


//----------------------------------------------------------------------------------
//
//	���C���֐�
//
//----------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
	Util::Console::Create();
#endif

	// Python�C���^�v���^�̏�����
	bool pyInitStatus = Util::Python::Manager::Initialize();

	//------------------------------------------------------------
	// �G���W���A�N�Z�X�p�̃R�A�𐶐�
	//		�����쐬�͏o���Ȃ�
	//------------------------------------------------------------
	if( !Util::Core::Manager::InitEngine() )
	{
		return 0;
	}

	const std::wstring appName = 
		boost::python::extract<std::wstring>( 
		boost::python::import( "Config" ).attr( "appName" ) );

	try
	{
		if( !pyInitStatus )
		{
			throw std::exception( "Python�C���^�v���^�̏������Ɏ��s���܂���" );
		}

		Util::Core::PCore				pCore		= Util::Core::Manager::GetCore();
		Util::Core::PInputManager		pIManager	= pCore->GetInputManager();
		Util::Core::PSoundManager		pSManager	= pCore->GetSoundManager();
		Util::Core::PGraphicsManager	pGManager	= pCore->GetGraphicsManager();
		Util::Core::PSpriteRenderer		pSprite		= Util::Core::Manager::GetSpriteRenderer();

		// �^�C�g���o�[�ɕ\������FPS�̍X�V�^�C�~���O�Ǘ�
		Util::RepeatCounter titleBarUpdateCounter( 60 );

		//------------------------------------------------------------
		// ���C�����[�v
		//		Selene�𗘗p�����ł̃��C�����[�v�̏������ł�
		//		ICore::DoEvent()��OS�̃C�x���g�������s���܂��B
		//------------------------------------------------------------
		while ( pCore->DoEvent( 60 ) )
		{
			// ���p����}�l�[�W���[�̍X�V
			pIManager->Update();
			pSManager->Update();
			Util::Sprite::Manager::Update();

			// ��ʂ̃N���A
			pGManager->Clear( true, false, ColorF(0, 0, 0) );

			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// �t���[���̊J�n
			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			pCore->FrameBegin();

			// �X�v���C�g���̃L���b�V�������Z�b�g
			pSprite->CacheReset();

			// �V�[���̏�ԍX�V
			Ctrl::Scene::Manager::UpdateState();

			// �X�v���C�g�̕`��
			// �L���b�V���ɂ��܂����f�[�^����C�ɕ`�悵�܂�
			pSprite->CacheDraw();

			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// �t���[���̏I��
			//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			pCore->FrameEnd();

			// ��ʂ̍X�V
			pGManager->Present();

			// �^�C�g���o�[�̍X�V
			titleBarUpdateCounter.UpdateState();
			if( titleBarUpdateCounter.GetRepeatCount() >= 1 )
			{
				boost::wformat fm( L"%s FPS[ %d ]" );
				fm % appName;
				fm % static_cast<int>( pCore->GetFPS() );

				pCore->GetWindow()->SetTitleText( fm.str().c_str() );
			}

			// �V�[���̏I���t���O�������Ă����烋�[�v�𔲂���
			if( Ctrl::Scene::Manager::IsEnd() )
			{
				break;
			}
		}
		// �������Ă��Ȃ����\�[�X�����݂���ꍇ�A�R���\�[���ɂ��̃��\�[�X��\������
		std::vector<std::wstring> resourceList;
		Util::Resource::Manager::GetList( resourceList );

		if( resourceList.size() != 0 )
		{
			Util::Console::WriteLine( L"�ȉ��̃��\�[�X���������Ă��܂���\n" );

			foreach( const std::wstring &rName, resourceList )
			{
				Util::Console::WriteLine( rName );
			}

			pCore->ErrorMessageBox( appName.c_str(), 
				L"�������Ă��Ȃ����\�[�X������܂�" );
		}
	}
	catch( boost::python::error_already_set const & )
	{
		PyErr_Print();

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"Python�C���^�v���^�ŗ�O���������܂���" );
	}
	catch( Util::Exception &e )
	{
		Util::Console::WriteLine( 
			Util::ToWide( boost::diagnostic_information( e ) ) );

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"��O���������܂����F%s", e.GetErrorMessageBoxInfo().c_str() );
	}
	catch( boost::exception &e )
	{
		Util::Console::WriteLine( 
			Util::ToWide( boost::diagnostic_information( e ) ) );

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"��O���������܂����F%s", Util::ToWide( typeid(e).name() ).c_str() );
	}
	catch( std::exception &e )
	{
		Util::Console::WriteLine( Util::ToWide( e.what() ) );

		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"��O���������܂����F%s", Util::ToWide( typeid(e).name() ).c_str() );
	}
	catch( ... )
	{
		Util::Core::Manager::GetCore()->ErrorMessageBox( appName.c_str(), 
			L"�\�����Ȃ���O���������܂���" );
	}

	// ��n��
	Ctrl::Scene::Manager::Release();
	Util::Core::Manager::Release();
	Util::File::Manager::Release();
	Util::Input::Manager::Release();
	Util::Resource::Manager::Clear();
	FinalizeEngine();

	return 0;
}