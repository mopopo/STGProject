#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Ctrl/Scene/IScene.h"
#include <boost/noncopyable.hpp>
#include "Ctrl/STG/Mode/Conf/Regular.h"
#include "Ctrl/STG/Mode/Conf/Replay.h"
#include "Ctrl/STG/Mode/Conf/StageSelect.h"
#include "Ctrl/STG/Python/ISTG.h"
#include "Util/Delegate/Delegate.h"
#include <boost/variant.hpp>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace Scene
{
namespace STG
{
	class STG
		: public IScene
		, public boost::noncopyable
	{
	public:
		// 1�t���[�����̏�ԍX�V
		virtual void UpdateState();

		// �R���X�g���N�^
		STG( const Ctrl::STG::Mode::Conf::Regular &conf );
		STG( const Ctrl::STG::Mode::Conf::Replay &conf );
		STG( const Ctrl::STG::Mode::Conf::StageSelect &conf );
		// �f�X�g���N�^
		~STG();

		// ���ʃ��\�[�X�̎擾
		typedef Util::Ptr<Mdl::STG::Resource::Common>::Shared PResource;
		PResource GetResource() const;

		// �\�����̎擾
		typedef boost::variant<int, 
			Ctrl::STG::Mode::Conf::Regular, 
			Ctrl::STG::Mode::Conf::Replay, 
			Ctrl::STG::Mode::Conf::StageSelect> STGConf;
		enum CONF_TYPE
		{
			CONF_EMPTY, 

			CONF_REGULAR, 
			CONF_REPLAY, 
			CONF_STAGESELECT, 
		};
		const STGConf GetConf() const;

		// �R���e�B�j���[�p�|�[�Y��ʂ̋N��
		void PauseForContinue();

		Util::Delegate::Delegate0<> GetDrawDelegate();

	private:
		// STG��ʂ̋��ʃ��\�[�X
		PResource mpResource;

		typedef Util::Ptr<Ctrl::STG::Python::ISTG>::Shared PPyInterface;
		PPyInterface mpPyInterface;

		typedef Util::Ptr<Ctrl::STG::Mode::IMode>::Shared PMode;
		PMode mpMode;

		bool mFadeFlag;

		// �\�����
		STGConf mConf;
		// �|�[�Y��ʋN���pStageSetID
		int mStageSetId;

		void Init();
		// �`��
		void Draw();

		void Pause( bool continuing = false );
	};
}
}
}
}