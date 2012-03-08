#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Util/STG/Vector2D.h"


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
	class IMyShip
	{
	public:
		// �t���[�����̍X�V
		virtual void Update() = 0;
		// �t���[�����̕`��
		virtual void Draw() const = 0;
		// ���̈�̕`��
		virtual void DrawInfArea( const Util::STG::Vector2DF &basePos ) const = 0;

		// �G�e�����蔻��
		virtual bool IsHit( const Util::STG::Hit::CircleI &bulletHit ) const = 0;
		// �A�C�e���z���񂹓����蔻��
		virtual bool IsHit_ItemRetrieve( const Util::STG::Hit::CircleI &itemhit ) const = 0;
		// �A�C�e���擾�����蔻��
		virtual bool IsHit_GetItem( const Util::STG::Hit::CircleI &itemHit ) const = 0;
		// ���@�̔j��
		virtual void Destruct() = 0;

		// ����p���[�̎擾
		virtual int GetPower() const = 0;
		// ����p���[�̏㏸
		virtual bool SupplyPower() = 0;
		// ����U���J�E���g�̎擾
		virtual int GetSpAttack() const = 0;
		// ����U���̕⋋
		virtual bool SupplySpAttack() = 0;

		// ���G��Ԕ���
		virtual bool IsBarriered() const = 0;
		// ���G��ԃt���[���J�E���g�̎擾
		virtual unsigned GetBarrierCount() const = 0;
		// ���G��Ԃ̐ݒ�
		virtual void SetBarrier( unsigned frameNum ) = 0;
		// �j���̏�����Ԕ���
		virtual bool IsDisappeared() const = 0;

		// ���݈ʒu�̎擾
		virtual Util::STG::Vector2DF GetPosition() const = 0;
		// ���݈ʒu�̐ݒ�
		virtual void SetPosition( const Util::STG::Vector2DF &position ) = 0;
		// �O�͂̓K�p
		virtual Util::STG::Vector2DF ApplyExternalForce( const Util::STG::Vector2DF &vec ) = 0;

		// �c�@�̎擾
		virtual unsigned GetRemainder() const = 0;
		// �c�@�̒ǉ�
		virtual void AddRemainder( unsigned num ) = 0;
		// �����c�@���̐ݒ�
		virtual void SetInitRemainder( unsigned num ) = 0;

		// �R���e�B�j���[���̏���
		virtual void Continue() = 0;

		// �ړ��֎~�ݒ�
		virtual void SetMoveForbidFlag( bool flag ) = 0;
		// �V���b�g�֎~�ݒ�
		virtual void SetShotForbidFlag( bool flag ) = 0;
		// ����U���֎~�ݒ�
		virtual void SetSpecialAttackForbidFlag( bool flag ) = 0;

		virtual ~IMyShip() {}
	};
}
}
}
}