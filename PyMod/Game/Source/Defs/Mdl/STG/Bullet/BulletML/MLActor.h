#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Defs/Mdl/STG/Bullet/Base.h"
#include "Util/STG/Locator/Linear.h"
#include <bulletmlrunner.h>
#include "CreateParam.h"
#include <list>
#include "Defs/Mdl/STG/Bullet/BulletDefs.h"


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
namespace BulletML
{
	class MLActor
		: public Base
		, public BulletMLRunner
	{
	public:
		// �R���X�g���N�^
		typedef Game::Util::Ptr<BulletMLParser>::Shared PBMLParser;
		typedef Game::Util::Sprite::DrawParameter DrawParameter;
		MLActor( PBMLParser bp, 
			const Game::Util::STG::Vector2DF &pos );
		MLActor( PBMLParser bp, 
			const Game::Util::STG::Locator::LinearF &locator, int hitRadius, 
			const DrawParameter &drawParam );

		// �ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// ���P�[�^�̎擾
		Game::Util::STG::Locator::LinearF &GetLocator();
		// �`��p�����[�^�̎擾
		const DrawParameter &GetDrawParameter() const;
		// �`��p�����[�^�̐ݒ�
		void SetDrawParameter( const DrawParameter &drawParam );
		// �����N�̎擾
		double GetRank() const;
		// �����N�̐ݒ�
		static const double DEFAULT_RANK;
		void SetRank( double rank );
		// �e�������p�����[�^���X�g�̎擾
		typedef std::list<CreateParam> CreateParamList;
		CreateParamList &GetCreateParamList();
		CreateParamList::iterator GetCreateParamListBegin() { return mCreateParamList.begin(); }
		CreateParamList::iterator GetCreateParamListEnd() { return mCreateParamList.end(); }
		void AddCreateParam( const CreateParam &param ) { mCreateParamList.push_back( param ); }

	private:
		Game::Util::STG::Locator::LinearF mLocator;
		DrawParameter mDrawParam;
		double mRank;
		int mFrameCount;
		CreateParamList mCreateParamList;
		float mAngle;
		PBMLParser mpBMLParser;

		MLActor( PBMLParser bp, BulletMLState *bs, 
			const Game::Util::STG::Locator::LinearF &locator, int hitRadius, 
			const DrawParameter &drawParam, 
			const CreateParamList &createParamList, 
			float angle );

		friend BulletDefs;

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