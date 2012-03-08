#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Actor/PyActor.h"
#include "Mdl/STG/Enemy/IEnemy.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------
namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Enemy
{
#pragma warning( disable:4250 )
	class PyEnemy
		: public Actor::PyActor
		, public Game::Mdl::STG::Enemy::IEnemy
	{
	public:
		PyEnemy( const boost::python::object &object )
			: PyActor( object )
		{}

		// �����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::RectI &hit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit" )( hit ) );
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
		// �����蔻��̎擾
		virtual Game::Util::STG::Hit::RectI GetHitRect() const
		{
			return boost::python::extract<Game::Util::STG::Hit::RectI>( 
				mPyObject.attr( "hitRect" ) );
		}

		// �����蔻��p�̔��a���擾
		virtual float GetHitRadius() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "hitRadius" ) );
		}

		// PrimalArmor����������Ă��邩���擾
		virtual bool IsPAGenerated() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "paGenerated" ) );
		}
		// PrimalArmor�̑��ʂ��擾
		virtual float GetMaxPAAmount() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "maxPAAmount" ) );
		}
		// PrimalArmor�̎c�ʂ��擾
		virtual float GetPAAmount() const
		{
			return boost::python::extract<float>( 
				mPyObject.attr( "paAmount" ) );
		}
	};
}
}
}
}