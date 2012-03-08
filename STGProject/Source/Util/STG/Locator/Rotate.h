#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include "ILocator.h"


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Defs
{
namespace Util
{
	class LocatorObject;
}
}

namespace Game
{
namespace Util
{
namespace STG
{
namespace Locator
{
	template <class T>
	class Rotate
		: public ILocator<T>
	{
	public:
		Rotate()
			: mCenter()
			, mCenterSp()
			, mCenterAc()
			, mExForce()
			, mRadius()
			, mRadiusSp()
			, mRadiusAc()
			, mAngle()
			, mAngleSp()
			, mAngleAc()
		{}

		// ��Ԃ̍X�V
		virtual void Update()
		{
			mCenterSp += mCenterAc + mExForce;
			mCenter += mCenterSp;

			mRadiusSp += mRadiusAc;
			mRadius += mRadiusSp;

			mAngleSp += mAngleAc;
			mAngle += mAngleSp;

			mExForce.SetXY( 0, 0 );
		}


		// �ʒu�̎擾
		virtual Vector2D<T> GetPosition() const
		{
			Vector2D<T> pos;
			pos.SetUnitVector( static_cast<float>( mAngle ) );
			pos *= mRadius;
			pos += mCenter;

			return pos;
		}

		// �O�͂̓K�p
		virtual Vector2D<T> ApplyExternalForce( const Vector2D<T> &vec )
		{
			Vector2D<T> ret = mCenterAc + mExForce;

			mExForce += vec;

			return ret;
		}


		// ���S�ʒu�̎擾
		Vector2D<T> GetCenter() const
		{
			return mCenter;
		}
		void SetCenter( const Vector2D<T> &center )
		{
			mCenter = center;
		}
		Vector2D<T> &GetCenter()
		{
			return mCenter;
		}

		// ���S�ʒu�̈ړ����x�̎擾
		Vector2D<T> GetCenterSpeed() const
		{
			return mCenterSp;
		}
		void SetCenterSpeed( const Vector2D<T> &centerSp )
		{
			mCenterSp = centerSp;
		}
		Vector2D<T> &GetCenterSpeed()
		{
			return mCenterSp;
		}

		// ���S�ʒu�̈ړ������x�̎擾
		Vector2D<T> GetCenterAccel() const
		{
			return mCenterAc;
		}
		void SetCenterAccel( const Vector2D<T> &centerAc )
		{
			mCenterAc = centerAc;
		}
		Vector2D<T> &GetCenterAccel()
		{
			return mCenterAc;
		}

		// ���a�̎擾
		T GetRadius() const
		{
			return mRadius;
		}
		// ���a�̐ݒ�
		void SetRadius( T radius )
		{
			mRadius = radius;
		}

		// ���a�̑������x�̎擾
		T GetRadiusSpeed() const
		{
			return mRadiusSp;
		}
		// ���a�̑������x�̐ݒ�
		void SetRadiusSpeed( T speed )
		{
			mRadiusSp = speed;
		}

		// ���a�̑��������x�̎擾
		T GetRadiusAccel() const
		{
			return mRadiusAc;
		}
		// ���a�̑������x�̐ݒ�
		void SetRadiusAccel( T accel )
		{
			mRadiusAc = accel;
		}

		// �p�x�̎擾
		T GetAngle() const
		{
			return mAngle;
		}
		// �p�x�̐ݒ�
		void SetAngle( T angle )
		{
			mAngle = angle;
		}

		// �p���x�̎擾
		T GetAngleSpeed() const
		{
			return mAngleSp;
		}
		// �p���x�̐ݒ�
		void SetAngleSpeed( T speed )
		{
			mAngleSp = speed;
		}

		// �p�����x�̎擾
		T GetAngleAccel() const
		{
			return mAngleAc;
		}
		// �p�����x�̐ݒ�
		void SetAngleAccel( T accel )
		{
			mAngleAc = accel;
		}

	private:
		Vector2D<T> mCenter, mCenterSp, mCenterAc, mExForce;
		T mRadius, mRadiusSp, mRadiusAc;
		T mAngle, mAngleSp, mAngleAc;

		friend class ::Defs::Util::LocatorObject;
	};

	typedef Rotate<float> RotateF;
	typedef Rotate<Selene::Sint32> RotateI;
}
}
}
}