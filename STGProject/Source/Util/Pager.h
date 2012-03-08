#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <vector>
#include <utility>


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Util
{
	template <class ElemType>
	class Pager
	{
	public:
		// �R���X�g���N�^
		Pager( unsigned pageSize )
			: mElems()
			, mPageSize( pageSize )
		{
			if( mPageSize == 0 )
			{
				mPageSize = 1;
			}
		}
		template <class Iterator>
		Pager( unsigned pageSize, Iterator begin, Iterator end )
			: mElems( begin, end )
			, mPageSize( pageSize )
		{
			if( mPageSize == 0 )
			{
				mPageSize = 1;
			}
		}

		// 1�y�[�W������̗v�f����ݒ肷��
		// 0�͐ݒ�ł��Ȃ�
		void SetPageSize( unsigned pageSize )
		{
			mPageSize = pageSize != 0 ? pageSize : 1;
		}

		// 1�y�[�W������̗v�f�����擾����
		unsigned GetPageSize() const
		{
			return mPageSize;
		}

		// ���y�[�W�����擾����
		std::size_t GetPageNum() const
		{
			std::size_t pageNum = mElems.size() / mPageSize;

			if( mElems.size() % mPageSize != 0 )
			{
				pageNum++;
			}

			return pageNum;
		}

		// �w�肵���y�[�W���擾����(�y�[�W�ԍ���0�N�Z)
		typedef typename std::vector<ElemType>::iterator ElemIterator;
		typedef std::pair<ElemIterator, ElemIterator> PageLocator;
		PageLocator GetPage( unsigned page )
		{
			unsigned pageBegin = page * mPageSize;
			if( pageBegin >= mElems.size() )
			{
				return PageLocator( mElems.end(), mElems.end() );
			}

			PageLocator itrPair;
			itrPair.first = mElems.begin() + pageBegin;

			itrPair.second = itrPair.first;
			for( unsigned i = 0; 
				itrPair.second != mElems.end() && i < mPageSize; 
				itrPair.second++, i++ );

			return itrPair;
		}
		typedef typename std::vector<ElemType>::const_iterator ConstElemIterator;
		typedef std::pair<ConstElemIterator, ConstElemIterator> ConstPageLocator;
		ConstPageLocator GetPage( unsigned page ) const
		{
			unsigned pageBegin = page * mPageSize;
			if( pageBegin >= mElems.size() )
			{
				return ConstPageLocator( mElems.end(), mElems.end() );
			}

			ConstPageLocator itrPair;
			itrPair.first = mElems.begin() + pageBegin;

			itrPair.second = itrPair.first;
			for( unsigned i = 0; 
				itrPair.second != mElems.end() && i < mPageSize; 
				itrPair.second++, i++ );

			return itrPair;
		}

		// �v�f�R���e�i�ւ̎Q�Ƃ��擾����
		typedef std::vector<ElemType> ElemCollection;
		ElemCollection &GetElemCollection()
		{
			return mElems;
		}
		const ElemCollection &GetElemCollection() const
		{
			return mElems;
		}

	private:
		std::vector<ElemType> mElems;
		unsigned mPageSize;
	};
}
}