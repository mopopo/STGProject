#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Util/Common.h"
#include <unordered_map>
#include <boost/any.hpp>
#include <vector>
#include "Exception/Duplicate.h"
#include "Exception/NotFound.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
namespace Resource
{
	// �q�[�v�ɍ쐬�����C���X�^���X�ɔC�ӂ̖��O��t���ĊǗ�����
	class Manager
	{
	public:
		// ���\�[�X�̒ǉ�
		// ���łɓ������O�̃��\�[�X�����݂���ꍇ�AResourceDuplicateException���X���[
		template <class ResourceType>
		static void Add( const std::wstring &name, std::tr1::shared_ptr<ResourceType> newPtr )
		{
			if( !IsExist( name ) )
			{
				mResourceMap[ name ] = boost::any( newPtr );
			}
			else
			{
				THROW( Resource::Exception::Duplicate( name ) );
			}
		}

		// �w��̃��\�[�X�����݂��邩�ǂ���
		static bool IsExist( const std::wstring &name )
		{
			return mResourceMap.find( name ) != mResourceMap.end();
		}

		// ���\�[�X�̎擾
		// ������Ȃ����ResourceNotFoundException���X���[�����
		template <class ResourceType>
		static std::tr1::shared_ptr<ResourceType> Get( const std::wstring &name )
		{
			if( !IsExist( name ) )
			{
				THROW( Resource::Exception::NotFound( name ) );
			}

			return boost::any_cast<std::tr1::shared_ptr<ResourceType>>( mResourceMap[ name ] );
		}

		// ���\�[�X���󂩂ǂ���
		static bool IsEmpty()
		{
			return mResourceMap.empty();
		}

		// ���\�[�X���폜����
		static bool Erase( const std::wstring &name )
		{
			if( IsExist( name ) )
			{
				mResourceMap.erase( name );

				return true;
			}
			else
			{
				return false;
			}
		}

		// ���\�[�X���N���A����
		static void Clear()
		{
			mResourceMap.clear();
		}

		// ���\�[�X�̈ꗗ���擾����
		static void GetList( std::vector<std::wstring> &resourceList )
		{
			resourceList.clear();

			typedef const std::pair<std::wstring, boost::any> rMapElem;
			foreach( rMapElem &resource, mResourceMap )
			{
				resourceList.push_back( resource.first );
			}
		}

	private:
		// ���\�[�X�̕ێ�
		// �L�[�͔C�ӂ̕�����
		static std::tr1::unordered_map<std::wstring, boost::any> mResourceMap;
	};
}
}
}