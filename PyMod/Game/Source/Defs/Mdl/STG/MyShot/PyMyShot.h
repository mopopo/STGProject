#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Mdl/STG/MyShot/IMyShot.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace MyShot
{
#pragma warning( disable:4250 )
	class PyMyShot
		: public Actor::PyActor
		, public Game::Mdl::STG::MyShot::IMyShot
	{
	public:
		PyMyShot( const boost::python::object &object )
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
		// �j��
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

		// PrimalArmor�ւ̃_���[�W���擾
		virtual float GetPADamage() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "paDamage" ) );
		}
		// PrimalArmor���W�J����Ă��Ȃ����ł������I�Ƀ_���[�W��^���邩�ǂ������擾
		virtual bool IsForcibleForPA() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "forcibleForPA" ) );
		}
	};
}
}
}
}