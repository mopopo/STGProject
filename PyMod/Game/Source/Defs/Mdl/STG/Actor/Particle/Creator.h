#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Parameter.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
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
		// �R���X�g���N�^
		Creator( const Parameter &param );

		// �p�����[�^�̎擾
		Parameter GetParameter() const;
		// �p�����[�^�̐ݒ�
		void SetParameter( const Parameter &param );

		// �p�[�e�B�N������
		void Create( unsigned num ) const;

	private:
		Parameter mParam;
	};
}
}
}
}
}