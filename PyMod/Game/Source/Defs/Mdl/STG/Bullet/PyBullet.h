#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Mdl/STG/Bullet/IBullet.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
#pragma warning( disable:4250 )
	class PyBullet
		: public Actor::PyActor
		, public Game::Mdl::STG::Bullet::IBullet
	{
	public:
		PyBullet( const boost::python::object &object )
			: PyActor( object )
		{}

		// �����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHitCircle" )( hit ) );
		}
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHitRect" )( hit ) );
		}
		// �j��(�G�t�F�N�g����)
		virtual void Destruct()
		{
			mPyObject.attr( "destruct" )();
		}
		virtual void Destruct( float hp )
		{
			mPyObject.attr( "applyDamage" )( hp );
		}

		// HP�̎擾
		virtual float GetHP() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hp" ) );
		}
		// �����蔻��̔��a�̎擾
		virtual float GetHitRadius() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hitRadius" ) );
		}
};
}
}
}
}