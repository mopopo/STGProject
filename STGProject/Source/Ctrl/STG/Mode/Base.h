#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "IMode.h"
#include <boost/noncopyable.hpp>
#include "Conf/Holder.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Mode
{
	class Base
		: public IMode
		, public boost::noncopyable
	{
	public:
		// �t���[�����̍X�V
		virtual void Update();
		// �t���[�����̕`��
		virtual void Draw() const;

		// �V�[���̎擾
		virtual PScene GetScene() const;
		// ���݂̃X�e�[�W�f�[�^�̎擾
		virtual const StageData &GetCurrentStageData() const;
		// STG�\���I�u�W�F�N�g�̎擾
		virtual Actors &GetActors();
		virtual const Actors &GetActors() const;
		// �R���g���[���̎擾
		virtual PController GetController() const;
		// �f�o�b�O��񕶎���\���t���O�̎擾
		virtual bool GetDebugStrFlag() const;
		// �f�o�b�O��񕶎���\���t���O�̐ݒ�
		virtual void SetDebugStrFlag( bool flag );
		// �I�u�W�F�N�g�p�̈�ӂȐ����l�̐���
		virtual Selene::Uint64 GenObjectId();

	protected:
		// �R���X�g���N�^
		typedef Configuration::Data::StageSet::Id StageSetId;
		Base( PScene pScene, StageSetId stageSetId );

		// STG��ʂ��I�����A�^�C�g����ʂ֑J�ڂ���
		void End() const;

		// �\���Ǘ��I�u�W�F�N�g�̎擾
		Conf::Holder &GetConfHolder();
		// �R���g���[���̐ݒ�
		void SetController( PController pController );

	private:
		Selene::Uint64 mObjectIdCount;
		PScene mpScene;
		Conf::Holder mConfHolder;
		PController mpController;
		unsigned mContinueWaitCount;
		bool mContinueFlag;
		bool mDebugStrFlag;
		bool mPrevMyShipDisappear;

		// �X�V���̏���
		virtual void OnUpdate() = 0;
		// �`�掞�̏���
		virtual void OnDraw() const = 0;

		// �^�C�g����ʂ֑J��
		void ToTitle() const;
	};
}
}
}
}