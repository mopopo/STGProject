#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "../Base.h"
#include "Resource.h"
#include "Util/Sprite/DrawParameter.h"
#include "Option.h"
#include <vector>
#include "Util/RepeatCounter.h"
#include "Mdl/STG/Auxs.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace MyShip
{
namespace TypeA
{
	class Core
		: public Base
	{
	public:
		Core( const Parameter &param );

		// ���̈�̕`��
		virtual void DrawInfArea( const Util::STG::Vector2DF &basePos ) const;

		// ����p���[�̎擾
		virtual int GetPower() const;
		// ����p���[�̏㏸
		virtual bool SupplyPower();
		// ����U���J�E���g�̎擾
		virtual int GetSpAttack() const;
		// ����U���̕⋋
		virtual bool SupplySpAttack();

	private:
		Resource mResource;
		Util::Sprite::DrawParameter mShipDParam;
		Util::Sprite::DrawParameter mHitMarkDParam;
		Util::Sprite::DrawParameter mBarrierDParam;

		unsigned mWeaponPowerCount;
		unsigned mSpAttackCount;

		std::vector<Option> mOptions;

		Util::RepeatCounter mLaserInterval;
		Util::RepeatCounter mMissileInterval;

		bool mSlow;

		Auxs mAuxs;

		// �X�V���̏���
		virtual void OnUpdate();
		// �`�掞�̏���
		virtual void OnDraw() const;
		// ���@�j�󎞂̏���
		virtual void OnDestruction();
		// ���@�������̏���
		virtual void OnRevival();
		// �R���e�B�j���[���̏���
		virtual void OnContinue();

		// ���@�T�C�Y�̎擾
		virtual Util::STG::Vector2DI GetShipSize() const;

		// �o���A���a�̎擾
		virtual int GetBarrierRadius() const;
		// �A�C�e���z���񂹔��a�̎擾
		virtual int GetItemRetrieveRadius() const;

		// �ړ����x�̎擾
		virtual float GetMoveSpeed() const;

		// �V���b�g���ˏ���
		virtual void Shot();
		// ����U����������
		virtual void SpecialAttack();

		void AddOption( unsigned num, float rotAngle = 0 );
	};
}
}
}
}
}