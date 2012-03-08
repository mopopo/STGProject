#include "PCH.h"
#include "Console.h"
#include <iostream>

using namespace Game;
using namespace std;

namespace
{
	// ���łɍ쐬����Ă��邩�ǂ���
	static bool mIsCreated = false;
}


// �R���\�[���E�B���h�E���쐬����
bool Util::Console::Create()
{
	if( !mIsCreated )
	{
		if( AllocConsole() != 0 )
		{
			mIsCreated = true;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

// �R���\�[���E�B���h�E�ɏ�������
bool Util::Console::Write( const wstring &str )
{
	Create();

	wcout << str;
	flushall();

	DWORD writtenSize;
	if( WriteConsole( 
		GetStdHandle( STD_OUTPUT_HANDLE ), 
		str.c_str(), static_cast<DWORD>( str.size() ), &writtenSize, NULL ) != 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Util::Console::WriteLine( const wstring &str )
{
	return Write( str + L"\n" );
}

// �R���\�[����j������
bool Util::Console::Delete()
{
	if( mIsCreated )
	{
		if( FreeConsole() != 0 )
		{
			mIsCreated = false;

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}