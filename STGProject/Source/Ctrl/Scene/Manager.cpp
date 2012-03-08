#include "PCH.h"
#include "Manager.h"
#include "Initialize.h"
#include "PyScene.h"
#include "Finalizer.h"

using namespace Game;
using namespace Game::Ctrl::Scene;
using namespace Selene;
using namespace std;

namespace
{
	typedef Util::Ptr<IScene>::Shared PScene;

	static PScene mpCurrentScene( new Initialize() );
	static PScene mpOldScene;
	static bool mIsEnd = false;
	static Util::FunctionList mFuncList;
	static stack<Util::FunctionList> mFuncStack;
}


// 1�t���[�����̏�ԍX�V
void Manager::UpdateState()
{
	if( mpOldScene )
	{
		mpOldScene.reset();

		ReturnAll();
		ClearUpdateFunction();

		Util::Sound::Manager::StopStatics();
		Util::Sound::Manager::StopStreams();
		Util::Sprite::Manager::ResetShake();

		boost::python::import( "gc" ).attr( "collect" )();
	}

	if( mFuncStack.empty() )
	{
		mFuncList();

		mpCurrentScene->Update( mpCurrentScene );
	}
	else
	{
		mFuncStack.top()();

		if( mFuncStack.top().IsEmpty() )
		{
			Return();
		}
	}

	// Esc�������ƏI��
	if( Util::Core::Manager::GetInputManager()->GetKeyboard()->GetKeyData( 
		Engine::Input::KEY_ESCAPE ) )
	{
		End();
	}
}


// �V�[���̐؂�ւ�
void Manager::ChangeScene( ::PScene pNextScene )
{
	if( pNextScene )
	{
		mpOldScene = mpCurrentScene;
		mpCurrentScene = pNextScene;
	}
}

void Manager::ChangeScene( const boost::python::object &obj )
{
	ChangeScene( PScene( new PyScene( obj ) ) );
}


// �Q�[���̏I��
void Manager::End()
{
	mIsEnd = true;
}

// �I���t���O�̎擾
bool Manager::IsEnd()
{
	return mIsEnd;
}


// 1�t���[�����ɌĂяo���֐���ǉ�
void Manager::AddUpdateFunction( const Delegate &func )
{
	if( mFuncStack.empty() )
	{
		mFuncList.Add( func );
	}
	else
	{
		mFuncStack.top().Add( func );
	}
}

// �ǉ������X�V�֐����N���A����
// ���荞�݂�����ꍇ�͕��A����
void Manager::ClearUpdateFunction()
{
	if( IsInterrupted() )
	{
		mFuncStack.pop();
	}
	else
	{
		mFuncList.Clear();
	}
}

// ��ԍX�V�����Ɋ��荞��
void Manager::Interrupt( const Delegate &func )
{
	mFuncStack.push( Util::FunctionList() );
	mFuncStack.top().Add( func );
}

// ���荞�܂�Ă��邩�ǂ������ׂ�
bool Manager::IsInterrupted()
{
	return !mFuncStack.empty();
}

// ���荞�݂��畜�A����
void Manager::Return()
{
	if( IsInterrupted() )
	{
		mFuncStack.pop();
	}
}

// ���ׂĂ̊��荞�݂��畜�A����
void Manager::ReturnAll()
{
	while( IsInterrupted() )
	{
		mFuncStack.pop();
	}
}


// �V�[���̊J��
void Manager::Release()
{
	mpCurrentScene.reset();
	mpOldScene.reset();
	ReturnAll();
	ClearUpdateFunction();

	Finalizer::Finalize();
}