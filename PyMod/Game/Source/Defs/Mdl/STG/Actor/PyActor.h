#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include "Mdl/STG/Actor/IActor.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
	class PyActor
		: virtual public Game::Mdl::STG::Actor::IActor
	{
	public:
		PyActor( const boost::python::object &object )
			: mPyObject( object )
		{}

		// ��ӂȐ����l���擾
		virtual Selene::Uint64 GetId() const
		{
			return boost::python::extract<Selene::Uint64>( 
				mPyObject.attr( "objectId" ) );
		}

		// �X�V
		virtual void Update()
		{
			mPyObject.attr( "update" )();
		}
		// �`��
		virtual void Draw() const
		{
			mPyObject.attr( "draw" )();
		}

		// �L���t���O�̎擾
		virtual bool IsValid() const
		{
			return boost::python::extract<bool>( 
				mPyObject.attr( "valid" ) );
		}
		// �L���t���O�̐ݒ�
		virtual void SetValid( bool flag )
		{
			mPyObject.attr( "valid" ) = flag;
		}

		// ����
		virtual void Erase()
		{
			mPyObject.attr( "erase" )();
		}

		// �ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const
		{
			return boost::python::extract<Game::Util::STG::Vector2DF>( 
				mPyObject.attr( "position" ) );
		}
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( const Game::Util::STG::Vector2DF &vec )
		{
			return boost::python::extract<Game::Util::STG::Vector2DF>( 
				mPyObject.attr( "applyExternalForce" )( vec ) );
		}
		// �L���̈攻��̎擾
		virtual Game::Util::STG::Hit::RectI GetValidRect() const
		{
			return boost::python::extract<Game::Util::STG::Hit::RectI>( 
				mPyObject.attr( "validRect" ) );
		}
		// �L���̈攻��̐ݒ�
		virtual void SetValidRect( const Game::Util::STG::Hit::RectI &rect )
		{
			mPyObject.attr( "validRect" ) = rect;
		}
		// �L���̈�̗]���̐ݒ�
		virtual void SetValidAreaMargin( int margin )
		{
			mPyObject.attr( "setValidAreaMargin" )( margin );
		}
		// ���݂̃t���[���J�E���g���擾
		virtual unsigned GetFrameCount() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "frameCount" ) );
		}
		// ���݂̃t���[���J�E���g��ݒ�
		virtual void SetFrameCount( unsigned count )
		{
			mPyObject.attr( "frameCount" ) = count;
		}
		// �L������t���[���J�E���g�̎擾
		virtual unsigned GetValidFrameNum() const
		{
			return boost::python::extract<unsigned>( 
				mPyObject.attr( "validFrameNum" ) );
		}
		// �L������t���[���J�E���g�̐ݒ�
		virtual void SetValidFrameNum( unsigned frameNum )
		{
			mPyObject.attr( "validFrameNum" )( frameNum );
		}

	protected:
		boost::python::object mPyObject;
	};
}
}
}
}