#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/Auxs.h"
#include "Mdl/STG/Bullet/Base.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/Sprite/DrawParameter.h"
#include <bulletmlrunner.h>
#include "CreateParam.h"
#include <list>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Bullet
{
namespace BulletML
{
	class MLActor
		: public Base
		, public BulletMLRunner
	{
	public:
		// �R���X�g���N�^
		typedef Util::Ptr<BulletMLParser>::Shared PBMLParser;
		MLActor( PMode pMode, PBMLParser bp, 
			const Util::STG::Vector2DF &pos );
		MLActor( PMode pMode, PBMLParser bp, 
			const Util::STG::Locator::LinearF &locator, int hitRadius, 
			const Util::Sprite::DrawParameter &drawParam );

		// �ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec );

		// ���P�[�^�̎擾
		Util::STG::Locator::LinearF &GetLocator();
		// �`��p�����[�^�̎擾
		const Util::Sprite::DrawParameter &GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const Util::Sprite::DrawParameter &drawParam );
		// �����N�̎擾
		double GetRank() const;
		// �����N�̐ݒ�
		static const double DEFAULT_RANK;
		void SetRank( double rank = DEFAULT_RANK );
		// �e�������p�����[�^���X�g�̎擾
		typedef std::list<CreateParam> CreateParamList;
		CreateParamList &GetCreateParamList();

	private:
		Util::STG::Locator::LinearF mLocator;
		Util::Sprite::DrawParameter mDrawParam;
		Auxs mAuxs;
		double mRank;
		int mFrameCount;
		CreateParamList mCreateParamList;
		float mAngle;
		PBMLParser mpBMLParser;

		MLActor( PMode pMode, PBMLParser bp, BulletMLState *bs, 
			const Util::STG::Locator::LinearF &locator, int hitRadius, 
			const Util::Sprite::DrawParameter &drawParam, 
			const CreateParamList &createParamList, 
			float angle );

	protected:
		virtual void OnUpdate();
		virtual void OnDraw() const;
		virtual void OnDestruct();
		virtual void OnDestruct( float hp );
		virtual void OnErase();

	private:
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
		virtual void createSimpleBullet( double direction, double speed );
		/// action �����e�����
		virtual void createBullet( BulletMLState *state, 
			double direction, double speed );
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
}