#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/python.hpp>
#include <bulletmlrunner.h>
#include "Fwd.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
namespace BulletML
{
	class RunnerHandler
		: public BulletMLRunner
	{
	public:
		typedef Game::Util::Ptr<BulletMLParser>::Shared PParser;
		explicit RunnerHandler( const boost::python::object &object, 
			PParser pParser )
			: BulletMLRunner( pParser.get() )
			, mPyObject( object )
			, mpParser( pParser )
		{}
		explicit RunnerHandler( const boost::python::object &object, 
			PParser pParser, BulletMLState *state )
			: BulletMLRunner( state )
			, mPyObject( object )
			, mpParser( pParser )
		{}

		PParser getParser() const
		{
			return mpParser;
		}

		// ----- ��Ύ������Ȃ���΂Ȃ�Ȃ��֐��Q�̎n�܂� -----
		//@{
		/// ���̒e�̊p�x�����߂�
		/**
		 * @return �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
		 */
		virtual double getBulletDirection()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletDirection" )() );
		}
		/// ���̒e���玩�@��_���p�x�����߂�
		/**
		 * @return �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
		 */
		virtual double getAimDirection()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getAimDirection" )() );
		}
		/// ���̒e�̑��x�����߂�
		virtual double getBulletSpeed()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletSpeed" )() );
		}
		/// �f�t�H���g�̑��x�����߂�
		virtual double getDefaultSpeed()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getDefaultSpeed" )() );
		}
		/// �����N�����߂�
		/**
		 * @return 0 ���� 1 �܂ł̎���
		 */
		virtual double getRank()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getRank" )() );
		}
		/// action �������Ȃ��e�����
		virtual void createSimpleBullet(double direction, double speed)
		{
			mPyObject.attr( "createSimpleBullet" )( direction, speed );
		}
		/// action �����e�����
		/**
		 * @param state
		 * �V�����e�� BulletMLRunner �̃R���X�g���N�^�ɓn�����ƁB
		 * �����n���Ȃ��̂ł���΁Adelete �ŉ�����Ȃ���΂Ȃ�Ȃ��B
		 */
		virtual void createBullet(BulletMLState* state,
										   double direction, double speed)
		{
			mPyObject.attr( "createBullet" )( state, direction, speed );
		}
		/// �e�̊�ƂȂ�^�[���̒l��Ԃ��A�ʏ�̓t���[����
		/**
		 * @return
		 * �Q�[�����Ƃ̊�ŃI�[�_�[�͕ύX���č\���܂��񂪁A
		 * �����͋�����܂���B
		 * xml �f�[�^��ŁAwait �� term �̃I�[�_�[�������Ă���Ζ�肠��܂���B
		 */
		virtual int getTurn()
		{
			return boost::python::extract<int>( 
				mPyObject.attr( "getTurn" )() );
		}
		/// ����
		virtual void doVanish()
		{
			mPyObject.attr( "doVanish" )();
		}
		//@}
		// ----- ��Ύ������Ȃ���΂Ȃ�Ȃ��֐��Q�̏I��� -----

		// ----- �K�v������Ύ�������֐��Q�̎n�܂� -----
		//@{
		/// �e�̕������w�肵�������ɕύX����
		virtual void doChangeDirection( double direction )
		{
			mPyObject.attr( "doChangeDirection" )( direction );
		}
		/// �e�̑��x���w�肵���l�ɕύX����
		virtual void doChangeSpeed( double speed )
		{
			mPyObject.attr( "doChangeSpeed" )( speed );
		}
		/// accel �ɑ΂���C���^�[�t�F�C�X
		/**
		 * @todo
		 * horizontal, vertical �� type �͖������ł��B
		 * �ǂ�� absolute �ɂȂ��Ă��܂��܂��B
		 */
		virtual void doAccelX( double accelX )
		{
			mPyObject.attr( "doAccelX" )( accelX );
		}
		/// accel �ɑ΂���C���^�[�t�F�C�X
		/**
		 * @todo
		 * horizontal, vertical �� type �͖������ł��B
		 * �ǂ�� absolute �ɂȂ��Ă��܂��܂��B
		 */
		virtual void doAccelY( double accelY )
		{
			mPyObject.attr( "doAccelY" )( accelY );
		}
		/// �e�̑����� X ����������Ԃ��܂�
		/**
		 * accel ���g���ꍇ�̓I�[�o�[���C�h���ĉ�����
		 */
		virtual double getBulletSpeedX()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletSpeedX" )() );
		}
		/// �e�̑����� Y ����������Ԃ��܂�
		/**
		 * accel ���g���ꍇ�̓I�[�o�[���C�h���ĉ�����
		 */
		virtual double getBulletSpeedY()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getBulletSpeedY" )() );
		}
		//@}
		// ----- �K�v������Ύ�������֐��Q�̏I��� -----

		/// ������Ԃ�
		/**
		 * ���Ă̂Ƃ���A�f�t�H���g�ł� std::rand ���p�����܂��B
		 */
		virtual double getRand()
		{
			return boost::python::extract<double>( 
				mPyObject.attr( "getRand" )() );
		}

	private:
		boost::python::object mPyObject;
		PParser mpParser;
	};
}
}
}