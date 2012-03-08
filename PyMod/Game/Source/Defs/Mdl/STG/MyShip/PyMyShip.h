#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Mdl/STG/MyShip/IMyShip.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
	class PyMyShip
		: public Game::Mdl::STG::MyShip::IMyShip
	{
	public:
		PyMyShip( const boost::python::object &object )
			: mPyObject( object )
		{}

		typedef Game::Util::STG::Vector2DF Vector2DF;
		typedef Game::Util::STG::Hit::CircleI CircleI;

		// �t���[�����̍X�V
		virtual void Update()
		{
			mPyObject.attr( "update" )();
		}
		// �t���[�����̕`��
		virtual void Draw() const
		{
			mPyObject.attr( "draw" )();
		}
		// ���̈�̕`��
		virtual void DrawInfArea( const Vector2DF &basePos ) const
		{
			mPyObject.attr( "drawInfArea" )( basePos );
		}

		// �G�e�����蔻��
		virtual bool IsHit( const CircleI &bulletHit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit" )( bulletHit ) );
		}
		// �A�C�e���z���񂹓����蔻��
		virtual bool IsHit_ItemRetrieve( const CircleI &itemHit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit_ItemRetrieve" )( itemHit ) );
		}
		// �A�C�e���擾�����蔻��
		virtual bool IsHit_GetItem( const CircleI &itemHit ) const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "isHit_GetItem" )( itemHit ) );
		}
		// ���@�̔j��
		virtual void Destruct()
		{
			mPyObject.attr( "destruct" )();
		}

		// ����p���[�̎擾
		virtual int GetPower() const
		{
			return boost::python::extract<int>( 
				mPyObject.attr( "power" ) );
		}
		// ����p���[�̏㏸
		virtual bool SupplyPower()
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "supplyPower" )() );
		}
		// ����U���J�E���g�̎擾
		virtual int GetSpAttack() const
		{
			return boost::python::extract<int>( 
				mPyObject.attr( "spAttack" ) );
		}
		// ����U���̕⋋
		virtual bool SupplySpAttack()
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "supplySpAttack" )() );
		}

		// ���G��Ԕ���
		virtual bool IsBarriered() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "barriered" ) );
		}
		// ���G��ԃt���[���J�E���g�̎擾
		virtual unsigned GetBarrierCount() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "barrierCount" ) );
		}
		// ���G��Ԃ̐ݒ�
		virtual void SetBarrier( unsigned frameNum )
		{
			mPyObject.attr( "setBarrier" )( frameNum );
		}
		// �j���̏�����Ԕ���
		virtual bool IsDisappeared() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "disappeared" ) );
		}

		// ���݈ʒu�̎擾
		virtual Vector2DF GetPosition() const
		{
			return boost::python::extract<Vector2DF>( 
				mPyObject.attr( "position" ) );
		}
		// ���݈ʒu�̐ݒ�
		virtual void SetPosition( const Vector2DF &position )
		{
			mPyObject.attr( "position" ) = position;
		}
		// �O�͂̓K�p
		virtual Vector2DF ApplyExternalForce( const Vector2DF &vec )
		{
			return boost::python::extract<Vector2DF>( 
				mPyObject.attr( "applyExternalForce" )( vec ) );
		}

		// �c�@�̎擾
		virtual unsigned GetRemainder() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "remainder" ) );
		}
		// �c�@�̒ǉ�
		virtual void AddRemainder( unsigned num )
		{
			mPyObject.attr( "addRemainder" )( num );
		}
		// �����c�@���̐ݒ�
		virtual void SetInitRemainder( unsigned num )
		{
			mPyObject.attr( "setInitRemainder" )( num );
		}

		// �R���e�B�j���[���̏���
		virtual void Continue()
		{
			mPyObject.attr( "doContinue" )();
		}

		// �ړ��֎~�ݒ�
		virtual void SetMoveForbidFlag( bool flag )
		{
			mPyObject.attr( "setMoveForbidFlag" )( flag );
		}
		// �V���b�g�֎~�ݒ�
		virtual void SetShotForbidFlag( bool flag )
		{
			mPyObject.attr( "setShotForbidFlag" )( flag );
		}
		// ����U���֎~�ݒ�
		virtual void SetSpecialAttackForbidFlag( bool flag )
		{
			mPyObject.attr( "setSpecialAttackForbidFlag" )( flag );
		}

	private:
		boost::python::object mPyObject;
	};
}
}
}
}