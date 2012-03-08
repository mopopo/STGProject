#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Mdl/STG/MyShip/IMyShip.h"
#include "Util/STG/Locator/Linear.h"
#include "Util/STG/Hit/Circle.h"


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
	class Base
		: public Game::Mdl::STG::MyShip::IMyShip
	{
	public:
		// �t���[�����̍X�V
		virtual void Update();
		// �t���[�����̕`��
		virtual void Draw() const;

		// �G�e�����蔻��
		virtual bool IsHit( const Game::Util::STG::Hit::CircleI &bulletHit ) const;
		// �A�C�e���z���񂹓����蔻��
		virtual bool IsHit_ItemRetrieve( 
			const Game::Util::STG::Hit::CircleI &itemHit ) const;
		// �A�C�e���擾�����蔻��
		virtual bool IsHit_GetItem( 
			const Game::Util::STG::Hit::CircleI &itemHit ) const;
		// ���@�̔j��
		virtual void Destruct();

		// ���G��Ԕ���
		virtual bool IsBarriered() const;
		// ���G��ԃt���[���J�E���g�̎擾
		virtual unsigned GetBarrierCount() const;
		// ���G��Ԃ̐ݒ�
		virtual void SetBarrier( unsigned frameNum );
		// �j���̏�����Ԕ���
		virtual bool IsDisappeared() const;

		// ���݈ʒu�̎擾
		virtual Game::Util::STG::Vector2DF GetPosition() const;
		// ���݈ʒu�̐ݒ�
		virtual void SetPosition( const Game::Util::STG::Vector2DF &position );
		// �O�͂̓K�p
		virtual Game::Util::STG::Vector2DF ApplyExternalForce( 
			const Game::Util::STG::Vector2DF &vec );

		// �c�@�̎擾
		virtual unsigned GetRemainder() const;
		// �c�@�̒ǉ�
		virtual void AddRemainder( unsigned num );
		// �����c�@���̐ݒ�
		virtual void SetInitRemainder( unsigned num );

		// �R���e�B�j���[���̏���
		virtual void Continue();

		// �ړ��֎~�ݒ�
		virtual void SetMoveForbidFlag( bool flag );
		// �V���b�g�֎~�ݒ�
		virtual void SetShotForbidFlag( bool flag );
		// ����U���֎~�ݒ�
		virtual void SetSpecialAttackForbidFlag( bool flag );

	protected:
		Base();

	private:
		Game::Util::STG::Locator::LinearF mLocator;

		Game::Util::STG::Hit::CircleI 
			mHitCircle, mItemRetrieveHitCircle, mItemHitCircle;

		unsigned mInitRemainder;
		unsigned mRemainder;

		unsigned mBarrierCount;
		unsigned mDisappearCount;

		bool mMoveForbidFlag;
		bool mShotForbidFlag;
		bool mSpecialAttackForbidFlag;

		// �X�V���̏���
		virtual void OnUpdate() = 0;
		// �`�掞�̏���
		virtual void OnDraw() const = 0;
		// ���@�j�󎞂̏���
		virtual void OnDestruction() = 0;
		// ���@�������̏���
		virtual void OnRevival() = 0;
		// �R���e�B�j���[���̏���
		virtual void OnContinue() = 0;

		// ���@�T�C�Y�̎擾
		virtual Game::Util::STG::Vector2DI GetShipSize() const = 0;

		// �ړ����x�̎擾
		virtual float GetMoveSpeed() const = 0;

		// �o���A���a�̎擾
		virtual int GetBarrierRadius() const = 0;
		// �A�C�e���z���񂹔��a�̎擾
		virtual int GetItemRetrieveRadius() const = 0;

		// �V���b�g���ˏ���
		virtual void Shot() = 0;
		// ����U����������
		virtual void SpecialAttack() = 0;

		void Input();
	};
}
}
}
}