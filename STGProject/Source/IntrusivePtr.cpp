#include "PCH.h"


// intrusive_ptr�̎Q�ƃJ�E���^����p�֐�
void intrusive_ptr_add_ref( Selene::Interface *p )
{
	SAFE_ADDREF( p );
}
void intrusive_ptr_release( Selene::Interface *p )
{
	SAFE_RELEASE( p );
}