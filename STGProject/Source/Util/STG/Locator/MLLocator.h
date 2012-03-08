#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Linear.h"
#include <bulletmlrunner.h>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
	class LocatorObject;
}
}

namespace Game
{
namespace Util
{
namespace STG
{
namespace Locator
{
	class MLLocator
		: public ILocator<float>
		, public BulletMLRunner
	{
	public:
		// �R���X�g���N�^
		typedef Util::Ptr<BulletMLParser>::Shared PBMLParser;
		MLLocator( PBMLParser bp, const Vector2DF &pos, 
			Random::PRandom pRandom );

		// ��Ԃ̍X�V
		virtual void Update();

		// �ʒu�̎擾
		virtual Vector2DF GetPosition() const;
		Vector2DF &GetPosition();
		// �ʒu�̐ݒ�
		void SetPosition( const Vector2DF &pos );
		// ���x�x�N�g���̎擾
		Vector2DF GetSpeed() const;
		Vector2DF &GetSpeed();
		// ���x�x�N�g���̐ݒ�
		void SetSpeed( const Vector2DF &sp );
		// �����x�x�N�g���̎擾
		Vector2DF GetAccel() const;
		Vector2DF &GetAccel();
		// �����x�x�N�g���̐ݒ�
		void SetAccel( const Vector2DF &ac );
		// �O�͂̓K�p
		virtual Vector2DF ApplyExternalForce( const Vector2DF &vec );

		// ���s���I�����Ă��邩�ǂ���
		bool IsEnd() const;
		// �_���p�x�̎擾
		float GetAimAngle() const;
		// �_���p�x�̐ݒ�
		void SetAimAngle( float angle );
		// �����N�̎擾
		double GetRank() const;
		// �����N�̐ݒ�
		static const double DEFAULT_RANK;
		void SetRank( double rank );

	private:
		LinearF mLocator;
		PBMLParser mpBMLParser;
		double mRank;
		int mFrameCount;
		float mAngle;
		float mAimAngle;
		Random::PRandom mpRandom;
		bool mVanished;

		friend class ::Defs::Util::LocatorObject;

		/// ���̒e�̊p�x�����߂�
		// �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
		virtual double getBulletDirection();
		/// ���̒e���玩�@��_���p�x�����߂�
		// �p�x��x�P�ʂŁA����� 0 �Ŏ��v����ŕԂ�
		virtual double getAimDirection();
		/// ���̒e�̑��x�����߂�
		virtual double getBulletSpeed();
		/// �f�t�H���g�̑��x�����߂�
		virtual double getDefaultSpeed();
		/// �����N�����߂�
		// 0 ���� 1 �܂ł̎���
		virtual double getRank();
		/// action �������Ȃ��e�����
		virtual void createSimpleBullet( double direction, double speed ) {}
		/// action �����e�����
		virtual void createBullet( BulletMLState *state, 
			double direction, double speed ) { delete state; }
		/// �e�̊�ƂȂ�^�[���̒l��Ԃ��A�ʏ�̓t���[����
		virtual int getTurn();
		/// ����
		virtual void doVanish();
		/// �e�̕������w�肵�������ɕύX����
		virtual void doChangeDirection( double dir );
		/// �e�̑��x���w�肵���l�ɕύX����
		virtual void doChangeSpeed( double speed );
		/// accel �ɑ΂���C���^�[�t�F�C�X
		virtual void doAccelX( double accelX );
		virtual void doAccelY( double accelY );
		/// �e�̑����� X ����������Ԃ��܂�
		virtual double getBulletSpeedX();
		/// �e�̑����� Y ����������Ԃ��܂�
		virtual double getBulletSpeedY();
		/// ������Ԃ�
		virtual double getRand();
	};
}
}
}
}