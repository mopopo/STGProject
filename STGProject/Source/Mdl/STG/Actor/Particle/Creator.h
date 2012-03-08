#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include "Parameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Mdl
{
namespace STG
{
namespace Actor
{
namespace Particle
{
	class Creator
	{
	public:
		typedef Ctrl::STG::Mode::IMode *PMode;

		// �R���X�g���N�^
		Creator( PMode pMode, const Parameter &param = Parameter() );

		// �p�����[�^�̎擾
		const Parameter &GetParameter() const;
		// �p�����[�^�̐ݒ�
		void SetParameter( const Parameter &param );

		// �p�[�e�B�N������
		void Create( unsigned num ) const;
		void Create( unsigned num, const Parameter &param ) const;

	private:
		PMode mpMode;
		Parameter mParam;
	};
}
}
}
}
}