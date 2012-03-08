#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "Fwd.h"
#include <cfloat>
#include <set>
#include <vector>
#include "Util/STG/Vector2D.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace Ctrl
{
namespace STG
{
namespace Collision
{
	template <class PObject>
	class Node
	{
	public:
		Node()
			: mDirection( DIR_NONE )
			, mAreaRange()
			, mLeft( 0 )
			, mRight( 0 )
			, mIndexOffset( 0 )
			, mIndexNumber( 0 )
		{}

		void Build( 
			float xMin, float xMax, 
			float yMin, float yMax, 
			std::vector<PObject> &indexVector, 
			Node *pNodes, 
			int *pNodePos, 
			int restLevel 
			)
		{
			//�����ł͈�ԒP���ȕ��@�Ŋ���B
			//x,y�̒������Ŋ���̂��B
			float divLine; //������
			if ( ( xMax - xMin ) > ( yMax - yMin ) ){
				mDirection = DIR_X;
				divLine = ( xMin + xMax ) * 0.5f;

				// �̈�͈͂̐ݒ�
				mAreaRange.first = xMin;
				mAreaRange.second = xMax;
			}else{
				mDirection = DIR_Y;
				divLine = ( yMin + yMax ) * 0.5f;

				mAreaRange.first = yMin;
				mAreaRange.second = yMax;
			}

			//�����鏀��
			int leftCircleNum, rightCircleNum;
			//���E�m�[�h�Ɋ���U��I�u�W�F�N�g�̐�
			leftCircleNum = rightCircleNum = 0;

			//�q�m�[�h�m��
			mLeft = &pNodes[ *pNodePos + 0 ];
			mRight = &pNodes[ *pNodePos + 1 ];
			*pNodePos += 2;

			//��͕����ɉ����ĕ���
			if ( mDirection == DIR_X ){
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					// �ʒu�ō��E���肵�A�J�E���g
					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= xMin - FLT_EPSILON ){ 
						++leftCircleNum;
					}
					if ( pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= xMax + FLT_EPSILON ){ 
						++rightCircleNum;
					}
				}

				//�q�z��؂�o��
				mLeft->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), leftCircleNum, PObject() );
				mRight->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), rightCircleNum, PObject() );

				//���z
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= xMin - FLT_EPSILON ){
						indexVector[ 
							mLeft->mIndexOffset + mLeft->mIndexNumber 
						] = pObject;
						++mLeft->mIndexNumber;
					}
					if ( pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= xMax + FLT_EPSILON ){
						indexVector[ 
							mRight->mIndexOffset + mRight->mIndexNumber 
						] = pObject;
						++mRight->mIndexNumber;
					}
				}

				//�q�ɂ܂�����������Ȃ�(>0�łȂ����R���l���Ă݂悤)
				if ( restLevel > 1 ){
					if ( leftCircleNum > 1 ){ //2�ȏ�Ȃ��Ɗ���Ӗ��͂Ȃ�
						mLeft->Build( 
							xMin, divLine, 
							yMin, yMax, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
					if ( rightCircleNum > 1 ){
						mRight->Build( 
							divLine, xMax, 
							yMin, yMax, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
				}
			}
			else{
				int &topCircleNum = leftCircleNum;
				int &bottomCircleNum = rightCircleNum;

				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					// �ʒu�ŏ㉺���肵�A�J�E���g
					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= yMin - FLT_EPSILON ){ 
						++topCircleNum;
					}
					if ( pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= yMax + FLT_EPSILON ){ 
						++bottomCircleNum;
					}
				}

				//�q�z��؂�o��
				mLeft->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), topCircleNum, PObject() );
				mRight->mIndexOffset = static_cast<int>( indexVector.size() );
				indexVector.insert( indexVector.end(), bottomCircleNum, PObject() );

				//���z
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					PObject pObject = indexVector[ i ];
					Util::STG::Vector2DF pos = pObject->GetPosition();
					float r = pObject->GetHitRadius();

					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= yMin - FLT_EPSILON ){
						indexVector[ 
							mLeft->mIndexOffset + mLeft->mIndexNumber 
						] = pObject;
						++mLeft->mIndexNumber;
					}
					if ( pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= yMax + FLT_EPSILON ){
						indexVector[ 
							mRight->mIndexOffset + mRight->mIndexNumber 
						] = pObject;
						++mRight->mIndexNumber;
					}
				}

				//�q�ɂ܂�����������Ȃ�(>0�łȂ����R���l���Ă݂悤)
				if ( restLevel > 1 ){
					if ( topCircleNum > 1 ){ //2�ȏ�Ȃ��Ɗ���Ӗ��͂Ȃ�
						mLeft->Build( 
							xMin, xMax, 
							yMin, divLine, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
					if ( bottomCircleNum > 1 ){
						mRight->Build( 
							xMin, xMax, 
							divLine, yMax, 
							indexVector, 
							pNodes, 
							pNodePos, 
							restLevel - 1 );
					}
				}
			}

			//�����̔z��͗v��Ȃ��B�������J���͂ł��Ȃ��̂ŁA�ԈႢ���N����ʂ悤0�ɂ��Ă����B
			//�Ȃ��A��������̕����ōė��p����悤�ɃR�[�h���������Ƃ��o���A
			//��������ΑO�����Ċm�ۂ���z������Ȃ�Z���ł��邪�A���Ȃ蕡�G�ɂȂ�B
			mIndexOffset = 0;
			mIndexNumber = 0;
		}

		template <class Detector>
		PObject Detect( 
			const std::vector<PObject> &indexVector, 
			const Detector &detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
			, int *pTestCount = 0, 
			int *pHitCount = 0 
#endif
			) const
		{
			//�������Ȃ��C�R�[���������I�_�B
			if ( mDirection == DIR_NONE ){
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
					if( pTestCount ) { ++( *pTestCount ); }
#endif

					PObject pObject = indexVector[ i ];
					if ( detector.Detect( pObject ) ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
						if( pHitCount ) { ++( *pHitCount ); }
#endif

						return pObject;
					}
				}
			}
			//�q������̂Ŏq�ɓn���B
			else{
				Vector2DF pos = detector.GetPosition();
				float r = detector.GetRadius();
				float divLine = ( mAreaRange.first + mAreaRange.second ) * 0.5f;
				PObject result;

				if( mDirection == DIR_X )
				{
					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= mAreaRange.first - FLT_EPSILON ){
						result = mLeft->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							,  pTestCount, pHitCount 
#endif
							);
					}

					if ( !result && 
						pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= mAreaRange.second + FLT_EPSILON ){
						return mRight->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							, pTestCount, pHitCount 
#endif
							);
					}
					else
					{
						return result;
					}
				}
				else
				{
					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= mAreaRange.first - FLT_EPSILON ){
						result = mLeft->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							, pTestCount, pHitCount 
#endif
							);
						}

					if ( !result && 
						pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= mAreaRange.second + FLT_EPSILON ){
						return mRight->Detect( 
							indexVector, detector
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							, pTestCount, pHitCount 
#endif
							);
					}
					else
					{
						return result;
					}
				}
			}

			return PObject();
		}
		template <class Detector>
		void DetectAll( 
			const std::vector<PObject> &indexVector, 
			const Detector &detector, 
			std::set<PObject> &resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
			, int *pTestCount = 0, 
			int *pHitCount = 0 
#endif
			) const
		{
			//�������Ȃ��C�R�[���������I�_�B
			if ( mDirection == DIR_NONE ){
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
					if( pTestCount ) { ++( *pTestCount ); }
#endif

					PObject pObject = indexVector[ i ];
					if ( detector.Detect( pObject ) ){
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
						if( pHitCount ) { ++( *pHitCount ); }
#endif

						resultSet.insert( pObject );
					}
				}
			}
			//�q������̂Ŏq�ɓn���B
			else{
				Vector2DF pos = detector.GetPosition();
				float r = detector.GetRadius();
				float divLine = ( mAreaRange.first + mAreaRange.second ) * 0.5f;

				if( mDirection == DIR_X )
				{
					if ( pos.x - r <= divLine + FLT_EPSILON && 
						pos.x + r >= mAreaRange.first - FLT_EPSILON ){
						mLeft->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							);
					}
					if ( pos.x + r >= divLine - FLT_EPSILON && 
						pos.x - r <= mAreaRange.second + FLT_EPSILON ){
						mRight->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							 );
					}
				}
				else
				{
					if ( pos.y - r <= divLine + FLT_EPSILON && 
						pos.y + r >= mAreaRange.first - FLT_EPSILON ){
						mLeft->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							);
					}
					if ( pos.y + r >= divLine - FLT_EPSILON && 
						pos.y - r <= mAreaRange.second + FLT_EPSILON ){
						mRight->DetectAll( indexVector, detector, resultSet
#if defined(SLN_DEBUG) || defined(SLN_DEVELOP)
							 ,pTestCount, pHitCount 
#endif
							);
					}
				}
			}
		}

		void SetIndexOffset( int value ) { mIndexOffset = value; }
		void SetIndexNumber( int value ) { mIndexNumber = value; }
		void SetAreaRange( const std::pair<float, float> &range ) { mAreaRange = range; }

		void GetObjects( 
			const std::vector<PObject> &indexVector, std::set<PObject> &resultSet ) const
		{
			if( mDirection == DIR_NONE )
			{
				for ( int i = mIndexOffset; i < mIndexOffset + mIndexNumber; ++i ){
					resultSet.insert( indexVector[ i ] );
				}
			}
			else
			{
				mLeft->GetObjects( indexVector, resultSet );
				mRight->GetObjects( indexVector, resultSet );
			}
		}
	private:
		enum Direction
		{
			DIR_X, 
			DIR_Y, 
			DIR_NONE, 
		};

		Direction mDirection;
		std::pair<float, float> mAreaRange;
		Node *mLeft;
		Node *mRight;
		int mIndexOffset;
		int mIndexNumber;
	};
}
}
}
}