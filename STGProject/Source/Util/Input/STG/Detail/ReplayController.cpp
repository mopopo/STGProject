#include "PCH.h"
#include "ReplayController.h"

using namespace Game;
using namespace Util::Input::STG;
using namespace Detail;
using namespace Selene;


// �t���[��Ԃ����擾
bool ReplayController::IsFree( KEY_ID key ) const
{
	return false;
}

// �������u�Ԃ����擾
bool ReplayController::IsPull( KEY_ID key ) const
{
	return false;
}

// �������u�Ԃ����擾
bool ReplayController::IsPush( KEY_ID key ) const
{
	return false;
}

// �z�[���h��Ԃ����擾
bool ReplayController::IsHold( KEY_ID key ) const
{
	return false;
}


// �����̎擾
Util::STG::Vector2DF ReplayController::GetDirection() const
{
	return Util::STG::Vector2DF();
}