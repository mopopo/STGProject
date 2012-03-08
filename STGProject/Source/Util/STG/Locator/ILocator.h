#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace STG
{
namespace Locator
{
	template <class T>
	class ILocator
	{
	public:
		// ��Ԃ̍X�V
		virtual void Update() = 0;

		// �ʒu�̎擾
		virtual Vector2D<T> GetPosition() const = 0;
		// �O�͂̓K�p
		virtual Vector2D<T> ApplyExternalForce( const Vector2D<T> &vec ) = 0;
	};

	typedef ILocator<float> ILocatorF;
	typedef ILocator<Selene::Sint32> ILocatorI;
}
}
}
}