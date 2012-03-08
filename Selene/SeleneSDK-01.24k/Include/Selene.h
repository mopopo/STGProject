#pragma once
#ifdef __cplusplus_cli
#pragma managed( push, off )
#endif
#include <windows.h>
#include <xmmintrin.h>
#include <string>
#include <vector>
#include <map>
/**
	@file
	@brief ���ʒ�`
	@author �t���`
*/


//-----------------------------------------------------------------------------------
// WARNING
//-----------------------------------------------------------------------------------
#pragma inline_depth ( 16 )
#pragma inline_recursion ( on )

#pragma warning ( disable : 4201 )
#pragma warning ( disable : 4995 )

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// LIBRARY
//-----------------------------------------------------------------------------------
#pragma comment( lib, "ole32.lib" )
#pragma comment( lib, "gdi32.lib" )
#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "comdlg32.lib" )
#pragma comment( lib, "advapi32.lib" )
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "shell32.lib" )

//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#define OFFSET_OF(Class,Value)				static_cast<Uint16>(offsetof(Class,Value))						///< �\���̃I�t�Z�b�g
#define toF(val)							(static_cast<float>(val))										///< float�ւ̃L���X�g
#define toI(val)							(static_cast<Sint32>(val))										///< int�ւ̃L���X�g
#define REV(val)							(1.0f/toF(val))													///< �t���Z�o�}�N��

#define SAFE_ADDREF(val)					if ( (val) != NULL ) { (val)->AddRef(); }						///< COM���SAddRef�}�N��
#define SAFE_RELEASE(val)					if ( (val) != NULL ) { (val)->Release(); (val) = NULL; }		///< COM���SRelease�}�N��
#define SAFE_DELETE(val)					if ( (val) != NULL ) { delete (val); (val) = NULL; }			///< new���������S���
#define SAFE_DELETE_ARRAY(val)				if ( (val) != NULL ) { delete [] (val); (val) = NULL; }			///< new[]���������S���

#define V_ALLOC(size)						VirtualAlloc( NULL, size, MEM_COMMIT, PAGE_READWRITE )
#define V_FREE(pointer)						if ( (pointer) != NULL ) { VirtualFree( pointer, 0, MEM_RELEASE ); (pointer) = NULL; }

//-----------------------------------------------------------------------------------
// DEFINE
//-----------------------------------------------------------------------------------
#if defined(SLN_DEBUG)

#define SLN_ABORT()			(*((int*)0x0) = 0x0)
#define SLN_PRINT( ... )	printf( __VA_ARGS__ )

#define SLN_ERROR(msg)															\
{																				\
	char __error_msg__[1024] = "";												\
	sprintf_s(																	\
		__error_msg__,															\
		sizeof(__error_msg__),													\
		"FILE: %s\nLINE: %d\nMESSAGE: %s\n",									\
		__FILE__, __LINE__, msg );												\
	printf( __error_msg__ );													\
	MessageBoxA( ::GetActiveWindow(), __error_msg__, "ERROR", MB_ICONSTOP );	\
	SLN_ABORT();																\
}

#define SLN_ASSERT(flag,msg)														\
{																					\
	if ( !(flag) )																	\
	{																				\
		char __error_msg__[1024] = "";												\
		sprintf_s(																	\
			__error_msg__,															\
			sizeof(__error_msg__),													\
			"FILE: %s\nLINE: %d\nERROR: %s\nMESSAGE: %s\n",							\
			__FILE__, __LINE__, #flag, msg );										\
		printf( __error_msg__ );													\
		MessageBoxA( ::GetActiveWindow(), __error_msg__, "ERROR", MB_ICONSTOP );	\
		SLN_ABORT();																\
	}																				\
}

#else // SLN_DEBUG

#define SLN_ABORT()
#define SLN_PRINT( ... )
#define SLN_ERROR(msg)
#define SLN_ASSERT(flag,msg)

#endif

#define SLN_ERR_MSG( ... )															\
{																					\
	char __title__[512] = "";														\
	sprintf_s( __title__, 512, "%s (line %u)", __FILE__, __LINE__ );				\
	MessageBoxW(																	\
		GetActiveWindow(),															\
		Kernel::String::Utility::Format( __VA_ARGS__ ).c_str(),						\
		Kernel::String::Utility::ToWide( __title__ ).c_str(),						\
		MB_ICONSTOP );																\
	SLN_ABORT();																	\
}

#define SLN_STDCALL		__stdcall
#define SLN_CDECL		__cdecl

//-----------------------------------------------------------------------------------
// TYPEDEF
//-----------------------------------------------------------------------------------
namespace Selene
{
	typedef char					Sint8;					///< signed char �^�̕ʒ�`
	typedef short					Sint16;					///< signed short �^�̕ʒ�`
	typedef long					Sint32;					///< signed long �^�̕ʒ�`
	typedef long long				Sint64;					///< signed long �^�̕ʒ�`
	typedef unsigned char			Uint8;					///< unsigned char �^�̕ʒ�`
	typedef unsigned short			Uint16;					///< unsigned short �^�̕ʒ�`
	typedef unsigned long			Uint32;					///< unsigned long �^�̕ʒ�`
	typedef unsigned long long		Uint64;					///< unsigned long long �^�̕ʒ�`
	typedef __m128					Uint128;				///< __m128 �^�̕ʒ�`

	static const Uint32 JOYSTICK_BUTTON_MAX				= 32;
	static const Uint32 JOYSTICK_AXIS_MAX				= (((3 * 2) + 1) * 4) + 2;
	static const Uint32 JOYSTICK_VIRTUAL_BUTTON_MAX		= JOYSTICK_BUTTON_MAX + (JOYSTICK_AXIS_MAX * 2);
	static const float PI								= 3.141592653589793238462643383279f;				///< ��
	static const float PI2								= 6.283185307179586476925286766559f;				///< 2��
	static const float PI_INV							= 1.0f / PI;										///< 1.0 / ��
	static const float PI2_INV							= 1.0f / PI2;										///< 1.0 / 2��

	/**
		@brief �Q�������W
		@author �t���b
		@note �Q�����̍��W�������N���X
	*/
	template <typename T>
	class Point2D
	{
	public:
		T x;		///< X���W
		T y;		///< Y���W

	public:
		Point2D()
			: x	( 0 )
			, y	( 0 )
		{
		}

		Point2D( const Point2D<T>& In )
			: x	( In.x )
			, y	( In.y )
		{
		}

		template <typename U>
		Point2D( const Point2D<U>& In )
			: x	( static_cast<T>(In.x) )
			, y	( static_cast<T>(In.y) )
		{
		}

		Point2D( T _x, T _y )
			: x	( _x )
			, y	( _y )
		{
		}

		template <typename U>
		Point2D<T> operator + ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x + static_cast<T>(In.x);
			Out.y = y + static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T> operator - ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x - static_cast<T>(In.x);
			Out.y = y - static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T> operator * ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x * static_cast<T>(In.x);
			Out.y = y * static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T> operator / ( const Point2D<U>& In ) const
		{
			Point2D<T> Out;
			Out.x = x / static_cast<T>(In.x);
			Out.y = y / static_cast<T>(In.y);
			return Out;
		}

		template <typename U>
		Point2D<T>& operator += ( const Point2D<U>& In )
		{
			x += static_cast<T>(In.x);
			y += static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator -= ( const Point2D<U>& In )
		{
			x -= static_cast<T>(In.x);
			y -= static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator *= ( const Point2D<U>& In )
		{
			x *= static_cast<T>(In.x);
			y *= static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator /= ( const Point2D<U>& In )
		{
			x /= static_cast<T>(In.x);
			y /= static_cast<T>(In.y);
			return *this;
		}

		template <typename U>
		Point2D<T> operator + ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x + static_cast<T>(In);
			Out.y = y + static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T> operator - ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x - static_cast<T>(In);
			Out.y = y - static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T> operator * ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x * static_cast<T>(In);
			Out.y = y * static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T> operator / ( U In ) const
		{
			Point2D<T> Out;
			Out.x = x / static_cast<T>(In);
			Out.y = y / static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point2D<T>& operator += ( U In )
		{
			x += static_cast<T>(In);
			y += static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator -= ( U In )
		{
			x -= static_cast<T>(In);
			y -= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator *= ( U In )
		{
			x *= static_cast<T>(In);
			y *= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator /= ( U In )
		{
			x /= static_cast<T>(In);
			y /= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point2D<T>& operator = ( const Point2D<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			return *this;
		}

		Point2D<T> LimitLength( float Limit ) const
		{
			float _x = static_cast<float>(x);
			float _y = static_cast<float>(y);
			float Length = sqrtf( (_x * _x) + (_y * _y) );
			if ( Length > Limit )
			{
				float Div = Limit / Length;
				_x *= Div;
				_y *= Div;
			}
			return Point2D<T>( static_cast<T>(_x), static_cast<T>(_y) );
		}

		Point2D<T> Normalize() const
		{
			return LimitLength( 1.0f );
		}
	};

	template <typename T>
	inline bool operator == ( const Point2D<T>& lhs, const Point2D<T>& rhs )
	{
		if ( lhs.x != rhs.x ) return false;
		if ( lhs.y != rhs.y ) return false;
		return true;
	}
	template <typename T>
	inline bool operator != ( const Point2D<T>& lhs, const Point2D<T>& rhs )
	{
		return !(lhs == rhs);
	}

	typedef Point2D<float>	Point2DF;
	typedef Point2D<Sint32>	Point2DI;

	/**
		@brief �R�������W
		@author �t���b
		@note �R�����̍��W�������N���X
	*/
	template <typename T>
	class Point3D
	{
	public:
		T x;		///< X���W
		T y;		///< Y���W
		T z;		///< Z���W

	public:
		Point3D()
			: x	( 0 )
			, y	( 0 )
			, z	( 0 )
		{
		}

		Point3D( const Point3D<T>& In )
			: x	( In.x )
			, y	( In.y )
			, z	( In.z )
		{
		}

		template <typename U>
		Point3D( const Point3D<U>& In )
			: x	( static_cast<T>(In.x) )
			, y	( static_cast<T>(In.y) )
			, z	( static_cast<T>(In.z) )
		{
		}

		Point3D( T _x, T _y, T _z )
			: x	( _x )
			, y	( _y )
			, z	( _z )
		{
		}

		template <typename U>
		Point3D<T> operator + ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x + static_cast<T>(In.x);
			Out.y = y + static_cast<T>(In.y);
			Out.z = z + static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T> operator - ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x - static_cast<T>(In.x);
			Out.y = y - static_cast<T>(In.y);
			Out.z = z - static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T> operator * ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x * static_cast<T>(In.x);
			Out.y = y * static_cast<T>(In.y);
			Out.z = z * static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T> operator / ( const Point3D<U>& In ) const
		{
			Point3D<T> Out;
			Out.x = x / static_cast<T>(In.x);
			Out.y = y / static_cast<T>(In.y);
			Out.z = z / static_cast<T>(In.z);
			return Out;
		}

		template <typename U>
		Point3D<T>& operator += ( const Point3D<U>& In )
		{
			x += static_cast<T>(In.x);
			y += static_cast<T>(In.y);
			z += static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator -= ( const Point3D<U>& In )
		{
			x -= static_cast<T>(In.x);
			y -= static_cast<T>(In.y);
			z -= static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator *= ( const Point3D<U>& In )
		{
			x *= static_cast<T>(In.x);
			y *= static_cast<T>(In.y);
			z *= static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator /= ( const Point3D<U>& In )
		{
			x /= static_cast<T>(In.x);
			y /= static_cast<T>(In.y);
			z /= static_cast<T>(In.z);
			return *this;
		}

		template <typename U>
		Point3D<T> operator + ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x + static_cast<T>(In);
			Out.y = y + static_cast<T>(In);
			Out.z = z + static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T> operator - ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x - static_cast<T>(In);
			Out.y = y - static_cast<T>(In);
			Out.z = z - static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T> operator * ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x * static_cast<T>(In);
			Out.y = y * static_cast<T>(In);
			Out.z = z * static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T> operator / ( const U In ) const
		{
			Point3D<T> Out;
			Out.x = x / static_cast<T>(In);
			Out.y = y / static_cast<T>(In);
			Out.z = z / static_cast<T>(In);
			return Out;
		}

		template <typename U>
		Point3D<T>& operator += ( const U In )
		{
			x += static_cast<T>(In);
			y += static_cast<T>(In);
			z += static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator -= ( const U In )
		{
			x -= static_cast<T>(In);
			y -= static_cast<T>(In);
			z -= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator *= ( const U In )
		{
			x *= static_cast<T>(In);
			y *= static_cast<T>(In);
			z *= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator /= ( const U In )
		{
			x /= static_cast<T>(In);
			y /= static_cast<T>(In);
			z /= static_cast<T>(In);
			return *this;
		}

		template <typename U>
		Point3D<T>& operator = ( const Point3D<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			z = static_cast<T>(In.z);
			return *this;
		}
	};

	template <typename T>
	inline bool operator == ( const Point3D<T>& lhs, const Point3D<T>& rhs )
	{
		if ( lhs.x != rhs.x ) return false;
		if ( lhs.y != rhs.y ) return false;
		if ( lhs.z != rhs.z ) return false;
		return true;
	}
	template <typename T>
	inline bool operator != ( const Point3D<T>& lhs, const Point3D<T>& rhs )
	{
		return !(lhs == rhs);
	}

	typedef Point3D<float>	Point3DF;
	typedef Point3D<Sint32>	Point3DI;

	/**
		@brief ��`��`
		@author �t���b
		@note ��`�̒�`
	*/
	template <typename T>
	class Rect
	{
	public:
		T	x;		///< X�ʒu
		T	y;		///< Y�ʒu
		T	w;		///< X��
		T	h;		///< Y��

	public:
		Rect()
			: x	( 0 )
			, y	( 0 )
			, w	( 0 )
			, h	( 0 )
		{
		}

		Rect( const Rect<T>& In )
			: x	( In.x )
			, y	( In.y )
			, w	( In.w )
			, h	( In.h )
		{
		}

		Rect( T _x, T _y, T _w, T _h )
			: x	( _x )
			, y	( _y )
			, w	( _w )
			, h	( _h )
		{
		}

		Point2D<T> Position() const
		{
			return Point2D<T>( x, y );
		}

		Point2D<T> LocalPosition( const Point2D<T>& Position ) const
		{
			return Point2D<T>( Position.x - x, Position.y - y );
		}

		Point2D<T> Size() const
		{
			return Point2D<T>( w, h );
		}

		Rect<T> Clip( const Rect<T>& In ) const
		{
			T sx1 = In.x;
			T sy1 = In.y;
			T sx2 = In.x + In.w;
			T sy2 = In.y + In.h;

			T dx1 = this->x;
			T dy1 = this->y;
			T dx2 = this->x + this->w;
			T dy2 = this->y + this->h;

			if ( dx1 < sx1 ) dx1 = sx1;
			if ( dy1 < sy1 ) dy1 = sy1;
			if ( dx2 > sx2 ) dx2 = sx2;
			if ( dy2 > sy2 ) dy2 = sy2;

			T x = dx1;
			T y = dy1;
			T w = dx2 - dx1;
			T h = dy2 - dy1;
			if ( x < 0 ) x = 0;
			if ( y < 0 ) y = 0;
			if ( w < 0 ) w = 0;
			if ( h < 0 ) h = 0;

			return Rect<T>( x, y, w, h );
		}

		bool CheckHit( const Point2D<T>& In ) const
		{
			if ( In.x < x ) return false;
			if ( In.y < y ) return false;
			if ( In.x > x + w ) return false;
			if ( In.y > y + h ) return false;

			return true;
		}

		template <typename U>
		Rect<T> ScaleByCenter( U In ) const
		{
			return Rect<T>(
				static_cast<T>(static_cast<U>(x) - In),
				static_cast<T>(static_cast<U>(y) - In),
				static_cast<T>(static_cast<U>(w) + In * 2),
				static_cast<T>(static_cast<U>(h) + In * 2) );
		}

		template <typename U>
		Rect( const Rect<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			w = static_cast<T>(In.w);
			h = static_cast<T>(In.h);
		}

		template <typename U>
		Rect<T>& operator = ( const Rect<U>& In )
		{
			x = static_cast<T>(In.x);
			y = static_cast<T>(In.y);
			w = static_cast<T>(In.w);
			h = static_cast<T>(In.h);
			return *this;
		}
	};

	template <typename T>
	inline bool operator == ( const Rect<T>& lhs, const Rect<T>& rhs )
	{
		if ( lhs.x != rhs.x ) return false;
		if ( lhs.y != rhs.y ) return false;
		if ( lhs.w != rhs.w ) return false;
		if ( lhs.h != rhs.h ) return false;
		return true;
	}
	template <typename T>
	inline bool operator != ( const Rect<T>& lhs, const Rect<T>& rhs )
	{
		return !(lhs == rhs);
	}

	typedef Rect<float>		RectF;
	typedef Rect<Sint32>	RectI;

	/**
		@brief �F��`
		@author �t���b
		@note �F�̒�`
	*/
	struct ColorU
	{
	public:
		Uint8 r;		///< �F��R�v�f
		Uint8 g;		///< �F��G�v�f
		Uint8 b;		///< �F��B�v�f
		Uint8 a;		///< �F��A�v�f

	public:
		ColorU( Uint8 _r = 0xFF, Uint8 _g = 0xFF, Uint8 _b = 0xFF, Uint8 _a = 0xFF )
			: r	( _r )
			, g	( _g )
			, b	( _b )
			, a	( _a )
		{
		}

		ColorU( Uint32 c )
			: r	( static_cast<Uint8>((c >>  0) & 0xFF) )
			, g	( static_cast<Uint8>((c >>  8) & 0xFF) )
			, b	( static_cast<Uint8>((c >> 16) & 0xFF) )
			, a	( static_cast<Uint8>((c >> 24) & 0xFF) )
		{
		}

		Uint32 GetRGBA() const
		{
			return (a << 24) | (b << 16) | (g << 8) | (r << 0);
		}

		ColorU& operator = ( Uint32 value )
		{
			*this = ColorU( value );
			return *this;
		}
	};

	inline bool operator == ( const ColorU& lhs, const ColorU& rhs )
	{
		if ( lhs.r != rhs.r ) return false;
		if ( lhs.g != rhs.g ) return false;
		if ( lhs.b != rhs.b ) return false;
		if ( lhs.a != rhs.a ) return false;
		return true;
	}

	inline bool operator != ( const ColorU& lhs, const ColorU& rhs )
	{
		return !(lhs == rhs);
	}

	/**
		@brief �F��`
		@author �t���b
		@note �F�̒�`
	*/
	struct ColorF
	{
	public:
		float r;		///< �F��R�v�f
		float g;		///< �F��G�v�f
		float b;		///< �F��B�v�f
		float a;		///< �F��A�v�f

	public:
		ColorF( float _r = 1.0f, float _g = 1.0f, float _b = 1.0f, float _a = 1.0f )
			: r	( _r )
			, g	( _g )
			, b	( _b )
			, a	( _a )
		{
		}

		ColorF( Uint32 c )
			: r	( static_cast<float>((c >>  0) & 0xFF) / 255.0f )
			, g	( static_cast<float>((c >>  8) & 0xFF) / 255.0f )
			, b	( static_cast<float>((c >> 16) & 0xFF) / 255.0f )
			, a	( static_cast<float>((c >> 24) & 0xFF) / 255.0f )
		{
		}

		Uint32 GetRGBA() const
		{
			Sint32 r = static_cast<Sint32>(this->r * 255.0f);
			Sint32 g = static_cast<Sint32>(this->g * 255.0f);
			Sint32 b = static_cast<Sint32>(this->b * 255.0f);
			Sint32 a = static_cast<Sint32>(this->a * 255.0f);
			if ( r < 0x00 ) r = 0x00;
			if ( g < 0x00 ) g = 0x00;
			if ( b < 0x00 ) b = 0x00;
			if ( a < 0x00 ) a = 0x00;
			if ( r > 0xFF ) r = 0xFF;
			if ( g > 0xFF ) g = 0xFF;
			if ( b > 0xFF ) b = 0xFF;
			if ( a > 0xFF ) a = 0xFF;
			return (a << 24) | (b << 16) | (g << 8) | (r << 0);
		}

		ColorF& operator = ( Uint32 value )
		{
			*this = ColorF( value );
			return *this;
		}

		ColorF operator + ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a + In.a;
			Out.r = r + In.r;
			Out.g = g + In.g;
			Out.b = b + In.b;
			return Out;
		}

		ColorF operator - ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a - In.a;
			Out.r = r - In.r;
			Out.g = g - In.g;
			Out.b = b - In.b;
			return Out;
		}

		ColorF operator * ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a * In.a;
			Out.r = r * In.r;
			Out.g = g * In.g;
			Out.b = b * In.b;
			return Out;
		}

		ColorF operator / ( const ColorF &In ) const
		{
			ColorF Out;
			Out.a = a / In.a;
			Out.r = r / In.r;
			Out.g = g / In.g;
			Out.b = b / In.b;
			return Out;
		}

		ColorF& operator += ( const ColorF &In )
		{
			a += In.a;
			r += In.r;
			g += In.g;
			b += In.b;
			return *this;
		}

		ColorF& operator -= ( const ColorF &In )
		{
			a -= In.a;
			r -= In.r;
			g -= In.g;
			b -= In.b;
			return *this;
		}

		ColorF& operator *= ( const ColorF &In )
		{
			a *= In.a;
			r *= In.r;
			g *= In.g;
			b *= In.b;
			return *this;
		}

		ColorF& operator /= ( const ColorF &In )
		{
			a /= In.a;
			r /= In.r;
			g /= In.g;
			b /= In.b;
			return *this;
		}
	};

	inline bool operator == ( const ColorF& lhs, const ColorF& rhs )
	{
		if ( lhs.r != rhs.r ) return false;
		if ( lhs.g != rhs.g ) return false;
		if ( lhs.b != rhs.b ) return false;
		if ( lhs.a != rhs.a ) return false;
		return true;
	}

	inline bool operator != ( const ColorF& lhs, const ColorF& rhs )
	{
		return !(lhs == rhs);
	}
}

//-----------------------------------------------------------------------------------
// INLINE
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �����˕��������ϊ�
		@author �t���`
		@param iVal		[in] ���͒l
		@return ���������_�����ꂽ���͒l
		@note
		��������̏�Ԃ����̂܂܂ɕ��������_�ɕϊ����܂�
	*/
	inline float toFloat( Sint32 iVal )
	{
		return *reinterpret_cast<float*>(&iVal);
	}

	/**
		@brief �����˕��������ϊ�
		@author �t���`
		@param iVal		[in] ���͒l
		@return ���������_�����ꂽ���͒l
		@note
		��������̏�Ԃ����̂܂܂ɕ��������_�ɕϊ����܂�
	*/
	inline float toFloat( Uint32 iVal )
	{
		return *reinterpret_cast<float*>(&iVal);
	}

	/**
		@brief ���������ː����ϊ�
		@author �t���`
		@param Value		[in] ���͒l
		@return ���������ꂽ���͒l
		@note
		��������̏�Ԃ����̂܂܂ɐ����ɕϊ����܂�
	*/
	inline Sint32 toInt( float Value )
	{
		return *reinterpret_cast<Sint32*>(&Value);
	}

	/**
		@brief ���������ː����ϊ�
		@author �t���`
		@param Value		[in] ���͒l
		@return ���������ꂽ���͒l
		@note
		��������̏�Ԃ����̂܂܂ɐ����ɕϊ����܂�
	*/
	inline Uint32 toUint( float Value )
	{
		return *reinterpret_cast<Uint32*>(&Value);
	}

	/**
		@brief FP16��FP32�ϊ�
		@author �t���`
		@param In	[in] 16bit���������_
		@return 32Bit���������_
		@note
		16Bit���������_��32Bit���������_�ɕϊ����܂��B
	*/
	inline float FP16toFP32( Uint16 In )
	{
		Uint32 Out = In;
		Out = ((Out & 0x8000) << 16) + ((((Out & 0x7C00) >> 10) - 15 + 127) << 23) + ((Out & 0x3FF) << 13);
		return toFloat( Out );
	}

	/**
		@brief sqrt�Z�o
		@author �t���`
		@param Value		[in] ���͒l
		@return Value��sqrt�l
		@note
		���x���]���ɍ�����sqrt���擾���܂�
	*/
	inline float FastSqrt( float Value )
	{
		Sint32 iVal = toInt( Value );

		iVal &= 0x7FFFFFFF;
		iVal -= 0x3F800000;
		iVal >>= 1;
		iVal += 0x3F800000;

		return toFloat( iVal );
	}

	/**
		@brief sqrt�̋t���Z�o
		@author �t���`
		@param Value		[in] ���͒l
		@return Value��sqrt�̋t��
		@note
		���x���]���ɍ�����sqrt�̋t�����擾���܂�
	*/
	inline float InvSqrt( float Value )
	{
		float ValHalf = Value * 0.5f;

		Sint32 iVal = toInt( Value );

		iVal = 0x5F375A86 - (iVal >> 1);

		Value = toFloat( iVal );

		return Value * (1.5f - ValHalf * Value * Value);
	}

	/**
		@brief ��Βl�擾
		@author �t���`
		@param Value		[in] ���͒l
		@return ���͒l�̐�Βl
		@note
		�w�肳�ꂽ�A�l�̐�Βl���擾���܂�
	*/
	inline float Abs( const float Value )
	{
		Sint32 iVal = toInt( Value );

		iVal &= 0x7FFFFFFF;

		return toFloat( iVal );
	}

	/**
		@brief ��Βl�擾
		@author �t���`
		@param iVal		[in] ���͒l
		@return ���͒l�̐�Βl
		@note
		�w�肳�ꂽ�A�l�̐�Βl���擾���܂�
	*/
	inline Sint32 Abs( const Sint32 iVal )
	{
		return iVal < 0 ? -iVal : +iVal;
	}

	/**
		@brief 2Byte�����`�F�b�N
		@author �t���`
		@retval true	2Byte����
		@retval false	1Byte����
		@note
		�w�肳�ꂽASCII������2Byte������1�����ڂ��ǂ������`�F�b�N���܂��B
	*/
	inline bool Is2ByteChara( char Src )
	{
		Uint8 Code = *reinterpret_cast<Uint8*>(&Src);

		if ( Code <= 0x80 ) return false;
		if ( Code <= 0x9F ) return true;
		if ( Code <= 0xDF ) return false;
		if ( Code <= 0xFE ) return true;

		return false;
	}

	/**
		@brief �G���f�B�A���̃`�F�b�N
		@author �t���`
		@retval true	���g���G���f�B�A��
		@retval false	�r�b�O�G���f�B�A��
		@note
		���g���G���f�B�A���������`�F�b�N���܂�
	*/
	inline bool IsLittleEndian()
	{
		static union
		{
			Uint8  Byte[2];
			Uint16 UShort;
		}
		Union = { 0x00, 0xFF };

		return Union.UShort == 0xFF00;
	}

	/**
		@brief �G���f�B�A���̕ϊ�
		@author �t���`
		@param In	[in] �ϊ���
		@return �ϊ���̒l
		@note
		���g���̃r�b�O�ŃG���f�B�A���̕ϊ������܂�
	*/
	template <typename T>
	inline T ChengeEndian( const T& In )
	{
		const Uint8* pByte = reinterpret_cast<const Uint8*>(&In);

		switch ( sizeof(T) )
		{
		case 2:
			{
				Uint8 Temp[] = { pByte[1], pByte[0] } __declspec( align( 2 ) );
				return *reinterpret_cast<T*>(Temp);
			}
			break;
		case 4:
			{
				Uint8 Temp[] = { pByte[3], pByte[2], pByte[1], pByte[0] } __declspec( align( 4 ) );
				return *reinterpret_cast<T*>(Temp);
			}
			break;
		case 8:
			{
				Uint8 Temp[] = { pByte[7], pByte[6], pByte[5], pByte[4], pByte[3], pByte[2], pByte[1], pByte[0] } __declspec( align( 8 ) );
				return *reinterpret_cast<T*>(Temp);
			}
			break;
		}

		return In;
	}

	/**
		@brief �ŏ��l
		@author �t���`
		@param lhs	[in] ��r�l
		@param rhs	[in] ��r�l
		@note
		�Q�̐��l�̂����������l��Ԃ��܂�
	*/
	template <typename T, typename U>
	T Min( T lhs, U rhs )
	{
		return (lhs < rhs) ? lhs : rhs;
	}

	/**
		@brief �ő�l
		@author �t���`
		@param lhs	[in] ��r�l
		@param rhs	[in] ��r�l
		@note
		�Q�̐��l�̂����傫���l��Ԃ��܂�
	*/
	template <typename T, typename U>
	T Max( T lhs, U rhs )
	{
		return (lhs > rhs) ? lhs : rhs;
	}

	/**
		@brief �l����
		@author �t���`
		@param lhs	[in] �l
		@param rhs	[in] �l
		@note
		�Q�̐��l�̒l���D�����܂��B
	*/
	template <typename T>
	void Swap( T& lhs, T& rhs )
	{
		lhs = rhs - lhs;
		rhs -= lhs;
		lhs += rhs;
	}
}

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
	/**
		@brief �C���^�[�t�F�C�X
		@author �t���`

		@note
		�C���^�[�t�F�C�X�̊��N���X
	*/
	class Interface
	{
	protected:
		virtual ~Interface(){}

	public:
		/**
			@brief �Q�ƃJ�E���^�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g

			@note
			�Q�ƃJ�E���^���f�N�������g���A<BR>
			�Q�ƃJ�E���g��0�ɂȂ������_�Ń��������������܂��B
		*/
		virtual Sint32 Release() = 0;

		/**
			@brief �Q�ƃJ�E���^�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g

			@note
			�Q�ƃJ�E���^���C���N�������g���܂��B<BR>
			�C���N�������g�����Q�ƃJ�E���g��Release()���ĂԂ��Ƃɂ��f�N�������g����܂��B<BR>
			AddRef()�������C���^�[�t�F�C�X�͕K��Release()�ŉ�����Ă��������B
		*/
		virtual Sint32 AddRef() = 0;

		/**
			@brief �Q�ƃJ�E���^�擾
			@author �t���`
			@return �Q�ƃJ�E���g

			@note
			���݂̎Q�ƃJ�E���^���擾
		*/
		virtual Sint32 GetReferenceCount() = 0;
	};
}


#ifdef __cplusplus_cli
#pragma managed( push, off )
#endif
/**
	@file
	@brief Engine��{��`
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief ���C�u�������O���
*/
namespace Selene
{
	/**
		@brief �J�[�l��
	*/
	namespace Kernel
	{
		namespace Math
		{
			class Vector2;
			class Vector3;
			class Vector4;
			class VectorS;
			class Quaternion;
			class Matrix;
			class Camera;
		}

		namespace Collision
		{
			class AABB;
			class OBB;
			class Plane;
			class Sphere;
		}

		namespace File
		{
			class FileControl;
			class LogFile;
		}
	}
}


/**
	@file
	@brief �R�s�[�֎~�I�u�W�F�N�g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Object
{
	/**
		@brief �R�s�[�֎~�N���X
		@author �t���`
	*/
	class NoneCopyableObject
	{
	private:
		NoneCopyableObject& operator = ( const NoneCopyableObject& In );

	public:
		NoneCopyableObject() {}
		virtual ~NoneCopyableObject() {}
	};
}
}
}




//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Misc
{
	class ModuleLoader
	{
	private:
		HMODULE						m_hDLL;
		std::map<std::string,void*>	m_Function;

	public:
		ModuleLoader();
		~ModuleLoader();
		bool Load( const wchar_t* pModuleName );
		void Unload();
		bool LoadFunction( const char* pFunction );
		void* GetFunction( const char* pFunction );
	};
}
}
}


/**
	@file
	@brief �A�g�~�b�N�ϐ�
	@author �t���`
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief �A�g�~�b�N�ϐ�
		@author �t���`
	*/
	class Atomic
	{
	private:
		volatile Sint32 m_Value;

	public:
		/*
			@brief �R���X�g���N�^
			@author �t���`
			@param Value	[in] �����l
		*/
		Atomic( Sint32 Value = 0 );
		/*
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~Atomic();
		/*
			@brief �l�擾
			@author �t���`
			@return �A�g�~�b�N�̒l
			@note
			�A�g�~�b�N�̒l���擾���܂��B
		*/
		Sint32 Get() const;
		/*
			@brief �l�ݒ�
			@author �t���`
			@param Value	�A�g�~�b�N�̒l
			@note
			�A�g�~�b�N�̒l��ݒ肵�܂��B
		*/
		void Set( Sint32 Value );
		/*
			@brief ���Z
			@author �t���`
			@param Value	�A�g�~�b�N�̒l
			@note
			�A�g�~�b�N�̒l�����Z���܂��B
		*/
		Sint32 Add( Sint32 Value );
		/*
			@brief �C���N�������g
			@author �t���`
			@return �C���N�������g��̒l
			@note
			�A�g�~�b�N�̒l���C���N�������g���܂��B
		*/
		Sint32 Increment();
		/*
			@brief �f�N�������g
			@author �t���`
			@return �f�N�������g��̒l
			@note
			�A�g�~�b�N�̒l���f�N�������g���܂��B
		*/
		Sint32 Decrement();

		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		void operator = ( Sint32 Value );
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator == ( Sint32 Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator != ( Sint32 Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator < ( Sint32 Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator > ( Sint32 Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator <= ( Sint32 Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator >= ( Sint32 Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		void operator = ( const Atomic& Value );
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator == ( const Atomic& Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator != ( const Atomic& Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator < ( const Atomic& Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator > ( const Atomic& Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator <= ( const Atomic& Value ) const;
		/*
			@brief �I�y���[�^�[
			@author �t���`
		*/
		bool operator >= ( const Atomic& Value ) const;
	};
}
}
}


/**
	@file
	@brief ����������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Memory
{
	/**
		@brief �������N���A
		@author �t���`
		@param pDst	[in] �N���A��
		@param Size	[in] �N���A�l
		@note
		���������N���A���܂�
	*/
	void Clear( void* pDst, size_t Size );
	/**
		@brief ������������
		@author �t���`
		@param pDst	[in] �N���A��
		@param Src	[in] �N���A�l
		@param Size	[in] �N���Abyte��
		@note
		���������w�肵���l�ŃN���A���܂�
	*/
	void Fill( void* pDst, Uint8 Src, size_t Size );
	/**
		@brief �������ړ�
		@author �t���`
		@param pDst	[in] �ړ���
		@param pSrc	[in] �ړ���
		@param Size	[in] �ړ�byte��
		@note
		�������̓��e�����ړ����܂�
	*/
	void Move( void* pDst, const void* pSrc, size_t Size );
	/**
		@brief �������R�s�[
		@author �t���`
		@param pDst	[in] �R�s�[��
		@param pSrc	[in] �R�s�[��
		@param Size	[in] �R�s�[byte��
		@note
		�������̓��e���R�s�[���܂�
	*/
	void Copy( void* pDst, const void* pSrc, size_t Size );
	/**
		@brief 16Byte�A���C�����g�������m��
		@author �t���`
		@param Size		[in] �m�ۂ���byte��
		@return �������|�C���^
		@note
		16Byte�A���C�����g���ꂽ���������m�ۂ��܂��B
	*/
	void* Alloc( size_t Size );
	/**
		@brief 16Byte�A���C�����g�������m��
		@author �t���`
		@param Size		[in] �m�ۂ���byte��
		@param Init		[in] �������̏����l
		@return �������|�C���^
		@note
		16Byte�A���C�����g���ꂽ���������m�ۂ��܂��B
	*/
	void* Alloc( size_t Size, Uint8 Init );
	/**
		@brief 16Byte�A���C�����g���������
		@author �t���`
		@param pData	[in] ������郁����
		@note
		16Byte�A���C�����g���ꂽ��������������܂��B
	*/
	void Free( const void* pData );
}
}
}


/**
	@file
	@brief �������Ǘ��p�I�u�W�F�N�g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Object
{
	/**
		@brief �������Ǘ��p�I�u�W�F�N�g
		@author �t���`
		@note
		16Byte�A���C�����ꂽ�N���X�𐶐�����ׂɎg���܂��B
	*/
	class MemoryObject
	{
	public:
		/**
			@brief new�I�[�o�[���C�h
			@param Size	[in] �m�ۃT�C�Y
		*/
		void *operator new ( size_t Size )
		{
			return Memory::Alloc( Size );
		}
		/**
			@brief delete�I�[�o�[���C�h
			@param pData	[in] ����̈�
		*/
		void operator delete ( void* pData )
		{
			Memory::Free( pData );
		}
		/**
			@brief new[]�I�[�o�[���C�h
			@param Size	[in] �m�ۃT�C�Y
		*/
		void *operator new[] ( size_t Size )
		{
			return Memory::Alloc( Size );
		}
		/**
			@brief delete[]�I�[�o�[���C�h
			@param pData	[in] ����̈�
		*/
		void operator delete[] ( void* pData )
		{
			Memory::Free( pData );
		}
	};
}
}
}


/**
	@file
	@brief �Q�ƃJ�E���^�I�u�W�F�N�g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Object
{
	/**
		@brief �Q�ƃJ�E���^�N���X
		@author �t���`
	*/
	class ReferenceObject
		: public MemoryObject
		, public NoneCopyableObject
	{
	private:
		Thread::Atomic m_ReferenceCount;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		ReferenceObject()
			: m_ReferenceCount	( 1 )
		{
		}
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~ReferenceObject()
		{
		}
		/**
			@brief �Q�ƃJ�E���g�擾
			@author �t���`
			@return �Q�ƃJ�E���g
			@note
			���݂̎Q�ƃJ�E���g���擾���܂��B
		*/
		virtual Sint32 GetReferenceCount()
		{
			return m_ReferenceCount.Get();
		}
		/**
			@brief �Q�ƃJ�E���g�C���N�������g
			@author �t���`
			@return �C���N�������g��̎Q�ƃJ�E���g
			@note
			�Q�ƃJ�E���g�̒l���C���N�������g���܂�
		*/
		virtual Sint32 AddRef()
		{
			return m_ReferenceCount.Increment();
		}
		/**
			@brief �Q�ƃJ�E���g�f�N�������g
			@author �t���`
			@return �f�N�������g��̎Q�ƃJ�E���g
			@note
			�Q�ƃJ�E���g�̒l���f�N�������g���A<BR>
			0�ɂȂ�����delete���܂��B
		*/
		virtual Sint32 Release()
		{
			Sint32 Count = m_ReferenceCount.Decrement();
			if ( Count == 0 )
			{
				delete this;
			}
			return Count;
		}
	};
}
}
}


/**
	@file
	@brief �N���e�B�J���Z�N�V����
	@author �t���`
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief �N���e�B�J���Z�N�V����
		@author �t���`
	*/
	class CriticalSection
		: public Object::NoneCopyableObject
	{
	private:
		mutable CRITICAL_SECTION m_CriticalSection;

	public:
		/*
			@brief �R���X�g���N�^
			@author �t���`
		*/
		CriticalSection();
		/*
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~CriticalSection();
		/*
			@brief �N���e�B�J���Z�N�V�����ɓ���
			@author �t���`
		*/
		void Enter() const;
		/*
			@brief �N���e�B�J���Z�N�V��������o��
			@author �t���`
		*/
		void Leave() const;
	};

	/*
		@brief �����N���e�B�J���Z�N�V����
		@author �t���`
	*/
	class ScopedLock
		: public Object::NoneCopyableObject
	{
	private:
		const CriticalSection& m_cs;

	public:
		/*
			@brief �R���X�g���N�^
			@author �t���`
			@note
			�����I�ɃN���e�B�J���Z�N�V�����ɓ���܂�
		*/
		ScopedLock( const CriticalSection& cs )
			: m_cs	( cs )
		{
			m_cs.Enter();
		}

		/*
			@brief �f�X�g���N�^
			@author �t���`
			@note
			�����I�ɃN���e�B�J���Z�N�V��������o�܂�
		*/
		~ScopedLock()
		{
			m_cs.Leave();
		}
	};
}
}
}


/**
	@file
	@brief �A�g�~�b�N�ϐ�
	@author �t���`
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief �A�g�~�b�N�ϐ�
		@author �t���`
	*/
	class Semaphore
	{
	private:
		HANDLE	m_hSemaphore;

	public:
		/*
			@brief �R���X�g���N�^
			@author �t���`
			@param IsAutoReset	[in] �������Z�b�gON/OFF
		*/
		Semaphore::Semaphore( bool IsAutoReset = true );
		/*
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~Semaphore();
		/*
			@brie �����҂�
			@author �t���`
			@note
			�Z�}�t�H�̓�����҂��܂��B
		*/
		void Wait();
		/*
			@brief �J�n
			@author �t���`
			@note
			�Z�}�t�H�̓������������܂��B
		*/
		void Signal();
		/*
			@brief ���Z�b�g
			@author �t���`
			@note
			�Z�}�t�H�̓������J�n���܂��B
		*/
		void Reset();
		/*
			@brie ������ԃ`�F�b�N
			@author �t���`
			@note
			�Z�}�t�H�̓�����Ԃ𒲂ׂ܂��B
		*/
		bool IsSignal();
	};
}
}
}


/**
	@file
	@brief �A�g�~�b�N�ϐ�
	@author �t���`
*/


//----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/*
		@brief �A�g�~�b�N�ϐ�
		@author �t���`
	*/
	class MultipleSemaphore
	{
	private:
		std::vector<HANDLE>	m_Handle;

	public:
		/*
			@brief �R���X�g���N�^
			@author �t���`
			@param IsAutoReset	[in] �������Z�b�gON/OFF
		*/
		MultipleSemaphore( Uint32 Count, bool IsAutoReset = true );
		/*
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~MultipleSemaphore();
		/*
			@brie �����҂�
			@author �t���`
			@note
			�Z�}�t�H�̓�����҂��܂��B
		*/
		void WaitAll();
		/*
			@brief �J�n
			@author �t���`
			@note
			�Z�}�t�H�̓������������܂��B
		*/
		void Signal( Uint32 Index );
		/*
			@brief ���Z�b�g
			@author �t���`
			@note
			�Z�}�t�H�̓������J�n���܂��B
		*/
		void Reset( Uint32 Index );
	};
}
}
}


/**
	@file
	@brief �X���b�h����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Thread
{
	/**
		@brief �X���b�h�Ǘ�����N���X
		@author �t���`
	*/
	class Threading
		: public Object::NoneCopyableObject
	{
	private:
		/**
			@brief �X���b�h�p�֐�
			@author �t���`
			@param pArguments	[in] Thread�̃|�C���^
			@note
			�N���X�̊֐��𒼐ڂ͎w��ł��Ȃ��̂�<BR>
			static�Ȋ֐����o�R���ČĂяo���B
		*/
		static Uint32 SLN_STDCALL ThreadProc( void* pArguments );

	private:
		HANDLE m_hThread;					///< �X���b�h�n���h��
		Uint32 m_ThreadId;					///< �X���b�hID
		void* m_pData;						///< �X���b�h�f�[�^�`�B�p�|�C���^
		void (*m_pMainProc)( void* );		///< �X���b�h�֐�
		CriticalSection m_CS;				///< �N���e�B�J���Z�N�V����

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Threading();

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~Threading();

	public:
		/**
			@brief �X���b�h����
			@author �t���`
			@param pThreadFunc	[in] �X���b�h�֐�
			@param pData		[in] �X���b�h�Ɉ����n���f�[�^�|�C���^
			@param CoreNo		[in] ���p����CPU�R�A�ԍ��i-1�ŃV�X�e���܂����j
			@param ThreadName	[in] �X���b�h��
			@retval false	�������sfor���ɃX���b�h����������Ă���
			@retval true	��������
			@note
			�X���b�h�̐������s���܂��B
		*/
		bool Create( void (*pThreadFunc)( void* ), void* pData, Uint32 CoreNo, const char* ThreadName );

		/**
			@brief �X���b�h�I���҂�
			@author �t���`
			@retval false	�X���b�h�͏I�����Ă��Ȃ�
			@retval true	�X���b�h�͏I������
			@note
			�X���b�h���I������̂�҂��܂�
		*/
		bool IsExitThread() const;

		/**
			@brief �X���b�h�I���҂�
			@author �t���`
			@retval false	�X���b�h�͏I�����Ă��Ȃ�
			@retval true	�X���b�h�͏I������
			@note
			�X���b�h���I������̂�҂��܂�
		*/
		bool Wait() const;
	};
}
}
}


/**
	@file
	@brief		�X���b�h���[�e�B���e�B�@��`
	@author		��
*/


namespace Selene
{
namespace Kernel
{
namespace Thread
{
	//---------------------------------------------------------------------------//
	/**
		@brief		�X���b�h���[�e�B���e�B
		@author		��
	*/
	class Utility
	{
		//---------------------------------------------------------------------------//
		/**
			@internal
			@brief		�R���X�g���N�^(��`�֎~)
		*/
		Utility();

	public:
		//---------------------------------------------------------------------------//
		/**
			@brief		CPU�����擾����
		*/
		static Uint32 GetNumberOfProcessors();

		//---------------------------------------------------------------------------//
		/**
			@brief		CPU���X���[�v������
		*/
		static void Sleep( Uint32 Time );
	};

}	// namespace Thread
}	// namespace Kernel
}	// namespace Selene



/**
	@file
	@brief ���O�pHTML�t�@�C��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace File
{
	/**
		@brief ���O�pHTML�t�@�C������
		@author �t���`
	*/
	class LogFile
	{
	private:
		HANDLE	m_hFile;

	private:
		Sint32 Write( const void* pData, Sint32 Size );
		Sint32 GetFileSize();
		Sint32 GetFilePosition();
		Sint32 SeekStart( Sint32 Offset );
		Sint32 SeekEnd( Sint32 Offset );
		Sint32 Seek( Sint32 Offset );

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param pFileName	[in] �t�@�C����
			@param pTitle		[in] �^�C�g��
			@note
			�w�肵���t�@�C������html�t�@�C���𐶐����܂��B
		*/
		LogFile( const wchar_t* pFileName, const wchar_t* pTitle );
		/**
			@brief �f�X�g���N�^
			@author �t���`
			@note
			html�^�O����ăt�@�C����close���܂��B
		*/
		~LogFile();
		/**
			@brief �`��
			@author �t���`
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����iprintf�Ɠ��������j
			@note
			������̕`������܂��B
		*/
		void Print( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief �����`��
			@author �t���`
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����iprintf�Ɠ��������j
			@note
			�����ŕ�����̕`������܂��B
		*/
		void PrintStrong( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief ���s�t���`��
			@author �t���`
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����iprintf�Ɠ��������j
			@note
			���s�t���̕�����̕`������܂��B
		*/
		void PrintLine( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief ���s�t�������`��
			@author �t���`
			@param Color	[in] �`��F
			@param pStr		[in] �`�敶����iprintf�Ɠ��������j
			@note
			���s�t���̑����ŕ�����̕`������܂��B
		*/
		void PrintStrongLine( Sint32 Color, const wchar_t* pStr,... );
		/**
			@brief �e�[�u���`��
			@author �t���`
			@param Width	[in] �^�C�g����
			@param pTitle	[in] �^�C�g��
			@param pStr		[in] �`�敶����iprintf�Ɠ��������j
			@note
			�P�s�����̃e�[�u����`�悵�܂�
		*/
		void PrintTable( Sint32 Width, const wchar_t* pTitle, const wchar_t* pStr,... );
		/**
			@brief �e�[�u���`��
			@author �t���`
			@param ColorTitle	[in] �^�C�g���F
			@param Color		[in] �����F
			@param pTitle		[in] �^�C�g��
			@param pKind		[in] ���
			@param pStr			[in] �`�敶����iprintf�Ɠ��������j
			@note
			�P�s�����̃e�[�u����`�悵�܂�
		*/
		void PrintTable( Sint32 ColorTitle, Sint32 Color, const wchar_t* pTitle, const wchar_t* pKind, const wchar_t* pStr,... );
		/**
			@brief �Z���^�C�g���`��
			@author �t���`
			@param Color		[in] �����F
			@param pTitle		[in] �^�C�g��
			@note
			�Z���̃^�C�g����`�悵�܂��B
		*/
		void PrintCellTitle( Sint32 Color, const wchar_t* pTitle );
		/**
			@brief �Z����ޕ`��
			@author �t���`
			@param pKind	[in] ��ށiprintf�Ɠ��������j
			@note
			�Z���̎�ނ�`�悵�܂��B
		*/
		void PrintCellKind( const wchar_t* pKind,... );
		/**
			@brief �e�[�u���J�n
			@author �t���`
			@note
			�e�[�u���̊J�n�����܂��B
		*/
		void TableBegin();
		/**
			@brief �e�[�u���I��
			@author �t���`
			@note
			�e�[�u���̏I�������܂��B
		*/
		void TableEnd();
		/**
			@brief �P�s�e�[�u��
			@author �t���`
			@param Bold	[in] ����
			@note
			�P�s�����̃e�[�u�����o�͂��܂��B
		*/
		void TableLine( Sint32 Bold );
		/**
			@brief �Z���J�n
			@author �t���`
			@param Width	[in] �Z���̕�
			@note
			�Z���̊J�n�����܂��B
		*/
		void CellBegin( Sint32 Width );
		/**
			@brief �Z���I��
			@author �t���`
			@note
			�Z���̏I�������܂��B
		*/
		void CellEnd();
	};
}
}
}


/**
	@file
	@brief �t�@�C������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace File
{
	/**
		@brief �t�@�C���I�[�v�����[�h
		@author �t���`
	*/
	enum eFileOpenType
	{
		FILE_OPEN_TYPE_WRITE,			///< �������ݐ�p
		FILE_OPEN_TYPE_READ,			///< �ǂݍ��ݐ�p
		FILE_OPEN_TYPE_READ_WRITE,		///< �ǂݏ����p

		FILE_OPEN_TYPE_INVALID,			///< ����
	};

	/**
		@brief �t�@�C������
		@author �t���`
	*/
	class FileControl
	{
	private:
		wchar_t			m_FileName[MAX_PATH];	///< �t�@�C����
		HANDLE			m_hFile;				///< �t�@�C���n���h��
		eFileOpenType	m_Type;					///< �t�@�C���I�[�v�����[�h
		FILETIME		m_TimeCreate;			///< �t�@�C���쐬����
		FILETIME		m_TimeAccess;			///< �t�@�C���A�N�Z�X����
		FILETIME		m_TimeLastWrite;		///< �t�@�C���������ݎ���

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		FileControl( const wchar_t* pFileName, eFileOpenType Type );

		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~FileControl();

		/**
			@brief �t�@�C���I�[�v���`�F�b�N
			@author �t���`
			@retval false	�t�@�C���͊J����Ă��Ȃ�
			@retval true	�t�@�C���͊J����Ă���
		*/
		const wchar_t* GetFileName() const;

		/**
			@brief �t�@�C���I�[�v���`�F�b�N
			@author �t���`
			@retval false	�t�@�C���͊J����Ă��Ȃ�
			@retval true	�t�@�C���͊J����Ă���
		*/
		bool IsOpened() const;

		/**
			@brief �t�@�C���N���[�Y
			@author �t���`
		*/
		void Close();

		/**
			@brief �t�@�C����������
			@author �t���`
			@param pData	[in] �������݃f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@return ���ۂ̏������݃T�C�Y
		*/
		Sint32 Write( const void* pData, Sint32 Size );

		/**
			@brief �t�@�C���ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@return ���ۂ̓ǂݍ��݃T�C�Y
		*/
		Sint32 Read( void* pData, Sint32 Size );

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y
		*/
		Sint32 GetFileSize() const;

		/**
			@brief �t�@�C���ʒu�擾
			@author �t���`
			@return �t�@�C���ʒu
		*/
		Sint32 GetFilePosition() const;

		/**
			@brief �擪����V�[�N
			@author �t���`
			@param Offset	[in] �擪����̃I�t�Z�b�g
			@return �t�@�C���ʒu
		*/
		Sint32 SeekStart( Sint32 Offset );

		/**
			@brief �I�[����V�[�N
			@author �t���`
			@param Offset	[in] �I�[����̃I�t�Z�b�g
			@return �t�@�C���ʒu
		*/
		Sint32 SeekEnd( Sint32 Offset );

		/**
			@brief �V�[�N
			@author �t���`
			@param Offset	[in] ���݈ʒu����̃I�t�Z�b�g
			@return �t�@�C���ʒu
		*/
		Sint32 Seek( Sint32 Offset );
	};
}
}
}


/**
	@file
	@brief �^������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	/**
		@brief ���������N���X
		@author �t���`
	*/
	class Random
	{
		enum { N = 624 };

	private:
		Sint32 m_MersenneTwister[N];
		Sint32 m_MersenneTwisterCount;

	private:
		Sint32 GenerateInt32();

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Random();

		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Random( Sint32 Param );

		/**
			@brief �����p��ݒ�
			@author �t���`
			@param Param	[in] �V�[�h�l
			@note
			���������̎��ݒ肵�܂��B
		*/
		void Seed( Sint32 Param );

		/**
			@brief 32Bit���������擾
			@author �t���`
			@return �����l
			@note
			32Bit�����̗����l���擾���܂��B
		*/
		Sint32 GetInt32();

		/**
			@brief 64Bit���������擾
			@author �t���`
			@return �����l
			@note
			64Bit�����̗����l���擾���܂��B
		*/
		Uint64 GetInt64();

		/**
			@brief 32Bit�������������擾
			@author �t���`
			@return �����l
			@note
			32Bit���������̗����l���擾���܂��B
		*/
		float GetFloat32();

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l
			@note
			�w��͈͓��̐����������擾���܂��B
		*/
		Sint32 GetInt( Sint32 Min, Sint32 Max );

		/**
			@brief �w��͈͗����擾
			@author �t���`
			@param Min [in] �ŏ��l
			@param Max [in] �ő�l
			@return �����l
			@note
			�w��͈͓��̕��������������擾���܂��B
		*/
		float GetFloat( float Min, float Max );
	};
}
}
}


/**
	@file
	@brief �O�p�֐�
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	static const Sint32 ANGLE_TABLE_BIT		= 12;						///< �T�C���e�[�u���̃r�b�g��
	static const Sint32 ANGLE_TABLE_MAX		= 1 << ANGLE_TABLE_BIT;		///< �T�C���e�[�u���̃T�C�Y
	static const Sint32 ANGLE_TABLE_MASK	= ANGLE_TABLE_MAX - 1;		///< �T�C���e�[�u���̃A�N�Z�X�p�}�X�N

	/**
		@brief �p�x���K��
		@author �t���`
		@param Value		[in] �p�x�i1��4096�j
		@return �p�x�i1��4096�j
	*/
	inline Sint32 NormalizeAngle( Sint32 Value )
	{
		return Value & ANGLE_TABLE_MASK;
	}

	/**
		@brief �p�x�ϊ�
		@author �t���`
		@param Value		[in] �p�x�i1��360�j
		@return �p�x�i1��4096�j
	*/
	inline Sint32 DegToAngle( float Value )
	{
		return toI(Value * toF(ANGLE_TABLE_MAX) / 360.0f);
	}

	/**
		@brief �p�x�ϊ�
		@author �t���`
		@param Value		[in] �p�x�i1��4096�j
		@return �p�x�i1��360�j
	*/
	inline Sint32 AngleToDeg( Sint32 Value )
	{
		return Value * 360 / ANGLE_TABLE_MAX;
	}

	/**
		@brief �p�x�ϊ�
		@author �t���`
		@param Value		[in] �p�x�i1��2�΁j
		@return �p�x�i1��4096�j
	*/
	inline Sint32 PiToAngle( float Value )
	{
		return toI(Value * toF(ANGLE_TABLE_MAX) / PI2);
	}

	/**
		@brief �p�x�ϊ�
		@author �t���`
		@param Value		[in] �p�x�i1��4096�j
		@return �p�x�i1��2�΁j

	*/
	inline float AngleToPi( Sint32 Value )
	{
		return toF(Value) * PI2 / toF(ANGLE_TABLE_MAX);
	}

	/**
		@brief �p�x�ϊ�
		@author �t���`
		@param Value		[in] �p�x�i1��360�j
		@return �p�x�i1��2�΁j
	*/
	inline float DegToPi( float Value )
	{
		return Value * PI2 / 360.0f;
	}

	/**
		@brief �p�x�ϊ�
		@author ����
		@param Value		[in] �p�x�i1��2�΁j
		@return �p�x�i1��360�j
	*/
	inline float PiToDeg( float Value )
	{
		return Value * 360.0f / PI2;
	}

	/**
		@brief ����sin�擾
		@author �t���`
		@param Angle	[in] �p�x�i1��4096�j
		@return sin�l
		@note
		�e�[�u����p���č�����sin�l���擾���܂��B<BR>
		1����4096���������ꍇ�̒l�Ȃ̂ł���ȏ�̐��x���K�v�ȏꍇ��<BR>
		�W���֐���sinf�𗘗p���Ă��������B
	*/
	float FastSin( Sint32 Angle );

	/**
		@brief ����cos�擾
		@author �t���`
		@param Angle	[in] �p�x�i1��4096�j
		@return cos�l
		@note
		�e�[�u����p���č�����cos�l���擾���܂��B<BR>
		1����4096���������ꍇ�̒l�Ȃ̂ł���ȏ�̐��x���K�v�ȏꍇ��<BR>
		�W���֐���cosf�𗘗p���Ă��������B
	*/
	float FastCos( Sint32 Angle );

	/**
		@brief ����sin�擾
		@author �t���`
		@param Angle	[in] �p�x�i1��2�΁j
		@return sin�l
		@note
		�e�[�u����p���č�����sin�l���擾���܂��B<BR>
		1����4096���������ꍇ�̒l�Ȃ̂ł���ȏ�̐��x���K�v�ȏꍇ��<BR>
		�W���֐���sinf�𗘗p���Ă��������B
	*/
	float FastSin( float Angle );

	/**
		@brief ����cos�擾
		@author �t���`
		@param Angle	[in] �p�x�i1��2�΁j
		@return cos�l
		@note
		�e�[�u����p���č�����cos�l���擾���܂��B<BR>
		1����4096���������ꍇ�̒l�Ȃ̂ł���ȏ�̐��x���K�v�ȏꍇ��<BR>
		�W���֐���cosf�𗘗p���Ă��������B
	*/
	float FastCos( float Angle );
}
}
}


/**
	@file
	@brief 2�����x�N�g��
	@author ��
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		2�����x�N�g��
	*/
	class Vector2
	{
	public:
		float x;
		float y;

	public:
		Vector2();
		Vector2( const Vector2& rhs );
		Vector2( float _x, float _y );

		Vector2& operator=( const Vector2& rhs );
		Vector2& operator+=( const Vector2& rhs );
		Vector2& operator-=( const Vector2& rhs );
		Vector2& operator*=( const Vector2& rhs );
		Vector2& operator*=( float rhs );

		Vector2 operator+( const Vector2& rhs ) const;
		Vector2 operator-( const Vector2& rhs ) const;
		Vector2 operator*( const Vector2& rhs ) const;
		Vector2 operator*( float rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		�X�J���[��Z
	*/
	Vector2 operator*( float lhs, const Vector2& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		2�����x�N�g�����Z
	*/
	class Vec2
	{
		Vec2();	// �����֎~�I

	public:
		static Vector2	Add( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Subtract( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Multiply( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Divide( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Scale( const Vector2& vec, float actor );
		static Vector2	Reciprocal( const Vector2& value );
		static Vector2	ReciprocalSqrt( const Vector2& value );
		static Vector2	Normal( const Vector2& value );
		static Vector2	Sqrt( const Vector2& value );
		static float	Length( const Vector2& value );
		static float	LengthSq( const Vector2& value );
		static float	Dot( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Min( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Max( const Vector2& lhs, const Vector2& rhs );
		static Vector2	Rotate( const Vector2& value, float Radian );
	};

	class Vector2H
	{
	public:
		Sint16 x, y;
	};
}
}
}


/**
	@file
	@brief 3�����x�N�g��
	@author ��
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		3�����x�N�g��
	*/
	class Vector3
	{
	public:
		float x;
		float y;
		float z;

	public:
		Vector3();
		Vector3( const class Vector2& rhs );
		Vector3( const class Vector3& rhs );
		Vector3( const class Vector4& rhs );
		Vector3( const class VectorS& rhs );
		Vector3( float _x, float _y, float _z );

		Vector3& operator=( const Vector3& rhs );
		Vector3& operator+=( const Vector3& rhs );
		Vector3& operator-=( const Vector3& rhs );
		Vector3& operator*=( const Vector3& rhs );
		Vector3& operator*=( float rhs );

		Vector3 operator+( const Vector3& rhs ) const;
		Vector3 operator-( const Vector3& rhs ) const;
		Vector3 operator*( const Vector3& rhs ) const;
		Vector3 operator*( float rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		�X�J���[��Z
	*/
	Vector3 operator*( float lhs, const Vector3& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		3�����x�N�g�����Z
	*/
	class Vec3
	{
		Vec3();	// �����֎~�I

	public:
		static Vector3	Add( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Subtract( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Multiply( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Divide( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Scale( const Vector3& vec, float actor );
		static Vector3	Reciprocal( const Vector3& value );
		static Vector3	ReciprocalSqrt( const Vector3& value );
		static Vector3	Normal( const Vector3& value );
		static Vector3	Sqrt( const Vector3& value );
		static float	Length( const Vector3& value );
		static float	LengthSq( const Vector3& value );
		static float	Dot( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Cross( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Min( const Vector3& lhs, const Vector3& rhs );
		static Vector3	Max( const Vector3& lhs, const Vector3& rhs );

		/**
			@brief X���P�ʃx�N�g��
			@author ����
			@note
			X�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector3  UnitX();

		/**
			@brief Y���P�ʃx�N�g��
			@author ����
			@note
			Y�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector3  UnitY();

		/**
			@brief Z���P�ʃx�N�g��
			@author ����
			@note
			Z�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector3  UnitZ();
	};
}
}
}


/**
	@file
	@brief 4�����x�N�g��
	@author ��
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		4�����x�N�g��
	*/
	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;

	public:
		Vector4();
		Vector4( const Vector4& rhs );
		Vector4( const VectorS& rhs );
		Vector4( float _x, float _y, float _z, float _w );

		Vector4& operator=( const Vector4& rhs );
		Vector4& operator=( const VectorS& rhs );
		Vector4& operator+=( const Vector4& rhs );
		Vector4& operator-=( const Vector4& rhs );
		Vector4& operator*=( const Vector4& rhs );
		Vector4& operator*=( float rhs );

		Vector4 operator+( const Vector4& rhs ) const;
		Vector4 operator-( const Vector4& rhs ) const;
		Vector4 operator*( const Vector4& rhs ) const;
		Vector4 operator*( float rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		�X�J���[��Z
	*/
	Vector4 operator*( float lhs, const Vector4& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		4�����x�N�g�����Z
	*/
	class Vec4
	{
		Vec4();	// �����֎~�I

	public:
		static Vector4	Add( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Subtract( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Multiply( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Divide( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Scale( const Vector4& vec, float actor );
		static Vector4	Reciprocal( const Vector4& value );
		static Vector4	ReciprocalSqrt( const Vector4& value );
		static Vector4	Normal( const Vector4& value );
		static Vector4	Sqrt( const Vector4& value );
		static float	Length( const Vector4& value );
		static float	LengthSq( const Vector4& value );
		static float	Dot( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Cross3( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Min( const Vector4& lhs, const Vector4& rhs );
		static Vector4	Max( const Vector4& lhs, const Vector4& rhs );

		/**
			@brief X���P�ʃx�N�g��
			@author ����
			@note
			X�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector4	UnitX();

		/**
			@brief Y���P�ʃx�N�g��
			@author ����
			@note
			Y�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector4	UnitY();

		/**
			@brief Z���P�ʃx�N�g��
			@author ����
			@note
			Z�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector4	UnitZ();

		/**
			@brief W���P�ʃx�N�g��
			@author ����
			@note
			W�������̒P�ʃx�N�g�����擾����B
		*/
		static Vector4	UnitW();
	};

	class Vector4H
	{
	public:
		Sint16 x, y, z, w;
	};
}
}
}


/**
	@file
	@brief �l�������Z
	@author ��
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	class Vector4;

	//---------------------------------------------------------------------------//
	/**
		@brief		�N�H�[�^�j�I��
	*/
	class Quaternion
		: public Object::MemoryObject
	{
	public:
		union
		{
			struct
			{
				float x, y, z, w;
			};
			struct
			{
				int ix, iy, iz, iw;
			};
			struct
			{
				unsigned ux, uy, uz, uw;
			};
			Uint128 v;
		};

	public:
		Quaternion();
		Quaternion( const Quaternion& rhs );
		Quaternion( const Matrix& rhs );
		Quaternion( Uint128 rhs );
		Quaternion( float _x, float _y, float _z );
		Quaternion( float _x, float _y, float _z, float _w );
		explicit Quaternion( const Vector4& rhs );

		Quaternion operator=( const Quaternion& rhs );
		Quaternion operator+=( const Quaternion& rhs );
		Quaternion operator-=( const Quaternion& rhs );
		Quaternion operator*=( const Quaternion& rhs );
		Quaternion operator*=( float rhs );
		Quaternion operator&=( const Quaternion& rhs );
		Quaternion operator|=( const Quaternion& rhs );
		Quaternion operator^=( const Quaternion& rhs );

		Quaternion operator-() const;

		Quaternion operator+( const Quaternion& rhs ) const;
		Quaternion operator-( const Quaternion& rhs ) const;
		Quaternion operator*( const Quaternion& rhs ) const;
		Quaternion operator*( float rhs ) const;
		Quaternion operator&( const Quaternion& rhs ) const;
		Quaternion operator|( const Quaternion& rhs ) const;
		Quaternion operator^( const Quaternion& rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		�X�J���[��Z
	*/
	Quaternion operator*( float lhs, const Quaternion& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		�N�H�[�^�j�I�����Z
	*/
	class Quat
	{
		Quat();	// �����֎~�I

	public:
		static Quaternion	RotationX( float Radian );
		static Quaternion	RotationY( float Radian );
		static Quaternion	RotationZ( float Radian );
		static Quaternion	RotationXYZ( const Vector3& Radian );
		static Quaternion	RotationAxis( const Vector3& Axis, float Radian );
		static Vector3		GetRotationAngle( const Quaternion& value );
		static Quaternion	Conjugate( const Quaternion& value );
		static Quaternion	Rotate( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Lerp( const Quaternion& lhs, const Quaternion& rhs, float value );
		static Quaternion	Slerp( const Quaternion& lhs, const Quaternion& rhs, float value );
		static Quaternion	Negative( const Quaternion& value );
		static Quaternion	Add( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Subtract( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Multiply( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Divide( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Scale( const Quaternion& vec, float actor );
		static Quaternion	Reciprocal( const Quaternion& value );
		static Quaternion	ReciprocalSqrt( const Quaternion& value );
		static Quaternion	Normal( const Quaternion& value );
		static Quaternion	Sqrt( const Quaternion& value );
		static Quaternion	Length( const Quaternion& value );
		static Quaternion	LengthSq( const Quaternion& value );
		static Quaternion	Dot( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Dot3( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Cross3( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Min( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Max( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Abs( const Quaternion& value );

		static Quaternion	And( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	AndNot( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Or( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Xor( const Quaternion& lhs, const Quaternion& rhs );

		static Quaternion	SplatX( const Quaternion& value );
		static Quaternion	SplatY( const Quaternion& value );
		static Quaternion	SplatZ( const Quaternion& value );
		static Quaternion	SplatW( const Quaternion& value );

		static Quaternion	SwizzleX( const Quaternion& toX, const Quaternion& toY, const Quaternion& toZ, const Quaternion& toW );
		static Quaternion	MergeXYZ_W( const Quaternion& xyz, const Quaternion& w );

		static Quaternion	Set( float x, float y, float z, float w );
		static Quaternion	SetInt( unsigned x, unsigned y, unsigned z, unsigned w );
		static Quaternion	LoadU( const float* pFloat4 );
		static Quaternion	LoadA( const float* pFloat4Aligned );
		static Quaternion	Zero();
		static void		Prefetch( const Quaternion* pAddress );
		static void		StoreU( float* pFloat4, const Quaternion& source );
		static void		StoreA( float* pFloat4Aligned, const Quaternion& source );
		static Quaternion	Fill( float value );
		static Quaternion	FReciprocal( const Quaternion& value );
		static Quaternion	FReciprocalSqrt( const Quaternion& value );
		static Quaternion	HorizonalAdd( const Quaternion& value );
		static Quaternion	HorizonalAnd( const Quaternion& value );
		static Quaternion	HorizonalOr( const Quaternion& value );

		static Quaternion	Equal( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	NotEqual( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Greater( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	GreaterEqual( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	Less( const Quaternion& lhs, const Quaternion& rhs );
		static Quaternion	LessEqual( const Quaternion& lhs, const Quaternion& rhs );

		static bool		ArbitraryTrue( const Quaternion& value );
		static bool		ExistTrue( const Quaternion& value );
		static bool		ArbitraryFalse( const Quaternion& value );
		static bool		ExistFalse( const Quaternion& value );
		static bool		ArbitraryTrue3( const Quaternion& value );
		static bool		ExistTrue3( const Quaternion& value );
		static bool		ArbitraryFalse3( const Quaternion& value );
		static bool		ExistFalse3( const Quaternion& value );

		static Quaternion	UnitX();
		static Quaternion	UnitY();
		static Quaternion	UnitZ();
		static Quaternion	UnitW();

		//---------------------------------------------------------------------------//
		/**
			@brief		�V���b�t��
			@par		SSE��shuffle���߂ɏ]���ē���ւ����܂��B
						XY�ɍ��v�f�AZW�ɉE�v�f������܂��B��̓I�ɂ�
						lhs = (V0,V1,V2,V3)
						rhs = (W0,W1,W2,W3)
						��
						result = (Va,Vb,Wc,Wd)
		*/
		template<int a, int b, int c, int d>
		static Quaternion	Shuffle( const Quaternion& lhs, const Quaternion& rhs )
		{
			return _mm_shuffle_ps( lhs.v, rhs.v, _MM_SHUFFLE(d,c,b,a) );
		}

		//---------------------------------------------------------------------------//
		/**
			@brief		�V���b�t��
			@par		SSE��shuffle���߂ō��E�����I�y�����h���w�肷��̂Ɠ��`�ł��B
		*/
		template<int a, int b, int c, int d>
		static Quaternion	Shuffle( const Quaternion& value )
		{
			return Shuffle<a,b,c,d>( value, value );
		}


		static const Quaternion	One;		///< 1.0f
		static const Quaternion	Half;		///< 0.5f
		static const Quaternion	NegOne;		///< -1.0f
		static const Quaternion	NegHalf;	///< -0.5f
	};
}
}
}


/**
	@file
	@brief SIMD�x�N�g��
	@author ��
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	//---------------------------------------------------------------------------//
	/**
		@brief		SIMD�x�N�g��
	*/
	class VectorS
		: public Object::MemoryObject
	{
	public:
		union
		{
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
			struct
			{
				Sint32 ix;
				Sint32 iy;
				Sint32 iz;
				Sint32 iw;
			};
			struct
			{
				Uint32 ux;
				Uint32 uy;
				Uint32 uz;
				Uint32 uw;
			};
			Uint128 v;
		};

	public:
		VectorS();
		VectorS( const VectorS& rhs );
		VectorS( const Vector3& rhs );
		VectorS( const Vector4& rhs );
		VectorS( const Uint128& rhs );
		VectorS( float _x, float _y, float _z );
		VectorS( float _x, float _y, float _z, float _w );

		VectorS& operator=( const Vector2& rhs );
		VectorS& operator=( const Vector3& rhs );
		VectorS& operator=( const Vector4& rhs );
		VectorS& operator=( const VectorS& rhs );
		VectorS& operator+=( const VectorS& rhs );
		VectorS& operator-=( const VectorS& rhs );
		VectorS& operator*=( const VectorS& rhs );
		VectorS& operator*=( float rhs );
		VectorS& operator&=( const VectorS& rhs );
		VectorS& operator|=( const VectorS& rhs );
		VectorS& operator^=( const VectorS& rhs );

		VectorS operator-() const;

		VectorS operator+( const VectorS& rhs ) const;
		VectorS operator-( const VectorS& rhs ) const;
		VectorS operator*( const VectorS& rhs ) const;
		VectorS operator*( float rhs ) const;
		VectorS operator&( const VectorS& rhs ) const;
		VectorS operator|( const VectorS& rhs ) const;
		VectorS operator^( const VectorS& rhs ) const;
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		�X�J���[��Z
	*/
	VectorS operator*( float lhs, const VectorS& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		SIMD�x�N�g�����Z
	*/
	class VecS
	{
		VecS();	// �����֎~�I

	public:
		static VectorS	Rotate( const VectorS& v, const Quaternion& q );
		static VectorS	Negative( const VectorS& value );
		static VectorS	Add( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Subtract( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Multiply( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Divide( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Scale( const VectorS& vec, float actor );
		static VectorS	Reciprocal( const VectorS& value );
		static VectorS	ReciprocalSqrt( const VectorS& value );
		static VectorS	Normal( const VectorS& value );
		static VectorS	Normal3( const VectorS& value );
		static VectorS	Sqrt( const VectorS& value );
		static VectorS	Length( const VectorS& value );
		static VectorS	Length3( const VectorS& value );
		static VectorS	LengthSq( const VectorS& value );
		static VectorS	LengthSq3( const VectorS& value );
		static VectorS	Dot( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Dot3( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Cross3( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Min( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Max( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Abs( const VectorS& value );

		static VectorS	And( const VectorS& lhs, const VectorS& rhs );
		static VectorS	AndNot( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Or( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Xor( const VectorS& lhs, const VectorS& rhs );

		static VectorS	SplatX( const VectorS& value );
		static VectorS	SplatY( const VectorS& value );
		static VectorS	SplatZ( const VectorS& value );
		static VectorS	SplatW( const VectorS& value );

		static VectorS	SwizzleX( const VectorS& toX, const VectorS& toY, const VectorS& toZ, const VectorS& toW );
		static VectorS	MergeXYZ_W( const VectorS& xyz, const VectorS& w );

		static VectorS	Set( float x, float y, float z, float w );
		static VectorS	SetInt( unsigned x, unsigned y, unsigned z, unsigned w );
		static VectorS	LoadU( const float* pFloat4 );
		static VectorS	LoadA( const float* pFloat4Aligned );
		static VectorS	Zero();
		static void		Prefetch( const VectorS* pAddress );
		static void		StoreU( float* pFloat4, const VectorS& source );
		static void		StoreA( float* pFloat4Aligned, const VectorS& source );
		static VectorS	Fill( float value );
		static VectorS	FReciprocal( const VectorS& value );
		static VectorS	FReciprocalSqrt( const VectorS& value );
		static VectorS	HorizonalAdd( const VectorS& value );
		static VectorS	HorizonalAnd( const VectorS& value );
		static VectorS	HorizonalOr( const VectorS& value );

		static VectorS	Equal( const VectorS& lhs, const VectorS& rhs );
		static VectorS	NotEqual( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Greater( const VectorS& lhs, const VectorS& rhs );
		static VectorS	GreaterEqual( const VectorS& lhs, const VectorS& rhs );
		static VectorS	Less( const VectorS& lhs, const VectorS& rhs );
		static VectorS	LessEqual( const VectorS& lhs, const VectorS& rhs );

		static bool		ArbitraryTrue( const VectorS& value );
		static bool		ExistTrue( const VectorS& value );
		static bool		ArbitraryFalse( const VectorS& value );
		static bool		ExistFalse( const VectorS& value );
		static bool		ArbitraryTrue3( const VectorS& value );
		static bool		ExistTrue3( const VectorS& value );
		static bool		ArbitraryFalse3( const VectorS& value );
		static bool		ExistFalse3( const VectorS& value );

		/**
			@brief ��������
			@author ����
			@param value		[in] �x�N�g��
			@param component	[in] ���������i�P�ʃx�N�g���j
			@note
			�x�N�g�����琬�������̐�������菜���B
		*/
		static VectorS	RemoveComponent( const VectorS& value, const VectorS& component );

		/**
			@brief ��������
			@author ����
			@param value		[in] �x�N�g��
			@param component	[in] ���������i�P�ʃx�N�g���j
			@note
			�x�N�g�����琬�������̐�������菜���B
		*/
		static VectorS	RemoveComponent3( const VectorS& value, const VectorS& component );

		/**
			@brief �p�x�擾
			@author ����
			@param lhs		[in] �P�ʃx�N�g��
			@param rhs		[in] �P�ʃx�N�g��
			@return �p�x�i1��2�΁A0�`�΁j
			@note
			hs����rhs�܂ŉ��x���邩�擾����B
		*/
		static float	AngleAbs3( const VectorS& lhs, const VectorS& rhs );

		/**
			@brief �p�x�擾
			@author ����
			@param axis		[in] ���i�P�ʃx�N�g���j
			@param lhs		[in] �x�N�g��
			@param rhs		[in] �x�N�g��
			@return �p�x�i1��2�΁A-�΁`�΁j
			@note
			�C�ӂ̎������lhs����rhs�܂ŉ��x���邩���v����̉�]�Ŏ擾����Blhs��axis�Arhs��axis�����s���Ă���K�v�͂Ȃ��B
		*/
		static float	Angle3( const VectorS& axis, const VectorS& lhs, const VectorS& rhs );

		/**
			@brief X���P�ʃx�N�g��
			@author ��
			@note
			X�������̒P�ʃx�N�g�����擾����B
		*/
		static VectorS	UnitX();

		/**
			@brief Y���P�ʃx�N�g��
			@author ��
			@note
			X�������̒P�ʃx�N�g�����擾����B
		*/
		static VectorS	UnitY();

		/**
			@brief Z���P�ʃx�N�g��
			@author ��
			@note
			X�������̒P�ʃx�N�g�����擾����B
		*/
		static VectorS	UnitZ();

		/**
			@brief W���P�ʃx�N�g��
			@author ��
			@note
			X�������̒P�ʃx�N�g�����擾����B
		*/
		static VectorS	UnitW();

		//---------------------------------------------------------------------------//
		/**
			@brief		�V���b�t��
			@par		SSE��shuffle���߂ɏ]���ē���ւ����܂��B
						XY�ɍ��v�f�AZW�ɉE�v�f������܂��B��̓I�ɂ�
						lhs = (V0,V1,V2,V3)
						rhs = (W0,W1,W2,W3)
						��
						result = (Va,Vb,Wc,Wd)
		*/
		template<int a, int b, int c, int d>
		static VectorS	Shuffle( const VectorS& lhs, const VectorS& rhs )
		{
			return _mm_shuffle_ps( lhs.v, rhs.v, _MM_SHUFFLE(d,c,b,a) );
		}

		//---------------------------------------------------------------------------//
		/**
			@brief		�V���b�t��
			@par		SSE��shuffle���߂ō��E�����I�y�����h���w�肷��̂Ɠ��`�ł��B
		*/
		template<int a, int b, int c, int d>
		static VectorS	Shuffle( const VectorS& value )
		{
			return Shuffle<a,b,c,d>( value, value );
		}


		static const VectorS	One;		///< 1.0f
		static const VectorS	Half;		///< 0.5f
		static const VectorS	NegOne;		///< -1.0f
		static const VectorS	NegHalf;	///< -0.5f
	};
}
}
}


/**
	@file
	@brief �s�񉉎Z
	@author ��
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	class Vector3;

	//---------------------------------------------------------------------------//
	/**
		@brief		�s��
	*/
	class Matrix
		: public Object::MemoryObject
	{
	public:
		union
		{
			struct
			{
				VectorS	x;
				VectorS	y;
				VectorS	z;
				VectorS	w;
			};
			struct
			{
				VectorS	r[4];
			};
		};

	public:
		Matrix();
		Matrix( const Matrix& rhs );
		Matrix(
			float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33
			);
		Matrix(
			const VectorS& r0,
			const VectorS& r1,
			const VectorS& r2,
			const VectorS& r3
			);

		Matrix& operator=( const Matrix& rhs );
		Matrix& operator+=( const Matrix& rhs );
		Matrix& operator-=( const Matrix& rhs );
		Matrix& operator*=( const Matrix& rhs );
		Matrix& operator*=( float rhs );

		Matrix operator+( const Matrix& rhs ) const;
		Matrix operator-( const Matrix& rhs ) const;
		Matrix operator*( const Matrix& rhs ) const;
		Matrix operator*( float rhs ) const;

		const VectorS& GetRight() const;
		const VectorS& GetUp() const;
		const VectorS& GetFront() const;
		const VectorS& GetPosition() const;

		void SetRight( const VectorS& value );
		void SetUp( const VectorS& value );
		void SetFront( const VectorS& value );
		void SetPosition( const VectorS& value );
	};

	//---------------------------------------------------------------------------//
	/**
		@brief		�X�J���[��Z
	*/
	Vector4 operator*( float lhs, const Vector4& rhs );

	//---------------------------------------------------------------------------//
	/**
		@brief		�s��I�y���[�^
	*/
	class MatX
	{
		MatX();	// �����֎~�I

	public:
		/**
			@brief �p�x�擾
			@author ��
			@param value	[in] �s��
			@return �p�x
			@note
			�s�񂩂��]�p�x���擾����B
		*/
		static Vector3	GetRotationAngle( const Matrix& value );

		/**
			@brief ���Z
			@author ��
			@param lhs	[in] �s��
			@param rhs	[in] �s��
			@note
			�s�񓯎m�����Z�������ʂ̍s��𐶐�����B
		*/
		static Matrix	Add( const Matrix& lhs, const Matrix& rhs );

		/**
			@brief ���Z
			@author ��
			@param lhs	[in] �s��
			@param rhs	[in] �s��
			@note
			�s�񓯎m�����Z�������ʂ̍s��𐶐�����B
		*/
		static Matrix	Subtract( const Matrix& lhs, const Matrix& rhs );

		
		/**
			@brief ��Z
			@author ��
			@param lhs	[in] �s��
			@param rhs	[in] �s��
			@note
			�s�񓯎m����Z�������ʂ̍s��𐶐�����B
		*/
		static Matrix	Multiply( const Matrix& lhs, const Matrix& rhs );

		/**
			@brief �X�J���[�{
			@author ��
			@param value	[in] �s��
			@param factor	[in] �{��
			@note
			���ׂĂ̐������X�J���[�{�����s��𐶐�����B
		*/
		static Matrix	Scale( const Matrix& value, float factor );

		/**
			@brief �]�u�s�񐶐�
			@author ��
			@param value	[in] �s��
			@note
			�w�肳�ꂽ�s��̓]�u�s��𐶐�����B
		*/
		static Matrix	Transpose( const Matrix& value );

		/**
			@brief �t�s�񐶐�
			@author ��
			@param value	[in] �s��
			@note
			�w�肳�ꂽ�s��̋t�s��𐶐�����B
		*/
		static Matrix	Inverse( const Matrix& value );

		/**
			@brief �t�s�񐶐�
			@author ��
			@param value	[in] ��]�ړ��s��
			@note
			�w�肳�ꂽ��]�ړ��݂̂̍s��̋t�s��𐶐�����B
		*/
		static Matrix	InverseRT( const Matrix& value );

		/**
			@brief �t�s�񐶐�
			@author ��
			@param value	[in] �g���]�ړ��s��
			@note
			�w�肳�ꂽ�g���]�ړ��݂̂̍s��̋t�s��𐶐�����B
		*/
		static Matrix	InverseSRT( const Matrix& value );

		/**
			@brief �s�񎮐���
			@author ����
			@param value	[in] �g���]�ړ��s��
			@note
			�w�肳�ꂽ�g���]�ړ��݂̂̍s��̍s�񎮂��擾����B
		*/
		static float	DeterminantSRT( const Matrix& value );

		/**
			@brief �ړ��s�񐶐�
			@author ��
			@param translation	[in] �ړ�����
			@note
			�ړ����s���s��𐶐�����B
		*/
		static Matrix	Translation( const Vector3& translation );

		/**
			@brief �ړ��s�񐶐�
			@author ��
			@param translation	[in] �ړ�����
			@note
			�ړ����s���s��𐶐�����B
		*/
		static Matrix	Translation( const VectorS& translation );

		/**
			@brief X����]�s�񐶐�
			@author ��
			@param angle	[in] �p�x�i1��2�΁j
			@note
			X������Ɏ��v����̉�]���s���s��𐶐�����B
		*/
		static Matrix	RotationX( float angle );

		/**
			@brief Y����]�s�񐶐�
			@author ��
			@param angle	[in] �p�x�i1��2�΁j
			@note
			Y������Ɏ��v����̉�]���s���s��𐶐�����B
		*/
		static Matrix	RotationY( float angle );

		/**
			@brief Z����]�s�񐶐�
			@author ��
			@param angle	[in] �p�x�i1��2�΁j
			@note
			Z������Ɏ��v����̉�]���s���s��𐶐�����B
		*/
		static Matrix	RotationZ( float angle );

		/**
			@brief �C�ӎ���]�s�񐶐�
			@author ����
			@param axis		[in] ��
			@param angle	[in] �p�x�i1��2�΁j
			@note
			�C�ӂ̎�����Ɏ��v����̉�]���s���s��𐶐�����B
		*/
		static Matrix	RotationAxis( const Vector3& axis, float angle );
		static Matrix	RotationAxis( const VectorS& axis, float angle );

		/**
			@brief �g��k���s�񐶐�
			@author ��
			@param scaling	[in] �g��k����
			@note
			�g��k�����s���s��𐶐�����B
		*/
		static Matrix	Scaling( const Vector3& scaling );

		/**
			@brief �g��k���s�񐶐�
			@author ��
			@param scaling	[in] �g��k����
			@note
			�g��k�����s���s��𐶐�����B
		*/
		static Matrix	Scaling( const VectorS& scaling );

		/**
			@brief ������W�n�r���[�s�񐶐�
			@author ��
			@param eye		[in] �J�����̒����Ώۂ̍��W
			@param at		[in] �J�����̍��W
			@param up		[in] �J�����̏����
			@note
			������W�n�r���[�s��𐶐�����B
		*/
		static Matrix	LookAtLH( const VectorS& eye, const VectorS& at, const VectorS& up );

		/**
			@brief ������W�n�p�[�X�y�N�e�B�u�ˉe�s�񐶐�
			@author ��
			@param ovY			[in] y�����̎���(���W�A��)
			@param aspect		[in] �c����
			@param zn			[in] �߂��r���[���ʂ�Z�l
			@param zf			[in] �����r���[���ʂ�Z�l
			@note
			������W�n�p�[�X�y�N�e�B�u�ˉe�s��𐶐�����B
		*/
		static Matrix	PerspectiveFovLH( float ovY, float aspect, float zn, float zf );

		/**
			@brief ������W�n���ˉe�s�񐶐�
			@author ��
			@param width		[in] ���̒���
			@param height		[in] �c�̒���
			@param zn			[in] �߂��r���[���ʂ�Z�l
			@param zf			[in] �����r���[���ʂ�Z�l
			@note
			������W�n���ˉe�s��𐶐�����B
		*/
		static Matrix	OrthographicLH( float width, float height, float zn, float zf );

		/**
			@brief ��s�񐶐�
			@author ��
			@note
			��s��𐶐�����B
		*/
		static const Matrix& Zero();

		/**
			@brief �P�ʍs�񐶐�
			@author ��
			@note
			�P�ʍs��𐶐�����B
		*/
		static const Matrix& Identity();

		/**
			@brief ��]�s�񐶐�
			@author ��
			@param Quat		[in] �ϊ������N�H�[�^�j�I��
			@note
			�N�H�[�^�j�I�������]�s��𐶐�����B
		*/
		static Matrix	Rotation( const Quaternion& Quat );

		/**
			@brief �x�N�g�����Z
			@author ��
			@param vIn		[in] �|����x�N�g��
			@param mIn		[in] �|����s��
			@note
			�x�N�g���ɍs����|�����l���o�͂���B�ړ��͍s��Ȃ��B
		*/
		static Vector3	Transform3( const Vector3& vIn, const Matrix& mIn );

		/**
			@brief �x�N�g�����Z
			@author ��
			@param vIn		[in] �|����x�N�g��
			@param mIn		[in] �|����s��
			@note
			�x�N�g���ɍs����|�����l���o�͂���B�ړ��͍s���B
		*/
		static Vector3	Transform4( const Vector3& vIn, const Matrix& mIn );

		/**
			@brief �x�N�g�����Z
			@author ��
			@param vIn		[in] �|����x�N�g��
			@param mIn		[in] �|����s��
			@note
			�x�N�g���ɍs����|�����l���o�͂���B�ړ��͍s��Ȃ��B
		*/
		static VectorS	Transform3( const VectorS& vIn, const Matrix& mIn );

		/**
			@brief �x�N�g�����Z
			@author ��
			@param vIn		[in] �|����x�N�g��
			@param mIn		[in] �|����s��
			@note
			�x�N�g���ɍs����|�����l���o�͂���B�ړ��͍s���B
		*/
		static VectorS	Transform4( const VectorS& vIn, const Matrix& mIn );

		/**
			@brief �x�N�g�����Z
			@author ��
			@param vIn		[in] �|����x�N�g��
			@param mIn		[in] �|����s��
			@note
			�w�肳�ꂽ�s��ɂ�� 3D �x�N�g�����g�����X�t�H�[�����A���̌��ʂ� w = 1 �Ɏˉe����B
		*/
		static Vector3	TransformProjection( const Vector3& vIn, const Matrix& mIn );

		/**
			@brief �x�N�g�����Z
			@author ��
			@param vIn		[in] �|����x�N�g��
			@param mIn		[in] �|����s��
			@note
			�w�肳�ꂽ�s��ɂ�� 3D �x�N�g�����g�����X�t�H�[�����A���̌��ʂ� w = 1 �Ɏˉe����B
		*/
		static VectorS	TransformProjection( const VectorS& vIn, const Matrix& mIn );

		/**
			@brief �C�ӎ��Œ�r���{�[�h�s�񐶐�
			@author ����
			@param vAxis		[in] ��
			@param vCameraPosition	[in] �J�����̍��W
			@param vBillboardPosition	[in] �r���{�[�h�̍��W
			@note
			���_����C�ӎ����Œ肵���r���{�[�h�̍s��𐶐�����B
		*/
		static Matrix	AxisBillboard( const VectorS& vAxis, const VectorS& vCameraPosition, const VectorS& vBillboardPosition );

		/**
			@brief ���ʔ��˗p�s�񐶐�
			@author �t���`
			@param mCamera			[in] �J�����̍s��
			@param Plane			[in] ���˂����镽��
			@note
			���ʔ��˗p�̍s��𐶐����܂��B
		*/
		static Matrix	Reflect( const Matrix& mCamera, const Kernel::Collision::Plane& Plane );
	};
}
}
}


/**
	@file
	@brief ���
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
namespace Interpolation
{
	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Linear( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		Rate *= Rate;
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(TimeAll-Time) / toF(TimeAll);
		Rate *= Rate;
		return (TypeA)(toF(End) + toF(Start - End) * Rate);
	}

	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(TimeAll-Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(End) + toF(Start - End) * Rate);
	}

	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Add4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief �����^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		float Rate = toF(TimeAll-Time) / toF(TimeAll);
		Rate *= Rate;
		Rate *= Rate;
		Rate *= Rate;
		return (TypeA)(toF(End) + toF(Start - End) * Rate);
	}

	/**
		@brief �����������^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief �����������^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief �����������^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief �����������^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd2( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub2( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add2( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief �����������^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA AddSub4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Add4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Sub4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief �����������^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		�����������^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA SubAdd4( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		TypeA Middle = (End + Start) / (TypeA)2;
		TypeB MiddleTime = TimeAll / (TypeB)2;

		if ( Time < MiddleTime )
		{
			return Sub4( Start, Middle, MiddleTime, Time );
		}
		else
		{
			return Add4( Middle, End, TimeAll-MiddleTime, Time-MiddleTime );
		}
	}

	/**
		@brief sin�^��
		@author �t���`
		@param Start	[in] �J�n�l
		@param End		[in] �I���l
		@param TimeAll	[in] End���B����
		@param Time		[in] ���ݎ���
		@return Time�ɂ�����l
		@note
		sin�g�ŉ^�����s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	template <typename TypeA, typename TypeB>
	inline TypeA Sin( TypeA Start, TypeA End, TypeB TimeAll, TypeB Time )
	{
		Sint32 Angle = (Sint32)( Kernel::Math::DegToAngle(180) * Time / TimeAll);
		float Rate = Kernel::Math::FastSin( Angle );
		return (TypeA)(toF(Start) + toF(End - Start) * Rate);
	}

	/**
		@brief �l���B�����
		@author �t���`
		@param Start	[in] �J�n�l
		@param Center	[in] ���Ԓl
		@param End		[in] �I���l
		@param Time	[in] ���ݎ��ԁi0.0�`1.0�j
		@return Time�ɂ�����l
		@note
		�l���B����Ԃ��s���Ƃ��̕�Ԓl���擾���܂��B
	*/
	inline float Neville( float Start, float Center, float End, float Time )
	{
		Time *= 2.0f;
		Start = Center + (Center - Start) * (Time - 1.0f);
		Center = End + (End - Center) * (Time - 2.0f);
		return Center + (Center - Start) * (Time - 2.0f) * 0.5f;
	}
}
}
}
}


/**
	@file
	@brief ����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief ����
		@author �t���`
	*/
	class Ray
	{
	public:
		Kernel::Math::VectorS	Point[2];

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param start	[in] �n�_
			@param end		[in] �I�_
		*/
		Ray( const Kernel::Math::VectorS& start, const Kernel::Math::VectorS& end )
		{
			Point[0] = start;
			Point[1] = end;
		}

	public:
		/**
			@brief Ray����
			@author �t���`
			@param ray		[out] �����s�{�b�N�X�i�[��
			@param Start	[in] �n�_
			@param End		[in] �I�_
			@note
			�����𐶐����܂��B
		*/
		static void Create( Ray& ray, const Kernel::Math::VectorS& Start, const Kernel::Math::VectorS& End );
	};
}
}
}

/**
	@file
	@brief �����s�{�b�N�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief �����s�{�b�N�X
		@author �t���`
	*/
	class AABB
	{
	public:
		Kernel::Math::VectorS	Min;		///< �ŏ��_
		Kernel::Math::VectorS	Max;		///< �ő�_

	public:
		/**
			@brief AABB����
			@author �t���`
			@param aabb	[out] �����s�{�b�N�X�i�[��
			@param Min	[in] �{�b�N�X�̍ŏ��_
			@param Max	[in] �{�b�N�X�̍ő�X
			@note
			�����s�{�b�N�X�𐶐����܂��B
		*/
		static void Create( AABB& aabb, const Kernel::Math::VectorS& Min, const Kernel::Math::VectorS& Max );
		/**
			@brief AABB����
			@author �t���`
			@param aabb		[out] �����s�{�b�N�X�i�[��
			@param pPoints	[in] �|�C���g�̃e�[�u��
			@param Count	[in] pPoint�̃|�C���g��
			@note
			�����s�{�b�N�X�𐶐����܂��B
		*/
		static void Create( AABB& aabb, const Kernel::Math::VectorS* pPoints, Sint32 Count );
	};
}
}
}

/**
	@file
	@brief ��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief ��
		@author �t���`
	*/
	class Sphere
	{
	public:
		Kernel::Math::VectorS	Center;		///< ���̒��S
		float					Radius;		///< ���̔��a
		AABB					AaBb;		///< ����AABB

	public:
		/**
			@brief ������
			@author �t���`
			@param sphere	[out] ���i�[��
			@param Center	[in] ���̒��S
			@param Radius	[in] ���̔��a
			@note
			���𐶐����܂��B
		*/
		static void Create( Sphere& sphere, const Kernel::Math::VectorS& Center, float Radius );
		/**
			@brief ������
			@author �t���`
			@param sphere	[out] ���i�[��
			@param pPoints	[in] �|�C���g�̃e�[�u��
			@param Count	[in] pPoint�̃|�C���g��
			@note
			���𐶐����܂��B
		*/
		static void Create( Sphere& sphere, const Kernel::Math::VectorS* pPoints, Sint32 Count );
	};
}
}
}

/**
	@file
	@brief ��������
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief ��������
		@author �t���`
	*/
	class Plane
	{
	public:
		Kernel::Math::VectorS	Normal;

	public:
		Plane()
			: Normal	( 0.0f, 0.0f, 0.0f, 0.0f )
		{
		}

		/**
			@brief ���ʐ���
			@author �t���`
			@param plane	[out] ���ʊi�[��
			@param p0		[in] ���ʏ�̓_
			@param p1		[in] ���ʏ�̓_
			@param p2		[in] ���ʏ�̓_
			@note
			���ʂ𐶐����܂��B
		*/
		static void Create( Plane& plane, const Kernel::Math::VectorS& p0, const Kernel::Math::VectorS& p1, const Kernel::Math::VectorS& p2 );
		/**
			@brief ���ʐ���
			@author �t���`
			@param plane	[out] ���ʊi�[��
			@param Normal	[in] ���ʂ̖@��
			@param d		[in] ���ʂ̋���
			@note
			���ʂ𐶐����܂��B
		*/
		static void Create( Plane& plane, const Kernel::Math::VectorS& Normal, float d );
		/**
			@brief �����擾
			@author �t���`
			@param plane	[in] ����
			@param Point	[in] ����������_
			@note
			���ʂ���̋������擾���܂��B
		*/
		static float GetDistance( const Plane& plane, const Kernel::Math::VectorS& Point );
	};
}
}
}

/**
	@file
	@brief ��]����Z�ʑ�
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief ��]����Z�ʑ�
		@author �t���`
	*/
	class OBB
	{
	public:
		enum
		{
			PLANE_FRONT,
			PLANE_BACK,
			PLANE_TOP,
			PLANE_BOTTOM,
			PLANE_LEFT,
			PLANE_RIGHT,
			PLANE_MAX,
		};
		enum
		{
			POINT_FRONT_BOTTOM_LEFT,
			POINT_FRONT_BOTTOM_RIGHT,
			POINT_FRONT_TOP_LEFT,
			POINT_FRONT_TOP_RIGHT,
			POINT_BACK_BOTTOM_LEFT,
			POINT_BACK_BOTTOM_RIGHT,
			POINT_BACK_TOP_LEFT,
			POINT_BACK_TOP_RIGHT,
			POINT_MAX,
		};

	public:
		Plane					Plane[PLANE_MAX];	///< ��]����Z�ʑ̖̂�
		Kernel::Math::VectorS	Point[POINT_MAX];	///< ��]����Z�ʑ̂̓_
		AABB					AaBb;				///< ��]����Z�ʑ̂�AABB

	public:
		/**
			@brief ��]����Z�ʑ̐���
			@author �t���`
			@param Obb		[out] ��]����Z�ʑ̊i�[��
			@param Camera	[in] ��]����Z�ʑ̂𐶐�����J����
			@note
			��]����Z�ʑ̂𐶐����܂��B
		*/
		static void Create( OBB& Obb, const Kernel::Math::Camera& Camera );
		/**
			@brief ��]����Z�ʑ̐���
			@author �t���`
			@param Obb		[out] ��]����Z�ʑ̊i�[��
			@param AaBb		[in] ��]����Z�ʑ̂𐶐�����AABB
			@note
			��]����Z�ʑ̂𐶐����܂��B
		*/
		static void Create( OBB& Obb, const AABB& AaBb );
	};
}
}
}


/**
	@file
	@brief �J����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Collision
{
	/**
		@brief �ʂɑ΂���ʒu
		@author �t���`
	*/
	enum eSide
	{
		SIDE_FRONT,
		SIDE_BACK,
		SIDE_BOTH,
	};

	//------------------------------------------------------------

	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Ray& lhs, const Sphere& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Ray& lhs, const AABB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Ray& lhs, const OBB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Ray& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Sphere& lhs, const Sphere& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Sphere& lhs, const AABB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Sphere& lhs, const OBB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const Sphere& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const AABB& lhs, const AABB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const AABB& lhs, const OBB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const AABB& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const OBB& lhs, const OBB& rhs );
	/**
		@brief �ڐG����
		@author �t���`
		@param lhs	[in] �ڐG����p�̃R���W����
		@param rhs	[in] �ڐG����p�̃R���W����
		@return �������Ă����true
		@note
		��̃R���W�����̐ڐG��������܂��B
	*/
	bool IsIntersect( const OBB& lhs, const Plane& rhs );

	//------------------------------------------------------------

	/**
		@brief �ʂ̑΂���ʒu�̎擾
		@author �t���`
		@param lhs	[in] �Ώۂ̖�
		@param rhs	[in] �Ώۂ̔�
		@return ���ʂɑ΂��Ăǂ��瑤�ɂ��邩
		@note
		���ʂɑ΂��Ăǂ��瑤�ɂ��邩�𒲂ׂ܂��B
	*/
	eSide Side( const Plane& lhs, const AABB& rhs );
	/**
		@brief �ʂ̑΂���ʒu�̎擾
		@author �t���`
		@param lhs	[in] �Ώۂ̖�
		@param rhs	[in] �Ώۂ̋�
		@return ���ʂɑ΂��Ăǂ��瑤�ɂ��邩
		@note
		���ʂɑ΂��Ăǂ��瑤�ɂ��邩�𒲂ׂ܂��B
	*/
	eSide Side( const Plane& lhs, const Sphere& rhs );
}
}
}


/**
	@file
	@brief �J����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Math
{
	/**
		@brief �J�����N���X
		@author �t���`
	*/
	class Camera
		: public Object::MemoryObject
	{
	protected:
		Matrix					m_mProjection;
		Kernel::Collision::OBB	m_Frustum;
		VectorS					m_vAxisX;
		VectorS					m_vAxisY;
		VectorS					m_vAxisZ;
		VectorS					m_vPosition;
		float					m_NearZ;
		float					m_FarZ;
		float					m_Aspect;
		float					m_Fov;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Camera();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param value	[in] �����l
		*/
		Camera( const Camera& value );
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		virtual ~Camera();

	public:
		/**
			@brief �t���X�^���̍X�V
			@author �t���`
		*/
		void UpdateFrustum();
		/**
			@brief �����ϊ��p�v���W�F�N�V�����s�񐶐�
			@author �t���`
			@param ovY		[in] ��p
			@param aspect	[in] �A�X�y�N�g��
			@param zn		[in] Z�߃N���b�v����
			@param zf		[in] Z���N���b�v����
			@note
			��ʓI�ȍ�����W�n�v���W�F�N�V�����s��𐶐����܂��B
		*/
		void PerspectiveFovLH( float ovY, float aspect, float zn, float zf );
		/**
			@brief ���s���e�p�v���W�F�N�V�����s�񐶐�
			@author �t���`
			@param width	[in] ��
			@param height	[in] ����
			@param zn		[in] Z�߃N���b�v����
			@param zf		[in] Z���N���b�v����
			@note
			���s���e����ׂ̍�����W�n�v���W�F�N�V�����s��𐶐����܂��B
		*/
		void OrthographicLH( float width, float height, float zn, float zf );
		/**
			@brief ���s���e�p�v���W�F�N�V�����s�񐶐�
			@author �t���`
			@note
			�J�����̏�Ԃ����������܂��B<BR>
			���W(0.0, 0.0, 0.0)�������(0.0, 0.0, 1.0)�����Ă����ԂɂȂ�܂��B
		*/
		void Identity();
		/**
			@brief �ړ�
			@author �t���`
			@param vMove	[in] �ړ���
			@note
			�J�����̈ړ������܂��B
		*/
		void Translation( const VectorS& vMove );
		/**
			@brief X����]
			@author �t���`
			@param Angle	[in] ��]�p�x�i���W�A���j
			@note
			�J������X����]�����܂��B
		*/
		void RotationX( float Angle );
		/**
			@brief Y����]
			@author �t���`
			@param Angle	[in] ��]�p�x�i���W�A���j
			@note
			�J������Y����]�����܂��B
		*/
		void RotationY( float Angle );
		/**
			@brief Z����]
			@author �t���`
			@param Angle	[in] ��]�p�x�i���W�A���j
			@note
			�J������Z����]�����܂��B
		*/
		void RotationZ( float Angle );
		/**
			@brief �C�ӎ��_�J����
			@author �t���`
			@param vPosition	[in] �J�����̈ʒu
			@param vTarget		[in] �J�����̒����ʒu
			@param Bank		[in] �o���N�p�x�i�X���j
			@note
			�w�肵���ʒu����w�肵���ꏊ������J�������쐬���܂��B
		*/
		void LookAt( const VectorS& vPosition, const VectorS& vTarget, float Bank );
		/**
			@brief �C�ӎ��_�J����
			@author �t���`
			@param vPosition	[in] �J�����̈ʒu
			@param vTarget		[in] �J�����̒����ʒu
			@param vUp			[in] �J�����̏����
			@note
			�w�肵���ʒu����w�肵���ꏊ������J�������쐬���܂��B
		*/
		void LookAt( const VectorS& vPosition, const VectorS& vTarget, const VectorS& vUp );
		/**
			@brief �r���[�s���ݒ�
			@author �t���`
			@param mView	[in] �r���[�s��
			@note
			�J�����̃r���[�s���ݒ肵�܂��B
		*/
		void SetViewMatrix( const Matrix& mView );
		/**
			@brief ���[���h�s���ݒ�
			@author �t���`
			@param mWorld	[in] ���[���h�s��
			@note
			�J�����̃��[���h�s���ݒ肵�܂��B
		*/
		void SetWorldMatrix( const Matrix& mWorld );
		/**
			@brief �v���W�F�N�V�����s���ݒ�
			@author �t���`
			@param mProjection	[in] �v���W�F�N�V�����s��
			@note
			�J�����̃v���W�F�N�V�����s���ݒ肵�܂��B
		*/
		void SetProjectionMatrix( const Matrix& mProjection );
		/**
			@brief �߃N���b�v�����擾
			@author �t���`
			@return �߃N���b�v����
			@note
			�J�����̋߃N���b�v�������擾���܂��B
		*/
		float GetNearClip() const;
		/**
			@brief ���N���b�v�����擾
			@author �t���`
			@return ���N���b�v����
			@note
			�J�����̉��N���b�v�������擾���܂��B
		*/
		float GetFarClip() const;
		/**
			@brief �ʒu�擾
			@author �t���`
			@return �ʒu
			@note
			�J�����̈ʒu���擾���܂��B
		*/
		VectorS GetPosition() const;
		/**
			@brief �r���[�s����擾
			@author �t���`
			@return �r���[�s��
			@note
			�J�����̃r���[�s����擾���܂��B
		*/
		Matrix GetViewMatrix() const;
		/**
			@brief �r���[�̋t�s����擾
			@author �t���`
			@return �r���[�̋t�s��
			@note
			�J�����̃r���[�s��̋t�s����擾���܂��B
		*/
		Matrix GetViewMatrixInverse() const;
		/**
			@brief �r���[�̋t�s����擾
			@author �t���`
			@return �r���[�̋t�s��
			@note
			�J�����̃r���[�s��̋t�s����擾���܂��B
		*/
		Matrix GetViewMatrixInverseDisableBank() const;
		/**
			@brief ���[���h�s����擾
			@author �t���`
			@return ���[���h�s��
			@note
			�J�����̃��[���h�s����擾���܂��B
		*/
		Matrix GetWorldMatrix() const;
		/**
			@brief �v���W�F�N�V�����s����擾
			@author �t���`
			@return �v���W�F�N�V�����s��
			@note
			�J�����̃v���W�F�N�V�����s����擾���܂��B
		*/
		const Matrix& GetProjectionMatrix() const;
		/**
			@brief �v���W�F�N�V�����s����擾
			@author �t���`
			@return �v���W�F�N�V�����s��
			@note
			�J�����̃v���W�F�N�V�����s����擾���܂��B
		*/
		Matrix& GetProjectionMatrix();
		/**
			@brief �v���W�F�N�V�����s���FOV���擾
			@author �t���`
			@return �v���W�F�N�V�����s���FOV
			@note
			�J�����̃v���W�F�N�V�����s���FOV���擾���܂��B
		*/
		float GetFov() const;
		/**
			@brief �v���W�F�N�V�����s��̃A�X�y�N�g���擾
			@author �t���`
			@return �v���W�F�N�V�����s��̃A�X�y�N�g
			@note
			�J�����̃v���W�F�N�V�����s��̃A�X�y�N�g���擾���܂��B
		*/
		float GetAspect() const;
		/**
			@brief �v���W�F�N�V�������Ɏ����s���������Ă��邩�`�F�b�N
			@author �t���`
			@param Aabb	[in] �`�F�b�N���鎲���s��
			@return �����Ă����true
			@note
			�J�����̃v���W�F�N�V�������Ɏ����s���������Ă��邩�`�F�b�N���܂��B
		*/
		bool FrustumCulling( const Kernel::Collision::AABB& Aabb ) const;
		/**
			@brief �v���W�F�N�V�������Ɏ����s���������Ă��邩�`�F�b�N
			@author �t���`
			@param Sphere [in] �`�F�b�N���鋅
			@return �����Ă����true
			@note
			�J�����̃v���W�F�N�V�������Ɏ����s���������Ă��邩�`�F�b�N���܂��B
		*/
		bool FrustumCulling( const Kernel::Collision::Sphere& Sphere ) const;

		/**
			@brief �X�N���[�����W���烏�[���h���W���擾
			@author ����
			@param vScreenPosition	[in] �X�N���[�����W
			@param ScreenSize		[in] ��ʃT�C�Y
			@return ���[���h���W
			@note
			�X�N���[�����W���烏�[���h���W���擾���擾���܂��B
		*/
		VectorS GetWorldPosition( const VectorS& vScreenPosition, const Vector2& ScreenSize ) const;

		/**
			@brief ���[���h���W����X�N���[�����W���擾
			@author ����
			@param vWorldPosition	[in] ���[���h���W
			@param ScreenSize		[in] ��ʃT�C�Y
			@param IsInScreen		[out] ��ʓ����ǂ���
			@return ���[���h���W
			@note
			���[���h���W����X�N���[�����W���擾���܂��B
		*/
		VectorS GetScreenPosition( const VectorS& vWorldPosition, const Vector2& ScreenSize, bool& IsInScreen ) const;

		/**
			@brief �r���[�t���X�^���擾
			@author �t���`
			@return �r���[�t���X�^��
			@note
			�J�����̃r���[�Ӄ��X�^�����擾���܂��B
		*/
		const Kernel::Collision::OBB& GetFrustum() const;
	};
}
}
}


/**
	@file
	@brief �f���Q�[�g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
	class Delegate00
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call() const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)();

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call() const
			{
				m_Function();
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)();

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call() const
			{
				(m_pClass->*m_Method)();
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate00()
			: m_pDelegate	( NULL )
		{
		}

		Delegate00( const Delegate00& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate00( T* pClass, void (T::*Method)() )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate00( void (SLN_STDCALL *Function)() )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate00()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call() const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call();
			}
		}

		void operator ()() const
		{
			Call();
		}

		Delegate00& operator = ( const Delegate00& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1 >
	class Delegate01
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1 ) const
			{
				m_Function( a1 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1 ) const
			{
				(m_pClass->*m_Method)( a1 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate01()
			: m_pDelegate	( NULL )
		{
		}

		Delegate01( const Delegate01& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate01( T* pClass, void (T::*Method)(A1) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate01( void (SLN_STDCALL *Function)(A1) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate01()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1 );
			}
		}

		void operator ()( A1 a1 ) const
		{
			Call( a1 );
		}

		Delegate01& operator = ( const Delegate01& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2 >
	class Delegate02
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2 ) const
			{
				m_Function( a1, a2 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2 ) const
			{
				(m_pClass->*m_Method)( a1, a2 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate02()
			: m_pDelegate	( NULL )
		{
		}

		Delegate02( const Delegate02& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate02( T* pClass, void (T::*Method)(A1,A2) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate02( void (SLN_STDCALL *Function)(A1,A2) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate02()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2 );
			}
		}

		void operator ()( A1 a1, A2 a2 ) const
		{
			Call( a1, a2 );
		}

		Delegate02& operator = ( const Delegate02& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3 >
	class Delegate03
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3 ) const
			{
				m_Function( a1, a2, a3 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate03()
			: m_pDelegate	( NULL )
		{
		}

		Delegate03( const Delegate03& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate03( T* pClass, void (T::*Method)(A1,A2,A3) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate03( void (SLN_STDCALL *Function)(A1,A2,A3) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate03()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3 ) const
		{
			Call( a1, a2, a3 );
		}

		Delegate03& operator = ( const Delegate03& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4 >
	class Delegate04
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4 ) const
			{
				m_Function( a1, a2, a3, a4 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate04()
			: m_pDelegate	( NULL )
		{
		}

		Delegate04( const Delegate04& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate04( T* pClass, void (T::*Method)(A1,A2,A3,A4) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate04( void (SLN_STDCALL *Function)(A1,A2,A3,A4) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate04()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4 ) const
		{
			Call( a1, a2, a3, a4 );
		}

		Delegate04& operator = ( const Delegate04& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5 >
	class Delegate05
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
			{
				m_Function( a1, a2, a3, a4, a5 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate05()
			: m_pDelegate	( NULL )
		{
		}

		Delegate05( const Delegate05& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate05( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate05( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate05()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5 ) const
		{
			Call( a1, a2, a3, a4, a5 );
		}

		Delegate05& operator = ( const Delegate05& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
	class Delegate06
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5, A6 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5, A6 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
			{
				m_Function( a1, a2, a3, a4, a5, a6 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5, A6 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5, a6 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate06()
			: m_pDelegate	( NULL )
		{
		}

		Delegate06( const Delegate06& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate06( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5,A6) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate06( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5,A6) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate06()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5, a6 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6 ) const
		{
			Call( a1, a2, a3, a4, a5, a6 );
		}

		Delegate06& operator = ( const Delegate06& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
	class Delegate07
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5, A6, A7 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5, A6, A7 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
			{
				m_Function( a1, a2, a3, a4, a5, a6, a7 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5, A6, A7 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5, a6, a7 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate07()
			: m_pDelegate	( NULL )
		{
		}

		Delegate07( const Delegate07& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate07( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5,A6,A7) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate07( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5,A6,A7) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate07()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5, a6, a7 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7 ) const
		{
			Call( a1, a2, a3, a4, a5, a6, a7 );
		}

		Delegate07& operator = ( const Delegate07& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	template < typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
	class Delegate08
	{
	private:
		class DelegateHolderBase
			: public Object::ReferenceObject
		{
		public:
			virtual void Call( A1, A2, A3, A4, A5, A6, A7, A8 ) const = 0;
		};

		class DelegateHolderStatic
			: public DelegateHolderBase
		{
		private:
			typedef void (SLN_STDCALL *StaticFunction)( A1, A2, A3, A4, A5, A6, A7, A8 );

		private:
			StaticFunction	m_Function;

		public:
			DelegateHolderStatic( StaticFunction Function )
				: m_Function	( Function )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
			{
				m_Function( a1, a2, a3, a4, a5, a6, a7, a8 );
			}
		};

		template < typename T >
		class DelegateHolderDynamics
			: public DelegateHolderBase
		{
		private:
			typedef void (T::*ClassMethod)( A1, A2, A3, A4, A5, A6, A7, A8 );

		private:
			T*			m_pClass;
			ClassMethod	m_Method;

		public:
			DelegateHolderDynamics( T* pClass, ClassMethod Method )
				: m_pClass		( pClass )
				, m_Method		( Method )
			{
			}

			virtual void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
			{
				(m_pClass->*m_Method)( a1, a2, a3, a4, a5, a6, a7, a8 );
			}
		};

	private:
		DelegateHolderBase*		m_pDelegate;

	public:
		Delegate08()
			: m_pDelegate	( NULL )
		{
		}

		Delegate08( const Delegate08& value )
			: m_pDelegate	( NULL )
		{
			*this = value;
		}

		template < typename T >
		Delegate08( T* pClass, void (T::*Method)(A1,A2,A3,A4,A5,A6,A7,A8) )
			: m_pDelegate	( new DelegateHolderDynamics<T>( pClass, Method ) )
		{
		}

		Delegate08( void (SLN_STDCALL *Function)(A1,A2,A3,A4,A5,A6,A7,A8) )
			: m_pDelegate	( new DelegateHolderStatic( Function ) )
		{
		}

		~Delegate08()
		{
			Reset();
		}

	public:
		void Reset()
		{
			SAFE_RELEASE( m_pDelegate );
		}

		bool IsEmpty() const
		{
			return m_pDelegate == NULL;
		}

		void Call( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
		{
			if ( m_pDelegate != NULL )
			{
				m_pDelegate->Call( a1, a2, a3, a4, a5, a6, a7, a8 );
			}
		}

		void operator ()( A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8 ) const
		{
			Call( a1, a2, a3, a4, a5, a6, a7, a8 );
		}

		Delegate08& operator = ( const Delegate08& value )
		{
			Reset();
			m_pDelegate = value.m_pDelegate;
			SAFE_ADDREF( m_pDelegate );

			return *this;
		}
	};

	//--------------------------------------------------------------------------------------------------------------------------//

	template < typename T >
	Delegate00 CreateDelegate( T* pClass, void (T::*pFunction)() )
	{
		return Delegate00( pClass, pFunction );
	}
	template < typename T, typename A1 >
	Delegate01< A1 > CreateDelegate( T* pClass, void (T::*pFunction)( A1 ) )
	{
		return Delegate01< A1 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2 >
	Delegate02< A1, A2 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2 ) )
	{
		return Delegate02< A1, A2 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3 >
	Delegate03< A1, A2, A3 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3 ) )
	{
		return Delegate03< A1, A2, A3 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4 >
	Delegate04< A1, A2, A3, A4 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4 ) )
	{
		return Delegate04< A1, A2, A3, A4 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5 >
	Delegate05< A1, A2, A3, A4, A5 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5 ) )
	{
		return Delegate05< A1, A2, A3, A4, A5 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6 >
	Delegate06< A1, A2, A3, A4, A5, A6 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5, A6 ) )
	{
		return Delegate06< A1, A2, A3, A4, A5, A6 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7 >
	Delegate07< A1, A2, A3, A4, A5, A6, A7 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5, A6, A7 ) )
	{
		return Delegate07< A1, A2, A3, A4, A5, A6, A7 >( pClass, pFunction );
	}
	template < typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8 >
	Delegate08< A1, A2, A3, A4, A5, A6, A7, A8 > CreateDelegate( T* pClass, void (T::*pFunction)( A1, A2, A3, A4, A5, A6, A7, A8 ) )
	{
		return Delegate08< A1, A2, A3, A4, A5, A6, A7, A8 >( pClass, pFunction );
	}

	//--------------------------------------------------------------------------------------------------------------------------//

	#define SLN_EVENT(...)		Kernel::CreateDelegate( this, __VA_ARGS__ )

}	// namespace Kernel
}	// namespace Selene


/**
	@file
	@brief		�����񃆁[�e�B���e�B�@��`
	@author		��
*/


namespace Selene
{
namespace Kernel
{
namespace String
{
	//---------------------------------------------------------------------------//
	/**
		@brief		�����񃆁[�e�B���e�B
		@author		��
		@note		�F��Ȃ��Ƃ����܂��B���x�͖������܂�
	*/
	class Utility
	{
		///< ���������Ⴞ�߁I
		Utility();

	public:
		static std::string ToMultiByte( const wchar_t* pText )
		{
			Sint32 Len = ::WideCharToMultiByte( CP_ACP, 0, pText, -1, NULL, 0, NULL, NULL );

			char* pOut = new char [ Len + 1 ];
			::WideCharToMultiByte( CP_ACP, 0, pText, -1, pOut, Len, NULL, NULL );
			std::string Out( pOut );
			delete [] pOut;

			return Out;
		}

		static std::wstring ToWide( const char* pText )
		{
			Sint32 Len = ::MultiByteToWideChar( CP_ACP, 0, pText, -1, NULL, 0 );

			wchar_t* pOut = new wchar_t [ Len + 1 ];
			::MultiByteToWideChar( CP_ACP, 0, pText, -1, pOut, Len );
			std::wstring Out( pOut );
			delete [] pOut;

			return Out;
		}

		static std::wstring Format( const wchar_t* pString, ... )
		{
			wchar_t Text[1024];
			vswprintf_s( Text, 1024, pString, reinterpret_cast<va_list>(&pString + 1) );
			return std::wstring( Text );
		}

		template<typename T>
		static std::basic_string<T>	Trim( const std::basic_string<T>& str, const T* aChar )
		{
			std::basic_string<T>::size_type begin_pos = str.find_first_not_of( aChar );
			std::basic_string<T>::size_type end_pos = str.find_last_not_of( aChar );
			return str.substr( begin_pos, end_pos - begin_pos + 1 );
		}

		///< ���������Ⴞ�߁I
		template<typename T>
		static std::basic_string<T> TrimSpace( const std::basic_string<T>& str );

		template<>
		static std::basic_string<char> TrimSpace( const std::basic_string<char>& str )
		{
			return Trim( str, "\r\n\t " );
		}

		template<>
		static std::basic_string<wchar_t> TrimSpace( const std::basic_string<wchar_t>& str )
		{
			return Trim( str, L"\r\n\t " );
		}
	};

}	// namespace String
}	// namespace Kernel
}	// namespace Selene


/**
	@file
	@brief CPU�^�C�}�[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Timer
{
	static Uint64 CPUTIMER_COUNT = 1000000;		///< �P�b�̃J�E���g��

	/**
		@brief CPU�^�C�}�[
		@author �t���`
	*/
	class SystemTimer
	{
	private:
		static Uint64 m_OneSecCount;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		SystemTimer();
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~SystemTimer();
		/**
			@brief �J�E���g�擾
			@author �t���`
			@return CPU�J�E���g
		*/
		Uint64 Get() const;
	};
}
}
}


/**
	@file
	@brief �v���t�@�C���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Kernel
{
namespace Timer
{
	/**
		@brief �v���t�@�C���[
		@author �t���`
	*/
	class Profiler
	{
	private:
		SystemTimer	m_Timer;
		wchar_t		m_Name[64];
		Uint64		m_Start;
		Uint64		m_Count;

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		Profiler();
		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param pName	[in] �v���t�@�C����
		*/
		Profiler( const wchar_t* pName );
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~Profiler();
		/**
			@brief ���O�ݒ�
			@author �t���`
			@param pName	[in] �v���t�@�C����
			@note
			�v���t�@�C���̖��O��ݒ肵�܂�
		*/
		void SetName( const wchar_t* pName );
		/**
			@brief �v���t�@�C���J�n
			@author �t���`
			@return �v���t�@�C����
			@note
			�v���t�@�C���̖��O���擾���܂�
		*/
		const wchar_t* GetName() const;
		/**
			@brief �v���t�@�C���J�n
			@author �t���`
			@note
			�v���t�@�C���̏������J�n���܂�
		*/
		void Begin();
		/**
			@brief �v���t�@�C���I��
			@author �t���`
			@note
			�v���t�@�C���̏������I�����܂�
		*/
		void End();
		/**
			@brief �v���t�@�C�����ԃ��Z�b�g
			@author �t���`
			@note
			�v���t�@�C���̏������Ԃ����������܂�
		*/
		void Reset();
		/**
			@brief �v���t�@�C�����Ԏ擾
			@author �t���`
			@return �v���t�@�C������
			@note
			�v���t�@�C����Begin()����End()�܂ł̏��v���Ԃ��擾���܂�
		*/
		float Get() const;
	};
}
}
}



#ifdef __cplusplus_cli
#pragma managed(pop)
#endif
#ifdef __cplusplus_cli
#pragma managed( push, off )
#endif
/**
	@file
	@brief Engine��{��`
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief ���C�u�������O���
*/
namespace Selene
{
	/**
		@brief �G���W��
	*/
	namespace Engine
	{
		class ICore;

		/**
			@brief �E�B���h�E
		*/
		namespace Window
		{
			class IWindow;
		}

		/**
			@brief �^�X�N
		*/
		namespace Task
		{
			class ITaskManager;
		}

		/**
			@brief �t�@�C��
		*/
		namespace File
		{
			class IManager;
			class IPackFile;
			class IStreamFile;
			class IFile;
		}

		/**
			@brief �O���t�B�b�N
		*/
		namespace Graphics
		{
			/**
				@brief �o�b�t�@���b�N�t���O
			*/
			enum eLock
			{
				LOCK_STATIC,		///< �ʏ탍�b�N
				LOCK_DISCARD,		///< �S�X�V���b�N�iIsDyanmic=true������j
				LOCK_NOOVERWRITE,	///< �����X�V���b�N�iIsDyanmic=true������j
			};

			class IManager;

			/**
				@brief �X�e�[�g
			*/
			namespace State
			{
				class IRenderState;
			}

			/**
				@brief �V���v��
			*/
			namespace Simple
			{
				class ILineRenderer;
				class ISpriteRenderer;
				class ISpriteRenderer3D;
				class ITriangleRenderer;
				class ITextRenderer;
			}

			/**
				@brief ���\�[�X
			*/
			namespace Resource
			{
				class ITexture;
				class IShaderConstantBuffer;
				class IGeometryShader;
				class IVertexShader;
				class IVertexLayout;
				class IVertexBuffer;
				class IIndexBuffer;
				class IPixelShader;
				class IMaterialPlugin;
				class IMaterialListener;
				class IFileLoadListener;
				class IDrawObject;
				class IMaterial;
				class IRenderTable;
				class ILocalResource;
				class IRootMotion;

				/**
					@brief SMF���f��
				*/
				namespace SMF
				{
					class IConstraint;
					class INode;
					class IModel;
					class IModelController;
					class IMotion;
					class IMotionController;
					class IMotionScheduler;
				}

				/**
					@brief STM���f��
				*/
				namespace STM
				{
					class IModelController;
				}

				/**
					@brief �e�L�X�g
				*/
				namespace Text
				{
					class ITextData;
				}

				/**
					@brief �|���S�����C��
				*/
				namespace PolyLine
				{
					class IPolyLineController;
				}

				/**
					@brief �X�v���C�g
				*/
				namespace Sprite
				{
					class ISpriteController;
				}

				/**
					@brief �v���~�e�B�u
				*/
				namespace Primitive
				{
					class IPrimitiveController;
				}

				/**
					@brief �p�[�e�B�N��
				*/
				namespace Particle
				{
					struct SParameter;
					class IParticleController;
					class IVolumeParticleController;
					class IEnhancedParticleController;
				}
			}
		}

		/**
			@brief �����_���[
		*/
		namespace Renderer
		{
			class IManager;

			/**
				@brief �W������
			*/
			namespace Standard
			{
				struct SMaterialOption;
				class IRenderer;

				namespace Material
				{
					namespace Standard
					{
						class IMaterial;
					}

					namespace Water
					{
						class IMaterial;
					}
				}
			}
		}

		/**
			@brief �T�E���h
		*/
		namespace Sound
		{
			class IManager;

			namespace Resource
			{
				class IStaticSound;
				class IStreamSound;
			}
		}

		/**
			@brief ���̓f�o�C�X
		*/
		namespace Input
		{
			/**
				@brief �{�^���̏��
				@author �t���`
			*/
			enum eButtonState
			{
				BUTTON_STATE_FREE,	///< �����Ă���
				BUTTON_STATE_PULL,	///< �����ꂽ
				BUTTON_STATE_PUSH,	///< �����ꂽ
				BUTTON_STATE_HOLD,	///< �����Ă���
			};

			/**
				@brief ���z�L�[�R�[�h
				@author �t���`
			*/
			enum eKeyCode
			{
				KEY_ESCAPE          = 0x01,
				KEY_1               = 0x02,
				KEY_2               = 0x03,
				KEY_3               = 0x04,
				KEY_4               = 0x05,
				KEY_5               = 0x06,
				KEY_6               = 0x07,
				KEY_7               = 0x08,
				KEY_8               = 0x09,
				KEY_9               = 0x0A,
				KEY_0               = 0x0B,
				KEY_MINUS           = 0x0C,
				KEY_EQUALS          = 0x0D,
				KEY_BACK            = 0x0E,
				KEY_TAB             = 0x0F,
				KEY_Q               = 0x10,
				KEY_W               = 0x11,
				KEY_E               = 0x12,
				KEY_R               = 0x13,
				KEY_T               = 0x14,
				KEY_Y               = 0x15,
				KEY_U               = 0x16,
				KEY_I               = 0x17,
				KEY_O               = 0x18,
				KEY_P               = 0x19,
				KEY_LBRACKET        = 0x1A,
				KEY_RBRACKET        = 0x1B,
				KEY_RETURN          = 0x1C,
				KEY_LCONTROL        = 0x1D,
				KEY_A               = 0x1E,
				KEY_S               = 0x1F,
				KEY_D               = 0x20,
				KEY_F               = 0x21,
				KEY_G               = 0x22,
				KEY_H               = 0x23,
				KEY_J               = 0x24,
				KEY_K               = 0x25,
				KEY_L               = 0x26,
				KEY_SEMICOLON       = 0x27,
				KEY_APOSTROPHE      = 0x28,
				KEY_GRAVE           = 0x29,
				KEY_LSHIFT          = 0x2A,
				KEY_BACKSLASH       = 0x2B,
				KEY_Z               = 0x2C,
				KEY_X               = 0x2D,
				KEY_C               = 0x2E,
				KEY_V               = 0x2F,
				KEY_B               = 0x30,
				KEY_N               = 0x31,
				KEY_M               = 0x32,
				KEY_COMMA           = 0x33,
				KEY_PERIOD          = 0x34,
				KEY_SLASH           = 0x35,
				KEY_RSHIFT          = 0x36,
				KEY_MULTIPLY        = 0x37,
				KEY_LMENU           = 0x38,
				KEY_SPACE           = 0x39,
				KEY_CAPITAL         = 0x3A,
				KEY_F1              = 0x3B,
				KEY_F2              = 0x3C,
				KEY_F3              = 0x3D,
				KEY_F4              = 0x3E,
				KEY_F5              = 0x3F,
				KEY_F6              = 0x40,
				KEY_F7              = 0x41,
				KEY_F8              = 0x42,
				KEY_F9              = 0x43,
				KEY_F10             = 0x44,
				KEY_NUMLOCK         = 0x45,
				KEY_SCROLL          = 0x46,
				KEY_NUMPAD7         = 0x47,
				KEY_NUMPAD8         = 0x48,
				KEY_NUMPAD9         = 0x49,
				KEY_SUBTRACT        = 0x4A,
				KEY_NUMPAD4         = 0x4B,
				KEY_NUMPAD5         = 0x4C,
				KEY_NUMPAD6         = 0x4D,
				KEY_ADD             = 0x4E,
				KEY_NUMPAD1         = 0x4F,
				KEY_NUMPAD2         = 0x50,
				KEY_NUMPAD3         = 0x51,
				KEY_NUMPAD0         = 0x52,
				KEY_DECIMAL         = 0x53,
				KEY_OEM_102         = 0x56,
				KEY_F11             = 0x57,
				KEY_F12             = 0x58,
				KEY_KANA            = 0x70,
				KEY_ABNT_C1         = 0x73,
				KEY_CONVERT         = 0x79,
				KEY_NOCONVERT       = 0x7B,
				KEY_YEN             = 0x7D,
				KEY_ABNT_C2         = 0x7E,
				KEY_NUMPADEQUALS    = 0x8D,
				KEY_PREVTRACK       = 0x90,
				KEY_NUMPADENTER     = 0x9C,
				KEY_RCONTROL        = 0x9D,
				KEY_NUMPADCOMMA     = 0xB3,
				KEY_DIVIDE          = 0xB5,
				KEY_SYSRQ           = 0xB7,
				KEY_RMENU           = 0xB8,
				KEY_PAUSE           = 0xC5,
				KEY_HOME            = 0xC7,
				KEY_UP              = 0xC8,
				KEY_PRIOR           = 0xC9,
				KEY_LEFT            = 0xCB,
				KEY_RIGHT           = 0xCD,
				KEY_END             = 0xCF,
				KEY_DOWN            = 0xD0,
				KEY_NEXT            = 0xD1,
				KEY_INSERT          = 0xD2,
				KEY_DELETE          = 0xD3,
				KEY_LWIN            = 0xDB,
				KEY_RWIN            = 0xDC,

				KEY_DISABLE         = 0x00
			};

			class IManager;
			class IInputController;
			class IJoystick;
			class IKeyboard;
			class IMouse;
		}

		/**
			@brief �l�b�g���[�N
		*/
		namespace Network
		{
			/**
				@brief	�z�X�g���
				@author �t���`
			*/
			struct SHostInfo
			{
				char Name[64];						///< �z�X�g��
				char Alias[16][64];					///< �z�X�g�ʖ��e�[�u��
				char Address[16][64];				///< IP�A�h���X�e�[�u��
				Sint32 Type;						///< �f�[�^�^�C�v
				Sint32 Length;						///< �f�[�^�T�C�Y
				Sint32 AliasCount;					///< �G�C���A�X��
				Sint32 AddressCount;				///< IP�A�h���X��
			};

			class IManager;

			/**
				@brief TCP�ʐM
			*/
			namespace TCP
			{
				class IClient;
				class IServer;
				class IClientOfServer;
				class IServerReciver;
				class IServerSender;
			}

			/**
				@brief UDP�ʐM
			*/
			namespace UDP
			{
				class IConnect;
			}
		}

		/**
			@brief ����
		*/
		namespace Dynamics
		{
			class IManager;

			namespace Body
			{
				class IBody;
				class IDynamicsBody;
				class IBox;
				class ICapsule;
				class ICharaProxy;
				class ICharaProxySimple;
				class IPlane;
				class ISphere;
				class ITriMesh;
				class ITriggerBox;
				class ICompound;
				class ICollisionBody;
				class ICollisionSphere;
				class ICollisionCapsule;
				class ICollisionBox;
				class ICollisionTriMesh;
				class ISoftBody;
				class IRope;

				/**
					@brief �L�����N�^�̃{�f�B�̎��
					@author ����
				*/
				enum eProxyType
				{
					PROXY_TYPE_SPHERE,					///< ��
					PROXY_TYPE_CAPSULE,					///< �J�v�Z��
				};

				/**
					@brief �{�f�B�̎��
					@author �t���`
				*/
				enum eBodyType
				{
					BODY_TYPE_BOX,						///< ��
					BODY_TYPE_CAPSULE,					///< �J�v�Z��
					BODY_TYPE_CHARA,					///< �L�����N�^�[
					BODY_TYPE_PLANE,					///< ����
					BODY_TYPE_SPHERE,					///< ��
					BODY_TYPE_TRIMESH,					///< �|���S�����b�V��
					BODY_TYPE_COMPOUND,					///< ����
					BODY_TYPE_TRIGGER_BOX,				///< �g���K�[��
					BODY_TYPE_ROPE,						///< ���[�v
					BODY_TYPE_COLLISION_CAPSULE,		///< �Փ˔���p�J�v�Z��
					BODY_TYPE_COLLISION_SPHERE,			///< �Փ˔���p��
					BODY_TYPE_COLLISION_BOX,			///< �Փ˔���p��
					BODY_TYPE_COLLISION_TRIMESH,		///< �Փ˔���p�|���S�����b�V��
				};

				/**
					@brief �ڐG�_���
					@author �t���`
				*/
				struct SContactInfo
				{
					Kernel::Math::Vector3	Normal;		///< �ڐG�_�@��
					Kernel::Math::Vector3	Position;	///< �ڐG�_�ʒu
					IBody*					pTarget;	///< �ڐG�{�f�B
				};

				/**
					@brief �����I�u�W�F�N�g
					@author �t���`
				*/
				struct CompoundShape
					: public Kernel::Object::MemoryObject
				{
					/**
						@brief �����I�u�W�F�N�g�̎��
						@author �t���`
					*/
					enum Type
					{
						SPHERE,		///< ��
						CAPSULE,	///< �J�v�Z��
						BOX,		///< ��
					};

					Kernel::Math::VectorS Position;		///< �ʒu
					Kernel::Math::VectorS Rotation;		///< ��]�p�x

					virtual ~CompoundShape(){}
					virtual Type GetType() const = 0;
				};

				/**
					@brief �����I�u�W�F�N�g��
					@author �t���`
				*/
				struct CompoundShapeSphere
					: public CompoundShape
				{
					float Radius;		///< ���a

					virtual ~CompoundShapeSphere(){}
					virtual Type GetType() const { return SPHERE; }
				};

				/**
					@brief �����I�u�W�F�N�g�J�v�Z��
					@author �t���`
				*/
				struct CompoundShapeCapsule
					: public CompoundShape
				{
					float Radius;		///< ���a
					float Length;		///< ����

					virtual ~CompoundShapeCapsule(){}
					virtual Type GetType() const { return CAPSULE; }
				};

				/**
					@brief �����I�u�W�F�N�g��
					@author �t���`
				*/
				struct CompoundShapeBox
					: public CompoundShape
				{
					Kernel::Math::VectorS Size;	//< �T�C�Y

					virtual ~CompoundShapeBox(){}
					virtual Type GetType() const { return BOX; }
				};
			}

			/**
				@brief �W���C���g
			*/
			namespace Joint
			{
				class IJoint;
				class ISliderJoint;
				class IHingeJoint;
				class IPointJoint;
				class IDofSpringJoint;
			}
		}

		/**
			@brief �O���t�B�J�����[�U�[�C���^�[�t�F�C�X
		*/
		namespace GUI
		{
			class IManager;
			class IHelper;

			/**
				@brief GUI�R���g���[��
			*/
			namespace Control
			{
				class IControl;
				class IIme;
				class IWindow;
				class IButton;
				class IProgressBar;
				class ISliderBar;
				class IScrollBar;
				class ILabel;
				class IGroupBox;
				class ICheckBox;
				class IListBox;
				class IComboBox;
				class IEditBox;
				class ITextBox;
				class IDialog;
				class IMenuBar;
				class IMenuButton;
				class IMenuList;
			}
		}
	}
}

/**
	@file
	@brief �Q�[���p�E�B���h�E
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Window
{
	/**
		@brief �Q�[���p�E�B���h�E�Ǘ��N���X
		@author �t���`
		@note
		�Q�[���p�E�B���h�E�����𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IWindow
		: public Interface
	{
	protected:
		virtual ~IWindow(){}

	public:
		/**
			@brief �E�B���h�E�̃n���h�����擾
			@author �t���`
			@note
			�E�B���h�E�̃n���h�����擾���܂��B
		*/
		virtual HWND GetHandle() = 0;

		/**
			@brief ���Ă��邩�`�F�b�N
			@author �t���`
			@retval true	���Ă���
			@retval false	���Ă��Ȃ�
			@note
			�E�B���h�E�������Ă��邩�擾���܂��B
		*/
		virtual bool IsClosed() = 0;

		/**
			@brief �^�C�g���o�[�̃e�L�X�g�ݒ�
			@author �t���`
			@param pText
			@note
			�^�C�g���o�[�ɕ\������e�L�X�g��ݒ肵�܂��B
		*/
		virtual void SetTitleText( const wchar_t* pText ) = 0;

		/**
			@brief �E�B���h�E�T�C�Y�擾
			@author �t���`
			@return �E�B���h�E�̃T�C�Y
			@note
			�E�B���h�E�̃T�C�Y���擾���܂��B
		*/
		virtual Point2DI GetSize() = 0;

		/**
			@brief �A�N�e�B�u�`�F�b�N
			@author �t���`
			@retval true	�E�B���h�E�̓A�N�e�B�u
			@retval false	�E�B���h�E�͔�A�N�e�B�u
			@note
			�E�B���h�E���A�N�e�B�u���ǂ������擾���܂��B
		*/
		virtual bool IsActive() = 0;

		/**
			@brief �J�[�\���\��ON/OFF
			@author �t���`
			@param IsShow	[in] �\��������ꍇ��true/�\���������ꍇ��false
			@note
			�}�E�X�J�[�\���̕\����ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetShowCursor( bool IsShow ) = 0;

		/**
			@brief �E�B���h�E�I���������̃R�[���o�b�N�C�x���g�ݒ�
			@author �t���`
			@param Event	[in] �R�[���o�b�N�C�x���g
			@note
			�E�B���h�E�I���̎��̃R�[���o�b�N�C�x���g��ݒ肵�܂��B<BR>
			������bool�l��false��ݒ肷��ƃE�B���h�E�̏I�����L�����Z���o���܂��B
		*/
		virtual void SetWindowCloseEvent( const Kernel::Delegate01<bool&>& Event ) = 0;

		/**
			@brief �t�@�C���h���b�O�A���h�h���b�v�������̃R�[���o�b�N�C�x���g�ݒ�
			@author �t���`
			@param Event	[in] �R�[���o�b�N�C�x���g
			@note
			�t�@�C���h���b�O�A���h�h���b�v�̎��̃R�[���o�b�N�C�x���g��ݒ肵�܂��B
		*/
		virtual void SetFileDropEvent( const Kernel::Delegate02<Uint32,const wchar_t**>& Event ) = 0;

		/**
			@brief �E�B���h�E���b�Z�[�W�������̃R�[���o�b�N�C�x���g�ݒ�
			@author �t���`
			@param Event	[in] �R�[���o�b�N�C�x���g
			@note
			�E�B���h�E���b�Z�[�W�̎��̃R�[���o�b�N�C�x���g��ݒ肵�܂��B
		*/
		virtual void SetWindowMessageEvent( const Kernel::Delegate04<Uint32,Sint64,Sint64&,bool&>& Event ) = 0;
	};
}
}
}

/**
	@file
	@brief �t�@�C������p���ʃC���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief �t�@�C������
		@author �t���`
	*/
	class IFile
		: public Interface
	{
	protected:
		virtual ~IFile(){};

	public:
		/**
			@brief �ǂݍ��݃`�F�b�N
			@author �t���`
			@return true�Ȃ琳��ɓǂ܂�Ă���
			@note
			�t�@�C��������ɓǂ܂�Ă��邩�ۂ�
		*/
		virtual bool IsLoaded() const = 0;

		/**
			@brief �t�@�C�����擾
			@author �t���`
			@return �t�@�C�����̐擪�A�h���X
			@note
			�t�@�C�����̐擪�A�h���X���擾���܂��B
		*/
		virtual const wchar_t* GetFileName() const = 0;

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y
			@note
			�t�@�C���̃T�C�Y���擾���܂��B
		*/
		virtual Sint32 GetSize() const = 0;

		/**
			@brief �f�[�^�擾
			@author �t���`
			@return �f�[�^�̐擪�|�C���^�[
			@note
			�t�@�C�����e�̃f�[�^�̃|�C���^�[���擾���܂��B
		*/
		virtual const void* GetData() const = 0;
	};
}
}
}

/**
	@file
	@brief �X�g���[���t�@�C���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief �t�@�C���X�g���[������
		@author �t���`
	*/
	class IStreamFile
		: public Interface
	{
	protected:
		virtual ~IStreamFile(){};

	public:
		/**
			@brief �t�@�C�����擾
			@author �t���`
			@return �t�@�C�����̐擪�A�h���X
			@note
			�t�@�C�����̐擪�A�h���X���擾���܂��B
		*/
		virtual const wchar_t* GetFileName() const = 0;

		/**
			@brief �t�@�C���ւ̓ǂݍ���
			@author �t���`
			@param pData	[in] �ǂݍ��݃f�[�^
			@param Size		[in] �ǂݍ��݃f�[�^�T�C�Y
			@return ���ۂɏ������񂾃o�C�g��
			@note
			�t�@�C���ւ̓ǂݍ��݂��s���܂��B<BR>
			�ǂݍ��݉\�ȃt�@�C���̓C���^�[�t�F�C�X��������<BR>
			FILE_OPEN_TYPE_READ��FILE_OPEN_TYPE_READ_WRITE�t���O��<BR>
			�w�肷��K�v������܂��B
		*/
		virtual Sint32 Read( void* pData, Sint32 Size ) = 0;

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y
			@note
			�t�@�C���̃T�C�Y���擾���܂��B
		*/
		virtual Sint32 GetFileSize() const = 0;

		/**
			@brief �t�@�C���|�C���^�[�ʒu�擾
			@author �t���`
			@return �t�@�C���|�C���^�[�̈ʒu
			@note
			���݂̃t�@�C���|�C���^�̈ʒu���擾���܂��B
		*/
		virtual Sint32 GetFilePosition() const = 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu
			@note
			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̐擪����Offset�o�C�g�ړ����܂��B
		*/
		virtual Sint32 SeekStart( Sint32 Offset ) = 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu
			@note
			�t�@�C���|�C���^�[�̈ʒu���t�@�C���̏I�[����Offset�o�C�g�ړ����܂��B
		*/
		virtual Sint32 SeekEnd( Sint32 Offset ) = 0;

		/**
			@brief �t�@�C���V�[�N
			@author �t���`
			@param Offset	[in] �ړ���
			@return �t�@�C���|�C���^�[�̈ʒu
			@note
			�t�@�C���|�C���^�[�̈ʒu�����݂̈ʒu����Offset�o�C�g�ړ����܂��B
		*/
		virtual Sint32 Seek( Sint32 Offset ) = 0;
	};
}
}
}

/**
	@file
	@brief �p�b�N�t�@�C���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief �p�b�N�t�@�C���N���X
		@author �t���`

		�p�b�N�t�@�C���̓ǂݍ��ݏ������s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IPackFile
		: public Interface
	{
	protected:
		virtual ~IPackFile(){}

	public:
		/**
			@brief �ǂݍ��݃`�F�b�N
			@author �t���`
			@return true�Ȃ琳��ɓǂ܂�Ă���
			@note
			�t�@�C��������ɓǂ܂�Ă��邩�ۂ�
		*/
		virtual bool IsLoaded() const = 0;

		/**
			@brief IFile�C���^�[�t�F�C�X�̎擾
			@author �t���`
			@param pDataName	[in] �擾����f�[�^��
			@return IFile�C���^�[�t�F�C�X
			@note
			�w�肵���f�[�^������IFile�C���^�[�t�F�C�X���擾���܂�
		*/
		virtual Engine::File::IFile* GetFile( const wchar_t* pDataName ) = 0;

		/**
			@brief IPackFile�C���^�[�t�F�C�X�̎擾
			@author �t���`
			@param pDataName	[in] �擾����f�[�^��
			@return IPackFile�C���^�[�t�F�C�X
			@note
			�p�b�N�t�@�C�����̃p�b�N�t�@�C�����擾����ׂ�IPackFile�C���^�[�t�F�C�X���擾���܂�
		*/
		virtual IPackFile* GetPackFile( const wchar_t* pDataName ) = 0;

		/**
			@brief �t�@�C���̃V�[�N
			@author �t���`
			@param pDataName	[in] �V�[�N����f�[�^��
			@return true�Ȃ琳��ɃV�[�N�ł���
			@note
			�w�肵���f�[�^�̐擪�܂Ńt�@�C�����V�[�N���܂��B
		*/
		virtual bool Seek( const wchar_t* pDataName ) = 0;

		/**
			@brief �t�@�C�����擾
			@author �t���`
			@return �t�@�C�����̐擪�A�h���X
			@note
			�t�@�C�����̐擪�A�h���X���擾���܂��B
		*/
		virtual const wchar_t* GetFileName() const = 0;

		/**
			@brief �t�@�C���T�C�Y�擾
			@author �t���`
			@return �t�@�C���T�C�Y
			@note
			�t�@�C���̃T�C�Y���擾���܂��B
		*/
		virtual Sint32 GetSize() const = 0;

		/**
			@brief �f�[�^�擾
			@author �t���`
			@return �f�[�^�̐擪�|�C���^�[
			@note
			�t�@�C�����e�̃f�[�^�̃|�C���^�[���擾���܂��B
		*/
		virtual const void* GetData() const = 0;
	};
}
}
}

/**
	@file
	@brief �t�@�C���}�l�[�W���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace File
{
	/**
		@brief �t�@�C���Ǘ��N���X
		@author �t���`

		�t�@�C���̓ǂݍ��ݏ������s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief �t�@�C���A�N�Z�X�̃��b�N
			@author �t���`
			@note
			�t�@�C���A�N�Z�X�����鎞�̔r���������J�n���܂��B
		*/
		virtual void Lock() = 0;

		/**
			@brief �t�@�C���A�N�Z�X�̃A�����b�N
			@author �t���`
			@note
			�t�@�C���A�N�Z�X�����鎞�̔r���������I�����܂��B
		*/
		virtual void Unlock() = 0;

		/**
			@brief �f�[�^���k
			@author �t���`
			@param pDst		[in/out] ���k��f�[�^�i�[��
			@param DstSize	[out] ���k��f�[�^�T�C�Y
			@param pSrc		[in] ���f�[�^�i�[��
			@param SrcSize	[in] ���f�[�^�T�C�Y
			@note
			�f�[�^�̈��k���s���܂��B
		*/
		virtual bool Compress( void* pDst, Uint32& DstSize, const void* pSrc, Uint32 SrcSize ) = 0;

		/**
			@brief �f�[�^��
			@author �t���`
			@param pDst		[in/out] �𓀌�f�[�^�i�[��
			@param DstSize	[out] �𓀌�f�[�^�T�C�Y
			@param pSrc		[in] ���f�[�^�i�[��
			@param SrcSize	[in] ���f�[�^�T�C�Y
			@note
			�f�[�^�̉𓀂��s���܂��B
		*/
		virtual bool Decompress( void* pDst, Uint32 DstSize, const void* pSrc, Uint32 SrcSize ) = 0;

		/**
			@brief �Í��p�v���O�C�����p�X���[�h�ݒ�
			@author �t���`
			@param pPluginPath	[in] �v���O�C����
			@param pPassword	[in] �p�X���[�h
			@note
			�p�b�N�t�@�C���̓W�J�p�̈Í��v���O�C���ƃp�X���[�h��ݒ肵�܂��B
		*/
		virtual void SetCryptPlugin( const wchar_t* pPluginPath, const char* pPassword ) = 0;

		/**
			@brief �ǂݍ��ݗp���[�g�p�X�X�V
			@author �t���`
			@param pRootPathList	[in] ���[�g�p�X�̃��X�g
			@note
			�ǂݍ��ݗp�̃p�X�̃��[�g�̃��X�g��ݒ肵�܂��B<BR>
			�z��̌��ɋL�q����Ă�����A�����̗D��x�������ł��B
		*/
		virtual void UpdateRootPath( const wchar_t* pRootPathList[] ) = 0;

		/**
			@brief �ǂݍ��ݗp���[�g�p�X�ǉ�
			@author ����
			@param pRootPath		[in] ���[�g�p�X
			@note
			�ǂݍ��ݗp�̃p�X�̃��[�g�̃��X�g��ǉ����܂��B<BR>
			��ɒǉ�����قǁA�����̗D��x�������ł��B
		*/
		virtual void AppendRootPath( const wchar_t* pRootPath ) = 0;

		/**
			@brief �ǂݍ��ݗp���[�g�p�X�����o��
			@author ����
			@param pListFile		[in] �t�@�C�����X�g�ۑ��p�t�@�C����
			@note
			�ǂݍ��ݗp�̃p�X�̃��[�g�̃��X�g���o�͂��܂��B
		*/
		virtual void SaveRootPath( const wchar_t* pListFile ) = 0;

		/**
			@brief �ǂݍ��ݗp���[�g�p�X�ǂݍ���
			@author �t���`
			@param pListFile		[in] ���p����t�@�C�����X�g�̃t�@�C����
			@note
			�ǂݍ��ݗp�̃p�X�̃��[�g�̃��X�g��ݒ肵�܂��B<BR>
			�t�@�C�����X�g�ɏ�����Ă���t�@�C����o�^���܂��B
		*/
		virtual void LoadRootPath( const wchar_t* pListFile ) = 0;

		/**
			@brief �ǂݍ��ݗp�J�����g�p�X�ݒ�
			@author �t���`
			@param pPath	[in] �J�����g�̃p�X�iLoadRootPath�����[�g�Ƃ��Ďw�肷��j
			@note
			�ǂݍ��݂��s���Ƃ��̃J�����g�̃p�X��ݒ肵�܂��B
		*/
		virtual void SetCurrentPath( const wchar_t* pPath ) = 0;

		/**
			@brief �t�@�C���̃t���p�X���擾
			@author �t���`
			@param pOut			[out] �p�X�i�[��
			@param pFileName	[in] �t�@�C����
			@note
			�t�@�C���̓ǂݍ��ݗp�̃p�X���擾���܂��B
		*/
		virtual void GetFileFullPath( wchar_t* pOut, const wchar_t* pFileName ) = 0;

		/**
			@brief �����t�@�C���ǂݍ���
			@author �t���`
			@param pFileName		[in] �t�@�C����
			@param IsLoadAbsPath	[in] �w��p�X�Ńt�@�C���������邩�ǂ���
			@return Engine::File::IFile�C���^�[�t�F�C�X
			@note
			�t�@�C���̃u���b�N�ǂݍ��݂��s���܂��B
		*/
		virtual Engine::File::IFile* OpenSyncFile( const wchar_t* pFileName, bool IsLoadAbsPath = false ) = 0;

		/**
			@brief �񓯊��t�@�C���ǂݍ���
			@author �t���`
			@param pFileName		[in] �t�@�C����
			@param IsLoadAbsPath	[in] �w��p�X�Ńt�@�C���������邩�ǂ���
			@return Engine::File::IFile�C���^�[�t�F�C�X
			@note
			�t�@�C���̔�u���b�N�ǂݍ��݂��s���܂��B
		*/
		virtual Engine::File::IFile* OpenASyncFile( const wchar_t* pFileName, bool IsLoadAbsPath = false ) = 0;

		/**
			@brief �X�g���[���p�t�@�C���ǂݍ���
			@author �t���`
			@param pFileName		[in] �t�@�C����
			@param IsLoadAbsPath	[in] �w��p�X�Ńt�@�C���������邩�ǂ���
			@return Engine::File::IStreamFile�C���^�[�t�F�C�X
			@note
			�t�@�C���̃X�g���[���p�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Engine::File::IStreamFile* OpenStreamFile( const wchar_t* pFileName, bool IsLoadAbsPath = false ) = 0;

		/**
			@brief �X�g���[���p�t�@�C���ǂݍ���
			@author �t���`
			@param pFile		[in] �t�@�C��
			@return Engine::File::IStreamFile�C���^�[�t�F�C�X
			@note
			�t�@�C���̃X�g���[���p�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Engine::File::IStreamFile* OpenStreamFile( Engine::File::IFile* pFile ) = 0;

		/**
			@brief �p�b�N�t�@�C������A�N�Z�X�p�̃C���^�[�t�F�C�X�𐶐�
			@author �t���`
			@param pFile		[in] �t�@�C��
			@return IPackData�C���^�[�t�F�C�X
			@note
			�p�b�N�t�@�C���̃A�N�Z�X�p�̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual IPackFile* CreatePackFile( Engine::File::IFile* pFile ) = 0;
	};
}
}
}

/**
	@file
	@brief �X�e�[�g�Ǘ��p�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace State
{
	/**
		@brief �A���t�@�u�����f�B���O
		@author �t���`
	*/
	enum eAlphaBlend
	{
		AB_OPACITY,				///< �s����
		AB_BLEND,				///< ����
		AB_ADD,					///< ���Z
		AB_ADD_ALPHADISABLE,	///< ���Z�i�A���t�@�`�����l�������j
		AB_SUB,					///< ���Z
		AB_SUB_ALPHADISABLE,	///< ���Z�i�A���t�@�`�����l�������j
		AB_MUL,					///< ��Z
		AB_SCREEN,				///< �X�N���[��

		AB_TYPE_MAX,
	};

	/**
		@brief �J�����O
		@author �t���`
	*/
	enum eCulling
	{
		CULL_FRONT,		///< �S�ʂ�\��
		CULL_BACK,		///< �w�ʂ�\��
		CULL_DOUBLE,	///< ���ʕ\��

		CULL_TYPE_MAX,
	};

	/**
		@brief �V�U�����O
		@author �t���`
	*/
	enum eScissorTest
	{
		ST_DISABLE,		///< �V�U�����O���Ȃ�
		ST_ENABLE,		///< �V�U�����O����

		ST_TYPE_MAX,
	};

	/**
		@brief �A���t�@�e�X�g
		@author �t���`
	*/
	enum eAlphaTest
	{
		AT_DISABLE,		///< �A���t�@�e�X�g���Ȃ�
		AT_ENABLE,		///< �A���t�@�e�X�g����

		AT_TYPE_MAX,
	};

	/**
		@brief �[�x�e�X�g
		@author �t���`
	*/
	enum eDepthTest
	{
		DT_DISABLE,		///< �[�x�e�X�g���Ȃ�
		DT_ENABLE,		///< �[�x�e�X�g����

		DT_TYPE_MAX,
	};

	/**
		@brief �[�x��������
		@author �t���`
	*/
	enum eDepthWrite
	{
		DW_DISABLE,		///< �[�x�������݂��Ȃ�
		DW_ENABLE,		///< �[�x�������݂���

		DW_TYPE_MAX,
	};

	/**
		@brief �|���S���h��Ԃ�
		@author �t���`
	*/
	enum ePolygonFill
	{
		PF_SOLID,		///< �h��Ԃ�
		PF_WIRE,		///< ���C���t���[��

		PF_TYPE_MAX,
	};

	/**
		@brief �X�e�[�g�Ǘ��p�C���^�[�t�F�C�X
		@author �t���`
		@note �X�e�[�g�̊Ǘ������邽�߂̃C���^�[�t�F�C�X
	*/
	class IRenderState
		: public Interface
	{
	protected:
		virtual ~IRenderState(){}

	public:
		/**
			@brief �A���t�@�u�����h�ݒ�
			@author �t���`
			@param Param	[in] �A���t�@�u�����h�^�C�v
			@note
			�A���t�@�u�����h�Ɋւ���ݒ�����܂�
		*/
		virtual void SetAlphaBlend( eAlphaBlend Param ) = 0;
		/**
			@brief �J�����O�ݒ�
			@author �t���`
			@param Param	[in] �J�����O�^�C�v
			@note
			�J�����O�Ɋւ���ݒ�����܂�
		*/
		virtual void SetCulling( eCulling Param ) = 0;
		/**
			@brief �V�U�[�e�X�g�ݒ�
			@author �t���`
			@param Param	[in] �V�U�[�e�X�g�^�C�v
			@note
			�V�U�[�e�X�g�Ɋւ���ݒ�����܂�
		*/
		virtual void SetScissorTest( eScissorTest Param ) = 0;
		/**
			@brief �A���t�@�e�X�g�ݒ�
			@author �t���`
			@param Param	[in] �A���t�@�e�X�g�^�C�v
			@note
			�A���t�@�e�X�g�Ɋւ���ݒ�����܂�
		*/
		virtual void SetAlphaTest( eAlphaTest Param ) = 0;
		/**
			@brief �[�x�e�X�g�ݒ�
			@author �t���`
			@param Param	[in] �[�x�e�X�g�^�C�v
			@note
			�[�x�e�X�g�Ɋւ���ݒ�����܂�
		*/
		virtual void SetDepthTest( eDepthTest Param ) = 0;
		/**
			@brief �[�x�������ݐݒ�
			@author �t���`
			@param Param	[in] �[�x�������݃^�C�v
			@note
			�[�x�������݂Ɋւ���ݒ�����܂�
		*/
		virtual void SetDepthWrite( eDepthWrite Param ) = 0;
		/**
			@brief �|���S���h��Ԃ��ݒ�
			@author �t���`
			@param Param	[in] �|���S���h��Ԃ��^�C�v
			@note
			�|���S���h��Ԃ��Ɋւ���ݒ�����܂�
		*/
		virtual void SetPolygonFill( ePolygonFill Param ) = 0;
		/**
			@brief �A���t�@�u�����h�擾
			@author �t���`
			@return �A���t�@�u�����h�^�C�v
			@note
			�A���t�@�u�����h�Ɋւ���ݒ���擾���܂�
		*/
		virtual eAlphaBlend GetAlphaBlend() const = 0;
		/**
			@brief �J�����O�擾
			@author �t���`
			@return �J�����O�^�C�v
			@note
			�J�����O�Ɋւ���ݒ���擾���܂�
		*/
		virtual eCulling GetCulling() const = 0;
		/**
			@brief �V�U�[�e�X�g�擾
			@author �t���`
			@return �V�U�[�e�X�g�^�C�v
			@note
			�V�U�[�e�X�g�Ɋւ���ݒ���擾���܂�
		*/
		virtual eScissorTest GetScissorTest() const = 0;
		/**
			@brief �A���t�@�e�X�g�擾
			@author �t���`
			@return �A���t�@�e�X�g�^�C�v
			@note
			�A���t�@�e�X�g�Ɋւ���ݒ���擾���܂�
		*/
		virtual eAlphaTest GetAlphaTest() const = 0;
		/**
			@brief �[�x�e�X�g�擾
			@author �t���`
			@return �[�x�e�X�g�^�C�v
			@note
			�[�x�e�X�g�Ɋւ���ݒ���擾���܂�
		*/
		virtual eDepthTest GetDepthTest() const = 0;
		/**
			@brief �[�x�������ݎ擾
			@author �t���`
			@return �[�x�������݃^�C�v
			@note
			�[�x�������݂Ɋւ���ݒ���擾���܂�
		*/
		virtual eDepthWrite GetDepthWrite() const = 0;
		/**
			@brief �|���S���h��Ԃ��擾
			@author �t���`
			@return �|���S���h��Ԃ��^�C�v
			@note
			�|���S���h��Ԃ��Ɋւ���ݒ���擾���܂�
		*/
		virtual ePolygonFill GetPolygonFill() const = 0;
		/**
			@brief �N���[������
			@author �t���`
			@return �������ꂽ�X�e�[�g
			@note
			����̃X�e�[�g�����N���[���𐶐����܂��B
		*/
		virtual IRenderState* Clone() const = 0;
		/**
			@brief ����X�e�[�g�`�F�b�N
			@author �t���`
			@param pIn	[in] ��r����X�e�[�g
			@note
			����̃X�e�[�g���ǂ����`�F�b�N���܂�
		*/
		virtual bool IsEqual( const IRenderState* pIn ) const = 0;
	};
}
}
}
}
/**
	@file
	@brief �ȈՃ��C���`��p�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief ���C���`��p���_
		@author �t���`
	*/
	struct SLineVertex
	{
		float Px;
		float Py;
		float Pz;
		ColorU Color;
	};

	/**
		@brief ���C���`�惂�[�h
		@author �t���`
	*/
	enum eLineMode
	{
		LINE_MODE_2D,	///< 2D�̃��C����`��
		LINE_MODE_3D,	///< 3D�̃��C����`��
	};

	/**
		@brief 2D�ȈՕ`��C���^�[�t�F�C�X
		@author �t���`
		@note 2D�ȈՕ`������邽�߂̃C���^�[�t�F�C�X
	*/
	class ILineRenderer
		: public Interface
	{
	protected:
		virtual ~ILineRenderer(){}

	public:
		/**
			@brief �`��J�n
			@author �t���`
			@param Mode		[in] ���C���̕`�惂�[�h
			@note
			���̃��\�b�h���ĂԂ��Ƃŕ�����̕`��̊J�n��錾�ł��܂��B
		*/
		virtual void CacheReset( eLineMode Mode ) = 0;
		/**
			@brief �`��I��
			@author �t���`
			@note
			���̃��\�b�h���Ă΂ꂽ���Ɏ��ۂɉ�ʂɑ΂��ĕ`�悪�s���܂��B
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief �J�����s��ݒ�
			@author �t���`
			@param Matrix	[in] �J�����̍s��
			@note
			�`��ɗ��p����J�����̃}�g���b�N�X��ݒ肵�܂��B<BR>
			�����Being()�̈�����eLineMode��LINE_MODE_3D�̏ꍇ�ɗ��p����܂��B
		*/
		virtual void SetCameraMatrix( const Kernel::Math::Matrix& Matrix ) = 0;
		/**
			@brief �`���Z�F�ݒ�
			@author �t���`
			@param Color	[in] ��Z����F
			@note
			�`�掞�ɑS�̂ɏ�Z����F��ݒ�ł��܂��B
		*/
		virtual void SetModulateColor( const ColorF& Color ) = 0;
		/**
			@brief �l�p�`�`�惊�N�G�X�g
			@author �t���`
			@param Points	[in] �������\������_�f�[�^�i�Q�łP�����j
			@param Count	[in] �_�̐��i2�_�łP�����ɂȂ�̂ōŒ�ł��Q�j
			@note
			�L���[�ɑ΂��ĕ`��̃��N�G�X�g���s���܂��B
		*/
		virtual void DrawRequest( const SLineVertex* Points, Sint32 Count ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 2D�ȈՕ`��p�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief 2D�ȈՕ`��C���^�[�t�F�C�X
		@author �t���`
		@note 2D�ȈՕ`������邽�߂̃C���^�[�t�F�C�X
	*/
	class ISpriteRenderer
		: public Interface
	{
	protected:
		virtual ~ISpriteRenderer(){}

	public:
		virtual void CacheReset() = 0;
		virtual void CacheDraw() = 0;

		virtual void SetScissorRect( const RectI& ScissorRect ) = 0;
		virtual const RectI& GetScissorRect() const = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, Graphics::State::eAlphaBlend AlphaBlend ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], Graphics::State::eAlphaBlend AlphaBlend ) = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend ) = 0;

		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF& Color, const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void SquareRequest( const RectF& Dst, Sint32 Priority, const ColorF ColorTbl[], const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void PolygonRequest( const Point2DF DstTbl[], Sint32 Priority, const ColorF ColorTbl[], const Point2DF SrcTbl[], Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend ) = 0;

		virtual void SquareDirect( const RectF& Dst, const ColorF& Color, const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void SquareDirect( const RectF& Dst, const ColorF ColorTbl[], const RectF& Src, Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		virtual void PolygonDirect( const Point2DF DstTbl[], const ColorF ColorTbl[], const Point2DF SrcTbl[], Graphics::Resource::ITexture* pTexture, bool IsFilterEnable, bool IsRepeatEnable, Graphics::State::eAlphaBlend AlphaBlend, float Radian, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
	};
}
}
}
}

/**
	@file
	@brief 2D�ȈՕ`��p�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief 2D�ȈՕ`��C���^�[�t�F�C�X
		@author �t���`
		@note 2D�ȈՕ`������邽�߂̃C���^�[�t�F�C�X
	*/
	class ISpriteRenderer3D
		: public Interface
	{
	protected:
		virtual ~ISpriteRenderer3D(){}

	public:
		/**
			@brief �`��J�n
			@author �t���`
			@note
			���̃��\�b�h���ĂԂ��Ƃŕ�����̕`��̊J�n��錾�ł��܂��B
		*/
		virtual void CacheReset() = 0;
		/**
			@brief �`��I��
			@author �t���`
			@note
			���̃��\�b�h���Ă΂ꂽ���Ɏ��ۂɉ�ʂɑ΂��ĕ`�悪�s���܂��B
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief �`��f�[�^��`�F�b�N
			@author �t���`
			@return �`��f�[�^�������true
			@note
			�`�悷��f�[�^�����邩��Ԃ��܂��B
		*/
		virtual bool IsEmpty() = 0;
		/**
			@brief �J�����s��ݒ�
			@author �t���`
			@param mView		[in] �r���[�̍s��
			@param mProjection	[in] �v���W�F�N�V�����̍s��
			@note
			�`��ɗ��p����J�����̃}�g���b�N�X��ݒ肵�܂��B
		*/
		virtual void SetCameraMatrix( const Kernel::Math::Matrix& mView, const Kernel::Math::Matrix& mProjection ) = 0;
		/**
			@brief �`���Z�F�ݒ�
			@author �t���`
			@param Color	[in] ��Z����F
			@note
			�`�掞�ɑS�̂ɏ�Z����F��ݒ�ł��܂��B
		*/
		virtual void SetModulateColor( const ColorF& Color ) = 0;
		/**
			@brief �e�N�X�`���t�B���^�[�L���ݒ�
			@author �t���`
			@param IsFilterEnable	[in] �t�B���^�[�̗L��
			@note
			�`�悷��|���S���ɑ΂���e�N�X�`���̃t�B���^�[�̗L����ݒ肵�܂��B
		*/
		virtual void SetTextureFilterEnable( bool IsFilterEnable ) = 0;
		/**
			@brief �e�N�X�`���J��Ԃ��L���ݒ�
			@author �t���`
			@param IsFilterEnable	[in] �J��Ԃ��̗L��
			@note
			�`�悷��|���S���ɑ΂���e�N�X�`���̌J��Ԃ��̗L����ݒ肵�܂��B
		*/virtual void SetTextureRepeatEnable( bool IsRepeatEnable ) = 0;
		/**
			@brief �l�p�`�`�惊�N�G�X�g
			@author �t���`
			@param Position			[in] �`���
			@param PositionOffset	[in] �`���I�t�Z�b�g
			@param Size				[in] �`��T�C�Y
			@param Color			[in] �`��F
			@param Src				[in] �`�挳
			@param pTexture			[in] �`��e�N�X�`���iNULL��Color�P�F�h��Ԃ��j
			@param AlphaBlend		[in] �A���t�@�u�����h�̎��
			@param Radian			[in] ��]�p�x
			@param RotateOffset		[in] ��]���̒��S����̃I�t�Z�b�g
			@note
			�L���[�ɑ΂��ĕ`��̃��N�G�X�g���s���܂��B<BR>
			���̃��\�b�h�ł̓e�N�X�`���t���̒P���Ȏl�p�`�̕`����s���܂��B
		*/
		virtual void SquareRequest( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		/**
			@brief �l�p�`�`��
			@author �t���`
			@param Position			[in] �`���
			@param PositionOffset	[in] �`���I�t�Z�b�g
			@param Size				[in] �`��T�C�Y
			@param Color			[in] �`��F
			@param Src				[in] �`�挳
			@param pTexture			[in] �`��e�N�X�`���iNULL��Color�P�F�h��Ԃ��j
			@param AlphaBlend		[in] �A���t�@�u�����h�̎��
			@param Radian			[in] ��]�p�x
			@param RotateOffset		[in] ��]���̒��S����̃I�t�Z�b�g
			@note
			�L���[�ɑ΂��ĕ`��̃��N�G�X�g���s�킸�ɒ��ڕ`����s���܂��B<BR>
			���̃��\�b�h�ł̓e�N�X�`���t���̒P���Ȏl�p�`�̕`����s���܂��B
		*/
		virtual void SquareDirect( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		/**
			@brief �l�p�`�`�惊�N�G�X�g
			@author �t���`
			@param Position			[in] �`���
			@param PositionOffset	[in] �`���I�t�Z�b�g
			@param Size				[in] �`��T�C�Y
			@param ColorTbl			[in] �`��F�i����E�E��E�����E�E���̏��ԂłS�j
			@param Src				[in] �`�挳
			@param pTexture			[in] �`��e�N�X�`���iNULL��Color�h��Ԃ��j
			@param AlphaBlend		[in] �A���t�@�u�����h�̎��
			@param Radian			[in] ��]�p�x
			@param RotateOffset		[in] ��]���̒��S����̃I�t�Z�b�g
			@note
			�L���[�ɑ΂��ĕ`��̃��N�G�X�g���s���܂��B<BR>
			���̃��\�b�h�ł̓e�N�X�`���t���̒P���Ȏl�p�`�̕`����s���܂��B
		*/
		virtual void SquareRequest( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF ColorTbl[], const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
		/**
			@brief �l�p�`�`��
			@author �t���`
			@param Position			[in] �`���
			@param PositionOffset	[in] �`���I�t�Z�b�g
			@param Size				[in] �`��T�C�Y
			@param ColorTbl			[in] �`��F�i����E�E��E�����E�E���̏��ԂłS�j
			@param Src				[in] �`�挳
			@param pTexture			[in] �`��e�N�X�`���iNULL��Color�h��Ԃ��j
			@param AlphaBlend		[in] �A���t�@�u�����h�̎��
			@param Radian			[in] ��]�p�x
			@param RotateOffset		[in] ��]���̒��S����̃I�t�Z�b�g
			@note
			�L���[�ɑ΂��ĕ`��̃��N�G�X�g���s�킸�ɒ��ڕ`����s���܂��B<BR>
			���̃��\�b�h�ł̓e�N�X�`���t���̒P���Ȏl�p�`�̕`����s���܂��B
		*/
		virtual void SquareDirect( const Kernel::Math::Vector3& Position, const Kernel::Math::Vector3& PositionOffset, const Kernel::Math::Vector2& Size, const ColorF ColorTbl[], const RectF& Src, Resource::ITexture* pTexture, State::eAlphaBlend AlphaBlend, float Radian = 0.0f, const Point2DF& RotateOffset = Point2DF(0.0f,0.0f) ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �e�L�X�g�`��p�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief �e�L�X�g�`��C���^�[�t�F�C�X
		@author �t���`
		@note �e�L�X�g�`������邽�߂̃C���^�[�t�F�C�X
	*/
	class ITextRenderer
		: public Interface
	{
	protected:
		virtual ~ITextRenderer(){}

	public:
		/**
			@brief �`��J�n
			@author �t���`
			@note
			���̃��\�b�h���ĂԂ��Ƃŕ�����̕`��̊J�n��錾�ł��܂��B
		*/
		virtual void CacheReset() = 0;
		/**
			@brief �`��I��
			@author �t���`
			@note
			���̃��\�b�h���Ă΂ꂽ���Ɏ��ۂɉ�ʂɑ΂��ĕ`�悪�s���܂��B
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief ������`��
			@author �t���`
			@param Position		[in] �`��ʒu
			@param Color		[in] �����F
			@param pText		[in] ������i������printf�j
			@note
			������̕`�揈�����s���܂��B<BR>
			���̃��\�b�h�ł͎��ۂɕ`��͍s��ꂸ�`��̃��N�G�X�g�������s���܂��B
		*/
		virtual Point2DI DrawRequest( const Point2DI& Position, const ColorF& Color, const wchar_t* pText, ... ) = 0;
		/**
			@brief �������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position		[in] �`��ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��č������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DI DrawRequestBasePosition( const Point2DI& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Rect				[in] �`���`
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��č������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DI DrawRequestLeft( const RectI& Rect, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief ���������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Rect				[in] �`���`
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��Ē��������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DI DrawRequestCenter( const RectI& Rect, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �E�����e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Rect				[in] �`���`
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĉE�����ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DI DrawRequestRight( const RectI& Rect, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕`��D��x��ݒ�
			@author �t���`
			@param Priority	[in] �`��D��x
			@note
			�e�L�X�g�̕`�掞�̕`��D��x��ݒ肵�܂��B<BR>
			�����I�ɂ�Simple::ISpriteRenderer�ɑ΂��ē������Ƃ��s���܂��B
		*/
		virtual void SetPriority( Sint32 Priority ) = 0;
		/**
			@brief �e�L�X�g�`��p�̃X�v���C�g�ݒ�
			@author �t���`
			@param pSprite	[in] �X�v���C�g�C���^�[�t�F�C�X
			@note
			�e�L�X�g�̕`��Ɏg���X�v���C�g��ݒ肵�܂��B<BR>
			���̃��\�b�h�ɂ��ݒ���s��Ȃ��ꍇ�͓����ŕێ����Ă���<BR>
			�X�v���C�g�𗘗p���ĕ`�悳��܂��B
		*/
		virtual void SetDrawSprite( Simple::ISpriteRenderer* pSprite ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��T�C�Y�擾
			@author �t���`
			@param pString		[in] �T�C�Y�𒲂ׂ镶����
			@param Length		[in] �������i-1�őS���j
			@return �����`��T�C�Y
			@note
			�����̎��ۂɕ`�悵���ꍇ�̃T�C�Y���擾���܂��B
		*/
		virtual Point2DI GetDrawSize( const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��ʒu�ݒ�
			@author �t���`
			@param Rect		[in] �V�U�����O�̈�
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����`��ʒu��ݒ肵�܂��B
		*/
		virtual void SetScissorRect( const RectI& Rect ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��ʒu�ݒ�
			@author �t���`
			@param Position		[in] �����`��ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����`��ʒu��ݒ肵�܂��B
		*/
		virtual void SetDrawBasePosition( const Point2DI& Position ) = 0;
	};
}
}
}
}
/**
	@file
	@brief �ȈՃg���C�A���O���`��p�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Simple
{
	/**
		@brief �g���C�A���O���`��p���_
		@author �t���`
	*/
	struct STriangleVertex
	{
		float Px;
		float Py;
		float Pz;
		float Nx;
		float Ny;
		float Nz;
		ColorU Color;
	};

	/**
		@brief �g���C�A���O���`�惂�[�h
		@author �t���`
	*/
	enum eTriangleMode
	{
		TRIANGLE_MODE_2D,	///< 2D�̃g���C�A���O����`��
		TRIANGLE_MODE_3D,	///< 3D�̃g���C�A���O����`��
	};

	/**
		@brief 2D�ȈՕ`��C���^�[�t�F�C�X
		@author �t���`
		@note 2D�ȈՕ`������邽�߂̃C���^�[�t�F�C�X
	*/
	class ITriangleRenderer
		: public Interface
	{
	protected:
		virtual ~ITriangleRenderer(){}

	public:
		/**
			@brief �ȈՃ��C�g
			@author �t���`
			@param DirectionVector	[in] ���C�g�̕���
			@param ColorVector		[in] ���C�g�̐F
			@param AmbientVector	[in] ���F
			@note
			�V���v���Ȃ畽�s�����̐ݒ���s���܂��B
		*/
		virtual void SetSimpleLight( const Kernel::Math::VectorS& DirectionVector, const Kernel::Math::VectorS& ColorVector, const Kernel::Math::VectorS& AmbientVector ) = 0;
		/**
			@brief �`��J�n
			@author �t���`
			@param Mode		[in] �g���C�A���O���̕`�惂�[�h
			@note
			���̃��\�b�h���ĂԂ��Ƃŕ�����̕`��̊J�n��錾�ł��܂��B
		*/
		virtual void CacheReset( eTriangleMode Mode ) = 0;
		/**
			@brief �`��I��
			@author �t���`
			@note
			���̃��\�b�h���Ă΂ꂽ���Ɏ��ۂɉ�ʂɑ΂��ĕ`�悪�s���܂��B
		*/
		virtual void CacheDraw() = 0;
		/**
			@brief �N���b�v�̈�ݒ�
			@author �t���`
			@param Matrix	[in] �J�����̍s��
			@note
			�`��ɗ��p����J�����̃}�g���b�N�X��ݒ肵�܂��B<BR>
			�����Being()�̈�����eTriangleMode��TRIANGLE_MODE_3D�̏ꍇ�ɗ��p����܂��B
		*/
		virtual void SetCameraMatrix( const Kernel::Math::Matrix& Matrix ) = 0;
		/**
			@brief �`���Z�F�ݒ�
			@author �t���`
			@param Color	[in] ��Z����F
			@note
			�`�掞�ɑS�̂ɏ�Z����F��ݒ�ł��܂��B
		*/
		virtual void SetModulateColor( const ColorF& Color ) = 0;
		/**
			@brief �O�p�`�`�惊�N�G�X�g
			@author �t���`
			@param Points	[in] �|���S�����\������_�f�[�^�i�R�łP�g���C�A���O���j
			@param Count	[in] �_�̐��i�R�_�łP�g���C�A���O���ɂȂ�̂ōŒ�ł��R�j
			@note
			�L���[�ɑ΂��ĕ`��̃��N�G�X�g���s���܂��B
		*/
		virtual void DrawRequest( const STriangleVertex* Points, Sint32 Count ) = 0;
	};
}
}
}
}
/**
	@file
	@brief ���[�V�����C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ���[�V�����C���^�[�t�F�C�X
		@author �t���`
	*/
	class IRootMotion
		: public Interface
	{
	protected:
		virtual ~IRootMotion(){}

	public:
		/**
			@brief �g��k���L�[���擾
			@author �t���`
			@return �l
			@note
			���[�V��������g��k���L�[���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetScaling() const = 0;
		/**
			@brief ��]�L�[���擾
			@author �t���`
			@return �l
			@note
			���[�V���������]�L�[���擾���܂��B
		*/
		virtual const Kernel::Math::Quaternion& GetRotation() const = 0;
		/**
			@brief �ʒu�L�[���擾
			@author �t���`
			@return �l
			@note
			���[�V��������ʒu�L�[���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetPosition() const = 0;

		/**
			@brief �����擾
			@author �t���`
			@return ���[�V�����̒����i�t���[�����j
			@note
			���[�V�����̒������擾���܂��B
		*/
		virtual float GetLength() const = 0;

		/**
			@brief �t���[�����[�g�ݒ�
			@author �t���`
			@param FrameRate	[in] �t���[�����[�g
			@note
			���[�V�����̃t���[�����[�g��ݒ肵�܂��B
		*/
		virtual void SetFrameRate( Sint32 FrameRate ) = 0;

		/**
			@brief ���[�V�����̍X�V
			@author �t���`
			@param Frame	[in] �t���[��
			@note
			���[�V�������P�t���[���i�߂܂��B
		*/
		virtual void Update( float Frame, bool IsScale, bool IsRotate, bool IsMove ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �e�N�X�`���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief �e�N�X�`���[���b�N���
		@author �t���`
		@note �e�N�X�`���[���b�N���̏��i�[�p
	*/
	struct STextureLockInfo
	{
		void* pPixels;		///< �摜���̐퓬�A�h���X
		Uint32 Pitch;		///< �摜�̂P���C���̃o�C�g��
		Point2DI Size;		///< �摜�̃s�N�Z���T�C�Y
	};

	/**
		@brief �e�N�X�`���[�C���^�[�t�F�C�X
		@author �t���`
		@note �e�N�X�`���[�p�C���^�[�t�F�C�X
	*/
	class ITexture
		: public Interface
	{
	protected:
		virtual ~ITexture(){}

	public:
		/**
			@brief �e�N�X�`���[�T�C�Y�擾
			@author �t���`
			@return �������̗v���T�C�Y
			@note
			�e�N�X�`���[�̐������̗v���T�C�Y
		*/
		virtual const Point2DI& GetRequestSize() const = 0;
		/**
			@brief �e�N�X�`���[�T�C�Y�擾
			@author �t���`
			@return ������̎��ۂ̃T�C�Y
			@note
			�e�N�X�`���[�̐�����̎��ۂ̃T�C�Y
		*/
		virtual const Point2DI& GetTextureSize() const = 0;
		/**
			@brief �e�N�X�`���[��UV�ϊ��l�擾
			@author �t���`
			@return �e�N�X�`���̃s�N�Z���ʒu��UV�ɕϊ�����ׂ̒l
			@note
			�e�N�X�`���̃s�N�Z���ʒu��UV�ɕϊ�����ׂ̒l���擾���܂�<BR>
			���̒l�� 1.0f / GetTextureSize() �Ɠ������̂ł��B
		*/
		virtual const Point2DF& GetTexel2UVTransform() const = 0;
		/**
			@brief �e�N�X�`���[���摜�Ƃ��ĕۑ�
			@author �t���`
			@param pFilePath	[in] �t�@�C���p�X
			@note
			�e�N�X�`����BMP�t�@�C���Ƃ��ĕۑ����܂��B
		*/
		virtual void SaveToBMP( const wchar_t* pFilePath ) const = 0;
		/**
			@brief �e�N�X�`���[���摜�Ƃ��ĕۑ�
			@author �t���`
			@param pFilePath	[in] �t�@�C���p�X
			@note
			�e�N�X�`����PNG�t�@�C���Ƃ��ĕۑ����܂��B
		*/
		virtual void SaveToPNG( const wchar_t* pFilePath ) const = 0;
		/**
			@brief �e�N�X�`���[���摜�Ƃ��ĕۑ�
			@author �t���`
			@param pFilePath	[in] �t�@�C���p�X
			@note
			�e�N�X�`����DDS�t�@�C���Ƃ��ĕۑ����܂��B
		*/
		virtual void SaveToDDS( const wchar_t* pFilePath ) const = 0;
		/**
			@brief �e�N�X�`���[�����b�N
			@author �t���`
			@param Info			[in] ���b�N�����e�N�X�`���̏����i�[���邽�߂̍\����
			@note
			�e�N�X�`���ւ�CPU����̃A�N�Z�X���J�n���܂�<BR>
			CPU�A�N�Z�X�\�ȃe�N�X�`���ȊO�ł͎��s���܂��B
		*/
		virtual bool Lock( STextureLockInfo& Info ) = 0;
		/**
			@brief �e�N�X�`���[���A�����b�N
			@author �t���`
			@note
			�e�N�X�`���ւ�CPU����̃A�N�Z�X���I�����܂�<BR>
			CPU�A�N�Z�X�\�ȃe�N�X�`���ȊO�ł͎��s���܂��B
		*/
		virtual void Unlock() = 0;
		/**
			@brief �e�N�X�`���[���o�b�N�A�b�v
			@author �t���`
			@note
			�����_�����O�^�[�Q�b�g�e�N�X�`���̓��e��<BR>
			�V�X�e���������փo�b�N�A�b�v���܂��B<BR>
			���R���Ȃ�d�������Ȃ̂ŗv���v���Ŏg���܂��傤�B
		*/
		virtual bool BackupToSystem() = 0;
	};
}
}
}
}

/**
	@file
	@brief �W�I���g���V�F�[�_�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief �W�I���g���V�F�[�_�[�C���^�[�t�F�C�X
		@author �t���`
		@note �W�I���g���V�F�[�_�[�p�C���^�[�t�F�C�X
	*/
	class IGeometryShader
		: public Interface
	{
	protected:
		virtual ~IGeometryShader(){}
	};
}
}
}
}
/**
	@file
	@brief ���_�V�F�[�_�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ���_�V�F�[�_�[�C���^�[�t�F�C�X
		@author �t���`
		@note ���_�V�F�[�_�[�p�C���^�[�t�F�C�X
	*/
	class IVertexShader
		: public Interface
	{
	protected:
		virtual ~IVertexShader(){}
	};
}
}
}
}
/**
	@file
	@brief ���_���C�A�E�g�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ���_���C�A�E�g�t�H�[�}�b�g
		@author �t���`
	*/
	enum eVertexLayoutFormat
	{
		VLF_FLOAT32x1,			///< 32Bit float x1
		VLF_FLOAT32x2,			///< 32Bit float x2
		VLF_FLOAT32x3,			///< 32Bit float x3
		VLF_FLOAT32x4,			///< 32Bit float x4
		VLF_FLOAT16x2,			///< 16Bit float x2
		VLF_FLOAT16x4,			///< 16Bit float x4
		VLF_R8G8B8A8,			///< (a,b,g,r) Packed unsigned int
		VLF_UINT8x4,			///< unsigned char x4
		VLF_UINT8Nx4,			///< unsigned char x4 (x/255, y/255, z/255, w/255)
		VLF_UINT16Nx2,			///< unsigned short x2 (x/65535, y/65535, 0.0, 1.0)
		VLF_UINT16Nx4,			///< unsigned short x4 (x/65535, y/65535, z/65535, w/65535)
		VLF_SINT16x2,			///< signed short x2
		VLF_SINT16x4,			///< signed short x4
		VLF_SINT16Nx2,			///< signed short x2 (x/32767, y/32767, 0.0, 1.0)
		VLF_SINT16Nx4,			///< signed short x4 (x/32767, y/32767, z/32767, w/32767)
	};

	/**
		@brief ���_���C�A�E�g���
		@author �t���`
	*/
	enum eVertexLayoutType
	{
		VLT_POSITION,			///< ���[���h�ʒu
		VLT_BLENDWEIGHT,		///< �u�����h�p�E�F�C�g
		VLT_BLENDINDEX,			///< �u�����h�p�C���f�b�N�X
		VLT_NORMAL,				///< �@��
		VLT_TANGENT,			///< �ڐ�
		VLT_BINORMAL,			///< �]�@��
		VLT_COLOR,				///< �F
		VLT_TEXCOORD,			///< �e�N�X�`���t�u
	};

	/**
		@brief ���_���C�A�E�g�p
		@author �t���`
	*/
	struct SVertexLayoutTable
	{
		Sint32 StreamNo;				///< �X�g���[���̔ԍ�
		Sint32 Offset;					///< �\���̂̃I�t�Z�b�g
		eVertexLayoutFormat Format;		///< �f�[�^�̃t�H�[�}�b�g
		eVertexLayoutType Type;			///< �f�[�^�̃^�C�v
		Sint32 TypeIndex;				///< �^�C�v���̃C���f�b�N�X
	};

	/**
		@brief ���_���C�A�E�g�C���^�[�t�F�C�X
		@author �t���`
		@note
		���_�̃��C�A�E�g���������߂̃C���^�[�t�F�C�X
	*/
	class IVertexLayout
		: public Interface
	{
	protected:
		virtual ~IVertexLayout(){}

	public:
	};
}
}
}
}
/**
	@file
	@brief ���_�o�b�t�@�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ���_�o�b�t�@�C���^�[�t�F�C�X
		@author �t���`
		@note
		���_�̃o�b�t�@���������߂̃C���^�[�t�F�C�X
	*/
	class IVertexBuffer
		: public Interface
	{
	protected:
		virtual ~IVertexBuffer(){}

	public:
		/**
			@brief �����O�o�b�t�@�c���_�����
			@author �t���`
			@param �c��̒��_��
			@note
			�����O�o�b�t�@�̎c��̗v�̂��擾���܂��B
		*/
		virtual Uint32 GetRingBufferRest() = 0;
		/**
			@brief �����O�o�b�t�@��������
			@author �t���`
			@note
			���_�o�b�t�@�������O�o�b�t�@�Ƃ��Ĉ����ď������݂܂��B
		*/
		virtual Uint32 RingBufferWrite( const void* pData, Uint32 Count ) = 0;
		/**
			@brief �����O�o�b�t�@��������
			@author �t���`
			@note
			���_�o�b�t�@�������O�o�b�t�@�Ƃ��Ĉ����ď������݂܂��B
		*/
		virtual Uint32 RingBufferWriteByPointer( const void* pData[], Uint32 Count ) = 0;
		/**
			@brief ���b�N
			@author �t���`
			@note
			���_�o�b�t�@�����b�N���ď������݉\�ȏ�Ԃɂ��܂��B
		*/
		virtual void Lock() = 0;
		/**
			@brief ���b�N����
			@author �t���`
			@note
			���_�o�b�t�@�̃��b�N���������ė��p�\�ȏ�Ԃɂ��܂��B
		*/
		virtual void Unlock() = 0;
		/**
			@brief �ǉ�
			@author �t���`
			@note
			���b�N���̒��_�o�b�t�@�Ƀf�[�^�̒ǉ������܂��B
		*/
		virtual void Push( const void* pBuffer, Sint32 Count ) = 0;
		/**
			@brief Push���ꂽ���_���擾
			@author �t���`
			@return ���_��
			@note
			���ۂ�Push����Ă��钸�_�����擾���܂��B
		*/
		virtual Sint32 GetCount() const = 0;
		/**
			@brief ���_�̂P�v�f�̃T�C�Y
			@author �t���`
			@return ���_�̃T�C�Y
			@note
			���_�̃T�C�Y���擾���܂��B
		*/
		virtual Sint32 GetSize() const = 0;
		/**
			@brief �o�b�t�@���ڎ擾
			@author �t���`
			@param Count	[in] ���_��
			@return ���_�o�b�t�@
			@note
			���_�f�[�^�̊i�[����擾���܂��B
		*/
		virtual void* GetBufferDirect( Sint32 Count ) = 0;
	};
}
}
}
}
/**
	@file
	@brief ���_�C���f�b�N�X�o�b�t�@�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ���_�C���f�b�N�X�C���^�[�t�F�C�X
		@author �t���`
		@note
		���_�̃C���f�b�N�X���������߂̃C���^�[�t�F�C�X
	*/
	class IIndexBuffer
		: public Interface
	{
	protected:
		virtual ~IIndexBuffer(){}

	public:
		/**
			@brief ���b�N
			@author �t���`
			@note
			���_�C���f�b�N�X�����b�N���ď������݉\�ȏ�Ԃɂ��܂��B
		*/
		virtual void Lock() = 0;
		/**
			@brief ���b�N����
			@author �t���`
			@note
			���_�C���f�b�N�X�̃��b�N���������ė��p�\�ȏ�Ԃɂ��܂��B
		*/
		virtual void Unlock() = 0;
		/**
			@brief �ǉ�
			@author �t���`
			@note
			���b�N���̒��_�C���f�b�N�X�Ƀf�[�^�̒ǉ������܂��B<BR>
			��������Is32BitIndex��true���w�肵�Ă���ꍇ��unsigned int�̔z����A<BR>
			false���w�肵�Ă���ꍇ��unsigned short�̔z����w�肵�ĉ������B
		*/
		virtual void Push( const void* pBuffer, Sint32 Count ) = 0;
		/**
			@brief Push���ꂽ�C���f�b�N�X���擾
			@author �t���`
			@return �C���f�b�N�X��
			@note
			���ۂ�Push����Ă���C���f�b�N�X�����擾���܂��B
		*/
		virtual Sint32 GetCount() const = 0;
		/**
			@brief �o�b�t�@���ڎ擾
			@author �t���`
			@param Count	[in] �C���f�b�N�X��
			@return �C���f�b�N�X�o�b�t�@
			@note
			�C���f�b�N�X�f�[�^
		*/
		virtual void* GetBufferDirect( Sint32 Count ) = 0;
	};
}
}
}
}
/**
	@file
	@brief �s�N�Z���V�F�[�_�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief �s�N�Z���V�F�[�_�[�C���^�[�t�F�C�X
		@author �t���`
		@note �s�N�Z���V�F�[�_�[�p�C���^�[�t�F�C�X
	*/
	class IPixelShader
		: public Interface
	{
	protected:
		virtual ~IPixelShader(){}
	};
}
}
}
}
/**
	@file
	@brief �t�@�C���ǂݍ��ݗp���X�i�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief �t�@�C���ǂݍ��ݗp�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IFileLoadListener
	{
	protected:
		virtual ~IFileLoadListener(){}

	public:
		/**
			@brief �ǂݍ��ݎ��C�x���g
			@author �t���`
			@param pFileName	[in] �v���t�@�C����
			@param pFileBuffer	[in] �t�@�C���̃o�b�t�@�[�i�[��
			@param FileSize		[in] �t�@�C���T�C�Y
			@param pUserData	[in] ���[�U�[��`�̃|�C���^�[�i�ǂݍ��ݎ��Ɏw�肳��Ă���|�C���^�[�j
			@param pUserSetData	[in] ���[�U�[���Z�b�g����|�C���^�[�iOnRelease�ւ̎󂯓n���j
			@note
			�t�@�C���ǂݍ��݂��K�v�ɂȂ������ɃG���W��������Ăяo�����R�[���o�b�N���\�b�h�ł��B
		*/
		virtual bool OnLoad( const wchar_t* pFileName, const void*& pFileBuffer, Sint32& FileSize, void*& pUserData, void* pUserSetData ) = 0;
		/**
			@brief ������C�x���g
			@author �t���`
			@param pFileBuffer	[in] �t�@�C���̃o�b�t�@�[�i�[��
			@param FileSize		[in] �t�@�C���T�C�Y
			@param pUserData	[in] ���[�U�[��`�̃|�C���^�[�i�ǂݍ��ݎ��Ɏw�肳��Ă���|�C���^�[�j
			@param pUserSetData	[in] ���[�U�[���Z�b�g�����|�C���^�[�iOnLoad����̎󂯓n���j
			@note
			�t�@�C��������K�v�ɂȂ������ɃG���W��������Ăяo�����R�[���o�b�N���\�b�h�ł��B
		*/
		virtual void OnRelease( const void* pFileBuffer, Sint32 FileSize, void* pUserData, void* pUserSetData ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �`�敪���e�[�u���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief �`�敪���e�[�u��
		@author �t���`
	*/
	class IRenderTable
		: public Interface
	{
	protected:
		virtual ~IRenderTable(){}

	public:
		/**
			@brief �{�[����
			@author �t���`
			@return �{�[����
			@note
			�e�[�u�����̃{�[���̐����擾���܂��B
		*/
		virtual Sint32 GetBoneCount() const = 0;
		/**
			@brief �{�[���ԍ��e�[�u��
			@author �t���`
			@return �{�[���ԍ��e�[�u��
			@note
			�e�[�u�����̃{�[���ԍ��e�[�u�����擾���܂��B
		*/
		virtual const Uint8* GetBoneNoTable() const = 0;

		/**
			@brief �|���S���J�n�C���f�b�N�X�擾
			@author �t���`
			@return �|���S���J�n�C���f�b�N�X
			@note
			�e�[�u�����̃|���S���̊J�n�C���f�b�N�X���擾���܂��B
		*/
		virtual Uint32 GetPolygonStart() const = 0;
		/**
			@brief �|���S�����擾
			@author �t���`
			@return �|���S����
			@note
			�e�[�u�����̃|���S�������擾���܂��B
		*/
		virtual Uint32 GetPolygonCount() const = 0;
		/**
			@brief ���_�J�n�C���f�b�N�X�擾
			@author �t���`
			@return ���_�J�n�C���f�b�N�X
			@note
			�e�[�u�����̒��_�̊J�n�C���f�b�N�X���擾���܂��B
		*/
		virtual Uint32 GetVertexStart() const = 0;
		/**
			@brief ���_���擾
			@author �t���`
			@return ���_��
			@note
			�e�[�u�����̒��_�̐����擾���܂��B
		*/
		virtual Uint32 GetVertexCount() const = 0;
	};
}
}
}
}

/**
	@file
	@brief �`��I�u�W�F�N�g�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	enum eDrawObjectType
	{
		DRAWOBJECT_TYPE_PRIMITIVE,
		DRAWOBJECT_TYPE_SPRITE,
		DRAWOBJECT_TYPE_PARTICLE,
		DRAWOBJECT_TYPE_POLYLINE,
	};

	class IDrawObject
		: public Interface
	{
	protected:
		virtual ~IDrawObject(){}

	public:
		virtual void Rendering( const Kernel::Math::Camera& Camera ) = 0;
		virtual void Rendering( Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 IndexCount ) = 0;
		virtual Uint32 GetParticleSortKey() = 0;

		virtual void FlipMatrix() = 0;
		virtual const Kernel::Math::VectorS& GetModelCenter() const = 0;
		virtual const Kernel::Math::Matrix& GetWorldMatrix() const = 0;
		virtual const Kernel::Math::Matrix& GetWorldMatrixPrev() const = 0;
		virtual const Kernel::Math::Matrix* GetBoneMatrixTable() const = 0;
		virtual const Kernel::Math::Matrix* GetBoneMatrixTablePrev() const = 0;

		virtual Sint32 GetWeightCount() const = 0;
		virtual Sint32 GetBoneCount() const = 0;

		virtual IMaterial* GetMaterial( Sint32 Index ) = 0;
		virtual Sint32 GetMaterialCount() const = 0;

		virtual void SetUserData( Kernel::Object::ReferenceObject* pUserData ) = 0;
		virtual Kernel::Object::ReferenceObject* GetUserData() = 0;

		virtual eDrawObjectType GetDrawObjectType() const = 0;
		virtual bool IsDrawEnable() const = 0;
		virtual bool IsDisableBankParticle() const = 0;
		virtual bool ViewFrustumCulling( const Kernel::Math::Camera& Camera ) const = 0;

		virtual void DebugDraw_ViewBounding( Engine::Graphics::Simple::ILineRenderer* pRenderer ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ���[�J�����\�[�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	/**
		@brief ���[�J�����\�[�X
		@author �t���`
	*/
	class ILocalResource
		: public Interface
	{
	protected:
		virtual ~ILocalResource(){}

	public:
		/**
			@brief ���[�J�����\�[�X�̎擾
			@author �t���`
			@param Index	[in] ���\�[�X�C���f�b�N�X
			@param pData	[out] �f�[�^�̃|�C���^
			@param Size		[out] �f�[�^�T�C�Y
			@retval true	����
			@retval false	���s
			@note
			���\�[�X���̃��[�J���ȃ��\�[�X�̎擾���s���܂��B
		*/
		virtual bool Get( Uint32 Index, const void*& pData, Uint32& Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �}�e���A���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
	static const Sint32 MATERIAL_USERDATA_MAX	= 8;
	static const Sint32 MATERIAL_SHADER_MAX		= 8;

	class IMaterialPlugin
		: public Kernel::Object::ReferenceObject
	{
	protected:
		virtual ~IMaterialPlugin() {}

	public:
		virtual const char* GetPluginName() const = 0;
		virtual bool IsLightEnable() const = 0;
		virtual void SetLightEnable( bool IsEnable ) = 0;
		virtual Resource::ITexture* GetTexture( Sint32 Index ) = 0;
		virtual void SetTexture( Sint32 Index, Resource::ITexture* pTex ) = 0;
	};

	class IMaterialListener
		: public Interface
		, public Kernel::Object::ReferenceObject
	{
	protected:
		virtual ~IMaterialListener(){}

	public:
		virtual void OnLoadFromFile( IMaterial* pMaterialInterface, const void* pMaterialData, Sint32 MaterialSize, ILocalResource* pLocalResource ) = 0;
		virtual Engine::Graphics::Resource::IMaterialPlugin* CloneMaterialPluginData( const Engine::Graphics::Resource::IMaterialPlugin* pOriginal ) = 0;

	public:
		virtual Sint32 Release() { return Kernel::Object::ReferenceObject::Release(); }
		virtual Sint32 AddRef()  { return Kernel::Object::ReferenceObject::AddRef(); }
		virtual Sint32 GetReferenceCount() { return Kernel::Object::ReferenceObject::GetReferenceCount(); }
	};

	class IMaterial
		: public Interface
	{
	protected:
		virtual ~IMaterial(){}

	public:
		virtual State::IRenderState* GetRenderState() = 0;

		virtual void* GetUserData( Uint32 Index ) = 0;
		virtual void SetUserData( Uint32 Index, void* pData ) = 0;

		virtual Resource::IVertexShader* GetVertexShader( Uint32 Index ) = 0;
		virtual void SetVertexShader( Uint32 Index, Resource::IVertexShader* pShader ) = 0;

		virtual Resource::IPixelShader* GetPixelShader( Uint32 Index ) = 0;
		virtual void SetPixelShader( Uint32 Index, Resource::IPixelShader* pShader ) = 0;

		virtual bool GetVisible() = 0;
		virtual void SetVisible( bool IsVisible ) = 0;

		virtual IMaterialPlugin* GetMaterialPluginData() = 0;
		virtual void SetMaterialPluginData( IMaterialPlugin* pMaterialPlugin ) = 0;

		virtual IMaterialListener* GetMaterialListener() = 0;
		virtual void SetMaterialListener( IMaterialListener* pMaterialListener ) = 0;

		virtual IRenderTable* GetRenderTable( Sint32 Index ) = 0;
		virtual Sint32 GetRenderTableCount() const = 0;

		virtual void SetType( Sint32 Type ) = 0;
		virtual Sint32 GetType() const = 0;

		virtual bool IsCullEnable() const = 0;
		virtual void SetCullEnable( bool Enable ) = 0;

		virtual bool IsZWriteEnable() const = 0;
		virtual void SetZWriteEnable( bool Enable ) = 0;

		virtual bool IsZTestEnable() const = 0;
		virtual void SetZTestEnable( bool Enable ) = 0;

		virtual State::eAlphaBlend GetAlphaBlend() const = 0;
		virtual void SetAlphaBlend( State::eAlphaBlend Type ) = 0;

		virtual State::ePolygonFill GetPolygonFill() const = 0;
		virtual void SetPolygonFill( State::ePolygonFill Fill ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �m�[�h�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief �m�[�h
		@author �t���`
	*/
	class INode
		: public Interface
	{
	protected:
		virtual ~INode(){}

	public:
		/**
			@brief ���[�J���s��ݒ�
			@author �t���`
			@param mIn	[in] ���[�J���s��
			@note
			�m�[�h�̃��[�J���s���ݒ肵�܂��B
		*/
		virtual void SetLocalMatrix( const Kernel::Math::Matrix& mIn ) = 0;
		/**
			@brief ���[�J���s��擾
			@author �t���`
			@return ���[�J���s��
			@note
			�m�[�h�̃��[�J���s����擾���܂��B
		*/
		virtual const Kernel::Math::Matrix& GetLocalMatrix() = 0;

		/**
			@brief ���[���h�s��ݒ�
			@author �t���`
			@param mIn				[in] ���[���h�s��
			@param HierarchyLevel	[in] �q�G�����L�[�̍X�V���x���i�w�肵���K�w���q�G�����L�[�̍X�V�����܂��j
			@note
			�m�[�h�̃��[���h�s���ݒ肵�܂��B
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mIn, Uint32 HierarchyLevel = 0xFFFFFFFF ) = 0;
		/**
			@brief ���[���h�s��擾
			@author �t���`
			@return ���[���h�s��
			@note
			�m�[�h�̃��[���h�s����擾���܂��B
		*/
		virtual const Kernel::Math::Matrix& GetWorldMatrix() = 0;

		/**
			@brief �e�̃m�[�h�ԍ��擾
			@author �t���`
			@return �e�̃m�[�h�ԍ�
			@note
			�m�[�h�̐e�̃m�[�h�̔ԍ����擾���܂��B
		*/
		virtual Sint32 GetParentNodeNo() = 0;

		/**
			@brief �m�[�h�̕`��L�����擾
			@author �t���`
			@retval true	�`�悷��
			@retval false	�`�悵�Ȃ�
			@note
			�m�[�h�̕`��̗L�����擾���܂��B
		*/
		virtual bool GetVisible() = 0;
		/**
			@brief �m�[�h�̕`��L����ݒ�
			@author �t���`
			@param IsVisible	[in] �`�悷�邩�ǂ���
			@note
			�m�[�h�̕`��̗L����ݒ肵�܂��B
		*/
		virtual void SetVisible( bool IsVisible ) = 0;

		virtual const char* GetName() = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �R���X�g���C���g�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief �R���X�g���C���g
		@author �t���`
	*/
	class IConstraint
		: public Interface
	{
	protected:
		virtual ~IConstraint(){}

	public:
		/**
			@brief ���[�J���s��擾
			@author �t���`
			@return ���[�J���s��
			@note
			�R���X�g���C���g�̃��[�J���s����擾���܂��B
		*/
		virtual Kernel::Math::Matrix GetLocalMatrix() = 0;
		/**
			@brief ���[���h�s��擾
			@author �t���`
			@return ���[���h�s��
			@note
			�R���X�g���C���g�̃��[���h�s����擾���܂��B
		*/
		virtual Kernel::Math::Matrix GetWorldMatrix() = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ���[�V�����X�P�W���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief ���[�V�����X�P�W���[���[�R���g���[���[
		@author �t���`
	*/
	class IMotionScheduler
		: public Interface
	{
	public:
		typedef Uint64								MOTION_HANDLE;
		typedef Kernel::Delegate01<MOTION_HANDLE>	ExitEvent;

	protected:
		virtual ~IMotionScheduler(){}

	public:
		/**
			@brief �Đ��J�n
			@author �t���`
			@param pMC			[in] ���[�V�����R���g���[���[
			@param BlendTime	[in] �u�����h����
			@return ���[�V�����n���h��
			@note
			���[�V�����̍Đ����J�n���܂��B
		*/
		virtual MOTION_HANDLE Play( IMotionController* pMC, Sint32 BlendTime ) = 0;
		/**
			@brief �I�����R�[���o�b�N�C�x���g�ݒ�
			@author �t���`
			@param Handle	[in] ���[�V�����n���h��
			@param Event	[in] �C�x���g
			@note
			���[�V�����̏I�����̃R�[���o�b�N�C�x���g��ݒ肵�܂��B
		*/
		virtual void SetExitCallbackEvent( MOTION_HANDLE Handle, const ExitEvent& Event ) = 0;
		/**
			@brief ���[�V������~
			@author �t���`
			@param Handle	[in] ���[�V�����n���h��
			@note
			���[�V�����̍Đ����~���܂��B
		*/
		virtual void Stop( MOTION_HANDLE Handle ) = 0;
		/**
			@brief ���[�V�����x����~
			@author �t���`
			@param Handle	[in] ���[�V�����n���h��
			@param Frame	[in] �폜����܂ł̃t���[��
			@note
			���[�V�����̍Đ���x����~���܂��B
		*/
		virtual void DelayStop( MOTION_HANDLE Handle, Uint32 Frame ) = 0;
		/**
			@brief ���[�V�����u�����h���ݒ�
			@author �t���`
			@param Handle		[in] ���[�V�����n���h��
			@param BlendRate	[in] �u�����h��
			@note
			���[�V�����̃u�����h����ݒ肵�܂��B
		*/
		virtual void SetBlendRate( MOTION_HANDLE Handle, float BlendRate ) = 0;
		/**
			@brief ���[�V�����v���C�I���e�B�ݒ�
			@author �t���`
			@param Handle	[in] ���[�V�����n���h��
			@param Priority	[in] �v���C�I���e�B
			@note
			���[�V�����̍Đ��v���C�I���e�B��ݒ肵�܂��B
		*/
		virtual void SetPriority( MOTION_HANDLE Handle, Uint8 Priority ) = 0;
		/**
			@brief ���[�V�����Đ����x�ݒ�
			@author �t���`
			@param Handle	[in] ���[�V�����n���h��
			@param Speed	[in] �Đ����x
			@note
			���[�V�����̍Đ����x��ݒ肵�܂��B
		*/
		virtual void SetSpeed( MOTION_HANDLE Handle, float Speed ) = 0;
		/**
			@brief ���[�V�����I���`�F�b�N
			@author �t���`
			@param Handle	[in] ���[�V�����n���h��
			@retval true	�Đ���
			@retval false	��~��
			@note
			���[�V�������Đ������ǂ������擾���܂��B
		*/
		virtual bool IsEnd( MOTION_HANDLE Handle ) = 0;

		virtual float GetFrame( MOTION_HANDLE Handle ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ���[�V�����R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief ���[�V�����R���g���[���[
		@author �t���`
	*/
	class IMotionController
		: public Interface
	{
	protected:
		virtual ~IMotionController(){}

	public:
		/**
			@brief �t���[�����[�g�ݒ�
			@author �t���`
			@param FrameRate	[in] ���[�V�����̃t���[�����[�g
			@note
			���[�V�����̃t���[�����[�g��ݒ肵�܂��B
		*/
		virtual void SetFrameRate( Sint32 FrameRate ) = 0;

		/**
			@brief �X�V
			@author �t���`
			@note
			���[�V�������P�t���[�����i�߂܂��B
		*/
		virtual void Update() = 0;

		/**
			@brief �����ݒ�
			@author �t���`
			@param Length	[in] ���[�V�����̒����i�t���[�����j
			@note
			���[�V�����̒������擾���܂��B
		*/
		virtual void SetLength( Sint32 Length ) = 0;

		/**
			@brief �����擾
			@author �t���`
			@return ���[�V�����̒����i�t���[�����j
			@note
			���[�V�����̒������擾���܂��B
		*/
		virtual float GetLength() const = 0;

		/**
			@brief ���[�v�ݒ�
			@author �t���`
			@param IsLoop	[in] ���[�v�̗L��
			@note
			���[�V�����̃��[�v�̗L����ݒ肵�܂��B
		*/
		virtual void SetLoop( bool IsLoop ) = 0;
		/**
			@brief ���[�v�L���擾
			@author �t���`
			@retval true	���[�v����
			@retval false	���[�v�Ȃ�
			@note
			���[�V�����̃��[�v�̗L�����擾���܂��B
		*/
		virtual bool GetLoop() const = 0;

		/**
			@brief ���[�v�J�n�t���[���ݒ�
			@author ����
			@param Frame	[in] �t���[��
			@note
			���[�v���J�n����Ƃ��̃t���[����ݒ肵�܂��B
		*/
		virtual void SetLoopStartFrame( float Frame ) = 0;

		/**
			@brief ���[�v�J�n�t���[���擾
			@author ����
			@return �t���[��
			@note
			���[�v���J�n����Ƃ��̃t���[�����擾���܂��B
		*/
		virtual float GetLoopStartFrame() const = 0;

		/**
			@brief ���x�ݒ�
			@author �t���`
			@param Speed	[in] ���x�̗L��
			@note
			���[�V�����̑��x�̗L����ݒ肵�܂��B
		*/
		virtual void SetSpeed( float Speed ) = 0;
		/**
			@brief ���x�L���擾
			@author �t���`
			@return ���x
			@note
			���[�V�����̑��x�̗L�����擾���܂��B
		*/
		virtual float GetSpeed() const = 0;

		/**
			@brief �t���[���ݒ�
			@author �t���`
			@param Frame	[in] �t���[��
			@note
			���[�V�����̃t���[���̗L����ݒ肵�܂��B
		*/
		virtual void SetFrame( float Frame ) = 0;
		/**
			@brief �t���[���L���擾
			@author �t���`
			@return �t���[����
			@note
			���[�V�����̃t���[���̗L�����擾���܂��B
		*/
		virtual float GetFrame() const = 0;

		/**
			@brief �D��x�ݒ�
			@author �t���`
			@param Priority	[in] �D��x
			@note
			���[�V�����̗D��x�̗L����ݒ肵�܂��B
		*/
		virtual void SetPriority( Uint8 Priority ) = 0;
		/**
			@brief �D��x�L���擾
			@author �t���`
			@return �D��x
			@note
			���[�V�����̗D��x�̗L�����擾���܂��B
		*/
		virtual Uint8 GetPriority() const = 0;

		/**
			@brief ���[�V�������擾
			@author �t���`
			@return ���[�V�����C���^�[�t�F�C�X��
			@note
			���[�V�����R���g���[���[�Ɋ܂܂�郂�[�V���������擾���܂��B
		*/
		virtual Sint32 GetMotionCount() const = 0;
		/**
			@brief ���[�V�����擾
			@author �t���`
			@param Index	[in] ���[�V�����̃C���f�b�N�X
			@return ���[�V�����C���^�[�t�F�C�X
			@note
			���[�V�����R���g���[���[�Ɋ܂܂�郂�[�V�������擾���܂��B
		*/
		virtual IMotion* GetMotion( Sint32 Index ) = 0;
		/**
			@brief ���[�V�����擾
			@author �t���`
			@param NodeId	[in] ���[�V�����̃m�[�h�C���f�b�N�X
			@return ���[�V�����C���^�[�t�F�C�X
			@note
			���[�V�����R���g���[���[�Ɋ܂܂�郂�[�V�������擾���܂��B
		*/
		virtual IMotion* GetMotionByNodeId( Sint32 NodeId ) = 0;
		/**
			@brief ���[�V�����擾
			@author �t���`
			@param pNodeName	[in] ���[�V�����̃m�[�h��
			@return ���[�V�����C���^�[�t�F�C�X
			@note
			���[�V�����R���g���[���[�Ɋ܂܂�郂�[�V�������擾���܂��B
		*/
		virtual IMotion* GetMotionByNodeName( const char* pNodeName ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ���[�V�����C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief ���[�V�����C���^�[�t�F�C�X
		@author �t���`
	*/
	class IMotion
		: public Interface
	{
	protected:
		virtual ~IMotion(){}

	public:
		/**
			@brief �g��k���L�[���擾
			@author �t���`
			@return �l
			@note
			���[�V��������g��k���L�[���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetScaling() const = 0;
		/**
			@brief ��]�L�[���擾
			@author �t���`
			@return �l
			@note
			���[�V���������]�L�[���擾���܂��B
		*/
		virtual const Kernel::Math::Quaternion& GetRotation() const = 0;
		/**
			@brief �ʒu�L�[���擾
			@author �t���`
			@return �l
			@note
			���[�V��������ʒu�L�[���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetPosition() const = 0;

		/**
			@brief �����擾
			@author �t���`
			@return ���[�V�����̒����i�t���[�����j
			@note
			���[�V�����̒������擾���܂��B
		*/
		virtual float GetLength() const = 0;

		/**
			@brief �t���[�����[�g�ݒ�
			@author �t���`
			@param FrameRate	[in] �t���[�����[�g
			@note
			���[�V�����̃t���[�����[�g��ݒ肵�܂��B
		*/
		virtual void SetFrameRate( Sint32 FrameRate ) = 0;

		/**
			@brief ���[�V�����̍X�V
			@author �t���`
			@note
			���[�V�������P�t���[���i�߂܂��B
		*/
		virtual void Update() = 0;

		/**
			@brief ���[�v�ݒ�
			@author �t���`
			@param IsLoop	[in] ���[�v�̗L��
			@note
			���[�V�����̃��[�v�̗L����ݒ肵�܂��B
		*/
		virtual void SetLoop( bool IsLoop ) = 0;
		/**
			@brief ���[�v�L���擾
			@author �t���`
			@retval true	���[�v����
			@retval false	���[�v�Ȃ�
			@note
			���[�V�����̃��[�v�̗L�����擾���܂��B
		*/
		virtual bool GetLoop() const = 0;

		/**
			@brief ���x�ݒ�
			@author �t���`
			@param Speed	[in] ���x�̗L��
			@note
			���[�V�����̑��x�̗L����ݒ肵�܂��B
		*/
		virtual void SetSpeed( float Speed ) = 0;
		/**
			@brief ���x�L���擾
			@author �t���`
			@return ���x
			@note
			���[�V�����̑��x�̗L�����擾���܂��B
		*/
		virtual float GetSpeed() const = 0;

		/**
			@brief �t���[���ݒ�
			@author �t���`
			@param Frame	[in] �t���[��
			@note
			���[�V�����̃t���[���̗L����ݒ肵�܂��B
		*/
		virtual void SetFrame( float Frame ) = 0;
		/**
			@brief �t���[���L���擾
			@author �t���`
			@return �t���[����
			@note
			���[�V�����̃t���[���̗L�����擾���܂��B
		*/
		virtual float GetFrame() const = 0;

		/**
			@brief �D��x�ݒ�
			@author �t���`
			@param Priority	[in] �D��x
			@note
			���[�V�����̗D��x�̗L����ݒ肵�܂��B
		*/
		virtual void SetPriority( Uint8 Priority ) = 0;
		/**
			@brief �D��x�L���擾
			@author �t���`
			@return �D��x
			@note
			���[�V�����̗D��x�̗L�����擾���܂��B
		*/
		virtual Uint8 GetPriority() const = 0;

		/**
			@brief �m�[�h�C���f�b�N�X�擾
			@author �t���`
			@return �m�[�h�̃C���f�b�N�X
			@note
			���[�V�����̑Ώۂ̃��f���̃m�[�h�̃C���f�b�N�X���擾���܂��B
		*/
		virtual Sint32 GetNodeIndex() const = 0;

		/**
			@brief �m�[�h���擾
			@author �t���`
			@return �m�[�h��
			@note
			���[�V�����̑Ώۂ̃��f���̃m�[�h�����擾���܂��B
		*/
		virtual const char* GetNodeName() const = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ���f���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief ���f���R���g���[���[
		@author �t���`
	*/
	class IModelController
		: public Interface
	{
	protected:
		virtual ~IModelController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief ���[���h�s��ݒ�
			@author �t���`
			@param mIn	[in] ���[���h�s��
			@note
			���f���̃��[���h�s���ݒ肵�܂��B
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mIn ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;

		/**
			@brief �X�P�W���[���[�̍X�V
			@author �t���`
			@param StepTime	[in] �i�s����
			@note
			���f���Ɋ֘A�t�����Ă���X�P�W�����[���X�V���܂��B<BR>
			����ɂ̓��[�V���������܂܂�܂��B
		*/
		virtual void UpdateScheduler( float StepTime = 1.0f ) = 0;
		/**
			@brief �X�P���g���̍X�V
			@author �t���`
			@note
			���f���̃X�P���g�����X�V���܂��B<BR>
			�����ɊK�w�\���̍X�V�������Ȃ��܂��B
		*/
		virtual void UpdateSkelton() = 0;

		/**
			@brief ���[�V�����o�^
			@author �t���`
			@param pMotonGroup	[in] �������郂�[�V�����O���[�v��
			@param pData		[in] ���[�V�����f�[�^�̃|�C���^
			@param Size			[in] ���[�V�����f�[�^�̃T�C�Y
			@note
			���f���Ƀ��[�V������o�^���܂��B
		*/
		virtual void RegistMotion( const char* pMotonGroup, const void* pData, Sint32 Size ) = 0;
		/**
			@brief ���[�V�����폜
			@author �t���`
			@param pMotonGroup	[in] �폜���[�V�����O���[�v��
			@note
			���f���ɓo�^����Ă��郂�[�V���������[�V�����O���[�v�P�ʂō폜���܂��B
		*/
		virtual void UnRegistMotion( const char* pMotonGroup ) = 0;
		/**
			@brief �S���[�V�����폜
			@author �t���`
			@note
			�S�Ẵ��[�V�������폜���܂��B
		*/
		virtual void UnRegistAllMotion() = 0;

		/**
			@brief ���[�V�����R���g���[���[�擾
			@author �t���`
			@param pName	[in] ���[�V�����R���g���[���[��
			@note
			���f�����̃��[�V�����R���g���[���[���擾���܂��B
		*/
		virtual IMotionController* GetMotionController( const char* pName ) = 0;
		/**
			@brief ���[�V�����X�P�W���[���[�擾
			@author �t���`
			@note
			���f�����̃��[�V�����X�P�W���[���[���擾���܂��B
		*/
		virtual IMotionScheduler* GetMotionScheduler() = 0;
		/**
			@brief �R���X�g���C���g�擾
			@author �t���`
			@param pName	[in] �R���X�g���C���g��
			@note
			���f�����̃R���X�g���C���g���擾���܂��B
		*/
		virtual IConstraint* GetConstraint( const char* pName ) = 0;
		/**
			@brief �R���X�g���C���g���擾
			@author �t���`
			@return �R���X�g���C���g��
			@note
			���f�����̃R���X�g���C���g�����擾���܂��B
		*/
		virtual Uint32 GetConstraintCount() = 0;
		/**
			@brief �R���X�g���C���g���擾
			@author �t���`
			@param Index	[in] �R���X�g���C���g�̃C���f�b�N�X
			@param pName	[out] �R���X�g���C���g��
			@param NameSize	[in] pName�̃o�b�t�@�T�C�Y
			@note
			���f�����̃R���X�g���C���g�����擾���܂��B
		*/
		virtual void GetConstraintName( Uint32 Index, char* pName, Uint32 NameSize ) = 0;
		/**
			@brief �m�[�h�擾
			@author �t���`
			@param pName	[in] �m�[�h��
			@note
			���f�����̃m�[�h���擾���܂��B
		*/
		virtual INode* GetNode( const char* pName ) = 0;
		/**
			@brief �m�[�h���擾
			@author �t���`
			@note
			���f�����̃m�[�h�����擾���܂��B
		*/
		virtual Uint32 GetNodeCount() = 0;
		/**
			@brief �m�[�h�擾
			@author �t���`
			@param Index	[in] �m�[�h�̃C���f�b�N�X
			@note
			���f�����̃m�[�h���擾���܂��B
		*/
		virtual INode* GetNode( Uint32 Index ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ���f���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace SMF
{
	/**
		@brief ���f��
		@author �t���`
	*/
	class IModel
		: public Interface
	{
	protected:
		virtual ~IModel(){}

	public:
		/**
			@brief ���f���R���g���[���[�̐���
			@author �t���`
			@return ���f���R���g���[���[
			@note
			���f���̑���p�R���g���[���[�𐶐����܂��B
		*/
		virtual IModelController* CreateController() = 0;
	};
}
}
}
}
}

/**
	@file
	@brief ���f���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace STM
{
	/**
		@brief ���f���R���g���[���[
		@author �t���`
	*/
	class IModelController
		: public Interface
	{
	protected:
		virtual ~IModelController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief �`��Z�����擾
			@author �t���`
			@return �`��Z����
			@note
			�J�����O��Ɏ��ۂɕ`�悳���Z���̐����擾���܂��B
		*/
		virtual Sint32 GetDrawCellCount() = 0;
		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief �r���[�t���X�^���J�����O
			@author �t���`
			@param Camera	[in] �J�����O���s���J����
			@note
			STM���f���S�̂ɑ΂��ăr���[�t���X�^���J�����O���s���܂��B
		*/
		virtual void UpdateViewFrustumCulling( const Kernel::Math::Camera& Camera ) = 0;
		/**
			@brief �R���W�����p���b�V�����̎擾
			@author �t���`
			@return �R���W�����p���b�V����
			@note
		*/
		virtual Uint32 GetCollisionMeshCount() const = 0;
		/**
			@brief �R���W�����p���b�V���̃A�g���r���[�g�擾
			@author �t���`
			@param Index	[in] �R���W�����p���b�V���̃C���f�b�N�X
			@return �R���W�����p���b�V���̃A�g���r���[�g
			@note
			�R���W�����p���b�V���̃A�g���r���[�g���擾���܂��B
		*/
		virtual Uint32 GetCollisionAttribute( Uint32 Index ) const = 0;
		/**
			@brief �R���W�����p���b�V���̒��_���擾
			@author �t���`
			@param Index	[in] �R���W�����p���b�V���̃C���f�b�N�X
			@return �R���W�����p���b�V���̒��_��
			@note
			�R���W�����p���b�V���̒��_�����擾���܂��B
		*/
		virtual Uint32 GetCollisionMeshVertexCount( Uint32 Index ) const = 0;
		/**
			@brief �R���W�����p���b�V���̒��_�C���f�b�N�X���擾
			@author �t���`
			@param Index	[in] �R���W�����p���b�V���̃C���f�b�N�X
			@return �R���W�����p���b�V���̒��_�C���f�b�N�X��
			@note
			�R���W�����p���b�V���̒��_�C���f�b�N�X�����擾���܂��B
		*/
		virtual Uint32 GetCollisionMeshIndexCount( Uint32 Index ) const = 0;
		/**
			@brief �R���W�����p���b�V���̒��_�擾
			@author �t���`
			@param Index	[in] �R���W�����p���b�V���̃C���f�b�N�X
			@return �R���W�����p���b�V���̒��_
			@note
			�R���W�����p���b�V���̒��_���擾���܂��B
		*/
		virtual const Kernel::Math::Vector3* GetCollisionMeshVertex( Uint32 Index ) const = 0;
		/**
			@brief �R���W�����p���b�V���̒��_�C���f�b�N�X�擾
			@author �t���`
			@param Index	[in] �R���W�����p���b�V���̃C���f�b�N�X
			@return �R���W�����p���b�V���̒��_�C���f�b�N�X
			@note
			�R���W�����p���b�V���̒��_�C���f�b�N�X���擾���܂��B
		*/
		virtual const Uint32* GetCollisionMeshIndex( Uint32 Index ) const = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �p�[�e�B�N���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief �p�[�e�B�N���p�p�����[�^�[
		@author �t���`
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< �X�e�[�g
		IMaterialPlugin*		pMaterialData;		///< ���p����}�e���A���v���O�C���f�[�^
		Uint32					SortKey;			///< �`��D��x
		bool					IsSortEnable;		///< �p�[�e�B�N���̃\�[�g�̗L��
		bool					IsBankDisable;		///< �p�[�e�B�N���̃o���N��]�𕕂���

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param pState		[in] �`��ɗ��p����X�e�[�g�i�K�{�j
			@param pMaterial	[in] �`��ɗ��p����}�e���A���i�K�{�j
			@param IsSort		[in] �p�[�e�B�N���̃\�[�g�̗L��
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial, bool IsSort )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, SortKey			( 0 )
			, IsSortEnable		( IsSort )
			, IsBankDisable		( false )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~SParameter()
		{
			SAFE_RELEASE( pRenderState )
			SAFE_RELEASE( pMaterialData )
		}
	};
}
}
}
}
}

/**
	@file
	@brief �p�[�e�B�N���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/

/**
	@file
	@brief �p�[�e�B�N���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief �p�[�e�B�N���R���g���[���[
		@author �t���`
	*/
	class IParticleController
		: public Interface
	{
	protected:
		virtual ~IParticleController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief �����J�n
			@author �t���`
			@note
			�p�[�e�B�N���̐����������J�n���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief �����I��
			@author �t���`
			@note
			�p�[�e�B�N���̐����������I�����܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �`��y�[�W�̃t���b�v
			@author �t���`
			@note
			�t���[���̍Ō�ŌĂяo���Ă��������B
		*/
		virtual void FlipPage() = 0;
		/**
			@brief �p�[�e�B�N������
			@author �t���`
			@param Position		[in] �ʒu
			@param Size			[in] �T�C�Y
			@param Color		[in] �F
			@param Texture		[in] �e�N�X�`����`
			@param Radian		[in] ��]�p�x
			@note
			�p�[�e�B�N���̐������s���܂��B<BR>
			�P��`�P�ʂ�Begin/End�Ԃɒǉ����Ă��������B
		*/
		virtual void DrawRequest( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Texture, float Radian ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �p�[�e�B�N���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief �p�[�e�B�N���R���g���[���[
		@author �t���`
	*/
	class IVolumeParticleController
		: public Interface
	{
	protected:
		virtual ~IVolumeParticleController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief �����J�n
			@author �t���`
			@note
			�p�[�e�B�N���̐����������J�n���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief �����I��
			@author �t���`
			@note
			�p�[�e�B�N���̐����������I�����܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �`��y�[�W�̃t���b�v
			@author �t���`
			@note
			�t���[���̍Ō�ŌĂяo���Ă��������B
		*/
		virtual void FlipPage() = 0;
		/**
			@brief �p�[�e�B�N������
			@author �t���`
			@param Position		[in] �ʒu
			@param Size			[in] �T�C�Y
			@param Color		[in] �F
			@param Texture		[in] �e�N�X�`����`
			@param Radian		[in] ��]�p�x
			@param BasePosition	[in] ��ʒu�i���̈ʒu�Ƀ|�C���g���C�g���u�����`�Ń��C�e�B���O����܂��j
			@note
			�p�[�e�B�N���̐������s���܂��B<BR>
			�P��`�P�ʂ�Begin/End�Ԃɒǉ����Ă��������B
		*/
		virtual void DrawRequest( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Texture, float Radian, const Kernel::Math::VectorS& BasePosition ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �p�[�e�B�N���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Particle
{
	/**
		@brief �p�[�e�B�N���R���g���[���[
		@author �t���`
	*/
	class IEnhancedParticleController
		: public Interface
	{
	protected:
		virtual ~IEnhancedParticleController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief �����J�n
			@author �t���`
			@note
			�p�[�e�B�N���̐����������J�n���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief �����I��
			@author �t���`
			@note
			�p�[�e�B�N���̐����������I�����܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �`��y�[�W�̃t���b�v
			@author �t���`
			@note
			�t���[���̍Ō�ŌĂяo���Ă��������B
		*/
		virtual void FlipPage() = 0;
		/**
			@brief �p�[�e�B�N������
			@author �t���`
			@param Position		[in] �ʒu
			@param Size			[in] �T�C�Y
			@param Color		[in] �F
			@param Texture		[in] �e�N�X�`����`
			@param Radian		[in] ��]�p�x
			@param AlphaBlend	[in] �A���t�@�u�����h�w��
			@note
			�p�[�e�B�N���̐������s���܂��B<BR>
			�P��`�P�ʂ�Begin/End�Ԃɒǉ����Ă��������B
		*/
		virtual void DrawRequest( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const ColorF& Color, const RectF& Texture, float Radian, State::eAlphaBlend AlphaBlend ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �v���~�e�B�u�R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Primitive
{
	/**
		@brief �v���~�e�B�u�p�p�����[�^�[
		@author �t���`
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< �X�e�[�g
		IMaterialPlugin*		pMaterialData;		///< ���p����}�e���A���v���O�C���f�[�^
		Sint32					BoneWeightCount;	///< �{�[���̂P���_������̃E�F�C�g���i�ő�S�j
		Sint32					BoneCount;			///< �{�[���̖{���i�ő�S�O�j
		bool					IsDynamic;			///< ���I�o�b�t�@��ON/OFF�i���t���[���ȏ㏑��������ꍇ��ON�Ɂj
		bool					IsWireFrame;		///< ���C���[�t���[���`��

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param pState		[in] �`��ɗ��p����X�e�[�g�i�K�{�j
			@param pMaterial	[in] �`��ɗ��p����}�e���A���i�K�{�j
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, BoneWeightCount	( 0 )
			, BoneCount			( 0 )
			, IsDynamic			( false )
			, IsWireFrame		( false )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~SParameter()
		{
			SAFE_RELEASE( pRenderState )
			SAFE_RELEASE( pMaterialData )
		}
	};

	/**
		@brief �v���~�e�B�u�p���_�f�[�^
		@author �t���`
	*/
	struct SVertex
	{
		Kernel::Math::Vector3	Position;	///< �ʒu
		Kernel::Math::Vector3	Normal;		///< �@��
		Uint32					Color;		///< �F
		Kernel::Math::Vector2	Texture;	///< �e�N�X�`��UV
		union {
			Uint32 Weight;					///< ���_�E�F�C�g
			Uint8 Weights[4];				///< ���_�E�F�C�g
		};
		union {
			Uint32 Index;					///< ���_�X�L�j���O�p�C���f�b�N�X
			Uint8 Indexs[4];				///< ���_�X�L�j���O�p�C���f�b�N�X
		};
	};

	/**
		@brief �v���~�e�B�u�R���g���[���[
		@author �t���`
	*/
	class IPrimitiveController
		: public Interface
	{
	protected:
		virtual ~IPrimitiveController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief ���[���h�s��ݒ�
			@author �t���`
			@param mIn	[in] ���[���h�s��
			@note
			�v���~�e�B�u�̃��[���h�s���ݒ肵�܂��B
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mIn ) = 0;

		/**
			@brief �{�[���p�s��ݒ�
			@author �t���`
			@param pMatrix	[in] �s��e�[�u��
			@param Count	[in] �s��
			@note
			�{�[���X�L�j���O�p�̍s���ݒ肵�܂��B
		*/
		virtual void SetBoneMatrix( const Kernel::Math::Matrix* pMatrix, Sint32 Count ) = 0;

		/**
			@brief �{�[���p�s��ݒ�
			@author �t���`
			@param Matrix	[in] �s��e�[�u��
			@param Index	[in] �s��
			@note
			�{�[���X�L�j���O�p�̍s���ݒ肵�܂��B
		*/
		virtual void SetBoneMatrix( const Kernel::Math::Matrix& Matrix, Sint32 Index ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;

		/**
			@brief �����J�n
			@author �t���`
			@note
			�f�[�^�̐����J�n���鎖��ʒm���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief �����I��
			@author �t���`
			@note
			�f�[�^�̐����I����������ʒm���܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �`��y�[�W�̃t���b�v
			@author �t���`
			@note
			�t���[���̍Ō�ŌĂяo���Ă��������B
		*/
		virtual void FlipPage() = 0;
		/**
			@brief ���_�f�[�^�ݒ�
			@author �t���`
			@param pVertex	[in] ���_�f�[�^
			@param Count	[in] ���_��
			@note
			���_�f�[�^��ݒ肵�܂��B<BR>
			���ɐ�������Ă�����̂ɑ΂��Ēǉ��ɂȂ�܂��B
		*/
		virtual void SetVertex( const SVertex* pVertex, Sint32 Count ) = 0;
		/**
			@brief ���_�C���f�b�N�X�f�[�^�ݒ�
			@author �t���`
			@param pIndex	[in] ���_�C���f�b�N�X�f�[�^
			@param Count	[in] ���_�C���f�b�N�X��
			@note
			���_�C���f�b�N�X�f�[�^��ݒ肵�܂��B<BR>
			���ɐ�������Ă�����̂ɑ΂��Ēǉ��ɂȂ�܂��B<BR>
			32Bit�C���f�b�N�X�̏ꍇ��Uint32�ɂȂ�A16Bit�C���f�b�N�X�̏ꍇ��Uint16�ɂȂ�܂��B
		*/
		virtual void SetIndex( const void* pIndex, Sint32 Count ) = 0;
		/**
			@brief 32Bit�C���f�b�N�X�����擾
			@author �t���`
			@retval true	32Bit�C���f�b�N�X
			@retval false	16Bit�C���f�b�N�X
			@note
			���_�C���f�b�N�X��32Bit���ǂ������擾���܂��B
		*/
		virtual bool Is32BitIndex() const = 0;
		/**
			@brief ���_���擾
			@author �t���`
			@return ���_��
			@note
			���݂̒��_�����擾���܂��B
		*/
		virtual Sint32 GetVertexCount() const = 0;
		/**
			@brief ���_�C���f�b�N�X���擾
			@author �t���`
			@return ���_�C���f�b�N�X��
			@note
			���݂̒��_�C���f�b�N�X�����擾���܂��B
		*/
		virtual Sint32 GetIndexCount() const = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �X�v���C�g�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Sprite
{
	/**
		@brief �v���~�e�B�u�p�p�����[�^�[
		@author �t���`
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< �X�e�[�g
		IMaterialPlugin*		pMaterialData;		///< ���p����}�e���A���v���O�C���f�[�^
		bool					IsSortEnable;		///< �\�[�g�̂��邩�ǂ���

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param pState		[in] �`��ɗ��p����X�e�[�g�i�K�{�j
			@param pMaterial	[in] �`��ɗ��p����}�e���A���i�K�{�j
			@param IsSort		[in] �`�掞�Ƀ\�[�g�����邩�ǂ���
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial, bool IsSort )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, IsSortEnable		( IsSort )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~SParameter()
		{
			SAFE_RELEASE( pMaterialData )
			SAFE_RELEASE( pRenderState )
		}
	};

	/**
		@brief �X�v���C�g�R���g���[���[
		@author �t���`
	*/
	class ISpriteController
		: public Interface
	{
	protected:
		virtual ~ISpriteController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief �����J�n
			@author �t���`
			@note
			�X�v���C�g�̐����������J�n���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief �����I��
			@author �t���`
			@note
			�X�v���C�g�̐����������I�����܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �`��y�[�W�̃t���b�v
			@author �t���`
			@note
			�t���[���̍Ō�ŌĂяo���Ă��������B
		*/
		virtual void FlipPage() = 0;
		/**
			@brief �X�v���C�g�̕`��
			@author �t���`
			@param mWorld	[in] ���[���h�s��
			@param Size		[in] �T�C�Y
			@param Src		[in] �`��Ɏg���e�N�X�`���̋�`
			@param Color	[in] �`��F
			@param UvIndex	[in] �`��Ɏg���e�N�X�`���̃C���f�b�N�X
			@note
			�X�v���C�g�̕`����s���܂��B<BR>
			�K��Begin()/End()�̊ԂŌĂяo���ĉ������B
		*/
		virtual void Draw( const Kernel::Math::Matrix &mWorld, const Kernel::Math::Vector2& Size, const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief �X�v���C�g�̕`��
			@author �t���`
			@param mWorld	[in] ���[���h�s��
			@param PointTbl	[in] �`��̂S�_�i����A�E��A�����A�E���j
			@param Src		[in] �`��Ɏg���e�N�X�`���̋�`
			@param Color	[in] �`��F
			@param UvIndex	[in] �`��Ɏg���e�N�X�`���̃C���f�b�N�X
			@note
			�X�v���C�g�̕`����s���܂��B<BR>
			�K��Begin()/End()�̊ԂŌĂяo���ĉ������B
		*/
		virtual void Draw( const Kernel::Math::Matrix &mWorld, const Kernel::Math::Vector2 PointTbl[], const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief �r���{�[�h�̕`��
			@author �t���`
			@param Position	[in] �`��ʒu
			@param Size		[in] �T�C�Y
			@param Src		[in] �`��Ɏg���e�N�X�`���̋�`
			@param Color	[in] �`��F
			@param UvIndex	[in] �`��Ɏg���e�N�X�`���̃C���f�b�N�X
			@note
			�X�v���C�g�̕`����s���܂��B<BR>
			�K��Begin()/End()�̊ԂŌĂяo���ĉ������B
		*/
		virtual void DrawBillboard( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief �r���{�[�h�̕`��
			@author �t���`
			@param Position	[in] �`��ʒu
			@param PointTbl	[in] �`��̂S�_�i����A�E��A�����A�E���j
			@param Src		[in] �`��Ɏg���e�N�X�`���̋�`
			@param Color	[in] �`��F
			@param UvIndex	[in] �`��Ɏg���e�N�X�`���̃C���f�b�N�X
			@note
			�X�v���C�g�̕`����s���܂��B<BR>
			�K��Begin()/End()�̊ԂŌĂяo���ĉ������B
		*/
		virtual void DrawBillboard( const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2 PointTbl[], const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief �C�ӎ��Œ�r���{�[�h�̕`��
			@author �t���`
			@param Axis		[in] ��]��(�P�ʃx�N�g��)
			@param Position	[in] �`��ʒu
			@param Size		[in] �T�C�Y
			@param Src		[in] �`��Ɏg���e�N�X�`���̋�`
			@param Color	[in] �`��F
			@param UvIndex	[in] �`��Ɏg���e�N�X�`���̃C���f�b�N�X
			@note
			�X�v���C�g�̕`����s���܂��B<BR>
			�K��Begin()/End()�̊ԂŌĂяo���ĉ������B
		*/
		virtual void DrawAxisBillboard( const Kernel::Math::VectorS& Axis, const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2& Size, const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
		/**
			@brief �C�ӎ��Œ�r���{�[�h�̕`��
			@author �t���`
			@param Axis		[in] ��]��(�P�ʃx�N�g��)
			@param Position	[in] �`��ʒu
			@param PointTbl	[in] �`��̂S�_�i����A�E��A�����A�E���j
			@param Src		[in] �`��Ɏg���e�N�X�`���̋�`
			@param Color	[in] �`��F
			@param UvIndex	[in] �`��Ɏg���e�N�X�`���̃C���f�b�N�X
			@note
			�X�v���C�g�̕`����s���܂��B<BR>
			�K��Begin()/End()�̊ԂŌĂяo���ĉ������B
		*/
		virtual void DrawAxisBillboard( const Kernel::Math::VectorS& Axis, const Kernel::Math::VectorS& Position, const Kernel::Math::Vector2 PointTbl[], const RectF& Src, ColorF Color, Sint32 UvIndex = 0 ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �|�����C���R���g���[���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace PolyLine
{
	/**
		@brief DrawList�p�\����
		@author �t���`
	*/
	struct SListData
	{
		Kernel::Math::VectorS Position;	///< ���S�_
		float Width;					///< ��
		ColorF Color;					///< �F
	};

	/**
		@brief �|�����C���p�p�����[�^�[
		@author �t���`
	*/
	struct SParameter
	{
		State::IRenderState*	pRenderState;		///< �X�e�[�g
		IMaterialPlugin*		pMaterialData;		///< ���p����}�e���A���v���O�C���f�[�^
		bool					IsDynamic;			///< ���I�o�b�t�@��ON/OFF�i���t���[���ȏ㏑��������ꍇ��ON�Ɂj
		bool					IsAutoResize;		///< �������T�C�Y��ON/OFF

		/**
			@brief �R���X�g���N�^
			@author �t���`
			@param pState		[in] �`��ɗ��p����X�e�[�g�i�K�{�j
			@param pMaterial	[in] �`��ɗ��p����}�e���A���i�K�{�j
		*/
		SParameter( State::IRenderState* pState, IMaterialPlugin* pMaterial )
			: pRenderState		( pState )
			, pMaterialData		( pMaterial )
			, IsDynamic			( false )
			, IsAutoResize		( false )
		{
			SAFE_ADDREF( pRenderState )
			SAFE_ADDREF( pMaterialData )
		}
		/**
			@brief �f�X�g���N�^
			@author �t���`
		*/
		~SParameter()
		{
			SAFE_RELEASE( pRenderState )
			SAFE_RELEASE( pMaterialData )
		}
	};

	/**
		@brief �|�����C���R���g���[���[
		@author �t���`
	*/
	class IPolyLineController
		: public Interface
	{
	protected:
		virtual ~IPolyLineController(){}

	public:
		/**
			@brief �A�N�e�B�u�̐ݒ�
			@author �t���`
			@param IsActive	[in] �A�N�e�B�u���ǂ���
			@note
			���f���̃A�N�e�B�u��Ԃ�ݒ肵�܂��B<BR>
			��A�N�e�B�u�ɂȂ�ƕ`�悳��܂���B
		*/
		virtual void SetActive( bool IsActive ) = 0;

		/**
			@brief �`��I�u�W�F�N�g���擾
			@author �t���`
			@return �`��I�u�W�F�N�g��
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�N�g�̐����擾���܂��B
		*/
		virtual Sint32 GetDrawObjectCount() const = 0;
		/**
			@brief �`��I�u�W�F�N�g�擾
			@author �t���`
			@param Index	[in] �`��I�u�W�F�N�g�̃C���f�b�N�X
			@return �`��I�u�W�F�N�g
			@note
			�C���^�[�t�F�C�X�Ɋ܂܂��`��I�u�W�F�g���擾���܂��B
		*/
		virtual IDrawObject* GetDrawObject( Sint32 Index ) = 0;
		/**
			@brief �����J�n
			@author �t���`
			@note
			�|�����C���̐����������J�n���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief �����I��
			@author �t���`
			@note
			�|�����C���̐����������I�����܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �`��y�[�W�̃t���b�v
			@author �t���`
			@note
			�t���[���̍Ō�ŌĂяo���Ă��������B
		*/
		virtual void FlipPage() = 0;
		/**
			@brief �|�����C������
			@author �t���`
			@param List		[in] �|�����C���p�̃f�[�^�̃��X�g
			@param Count	[in] �f�[�^�̃��X�g�̐�
			@param Src		[in] �e�N�X�`����UV���i�s�N�Z���P�ʁj
			@param UvIndex	[in] �e�N�X�`���̃C���f�b�N�X
			@note
			�|�����C���̐������s���܂��B<BR>
			�K��Being()/End()�ԂŌĂяo���ĉ������B
		*/
		virtual void DrawPolyLine( const SListData List[], Sint32 Count, const RectF& Src, Sint32 UvIndex = 0 ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �e�L�X�g�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
namespace Resource
{
namespace Text
{
	/**
		@brief �e�L�X�g�f�[�^
		@author �t���`
	*/
	class ITextData
		: public Interface
	{
	protected:
		virtual ~ITextData(){}

	public:
		/**
			@brief �e�L�X�g�f�[�^�̕����Ԑݒ�
			@author �t���`
			@param Space		[in] �����Ԃ̗]��
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����Ԃ̗]����ݒ肵�܂��B
		*/
		virtual void SetFontSpace( const Point2DI& Space ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����T�C�Y�ݒ�
			@author �t���`
			@param Size		[in] �����T�C�Y
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����T�C�Y��ݒ肵�܂��B
		*/
		virtual void SetDrawFontSize( Sint32 Size ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����T�C�Y�ݒ�
			@author �t���`
			@param Size		[in] �����T�C�Y
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����T�C�Y��ݒ肵�܂��B
		*/
		virtual void SetDrawFontSize3D( float Size ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����T�C�Y�擾
			@author �t���`
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̊�{�����T�C�Y���擾���܂��B
		*/
		virtual Sint32 GetOriginalFontSize() const = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����T�C�Y�擾
			@author �t���`
			@return �����̃x�[�X�T�C�Y
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̊�{�����T�C�Y���擾���܂��B<BR>
			�����Ŏ擾�ł���T�C�Y�̓c�[����Ő����������̃T�C�Y�ł��B
		*/
		virtual Sint32 GetDrawFontSize() const = 0;
		/**
			@brief �e�L�X�g�f�[�^�̏c�p���擾
			@author �t���`
			@retval true	�c�����t�H���g
			@retval false	�������t�H���g
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̊�{�����T�C�Y���擾���܂��B
		*/
		virtual bool IsVerticale() const = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕`��D��x��ݒ�
			@author �t���`
			@param Priority	[in] �`��D��x
			@note
			�e�L�X�g�̕`�掞�̕`��D��x��ݒ肵�܂��B<BR>
			�����I�ɂ�Simple::ISpriteRenderer�ɑ΂��ē������Ƃ��s���܂��B
		*/
		virtual void SetPriority( Sint32 Priority ) = 0;
		/**
			@brief �e�L�X�g�`��p�̃X�v���C�g�ݒ�
			@author �t���`
			@param pSprite	[in] �X�v���C�g�C���^�[�t�F�C�X
			@note
			�e�L�X�g�̕`��Ɏg���X�v���C�g��ݒ肵�܂��B<BR>
			���̃��\�b�h�ɂ��ݒ���s��Ȃ��ꍇ�͓����ŕێ����Ă���<BR>
			�X�v���C�g�𗘗p���ĕ`�悳��܂��B
		*/
		virtual void SetDrawSprite( Simple::ISpriteRenderer* pSprite ) = 0;
		/**
			@brief �e�L�X�g�`��p�̃X�v���C�g�ݒ�
			@author �t���`
			@param pSprite	[in] �X�v���C�g�C���^�[�t�F�C�X
			@note
			�e�L�X�g�̕`��Ɏg���X�v���C�g��ݒ肵�܂��B<BR>
			���̃��\�b�h�ɂ��ݒ���s��Ȃ��ꍇ�͓����ŕێ����Ă���<BR>
			�X�v���C�g�𗘗p���ĕ`�悳��܂��B
		*/
		virtual void SetDrawSprite3D( Simple::ISpriteRenderer3D* pSprite ) = 0;

		/**
			@brief �e�L�X�g�f�[�^�̕����`��ʒu�ݒ�
			@author �t���`
			@param Position		[in] �����`��ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����`��ʒu��ݒ肵�܂��B
		*/
		virtual void SetDrawBasePosition( const Point2DF& Position ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̃��Z�b�g
			@author �t���`
			@note
			�e�L�X�g�f�[�^�����Z�b�g���܂��B
		*/
		virtual void Reset() = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕`��
			@author �t���`
			@note
			�e�L�X�g�f�[�^���̕`����ꊇ�ōs���܂��B
		*/
		virtual void Draw() = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��ʒu�ݒ�
			@author �t���`
			@param Rect		[in] �V�U�����O�̈�
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����f�[�^�̕����`��ʒu��ݒ肵�܂��B
		*/
		virtual void SetScissorRect( const RectI& Rect ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��T�C�Y�擾
			@author �t���`
			@param pString		[in] �T�C�Y�𒲂ׂ镶����
			@param Length		[in] �������i-1�őS���j
			@return �����`��T�C�Y
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̎��ۂɕ`�悵���ꍇ�̃T�C�Y���擾���܂��B
		*/
		virtual Point2DF GetDrawSize( const wchar_t* pString, Sint32 Length = -1 ) const = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��T�C�Y�擾
			@author �t���`
			@param pString		[in] �T�C�Y�𒲂ׂ镶����
			@param Length		[in] �������i-1�őS���j
			@return �����`��T�C�Y
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̎��ۂɕ`�悵���ꍇ�̃T�C�Y���擾���܂��B
		*/
		virtual Kernel::Math::Vector3 GetDrawSize3D( const wchar_t* pString, Sint32 Length ) const = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��I���ʒu�擾
			@author �t���`
			@param pString		[in] �T�C�Y�𒲂ׂ镶����
			@param Length		[in] �������i-1�őS���j
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̎��ۂɕ`�悵���ꍇ�̏I�[�ʒu���擾���܂��B
		*/
		virtual Point2DF GetDrawEndPosition( const wchar_t* pString, Sint32 Length = -1 ) const = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��J�n�ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̕`����s���܂��B<BR>
			Text_DrawLeft()�Ɠ��l�ɍ������ŕ`�悳��܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DF DrawDirect( const Point2DF& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��J�n�ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̕`����s���܂��B<BR>
			Text_DrawLeft()�Ɠ��l�ɍ������ŕ`�悳��܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DF DrawRequest( const Point2DF& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Rect				[in] �`���`
			@param Offset			[in] �`��ʒu�̃I�t�Z�b�g
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��č������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DF DrawRequestLeft( const RectF& Rect, const Point2DF& Offset, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief ���������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Rect				[in] �`���`
			@param Offset			[in] �`��ʒu�̃I�t�Z�b�g
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��Ē��������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DF DrawRequestCenter( const RectF& Rect, const Point2DF& Offset, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �E�����e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Rect				[in] �`���`
			@param Offset			[in] �`��ʒu�̃I�t�Z�b�g
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@param IsBasePosition	[in] �x�[�X�|�W�V��������`�悷�邩�ǂ����̃t���O
			@return �����`��I�[�ʒu
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĉE�����ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual Point2DF DrawRequestRight( const RectF& Rect, const Point2DF& Offset, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1, bool IsBasePosition = false ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̕`����s���܂��B<BR>
			Text_DrawLeft()�Ɠ��l�ɍ������ŕ`�悳��܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual void DrawDirect3D( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief �e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��ʒu
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĕ����̕`����s���܂��B<BR>
			Text_DrawLeft()�Ɠ��l�ɍ������ŕ`�悳��܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual void DrawRequest3D( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief �������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��č������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual void DrawRequest3DLeft( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief ���������e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��Ē��������ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual void DrawRequest3DCenter( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
		/**
			@brief �E�����e�L�X�g�f�[�^�̕����`��
			@author �t���`
			@param Position			[in] �`��ʒu
			@param Color			[in] �`��F
			@param pString			[in] �`�悷�镶����
			@param Length			[in] �������i-1�őS���j
			@note
			�Ώۂ̃C���f�b�N�X�ɑ΂��ĉE�����ŕ����̕`����s���܂��B<BR>
			IsBasePosition=true�̏ꍇ��Text_SetDrawBasePosition�Őݒ肵���ꏊ���炩����܂��B
		*/
		virtual void DrawRequest3DRight( const Kernel::Math::Vector3& Position, const ColorF& Color, const wchar_t* pString, Sint32 Length = -1 ) = 0;
	};
}
}
}
}
}

/**
	@file
	@brief �O���t�B�b�N�}�l�[�W���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Graphics
{
	static const Sint32 RENDER_TARGET_MAX_COUNT	= 4;	///< �`��^�[�Q�b�g�̍ő吔
	static const Sint32 TEXTURE_STAGE_MAX_COUNT	= 12;	///< �e�N�X�`���̓������p�\�̍ő吔

	/**
		@brief �O���t�B�b�NAPI
		@author �t���`
		@note
		�O���t�B�b�NAPI
	*/
	enum eGraphicsAPI
	{
		GRAPHICS_API_DIRECTX_09,
		GRAPHICS_API_DIRECTX_10,
		GRAPHICS_API_DIRECTX_11,
		GRAPHICS_API_UNKNOWN,
	};

	/**
		@brief �e�N�X�`���t�B���^
		@author �t���`
		@note
		�e�N�X�`���̃t�B���^
	*/
	enum eTextureFilter
	{
		TEXTURE_FILTER_NEAREST,
		TEXTURE_FILTER_BILINEAR,
		TEXTURE_FILTER_ANISOTROPIC,
	};

	/**
		@brief �e�N�X�`���t�H�[�}�b�g
		@author �t���`
		@note
		�e�N�X�`���̃t�H�[�}�b�g
	*/
	enum eTextureFormat
	{
		TF_TEXTURE_A8,					///< alpha-only
		TF_TEXTURE_32BIT,				///< A8R8G8B8
		TF_TEXTURE_16BIT,				///< A4R4G4B4
		TF_TEXTURE_DXT,					///< DXT1
		TF_TEXTURE_DXT_ALPHA,			///< DXT5/DXT3

		TF_TARGET_UCHARx4,				///< A8R8G8B8
		TF_TARGET_RGB10BIT,				///< A2R10G10B10
		TF_TARGET_FLOAT32x1,			///< fp32-R
		TF_TARGET_FLOAT32x4,			///< fp32-RGBA
		TF_TARGET_FLOAT16x1,			///< fp16-R
		TF_TARGET_FLOAT16x4,			///< fp16-RGBA
		TF_TARGET_UCHARx4_ALPHA,		///< A8R8G8B8    - alpha blending enable
		TF_TARGET_RGB10BIT_ALPHA,		///< A2R10G10B10 - alpha blending enable
		TF_TARGET_FLOAT32x1_ALPHA,		///< fp32-R      - alpha blending enable
		TF_TARGET_FLOAT32x4_ALPHA,		///< fp32-RGBA   - alpha blending enable
		TF_TARGET_FLOAT16x1_ALPHA,		///< fp16-R      - alpha blending enable
		TF_TARGET_FLOAT16x4_ALPHA,		///< fp16-RGBA   - alpha blending enable

		TF_DEPTH_TARGET,				///< DepthBuffer

		TF_MAX,

		TF_INVALID = TF_MAX,
	};

	/**
		@brief �e�N�X�`���ǂݍ��ݗp�p�����[�^�[
		@author �t���`
		@note
		�e�N�X�`���̓ǂݍ��݂Ɏg����p�����[�^�[�ł�
	*/
	struct STextureLoadParameter
	{
		bool IsFromFile;			///< �t�@�C�����炻�̂܂ܓǂݍ��ށi���̃t���O��S�������j
		bool IsCompressFormat;		///< ���k�e�N�X�`���̗L��
		bool IsMipmapEnable;		///< �~�b�v�}�b�v�̗L��
		Sint32 SizeDivide;			///< ���̃T�C�Y�ɑ΂��ď��Z���鐔�i2�Ȃ�256x256������I��128x128�Ő����j
		ColorF ColorKey;			///< �J���[�L�[�𗘗p���Ȃ��ꍇ��(0,0,0,0)
	};

	/**
		@brief �v���~�e�B�u�`����
		@author �t���`
		@note
		DrawPrimitive���̕`��v���~�e�B�u�̎��
	*/
	enum DrawPrimitiveType
	{
		DP_LINE_LIST,				///< ���C�����X�g�`��
		DP_LINE_STRIP,				///< ���C���X�g���b�v�`��
		DP_TRIANGLE_LIST,			///< �O�p�`���X�g�`��
		DP_TRIANGLE_STRIP,			///< �O�p�`�X�g���b�v�`��
	};

	/**
		@brief �f�o�C�X�����p�p�����[�^�[
		@author �t���`
		@note
		�f�o�C�X�𐶐����邽�߂̃p�����[�^�[�N���X�ł�
	*/
	class SDeviceCreationParameter
	{
	private:
		bool		m_IsFullScreen;			///< �t���X�N�[�����N���̗L��
		bool		m_IsWaitVSync;			///< VSync�҂��̗L��
		Point2DI	m_BackBufferSize;		///< �o�b�N�o�b�t�@�T�C�Y
		HWND		m_WindowHandle;			///< �E�B���h�E�n���h��

	public:
		/**
			@brief �R���X�g���N�^
			@author �t���`
		*/
		SDeviceCreationParameter()
			: m_IsFullScreen	( false )
			, m_IsWaitVSync		( true )
			, m_BackBufferSize	( 0, 0 )
			, m_WindowHandle	( 0 )
		{
		}

	public:
		/**
			@brief �E�B���h�E�n���h���ݒ�
			@author �t���`
			@param Handle	[in] �E�B���h�E�n���h��
		*/
		void SetWindowHandle( HWND Handle )
		{
			m_WindowHandle = Handle;
		}

		/**
			@brief �t���`
			@author �t���`
			@param Flag	[in] true�̎�VSync�҂�����
		*/
		void SetWaitVSync( bool Flag )
		{
			m_IsWaitVSync = Flag;
		}

		/**
			@brief �t���X�N���[�����[�h�L���ݒ�
			@author �t���`
			@param Flag	[in] true�̎��t���X�N���[�����[�h�ŋN��
		*/
		void SetFullScreenMode( bool Flag )
		{
			m_IsFullScreen = Flag;
		}

		/**
			@brief �o�b�N�o�b�t�@�̃T�C�Y��ݒ�
			@author �t���`
			@param Size	[in] �o�b�N�o�b�t�@�̃T�C�Y
		*/
		void SetBackbufferSize( const Point2DI &Size )
		{
			m_BackBufferSize = Size;
		}

		/**
			@brief �E�B���h�E�n���h���擾
			@author �t���`
			@return �E�B���h�E�n���h��
		*/
		HWND GetWindowHandle() const
		{
			return m_WindowHandle;
		}

		/**
			@brief VSync�҂��̗L�����擾
			@author �t���`
			@return VSync�҂����s�����̗L��
		*/
		bool GetWaitVSync() const
		{
			return m_IsWaitVSync;
		}

		/**
			@brief �t���X�N���[�����[�h�ŋN�����邩���擾
			@author �t���`
			@return �t���X�N���[�����[�h�ŋN�����邩�̗L��
		*/
		bool GetFullScreenMode() const
		{
			return m_IsFullScreen;
		}

		/**
			@brief �o�b�N�o�b�t�@�̃T�C�Y���擾
			@author �t���`
			@return �o�b�N�o�b�t�@�̃T�C�Y
		*/
		const Point2DI &GetBackbufferSize() const
		{
			return m_BackBufferSize;
		}
	};

	/**
		@brief �`��Ǘ��N���X
		@author �t���`

		�`��̓ǂݍ��ݏ������s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		virtual void* GetDevicePointer() = 0;
		/**
			@brief �O���t�B�b�NAPI�擾
			@author �t���`
			@return �O���t�B�b�NAPI�̎��
			@note
			���݂�GraphicsManager�����p���Ă���API���擾���܂��B
		*/
		virtual eGraphicsAPI GetGraphicsAPI() = 0;
		/**
			@brief �f�B�X�v���C���[�h�̐����擾
			@author �t���`
			@return �f�B�X�v���C���[�h�̐�
			@note
			�A�_�v�^�[���ݒ�\�ȃf�B�X�v���C���[�h�̐����擾���܂��B<BR>
			�E�B���h�E���[�h�̏ꍇ�̓T�C�Y�ɐ����͂���܂���B
		*/
		virtual Sint32 GetDisplayModeCount() const = 0;
		/**
			@brief �f�B�X�v���C���[�h���擾
			@author �t���`
			@param Index	[in]
			@return �f�B�X�v���C���[�h
			@note
			Index�ԖڂɌ��������f�B�X�v���C���[�h���擾���܂��B
		*/
		virtual Point2DI GetDisplayMode( Sint32 Index ) const = 0;
		/**
			@brief �X�N���[�����[�h�̐؂�ւ�
			@author �t���`
			@param IsFullscreen	[in] �X�N���[�����[�h�̐؂�ւ�
			@note
			�X�N���[�����[�h�̐؂�ւ����s���܂��B
		*/
		virtual void ChangeScreenMode( bool IsFullscreen ) = 0;
		/**
			@brief ��ʕ`��J�n
			@author �t���`
			@note
			�����_�����O�������J�n���鎖���h���C�o�[�ɒʒm���܂��B
		*/
		virtual void Begin() = 0;
		/**
			@brief ��ʕ`��I��
			@author �t���`
			@note
			�����_�����O�������I�����������h���C�o�[�ɒʒm���܂��B
		*/
		virtual void End() = 0;
		/**
			@brief �E�B���h�E�Ƀo�b�N�o�b�t�@�̓��e��]��
			@author �t���`
			@return false�̎��f�o�C�X�̕��A�s�\�ȃG���[����
			@note
			�o�b�N�o�b�t�@�ɑ΂��Đ���������ʂ��E�B���h�E�ɓ]�����܂��B
		*/
		virtual bool Present() = 0;
		/**
			@brief �`��^�[�Q�b�g�̃N���A
			@author �t���`
			@param IsClearTarget	[in] �J���[�o�b�t�@���N���A���邩�ۂ�
			@param IsClearDepth		[in] �[�x�o�b�t�@���N���A���邩�ۂ�
			@param Color			[in] �J���[�o�b�t�@�̃N���A�F
			@return false�̎��f�o�C�X�̕��A�s�\�ȃG���[����
			@note
			�o�b�N�o�b�t�@�Ɛ[�x�o�b�t�@���N���A���܂��B
		*/
		virtual void Clear( bool IsClearTarget, bool IsClearDepth, const ColorF& Color ) = 0;
		/**
			@brief �V�F�[�_�[�̑Ή��󋵂��擾
			@author �t���`
			@retval true	�Œ�ł�3.0����̃V�F�[�_�[���T�|�[�g���Ă���
			@retval false	�V�F�[�_�[3.0����T�|�[�g���ĂȂ�
			@note
			���݃f�o�C�X���V�F�[�_�[�ɑΉ����Ă��邩�擾���܂��B
		*/
		virtual bool IsSupportPixelShader() const = 0;
		/**
			@brief �r���[�|�[�g�擾
			@author �t���`
			@return ���݂̃r���[�|�[�g
			@note
			���݃f�o�C�X�ɐݒ肳��Ă���r���[�|�[�g���擾���܂��B
		*/
		virtual RectI GetViewport() const = 0;
		/**
			@brief �r���[�|�[�g�ݒ�
			@author �t���`
			@param Rect	[in] �r���[�|�[�g
			@note
			���݂̃f�o�C�X�Ƀr���[�|�[�g��ݒ肵�܂��B<BR>
			���̃T�C�Y�̓����_�����O�^�[�Q�b�g�Ɏ��܂�傫���łȂ��Ă͂����܂���B
		*/
		virtual void SetViewport( const RectI& Rect ) = 0;
		/**
			@brief �����_�[�X�e�[�g�𕜋A
			@author �t���`
			@note
			���ݓ����I�ɕێ�����Ă���X�e�[�g���ēK�p���܂�
		*/
		virtual void RestoreRenderState() = 0;
		
		/**
			@brief �����_�[�X�e�[�g�𐶐�
			@author �t���`
			@return IRenderState�C���^�[�t�F�C�X
			@note
			�V�K�̃A�N�e�B�u�ȃX�e�[�g�̕����𐶐����܂��B
		*/
		virtual State::IRenderState* CreateRenderState() = 0;
		/**
			@brief �����_�[�X�e�[�g���擾
			@author �t���`
			@return IRenderState�C���^�[�t�F�C�X
			@note
			���݃A�N�e�B�u�ȃX�e�[�g���擾���܂��B
		*/
		virtual State::IRenderState* GetRenderState() = 0;
		/**
			@brief �����_�[�X�e�[�g��ݒ�
			@author �t���`
			@param pState	[in] IRenderState�C���^�[�t�F�C�X
			@note
			���݃A�N�e�B�u�ȃX�e�[�g�ɐݒ肵�܂��B
		*/
		virtual void SetRenderState( State::IRenderState* pState ) = 0;
		/**
			@brief �����_�[�X�e�[�g���X�^�b�N��Push
			@author �t���`
			@note
			�X�e�[�g�̊K�w���P�iPush���܂��B
		*/
		virtual void PushRenderState() = 0;
		/**
			@brief �����_�[�X�e�[�g���X�^�b�N����Pop
			@author �t���`
			@note
			�X�e�[�g�̊K�w���P�iPop���܂��B
		*/
		virtual void PopRenderState() = 0;
		/**
			@brief �����_�[�X�e�[�g���h���C�o�[�ɒ蒅
			@author �t���`
			@note
			���ۂɃX�e�[�g�̓��e���h���C�o�[�ɒ蒅�����܂��B
		*/
		virtual void UpdateRenderState() = 0;
		/**
			@brief �N���b�v�̈�ݒ�
			@author �t���`
			@param ScissorRect	[in] �N���b�v�̈�
			@note
			�`�掞�̃X�N���[����Ԃł̃N���b�v�̈��ݒ肵�܂��B
		*/
		virtual void SetScissorRect( const RectI& ScissorRect ) = 0;

		virtual Kernel::Math::Matrix CreateScreenTransformMatrix() const = 0;

		/**
			@brief Antialias�\�e�N�X�`���`�F�b�N
			@author �t���`
			@retval true	Antialias�\
			@retval false	Antialias�s�\
			@note
			�����_�����O�^�[�Q�b�g��Antialias�\�����ׂ܂��B
		*/
		virtual bool IsMultiSampleRenderTargetEnable( eTextureFormat Format ) = 0;
		/**
			@brief �F�}�X�N�ݒ�
			@author �t���`
			@param pPlane	[in] �N���b�s���O�p����
			@note
			�f�o�C�X�ɃN���b�s���O�p���ʂ��Z�b�g���܂��B
		*/
		virtual void SetStateEffectRenderingForWater( bool IsEnable ) = 0;

		/**
			@brief �e�N�X�`���`�F�b�N
			@author �t���`
			@retval true	�\
			@retval false	�s�\
			@note
			�����_�����O�^�[�Q�b�g���\�����ׂ܂��B
		*/
		virtual bool IsRenderTargetEnable( eTextureFormat Format ) = 0;

		/**
			@brief ���_�e�N�X�`���\�e�N�X�`���`�F�b�N
			@author �t���`
			@retval true	���_�e�N�X�`���\
			@retval false	���_�e�N�X�`���s�\
			@note
			�����_�����O�^�[�Q�b�g�����_�e�N�X�`���\�����ׂ܂��B
		*/
		virtual bool IsVertexTextureEnable( eTextureFormat Format ) = 0;

		/**
			@brief �e�L�X�g�����_���[����
			@author �t���`
			@param pFontName	[in] �t�H���g��
			@param FontSize		[in] �t�H���g�T�C�Y
			@param IsBold		[in] ����On/Off
			@param IsItalic		[in] �Α�On/Off
			@return ITextRenderer�C���^�[�t�F�C�X
			@note
			�e�L�X�g�`��p�̃C���^�[�t�F�C�X���擾���܂��B
		*/
		virtual Simple::ITextRenderer* CreateTextRenderer( const wchar_t* pFontName, Sint32 FontSize, bool IsBold, bool IsItalic ) = 0;
		/**
			@brief �X�v���C�g�����_���[����
			@author �t���`
			@param SpriteSortMode	[in] �\�[�g�̃��[�h
			@return ISpriteRenderer�C���^�[�t�F�C�X
			@note
			2D��ʕ`��p�̃C���^�[�t�F�C�X���擾���܂��B
		*/
		virtual Simple::ISpriteRenderer* CreateSpriteRenderer() = 0;
		/**
			@brief 3D�X�v���C�g�����_���[����
			@author �t���`
			@return ISpriteRenderer3D�C���^�[�t�F�C�X
			@note
			3D��ʕ`��p�̃C���^�[�t�F�C�X���擾���܂��B
		*/
		virtual Simple::ISpriteRenderer3D* CreateSpriteRenderer3D() = 0;
		/**
			@brief ���C�������_���[����
			@author �t���`
			@return ILineRenderer�C���^�[�t�F�C�X
			@note
			���C���`��p�̃C���^�[�t�F�C�X���擾���܂��B
		*/
		virtual Simple::ILineRenderer* CreateLineRenderer() = 0;
		/**
			@brief �g���C�A���O�������_���[����
			@author �t���`
			@return ITriangleRenderer�C���^�[�t�F�C�X
			@note
			�g���C�A���O���`��p�̃C���^�[�t�F�C�X���擾���܂��B
		*/
		virtual Simple::ITriangleRenderer* CreateTriangleRenderer() = 0;
		/**
			@brief ���_�V�F�[�_�[����
			@author �t���`
			@param pBuffer			[in] ���\�[�X�̃o�b�t�@�̃|�C���^
			@param Size				[in] ���\�[�X�̃T�C�Y
			@param Line				[in] ���������\�[�X�̍s
			@param pSourceFile		[in] ���������\�[�X�̃t�@�C����
			@return IShader�C���^�[�t�F�C�X
			@note
			�R���p�C���ςݒ��_�V�F�[�_�[����C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IVertexShader* CreateVertexShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �s�N�Z���V�F�[�_�[����
			@author �t���`
			@param pBuffer			[in] ���\�[�X�̃o�b�t�@�̃|�C���^
			@param Size				[in] ���\�[�X�̃T�C�Y
			@param Line				[in] ���������\�[�X�̍s
			@param pSourceFile		[in] ���������\�[�X�̃t�@�C����
			@return IShader�C���^�[�t�F�C�X
			@note
			�R���p�C���ς݃s�N�Z���V�F�[�_�[����C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IPixelShader* CreatePixelShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �e�N�X�`������
			@author �t���`
			@param Size				[in] �e�N�X�`���̃T�C�Y
			@param IsFloat			[in] ���������_���ۂ��itrue=float32x4, false=uint8x4�j
			@param IsSystemMemory	[in] �V�X�e���������Ƀo�b�N�A�b�v��ێ����邩�ۂ�
			@param Line				[in] ���������\�[�X�̍s
			@param pSourceFile		[in] ���������\�[�X�̃t�@�C����
			@return ITexture�C���^�[�t�F�C�X
			@note
			CPU����A�N�Z�X�\�ȋ�̃e�N�X�`���𐶐����܂��B<BR>
			�uIsSystemMemory = true�v�̏ꍇ�͓����ŕێ����Ă���o�b�N�A�b�v�̃V�X�e���������̃A�h���X��Ԃ��܂��B<BR>
			Unlock()���R�[�����ꂽ���_��VRAM�ւ̓]�����s����悤�ɂȂ��Ă��܂��B
		*/
		virtual Resource::ITexture* CreateCpuAccessTexture( const Point2DI& Size, bool IsFloat, bool IsSystemMemory, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �e�N�X�`������
			@author �t���`
			@param pBuffer			[in] ���\�[�X�̃o�b�t�@�̃|�C���^
			@param Size				[in] ���\�[�X�̃T�C�Y
			@param pResourceName	[in] ���ꃊ�\�[�X�����p�̃��\�[�X��
			@param Param			[in] �e�N�X�`�������p�̃p�����[�^�[
			@return ITexture�C���^�[�t�F�C�X
			@note
			�摜�t�@�C������e�N�X�`���C���^�[�t�F�C�X�𐶐����܂��B<BR>
			TGA/BMP/JPG/PNG/DDS�t�@�C����ǂݍ��ނ��Ƃ��ł��܂��B
		*/
		virtual Resource::ITexture* CreateTexture( const void* pBuffer, Sint32 Size, const wchar_t* pResourceName, const STextureLoadParameter& Param ) = 0;
		/**
			@brief �L���[�u�e�N�X�`������
			@author �t���`
			@param pBuffer			[in] ���\�[�X�̃o�b�t�@�̃|�C���^
			@param Size				[in] ���\�[�X�̃T�C�Y
			@param pResourceName	[in] ���ꃊ�\�[�X�����p�̃��\�[�X��
			@param Param			[in] �e�N�X�`�������p�̃p�����[�^�[
			@return ITexture�C���^�[�t�F�C�X
			@note
			�摜�t�@�C������e�N�X�`���C���^�[�t�F�C�X�𐶐����܂��B<BR>
			BMP/JPG/PNG/DDS�t�@�C����ǂݍ��ނ��Ƃ��ł��܂��B<BR>
			�\�Ȍ���DDS�t�@�C���̗��p�𐄏����܂��B
		*/
		virtual Resource::ITexture* CreateCubeTexture( const void* pBuffer, Sint32 Size, const wchar_t* pResourceName, const STextureLoadParameter& Param ) = 0;
		/**
			@brief �[�x�o�b�t�@�e�N�X�`������
			@author �t���`
			@param Size			[in] ���\�[�X�̃T�C�Y
			@param DepthFormat	[in] �[�x�o�b�t�@�t�H�[�}�b�g
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return ITexture�C���^�[�t�F�C�X
			@note
			�[�x�o�b�t�@�p�̃e�N�X�`���C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::ITexture* CreateDepthTexture( const Point2DI& Size, eTextureFormat DepthFormat, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �`��^�[�Q�b�g�e�N�X�`������
			@author �t���`
			@param Size			[in] ���\�[�X�̃T�C�Y
			@param Format		[in] ��������^�[�Q�b�g�̃t�H�[�}�b�g
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return ITexture�C���^�[�t�F�C�X
			@note
			�`��^�[�Q�b�g�p�̃e�N�X�`���C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::ITexture* CreateTargetTexture( const Point2DI& Size, eTextureFormat Format, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �}���`�T���v�����O�Ή��`��^�[�Q�b�g�e�N�X�`������
			@author �t���`
			@param Size			[in] ���\�[�X�̃T�C�Y
			@param TargetFormat	[in] ��������`��^�[�Q�b�g�̃t�H�[�}�b�g
			@param pTarget		[out] �`��^�[�Q�b�g�C���^�[�t�F�C�X�i�[��
			@param DepthFormat	[in] ��������[�x�^�[�Q�b�g�̃t�H�[�}�b�g
			@param pDepth		[out] �[�x�^�[�Q�b�g�C���^�[�t�F�C�X�i�[��
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return ITexture�C���^�[�t�F�C�X
			@note
			�`��^�[�Q�b�g�p�̃e�N�X�`���C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual bool CreateRenderTargetWithAntialias( const Point2DI& Size, eTextureFormat TargetFormat, Resource::ITexture*& pTarget, eTextureFormat DepthFormat, Resource::ITexture*& pDepth, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ���_���C�A�E�g����
			@author �t���`
			@param LayoutTable	[in] ���C�A�E�g����`����Ă���e�[�u���i�I�[�ɂ�StreamNo��-1�����Ă����Ă��������j
			@param pData		[in] ���_�V�F�[�_�[�o�C�i��
			@param Size			[in] ���_�V�F�[�_�[�T�C�Y
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@note
			���_�\���̂̒�`�ƃV�F�[�_�[���֘A�t����ׂ̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IVertexLayout* CreateVertexLayout( const Graphics::Resource::SVertexLayoutTable LayoutTable[], const void* pData, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ���_���C�A�E�g����
			@author �t���`
			@param LayoutTable	[in] ���C�A�E�g����`����Ă���e�[�u���i�I�[�ɂ�StreamNo��-1�����Ă����Ă��������j
			@param pShader		[in] �`�F�b�N���钸�_�t�H�[�}�b�g�̓��������_�V�F�[�_�[
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@note
			���_�\���̂̒�`�ƃV�F�[�_�[���֘A�t����ׂ̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IVertexLayout* CreateVertexLayout( const Resource::SVertexLayoutTable LayoutTable[], Graphics::Resource::IVertexShader* pShader, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ���_�o�b�t�@����
			@author �t���`
			@param VertexSize	[in] ���_�̂P�v�f�̃T�C�Y
			@param VertexCount	[in] ���_��
			@param IsDynamic	[in] ���I�����t���O
			@param pInitialize	[in] �o�b�t�@�������p�f�[�^
			@param IsAutoResize	[in] �����T�C�Y�g��
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return IVertexBuffer�C���^�[�t�F�C�X
			@note
			���_�\���̂̎��f�[�^���i�[����ׂ̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IVertexBuffer* CreateVertexBuffer( Sint32 VertexSize, Sint32 VertexCount, bool IsDynamic, const void* pInitialize, bool IsAutoResize, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief ���_�C���f�b�N�X����
			@author �t���`
			@param Is32Bit		[in] 32Bit�̃C���f�b�N�X�𗘗p���邩�ۂ�
			@param IndexCount	[in] ���_�C���f�b�N�X��
			@param IsDynamic	[in] ���I�����t���O
			@param pInitialize	[in] �C���f�b�N�X�������p�f�[�^
			@param IsAutoResize	[in] �����T�C�Y�g��
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return IIndexBuffer�C���^�[�t�F�C�X
			@note
			���_�\���̂̎��f�[�^���i�[����ׂ̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IIndexBuffer* CreateIndexBuffer( bool Is32Bit, Sint32 IndexCount, bool IsDynamic, const void* pInitialize, bool IsAutoResize, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �v���~�e�B�u�`��
			@author �t���`
			@param Type			[in] �`��^�C�v
			@param VertexStart	[in] ���_�̊J�n�ʒu
			@param VertexCount	[in] ���_�̐�
			@note
			�ݒ肳�ꂽ���ƈ��������ɂ��ĕ`��^�[�Q�b�g�Ƀ|���S���̕`����s���܂��B
		*/
		virtual void DrawPrimitive( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount ) = 0;
		/**
			@brief �v���~�e�B�u�`��
			@author �t���`
			@param Type				[in] �`��^�C�v
			@param VertexStart		[in] ���_�̊J�n�ʒu
			@param VertexCount		[in] ���_�̐�
			@param IndexStart		[in] �C���f�b�N�X�̊J�n�ʒu
			@param IndexCount		[in] �C���f�b�N�X�̐�
			@note
			�ݒ肳�ꂽ���ƈ��������ɂ��ĕ`��^�[�Q�b�g�Ƀ|���S���̕`����s���܂��B
		*/
		virtual void DrawPrimitiveIndex( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 IndexCount ) = 0;
		/**
			@brief �v���~�e�B�u�`��
			@author �t���`
			@param Type			[in] �`��^�C�v
			@param VertexStart	[in] ���_�̊J�n�ʒu
			@param VertexCount	[in] ���_�̐�
			@param InstanceCount	[in] �C���X�^���X��
			@note
			�ݒ肳�ꂽ���ƈ��������ɂ��ĕ`��^�[�Q�b�g�Ƀ|���S���̕`����s���܂��B
		*/
		virtual void DrawPrimitiveInstance( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount, Uint32 InstanceCount ) = 0;
		/**
			@brief �v���~�e�B�u�`��
			@author �t���`
			@param Type				[in] �`��^�C�v
			@param VertexStart		[in] ���_�̊J�n�ʒu
			@param VertexCount		[in] ���_�̐�
			@param IndexStart		[in] �C���f�b�N�X�̊J�n�ʒu
			@param IndexCount		[in] �C���f�b�N�X�̐�
			@param InstanceCount	[in] �C���X�^���X��
			@note
			�ݒ肳�ꂽ���ƈ��������ɂ��ĕ`��^�[�Q�b�g�Ƀ|���S���̕`����s���܂��B
		*/
		virtual void DrawPrimitiveIndexInstance( DrawPrimitiveType Type, Sint32 VertexStart, Sint32 VertexCount, Sint32 IndexStart, Sint32 IndexCount, Uint32 InstanceCount ) = 0;
		/**
			@brief �`��^�[�Q�b�g�ݒ�
			@author �t���`
			@param pTargetTexture1	[in] �`��p�`��^�[�Q�b�g
			@param pTargetTexture2	[in] �`��p�`��^�[�Q�b�g
			@param pTargetTexture3	[in] �`��p�`��^�[�Q�b�g
			@param pTargetTexture4	[in] �`��p�`��^�[�Q�b�g
			@param pDepthTexture	[in] �`��p�[�x�o�b�t�@
			@param IsAntialias			[in] Antialias(�A���`�G�C���A�X)������ON�ɂ��邩�ǂ���
			@note
			�`��ɗ��p����`��^�[�Q�b�g�e�N�X�`���C���^�[�t�F�C�X��ݒ肵�܂��B<BR>
			IsAntialias��ON�ɂ���ɂ�CreateRenderTargetWithAntialias()�Ő��������o�b�t�@�̕K�v������܂��B
		*/
		virtual void SetRenderTarget( Resource::ITexture* pTargetTexture1, Resource::ITexture* pTargetTexture2, Resource::ITexture* pTargetTexture3, Resource::ITexture* pTargetTexture4, Resource::ITexture* pDepthTexture, bool IsAntialias ) = 0;
		/**
			@brief ���_���C�A�E�g�ݒ�
			@author �t���`
			@param pVertexLayout	[in] �`��p���_���C�A�E�g
			@note
			�`��ɗ��p���钸�_�f�[�^�̃��C�A�E�g����`���ꂽ�C���^�[�t�F�C�X��ݒ肵�܂��B
		*/
		virtual void SetVertexLayout( Resource::IVertexLayout* pVertexLayout ) = 0;
		/**
			@brief ���_�o�b�t�@�ݒ�
			@author �t���`
			@param pBuffer				[in] �`��p���_�o�b�t�@
			@note
			�`��ɗ��p���钸�_�f�[�^�̃o�b�t�@����`���ꂽ�C���^�[�t�F�C�X��ݒ肵�܂��B
		*/
		virtual void SetVertexBuffer( Resource::IVertexBuffer* pBuffer ) = 0;
		/**
			@brief ���_�C���f�b�N�X�ݒ�
			@author �t���`
			@param pBuffer			[in] �`��p���_�C���f�b�N�X
			@note
			�`��ɗ��p���钸�_�f�[�^�̃C���f�b�N�X����`���ꂽ�C���^�[�t�F�C�X��ݒ肵�܂��B
		*/
		virtual void SetIndexBuffer( Resource::IIndexBuffer* pBuffer ) = 0;
		/**
			@brief ���_�V�F�[�_�[�ݒ�
			@author �t���`
			@param pShader	[in] �V�F�[�_�[
			@note
			�f�o�C�X�ɒ��_�V�F�[�_�[���Z�b�g���܂��B
		*/
		virtual void SetVertexShader( Resource::IVertexShader* pShader ) = 0;
		/**
			@brief �s�N�Z���V�F�[�_�[�ݒ�
			@author �t���`
			@param pShader	[in] �V�F�[�_�[
			@note
			�f�o�C�X�Ƀs�N�Z���V�F�[�_�[���Z�b�g���܂��B
		*/
		virtual void SetPixelShader( Resource::IPixelShader* pShader ) = 0;
		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param State	[in] �X�e�[�W
			@param pTexture	[in] �e�N�X�`��
			@param IsFilter	[in] �t�B���^ON/OFF
			@param IsWrap	[in] ���b�s���OON/OFF
			@note
			�f�o�C�X�Ƀe�N�X�`�����Z�b�g���܂��B
		*/
		virtual void SetTexture( Uint32 Stage, Resource::ITexture* pTexture, eTextureFilter Filter, bool IsWrap ) = 0;
		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param State	[in] �X�e�[�W
			@param pTexture	[in] �e�N�X�`��
			@note
			�f�o�C�X�Ƀe�N�X�`�����Z�b�g���܂��B
		*/
		virtual void SetVertexTexture( Uint32 Stage, Resource::ITexture* pTexture ) = 0;
		/**
			@brief �`�搔���擾
			@author �t���`
			@note
			���ۂɕ`�悪�R�[�����ꂽ�񐔂��擾���܂��B
		*/
		virtual Uint32 GetDrawPrimitiveCount() = 0;

		/**
			@brief �`��|���S�������擾
			@author �t���`
			@note
			���ۂɕ`�悵���|���S�������擾���܂��B
		*/
		virtual Uint32 GetDrawPolygonCount() = 0;

		/**
			@brief ��ʂ��摜�ŕۑ�
			@author �t���`
			@param pFileName	[in] �t�@�C����
			@note
			���݂̉�ʂ̓��e���摜�ŕۑ����܂��B
		*/
		virtual void SaveScreen( const wchar_t* pFileName ) = 0;

		/**
			@brief �`��^�[�Q�b�g����
			@author �t���`
			@param pTextureDst	[in] �]����^�[�Q�b�g�e�N�X�`��
			@param pTextureSrc	[in] �]�����^�[�Q�b�g�e�N�X�`��
			@note
			�`��^�[�Q�b�g�̓��e��ʂ̕`��^�[�Q�b�g�ɕ������܂��B
		*/
		virtual void MultSampleTargetDownSampling( Resource::ITexture* pTextureDst, Resource::ITexture* pTextureSrc ) = 0;

		/**
			@brief �}�e���A�����X�i�[�̓o�^
			@author �t���`
			@param pPluginName	[in] �v���O�C����
			@param pListener	[in] ���X�i�[
			@note
			�}�e���A���ǂݍ��ݎ��Ɍ�������}�e���A�����X�i�[��o�^���܂��B
		*/
		virtual void RegistMaterialListener( const char* pPluginName, Resource::IMaterialListener* pListener ) = 0;
		/**
			@brief �}�e���A�����X�i�[�̍폜
			@author �t���`
			@param pPluginName	[in] �v���O�C����
			@note
			�}�e���A���ǂݍ��ݎ��Ɍ�������}�e���A�����X�i�[���폜���܂��B
		*/
		virtual void UnRegistMaterialListener( const char* pPluginName ) = 0;
		/**
			@brief �}�e���A�����X�i�[�̎擾
			@author �t���`
			@param pPluginName	[in] �v���O�C����
			@note
			�v���O�C���ɑΉ������}�e���A�����X�i�[���擾���܂��B
		*/
		virtual Resource::IMaterialListener* GetMaterialListener( const char* pPluginName ) = 0;

		/**
			@brief ���f������
			@author �t���`
			@param pData		[in] �f�[�^�̃|�C���^
			@param Size			[in] �f�[�^�̃T�C�Y
			@param pFileName	[in] �f�[�^��
			@note
			Amaryllis�ō쐬�\��SMF�t�@�C�����烂�f���f�[�^�̐������s���܂��B
		*/
		virtual Resource::SMF::IModel* CreateModel( const void* pData, Uint32 Size, const wchar_t* pFileName ) = 0;
		/**
			@brief ���f������
			@author �t���`
			@param pData		[in] �f�[�^�̃|�C���^
			@param Size			[in] �f�[�^�̃T�C�Y
			@param pFileName	[in] �f�[�^��
			@note
			Almeria�ō쐬�\��STM�t�@�C�����烂�f���f�[�^�̐������s���܂��B
		*/
		virtual Resource::STM::IModelController* CreateMap( const void* pData, Uint32 Size, const wchar_t* pFileName ) = 0;
		/**
			@brief �e�L�X�g����
			@author �t���`
			@param pData		[in] �f�[�^�̃|�C���^
			@param Size			[in] �f�[�^�̃T�C�Y
			@param pFileName	[in] �f�[�^��
			@param Param		[in] �e�N�X�`�������p�p�����[�^�[
			@param pListener	[in] �t�@�C���ǂݍ��݃C�x���g���X�i�[
			@param pUserSetData	[in] ���X�i�[��n���p���[�U�[�|�C���^�[
			@note
			Liatris�ō쐬�\��SFF�t�@�C������e�L�X�g�f�[�^�̐������s���܂��B
		*/
		virtual Resource::Text::ITextData* CreateText( const void* pData, Uint32 Size, const wchar_t* pFileName, const STextureLoadParameter& Param, Resource::IFileLoadListener* pListener, void* pUserSetData = NULL ) = 0;
		/**
			@brief ���[�ƃ��[�V�����C���^�[�t�F�C�X�擾
			@author �t���`
			@param pData		[in] �f�[�^�̃|�C���^
			@param Size			[in] �f�[�^�̃T�C�Y
			@note
			���[�g���[�V�����f�[�^��saf�t�@�C�����琶�����܂��B
		*/
		virtual Resource::IRootMotion* CreateRootMotion( const void* pData, Uint32 Size ) = 0;

		/**
			@brief �v���~�e�B�u����
			@author �t���`
			@param VertexCount	[in] ���_��
			@param IndexCount	[in] ���_�C���f�b�N�X��
			@param Param		[in] �v���~�e�B�u�p�p�����[�^�[
			@note
			�v���O������ŊȈՂȃ��f���f�[�^�̍쐬���s�����߂̃C���^�[�t�F�C�X�ł��B<BR>
			SMF���f���Ɠ����悤�Ƀ{�[����}�e���A�����K�p�ł��܂��B
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitive( Sint32 VertexCount, Sint32 IndexCount, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief ���`��v���~�e�B�u����
			@author �t���`
			@param Size		[in] ���̃T�C�Y�i���a�j
			@param Param	[in] �v���~�e�B�u�p�p�����[�^�[
			@note
			Resource::Primitive::IPrimitiveController�𗘗p���ċ��`��̃v���~�e�B�u�𐶐����܂��B
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveSphere( const Kernel::Math::Vector3& Size, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief ���`��v���~�e�B�u����
			@author �t���`
			@param Size		[in] ���̃T�C�Y�i�R�Ӂj
			@param Param	[in] �v���~�e�B�u�p�p�����[�^�[
			@note
			Resource::Primitive::IPrimitiveController�𗘗p���Ĕ��`��̃v���~�e�B�u�𐶐����܂��B
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveCube( const Kernel::Math::Vector3& Size, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief �J�v�Z���`��v���~�e�B�u����
			@author �t���`
			@param Radius	[in] �J�v�Z���̃T�C�Y�i���a�j
			@param Length	[in] �J�v�Z���̒���
			@param Param	[in] �v���~�e�B�u�p�p�����[�^�[
			@note
			Resource::Primitive::IPrimitiveController�𗘗p���ăJ�v�Z���`��̃v���~�e�B�u�𐶐����܂��B
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveCapsule( float Radius, float Length, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief ���ʌ`��v���~�e�B�u����
			@author �t���`
			@param Size		[in] ���ʂ̃T�C�Y�i���a�j
			@param Param	[in] �v���~�e�B�u�p�p�����[�^�[
			@note
			Resource::Primitive::IPrimitiveController�𗘗p���ĕ��ʌ`��̃v���~�e�B�u�𐶐����܂��B
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitivePlane( const Kernel::Math::Vector2& Size, const Resource::Primitive::SParameter& Param ) = 0;
		/**
			@brief ���`��v���~�e�B�u����
			@author �t���`
			@param Size			[in] ���̃T�C�Y�i���a�j
			@param CellCount	[in] ���̃Z����
			@param Param		[in] �v���~�e�B�u�p�p�����[�^�[
			@note
			Resource::Primitive::IPrimitiveController�𗘗p���ď��`��̃v���~�e�B�u�𐶐����܂��B
		*/
		virtual Resource::Primitive::IPrimitiveController* CreatePrimitiveFloor( const Kernel::Math::Vector2& Size, Sint32 CellCount, const Resource::Primitive::SParameter& Param ) = 0;

		/**
			@brief �p�[�e�B�N������
			@author �t���`
			@param Count	[in] �p�[�e�B�N����
			@param Param	[in] �p�[�e�B�N���p�p�����[�^�[
			@note
			�r���{�[�h�ɂ��\�������p�[�e�B�N���̐������s���܂��B<BR>
			�P���ȃr���{�[�h�Ƃ��Ẳ^�p���ł��A�\�t�g�p�[�e�B�N���������s�������o���܂��B
		*/
		virtual Resource::Particle::IParticleController* CreateParticle( Sint32 Count, const Resource::Particle::SParameter& Param ) = 0;
		/**
			@brief �p�[�e�B�N������
			@author �t���`
			@param Count	[in] �p�[�e�B�N����
			@param Param	[in] �p�[�e�B�N���p�p�����[�^�[
			@note
			�r���{�[�h�ɂ��\�������p�[�e�B�N���̐������s���܂��B<BR>
			�P���ȃr���{�[�h�Ƃ��Ẳ^�p���ł��A�\�t�g�p�[�e�B�N���������s�������o���܂��B
		*/
		virtual Graphics::Resource::Particle::IVolumeParticleController* CreateVolumeParticle( Sint32 Count, const Graphics::Resource::Particle::SParameter& Param ) = 0;
		/**
			@brief �p�[�e�B�N������
			@author �t���`
			@param Count	[in] �p�[�e�B�N����
			@param Param	[in] �p�[�e�B�N���p�p�����[�^�[
			@note
			�r���{�[�h�ɂ��\�������p�[�e�B�N���̐������s���܂��B<BR>
			�P���ȃr���{�[�h�Ƃ��Ẳ^�p���ł��A�\�t�g�p�[�e�B�N���������s�������o���܂��B
		*/
		virtual Graphics::Resource::Particle::IEnhancedParticleController* CreateEnhancedParticle( Sint32 Count, const Graphics::Resource::Particle::SParameter& Param ) = 0;
		/**
			@brief �X�v���C�g����
			@author �t���`
			@param Count	[in] �X�v���C�g��
			@param Param	[in] �X�v���C�g�p�p�����[�^�[
			@note
			3D�X�v���C�g�̐������s���܂��B<BR>
			3D�X�v���C�g�͎l�p�n�݂̂̕`����s�������ł��܂��B
		*/
		virtual Resource::Sprite::ISpriteController* CreateSprite( Sint32 Count, const Resource::Sprite::SParameter& Param ) = 0;
		/**
			@brief �|�����C������
			@author �t���`
			@param VertexCount	[in] ���_��
			@param IndexCount	[in] ���_�C���f�b�N�X��
			@param Param		[in] �|�����C���p�p�����[�^�[
			@note
			�|���S�����Ȃ��đ��������������C����\������ׂ̃|�����C���̐������s���܂��B
		*/
		virtual Resource::PolyLine::IPolyLineController* CreatePolyLine( Sint32 VertexCount, Sint32 IndexCount, const Resource::PolyLine::SParameter& Param ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@����
			@author �t���`
			@param Size			[in] �o�b�t�@�̃T�C�Y
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return IShader�C���^�[�t�F�C�X
			@note
			�V�F�[�_�[�萔�o�b�t�@�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IShaderConstantBuffer* D3D10_CreateShaderConstantBuffer( Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@�ݒ�
			@author �t���`
			@param Slot		[in] �X���b�g
			@param pBuffer	[in] �o�b�t�@
			@note
			�f�o�C�X�ɃV�F�[�_�[�萔�o�b�t�@���Z�b�g���܂��B
		*/
		virtual void D3D10_SetVertexShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@�ݒ�
			@author �t���`
			@param Slot		[in] �X���b�g
			@param pBuffer	[in] �o�b�t�@
			@note
			�f�o�C�X�ɃV�F�[�_�[�萔�o�b�t�@���Z�b�g���܂��B
		*/
		virtual void D3D10_SetGeometryShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@�ݒ�
			@author �t���`
			@param Slot		[in] �X���b�g
			@param pBuffer	[in] �o�b�t�@
			@note
			�f�o�C�X�ɃV�F�[�_�[�萔�o�b�t�@���Z�b�g���܂��B
		*/
		virtual void D3D10_SetPixelShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param State	[in] �X�e�[�W
			@param pTexture	[in] �e�N�X�`��
			@note
			�f�o�C�X�Ƀe�N�X�`�����Z�b�g���܂��B
		*/
		virtual void D3D10_SetShadowTexture( Uint32 Stage, Resource::ITexture* pTexture ) = 0;
		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param pTexture		[in] �e�N�X�`��
			@note
			�f�o�C�X�Ƀe�N�X�`�����Z�b�g���܂��B
		*/
		virtual void D3D10_SetShadowRenderTarget( Resource::ITexture* pTexture ) = 0;
		/**
			@brief �W�I���g���V�F�[�_�[����
			@author �t���`
			@param pBuffer			[in] ���\�[�X�̃o�b�t�@�̃|�C���^
			@param Size				[in] ���\�[�X�̃T�C�Y
			@param Line				[in] ���������\�[�X�̍s
			@param pSourceFile		[in] ���������\�[�X�̃t�@�C����
			@return IShader�C���^�[�t�F�C�X
			@note
			�R���p�C���ς݃W�I���g���V�F�[�_�[����C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IGeometryShader* D3D10_CreateGeometryShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �W�I���g���V�F�[�_�[�ݒ�
			@author �t���`
			@param pShader	[in] �V�F�[�_�[
			@note
			�f�o�C�X�ɃW�I���g���V�F�[�_�[���Z�b�g���܂��B
		*/
		virtual void D3D10_SetGeometryShader( Resource::IGeometryShader* pShader ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@����
			@author �t���`
			@param Size			[in] �o�b�t�@�̃T�C�Y
			@param Line			[in] ���������\�[�X�̍s
			@param pSourceFile	[in] ���������\�[�X�̃t�@�C����
			@return IShader�C���^�[�t�F�C�X
			@note
			�V�F�[�_�[�萔�o�b�t�@�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IShaderConstantBuffer* D3D11_CreateShaderConstantBuffer( Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@�ݒ�
			@author �t���`
			@param Slot		[in] �X���b�g
			@param pBuffer	[in] �o�b�t�@
			@note
			�f�o�C�X�ɃV�F�[�_�[�萔�o�b�t�@���Z�b�g���܂��B
		*/
		virtual void D3D11_SetVertexShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@�ݒ�
			@author �t���`
			@param Slot		[in] �X���b�g
			@param pBuffer	[in] �o�b�t�@
			@note
			�f�o�C�X�ɃV�F�[�_�[�萔�o�b�t�@���Z�b�g���܂��B
		*/
		virtual void D3D11_SetGeometryShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief �V�F�[�_�[�萔�o�b�t�@�ݒ�
			@author �t���`
			@param Slot		[in] �X���b�g
			@param pBuffer	[in] �o�b�t�@
			@note
			�f�o�C�X�ɃV�F�[�_�[�萔�o�b�t�@���Z�b�g���܂��B
		*/
		virtual void D3D11_SetPixelShaderConstantBuffer( Uint32 Slot, Resource::IShaderConstantBuffer* pBuffer ) = 0;
		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param State	[in] �X�e�[�W
			@param pTexture	[in] �e�N�X�`��
			@note
			�f�o�C�X�Ƀe�N�X�`�����Z�b�g���܂��B
		*/
		virtual void D3D11_SetShadowTexture( Uint32 Stage, Resource::ITexture* pTexture ) = 0;
		/**
			@brief �e�N�X�`���ݒ�
			@author �t���`
			@param pTexture		[in] �e�N�X�`��
			@note
			�f�o�C�X�Ƀe�N�X�`�����Z�b�g���܂��B
		*/
		virtual void D3D11_SetShadowRenderTarget( Resource::ITexture* pTexture ) = 0;
		/**
			@brief �W�I���g���V�F�[�_�[����
			@author �t���`
			@param pBuffer			[in] ���\�[�X�̃o�b�t�@�̃|�C���^
			@param Size				[in] ���\�[�X�̃T�C�Y
			@param Line				[in] ���������\�[�X�̍s
			@param pSourceFile		[in] ���������\�[�X�̃t�@�C����
			@return IShader�C���^�[�t�F�C�X
			@note
			�R���p�C���ς݃W�I���g���V�F�[�_�[����C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Resource::IGeometryShader* D3D11_CreateGeometryShader( const void* pBuffer, Uint32 Size, Uint32 Line = 0, const wchar_t* pSourceFile = L"NODATA" ) = 0;
		/**
			@brief �W�I���g���V�F�[�_�[�ݒ�
			@author �t���`
			@param pShader	[in] �V�F�[�_�[
			@note
			�f�o�C�X�ɃW�I���g���V�F�[�_�[���Z�b�g���܂��B
		*/
		virtual void D3D11_SetGeometryShader( Resource::IGeometryShader* pShader ) = 0;
		/**
			@brief ���_�V�F�[�_�[�萔�ݒ�
			@author �t���`
			@param Register		[in] ���W�X�^�ԍ�
			@param pVector		[in] �x�N�g��
			@param Count		[in] �x�N�g����
			@note
			�f�o�C�X�ɒ��_�V�F�[�_�[�p�萔���Z�b�g���܂��B
		*/
		virtual void D3D9_SetVertexShaderConstant( Uint32 Register, const Kernel::Math::VectorS* pVector, Uint32 Count ) = 0;
		/**
			@brief �s�N�Z���V�F�[�_�[�萔�ݒ�
			@author �t���`
			@param Register		[in] ���W�X�^�ԍ�
			@param pVector		[in] �x�N�g��
			@param Count		[in] �x�N�g����
			@note
			�f�o�C�X�Ƀs�N�Z���V�F�[�_�[�p�萔���Z�b�g���܂��B
		*/
		virtual void D3D9_SetPixelShaderConstant( Uint32 Register, const Kernel::Math::VectorS* pVector, Uint32 Count ) = 0;
		/**
			@brief �Œ�O���t�B�b�N�X�p�C�v���C�����[�h
			@author �t���`
			@param IsEnable		[in] ON/OFF
			@param IsFogEnable	[in] �t�H�O��ON/OFF
			@param FogColor		[in] �t�H�O�F
			@note
			DirectX9�ł̂ݗ��p�\�ȌŒ�p�C�v���C�����[�h�̐ݒ�����܂��B
		*/
		virtual void D3D9_SetFixedRenderingPiplineMode( bool IsEnable, bool IsFogEnable, const Kernel::Math::VectorS& FogColor ) = 0;
	};
}
}
}

/**
	@file
	@brief �^�X�N����
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Task
{
	enum eTaskPass
	{
		TaskPass_Main,
		TaskPass_Post,
		TaskPass_Max,
	};

	typedef Kernel::Delegate01<Sint64> TaskExecutor;

	class TaskQueue
	{
	private:
		mutable TaskExecutor	m_Execute;

	public:
		TaskQueue()
		{
		}

		TaskQueue( const TaskExecutor& Execute )
			: m_Execute	( Execute )
		{
		}

		void Set( const TaskExecutor& Execute )
		{
			m_Execute = Execute;
		}

		void Execute( Sint64 DeltaTime ) const
		{
			m_Execute( DeltaTime );
		}
	};

	class ITaskManager
		: public Interface
	{
	public:
		virtual void Clear() = 0;
		virtual void SetProfileEnable( bool IsProfile ) = 0;
		virtual void Start() = 0;
		virtual void End() = 0;
		virtual void PushMasterTask( eTaskPass TaskPass, const TaskQueue& Que, const ColorF& Color ) = 0;
		virtual void PushSlaveTask( eTaskPass TaskPass, const TaskQueue& Que, const ColorF& Color ) = 0;
		virtual void PushSlaveTaskBarrier( eTaskPass TaskPass ) = 0;
		virtual void Execute( Sint64 DeltaTime ) = 0;
		virtual Sint32 GetMaxTaskCount() = 0;
		virtual void DrawTaskExecuteTime( Engine::Graphics::Simple::ISpriteRenderer* pSprite ) = 0;
	};
}
}
}


/**
	@file
	@brief �R���g���[�����C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	enum eControlType
	{
		CONTROL_TYPE_DESKTOP,
		CONTROL_TYPE_DIALOG,
		CONTROL_TYPE_WINDOW,
		CONTROL_TYPE_WINDOW_IME,
		CONTROL_TYPE_MENUBAR,
		CONTROL_TYPE_MENUBAR_BUTTON,
		CONTROL_TYPE_MENUBAR_LIST,
		CONTROL_TYPE_SCROLLBAR,
		CONTROL_TYPE_BUTTON,
		CONTROL_TYPE_LISTBOX,
		CONTROL_TYPE_COMBOBOX,
		CONTROL_TYPE_SLIDERBAR,
		CONTROL_TYPE_PROGRESSBAR,
		CONTROL_TYPE_LABEL,
		CONTROL_TYPE_GROUPBOX,
		CONTROL_TYPE_CHECKBOX,
		CONTROL_TYPE_EDITBOX,
		CONTROL_TYPE_TEXTBOX,
	};

	enum eTextAlign
	{
		TEXT_ALIGN_LEFT,
		TEXT_ALIGN_CENTER,
		TEXT_ALIGN_RIGHT,
	};

	enum eControlEdge
	{
		CONTROL_EDGE_NONE,
		CONTROL_EDGE_LINE,
	};

	enum eImeCursorAttribute
	{
		ICA_INPUT,					// �I������Ă��Ȃ��A�ϊ�����Ă��Ȃ������B 
		ICA_TARGET_CONVERTED,		// �I������Ă��āA�ϊ�����Ă��镶���B 
		ICA_CONVERTED,				// �I������ĂȂ��A�ϊ�����Ă��镶���B 
		ICA_TARGET_NOTCONVERTED,	// �I������Ă��āA�ϊ�����Ă��Ȃ������B 
		ICA_INPUT_ERROR,			// �����ȕ����B 
	};

	enum eControlShapeType
	{
		CONTROL_TYPE_HORIZONTAL,
		CONTROL_TYPE_VERTICAL,
		CONTROL_TYPE_MAX,
	};

	struct DrawArgs
	{
		bool IsForcus;
		bool IsForcusParentWindow;
		bool IsMouseHover;
		bool IsMouseDown;
		Sint32 MouseHoverTime;
		RectI ScissorRect;
		RectI ClientRect;
		RectI ClientDrawRect;
		eControlEdge Edge;
	};

	typedef Kernel::Delegate02<IControl*,const DrawArgs&>	OwnerDrawEvent;
	typedef Kernel::Delegate01<IControl*>					OwnerDeleteEvent;

	class IControl
		: public Interface
	{
	protected:
		virtual ~IControl(){}

	public:
		virtual bool IsShow() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void SetControlEdge( eControlEdge Edge ) = 0;

		virtual void SetOwnerDrawEvent( const OwnerDrawEvent& Event ) = 0;
		virtual void SetOwnerDeleteEvent( const OwnerDeleteEvent& Event ) = 0;

		virtual eControlType GetType() const = 0;

		virtual void* GetUserData() = 0;
		virtual void SetUserData( void* pData ) = 0;

		virtual void SetID( Uint32 Id ) = 0;
		virtual Uint32 GetID() const = 0;

		virtual void SetName( const wchar_t* pName ) = 0;
		virtual const wchar_t* GetName() const = 0;

		virtual void SetDockType( bool IsTop, bool IsBottom, bool IsLeft, bool IsRight ) = 0;
		virtual void SetMargin( Sint32 Size ) = 0;
		virtual void SetPosition( const Point2DI& Position ) = 0;
		virtual void SetSize( const Point2DI& Size ) = 0;
		virtual void SetMinSize( const Point2DI& Size ) = 0;
		virtual void SetMaxSize( const Point2DI& Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief IME�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ImeDrawArgs
		: public DrawArgs
	{
		const wchar_t** ppCandidateList;
		const RectI* pCandidateRect;
		Sint32 CandidateListCount;
		Sint32 SelectCandidateIndex;

		RectI L_EdgeRect;
		RectI R_EdgeRect;
		RectI T_EdgeRect;
		RectI B_EdgeRect;
		RectI LT_CornerRect;
		RectI LB_CornerRect;
		RectI RT_CornerRect;
		RectI RB_CornerRect;
	};

	class IIme
		: public IControl
	{
	protected:
		virtual ~IIme(){}

	public:
		virtual void SetPositionAuto( const Point2DI& Position ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �G�f�B�b�g�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct EditBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t** ppText;
		const Point2DI* pPosition;
		Sint32 LineMax;
		Sint32 ActiveLine;
		Sint32 ActiveCursor;
		bool IsReadOnly;
		const wchar_t* pImeConvertText;
		const Sint32* pImeConvertCursor;
		const eImeCursorAttribute* pImeConvertTextAttribute;
		Sint32 ImeConvertCursorCount;
	};

	typedef Kernel::Delegate01<IControl*> EditBoxCopyEvent;
	typedef Kernel::Delegate01<IControl*> EditBoxPasteEvent;
	typedef Kernel::Delegate01<IControl*> EditBoxPressEnterEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> EditBoxGetStringLengthEvent;

	class IEditBox
		: public IControl
	{
	protected:
		virtual ~IEditBox(){}

	public:
		virtual void SetCopyEvent( const EditBoxCopyEvent& Event ) = 0;
		virtual void SetPasteEvent( const EditBoxPasteEvent& Event ) = 0;
		virtual void SetPressEnterEvent( const EditBoxPressEnterEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const EditBoxGetStringLengthEvent& Event ) = 0;

		virtual void ClearText() = 0;
		virtual void AddText( const wchar_t* pText ) = 0;
		virtual void InsertText( const wchar_t* pText ) = 0;
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual IScrollBar* GetScrollBar() = 0;
	};
}
}
}
}

/**
	@file
	@brief �e�L�X�g�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	enum eTextBoxInputType
	{
		TB_INPUT_TYPE_READ_ONLY,
		TB_INPUT_TYPE_NUMBER_ONLY,
		TB_INPUT_TYPE_ASCII_ONLY,
		TB_INPUT_TYPE_ALL,
	};

	struct TextBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t* pText;
		Sint32 ActiveCursor;
		bool IsReadOnly;
		Sint32 OffsetPosition;
		const wchar_t* pImeConvertText;
		const Sint32* pImeConvertCursor;
		const eImeCursorAttribute* pImeConvertTextAttribute;
		Sint32 ImeConvertCursorCount;
	};

	typedef Kernel::Delegate01<IControl*> TextBoxCopyEvent;
	typedef Kernel::Delegate01<IControl*> TextBoxPasteEvent;
	typedef Kernel::Delegate01<IControl*> TextBoxPressEnterEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> TextBoxGetStringLengthEvent;

	class ITextBox
		: public IControl
	{
	protected:
		virtual ~ITextBox(){}

	public:
		virtual void SetCopyEvent( const TextBoxCopyEvent& Event ) = 0;
		virtual void SetPasteEvent( const TextBoxPasteEvent& Event ) = 0;
		virtual void SetPressEnterEvent( const TextBoxPressEnterEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const TextBoxGetStringLengthEvent& Event ) = 0;

		virtual void InsertText( const wchar_t* pText ) = 0;
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;
	};
}
}
}
}

/**
	@file
	@brief �X�N���[���o�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ScrollBarDrawArgsData
	{
		bool IsEnable;
		bool IsOver[2];
		RectI Client;
		RectI HandleRect;
		RectI ButtonRect[2];
	};

	struct ScrollBarDrawArgs
		: public DrawArgs
	{
		ScrollBarDrawArgsData DataH;
		ScrollBarDrawArgsData DataV;
	};

	typedef Kernel::Delegate03<IControl*,Sint32,Sint32> ScrollBarChangeEvent;

	class IScrollBar
		: public IControl
	{
	protected:
		virtual ~IScrollBar(){}

	public:
		virtual void SetScrollBarChangeEvent( const ScrollBarChangeEvent& ScrollBarChange ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �X���C�_�[�o�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct SliderBarDrawArgs
		: public DrawArgs
	{
		eControlShapeType Type;
		float MinValue;
		float MaxValue;
		float Value;
		RectI HandleRect;
		RectI RulerRect;
	};

	typedef Kernel::Delegate03<IControl*,float,float> SliderBarChangeEvent;

	class ISliderBar
		: public IControl
	{
	protected:
		virtual ~ISliderBar(){}

	public:
		virtual void SetSliderBarChangeEvent( const SliderBarChangeEvent& Event ) = 0;

		virtual float GetMinValue() const = 0;
		virtual float GetMaxValue() const = 0;
		virtual float GetValue() const = 0;

		virtual void SetMinValue( float Value ) = 0;
		virtual void SetMaxValue( float Value ) = 0;
		virtual void SetValue( float Value ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �v���O���X�o�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ProgressBarDrawArgs
		: public DrawArgs
	{
		eControlShapeType Type;
		RectI ProgressRect;
		float Rate;
	};

	class IProgressBar
		: public IControl
	{
	protected:
		virtual ~IProgressBar(){}

	public:
		virtual Sint32 GetMaxValue() const = 0;
		virtual Sint32 GetValue() const = 0;

		virtual void SetMaxValue( Sint32 Value ) = 0;
		virtual void SetValue( Sint32 Value ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �`�F�b�N�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct CheckBoxDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
		bool IsCheck;
	};

	typedef Kernel::Delegate02<IControl*,bool> CheckBoxChangeEvent;

	class ICheckBox
		: public IControl
	{
	protected:
		virtual ~ICheckBox(){}

	public:
		virtual void SetCheckBoxChangeEvent( const CheckBoxChangeEvent& Event ) = 0;

		virtual void SetTextAlign( eTextAlign TextAlign ) = 0;

		virtual void SetText( const wchar_t* pText ) = 0;
		virtual void GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual void SetChecked( bool IsCheck ) = 0;
		virtual bool GetChecked() const = 0;
	};
}
}
}
}

/**
	@file
	@brief �{�^���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ButtonDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
	};

	typedef Kernel::Delegate01<IControl*> ButtonPushEvent;

	class IButton
		: public IControl
	{
	protected:
		virtual ~IButton(){}

	public:
		virtual void SetButtonPushEvent( const ButtonPushEvent& Event ) = 0;

		virtual void SetTextAlign( eTextAlign TextAlign ) = 0;

		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;
	};
}
}
}
}

/**
	@file
	@brief ���x���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct LabelDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
	};

	class ILabel
		: public IControl
	{
	protected:
		virtual ~ILabel(){}

	public:
		virtual void SetTextAlign( eTextAlign TextAlign ) = 0;

		virtual void SetText( const wchar_t* pText ) = 0;
		virtual void GetText( wchar_t* pText, Sint32 Length ) const = 0;
		virtual void SetFloat( float Value ) = 0;
		virtual float GetFloat() const = 0;
		virtual void SetInt( Sint32 Value ) = 0;
		virtual Sint32 GetInt() const = 0;
	};
}
}
}
}

/**
	@file
	@brief �O���[�v�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct GroupBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t* pText;
		RectI TitleRect;
	};

	class IGroupBox
		: public IControl
	{
	protected:
		virtual ~IGroupBox(){}

	public:
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual void GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual IButton* AddButton( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual ICheckBox* AddCheckBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked ) = 0;
		virtual ILabel* AddLabel( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual IGroupBox* AddGroupBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight ) = 0;
		virtual IEditBox* AddEditBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight ) = 0;
		virtual ISliderBar* AddSliderBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type, Sint32 HandleSize ) = 0;
		virtual IProgressBar* AddProgressBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type ) = 0;
		virtual IListBox* AddListBox( const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort ) = 0;
		virtual IComboBox* AddComboBox( const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort ) = 0;
		virtual ITextBox* AddTextBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, eTextBoxInputType InputType ) = 0;
	};
}
}
}
}

/**
	@file
	@brief ���X�g�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ListBoxDrawArgs
		: public DrawArgs
	{
		Sint32 SelectItem;
		Sint32 MouseHoverItem;
		Sint32 ItemCount;
		RectI* pItemRect;
		const wchar_t** ppItemText;
	};

	typedef Kernel::Delegate03<IControl*,const wchar_t*,Kernel::Object::ReferenceObject*> ListBoxSelectEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> ListBoxGetStringLengthEvent;

	class IListBox
		: public IControl
	{
	protected:
		virtual ~IListBox(){}

	public:
		virtual void SetSelectEvent( const ListBoxSelectEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const ListBoxGetStringLengthEvent& Event ) = 0;

		virtual Sint32 AddItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( Sint32 Index ) = 0;

		virtual Sint32 GetSelectItem( wchar_t* pText, Sint32 TextSize, Kernel::Object::ReferenceObject*& pObject ) const = 0;
		virtual void SetSelectItem( Sint32 Index ) = 0;
		virtual void SetSelectItem( wchar_t* pText ) = 0;

		virtual IScrollBar* GetScrollBar() = 0;
	};
}
}
}
}

/**
	@file
	@brief �R���{�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct ComboBoxDrawArgs
		: public DrawArgs
	{
		const wchar_t* pText;
		RectI ButtonRect;
		RectI DropDownListRect;
		RectI DropDownListDrawRect;
		Sint32 DropDownSelectItem;
		Sint32 DropDownItemCount;
		RectI* pDropDownItemRect;
		const wchar_t** ppDropDownItemText;
		bool IsDropDownOpen;
	};

	typedef Kernel::Delegate03<IControl*,const wchar_t*,Kernel::Object::ReferenceObject*> ComboBoxSelectEvent;
	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> ComboBoxGetStringLengthEvent;

	class IComboBox
		: public IControl
	{
	protected:
		virtual ~IComboBox(){}

	public:
		virtual void SetSelectEvent( const ComboBoxSelectEvent& Event ) = 0;
		virtual void SetGetStringLengthEvent( const ComboBoxGetStringLengthEvent& Event ) = 0;

		virtual void AddItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( const wchar_t* pText, Kernel::Object::ReferenceObject* pObject ) = 0;
		virtual void SubItem( Sint32 Index ) = 0;

		virtual Sint32 GetSelectItem( const wchar_t* pText, Sint32 Length, Kernel::Object::ReferenceObject*& pObject ) const = 0;
		virtual void SetSelectItem( Sint32 Index ) = 0;

		virtual IScrollBar* GetScrollBar() = 0;
	};
}
}
}
}

/**
	@file
	@brief ���j���[�{�^���C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct MenuButtonDrawArgs
		: public DrawArgs
	{
		eTextAlign TextAlign;
		const wchar_t* pText;
		bool IsPopupMenu;
		bool IsCheckBox;
		bool IsChecked;
	};

	class IMenuButton
		: public IControl
	{
	protected:
		virtual ~IMenuButton(){}

	public:
		virtual void SetText( const wchar_t* pText ) = 0;
		virtual Sint32 GetText( wchar_t* pText, Sint32 Length ) const = 0;

		virtual void SetChecked( bool IsChecked ) = 0;
		virtual bool GetChecked() const = 0;
	};
}
}
}
}

/**
	@file
	@brief �X���C�_�[�o�[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	typedef Kernel::Delegate01<IControl*> MenuClickEvent;

	struct SMenuItem
	{
		wchar_t Text[64];
		Uint32 ID;
		bool IsCheckBox;
		bool IsChecked;
		MenuClickEvent Event;
	};

	struct MenuBarDrawArgs
		: public DrawArgs
	{
	};

	typedef Kernel::Delegate03<IControl*,const wchar_t*,Sint32&> MenuBarGetStringLengthEvent;

	class IMenuBar
		: public IControl
	{
	protected:
		virtual ~IMenuBar(){}

	public:
		virtual void SetGetStringLengthEvent( const MenuBarGetStringLengthEvent& Event ) = 0;
		virtual IMenuButton* SearchMenuButtonByID( Uint32 TargetID ) = 0;
		virtual bool AppendRootMenu( const SMenuItem& Item ) = 0;
		virtual bool AppendSubMenu( Uint32 TargetID, const SMenuItem& Item ) = 0;
		virtual bool DeleteMenu( Uint32 TargetID ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �E�B���h�E�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct WindowDrawArgs
		: public DrawArgs
	{
		const wchar_t* pTitle;
		bool IsMouseOnWindow;
		RectI TitleBarRect;
		RectI CloseButtonRect;
		RectI L_EdgeRect;
		RectI R_EdgeRect;
		RectI T_EdgeRect;
		RectI B_EdgeRect;
		RectI LT_CornerRect;
		RectI LB_CornerRect;
		RectI RT_CornerRect;
		RectI RB_CornerRect;
	};

	typedef Kernel::Delegate02<IControl*,bool&> WindowCloseEvent;

	class IWindow
		: public IControl
	{
	protected:
		virtual ~IWindow(){}

	public:
		virtual void SetTitle( const wchar_t* pTitle ) = 0;
		virtual void GetTitle( wchar_t* pTitle, Sint32 Length ) const = 0;
		virtual void SetCloseEvent( const WindowCloseEvent& Event ) = 0;

		virtual IButton* AddButton( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual ICheckBox* AddCheckBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked ) = 0;
		virtual ILabel* AddLabel( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual IGroupBox* AddGroupBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight ) = 0;
		virtual IEditBox* AddEditBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight ) = 0;
		virtual ISliderBar* AddSliderBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type, Sint32 HandleSize ) = 0;
		virtual IProgressBar* AddProgressBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type ) = 0;
		virtual IListBox* AddListBox( const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort ) = 0;
		virtual IComboBox* AddComboBox( const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort ) = 0;
		virtual ITextBox* AddTextBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, eTextBoxInputType InputType ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �_�C�A���O�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
namespace Control
{
	struct DialogDrawArgs
		: public DrawArgs
	{
		const wchar_t* pTitle;
		Sint32 BlinkTime;
		RectI TitleBarRect;
		RectI CloseButtonRect;
		RectI L_EdgeRect;
		RectI R_EdgeRect;
		RectI T_EdgeRect;
		RectI B_EdgeRect;
		RectI LT_CornerRect;
		RectI LB_CornerRect;
		RectI RT_CornerRect;
		RectI RB_CornerRect;
	};

	typedef Kernel::Delegate02<IControl*,bool&> DialogCloseEvent;

	class IDialog
		: public IControl
	{
	protected:
		virtual ~IDialog(){}

	public:
		virtual void SetTitle( const wchar_t* pTitle ) = 0;
		virtual void GetTitle( wchar_t* pTitle, Sint32 Length ) const = 0;
		virtual void Close() = 0;

		virtual IButton* AddButton( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual ICheckBox* AddCheckBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked ) = 0;
		virtual ILabel* AddLabel( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size ) = 0;
		virtual IGroupBox* AddGroupBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight ) = 0;
		virtual IEditBox* AddEditBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight ) = 0;
		virtual ISliderBar* AddSliderBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type, Sint32 HandleSize ) = 0;
		virtual IProgressBar* AddProgressBar( const Point2DI& Position, const Point2DI& Size, eControlShapeType Type ) = 0;
		virtual IListBox* AddListBox( const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort ) = 0;
		virtual IComboBox* AddComboBox( const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort ) = 0;
		virtual ITextBox* AddTextBox( const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, eTextBoxInputType InputType ) = 0;
	};
}
}
}
}

/**
	@file
	@brief GUI�}�l�[�W���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
	enum eMouseCursorState
	{
		MCS_NORMAL,
		MCS_BEAM,
		MCS_DRAG,
		MCS_ARROW_L_R,
		MCS_ARROW_T_B,
		MCS_ARROW_LT_RB,
		MCS_ARROW_LB_RT,
	};

	enum eEventMessage
	{
		EM_NULL,

		EM_MOUSE_L_DOWN,
		EM_MOUSE_R_DOWN,
		EM_MOUSE_M_DOWN,
		EM_MOUSE_L_UP,
		EM_MOUSE_R_UP,
		EM_MOUSE_M_UP,
		EM_MOUSE_L_DOUBLE_CLICK,
		EM_MOUSE_R_DOUBLE_CLICK,
		EM_MOUSE_M_DOUBLE_CLICK,
		EM_MOUSE_MOVE,

		EM_FORCUS_BEGIN,
		EM_FORCUS_KEY_DOWN,
		EM_FORCUS_KEY_UP,
		EM_FORCUS_CHAR,
		EM_FORCUS_END,

		EM_IME_BEGIN,
		EM_IME_COMPOSITION_START,
		EM_IME_COMPOSITION_END,
		EM_IME_COMPOSITION,
		EM_IME_CANDIDATE_OPEN,
		EM_IME_CANDIDATE_CLOSE,
		EM_IME_CANDIDATE_UPDATE,
		EM_IME_END,
	};

	struct EventArgs
	{
	};

	struct MouseEventArgs
		: public EventArgs
	{
		bool IsAlt;
		bool IsShift;
		bool IsControl;
		bool IsLButton;
		bool IsRButton;
		bool IsMButton;
		Point2DI Position;
	};

	struct MouseMoveEventArgs
		: public MouseEventArgs
	{
		Point2DI Move;
	};

	struct KeyEventArgs
		: public EventArgs
	{
		bool IsAlt;
		bool IsShift;
		bool IsControl;
		Uint64 VirtualKey;
	};

	struct CharEventArgs
		: public EventArgs
	{
		wchar_t Chara;
	};

	struct ImeEventArgs
		: public EventArgs
	{
		bool IsCOMPATTR;			///< �ҏW������̃A�g���r���[�g���擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsCOMPCLAUSE;			///< �ҏW������̕��ߏ�񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsCOMPREADATTR;		///< ���݂̕ҏW�̃��[�f�B���O�����񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsCOMPREADCLAUSE;		///< �ҏW������̃��[�f�B���O������̕��ߏ�񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsCOMPREADSTR;			///< ���݂̕ҏW�̃��[�f�B���O�����񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsCOMPSTR;				///< ���݂̕ҏW�����񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsCURSORPOS;			///< �ҏW������̃J�[�\���ʒu���擾�����A�܂��͍ŐV�����ꂽ 
		bool IsDELTASTART;			///< �ҏW������̕ω��̊J�n�ʒu���擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsRESULTCLAUSE;		///< �m�蕶����̕��ߏ�񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsRESULTREADCLAUSE;	///< ���[�f�B���O������̕��ߏ�񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ 
		bool IsRESULTREADSTR;		///< ���[�f�B���O��������擾�����A�܂��͍ŐV�����ꂽ 
		bool IsRESULTSTR;			///< �m�蕶���񂪎擾���ꂽ�A�܂��͍ŐV�����ꂽ
	};

	typedef Kernel::Delegate01<const MouseMoveEventArgs&> DesktopMouseDragEvent;
	typedef Kernel::Delegate01<const MouseMoveEventArgs&> DesktopMouseMoveEvent;
	typedef Kernel::Delegate01<const MouseEventArgs&> DesktopMouseDownEvent;
	typedef Kernel::Delegate01<const MouseEventArgs&> DesktopMouseUpEvent;
	typedef Kernel::Delegate01<const eMouseCursorState&> MouseCursorSettingEvent;

	/**
		@brief GUI�Ǘ��N���X
		@author �t���`

		GUI�̏������s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		virtual bool OnEvent( eEventMessage Message, const EventArgs& Args ) = 0;
		virtual bool EventByWindowMessage( Uint32 Message, Uint64 wParam, Uint64 lParam ) = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		virtual const wchar_t* GetActiveControlName() const = 0;
		virtual Uint32 GetActiveControlID() const = 0;
		virtual const wchar_t* GetForcusWindowName() const = 0;
		virtual Uint32 GetForcusWindowID() const = 0;

		virtual bool IsForcusDesktop() = 0;
		virtual void CreateMenuBar( Sint32 TextHeight, bool IsAutoErase ) = 0;
		virtual Control::IMenuBar* GetMenuBar() = 0;
		virtual void CreateIME( Sint32 WindowWidth, Sint32 EdgeSize, Sint32 ItemHeight, Sint32 PageItemCount ) = 0;
		virtual Control::IIme* GetIME() = 0;
		virtual Control::IDialog* OpenDialog( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed ) = 0;
		virtual Control::IWindow* AddWindow( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed ) = 0;

		virtual void SetDesktopMouseDragEvent( const DesktopMouseDragEvent& Event ) = 0;
		virtual void SetDesktopMouseDownEvent( const DesktopMouseDownEvent& Event ) = 0;
		virtual void SetDesktopMouseUpEvent( const DesktopMouseUpEvent& Event ) = 0;
		virtual void SetDesktopMouseMoveEvent( const DesktopMouseMoveEvent& Event ) = 0;
		virtual void SetMouseCursorSettingEvent( const MouseCursorSettingEvent& Event ) = 0;
	};
}
}
}

/**
	@file
	@brief GUI�}�l�[�W���[�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace GUI
{
	/**
		@brief GUI�Ǘ��N���X
		@author �t���`

		GUI�̏������s�����߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IHelper
		: public Interface
	{
	protected:
		virtual ~IHelper(){}

	public:
		virtual void CreateMenuBar( Sint32 TextHeight, bool IsAutoErase ) = 0;
		virtual Engine::GUI::Control::IMenuBar* GetMenuBar() = 0;

		virtual Engine::GUI::Control::IControl* GetControlByID( Uint32 ControlId ) = 0;
		virtual void DeleteControlByID( Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IDialog* OpenDialog( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IWindow* AddWindow( const wchar_t* pTitleName, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Sint32 EdgeSize, bool IsFixed, Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IButton* AddButton( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ICheckBox* AddCheckBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ILabel* AddLabel( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IGroupBox* AddGroupBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IEditBox* AddEditBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ISliderBar* AddSliderBar( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Sint32 HandleSize, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IProgressBar* AddProgressBar( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IListBox* AddListBox( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IComboBox* AddComboBox( Engine::GUI::Control::IWindow* pTarget, const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ITextBox* AddTextBox( Engine::GUI::Control::IWindow* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eTextBoxInputType InputType, Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IButton* AddButton( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ICheckBox* AddCheckBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ILabel* AddLabel( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IGroupBox* AddGroupBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IEditBox* AddEditBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ISliderBar* AddSliderBar( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Sint32 HandleSize, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IProgressBar* AddProgressBar( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IListBox* AddListBox( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IComboBox* AddComboBox( Engine::GUI::Control::IGroupBox* pTarget, const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ITextBox* AddTextBox( Engine::GUI::Control::IGroupBox* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eTextBoxInputType InputType, Uint32 ControlId ) = 0;

		virtual Engine::GUI::Control::IButton* AddButton( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ICheckBox* AddCheckBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsChecked, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ILabel* AddLabel( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IGroupBox* AddGroupBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Sint32 TitleHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IEditBox* AddEditBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, bool IsReadOnly, bool IsMultiLine, Sint32 LineHeight, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ISliderBar* AddSliderBar( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Sint32 HandleSize, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IProgressBar* AddProgressBar( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eControlShapeType Type, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IListBox* AddListBox( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, const Point2DI& Size, Sint32 ItemHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::IComboBox* AddComboBox( Engine::GUI::Control::IDialog* pTarget, const Point2DI& Position, Sint32 Width, Sint32 ItemHeight, Sint32 DropDownListHeight, bool IsSort, Uint32 ControlId ) = 0;
		virtual Engine::GUI::Control::ITextBox* AddTextBox( Engine::GUI::Control::IDialog* pTarget, const wchar_t* pText, const Point2DI& Position, const Point2DI& Size, Engine::GUI::Control::eTextBoxInputType InputType, Uint32 ControlId ) = 0;
	};
}
}
}

/**
	@file
	@brief UDP�ڑ��p
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace UDP
{
	/**
		@brief UDP�ڑ��Ǘ��N���X
		@author �t���`

		UDP�ʐM�𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IConnect
		: public Interface
	{
	protected:
		virtual ~IConnect(){}

	public:
		/**
			@brief �f�[�^���M
			@author �t���`
			@param pData	[in] ���M����f�[�^
			@param Size		[in] �f�[�^��byte��
			@retval true	����
			@retval false	���s
			@note
			�f�[�^��ڑ���ɑ��M���܂��B
		*/
		virtual bool Send( const void* pData, Sint32 Size ) = 0;
		/**
			@brief �f�[�^��M
			@author �t���`
			@param pData	[in] ��M����f�[�^
			@param Size		[in] �f�[�^��byte��
			@retval true	����
			@retval false	���s
			@note
			�f�[�^��ڑ��悩���M���܂��B
		*/
		virtual bool Recv( void* pData, Sint32 Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief TCP�ʐM�p�N���C�A���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace TCP
{
	/**
		@brief TCP�ʐM�Ǘ��N���X
		@author �t���`

		TCP�ʐM�̃N���C�A���g�����𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IClient
		: public Interface
	{
	protected:
		virtual ~IClient(){}

	public:
		/**
			@brief �f�[�^���M
			@author �t���`
			@param pData	[in] ���M����f�[�^
			@param Size		[in] �f�[�^��byte��
			@retval true	����
			@retval false	���s
			@note
			�f�[�^��ڑ���ɑ��M���܂��B
		*/
		virtual bool Send( const void* pData, Sint32 Size ) = 0;
		/**
			@brief �f�[�^��M
			@author �t���`
			@param pData	[in] ��M����f�[�^
			@param Size		[in] �f�[�^��byte��
			@retval true	����
			@retval false	���s
			@note
			�f�[�^��ڑ��悩���M���܂��B
		*/
		virtual bool Recv( void* pData, Sint32 Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief TCP�ڑ��p�T�[�o�[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace TCP
{
	/**
		@brief �T�[�o�[�C�x���g�̃��V�[�o�[
		@author �t���`
		@note
		�T�[�o�[�C�x���g���̃R�[���o�b�N���擾����ׂ̃��X�i�[�C���^�[�t�F�C�X
	*/
	class IServerEventReceiver
	{
	protected:
		virtual ~IServerEventReceiver(){}

	public:
		/**
			@brief �ڑ����R�[���o�b�N�C�x���g
			@author �t���`
			@param pClient	[in] �ڑ��N���C�A���g
			@note
			�N���C�A���g����̐ڑ����s��ꂽ���ɃR�[���o�b�N����Ă��܂��B
		*/
		virtual void OnConnect( Engine::Network::TCP::IClientOfServer* pClient ) = 0;
		/**
			@brief �ؒf���R�[���o�b�N�C�x���g
			@author �t���`
			@param pClient	[in] �ؒf�N���C�A���g
			@note
			�N���C�A���g����̐ؒf���s��ꂽ���ɃR�[���o�b�N����Ă��܂��B
		*/
		virtual void OnDisconnect( Engine::Network::TCP::IClientOfServer* pClient ) = 0;
		/**
			@brief �A�C�h�����R�[���o�b�N�C�x���g
			@author �t���`
			@param pSender	[in] �N���C�A���g�ւ̑��M�p�C���^�[�t�F�C�X
			@note
			�A�C�h�����̃R�[���o�b�N����Ă��܂��B
		*/
		virtual bool OnIdle( Engine::Network::TCP::IServerSender* pSender ) = 0;
		/**
			@brief ��M���R�[���o�b�N�C�x���g
			@author �t���`
			@param pReciver	[in] �N���C�A���g�ւ̎�M�p�C���^�[�t�F�C�X
			@note
			�N���C�A���g����̎�M���ɃR�[���o�b�N����Ă��܂��B
		*/
		virtual bool OnRecv( Engine::Network::TCP::IServerReciver* pReciver ) = 0;
	};

	/**
		@brief �T�[�o�[���̃C�x���g���X�i�[�N���X����
		@author �t���`
		@return �N���C�A���g�N���X
		@note
		�T�[�o�[���ŕێ����Ă������X�i�[�C�x���g�t���̃N���A���g�N���X��<BR>
		�������s�����߂̃e���v���[�g�֐��ł��B
	*/
	template < typename T >
	IServerEventReceiver* CreateReceiverFactory( IManager* pManager )
	{
		return new T( pManager );
	}

	typedef IServerEventReceiver* (*RECEIVER_FACTORY_PROC)( IManager* pManager );

	/**
		@brief TCP�ʐM�Ǘ��N���X
		@author �t���`
		@note
		TCP�ʐM�̃T�[�o�[�����𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IServer
		: public Interface
	{
	protected:
		virtual ~IServer(){}

	public:
		/**
			@brief �T�[�o�[�����N��
			@author �t���`
			@param pFactory	[in] �T�[�o�[�ւ̐ڑ����ɃN���C�A���g�N���X�𐶐�����ׂ̃t�@�N�g���[�֐�
			@retval true	����
			@retval false	���s
			@note
			�T�[�o�[�Ƃ��Ă̏������J�n���܂��B
		*/
		virtual bool Start( RECEIVER_FACTORY_PROC pFactory ) = 0;
		/**
			@brief �S�N���C�A���g�ɑ��M
			@author �t���`
			@param pData	[in] ���M����f�[�^
			@param Size		[in] �f�[�^�T�C�Y
			@retval true	����
			@retval false	���s
			@note
			�S�ẴN���C�A���g�ɑ΂��ăf�[�^�̑��M���s���܂��B
		*/
		virtual bool SendToAllClient( const void* pData, Sint32 Size ) = 0;
	};
}
}
}
}

/**
	@file
	@brief TCP�ʐM�p�T�[�o�[�ڑ��N���C�A���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
namespace TCP
{
	/**
		@brief �T�[�o�[��M�p�C���^�[�t�F�C�X
		@author �t���`
		@note
		�T�[�o�[���N���A���g����f�[�^����M����ꍇ�ɗ��p�����
	*/
	class IServerReciver
	{
	protected:
		virtual ~IServerReciver(){}

	public:
		/**
			@brief �z�X�g���擾
			@author �t���`
			@param Info	[out] �ڑ���̃z�X�g�����擾
			@note
			�ڑ���̃z�X�g�����擾�ł��܂��B
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
		/**
			@brief �f�[�^��M
			@author �t���`
			@param pData	[in] ��M����f�[�^
			@param Size		[in] �f�[�^��byte��
			@retval true	����
			@retval false	���s
			@note
			�f�[�^��ڑ��悩���M���܂��B
		*/
		virtual bool Recv( void* pData, Sint32 Size ) = 0;
	};

	/**
		@brief �T�[�o�[���M�p�C���^�[�t�F�C�X
		@author �t���`
		@note
		�T�[�o�[���N���A���g�Ƀf�[�^�𑗐M����ꍇ�ɗ��p�����
	*/
	class IServerSender
	{
	protected:
		virtual ~IServerSender(){}

	public:
		/**
			@brief �z�X�g���擾
			@author �t���`
			@param Info	[out] �ڑ���̃z�X�g�����擾
			@note
			�ڑ���̃z�X�g�����擾�ł��܂��B
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
		/**
			@brief �f�[�^���M
			@author �t���`
			@param pData	[in] ���M����f�[�^
			@param Size		[in] �f�[�^��byte��
			@retval true	����
			@retval false	���s
			@note
			�f�[�^��ڑ���ɑ��M���܂��B
		*/
		virtual bool Send( const void* pData, Sint32 Size ) = 0;
	};

	/**
		@brief TCP�ʐM�T�[�o�[�p�N���C�A���g�Ǘ��N���X
		@author �t���`
		@note
		TCP�ʐM�̃T�[�o�[���̃N���C�A���g�Ǘ����s�����߂̃C���^�[�t�F�C�X�B
	*/
	class IClientOfServer
		: public Interface
	{
	protected:
		virtual ~IClientOfServer(){}

	public:
		/**
			@brief �z�X�g���擾
			@author �t���`
			@param Info	[out] �ڑ���̃z�X�g�����擾
			@note
			�ڑ���̃z�X�g�����擾�ł��܂��B
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
	};
}
}
}
}

/**
	@file
	@brief �l�b�g���[�N�}�l�[�W���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Network
{
	/**
		@brief �l�b�g���[�N�Ǘ��N���X
		@author �t���`

		�l�b�g���[�N�����𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief ���M�p�������m��
			@author �t���`
			@return �������A�h���X
			@note
			���M�ŗ��p����ׂ̃��������擾���܂��B<BR>
			���M��Ɏ����I�Ƀ������͉������܂��B
		*/
		virtual void* GetDataSendMemory( Uint32 Size ) const = 0;
		/**
			@brief �ŏI�G���[�擾
			@author �t���`
			@return �G���[���b�Z�[�W
			@note
			�ŏI�I�ɔ��������G���[���擾���܂��B
		*/
		virtual const wchar_t* GetLastError() const = 0;
		/**
			@brief �z�X�g���擾
			@author �t���`
			@param Info	[out] �����̃z�X�g�����擾
			@note
			�����̃z�X�g�����擾�ł��܂��B
		*/
		virtual void GetHostInfo( SHostInfo& Info ) const = 0;
		/**
			@brief �T�[�o�[����
			@author �t���`
			@param Port			[in] �|�[�g
			@param ConnectMax	[in] �ڑ��ő吔
			@note
			TCP�ڑ��̃T�[�o�[�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual TCP::IServer* CreateServer( Uint16 Port, Uint32 ConnectMax ) = 0;
		/**
			@brief TCP�ڑ��N���C�A���g����
			@author �t���`
			@param pTargetHost	[in] �Ώۂ̃z�X�g�܂���IP�A�h���X
			@param TargetPort	[in] �Ώۂ̃z�X�g�̃|�[�g
			@note
			TCP�ڑ��̃N���C�A���g�C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual TCP::IClient* ConnectByTCP( const char* pTargetHost, Uint16 TargetPort ) = 0;
		/**
			@brief UDP�ڑ�����
			@author �t���`
			@param pTargetHost	[in] �Ώۂ̃z�X�g�܂���IP�A�h���X
			@param TargetPort	[in] �Ώۂ̃z�X�g�̃|�[�g
			@note
			UDP�ڑ����s���܂��B<BR>
			UDP�ɂ̓T�[�o�[��N���C�A���g�̊T�O���Ȃ��̂�<BR>
			�o���ō쐬���Ď��O�ŊǗ�����K�v������܂��B
		*/
		virtual UDP::IConnect* ConnectByUDP( const char* pTargetHost, Uint16 TargetPort ) = 0;
	};
}
}
}

/**
	@file
	@brief �������풓�T�E���h
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Sound
{
namespace Resource
{
	/**
		@brief �T�E���h�Ǘ��N���X
		@author �t���`
		@note
		�������풓�^�̃T�E���h�̏������s���N���X�ł��B<BR>
		�����kWave�݂̂̃I�����������d�Đ��ɑΉ����Ă��܂��B<BR>
		�܂�3D�T�E���h�̗��p���\�ŁA���ʉ��Ƃ��Ă̗p�r��z�肵�Ă��܂��B
	*/
	class IStaticSound
		: public Interface
	{
	protected:
		virtual ~IStaticSound(){}

	public:
		/**
			@brief �Đ�
			@author �t���`
			@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
			@param IsLoop	[in] ���[�v�L���t���O
			@note
			�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
			���[�v�̗L�����w��ł��܂��B
		*/
		virtual void Play( Sint32 Layer, bool IsLoop = false ) = 0;

		/**
			@brief ��~
			@author �t���`
			@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
			@note
			�Đ����̃T�E���h���~���܂��B
		*/
		virtual void Stop( Sint32 Layer ) = 0;

		/**
			@brief �ꎞ��~/����
			@author �t���`
			@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
			@note
			�Đ����̃T�E���h���ꎞ��~�A<BR>
			�ꎞ��~���̃T�E���h���Đ����܂��B
		*/
		virtual void Pause( Sint32 Layer ) = 0;

		/**
			@brief �ꎞ��~�`�F�b�N
			@author �t���`
			@param Layer	[in] ���C���[�ԍ�
			@retval false	�ꎞ��~���Ă��Ȃ�
			@retval true	�ꎞ��~���Ă���
			@note
			���݈ꎞ��~�̃T�E���h���ǂ������ׂ܂��B
		*/
		virtual bool IsPause( Sint32 Layer ) const = 0;

		/**
			@brief �Đ��`�F�b�N
			@author �t���`
			@param Layer	[in] ���C���[�ԍ�
			@retval false	�Đ����Ă��Ȃ�
			@retval true	�Đ����Ă���
			@note
			���ݍĐ����̃T�E���h���ǂ������ׂ܂��B
		*/
		virtual bool IsPlay( Sint32 Layer ) const = 0;

		/**
			@brief �{�����[���ύX
			@author �t���`
			@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
			@param Volume	[in] �{�����[���i0�`100%�j
			@note
			�{�����[���̕ύX���s���܂��B
		*/
		virtual void SetVolume( Sint32 Layer, float Volume ) = 0;

		/**
			@brief 3D�T�E���h�̈ʒu�ݒ�
			@author �t���`
			@param Layer	[in] ���C���[�ԍ��i-1�w��őS���C���[�ɑ΂��āj
			@param Position	[in] 3D��ԏ�̈ʒu
			@note
			3D�T�E���h���̃��[���h�̈ʒu��ݒ肵�܂��B
		*/
		virtual void SetPosition( Sint32 Layer, const Kernel::Math::VectorS& Position ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �X�g���[���T�E���h
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Sound
{
namespace Resource
{
	static const float PLAY_TIME_AUTO = -1.0f;	///< �Đ����Ԏ����ݒ�

	/**
		@brief �X�g���[���T�E���h�Đ��p�����[�^�[
		@author �t���`
		@note
		�X�g���[���T�E���h�̍Đ����s�����߂̃e�[�u���f�[�^�ł��B
	*/
	struct SPlayBlock
	{
		Sint32 LoopCount;		///< ���̃e�[�u���̃��[�v���i-1�Ŗ������[�v�j
		float StartTime;		///< �Đ��J�n�ʒu�i�b�w��j�iPLAY_TIME_AUTO�w��ōŏ�����j
		float EndTime;			///< �Đ��I���ʒu�i�b�w��j�iPLAY_TIME_AUTO�w��ōŌ�܂Łj
	};

	/**
		@brief �X�g���[���T�E���h�Ǘ��N���X
		@author �t���`
		@note
		�X�g���[���T�E���h�̏������s���N���X�ł��B<BR>
		�����kWave/���kWave/OggVorbis�̍Đ��ɑΉ����Ă��܂��B<BR>
		BGM�≹���̍Đ��p�r��z�肵�Ă��܂��B
	*/
	class IStreamSound
		: public Interface
	{
	protected:
		virtual ~IStreamSound(){}

	public:
		/**
			@brief �Đ�
			@author �t���`
			@param pTbl			[in] �Đ��e�[�u��
			@param Count		[in] �Đ��e�[�u����
			@note
			�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B<BR>
			�Đ��e�[�u���̒�`�ɂ����čĐ�����Ă����܂��B
		*/
		virtual void Play( const SPlayBlock* pTbl, Sint32 Count ) = 0;

		/**
			@brief �Đ�
			@author �t���`
			@param LoopCount	[in] ���[�v��(-1�Ŗ���)
			@note
			�ǂݍ��񂾃T�E���h�f�[�^�̍Đ����J�n���܂��B
		*/
		virtual void Play( Sint32 LoopCount = 0 ) = 0;

		/**
			@brief ��~
			@author �t���`
			@note
			�Đ����̃T�E���h���~���܂��B
		*/
		virtual void Stop() = 0;

		/**
			@brief �ꎞ��~/����
			@author �t���`
			@note
			�Đ����̃T�E���h���ꎞ��~�A<BR>
			�ꎞ��~���̃T�E���h���Đ����܂��B
		*/
		virtual void Pause() = 0;

		/**
			@brief �Đ��`�F�b�N
			@author �t���`
			@retval true	�Đ����Ă���
			@retval false	�Đ����Ă��Ȃ�
			@note
			���ݍĐ����̃T�E���h���ǂ������ׂ܂��B
		*/
		virtual bool IsPlay() const = 0;

		/**
			@brief �{�����[���ύX
			@author �t���`
			@param Volume	[in] �{�����[���i0�`100�j
			@note
			�{�����[���̕ύX���s���܂��B
		*/
		virtual void SetVolume( float Volume ) = 0;

		/**
			@brief �t�F�[�h�C��
			@author �t���`
			@param Second	[in] �b�P�ʂł̎���
			@param Volume	[in] �^�[�Q�b�g�̃{�����[��
			@note
			�t�F�[�h�C���������s���܂�
		*/
		virtual void FadeIn( float Second, float Volume = 100.0f ) = 0;

		/**
			@brief �t�F�[�h�A�E�g
			@author �t���`
			@param Second	[in] �b�P�ʂł̎���
			@note
			�t�F�[�h�A�E�g�������s���܂�
		*/
		virtual void FadeOut( float Second ) = 0;
	};
}
}
}
}
/**
	@file
	@brief �T�E���h�}�l�[�W���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Sound
{
	/**
		@brief �T�E���h�f�o�C�X�Ǘ��N���X
		@author �t���`
		@note
		�T�E���h�����𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief �X�g���[���T�E���h�̐���
			@author �t���`
			@param pFile		[in] �Đ�����t�@�C��
			@param pPluginName	[in] ���p����v���O�C����
			@param IsMemoryCopy	[in] �����Ń��������R�s�[���Ă����Ă������ǂ���
			@return IStreamSound�C���^�[�t�F�C�X
			@note
			������BGM�Ŏg���t�@�C���X�g���[���Đ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�w�肵���v���O�C�����g���ă��A���^�C���Ƀf�R�[�h���Ȃ���Đ����s���܂��B<BR>
			���k�����t�@�C���𒼐ڍĐ��ł���̂Ń������I�ɂ͗L���ł����f�R�[�h��CPU���g���̂�<BR>
			���ʂ̍Đ��𓯎��ɍs���ꍇ�͒��ӂ��K�v�ł��B
		*/
		virtual Resource::IStreamSound* CreateStreamSound( File::IFile* pFile, const wchar_t *pPluginName, bool IsMemoryCopy = true ) = 0;

		/**
			@brief �X�g���[���T�E���h�̐���
			@author �t���`
			@param pFileName	[in] �t�@�C����
			@param pData		[in] Wave�t�@�C���̃f�[�^
			@param Size			[in] Wave�t�@�C���̃f�[�^�T�C�Y
			@param pPluginName	[in] ���p����v���O�C����
			@param IsMemoryCopy	[in] �����Ń��������R�s�[���Ă����Ă������ǂ���
			@return IStreamSound�C���^�[�t�F�C�X
			@note
			������BGM�Ŏg���t�@�C���X�g���[���Đ��p�̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			�w�肵���v���O�C�����g���ă��A���^�C���Ƀf�R�[�h���Ȃ���Đ����s���܂��B<BR>
			���k�����t�@�C���𒼐ڍĐ��ł���̂Ń������I�ɂ͗L���ł����f�R�[�h��CPU���g���̂�<BR>
			���ʂ̍Đ��𓯎��ɍs���ꍇ�͒��ӂ��K�v�ł��B
		*/
		virtual Resource::IStreamSound* CreateStreamSound( const wchar_t* pFileName, const void* pData, Uint32 Size, const wchar_t *pPluginName, bool IsMemoryCopy ) = 0;

		/**
			@brief �X�^�e�B�b�N�T�E���h�̐���
			@author �t���`
			@param pFileName	[in] �t�@�C����
			@param pData		[in] Wave�t�@�C���̃f�[�^
			@param Size			[in] Wave�t�@�C���̃f�[�^�T�C�Y
			@param LayerCount	[in] �����Đ��p���C���[�̐�
			@param Is3DSound	[in] 3D�T�E���h�Ƃ��Đ������邩�ǂ���
			@return IStaticSound�C���^�[�t�F�C�X
			@note
			�����Ɍ��ʉ��Ŏg���풓��wave�t�@�C���̃C���^�[�t�F�C�X�𐶐����܂��B<BR>
			����o�b�t�@���g�������������Đ���3D�T�E���h�Ȃǂ̋@�\�������Ă��܂��B<BR>
			�f�R�[�h�ς݂̐�wave�t�@�C�����������Ȃ��̂ő傫�ȃt�@�C���̓��������������܂����A<BR>
			�f�R�[�h�̕��ׂ��Ȃ��̂�SE�̂悤�ɐ��������T�C�Y�̏��������Ɍ����Ă��܂��B
		*/
		virtual Resource::IStaticSound* CreateStaticSound( const wchar_t* pFileName, const void* pData, Uint32 Size, Sint32 LayerCount, bool Is3DSound ) = 0;

		/**
			@brief �v���O�C���f�B���N�g���ݒ�
			@author �t���`
			@param pPath	[in] �v���O�C���f�B���N�g���̃p�X
			@note
			�X�g���[���Đ��ɗ��p����v���O�C���̌����f�B���N�g����ݒ肵�܂�
		*/
		virtual void SetPluginDirectory( const wchar_t* pPath ) = 0;

		/**
			@brief ���X�i�[�̈ʒu��ݒ�
			@author �t���`
			@param Position	[in] ���X�i�[�̈ʒu
			@note
			3D�T�E���h�̃��X�i�[�̈ʒu��ݒ肵�܂��B
		*/
		virtual void SetListenerPosition( const Kernel::Math::VectorS& Position ) = 0;

		/**
			@brief ���X�i�[�̕�����ݒ�
			@author �t���`
			@param Front	[in] ���X�i�[�̑O����
			@param Up		[in] ���X�i�[�̏����
			@note
			3D�T�E���h�̃��X�i�[�̕�����ݒ肵�܂��B
		*/
		virtual void SetListenerDirection( const Kernel::Math::VectorS& Front, const Kernel::Math::VectorS& Up ) = 0;

		/**
			@brief �T�E���h�̏������X�V����
			@author �t���`
			@note
			3D�T�E���h�Ɋւ���Čv�Z���s���܂��B
		*/
		virtual void Update() = 0;
	};
}
}
}

/**
	@file
	@brief �}�E�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief �}�E�X�Ǘ��C���^�[�t�F�C�X
		@author �t���`
		@note
		�}�E�X���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IMouse
		: public Interface
	{
	protected:
		virtual ~IMouse(){}

	public:
		/**
			@brief �}�E�X��X���W�擾
			@author �t���`
			@return X���W
			@note
			�}�E�X�|�C���^�[�̃X�N���[�����W���X���W���擾���܂��B
		*/
		virtual Sint32 GetPositionX() const = 0;

		/**
			@brief �}�E�X��Y���W�擾
			@author �t���`
			@return Y���W
			@note
			�}�E�X�|�C���^�[�̃X�N���[�����W���Y���W���擾���܂��B
		*/
		virtual Sint32 GetPositionY() const = 0;

		/**
			@brief �}�E�X��X�ړ��ʎ擾
			@author �t���`
			@return X�ړ���
			@note
			�}�E�X�|�C���^�[�̃X�N���[�����X�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveX() const = 0;

		/**
			@brief �}�E�X��Y�ړ��ʎ擾
			@author �t���`
			@return Y�ړ���
			@note
			�}�E�X�|�C���^�[�̃X�N���[�����Y�ړ��ʂ��擾���܂��B
		*/
		virtual Sint32 GetMoveY() const = 0;

		/**
			@brief �}�E�X�̍��N���b�N��Ԏ擾
			@author �t���`
			@retval false	���{�^���͉�����Ă��Ȃ�
			@retval true	���{�^���͉�����Ă���
			@note
			�}�E�X�̍��{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual bool GetClickL() const = 0;

		/**
			@brief �}�E�X�̉E�N���b�N��Ԏ擾
			@author �t���`
			@retval false	�E�{�^���͉�����Ă��Ȃ�
			@retval true	�E�{�^���͉�����Ă���
			@note
			�}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual bool GetClickR() const = 0;

		/**
			@brief �}�E�X�̃z�C�[���N���b�N��Ԏ擾
			@author �t���`
			@retval false	�z�C�[���{�^���͉�����Ă��Ȃ�
			@retval true	�z�C�[���{�^���͉�����Ă���
			@note
			�}�E�X�̃z�C�[���{�^���̏�Ԃ��擾���܂��B<BR>
			���̊֐��ł�ON/OFF�����擾�ł��܂���B
		*/
		virtual bool GetClickW() const = 0;

		/**
			@brief �}�E�X�̍��{�^����Ԏ擾
			@author �t���`
			@return		���{�^���̏��
			@note
			�}�E�X�̍��{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eButtonState GetStateL() const = 0;

		/**
			@brief �}�E�X�̉E�{�^����Ԏ擾
			@author �t���`
			@return		�E�{�^���̏��
			@note
			�}�E�X�̉E�{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eButtonState	GetStateR() const = 0;

		/**
			@brief �}�E�X�̃z�C�[���{�^����Ԏ擾
			@author �t���`
			@return		�z�C�[���{�^���̏��
			@note
			�}�E�X�̃z�C�[���{�^���̏ڍׂȏ����擾���܂��B
		*/
		virtual eButtonState	GetStateW() const = 0;

		/**
			@brief �}�E�X�̃z�C�[����]�ʎ擾
			@author �t���`
			@return		�z�C�[����]��
			@note
			�}�E�X�̃z�C�[����]�ʂ��擾���܂��B
		*/
		virtual float GetWheelRotate() const = 0;

		/**
			@brief �}�E�X�̈ʒu��ݒ�
			@author �t���`
			@param Pos	[in] �X�N���[�����W
			@note
			�}�E�X�̈ʒu��C�ӂ̏ꏊ�ɐݒ肵�܂��B
		*/
		virtual void SetPosition( Point2DI& Pos ) = 0;
	};
}
}
}

/**
	@file
	@brief �L�[�{�[�h
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief �L�[�{�[�h�Ǘ��C���^�[�t�F�C�X
		@author �t���`
		@note
		�L�[�{�[�h���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IKeyboard
		: public Interface
	{
	protected:
		virtual ~IKeyboard(){}

	public:
		/**
			@brief �L�[���̓o�b�t�@�t���b�V��
			@author �t���`
			@note
			�L�[���̓o�b�t�@�ɒ~�ς������̓o�b�t�@���N���A���܂��B
		*/
		virtual void ClearKeyBuffer() = 0;

		/**
			@brief �L�[���̓o�b�t�@����f�[�^�擾
			@author �t���`
			@return ���͂��ꂽ�L�[�̃L�[�R�[�h
			@note
			�L�[���̓o�b�t�@�ɒ~�ς��ꂽ�f�[�^�����o���܂��B<BR>
			�����ꂽ�L�[��S�Ď��o������while()�����ŏ������Ă��������B
		*/
		virtual eKeyCode GetKeyBuffer() = 0;

		/**
			@brief �L�[��������Ă��邩�`�F�b�N����
			@author �t���`
			@retval false	������Ă��Ȃ�
			@retval true	������Ă���
			@note
			�w�肳�ꂽ�L�[�����݉�����Ă��邩�`�F�b�N���܂��B<BR>
			�����ɃL�[��ON/OFF�̂ݎ擾�ł��܂��B
		*/
		virtual bool GetKeyData( eKeyCode Key ) const = 0;
	};
}
}
}

/**
	@file
	@brief �W���C�X�e�B�b�N
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief �W���C�X�e�B�b�N�Ǘ��C���^�[�t�F�C�X
		@author �t���`
		@note
		�W���C�X�e�B�b�N���������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IJoystick
		: public Interface
	{
	protected:
		virtual ~IJoystick(){}

	public:
		/**
			@brief ���𒼐ڎ擾
			@author �t���`
			@param AxisNo	[in] �����I�Ȏ��̔ԍ�
			@retval true	�����Ă���
			@retval false	�����Ă��Ȃ�
			@note
			���ڎ��̏�Ԃ��擾���܂��B
		*/
		virtual float GetAxisDirect( Uint32 AxisNo ) const = 0;

		/**
			@brief �{�^���𒼐ڎ擾
			@author �t���`
			@param ButtonNo	[in] �����I�ȃ{�^���̔ԍ�
			@retval true	�����Ă���
			@retval false	�����Ă��Ȃ�
			@note
			���ڃ{�^���̏�Ԃ��擾���܂��B
		*/
		virtual bool GetButtonDirect( Uint32 ButtonNo ) const = 0;

		/**
			@brief ���z�{�^���̓��̓��x�����擾
			@author �t���`
			@param Button	[in] ���z�{�^���̔ԍ�
			@note
			���z�{�^���̓��̓��x����0.0�`1.0�Ŏ擾���܂��B<BR>
			�ʏ�̃{�^���̏ꍇ��0.0(�����Ă��Ȃ�)��1.0(�����Ă���)�ɂȂ�<BR>
			�A�i���O�X�e�B�b�N�̏ꍇ�͂��ꂼ��̕����Œl���擾����܂��B
		*/
		virtual float GetVirtualButton( Uint32 Button ) const = 0;

		/**
			@brief ���z�{�^���̏�Ԃ��擾
			@author �t���`
			@param Button	[in] ���z�{�^���̔ԍ�
			@return �{�^���̏��
			@note
			���z�{�^���̏�Ԃ𒲂ׂ܂��B
		*/
		virtual eButtonState GetVirtualButtonState( Uint32 Button ) const = 0;

		/**
			@brief ���͂��Ă��邩�`�F�b�N
			@author �t���`
			@retval true	��؂̓��͂����Ă��Ȃ�
			@retval false	�Ȃ�炩�̓��͂����Ă���
			@note
			�Ȃ�炩�̓��͂����Ă��邩���ׂ܂��B
		*/
		virtual bool IsFree() const = 0;
	};
}
}
}

/**
	@file
	@brief ���͊ȈՑ���R���g���[���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief �R���g���[���[�̃{�^��
		@author �t���`
		@note
		�R���g���[���[�̃{�^���̒�`�B
	*/
	enum eControllerButton
	{
		CONTROLLER_BUTTON_01,				///< �{�^�� 1
		CONTROLLER_BUTTON_02,				///< �{�^�� 2
		CONTROLLER_BUTTON_03,				///< �{�^�� 3
		CONTROLLER_BUTTON_04,				///< �{�^�� 4
		CONTROLLER_BUTTON_05,				///< �{�^�� 5
		CONTROLLER_BUTTON_06,				///< �{�^�� 6
		CONTROLLER_BUTTON_07,				///< �{�^�� 7
		CONTROLLER_BUTTON_08,				///< �{�^�� 8
		CONTROLLER_BUTTON_09,				///< �{�^�� 9
		CONTROLLER_BUTTON_10,				///< �{�^��10
		CONTROLLER_BUTTON_11,				///< �{�^��11
		CONTROLLER_BUTTON_12,				///< �{�^��12
		CONTROLLER_BUTTON_13,				///< �{�^��13
		CONTROLLER_BUTTON_14,				///< �{�^��14
		CONTROLLER_BUTTON_15,				///< �{�^��15
		CONTROLLER_BUTTON_16,				///< �{�^��16
		CONTROLLER_AXIS_01_MINUIS,			///< ��1�}�C�i�X����
		CONTROLLER_AXIS_01_PLUS,			///< ��1�v���X����
		CONTROLLER_AXIS_02_MINUIS,			///< ��2�}�C�i�X����
		CONTROLLER_AXIS_02_PLUS,			///< ��2�v���X����
		CONTROLLER_AXIS_03_MINUIS,			///< ��3�}�C�i�X����
		CONTROLLER_AXIS_03_PLUS,			///< ��3�v���X����
		CONTROLLER_AXIS_04_MINUIS,			///< ��4�}�C�i�X����
		CONTROLLER_AXIS_04_PLUS,			///< ��4�v���X����
		CONTROLLER_AXIS_05_MINUIS,			///< ��5�}�C�i�X����
		CONTROLLER_AXIS_05_PLUS,			///< ��5�v���X����
		CONTROLLER_AXIS_06_MINUIS,			///< ��6�}�C�i�X����
		CONTROLLER_AXIS_06_PLUS,			///< ��6�v���X����
		CONTROLLER_AXIS_07_MINUIS,			///< ��7�}�C�i�X����
		CONTROLLER_AXIS_07_PLUS,			///< ��7�v���X����
		CONTROLLER_AXIS_08_MINUIS,			///< ��8�}�C�i�X����
		CONTROLLER_AXIS_08_PLUS,			///< ��8�v���X����
		CONTROLLER_MAX,
	};

	/**
		@brief ���̓f�o�C�X�ȈՑ���N���X
		@author �t���`
		@note
		�L�[�{�[�h�ƃp�b�h�𓝈ꂵ�Ĉ������߂̃C���^�[�t�F�C�X�ł��B
	*/
	class IInputController
		: public Interface
	{
	protected:
		virtual ~IInputController(){}

	public:
		/**
			@brief �L�[���s�[�g�ݒ�
			@author �t���`
			@param RepeatStart		[in] ���s�[�g�J�n�܂ł̃t���[����
			@param RepeatInterval	[in] ���s�[�g�̊Ԋu�t���[����
			@note
			���̓R���g���[���[�̉������ςȂ����̃L�[���s�[�g�̐ݒ���s���܂��B
		*/
		virtual void SetRepeatParameter( Sint32 RepeatStart, Sint32 RepeatInterval ) = 0;

		/**
			@brief �L�[���s�[�g�ݒ�
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@param RepeatStart		[in] ���s�[�g�J�n�܂ł̃t���[����
			@param RepeatInterval	[in] ���s�[�g�̊Ԋu�t���[����
			@note
			���̓R���g���[���[�̉������ςȂ����̃L�[���s�[�g�̐ݒ���s���܂��B<BR>
			���̃��\�b�h�Ōʂɐݒ���s��Ȃ��ꍇ��SetRepeatParameter()�ł̐ݒ肪���p����܂��B
		*/
		virtual void SetButtonRepeatParameter( eControllerButton Button, Sint32 RepeatStart, Sint32 RepeatInterval ) = 0;

		/**
			@brief ���z�{�^���̃A�^�b�`
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@param VirtualButton	[in] �A�^�b�`���鉼�z�L�[
			@note
			�Q�[���p�b�h�̉��z�{�^������̓R���g���[���[�̃{�^���ɃA�^�b�`���܂��B
		*/
		virtual void AttachGamepadVirtualButton( eControllerButton Button, Uint32 VirtualButton ) = 0;

		/**
			@brief �L�[�{�[�h�̃A�^�b�`
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@param KeyCode			[in] �A�^�b�`����L�[
			@note
			�L�[�{�[�h�̃L�[����̓R���g���[���[�̃{�^���ɃA�^�b�`���܂��B
		*/
		virtual void AttachKeyboard( eControllerButton Button, eKeyCode KeyCode ) = 0;

		/**
			@brief ���z�{�^���̃A�^�b�`����
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@param VirtualButton	[in] �A�^�b�`�������鉼�z�L�[
			@note
			�Q�[���p�b�h�̉��z�{�^������̓R���g���[���[�̃{�^���̃A�^�b�`�������܂��B
		*/
		virtual void DetachGamepadVirtualButton( eControllerButton Button, Uint32 VirtualButton ) = 0;

		/**
			@brief �L�[�{�[�h�̃A�^�b�`����
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@param KeyCode			[in] �A�^�b�`��������L�[
			@note
			�L�[�{�[�h�̃L�[����̓R���g���[���[�̃{�^���̃A�^�b�`�������܂��B
		*/
		virtual void DetachKeyboard( eControllerButton Button, eKeyCode KeyCode ) = 0;

		/**
			@brief �t���[��Ԃ����擾
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@retval true	�����Ă��Ȃ�
			@retval false	�����Ă���
			@note
			�w��{�^�����������ςȂ��̏�Ԃ��ǂ������擾���܂��B
		*/
		virtual bool IsFree( eControllerButton Button ) const = 0;

		/**
			@brief �������u�Ԃ����擾
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@retval true	���̃t���[���ŉ����ꂽ
			@retval false	������ĂȂ�
			@note
			�w��{�^�������܂̃t���[���ŉ����ꂽ�����擾���܂��B
		*/
		virtual bool IsPull( eControllerButton Button ) const = 0;

		/**
			@brief �������u�Ԃ����擾
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@retval true	���̃t���[���ŉ����ꂽ
			@retval false	������ĂȂ�
			@note
			�w��{�^�������܂̃t���[���ŉ����ꂽ�����擾���܂��B
		*/
		virtual bool IsPush( eControllerButton Button ) const = 0;

		/**
			@brief �z�[���h��Ԃ����擾
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@retval true	�������ςȂ�
			@retval false	�����Ă��Ȃ�
			@note
			�w��{�^�����������ςȂ��̏�Ԃ��ǂ������擾���܂��B
		*/
		virtual bool IsHold( eControllerButton Button ) const = 0;

		/**
			@brief ���͒l���擾
			@author �t���`
			@param Button			[in] �R���g���[���[�̃{�^��
			@note
			�w��{�^���̓��͒l���A�i���O�Ŏ擾���܂��B<BR>
			�l��0.0����1.0�̒l�Ŏ擾�ł��܂��B<BR>
			�{�^���Ƃ��Ă̈����Ȃ̂Ŏ������ꂼ��̕����ɑ΂���0.0�`1.0�Ŏ擾����܂��B
		*/
		virtual float GetPower( eControllerButton Button ) const = 0;
	};
}
}
}

/**
	@file
	@brief ���̓f�o�C�X�}�l�[�W���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Input
{
	/**
		@brief ���̓f�o�C�X�Ǘ��N���X
		@author �t���`
		@note
		���̓f�o�C�X�֌W�̃}�l�[�W���[
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief ���͏��X�V
			@author �t���`
			@note
			���͏�񂩂�ŐV�̏�Ԃ֍X�V���܂��B<BR>
			�K���P�t���[���ɂP��ĂԂ悤�ɂ��ĉ������B
		*/
		virtual void Update() = 0;

		/**
			@brief �W���C�X�e�B�b�N���擾
			@author �t���`
			@return �W���C�X�e�B�b�N��
			@note
			���p�\�ȃW���C�X�e�B�b�N�̐����擾���܂�
		*/
		virtual Sint32 GetJoystickCount() const = 0;

		/**
			@brief �W���C�X�e�B�b�N�ԍ��擾
			@author �t���`
			@param GuidInstance		[in] �C���X�^���X
			@param GuidProduct		[in] �v���_�N�g
			@return �W���C�X�e�B�b�N�ԍ�
			@note
			GUID����v����W���C�X�e�B�b�N�̔ԍ���Ԃ��܂��B<BR>
			�Ȃ����-1�ɂȂ�܂��B
		*/
		virtual Sint32 GetJoystickIndex( const GUID& GuidInstance, const GUID& GuidProduct ) const = 0;

		/**
			@brief �W���C�X�e�B�b�N�p�C���^�[�t�F�C�X�擾
			@author �t���`
			@param No	[in] �W���C�X�e�B�b�N�ԍ�
			@return IJoystick�C���^�[�t�F�C�X
			@note
			�W���C�X�e�B�b�N����p�̃C���^�[�t�F�C�X���擾���܂�
		*/
		virtual IJoystick* GetJoystick( Sint32 No ) = 0;

		/**
			@brief �L�[�{�[�h�p�C���^�[�t�F�C�X�擾
			@author �t���`
			@return IKeyboard�C���^�[�t�F�C�X
			@note
			�L�[�{�[�h����p�̃C���^�[�t�F�C�X���擾���܂�
		*/
		virtual IKeyboard* GetKeyboard() = 0;

		/**
			@brief �}�E�X�p�C���^�[�t�F�C�X�擾
			@author �t���`
			@return IMouse�C���^�[�t�F�C�X
			@note
			�}�E�X����p�̃C���^�[�t�F�C�X���擾���܂�
		*/
		virtual IMouse* GetMouse() = 0;

		/**
			@brief ���͐���p�C���^�[�t�F�C�X�擾
			@author �t���`
			@param No		[in] ���͂Ɏg���W���C�X�e�B�b�N�̔ԍ�
			@return IInputController�C���^�[�t�F�C�X
			@note
			���͐��䑀��p�̃C���^�[�t�F�C�X���擾���܂�
		*/
		virtual IInputController* CreateInputController( Sint32 No ) = 0;
	};
}
}
}

/**
	@file
	@brief �{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �{�f�B
		@author �t���`
	*/
	class IBody
		: public Interface
	{
	protected:
		virtual ~IBody(){}

	public:
		/**
			@brief �����f�[�^�̎擾
			@author �t���`
			@return �����f�[�^
			@note
			�����ŗ��p���Ă������ȃf�[�^���擾���܂��B<BR>
			��������[�U�[�����p���鎖�͂���܂���B
		*/
		virtual void* GetInstance() = 0;
		/**
			@brief �{�f�B�^�C�v�擾
			@author �t���`
			@return �{�f�B�^�C�v
			@note
			�{�f�B�̃^�C�v���擾���܂��B
		*/
		virtual eBodyType GetBodyType() = 0;
		/**
			@brief ���[�U�[�|�C���^�[�擾
			@author �t���`
			@return ���[�U�[���ݒ肵���|�C���^�[
			@note
			���[�U�[���ݒ肵���|�C���^�[���擾���܂��B
		*/
		virtual void* GetUserData() = 0;
		/**
			@brief ���[�U�[�|�C���^�[�ݒ�
			@author �t���`
			@param pData	[in] ���[�U�[��`�̃|�C���^�[
			@note
			���[�U�[��`�̃|�C���^�[��ݒ肵�܂��B
		*/
		virtual void SetUserData( void* pData ) = 0;
		/**
			@brief �f�o�b�O�p�`��f�[�^����
			@author �t���`
			@param Color	[in] �`��̐F
			@note
			�f�o�b�O�`��ŗ��p����`��f�[�^�𐶐����܂��B
		*/
		virtual void CreateDebugShape( const ColorF& Color ) = 0;
		/**
			@brief �ڐG�{�f�B���擾
			@author �t���`
			@return �ڐG�{�f�B��
			@note
			�ڐG���Ă���{�f�B�̐����擾���܂��B
		*/
		virtual Uint32 GetContactCount() = 0;
		/**
			@brief �ڐG�{�f�B�擾
			@author �t���`
			@param Index	[in] �ڐG�{�f�B�̃C���f�b�N�X
			@return �ڐG���Ă���{�f�B�̏��
			@note
			�ڐG���Ă���{�f�B�̃C���f�b�N�X���擾���܂��B
		*/
		virtual const SContactInfo& GetContactBody( Uint32 Index ) = 0;
		/**
			@brief �ڐG���R�[���o�b�N�C�x���g�ݒ�
			@author �t���`
			@param Event	[in] �ڐG���R�[���o�b�N�C�x���g
			@note
			�ڐG���̃R�[���o�b�N�C�x���g��ݒ肵�܂��B
		*/
		virtual void SetContactEvent( const Kernel::Delegate02<Body::IBody*, const SContactInfo&>& Event ) = 0;
		/**
			@brief ���[���h�s��擾
			@author �t���`
			@return ���[���h�s��
			@note
			�{�f�B�̃��[���h�s����擾���܂��B
		*/
		virtual const Kernel::Math::Matrix& GetWorldMatrix() const = 0;
		/**
			@brief �_�C�i�~�N�X�p�}�l�[�W���[�擾
			@author ����
			@return �_�C�i�~�N�X�p�}�l�[�W���[
			@note
			�_�C�i�~�N�X�p�}�l�[�W���[���擾���܂��B
		*/
		virtual IManager* GetManager() = 0;
	};
}
}
}
}
/**
	@file
	@brief ��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	class IDynamicsBody
		: public IBody
	{
	protected:
		virtual ~IDynamicsBody(){}

	public:
		/**
			@brief �ڐG�����ݒ�
			@author �t���`
			@note
			�ڐG���̉����𖳌��ɂ��܂��B<BR>
			�������Ȃ��{�f�B�̓R���W�����̔����͂��܂���<BR>
			�Ԃ��������̕����V�~�����[�V�������s���܂���B
		*/
		virtual void SetNoContactResponseObject() = 0;

		/**
			@brief �L�l�}�e�B�N�X�ݒ�
			@author �t���`
			@note
			�L�l�}�e�B�N�X�I�u�W�F�N�g�����܂��B
		*/
		virtual void SetKinematicsObject() = 0;

		/**
			@brief ��ԃ��Z�b�g
			@author �t���`
			@param Position	[in] �ʒu
			@param Rotation	[in] �p�x
			@note
			�����V�~�����[�V������Ԃ����Z�b�g���܂��B
		*/
		virtual void ResetAll( const Kernel::Math::VectorS& Position, const Kernel::Math::VectorS& Rotation ) = 0;
		/**
			@brief �ʒu���ڐݒ�
			@author �t���`
			@param Position	[in] �ʒu
			@note
			���[���h���W�𒼐ڎw�肵�Ĉʒu���ړ����܂��B
		*/
		virtual void SetPosition( const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief �ړ����x�ݒ�
			@author �t���`
			@param Velocity	[in] �ړ����x
			@note
			�ʏ�Appl��Force�ŗ͂�^�������ʂƂ���Velocity�����܂�܂���<BR>
			����𖳎����Ē��ڃ{�f�B�ɑ��x��^�����܂��B
		*/
		virtual void SetLinearVelocity( const Kernel::Math::VectorS& Velocity ) = 0;
		/**
			@brief ��]���x�ݒ�
			@author �t���`
			@param Velocity	[in] ��]���x
			@note
			�ʏ�Appl��Force�ŗ͂�^�������ʂƂ���Velocity�����܂�܂���<BR>
			����𖳎����Ē��ڃ{�f�B�ɑ��x��^�����܂��B
		*/
		virtual void SetAngularVelocity( const Kernel::Math::VectorS& Velocity ) = 0;
		/**
			@brief �ړ����x�W���ݒ�
			@author �t���`
			@param Factor	[in] �W��
			@note
			�ړ����x��Velocity�ɑ΂��ď�Z����W����ݒ肵�܂��B<BR>
			���Ƃ���z=0.0�ɂ����XY���ʏ�ł̈ړ��������Ȃ��Ȃ�܂��B
		*/
		virtual void SetLinearFactor( const Kernel::Math::VectorS& Factor ) = 0;
		/**
			@brief ��]���x�W���ݒ�
			@author �t���`
			@param Factor	[in] �W��
			@note
			��]���x��Velocity�ɑ΂��ď�Z����W����ݒ肵�܂��B<BR>
			���Ƃ���xy=0.0�ɂ����z����ł̉�]�������Ȃ��Ȃ�܂��B
		*/
		virtual void SetAngularFactor( const Kernel::Math::VectorS& Factor ) = 0;
		/**
			@brief �ړ����x�擾
			@author �t���`
			@param �ړ����x
			@note
			�V�~�����[�V������̈ړ��̑��x���擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetLinearVelocity() const = 0;
		/**
			@brief ��]���x�擾
			@author �t���`
			@param ��]���x
			@note
			�V�~�����[�V������̉�]�̑��x���擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetAngularVelocity() const = 0;
		/**
			@brief �ړ����x�W���擾
			@author �t���`
			@param �ړ����x�W��
			@note
			�V�~�����[�V������̈ړ��̑��x�ւ̌W�����擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetLinearFactor() const = 0;
		/**
			@brief ��]���x�W���擾
			@author �t���`
			@param ��]���x�W��
			@note
			�V�~�����[�V������̉�]�̑��x�ւ̌W�����擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetAngularFactor() const = 0;
		/**
			@brief ���˗��ݒ�
			@author �t���`
			@param Value	[in] ���˗�
			@note
			�{�f�B�̔��˗���ݒ肵�܂��B
		*/
		virtual void SetRestitution( float Value ) = 0;
		/**
			@brief ���˗��擾
			@author �t���`
			@return ���˗�
			@note
			�{�f�B�̔��˗����擾���܂��B
		*/
		virtual float GetRestitution() const = 0;
		/**
			@brief ���C�W���ݒ�
			@author �t���`
			@param Value	[in] ���C�W��
			@note
			�{�f�B�̖��C�W����ݒ肵�܂��B
		*/
		virtual void SetFriction( float Value ) = 0;
		/**
			@brief ���C�W���擾
			@author �t���`
			@return ���C�W��
			@note
			�{�f�B�̖��C�W�����擾���܂��B
		*/
		virtual float GetFriction() const = 0;
		/**
			@brief �d�͐ݒ�
			@author ����
			@param Gravity	[in] �d��
			@note
			�{�f�B�ɂ�����d�͂�ݒ肵�܂��B
		*/
		virtual void SetGravity( const Kernel::Math::VectorS& Gravity ) = 0;
		/**
			@brief �d�͎擾
			@author ����
			@return �d��
			@note
			�{�f�B�ɂ�����d�͂��擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetGravity() = 0;
		/**
			@brief �{�f�B�ɗ͂�������
			@author �t���`
			@param Force	[in] ��
			@param Position	[in] �͂�������ʒu
			@note
			�{�f�B�ɗ͂������ĕ����V�~�����[�V�����œ������܂��B
		*/
		virtual void ApplyForce( const Kernel::Math::VectorS& Force, const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief ��]�͎擾
			@author ����
			@return ��]��
			@note
			�{�f�B�ɏd�S�ɂ������Ă����]�͂��擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetTotalTorque() = 0;
		/**
			@brief �͎擾
			@author ����
			@return ��
			@note
			�{�f�B�ɏd�S�ɂ������Ă���͂��擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetTotalForce() = 0;
		/**
			@brief �{�f�B�ɗ͂�������
			@author ����
			@param Torque	[in] ��
			@note
			�{�f�B�ɏd�S�ɉ�]�͂������ĕ����V�~�����[�V�����œ������܂��B
		*/
		virtual void ApplyTorque( const Kernel::Math::VectorS & Torque ) = 0;
		/**
			@brief �{�f�B�ɗ͂�������
			@author ����
			@param Force	[in] ��
			@note
			�{�f�B�ɏd�S�ɗ͂������ĕ����V�~�����[�V�����œ������܂��B
		*/
		virtual void ApplyCentralForce( const Kernel::Math::VectorS & Force ) = 0;
		/**
			@brief �ő嗎�����x�ݒ�
			@author �t���`
			@param Speed	[in] �������x
			@note
			�ő嗎�����x��ݒ肵�܂��B<BR>
			-1���w�肷��Əd�͂ɂ�薳���ɉ������Ă����܂��B
		*/
		virtual void SetMaxFalloffSpeed( float Speed ) = 0;
		/**
			@brief �ő�ړ����x�ݒ�
			@param Speed	[in] �ړ����x
			@note
			�ő�ړ����x��ݒ肵�܂��B<BR>
			�w��͂P�b�Ԃ̈ړ����x�ɂȂ�܂��B
		*/
		virtual void SetMaxMoveSpeed( float Speed ) = 0;
		/**
			@brief �����ݒ�
			@author �t���`
			@param Linear		[in] �ړ�����
			@param Angulate	[in] ��]����
			@note
			�����V�~�����[�V�������̌�����ݒ肵�܂��B
		*/
		virtual void SetDamping( float Linear, float Angulate ) = 0;
	};
}
}
}
}
/**
	@file
	@brief �����{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �����{�f�B
		@author �t���`
	*/
	class ICompound
		: public IDynamicsBody
	{
	protected:
		virtual ~ICompound(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief ���b�V���{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ���b�V���{�f�B
		@author �t���`
	*/
	class ITriMesh
		: public IDynamicsBody
	{
	protected:
		virtual ~ITriMesh(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �������ʃC���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ��������
		@author �t���`
	*/
	class IPlane
		: public IDynamicsBody
	{
	protected:
		virtual ~IPlane(){}

	public:
		/**
			@brief ���C�W���ݒ�
			@author �t���`
			@param Value	[in] ���C�W��
			@note
			�{�f�B�̖��C�W����ݒ肵�܂��B
		*/
		virtual void SetRestitution( float Value ) = 0;
		/**
			@brief ���C�W���擾
			@author �t���`
			@return ���C�W��
			@note
			�{�f�B�̖��C�W�����擾���܂��B
		*/
		virtual float GetRestitution() const = 0;
		/**
			@brief ���˗��ݒ�
			@author �t���`
			@param Value	[in] ���˗�
			@note
			�{�f�B�̔��˗���ݒ肵�܂��B
		*/
		virtual void SetFriction( float Value ) = 0;
		/**
			@brief ���˗��擾
			@author �t���`
			@return ���˗�
			@note
			�{�f�B�̔��˗����擾���܂��B
		*/
		virtual float GetFriction() const = 0;
	};
}
}
}
}

/**
	@file
	@brief ���{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ���{�f�B
		@author �t���`
	*/
	class IBox
		: public IDynamicsBody
	{
	protected:
		virtual ~IBox(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �J�v�Z���{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �J�v�Z���{�f�B
		@author �t���`
	*/
	class ICapsule
		: public IDynamicsBody
	{
	protected:
		virtual ~ICapsule(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �L�����N�^�N���X
	@author ����
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �L�����N�^�N���X
		@author ����
		@note
		�L�����N�^�N���X
	*/
	class ICharaProxy
		: public IDynamicsBody
	{
	protected:
		virtual ~ICharaProxy(){}

	public:
	
		/**
			@brief �ڒn�`�F�b�N
			@author ����
			@note
			�{�f�B���n�ʂɐݒu���Ă��邩�ǂ������`�F�b�N���܂��B<BR>
			�������̒��n�̔����ł킸���ɕ������肷��̂�<BR>
			�^�C�~���O��}��Ȃǂ̍H�v���K�v�ȏꍇ������܂��B
		*/
		virtual bool IsFitGround() const = 0;
		/**
			@brief �ڒn�ʂ̖@���擾
			@author ����
			@return �ڒn�ӏ��̖@��
			@note
			�ڒn���Ă���ӏ��̖@�����擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetGroundNormal() = 0;
		/**
			@brief �S���擾
			@author ����
			@return �S������Ă��邩�H
			@note
			�ڒn���A���̃I�u�W�F�N�g�ɍS������Ă��邩���擾���܂��B
		*/
		virtual bool IsConstraint() = 0;
		/**
			@brief �S�����x�擾
			@author ����
			@return �S�����Ă��镨�̂̑��x
			@note
			�S�����Ă��镨�̂̑��x���擾���܂��B<BR>
			���������̏ꍇ�A���̑����ƕ��̂ɉ����Ȃ��Ə��Ƃ���邱�ƂɂȂ�܂��B
		*/
		virtual Kernel::Math::VectorS GetConstraintVelocity() = 0;
		/**
			@brief �X�V�C�x���g�ݒ�
			@author ����
			@param Event			[in] �X�V�C�x���g
			@note
			���t���[�����Ƃ̈ړ���]�Ȃǂ̍X�V�������s���֐���ݒ肵�܂��B<BR>
			Delegate�́uICharaProxy*�v�͍X�V����Ώۂ̃L�����N�^�N���X�ł��B
		*/
		virtual void SetPreUpdateEvent( const Kernel::Delegate01<ICharaProxy*>& Event ) = 0;
		/**
			@brief ����C�x���g�ݒ�
			@author ����
			@param Event			[in] ����C�x���g
			@note
			�N���X���폜�����Ƃ��Ɏ��s�����֐���ݒ�܂��B<BR>
			Delegate�́uICharaProxy*�v�͍폜�����Ώۂ̃L�����N�^�N���X�ł��B
		*/
		virtual void SetReleaseEvent( const Kernel::Delegate01<ICharaProxy*>& Event ) = 0;
		/**
			@brief �ڒn�C�x���g�ݒ�
			@author ����
			@param Event			[in] �ڒn�C�x���g
			@note
			�������̂ƏՓ˂����Ƃ��ɁA�����ڒn�Ƃ��Ĉ������ǂ������w�肷��֐���ݒ肵�܂��B<BR>
			Delegate�́uICharaProxy*�v�͐ڒn����Ώۂ̃L�����N�^�N���X�ł��B<BR>
			�uIBody*�v�͏Փ˂����{�f�B�N���X�ł��B<BR>
			�uconst Kernel::Math::VectorS&�v�͏Փ˂��������̖@���ł��B<BR>
			�ubool&�v��true��������Ɛڒn�������ƂɂȂ�܂��B
		*/
		virtual void SetFitGroundEvent( const Kernel::Delegate04<ICharaProxy*, IBody*, const Kernel::Math::VectorS&, bool&>& Event ) = 0;
		/**
			@brief �ڒn�ʂ̖@���ݒ�C�x���g�ݒ�
			@author ����
			@param Event			[in] �ڒn�ʂ̖@���ݒ�C�x���g
			@note
			�������̂ƏՓ˂����Ƃ��ɁA�ڒn�ʂ̖@�����ǂ���������ݒ肷��֐���ݒ肵�܂��B<BR>
			Delegate�́uICharaProxy*�v�͐ڒn����Ώۂ̃L�����N�^�N���X�ł��B<BR>
			�uIBody*�v�͏Փ˂����{�f�B�N���X�ł��B<BR>
			�uconst Kernel::Math::VectorS&�v�͏Փ˂��������̖@���ł��B<BR>
			�uKernel::Math::VectorS&�v�ɐڒn�ʂ������܂��B
		*/
		virtual void SetSetGroundNormalEvent( const Kernel::Delegate04<ICharaProxy*, IBody*, const Kernel::Math::VectorS&, Kernel::Math::VectorS&>& Event ) = 0;
		/**
			@brief ���[���h�s��ݒ�
			@author ����
			@param mat		[in] ���[���h�s��
			@note
			�{�f�B�̃��[���h�s���ݒ肵�܂��B
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mat ) = 0;
		/**
			@brief �ʒu�擾
			@author ����
			@return �ʒu
			@note
			���[���h���W���擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetPosition() = 0;
		/**
			@brief �쓮
			@author ����
			@note
			���x�A��]�Ȃǂ�ύX������Ɏ��s���܂��B
		*/
		virtual void Activate() = 0;
		/**
			@brief ���a�擾
			@author ����
			@return ���a
			@note
			���A�J�v�Z���̔��a���擾���܂��B
		*/
		virtual float GetRadius() = 0;
		/**
			@brief �����擾
			@author ����
			@return ���a
			@note
			�J�v�Z���̒������擾���܂��B
		*/
		virtual float GetLength() = 0;

		/**
			@brief ���[�U�[�|�C���^�[�擾
			@author ����
			@return ���[�U�[���ݒ肵���|�C���^�[
			@note
			���[�U�[���ݒ肵���|�C���^�[���擾���܂��B<BR>
			Get/SetUserData�Ƃ͕ʂ̃|�C���^���g�p���Ă��܂��B
		*/
		virtual void* GetUserCharaData() = 0;

		/**
			@brief ���[�U�[�|�C���^�[�ݒ�
			@author ����
			@param pData	[in] ���[�U�[��`�̃|�C���^�[
			@note
			���[�U�[��`�̃|�C���^�[��ݒ肵�܂��B<BR>
			Get/SetUserData�Ƃ͕ʂ̃|�C���^���g�p���Ă��܂��B
		*/
		virtual void SetUserCharaData( void* pData ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �ȈՃL�����N�^�N���X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �ȈՃL�����N�^�N���X
		@author �t���`
		@note
		�ȈՃL�����N�^
	*/
	class ICharaProxySimple
		: public IBody
	{
	protected:
		virtual ~ICharaProxySimple(){}

	public:
		/**
			@brief �ڒn�`�F�b�N
			@author �t���`
			@note
			�{�f�B���n�ʂɐݒu���Ă��邩�ǂ������`�F�b�N���܂��B<BR>
			�������̒��n�̔����ł킸���ɕ������肷��̂�<BR>
			�^�C�~���O��}��Ȃǂ̍H�v���K�v�ȏꍇ������܂��B
		*/
		virtual bool IsFitGround() const = 0;
		/**
			@brief �ڒn�ʂ̖@���擾
			@author �t���`
			@return �ڒn�ӏ��̖@��
			@note
			�ڒn���Ă���ӏ��̖@�����擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetGroundNormal() = 0;
		/**
			@brief �W�����v����
			@author �t���`
			@param Value	[in] �W�����v��
			@note
			�{�f�B�ɏ�����i���{�j�ɗ͂������ăW�����v�̏������s���܂��B
		*/
		virtual void Jump( float Value ) = 0;
		/**
			@brief �ړ�
			@author �t���`
			@note
			�{�f�B��XZ���ʏ�ňړ�������悤�ɂ��܂��B<BR>
			��Ȃǂɂ��ړ��ʂ̕␳�͎����ōs���܂��̂�<BR>
			�ŏI�I�ɂ͎w�肵���x�N�g����
		*/
		virtual void MoveXZ( const Kernel::Math::VectorS& Move ) = 0;
		/**
			@brief �ő嗎�����x�ݒ�
			@author �t���`
			@param Speed	[in] �������x
			@note
			�ő嗎�����x��ݒ肵�܂��B<BR>
			-1���w�肷��Əd�͂ɂ�薳���ɉ������Ă����܂��B
		*/
		virtual void SetMaxFalloffSpeed( float Speed ) = 0;
		/**
			@brief �ő�ړ����x�ݒ�
			@param Speed	[in] �ړ����x
			@note
			�ő�ړ����x��ݒ肵�܂��B<BR>
			�w��͂P�b�Ԃ̈ړ����x�ɂȂ�܂��B
		*/
		virtual void SetMaxMoveSpeed( float Speed ) = 0;
		/**
			@brief �ʒu���ڐݒ�
			@author �t���`
			@param Position	[in] �ʒu
			@note
			���[���h���W�𒼐ڎw�肵�Ĉʒu���ړ����܂��B
		*/
		virtual void SetPosition( const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief �d�͐ݒ�
			@author ����
			@param Gravity	[in] �d��
			@note
			�{�f�B�ɂ�����d�͂�ݒ肵�܂��B
		*/
		virtual void SetGravity( const Kernel::Math::VectorS& Gravity ) = 0;
		/**
			@brief �d�͎擾
			@author ����
			@return �d��
			@note
			�{�f�B�ɂ�����d�͂��擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetGravity() = 0;
	};
}
}
}
}

/**
	@file
	@brief ���{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ���{�f�B
		@author �t���`
	*/
	class ISphere
		: public IDynamicsBody
	{
	protected:
		virtual ~ISphere(){}

	public:
	};
}
}
}
}
/**
	@file
	@brief �g���K�[�{�b�N�X�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �g���K�[�{�b�N�X
		@author �t���`
	*/
	class ITriggerBox
		: public IBody
	{
	protected:
		virtual ~ITriggerBox(){}

	public:
		/**
			@brief �g���K�[�{�b�N�X�ɖ��O��ݒ�
			@author �t���`
			@param pName	[in] ���O
			@note
			�g���K�[�{�b�N�X�ɑ΂��Ė��O��ݒ肵�܂��B
		*/
		virtual void SetName( const char* pName ) = 0;
		/**
			@brief �g���K�[�{�b�N�X�̖��O���擾
			@author �t���`
			@return ���O
			@note
			�g���K�[�{�b�N�X���疼�O���擾���܂��B
		*/
		virtual const char* GetName() = 0;
		/**
			@brief �g���K�[�{�b�N�X�̖��O�`�F�b�N
			@author �t���`
			@param pName	[in] ���O
			@retval true	���ꖼ�̂ł���
			@retval false	���ꖼ�̂ł͂Ȃ�
			@note
			�g���K�[�{�b�N�X���w�肳�ꂽ���̂��ǂ����`�F�b�N���܂��B
		*/
		virtual bool IsName( const char* pName ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �\�t�g�{�f�B
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	class ISoftBody
		: public IBody
	{
	protected:
		virtual ~ISoftBody(){}

	public:
	};
}
}
}
}
/**
	@file
	@brief ���[�v�{�f�B�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief ���[�v�{�f�B
		@author �t���`
	*/
	class IRope
		: public ISoftBody
	{
	protected:
		virtual ~IRope(){}

	public:
		virtual void ConnentFrom( Body::IBody* pBody ) = 0;
		virtual void ConnentTo( Body::IBody* pBody ) = 0;
		virtual void DrawDebugShape( Engine::Graphics::Simple::ILineRenderer* pLine ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �Փ˔���
	@author ����
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	class ICollisionBody
		: public IBody
	{
	protected:
		virtual ~ICollisionBody(){}

	public:
		/**
			@brief ���[���h�s��ݒ�
			@author ����
			@param mat		[in] ���[���h�s��
			@note
			�{�f�B�̃��[���h�s���ݒ肵�܂��B
		*/
		virtual void SetWorldMatrix( const Kernel::Math::Matrix& mat ) = 0;
		/**
			@brief �ʒu���ڐݒ�
			@author ����
			@param Position	[in] �ʒu
			@note
			���[���h���W�𒼐ڎw�肵�Ĉʒu���ړ����܂��B
		*/
		virtual void SetPosition( const Kernel::Math::VectorS& Position ) = 0;
		/**
			@brief �Փ˔���
			@author ����
			@param value		[in] �L�����ǂ���
			@note
			�Փ˔��肪�L�����ǂ����ݒ肵�܂��B
		*/
		virtual void SetHit( bool value ) = 0;

		/**
			@brief �Փ˔���
			@author ����
			@return value		�L�����ǂ���
			@note
			�Փ˔��肪�L�����ǂ����擾���܂��B
		*/
		virtual bool GetHit() = 0;
	};
}
}
}
}
/**
	@file
	@brief �Փ˔���p�J�v�Z���{�f�B�C���^�[�t�F�C�X
	@author ����
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �Փ˔���p�J�v�Z���{�f�B
		@author ����
	*/
	class ICollisionCapsule
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionCapsule(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �Փ˔���p���{�f�B�C���^�[�t�F�C�X
	@author ����
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �Փ˔���p���{�f�B
		@author ����
	*/
	class ICollisionSphere
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionSphere(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �Փ˔���p���{�f�B�C���^�[�t�F�C�X
	@author ����
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �Փ˔���p���{�f�B
		@author ����
	*/
	class ICollisionBox
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionBox(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �Փ˔���p���b�V���{�f�B�C���^�[�t�F�C�X
	@author ����
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Body
{
	/**
		@brief �Փ˔���p���b�V���{�f�B
		@author ����
	*/
	class ICollisionTriMesh
		: public ICollisionBody
	{
	protected:
		virtual ~ICollisionTriMesh(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �W���C���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief �W���C���g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IJoint
		: public Interface
	{
	protected:
		virtual ~IJoint(){}

	public:
		virtual float GetAppliedImpulse() const = 0;
	};
}
}
}
}

/**
	@file
	@brief �q���W�W���C���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief �q���W�W���C���g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IHingeJoint
		: public IJoint
	{
	protected:
		virtual ~IHingeJoint(){}

	public:
		virtual void SetAngularOnly( bool IsAngularOnly ) = 0;
		virtual void EnableAngularMotor( bool IsMotor, float TargetVelocity, float MaxMotorImpulse ) = 0;
		virtual void EnableMotor( bool IsMotor ) = 0;
		virtual void SetMaxMotorImpulse( float MaxMotorImpulse ) = 0;
		virtual void SetMotorTarget( const Kernel::Math::Quaternion& AinB, float DeltaTime ) = 0;
		virtual void SetMotorTarget( float TargetAngle, float DeltaTime ) = 0;
		virtual void SetLimit( float Low, float High, float Softness = 0.9f, float BiasFactor = 0.3f, float RelaxationFactor = 1.0f ) = 0;
		virtual void SetAxis( const Kernel::Math::VectorS& AxisInA ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �X���C�_�[�W���C���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief �X���C�_�[�W���C���g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class ISliderJoint
		: public IJoint
	{
	protected:
		virtual ~ISliderJoint(){}

	public:
		/**
			@brief �ړ������ݒ�
			@author �t���`
			@param Value	[in] �ړ������l
			@note
			�X���C�_�[�̈ړ��ʂ̉���
		*/
		virtual void SetLowerLinLimit( float Value ) = 0;
		/**
			@brief �ړ�����ݒ�
			@author �t���`
			@param Value	[in] �ړ�����l
			@note
			�X���C�_�[�̈ړ��ʂ̏��
		*/
		virtual void SetUpperLinLimit( float Value ) = 0;
		/**
			@brief ��]�����ݒ�
			@author �t���`
			@param Value	[in] ��]�p�x����
			@note
			�X���C�_�[�̉�]�p�x�̉���
		*/
		virtual void SetLowerAngLimit( float Value ) = 0;
		/**
			@brief ��]����ݒ�
			@author �t���`
			@param Value	[in] ��]�p�x���
			@note
			�X���C�_�[�̉�]�p�x�̏��
		*/
		virtual void SetUpperAngLimit( float Value ) = 0;
		/**
			@brief ���[�^�[��ON/OFF�ݒ�
			@author �t���`
			@param IsEnable	[in] ON/OFF
			@note
			���[�^�[�ɂ��쓮��ON/OFF�ݒ�
		*/
		virtual void SetPoweredLinMotor( bool IsEnable ) = 0;
		/**
			@brief ���[�^�[�̍ő�g���N�ݒ�
			@author �t���`
			@param Value	[in] �g���N�l
			@note
			���[�^�[�̍ő�g���N�ݒ�
		*/
		virtual void SetMaxLinMotorForce( float Value ) = 0;
		/**
			@brief ���[�^�[�̉����x�ݒ�
			@author �t���`
			@param Value	[in] �����x
			@note
			���[�^�[�̉����x�ݒ�
		*/
		virtual void SetTargetLinMotorVelocity( float Value ) = 0;

		virtual float GetSoftnessDirLin() = 0;
		virtual float GetRestitutionDirLin() = 0;
		virtual float GetDampingDirLin() = 0;
		virtual float GetSoftnessDirAng() = 0;
		virtual float GetRestitutionDirAng() = 0;
		virtual float GetDampingDirAng() = 0;
		virtual float GetSoftnessLimLin() = 0;
		virtual float GetRestitutionLimLin() = 0;
		virtual float GetDampingLimLin() = 0;
		virtual float GetSoftnessLimAng() = 0;
		virtual float GetRestitutionLimAng() = 0;
		virtual float GetDampingLimAng() = 0;
		virtual float GetSoftnessOrthoLin() = 0;
		virtual float GetRestitutionOrthoLin() = 0;
		virtual float GetDampingOrthoLin() = 0;
		virtual float GetSoftnessOrthoAng() = 0;
		virtual float GetRestitutionOrthoAng() = 0;
		virtual float GetDampingOrthoAng() = 0;
	};
}
}
}
}

/**
	@file
	@brief �|�C���g�W���C���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	/**
		@brief �|�C���g�W���C���g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IPointJoint
		: public IJoint
	{
	protected:
		virtual ~IPointJoint(){}

	public:
	};
}
}
}
}

/**
	@file
	@brief �X���C�_�[�W���C���g
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
namespace Joint
{
	enum eDofSpringJoint
	{
		JOINT_DOF_TRANSLATION_X,	// 0 : translation X
		JOINT_DOF_TRANSLATION_Y,	// 1 : translation Y
		JOINT_DOF_TRANSLATION_Z,	// 2 : translation Z
		JOINT_DOF_ROTATION_X,		// 3 : rotation X (3rd Euler rotational around new position of X axis, range [-PI+epsilon, PI-epsilon] )
		JOINT_DOF_ROTATION_Y,		// 4 : rotation Y (2nd Euler rotational around new position of Y axis, range [-PI/2+epsilon, PI/2-epsilon] )
		JOINT_DOF_ROTATION_Z,		// 5 : rotation Z (1st Euler rotational around Z axis, range [-PI+epsilon, PI-epsilon] )
		JOINT_DOF_MAX,
	};

	/**
		@brief �X���C�_�[�W���C���g�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IDofSpringJoint
		: public IJoint
	{
	protected:
		virtual ~IDofSpringJoint(){}

	public:
		virtual void EnableSpring( Sint32 Index, bool IsEnable ) = 0;
		virtual void SetStiffness( Sint32 Index, float Stiffness ) = 0;
		virtual void SetDamping( Sint32 Index, float Damping ) = 0;
		virtual void SetEquilibriumPoint() = 0; // set the current constraint position/orientation as an equilibrium point for all DOF
		virtual void SetEquilibriumPoint( Sint32 Index ) = 0;  // set the current constraint position/orientation as an equilibrium point for given DOF
		virtual void SetLimit( Sint32 Index, float Low, float Hi ) = 0;
		virtual void SetLinearLowerLimit( const Kernel::Math::Vector3& LinearLower ) = 0;
		virtual void SetLinearUpperLimit( const Kernel::Math::Vector3& LinearUpper ) = 0;
		virtual void SetAngularLowerLimit( const Kernel::Math::Vector3& AngularLower ) = 0;
		virtual void SetAngularUpperLimit( const Kernel::Math::Vector3& AngularUpper ) = 0;
	};
}
}
}
}

/**
	@file
	@brief �_�C�i�~�N�X�p�}�l�[�W���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Dynamics
{
	/**
		@brief �R���W�����p��
		@author �t���`
	*/
	struct CollisionSphere
	{
		float Radius;
	};
	/**
		@brief �R���W�����p��
		@author �t���`
	*/
	struct CollisionBox
	{
		float AxisX;
		float AxisY;
		float AxisZ;
	};
	/**
		@brief �R���W�����p�J�v�Z��
		@author �t���`
	*/
	struct CollisionCapsule
	{
		float Radius;
		float Length;
	};

	/**
		@brief ���b�V�������p
		@author �t���`
	*/
	struct SMeshCreateInfo
	{
		Uint32 VertexCount;							///< ���_��
		Uint32 IndexCount;							///< �C���f�b�N�X��
		const Kernel::Math::Vector3* pVertexTable;	///< ���_�f�[�^�e�[�u��
		const Uint32* pIndexTable;					///< �C���f�b�N�X�f�[�^�e�[�u��
	};

	/**
		@brief �W���C���g�p�������
		@author �t���`
	*/
	struct SJointLocalTransform
	{
		Kernel::Math::VectorS Position;		///< �ʒu
		Kernel::Math::VectorS Rotation;		///< ��]�p�x�i�y�x�w�j
	};

	/**
		@brief �_�C�i�~�N�X�p�C���^�[�t�F�C�X
		@author �t���`
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief ���C�L���X�g
			@author �t���`
			@param RayFrom		[in] ���C�̎n�_
			@param RayTo		[in] ���C�̏I�_
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@param pHitBody		[out] �Փ˃{�f�B
			@param Group		[in] ���C�̃R���W�����O���[�v
			@param Mask			[in] ���C�̃R���W�����}�X�N
			@note
			�������[���h�ɑ΂��ă��C�L���X�g���s���܂��B
		*/
		virtual bool RayCast( const Kernel::Math::VectorS& RayFrom, const Kernel::Math::VectorS& RayTo, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param Shape		[in] ���肷��`��
			@param MoveFrom		[in] �ړ��J�n���W
			@param MoveTo		[in] �ړ��I�����W
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@param pHitBody		[out] �Փ˃{�f�B
			@param Group		[in] ���C�̃R���W�����O���[�v
			@param Mask			[in] ���C�̃R���W�����}�X�N
			@note
			�������[���h�ɑ΂��ăR���W����������s���܂��B
		*/
		virtual bool SweepTestSingle( const CollisionSphere& Shape, const Kernel::Math::VectorS& MoveFrom, const Kernel::Math::VectorS& MoveTo, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param Shape		[in] ���肷��`��
			@param MoveFrom		[in] �ړ��J�n���W
			@param MoveTo		[in] �ړ��I�����W
			@param Rotate		[in] XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@param pHitBody		[out] �Փ˃{�f�B
			@param Group		[in] ���C�̃R���W�����O���[�v
			@param Mask			[in] ���C�̃R���W�����}�X�N
			@note
			�������[���h�ɑ΂��ăR���W����������s���܂��B
		*/
		virtual bool SweepTestSingle( const CollisionBox& Shape, const Kernel::Math::VectorS& MoveFrom, const Kernel::Math::VectorS& MoveTo, const Kernel::Math::VectorS& Rotate, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param Shape		[in] ���肷��`��
			@param MoveFrom		[in] �ړ��J�n���W
			@param MoveTo		[in] �ړ��I�����W
			@param Rotate		[in] XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@param pHitBody		[out] �Փ˃{�f�B
			@param Group		[in] ���C�̃R���W�����O���[�v
			@param Mask			[in] ���C�̃R���W�����}�X�N
			@note
			�������[���h�ɑ΂��ăR���W����������s���܂��B
		*/
		virtual bool SweepTestSingle( const CollisionCapsule& Shape, const Kernel::Math::VectorS& MoveFrom, const Kernel::Math::VectorS& MoveTo, const Kernel::Math::VectorS& Rotate, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal, Body::IBody*& pHitBody, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief �R���W��������
			@author �t���`
			@param SrcShape		[in] ���肷��`��P
			@param SrcMoveFrom	[in] �`��P�̈ړ��J�n���W
			@param SrcMoveTo	[in] �`��P�̈ړ��I�����W
			@param SrcRotate	[in] �`��P��XYZ��]�p�x
			@param DstShape		[in] ���肷��`��Q
			@param DstPosition	[in] �`��Q�̈ʒu
			@param DstRotation	[in] �`��Q��XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@note
			�`�󓯎m�̃R���W����������s���܂��B
		*/
		virtual bool SingleCollision( const CollisionSphere& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionSphere& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param SrcShape		[in] ���肷��`��P
			@param SrcMoveFrom	[in] �`��P�̈ړ��J�n���W
			@param SrcMoveTo	[in] �`��P�̈ړ��I�����W
			@param SrcRotate	[in] �`��P��XYZ��]�p�x
			@param DstShape		[in] ���肷��`��Q
			@param DstPosition	[in] �`��Q�̈ʒu
			@param DstRotation	[in] �`��Q��XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@note
			�`�󓯎m�̃R���W����������s���܂��B
		*/
		virtual bool SingleCollision( const CollisionSphere& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionBox& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param SrcShape		[in] ���肷��`��P
			@param SrcMoveFrom	[in] �`��P�̈ړ��J�n���W
			@param SrcMoveTo	[in] �`��P�̈ړ��I�����W
			@param SrcRotate	[in] �`��P��XYZ��]�p�x
			@param DstShape		[in] ���肷��`��Q
			@param DstPosition	[in] �`��Q�̈ʒu
			@param DstRotation	[in] �`��Q��XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@note
			�`�󓯎m�̃R���W����������s���܂��B
		*/
		virtual bool SingleCollision( const CollisionSphere& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionCapsule& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param SrcShape		[in] ���肷��`��P
			@param SrcMoveFrom	[in] �`��P�̈ړ��J�n���W
			@param SrcMoveTo	[in] �`��P�̈ړ��I�����W
			@param SrcRotate	[in] �`��P��XYZ��]�p�x
			@param DstShape		[in] ���肷��`��Q
			@param DstPosition	[in] �`��Q�̈ʒu
			@param DstRotation	[in] �`��Q��XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@note
			�`�󓯎m�̃R���W����������s���܂��B
		*/
		virtual bool SingleCollision( const CollisionBox& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionBox& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param SrcShape		[in] ���肷��`��P
			@param SrcMoveFrom	[in] �`��P�̈ړ��J�n���W
			@param SrcMoveTo	[in] �`��P�̈ړ��I�����W
			@param SrcRotate	[in] �`��P��XYZ��]�p�x
			@param DstShape		[in] ���肷��`��Q
			@param DstPosition	[in] �`��Q�̈ʒu
			@param DstRotation	[in] �`��Q��XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@note
			�`�󓯎m�̃R���W����������s���܂��B
		*/
		virtual bool SingleCollision( const CollisionBox& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionCapsule& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;
		/**
			@brief �R���W��������
			@author �t���`
			@param SrcShape		[in] ���肷��`��P
			@param SrcMoveFrom	[in] �`��P�̈ړ��J�n���W
			@param SrcMoveTo	[in] �`��P�̈ړ��I�����W
			@param SrcRotate	[in] �`��P��XYZ��]�p�x
			@param DstShape		[in] ���肷��`��Q
			@param DstPosition	[in] �`��Q�̈ʒu
			@param DstRotation	[in] �`��Q��XYZ��]�p�x
			@param HitPosition	[out] ���C�̏Փˈʒu
			@param HitNormal	[out] ���C�̏Փ˖@��
			@note
			�`�󓯎m�̃R���W����������s���܂��B
		*/
		virtual bool SingleCollision( const CollisionCapsule& SrcShape, const Kernel::Math::VectorS& SrcMoveFrom, const Kernel::Math::VectorS& SrcMoveTo, const Kernel::Math::VectorS& SrcRotate, const CollisionCapsule& DstShape, const Kernel::Math::VectorS& DstPosition, const Kernel::Math::VectorS& DstRotation, Kernel::Math::VectorS& HitPosition, Kernel::Math::VectorS& HitNormal ) = 0;

		/**
			@brief �d�͎擾
			@author ����
			@return �d��
			@note
			�V�~�����[�V�������[���h�̏d�͂��擾���܂��B
		*/
		virtual Kernel::Math::VectorS GetGravity() = 0;

		/**
			@brief �d�͐ݒ�
			@author �t���`
			@param Gravity	[in] �d��
			@note
			�V�~�����[�V�������[���h�̏d�͂�ݒ肵�܂��B
		*/
		virtual void SetGravity( const Kernel::Math::VectorS& Gravity ) = 0;
		/**
			@brief �����V�~�����[�V�����̃X�e�b�v�p�����[�^�[�ݒ�
			@author �t���`
			@param StepTime	[in] �P�V�~�����[�V�����X�e�b�v�̎��ԁi�b�w��j
			@param Iteration	[in] �P�V�~�����[�V�����̏�����
			@note
			�V�~�����[�V�������̕���\��ݒ肵�܂��B<BR>
			Iteration���傫���Ȃ�قǃR���W�����̔�������������肵�܂����A<BR>
			���̕��������d���Ȃ��Ă����܂��B
		*/
		virtual void SetStepSimulationParameteer( float StepTime, Uint32 Iteration ) = 0;
		/**
			@brief �����V�~�����[�V�����̃X�e�b�v
			@author �t���`
			@param StepTimeScale	[in] �X�V���Ԕ{��
			@note
			���ۂ̃V�~�����[�V�����̎��s
		*/
		virtual void StepSimulation( float StepTimeScale = 1.0f ) = 0;
		/**
			@brief �Փ˃|�C���g���X�V
			@author �t���`
			@note
			�Փ˂̃|�C���g�̃��X�g���X�V
		*/
		virtual void EndSimulation() = 0;
		/**
			@brief �f�o�b�O�p�I�u�W�F�`��
			@author �t���`
			@param pLine		[in] ���C�������_���[
			@param pTriangle	[in] �|���S�������_���[
			@param pCamera		[in] �`��Ɏg���J����
			@note
			�f�o�b�O�p�̊ȈՃV�F�C�v�̕`����s���܂��B
		*/
		virtual void DrawDebugShape( Graphics::Simple::ILineRenderer* pLine, Graphics::Simple::ITriangleRenderer* pTriangle, const Kernel::Math::Matrix* pCamera ) = 0;
		/**
			@brief �f�o�b�O�p�ڐG�_�`��
			@author �t���`
			@param pLineRenderer	[in] ���C�������_���[
			@param Lenfth			[in] �ڐG�_�̖@���̒���
			@note
			�f�o�b�O�p�̐ڐG�_�̕`����s���܂��B
		*/
		virtual void DrawDebugContactPoint( Graphics::Simple::ILineRenderer* pLineRenderer, float Lenfth ) = 0;

		/**
			@brief �����{�f�B����
			@author �t���`
			@param pCompoundTbl		[in] �{�f�B�̃e�[�u��
			@param CompoundCount	[in] �{�f�B�̐�1
			@param Mass			[in] ����
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�����̃{�f�B��g�ݍ��킹�������{�f�B���쐬���܂��B
		*/
		virtual Body::ICompound* CreateCompound( const Body::CompoundShape* pCompoundTbl[], Uint32 CompoundCount, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief ������
			@author �t���`
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�������ʂ̏��̃{�f�B���쐬���܂��B<BR>
			���̃{�f�B�ɑ΂��镨���V�~�����[�V�����͖����ł��B
		*/
		virtual Body::IPlane* CreateFloor( Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief ������
			@author �t���`
			@param Radius			[in] ���̔��a
			@param Mass			[in] ����
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			����̃{�f�B���쐬���܂��B
		*/
		virtual Body::ISphere* CreateSphere( float Radius, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �J�v�Z������
			@author �t���`
			@param Length			[in] �J�v�Z���̒���
			@param Radius			[in] �J�v�Z���̔��a
			@param Mass			[in] ����
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�J�v�Z����̃{�f�B���쐬���܂��B
		*/
		virtual Body::ICapsule* CreateCapsule( float Length, float Radius, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �{�b�N�X����
			@author �t���`
			@param Size				[in] ���̃T�C�Y�i�R�Ӂj
			@param Mass			[in] ����
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			����̃{�f�B���쐬���܂��B
		*/
		virtual Body::IBox* CreateBox( const Kernel::Math::VectorS& Size, float Mass, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief ���b�V������
			@author �t���`
			@param Mass				[in] ����
			@param Info				[in] ���b�V�����
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			���b�V���`��̃{�f�B���쐬���܂��B
		*/
		virtual Body::ITriMesh* CreateTriMesh( float Mass, const SMeshCreateInfo& Info, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief ���b�V������
			@author �t���`
			@param Mass				[in] ����
			@param pInfo			[in] ���b�V�����e�[�u��
			@param InfoCount		[in] ���b�V�����e�[�u����
			@param InitPosition		[in] �����ʒu
			@param Inertia			[in] ����
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			���b�V���`��̃{�f�B���쐬���܂��B
		*/
		virtual Body::ITriMesh* CreateTriMesh( float Mass, const SMeshCreateInfo* pInfo, Uint32 InfoCount, const Kernel::Math::VectorS& InitPosition, const Kernel::Math::VectorS& Inertia, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �}�b�v�p���b�V������
			@author �t���`
			@param Info				[in] ���b�V�����
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�}�b�v�p�̃��b�V���`��̃{�f�B���쐬���܂��B<BR>
			���̃{�f�B�͕����V�~�����[�V�����͖����ł��B
		*/
		virtual Body::ITriMesh* CreateTriMeshForMap( const SMeshCreateInfo& Info, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �}�b�v�p���b�V������
			@author �t���`
			@param pInfo			[in] ���b�V�����e�[�u��
			@param InfoCount		[in] ���b�V�����e�[�u����
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�}�b�v�p�̃��b�V���`��̃{�f�B���쐬���܂��B<BR>
			���̃{�f�B�͕����V�~�����[�V�����͖����ł��B
		*/
		virtual Body::ITriMesh* CreateTriMeshForMap( const SMeshCreateInfo* pInfo, Uint32 InfoCount, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief �L�����N�^�[�p�v���L�V�[����
			@author ����
			@param Mass				[in] ����
			@param Length			[in] �J�v�Z���̒���
			@param Radius			[in] �J�v�Z���̔��a
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�L�����N�^�[����p�̓���ȃJ�v�Z���`��̃{�f�B���쐬���܂��B<BR>
			Delegate�ɂ��A�֐���ݒ肷�邱�Ƃɂ���ăL�����N�^�[�p�̓�����������܂��B
		*/
		virtual Body::ICharaProxy* CreateCharaProxy( float Mass, float Length, float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group= 0xFFFF, Uint16 Mask= 0xFFFF ) = 0;
		/**
			@brief �L�����N�^�[�p�v���L�V�[����
			@author ����
			@param Mass				[in] ����
			@param Radius			[in] ���̔��a
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�L�����N�^�[����p�̓���ȋ��`��̃{�f�B���쐬���܂��B<BR>
			Delegate�ɂ��A�֐���ݒ肷�邱�Ƃɂ���ăL�����N�^�[�p�̓�����������܂��B
		*/
		virtual Body::ICharaProxy* CreateCharaProxy( float Mass, float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group= 0xFFFF, Uint16 Mask= 0xFFFF ) = 0;
		/**
			@brief �ȈՃL�����N�^�[�p�v���L�V�[����
			@author �t���`
			@param Length			[in] �J�v�Z���̒���
			@param Radius			[in] �J�v�Z���̔��a
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�L�����N�^�[����p�̓���ȃJ�v�Z���`��̃{�f�B���쐬���܂��B<BR>
			��{�I�ɕ����V�~�����[�V�����ɑ����ē����܂�����̊������<BR>
			���C�̏���������Ȃ��̂ɂȂ��Ă��܂��B
		*/
		virtual Body::ICharaProxySimple* CreateCharaProxySimple( float Length, float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �ȈՃL�����N�^�[�p�v���L�V�[����
			@author �t���`
			@param Radius			[in] ���̔��a
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�L�����N�^�[����p�̓���ȋ��`��̃{�f�B���쐬���܂��B<BR>
			��{�I�ɕ����V�~�����[�V�����ɑ����ē����܂�����̊������<BR>
			���C�̏���������Ȃ��̂ɂȂ��Ă��܂��B
		*/
		virtual Body::ICharaProxySimple* CreateCharaProxySimple( float Radius, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �g���K�[�{�b�N�X�̐���
			@author �t���`
			@param Size				[in] ���̃T�C�Y�i�R�Ӂj
			@param InitPosition		[in] �����ʒu
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�C�x���g�p�̔���̃{�f�B���쐬���܂��B<BR>
			�����������ɓ��������ɃC�x���g���N�����Ȃǂ̏����̂��߂Ɏg���܂��B
		*/
		virtual Body::ITriggerBox* CreateTriggerBox( const Kernel::Math::VectorS& Size, const Kernel::Math::VectorS& InitPosition, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief ���[�v�̐���
			@author �t���`
			@param From				[in] �n�_
			@param To				[in] �I�_
			@param Count			[in] �m�[�h�̐�
			@param Mass				[in] ����
			@param IsLockFrom		[in] From�������Œ�
			@param IsLockTo			[in] To�������Œ�
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			���[�v��̃\�t�g�{�f�B�𐶐����܂��B
		*/
		virtual Body::IRope* CreateRope( const Kernel::Math::VectorS& From, const Kernel::Math::VectorS& To, Sint32 Count, float Mass, bool IsLockFrom, bool IsLockTo, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;

		/**
			@brief �X���C�_�[�W���C���g�̐���
			@author �t���`
			@param pBody0		[in] �ڑ����̃{�f�B
			@param pBody1		[in] �ڑ���̃{�f�B
			@param Transform0	[in] �ڑ����̏������
			@param Transform1	[in] �ڑ���̏������
			@note
			�P����]�A�P���ړ��̃X���C�_�[���̃W���C���g���쐬���܂��B<BR>
			�Q�̃{�f�B���X���C�_�[�Őڑ�����ꍇ�ɗ��p���܂��B
		*/
		virtual Joint::ISliderJoint* CreateSliderJoint( Body::IBody* pBody0, Body::IBody* pBody1, const SJointLocalTransform& Transform0, const SJointLocalTransform& Transform1 ) = 0;
		/**
			@brief �q���W�W���C���g�̐���
			@author �t���`
			@param pBody0		[in] �ڑ����̃{�f�B
			@param pBody1		[in] �ڑ���̃{�f�B
			@param Transform0	[in] �ڑ����̏������
			@param Transform1	[in] �ڑ���̏������
			@note
			�P����]�̃q���W���̃W���C���g���쐬���܂��B<BR>
			�Q�̃{�f�B���q���W�Őڑ�����ꍇ�ɗ��p���܂��B
		*/
		virtual Joint::IHingeJoint* CreateHingeJoint( Body::IBody* pBody0, Body::IBody* pBody1, const SJointLocalTransform& Transform0, const SJointLocalTransform& Transform1 ) = 0;
		/**
			@brief �|�C���g�W���C���g�̐���
			@author �t���`
			@param pBody0		[in] �ڑ����̃{�f�B
			@param pBody1		[in] �ڑ���̃{�f�B
			@param Pivot0		[in] �ڑ����̐ڑ��ꏊ
			@param Pivot1		[in] �ڑ���̐ڑ��ꏊ
			@note
			�R����]�̃|�C���g���̃W���C���g���쐬���܂��B<BR>
			�Q�̃{�f�B���|�C���g�Őڑ�����ꍇ�ɗ��p���܂��B
		*/
		virtual Joint::IPointJoint* CreatePointJoint( Body::IBody* pBody0, Body::IBody* pBody1, const Kernel::Math::VectorS& Pivot0, const Kernel::Math::VectorS& Pivot1 ) = 0;

		virtual Joint::IDofSpringJoint* CreateDofSpringJoint( Body::IBody* pBody0, Body::IBody* pBody1, const Kernel::Math::VectorS& Pivot0, const Kernel::Math::VectorS& Pivot1 ) = 0;

		/**
			@brief �Փ˔��苅����
			@author ����
			@param Radius			[in] ���̔��a
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�Փ˔���p����̃{�f�B���쐬���܂��B
		*/
		virtual Body::ICollisionSphere* CreateCollisionSphere( float Radius, Uint16 Group, Uint16 Mask ) = 0;
	
		/**
			@brief �Փ˔���J�v�Z������
			@author ����
			@param Length			[in] �J�v�Z���̒���
			@param Radius			[in] �J�v�Z���̔��a
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�Փ˔���p�J�v�Z����̃{�f�B���쐬���܂��B
		*/
		virtual Body::ICollisionCapsule* CreateCollisionCapsule( float Length, float Radius, Uint16 Group, Uint16 Mask ) = 0;
		/**
			@brief �Փ˔���{�b�N�X����
			@author ����
			@param Size				[in] ���̃T�C�Y�i�R�Ӂj
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�Փ˔���p����̃{�f�B���쐬���܂��B
		*/
		virtual Body::ICollisionBox* CreateCollisionBox( const Kernel::Math::VectorS& Size, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �Փ˔��胁�b�V������
			@author ����
			@param Info				[in] ���b�V�����
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�Փ˔���p���b�V���`��̃{�f�B���쐬���܂��B
		*/
		virtual Body::ICollisionTriMesh* CreateCollisionTriMesh( const SMeshCreateInfo& Info, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
		/**
			@brief �Փ˔��胁�b�V������
			@author ����
			@param pInfo			[in] ���b�V�����e�[�u��
			@param InfoCount		[in] ���b�V�����e�[�u����
			@param Group			[in] �R���W�����̃O���[�v�i�����̃O���[�v�j
			@param Mask				[in] �R���W�����̃}�X�N�i�ڐG�Ώۂ̃}�X�N�j
			@note
			�Փ˔���p���b�V���`��̃{�f�B���쐬���܂��B
		*/
		virtual Body::ICollisionTriMesh* CreateCollisionTriMesh( const SMeshCreateInfo* pInfo, Uint32 InfoCount, Uint16 Group = 0xFFFF, Uint16 Mask = 0xFFFF ) = 0;
	};
}
}
}

/**
	@file
	@brief �W�������}�e���A��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
namespace Standard
{
namespace Material
{
namespace Standard
{
	/**
		@brief �W�������p�}�e���A���e�N�X�`���X�e�[�W
		@author �t���`
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_COLOR,			///< �g�U����
		TEXTURE_STAGE_EMISSIVE,			///< ���Ȕ���
		TEXTURE_STAGE_ENVIRONMENT,		///< ���}�b�v�i�L���[�u�}�b�v�j
		TEXTURE_STAGE_SPECULAR,			///< ���ʔ���
		TEXTURE_STAGE_NORMAL,			///< �@���}�b�v
		TEXTURE_STAGE_HEIGHT,			///< �����}�b�v�p�����}�b�v
		TEXTURE_STAGE_LIGHT_LOOKUP,		///< ���C�g�Q�ƃe�N�X�`��
		TEXTURE_STAGE_MAX,
	};

	/**
		@brief �W�������}�e���A��
		@author �t���`
	*/
	class IMaterial
		: public Engine::Graphics::Resource::IMaterialPlugin
	{
	protected:
		virtual ~IMaterial() {}

	public:
		/**
			@brief ���C�e�B���O�̗L����ݒ�
			@author �t���`
			@param Enable	[in] ���C�e�B���O���p����true
			@note
			�}�e���A���ɑ΂��ă��C�g�̏�����ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetLightEnable( bool Enable ) = 0;
		/**
			@brief ���C�e�B���O�̗L�����擾
			@author �t���`
			@retval true	���C�g����
			@retval false	���C�g�Ȃ�
			@note
			���C�e�B���O���s�����ǂ������擾���܂��B
		*/
		virtual bool IsLightEnable() const = 0;

		/**
			@brief ���Ȕ����̗L����ݒ�
			@author �t���`
			@param Enable	[in] ���Ȕ������p����true
			@note
			�}�e���A���ɑ΂��Ď��Ȕ����̏�����ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetEmissiveEnable( bool Enable ) = 0;
		/**
			@brief ���Ȕ����̗L�����擾
			@author �t���`
			@retval true	���Ȕ�������
			@retval false	���Ȕ����Ȃ�
			@note
			���Ȕ������s�����ǂ������擾���܂��B
		*/
		virtual bool IsEmissiveEnable() const = 0;

		/**
			@brief ���ʔ��˂̗L����ݒ�
			@author �t���`
			@param Enable	[in] ���ʔ��˗��p����true
			@note
			�}�e���A���ɑ΂��ċ��ʔ��˂̏�����ON/OFF��ݒ肵�܂��B
		*/
		virtual void SetSpecularEnable( bool Enable ) = 0;
		/**
			@brief ���ʔ��˂̗L�����擾
			@author �t���`
			@retval true	���ʔ��˂���
			@retval false	���ʔ��˂Ȃ�
			@note
			���ʔ��˂��s�����ǂ������擾���܂��B
		*/
		virtual bool IsSpecularEnable() const = 0;

		/**
			@brief ���C�g�̎�ނ�ݒ�
			@author �t���`
			@param Value	[in] ���
			@note
			���C�g�̎�ނ�ݒ肵�܂��B
		*/
		virtual void SetLightType( Sint32 Type ) = 0;
		/**
			@brief ���C�g�̎�ނ��擾
			@author �t���`
			@return	���C�g�̎��
			@note
			�K�p���郉�C�g�̎�ނ��擾���܂��B
		*/
		virtual Sint32 GetLightType() const = 0;

		/**
			@brief �\�[�g�p�̃��C���[��ݒ�
			@author �t���`
			@param Value	[in] �\�[�g�l
			@note
			�\�[�g���̊�l��ݒ肵�܂��B
		*/
		virtual void SetSortKey( Uint32 Value ) = 0;
		/**
			@brief �\�[�p�̃L�[���擾
			@author �t���`
			@return �\�[�g�p�̃L�[
			@note
			�\�[�g�ɗ��p����L�[���擾���܂��B
		*/
		virtual Uint32 GetSortKey() const = 0;

		/**
			@brief �}���`�|���S���p���C���[��ݒ�
			@author �t���`
			@param Value	[in] ���C���[
			@note
			�}���`�|���S���p�̃��C���[�ݒ肵�܂��B
		*/
		virtual void SetMultiPolygonLayer( Uint32 Value ) = 0;
		/**
			@brief �}���`�|���S���p���C���[���擾
			@author �t���`
			@return �}���`�|���S���p���C���[
			@note
			�}���`�|���S���p�̃��C���[���擾���܂��B
		*/
		virtual Uint32 GetMultiPolygonLayer() const = 0;

		/**
			@brief �V���h�E�}�b�v�̋�����ݒ�
			@author �t���`
			@param Value	[in] ����
			@note
			�V���h�E�}�b�v�������̋�����ݒ肵�܂��B
		*/
		virtual void SetShadowMapType( Uint32 Value ) = 0;
		/**
			@brief �V���h�E�}�b�v�̋������擾
			@author �t���`
			@return �V���h�E�}�b�v�̋���
			@note
			�V���h�E�}�b�v���̋������擾���܂��B
		*/
		virtual Uint32 GetShadowMapType() const = 0;

		/**
			@brief �����_�����O�p���C���[��ݒ�
			@author �t���`
			@param Value	[in] ���C���[
			@note
			�����_�����O�p�̃��C���[��ݒ肵�܂��B
		*/
		virtual void SetRenderingLayer( Uint32 Value ) = 0;
		/**
			@brief �`��p���C���[���擾
			@author �t���`
			@return �`��p���C���[
			@note
			�`��p�̃��C���[���擾���܂��B
		*/
		virtual Uint32 GetRenderingLayer() const = 0;

		/**
			@brief �e�N�X�`����UV�I�t�Z�b�g��ݒ�
			@author �t���`
			@param Offset	[in] �e�N�X�`����UV�I�t�Z�b�g
			@note
			�}�e���A���ɑ΂��ăe�N�X�`����UV�I�t�Z�b�g��ݒ肵�܂��B
		*/
		virtual void SetTextureOffset( const Kernel::Math::Vector2& Offset ) = 0;
		/**
			@brief �e�N�X�`����UV�I�t�Z�b�g���擾
			@author �t���`
			@return �e�N�X�`����UV�I�t�Z�b�g
			@note
			�}�e���A������e�N�X�`����UV�I�t�Z�b�g���擾���܂��B
		*/
		virtual const Kernel::Math::Vector2& GetTextureOffset() const = 0;

		/**
			@brief �g�U���˂̐F��ݒ�
			@author �t���`
			@param Diffuse	[in] �g�U���˂̐F
			@note
			�}�e���A���ɑ΂��Ċg�U���˂̐F��ݒ肵�܂��B
		*/
		virtual void SetDiffuse( const Kernel::Math::VectorS& Diffuse ) = 0;
		/**
			@brief �g�U���˂̐F���擾
			@author �t���`
			@return �g�U���ːF
			@note
			�g�U���˂̐F���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetDiffuse() const = 0;

		/**
			@brief ���Ȕ����̐F��ݒ�
			@author �t���`
			@param Emissive	[in] ���Ȕ����̐F
			@note
			�}�e���A���ɑ΂��Ď��Ȕ����̐F��ݒ肵�܂��B
		*/
		virtual void SetEmissive( const Kernel::Math::VectorS& Emissive ) = 0;
		/**
			@brief ���Ȕ����̐F���擾
			@author �t���`
			@return ���Ȕ����F
			@note
			���Ȕ����̐F���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetEmissive() const = 0;

		/**
			@brief ���ʔ��˂̐F��ݒ�
			@author �t���`
			@param Specular	[in] ���ʔ��˂̐F
			@note
			�}�e���A���ɑ΂��ċ��ʔ��˂̐F��ݒ肵�܂��B
		*/
		virtual void SetSpecular( const Kernel::Math::VectorS& Specular ) = 0;
		/**
			@brief ���ʔ��˂̐F���擾
			@author �t���`
			@return ���ʔ��ːF
			@note
			���ʔ��˂̐F���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetSpecular() const = 0;

		/**
			@brief ���ʔ��˂̃o�C�A�X��ݒ�
			@author �t���`
			@param Value	[in] ���ʔ��˂̃o�C�A�X�l
			@note
			���ʔ��˂̌v�Z���̃o�C�A�X�l��ݒ肵�܂��B<BR>
			���ʔ��˂͈ȉ��̎��ŋ��߂��܂��B<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularBias( float Value ) = 0;
		/**
			@brief ���ʔ��˂̃o�C�A�X���擾
			@author �t���`
			@return �o�C�A�X�l
			@note
			���ʔ��˂̃o�C�A�X�l���擾���܂��B
		*/
		virtual float GetSpecularBias() const = 0;

		/**
			@brief ���ʔ��˂̃X�P�[����ݒ�
			@author �t���`
			@param Value	[in] ���ʔ��˂̃X�P�[���l
			@note
			���ʔ��˂̌v�Z���̃X�P�[���l��ݒ肵�܂��B<BR>
			���ʔ��˂͈ȉ��̎��ŋ��߂��܂��B<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularScale( float Value ) = 0;
		/**
			@brief ���ʔ��˂̃X�P�[�����擾
			@author �t���`
			@return �X�P�[���l
			@note
			���ʔ��˂̃X�P�[���l���擾���܂��B
		*/
		virtual float GetSpecularScale() const = 0;

		/**
			@brief ���ʔ��˂̌W����ݒ�
			@author �t���`
			@param Value	[in] ���ʔ��˂̌W���l
			@note
			���ʔ��˂̌v�Z���̌W���l��ݒ肵�܂��B<BR>
			���ʔ��˂͈ȉ��̎��ŋ��߂��܂��B<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularPow( float Value ) = 0;
		/**
			@brief ���ʔ��˂̌W�����擾
			@author �t���`
			@return �W���l
			@note
			���ʔ��˂̌W���l���擾���܂��B
		*/
		virtual float GetSpecularPow() const = 0;

		/**
			@brief �@���}�b�v�̃X�P�[���l��ݒ�
			@author �t���`
			@param Value	[in] �@���}�b�v�̃X�P�[���l�i�傫���قǉ��ʂ��͂����肷��j
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l��ݒ肵�܂��B
		*/
		virtual void SetNormalScale( float Value ) = 0;
		/**
			@brief �@���}�b�v�̃X�P�[���l���擾
			@author �t���`
			@return �X�P�[���l
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l���擾���܂��B
		*/
		virtual float GetNormalScale() const = 0;

		/**
			@brief �����}�b�v���̍ŏ��T���v������ݒ�
			@author �t���`
			@param Value	[in] �����}�b�v�̍ŏ��T���v����
			@note
			�����}�b�v���̍ŏ��̃T���v������ݒ肵�܂��B
		*/
		virtual void SetParallaxMinSample( Sint32 Value ) = 0;
		/**
			@brief �����}�b�v���̍ŏ��T���v�������擾
			@author �t���`
			@return �����}�b�v�̍ŏ��T���v����
			@note
			�����}�b�v���̍ŏ��T���v�������擾���܂��B
		*/
		virtual Sint32 GetParallaxMinSample() = 0;

		/**
			@brief �����}�b�v���̍ő�T���v������ݒ�
			@author �t���`
			@param Value	[in] �����}�b�v�̍ő�T���v����
			@note
			�����}�b�v���̍ő�̃T���v������ݒ肵�܂��B
		*/
		virtual void SetParallaxMaxSample( Sint32 Value ) = 0;
		/**
			@brief �����}�b�v���̍ő�T���v�������擾
			@author �t���`
			@return �����}�b�v�̍ő�T���v����
			@note
			�����}�b�v���̍ő�T���v�������擾���܂��B
		*/
		virtual Sint32 GetParallaxMaxSample() const = 0;

		/**
			@brief �����}�b�v�̍�����ݒ�
			@author �t���`
			@param Value	[in] �����}�b�v�̍����l
			@note
			�����}�b�v���̍�����ݒ肵�܂��B<BR>
			��������قǉ��ʂ��͂����肵�܂���<BR>
			�T���v���������Ȃ��Ɖ����Ȃ�܂��B
		*/
		virtual void SetParallaxHeight( float Value ) = 0;
		/**
			@brief �����}�b�v�̍������擾
			@author �t���`
			@return �����}�b�v�̍���
			@note
			�����}�b�v���̍������擾���܂��B
		*/
		virtual float GetParallaxHeight() const = 0;
	};
}
}
}
}
}
}
/**
	@file
	@brief �W�������}�e���A��
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
namespace Standard
{
namespace Material
{
namespace Water
{
	/**
		@brief �W�������p�}�e���A���e�N�X�`���X�e�[�W
		@author �t���`
	*/
	enum eTextureStage
	{
		TEXTURE_STAGE_ENVIRONMENT,		///< ���}�b�v�i�L���[�u�}�b�v�j
		TEXTURE_STAGE_NORMAL_A,			///< �@���}�b�v
		TEXTURE_STAGE_NORMAL_B,			///< �@���}�b�v
		TEXTURE_STAGE_MAX,
	};

	/**
		@brief �W�������}�e���A��
		@author �t���`
	*/
	class IMaterial
		: public Engine::Graphics::Resource::IMaterialPlugin
	{
	protected:
		virtual ~IMaterial() {}

	public:
		/**
			@brief �g�U���˂̐F��ݒ�
			@author �t���`
			@param Diffuse	[in] �g�U���˂̐F
			@note
			�}�e���A���ɑ΂��Ċg�U���˂̐F��ݒ肵�܂��B
		*/
		virtual void SetDiffuse( const Kernel::Math::VectorS& Diffuse ) = 0;
		/**
			@brief �g�U���˂̐F���擾
			@author �t���`
			@return �g�U���ːF
			@note
			�g�U���˂̐F���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetDiffuse() const = 0;

		/**
			@brief ���ʔ��˂̐F��ݒ�
			@author �t���`
			@param Specular	[in] ���ʔ��˂̐F
			@note
			�}�e���A���ɑ΂��ċ��ʔ��˂̐F��ݒ肵�܂��B
		*/
		virtual void SetSpecular( const Kernel::Math::VectorS& Specular ) = 0;
		/**
			@brief ���ʔ��˂̐F���擾
			@author �t���`
			@return ���ʔ��ːF
			@note
			���ʔ��˂̐F���擾���܂��B
		*/
		virtual const Kernel::Math::VectorS& GetSpecular() const = 0;

		/**
			@brief ���ʔ��˂̃o�C�A�X��ݒ�
			@author �t���`
			@param Value	[in] ���ʔ��˂̃o�C�A�X�l
			@note
			���ʔ��˂̌v�Z���̃o�C�A�X�l��ݒ肵�܂��B<BR>
			���ʔ��˂͈ȉ��̎��ŋ��߂��܂��B<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularBias( float Value ) = 0;
		/**
			@brief ���ʔ��˂̃o�C�A�X���擾
			@author �t���`
			@return �o�C�A�X�l
			@note
			���ʔ��˂̃o�C�A�X�l���擾���܂��B
		*/
		virtual float GetSpecularBias() const = 0;

		/**
			@brief ���ʔ��˂̃X�P�[����ݒ�
			@author �t���`
			@param Value	[in] ���ʔ��˂̃X�P�[���l
			@note
			���ʔ��˂̌v�Z���̃X�P�[���l��ݒ肵�܂��B<BR>
			���ʔ��˂͈ȉ��̎��ŋ��߂��܂��B<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularScale( float Value ) = 0;

		/**
			@brief ���ʔ��˂̃X�P�[�����擾
			@author �t���`
			@return �X�P�[���l
			@note
			���ʔ��˂̃X�P�[���l���擾���܂��B
		*/
		virtual float GetSpecularScale() const = 0;

		/**
			@brief ���ʔ��˂̌W����ݒ�
			@author �t���`
			@param Value	[in] ���ʔ��˂̌W���l
			@note
			���ʔ��˂̌v�Z���̌W���l��ݒ肵�܂��B<BR>
			���ʔ��˂͈ȉ��̎��ŋ��߂��܂��B<BR>
			Result = Bias + (Scale * pow( Pow ))
		*/
		virtual void SetSpecularPow( float Value ) = 0;
		/**
			@brief ���ʔ��˂̌W�����擾
			@author �t���`
			@return �W���l
			@note
			���ʔ��˂̌W���l���擾���܂��B
		*/
		virtual float GetSpecularPow() const = 0;

		/**
			@brief �@���}�b�v�̃X�P�[���l��ݒ�
			@author �t���`
			@param Value	[in] �@���}�b�v�̃X�P�[���l�i�傫���قǉ��ʂ��͂����肷��j
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l��ݒ肵�܂��B
		*/
		virtual void SetNormalScaleA( float Value ) = 0;
		/**
			@brief �@���}�b�v�̃X�P�[���l���擾
			@author �t���`
			@return �X�P�[���l
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l���擾���܂��B
		*/
		virtual float GetNormalScaleA() const = 0;

		/**
			@brief �@���}�b�v�̃X�P�[���l��ݒ�
			@author �t���`
			@param Value	[in] �@���}�b�v�̃X�P�[���l�i�傫���قǉ��ʂ��͂����肷��j
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l��ݒ肵�܂��B
		*/
		virtual void SetNormalScaleB( float Value ) = 0;
		/**
			@brief �@���}�b�v�̃X�P�[���l���擾
			@author �t���`
			@return �X�P�[���l
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l���擾���܂��B
		*/
		virtual float GetNormalScaleB() const = 0;

		/**
			@brief �@���}�b�v�̃X�P�[���l��ݒ�
			@author �t���`
			@param Value	[in] �@���}�b�v�̃X�P�[���l�i�傫���قǉ��ʂ��͂����肷��j
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l��ݒ肵�܂��B
		*/
		virtual void SetReflectRate( float Value ) = 0;
		/**
			@brief �@���}�b�v�̃X�P�[���l���擾
			@author �t���`
			@return �X�P�[���l
			@note
			�@���}�b�v�̖@���ɑ΂��ẴX�P�[���l���擾���܂��B
		*/
		virtual float GetReflectRate() const = 0;
	};
}
}
}
}
}
}

/**
	@file
	@brief �W�����������_���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
namespace Standard
{

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef Uint32 POINTLIGHT_HANDLE;		///< �|�C���g���C�g�̃n���h��

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------


/**
	@brief �r���[�̃^�C�v
	@author �t���`
*/
enum eViewType
{
	VIEW_TYPE_01,		///< �P�ڂ̃r���[
	VIEW_TYPE_02,		///< �Q�ڂ̃r���[
	VIEW_TYPE_03,		///< �R�ڂ̃r���[
	VIEW_TYPE_04,		///< �S�ڂ̃r���[
	VIEW_TYPE_05,		///< �T�ڂ̃r���[
	VIEW_TYPE_06,		///< �U�ڂ̃r���[
	VIEW_TYPE_07,		///< �V�ڂ̃r���[
	VIEW_TYPE_08,		///< �W�ڂ̃r���[

	VIEW_TYPE_MAX,
};

/**
	@brief ���s�����̃^�C�v
	@author �t���`
*/
enum eDirectionLight
{
	DIRECTION_LIGHT_MAIN,	///< ���C���̕��s����
	DIRECTION_LIGHT_SUB1,	///< �T�u�P
	DIRECTION_LIGHT_SUB2,	///< �T�u�Q
	DIRECTION_LIGHT_SUB3,	///< �T�u�R

	DIRECTION_LIGHT_MAX,
};

/**
	@brief �V���h�E�}�b�v�̎��
	@author �t���`
*/
enum eShadowMapType
{
	SHADOW_MAP_DISABLE,		///< �Ȃ�
	SHADOW_MAP_STANDARD,	///< �V���h�E�}�b�v
	SHADOW_MAP_SOFT,		///< 3x3�T���v��PCF�ɂ��\�t�g�V���h�E

	SHADOW_MAP_MAX,
};

/**
	@brief �}�e���A���̎��
	@author �t���`
*/
enum eMaterialType
{
	MATERIAL_TYPE_STANDARD,
	MATERIAL_TYPE_WATER,

	MATERIAL_TYPE_MAX,
};

/**
	@brief �����_�����O�Ώۂ̃��C���[
	@author �t���`
*/
enum eRenderingLayer
{
	RENDERING_LAYER_BACKGROUND,
	RENDERING_LAYER_DEFAULT,
	RENDERING_LAYER_AFTER_WATER,
	RENDERING_LAYER_AFTER_PARTICLE,

	RENDERING_LAYER_MAX,
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief �|�C���g���C�g
	@author �t���`
*/
struct SPointLight
{
	Kernel::Math::Vector4 Position;		///< �|�C���g���C�g�̈ʒu
	Kernel::Math::Vector4 Color;		///< �|�C���g���C�g�̐F
	float Distance;						///< �|�C���g���C�g�̉e������
};

/**
	@brief �}�e���A������p�I�v�V����
	@author �t���`
*/
struct SMaterialOption
{
public:
	bool IsEmissiveMap;
	bool IsEnvironmentMap;
	bool IsSpecularMap;
	bool IsNormalMap;
	bool IsParallaxMap;
	bool IsLookUpMap;
	bool IsScattering;
	bool IsFog;

public:
	SMaterialOption()
		: IsEmissiveMap		( true )
		, IsEnvironmentMap	( true )
		, IsSpecularMap		( true )
		, IsNormalMap		( true )
		, IsParallaxMap		( true )
		, IsLookUpMap		( true )
		, IsScattering		( true )
		, IsFog				( true )
	{
	}
};

/**
	@brief �����_���[�Z�b�e�B���O�p�p�����[�^�[
	@author �t���`
*/
struct SParameter
{
	bool IsHighQuality;					///< ���i�������_�����O���s��
	bool IsFog;							///< �t�H�O�̗L��
	bool IsScattering;					///< ���O�U�����̗L��
	bool IsDepthOfField;				///< ��ʊE�[�x�̗L��
	bool IsHighDynamicRange;			///< HDR�����_�����O�̗L��
	bool IsSoftParticle;				///< �\�t�g�p�[�e�B�N���̗L��
	bool IsMotionBlur;					///< ���[�V�����u���[�̗L��
	bool IsAmbientOcclusion;			///< �A���r�G���g�B��
	bool IsWaterInside;					///< �������o
	bool IsWaterDepthFog;				///< ���������t�H�O
	bool IsDynamicReflectionMap;		///< ���I���˃}�b�v���p
	bool IsWaterVertexAnimation;		///< ���ʒ��_�A�j���[�V����
	bool IsFrontFaceShadow;				///< ���ʃV���h�E�}�b�v
	eShadowMapType ShadowType;			///< �V���h�E�}�b�v�̎��

public:
	SParameter()
		: IsHighQuality					( false )
		, IsFog							( false )
		, IsScattering					( false )
		, IsDepthOfField				( false )
		, IsHighDynamicRange			( false )
		, IsSoftParticle				( false )
		, IsMotionBlur					( false )
		, IsAmbientOcclusion			( false )
		, IsWaterInside					( false )
		, IsWaterDepthFog				( false )
		, IsDynamicReflectionMap		( false )
		, IsWaterVertexAnimation		( false )
		, IsFrontFaceShadow				( false )
		, ShadowType					( SHADOW_MAP_DISABLE )
	{
	}
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief �����_���[�C���^�[�t�F�C�X
	@author �t���`
	@note
	Selene�����ŕW���̎����Ƃ��Ď����Ă��郌���_���[�ł��B<BR>
	���ڍׂȐ�������邽�߂Ɏ��O�Ń����_���[��p�ӂ��邱�Ƃ��\�ł��B
*/
class IRenderer
	: public Interface
{
protected:
	virtual ~IRenderer() {}

public:
	/**
		@brief �`��I�u�W�F�N�g�̑S���
		@author �t���`
		@note
		�`��I�u�W�F�N�g�S����B
	*/
	virtual void DestroyAllResource() = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::SMF::IModelController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::STM::IModelController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Particle::IParticleController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Particle::IVolumeParticleController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Particle::IEnhancedParticleController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Primitive::IPrimitiveController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::Sprite::ISpriteController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̎��O�V�F�[�_�[����
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@param Option		[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g�ɑ΂��Ď��O�ɃV�F�[�_�[�̐������s���܂��B<BR>
		�ʏ��AddDrawObject()���ɍs���܂������O�ɍs���Ă������œo�^�̃R�X�g�����点�܂��B
	*/
	virtual void PreShaderSetupDrawObject( Engine::Graphics::Resource::PolyLine::IPolyLineController* pDrawObject, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::SMF::IModelController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::SMF::IModelController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::STM::IModelController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::STM::IModelController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Particle::IParticleController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Particle::IParticleController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Particle::IVolumeParticleController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Particle::IVolumeParticleController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Particle::IEnhancedParticleController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Particle::IEnhancedParticleController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Primitive::IPrimitiveController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Primitive::IPrimitiveController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::Sprite::ISpriteController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::Sprite::ISpriteController* pDrawObject ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̒ǉ�
		@author �t���`
		@param pDrawObject		[in] �`��I�u�W�F�N�g
		@param IsShaderBuild	[in] �o�^���ɃV�F�[�_�[�̃r���h���ꏏ�ɍs�����ǂ���
		@param Option			[in] �}�e���A���V�F�[�_�[�p�I�v�V����
		@note
		�`��I�u�W�F�N�g��o�^���ă����_�����O���X�g�ɒǉ����܂��B
	*/
	virtual void AddDrawObject( Engine::Graphics::Resource::PolyLine::IPolyLineController* pDrawObject, bool IsShaderBuild = true, const SMaterialOption& Option = SMaterialOption() ) = 0;

	/**
		@brief �`��I�u�W�F�N�g�̔j��
		@author �t���`
		@param pDrawObject	[in] �`��I�u�W�F�N�g
		@note
		�o�^����Ă���`��I�u�W�F�N�g��j�����܂��B
	*/
	virtual void RemoveDrawObject( Engine::Graphics::Resource::PolyLine::IPolyLineController* pDrawObject ) = 0;

	/**
		@brief �r���[�̕\���̗L��
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@note
		�r���[�̕\�����K�v���ǂ������擾���܂��B<BR>
		�\����false�ɂ����ꍇ�ł�IsViewRendering()��true�ł����<BR>
		�����_�����O�����͍s���܂��B<BR>
		�R���̓����_�����O��̉摜�����[�U�[�����O�ŏ�������ꍇ�ɗ��p�ł��܂��B
	*/
	virtual bool IsViewDraw( eViewType ViewIndex ) = 0;

	/**
		@brief �r���[�̕`��̗L��
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@note
		�r���[�̕`�悪�K�v���ǂ������擾���܂��B<BR>
		���ꂪfalse�̏ꍇ�̓����_�����O�������̂��s���܂���B
	*/
	virtual bool IsViewRendering( eViewType ViewIndex ) = 0;

	/**
		@brief �����_�����O�̗L���ݒ�
		@author �t���`
		@param IsRenderingEnable	[in] �����_�����O�L��
		@note
		�����_�����O�̗L����ݒ肵�܂��B
	*/
	virtual void SetRenderingEnable( bool IsRenderingEnable ) = 0;

	/**
		@brief �R�}���h�̐���
		@author �t���`
		@param CameraTbl	[in] �r���[�̐����̃J����
		@note
		�`��p�̃R�}���h�𐶐����܂��B<BR>
		DrawRenderingCommand()�ƕ���ɌĂяo����悤�ɂȂ��Ă��܂��B
	*/
	virtual void CreateRenderingCommandSerial( const Kernel::Math::Camera CameraTbl[] ) = 0;

	/**
		@brief �R�}���h�̕`��
		@author �t���`
		@note
		�������Ă���R�}���h�����ۂɕ`�悵�܂��B
	*/
	virtual void DrawRenderingCommand() = 0;

	/**
		@brief �R�}���h�̃t���b�v
		@author �t���`
		@note
		�_�u���o�b�t�@�ɂȂ��Ă���`��R�}���h���t���b�v���܂��B<BR>
		�t���[���̍Ō�ŌĂяo���悤�ɂ��ĉ������B
	*/
	virtual void EndFrame() = 0;

	/**
		@brief �V���v���ȃ����_�����O����
		@author �t���`
		@param CameraTbl	[in] �r���[�̐����̃J����
		@note
		�`��̃R�}���h��������㏈���܂ł��ꊇ�ōs�����߂̃V���v���ȃ��\�b�h�ł��B
	*/
	virtual void SimpleRendering( const Kernel::Math::Camera CameraTbl[] ) = 0;

	/**
		@brief ���ʃA�j���[�V�����p�����e�N�X�`���ݒ�
		@author �t���`
		@param pTexHeightA		[in] �����e�N�X�`���P
		@param pTexHeightB		[in] �����e�N�X�`���Q
		@note
		���ʃA�j���[�V�����p�̍����e�N�X�`����ݒ肵�܂��B
	*/
	virtual void SetWaterHeightTexture( Engine::Graphics::Resource::ITexture* pTexHeightA, Engine::Graphics::Resource::ITexture* pTexHeightB ) = 0;

	/**
		@brief ������
		@author �t���`
		@param Parameter			[in] �����_���[�p�p�����[�^�[
		@param CommandBufferBytes	[in] �R�}���h�p�o�b�t�@�̃T�C�Y
		@note
		�����_���[�̏��������s���܂��B
	*/
	virtual bool Initialize( const SParameter& Parameter, Uint32 CommandBufferBytes = 16 * 1024 ) = 0;

	/**
		@brief ������
		@author �t���`
		@param Parameter			[in] �����_���[�p�p�����[�^�[
		@param Option				[in] �}�e���A������p�I�v�V����
		@param CommandBufferBytes	[in] �R�}���h�p�o�b�t�@�̃T�C�Y
		@note
		�����_���[�̏��������s���܂��B
	*/
	virtual bool Initialize( const SParameter& Parameter, const SMaterialOption& Option, Uint32 CommandBufferBytes = 16 * 1024 ) = 0;

	/**
		@brief �}�e���A������p�I�v�V�����ύX
		@author �t���`
		@param Option				[in] �}�e���A������p�I�v�V����
		@note
		�}�e���A������p�I�v�V�����̕ύX�����܂��B
	*/
	virtual void ChangeMaterialOption( const SMaterialOption& Option ) = 0;

	/**
		@brief �}�e���A������p�I�v�V�����擾
		@author �t���`
		@return �}�e���A������p�I�v�V����
		@note
		�}�e���A������p�I�v�V�����̎擾�����܂��B
	*/
	virtual const SMaterialOption& GetMaterialOption() = 0;

	/**
		@brief �p�����[�^�[�ύX
		@author �t���`
		@param Parameter	[in] �����_���[�p�p�����[�^�[
		@note
		�����_���[�̃p�����[�^�[���Q�l�Ƀ��Z�b�g�������܂��B<BR>
		�����_���[�̃p�����[�^�[��ύX�������ꍇ�ɗ��p���܂��B
	*/
	virtual void Reset( const SParameter& Parameter ) = 0;

	/**
		@brief �r���[�̐���
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param ViewRect		[in] �r���[�̕\�����`�i���T�C�Y�j
		@param IsClear		[in] �r���[���N���A�̗L��
		@param ClearColor	[in] �r���[�̃N���A�F
		@param IsAntiAlias	[in] �A���`�G�C���A�X�̗L��
		@note
		�����_���[�ɑ΂��ăr���[�̐������s���܂��B<BR>
		�r���[�̓J�����Ƒ΂ɂȂ���̂Ńr���[�𕡐��p�ӂ��邱�Ƃ�<BR>
		�o�b�N�~���[�╪���E�B���h�E�̂悤�Ȃ��̂�\�����邱�Ƃ��o���܂��B
	*/
	virtual void CreateView( eViewType ViewIndex, const RectI& ViewRect, bool IsClear, const ColorF& ClearColor, bool IsAntiAlias = false ) = 0;

	/**
		@brief �r���[�̐���
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param ViewRect		[in] �r���[�̕\�����`
		@param Size			[in] �r���[�̃T�C�Y
		@param IsClear		[in] �r���[���N���A�̗L��
		@param ClearColor	[in] �r���[�̃N���A�F
		@param IsAntiAlias	[in] �A���`�G�C���A�X�̗L��
		@note
		�����_���[�ɑ΂��ăr���[�̐������s���܂��B<BR>
		�r���[�̓J�����Ƒ΂ɂȂ���̂Ńr���[�𕡐��p�ӂ��邱�Ƃ�<BR>
		�o�b�N�~���[�╪���E�B���h�E�̂悤�Ȃ��̂�\�����邱�Ƃ��o���܂��B
	*/
	virtual void CreateView( eViewType ViewIndex, const RectI& ViewRect, const Point2DI& Size, bool IsClear, const ColorF& ClearColor, bool IsAntiAlias = false ) = 0;

	/**
		@brief �r���[�̍폜
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@note
		�����_���[�ɑ΂��ăr���[�̍폜���s���܂��B
	*/
	virtual void DeleteView( eViewType ViewIndex ) = 0;

	/**
		@brief �r���[�̕\�����`�擾
		@author ����
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@return �r���[�̕\�����`
		@note
		�r���[�̕\�����`���擾���܂��B
	*/
	virtual const RectI& GetViewRect( eViewType ViewIndex ) = 0;

	/**
		@brief �r���[�̕`���̃e�N�X�`�����擾
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param pTexture		[in] �`���̃e�N�X�`��
		@note
		�r���[�̃����_�����O������̃e�N�X�`�����擾���܂��B<BR>
		���̃e�N�X�`���̓����_�����O�^�[�Q�b�g�Ȃ̂�<BR>
		�����_���[�̕`����s���Ă���Œ��͕��t���[���X�V����܂��B
	*/
	virtual void GetViewRenderTargetTexture( eViewType ViewIndex, Engine::Graphics::Resource::ITexture*& pTexture ) = 0;

	/**
		@brief �r���[�̐����ݒ�
		@author �t���`
		@param ViewIndex		[in] �r���[�̃C���f�b�N�X
		@param IsWaterInside	[in] �����̗L��
		@note
		�r���[�ɑ΂��Đ����ɓ����Ă��邩��ݒ肵�܂��B<BR>
		�����ɓ����Ă���ꍇ�͐����V�F�[�_�[�Ń|�X�g�G�t�F�N�g��������܂��B
	*/
	virtual void SetCameraIsWaterInside( eViewType ViewIndex, bool IsWaterInside ) = 0;

	/**
		@brief �r���[�̃��t���N�V�����L���ݒ�
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param IsReflection	[in] �`��̗L��
		@param Plane		[in] ���˕���
		@note
		�r���[�ɑ΂��Ĕ��˕`��̗L����ݒ肵�܂��B<BR>
		�w�肵���r���[�𔽎˗p�̉摜�����Ɏg���悤�ɂȂ�܂��B
	*/
	virtual void SetViewReflectionMode( eViewType ViewIndex, bool IsReflection, const Kernel::Math::VectorS Point[] ) = 0;

	/**
		@brief �r���[�̃��t���N�V�����e�N�X�`���ݒ�
		@author �t���`
		@param ViewIndex		[in] �r���[�̃C���f�b�N�X
		@param pReflectTexture	[in] ���˗p�e�N�X�`��
		@note
		�r���[�ɑ΂��Ĕ��˕`��p�̃e�N�X�`����ݒ肵�܂��B
	*/
	virtual void SetViewReflectionTexture( eViewType ViewIndex, Engine::Graphics::Resource::ITexture* pReflectTexture ) = 0;

	/**
		@brief �r���[�̕\���L���ݒ�
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param IsDrawEnable	[in] �`��̗L��
		@note
		�r���[�ɑ΂��ĕ\���̗L����ݒ肵�܂��B<BR>
		�r���[�̐����ƍ폜�̓R�X�g��������̂ŕ\���̐؂�ւ��Ɋւ��Ă�<BR>
		���O�Ƀr���[�𐶐����Ă������̃��\�b�h�ɂ��؂�ւ��𐄏����܂��B
	*/
	virtual void SetViewDrawEnable( eViewType ViewIndex, bool IsDrawEnable ) = 0;

	/**
		@brief �r���[�̃����_�����O�L���ݒ�
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param IsRendering	[in] �`��̗L��
		@note
		�r���[�ɑ΂��ĕ`��̗L����ݒ肵�܂��B<BR>
		�r���[�̐����ƍ폜�̓R�X�g��������̂ŕ\���̐؂�ւ��Ɋւ��Ă�<BR>
		���O�Ƀr���[�𐶐����Ă������̃��\�b�h�ɂ��؂�ւ��𐄏����܂��B
	*/
	virtual void SetViewRenderingEnable( eViewType ViewIndex, bool IsRendering ) = 0;

	/**
		@brief �r���[�̃G�t�F�N�g�ݒ�
		@author �t���`
		@param ViewIndex			[in] �r���[�̃C���f�b�N�X
		@param IsMotionBlur			[in] ���[�V�����u���[�̗L��
		@param IsAmbientOcclusion	[in] �A���r�G���g�B���̗L��
		@param IsDepthOfField		[in] ��ʊE�[�x�̗L��
		@param IsShadowMap			[in] �V���h�E�}�b�v�̗L��
		@note
		�r���[�ɑ΂��ă|�X�g�G�t�F�N�g�̗L����ݒ肵�܂��B<BR>
		�����_���[�̐������ɗL���ɂ��ꂽ�G�t�F�N�g�Ŗ����ꍇ��<BR>
		���̃��\�b�h��true�ɂ��Ă��L���ɂȂ�܂���B
	*/
	virtual void SetViewEffect( eViewType ViewIndex, bool IsMotionBlur, bool IsAmbientOcclusion, bool IsDepthOfField, bool IsShadowMap ) = 0;

	/**
		@brief ��ʃN���A��C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		��ʃN���A��ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_AfterClear( eViewType ViewIndex, const Kernel::Delegate00& Callback ) = 0;

	/**
		@brief �s�������f���`��O�C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		�s�������f���`��O�ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_BeforeModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief �s�������f���`���C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		�s�������f���`���ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_AfterModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief ���ʕ`��O�C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		���ʕ`��O�ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_BeforeWaterDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief �������`��O�C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		�������`��O�ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_BeforeBlendModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief �������`���C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		�������`���ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_AfterBlendModelDraw( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief �|�X�g�G�t�F�N�g�O�C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		�|�X�g�G�t�F�N�g�`��O�ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_BeforePostEffect( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief �|�X�g�G�t�F�N�g��C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		�|�X�g�G�t�F�N�g�`���ɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_AfterPostEffect( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief 3D�e�L�X�g�`��p�C�x���g
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param Callback		[in] �C�x���g
		@note
		3D�e�L�X�g��`�悷��ۂɌĂяo�����R�[���o�b�N��o�^���܂��B
	*/
	virtual void SetCallbackEvent_OnDrawText3D( eViewType ViewIndex, const Kernel::Delegate01<const Kernel::Math::Camera&>& Callback ) = 0;

	/**
		@brief ���[�V�����u���[�p�����[�^�[�ݒ�
		@author �t���`
		@param Power	[in] ���[�V�����u���[�̋��x
		@note
		���[�V�����u���[�`��Ɋւ���p�����[�^�[�̐ݒ���s���܂��B
	*/
	virtual void SetParameter_MotionBlurPower( float Power ) = 0;

	/**
		@brief �\�t�g�p�[�e�B�N���p�����[�^�[�ݒ�
		@author �t���`
		@param Distance	[in] �u�����h�����鋗��
		@note
		�\�t�g�p�[�e�B�N���`��Ɋւ���p�����[�^�[�̐ݒ���s���܂��B
	*/
	virtual void SetParameter_SoftParticleDistance( float Distance ) = 0;

	/**
		@brief ��ʊE�[�x�p�����[�^�[�ݒ�
		@author �t���`
		@param NearEnd		[in] ��O�̂ڂ��������ʒu
		@param NearStart	[in] ��O�̂ڂ����J�n�ʒu
		@param FarStart		[in] ���̂ڂ����J�n�ʒu
		@param FarEnd		[in] ���̂ڂ��������ʒu
		@note
		��ʊE�[�x�Ɋւ���p�����[�^�[�̐ݒ���s���܂��B
	*/
	virtual void SetParameter_DepthOfField( float NearEnd, float NearStart, float FarStart, float FarEnd ) = 0;

	/**
		@brief �t�H�O�p�����[�^�[�ݒ�
		@author �t���`
		@param Near		[in] �t�H�O�̎n�_
		@param Far		[in] �t�H�O�̏I�_
		@param Color	[in] �t�H�O�̐F
		@note
		�t�H�O�Ɋւ���p�����[�^�[�̐ݒ���s���܂��B
	*/
	virtual void SetParameter_Fog( float Near, float Far, const Kernel::Math::VectorS& Color ) = 0;

	/**
		@brief ���O�U�����p�����[�^�[�ݒ�
		@author �t���`
		@param SunDirection	[in] �t�H�[�J�X�̃J��������̋���
		@param vSunColor	[in] �ڂ��������W
		@param Rayleigh		[in] ���C���[�U��
		@param Mie			[in] �~�[�U��
		@param G			[in] HenyeyGreenstein�p�����[�^�[
		@param Range		[in] ���z�܂ł̋����i���z�����j
		@note
		���O�U�����Ɋւ���p�����[�^�[�̐ݒ���s���܂��B
	*/
	virtual void SetParameter_Scattering( const Kernel::Math::VectorS& SunDirection, const Kernel::Math::VectorS& vSunColor, const Kernel::Math::VectorS& Rayleigh, const Kernel::Math::VectorS& Mie, float G, float Range ) = 0;

	/**
		@brief �A���r�G���g�B���p�����[�^�[�ݒ�
		@author �t���`
		@param Radius			[in] ���C�̔��a
		@param Contrast			[in] �B���ӏ��̔Z��
		@param Attenuation		[in] �B���̌�����
		@param DistanceLimit	[in] �K�p���鋗���̌��E�l
		@param StepCount		[in] ���C�̃X�e�b�v��
		@param DirectionCount	[in] ���C�̐�
		@param BlurRadius		[in] �ڂ����̔��a
		@note
		�A���r�G���g�B���Ɋւ���p�����[�^�[�̐ݒ���s���܂��B
	*/
	virtual void SetParameter_AmbientOcclusion( float Radius, float Contrast, float Attenuation, float DistanceLimit, Sint32 StepCount, Sint32 DirectionCount, Sint32 BlurRadius ) = 0;

	/**
		@brief ���C�g�p�p�����[�^�[�ݒ�
		@author �t���`
		@param Position				[in] ���C�g�̈ʒu
		@param Target				[in] ���C�g�̃^�[�Q�b�g�ʒu
		@param Color				[in] ���C�g�̐F
		@param Earth				[in] �����̒n�ʂ̐F
		@param Sky					[in] �����̋�̐F
		@param ShadowMapDistance	[in] �V���h�E�}�b�v�̗L������
		@param ShadowPower			[in] �V���h�E�̋���
		@param ShadowBias			[in] �V���h�E�̃o�C�A�X
		@note
		�V�[���S�̂ɂ�����O���[�o�����C�g�̐ݒ�����܂��B<BR>
		Position����Target������悤�ȕ��s������Earth/Sky���g�����������C�g���`���܂��B
	*/
	virtual void SetParameter_MainLight( const Kernel::Math::VectorS& Position, const Kernel::Math::VectorS& Target, const Kernel::Math::VectorS& Color, const Kernel::Math::VectorS& Earth, const Kernel::Math::VectorS& Sky, float ShadowMapDistance = 100.0f, float ShadowPower = 0.0f, float ShadowBias = 0.0f ) = 0;

	/**
		@brief ���C�g�p�p�����[�^�[�ݒ�
		@author �t���`
		@param LightNo		[in] ���C�g�ԍ� (0,1,2)
		@param Position		[in] ���C�g�̈ʒu
		@param Target		[in] ���C�g�̃^�[�Q�b�g�ʒu
		@param Color		[in] ���C�g�̐F
		@note
		�V�[���S�̂ɂ�����O���[�o���ȃT�u�̃��C�g�̐ݒ�����܂��B<BR>
		Position����Target������悤�ȕ��s�������ő�R�{�ݒ�ł��܂��B
	*/
	virtual void SetParameter_SubLight( Sint32 LightNo, const Kernel::Math::VectorS& Position, const Kernel::Math::VectorS& Target, const Kernel::Math::VectorS& Color ) = 0;

	/**
		@brief �|�C���g���C�g�p�����[�^�[�ݒ�
		@author �t���`
		@param Distance	[in] �|�C���g���C�g�𔽉f�����鎋�_����̍ő勗��
		@note
		�ݒ肵���l��莋�_���牓���ɂ��郉�C�g��K�p�����Ȃ��悤�Ƀ|�C���g���C�g��LOD�������s���܂��B<BR>
		�����l��150.0�ł��B
	*/
	virtual void SetParameter_PointLightLimitDistance( float Distance ) = 0;

	/**
		@brief �����p�p�����[�^�[�ݒ�
		@author �t���`
		@param Wrap				[in] �h�炬�̌J��Ԃ���
		@param Time				[in] �h�炬�̐i�s����
		@param Scale			[in] �h�炬�̃X�P�[���l
		@param FogModulateColor	[in] �S�̂֏�Z����F
		@note
		�����h�炵�p�̃p�����[�^�[��ݒ肵�܂��B
	*/
	virtual void SetParameter_WaterInsideWave( float Wrap, float Time, float Scale, const ColorF& FogModulateColor ) = 0;

	/**
		@brief ���ʉ��[�x�t�H�O�p�����[�^�[�ݒ�
		@author �t���`
		@param Color		[in] �F
		@param DepthLimit	[in] ���S��Color�l�ɂȂ�[�x
		@note
		���ʉ��p�[�x�t�H�O�̃p�����[�^�[��ݒ肵�܂��B
	*/
	virtual void SetParameter_WaterDepthFog( const ColorF& Color, float DepthLimit ) = 0;

	/**
		@brief ���ʘc�݃p�����[�^�[�ݒ�
		@author �t���`
		@param Value	[in] �c�ݗ�
		@note
		���ʘc�݃p�����[�^�[��ݒ肵�܂��B
	*/
	virtual void SetParameter_WaterDistortion( float Value ) = 0;

	/**
		@brief �t���l�����˃e�N�X�`���ݒ�
		@author �t���`
		@param pTexture	[in] �e�N�X�`��
		@note
		���ʂ̃t���l�����˗����`�����e�N�X�`����ݒ肵�܂��B
	*/
	virtual void SetWaterReflectFresnelTexture( Engine::Graphics::Resource::ITexture* pTexture ) = 0;

	/**
		@brief �|�C���g���C�g�폜
		@author �t���`
		@param PointLight	[in] ���C�g���
		@return ���C�g��ID
		@note
		�V�[���Ƀ|�C���g���C�g��o�^���܂��B
	*/
	virtual POINTLIGHT_HANDLE RegistPointLight( const SPointLight& PointLight ) = 0;

	/**
		@brief �|�C���g���C�g�폜
		@author �t���`
		@param PointLightID	[in] ���C�g��ID
		@note
		�V�[���ɓo�^����Ă���|�C���g���C�g���폜���܂��B
	*/
	virtual void UnregistPointLight( POINTLIGHT_HANDLE PointLightID ) = 0;

	/**
		@brief �|�C���g���C�g�X�V
		@author �t���`
		@param PointLightID	[in] ���C�g��ID
		@param PointLight	[in] ���C�g���
		@note
		�V�[���ɓo�^����Ă���|�C���g���C�g���X�V���܂��B
	*/
	virtual void UpdatePointLight( POINTLIGHT_HANDLE PointLightID, const SPointLight& PointLight ) = 0;

	/**
		@brief �V�[���p�J���[�ϊ�
		@author �t���`
		@param Color	[in] ���̐F
		@return �ϊ���̐F
		@note
		�V�[���ւ̕`����s���ꍇ�ɓK�����F�ւ̕ϊ����s���܂��B
	*/
	virtual ColorF ConvertSceneColor( const ColorF& Color ) = 0;

	/**
		@brief �G�t�F�N�g�p�o�b�t�@�̃f�o�b�O�\��
		@author �t���`
		@param ViewIndex	[in] �r���[�̃C���f�b�N�X
		@param IsEnable		[in] �\��ON/OFF
		@note
		�G�t�F�N�g�p�̃o�b�t�@����ʏ�ɕ`�悷�邩�ǂ�����ݒ肵�܂�
	*/
	virtual void EffectBufferDrawEnable( eViewType ViewIndex, bool IsEnable ) = 0;

	/**
		@brief �f�o�b�O�p�r���[�o�E���f�B���O�\��
		@author �t���`
		@param pRenderer	[in] �����_���[
		@note
		�f�o�b�O�p�ɕ`��I�u�W�F�N�g�̃r���[�{�����[����\�����܂��B
	*/
	virtual void DebugDraw_DrawObjectViewBounding( Engine::Graphics::Simple::ILineRenderer* pRenderer ) = 0;
};

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
}
}
}

/**
	@file
	@brief �����_���[�}�l�[�W���[
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
namespace Renderer
{
	enum eShaderModel
	{
		SHADER_MODEL_0_0,
		SHADER_MODEL_3_0,
		SHADER_MODEL_4_0,
		SHADER_MODEL_5_0,
	};

	/**
		@brief �����_���[�Ǘ��N���X
		@author �t���`
		@note
		�����_���[�֌W�̃}�l�[�W���[
	*/
	class IManager
		: public Interface
	{
	protected:
		virtual ~IManager(){}

	public:
		/**
			@brief �W�����������_���[����
			@author �t���`
			@param IsShaderEnable	[in] �V�F�[�_�[���p�̗L��
			@return �����_���[�C���^�[�t�F�C�X
			@note
			�W�����������_���[�̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Standard::IRenderer* CreateStandardRenderer( bool IsShaderEnable ) = 0;

		/**
			@brief �W�����������_���[�p�}�e���A������
			@author �t���`
			@return �����_���[�p�}�e���A���C���^�[�t�F�C�X
			@note
			�W�����������_���[�p�}�e���A���̃C���^�[�t�F�C�X�𐶐����܂��B
		*/
		virtual Standard::Material::Standard::IMaterial* CreateStandardRendererMaterial() = 0;
	};
}
}
}

/**
	@file
	@brief �R�A�C���^�[�t�F�C�X
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Engine
{
	/**
		@brief �R�A�C���^�[�t�F�C�X
		@author �t���`
		@note
		�G���W���ɑ΂��邷�ׂẴA�N�Z�X���������R�A�ɂȂ�C���^�[�t�F�C�X
	*/
	class ICore
		: public Interface
	{
	protected:
		virtual ~ICore(){}

	public:
		/**
			@brief ������
			@author �t���`
			@param pApplicationName		[in] �A�v���P�[�V������
			@param WindowSize			[in] �E�B���h�E�̃T�C�Y
			@param IsLogFileEnable		[in] ���O�o�͗L��
			@param IsEnableBootCheck	[in] ���d�N���u���b�N�L��
			@retval true	����
			@retval false	���s
			@note
			Core�̏��������s���܂��B<BR>
			�����ŃE�B���h�E�̐����Ȃǂ̃Z�b�g�A�b�v���s���܂��B
		*/
		virtual bool Initialize( const wchar_t* pApplicationName, const Point2DI& WindowSize, bool IsLogFileEnable, bool IsEnableBootCheck ) = 0;

		/**
			@brief ������
			@author �t���`
			@param pApplicationName		[in] �A�v���P�[�V������
			@param WindowHandle		[in] �E�B���h�E�̃n���h��
			@param IsLogFileEnable		[in] ���O�o�͗L��
			@param IsEnableBootCheck	[in] ���d�N���u���b�N�L��
			@retval true	����
			@retval false	���s
			@note
			Core�̏��������s���܂��B<BR>
			�����ŃE�B���h�E�𗘗p�����Z�b�g�A�b�v���s���܂��B
		*/
		virtual bool InitializeByExternalWindow( const wchar_t* pApplicationName, HWND WindowHandle, bool IsLogFileEnable, bool IsEnableBootCheck ) = 0;

		/**
			@brief �I��
			@author �t���`
			@note
			Core�̉���������s���܂��B
		*/
		virtual void Finalize() = 0;

		/**
			@brief �G���[�p���b�Z�[�W�{�b�N�X
			@author �t���`
			@param pTitle	[in] �^�C�g��
			@param pMessage	[in] ���b�Z�[�W(printf�`��)
			@note
			�G���[�p�̃��b�Z�[�W�{�b�N�X�\�����s���܂��B
		*/
		virtual void ErrorMessageBox( const wchar_t* pTitle, const wchar_t* pMessage, ... ) = 0;

		/**
			@brief Graphics::Manager����
			@author �t���`
			@param pTable		[in] Api�������D��x�e�[�u���iNULL�Ńf�t�H���g�l�𗘗p�j
			@param IsWaitVSync	[in] Vsync�҂��̗L��
			@retval true	����
			@retval false	���s
			@note
			Graphics�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateGraphicsManager( const Engine::Graphics::eGraphicsAPI* pTable = NULL, bool IsWaitVSync = false ) = 0;

		/**
			@brief File::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			File�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateFileManager() = 0;

		/**
			@brief Sound::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			Sound�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateSoundManager() = 0;

		/**
			@brief Network::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			Network�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateNetworkManager() = 0;

		/**
			@brief GUI::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			GUI�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateGUIManager( bool IsMouseEnable ) = 0;

		/**
			@brief Input::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			Input�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateInputManager() = 0;

		/**
			@brief Dynamics::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			Dynamics�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateDynamicsManager() = 0;

		/**
			@brief Renderer::Manager����
			@author �t���`
			@retval true	����
			@retval false	���s
			@note
			Renderer�p�̃}�l�[�W���[�𐶐����܂��B
		*/
		virtual bool CreateRendererManager() = 0;

		/**
			@brief Window::IWindow���擾
			@author �t���`
			@return Window::IWindow�C���^�[�t�F�C�X
			@note
			Window::IWindow���擾���܂��B
		*/
		virtual Window::IWindow* GetWindow() = 0;

		/**
			@brief Graphics::IManager���擾
			@author �t���`
			@return Graphics::IManager�C���^�[�t�F�C�X
			@note
			Graphics::IManager���擾���܂��B
		*/
		virtual Graphics::IManager* GetGraphicsManager() = 0;

		/**
			@brief File::IManager���擾
			@author �t���`
			@return File::IManager�C���^�[�t�F�C�X
			@note
			File::IManager���擾���܂��B
		*/
		virtual File::IManager* GetFileManager() = 0;

		/**
			@brief Sound::IManager���擾
			@author �t���`
			@return Sound::IManager�C���^�[�t�F�C�X
			@note
			Sound::IManager���擾���܂��B
		*/
		virtual Sound::IManager* GetSoundManager() = 0;

		/**
			@brief Network::IManager���擾
			@author �t���`
			@return Network::IManager�C���^�[�t�F�C�X
			@note
			Network::IManager���擾���܂��B
		*/
		virtual Network::IManager* GetNetworkManager() = 0;

		/**
			@brief GUI::IManager���擾
			@author �t���`
			@return GUI::IManager�C���^�[�t�F�C�X
			@note
			GUI::IManager���擾���܂��B
		*/
		virtual GUI::IManager* GetGUIManager() = 0;

		/**
			@brief Input::IManager���擾
			@author �t���`
			@return Input::IManager�C���^�[�t�F�C�X
			@note
			Input::IManager���擾���܂��B
		*/
		virtual Input::IManager* GetInputManager() = 0;

		/**
			@brief Dynamics::IManager���擾
			@author �t���`
			@return Dynamics::IManager�C���^�[�t�F�C�X
			@note
			Dynamics::IManager���擾���܂��B
		*/
		virtual Dynamics::IManager* GetDynamicsManager() = 0;

		/**
			@brief Renderer::IManager���擾
			@author �t���`
			@return Renderer::IManager�C���^�[�t�F�C�X
			@note
			Renderer::IManager���擾���܂��B
		*/
		virtual Renderer::IManager* GetRendererManager() = 0;
		virtual GUI::IHelper* GetGUIHelper() = 0;

		virtual float GetDeltaTime() = 0;

		/**
			@brief �A�v���P�[�V�����̃C�x���g����
			@author �t���`
			@param FramePerSec	[in] 1�b�Ԃ̃t���[����
			@note
			�A�v���P�[�V�����̃C�x���g���������܂��B<BR>
			���̒��ŃA�v���P�[�V�����ɕK�v�ȏ������s���Ă��܂��B
		*/
		virtual bool DoEvent( Uint32 FramePerSec ) = 0;

		/**
			@brief �t���[���̊J�n
			@author �t���`
			@note
			�t���[���̏������J�n���܂��B
		*/
		virtual void FrameBegin() = 0;

		/**
			@brief �t���[���̏I��
			@author �t���`
			@note
			�t���[���̏������I�����܂��B
		*/
		virtual void FrameEnd() = 0;

		/**
			@brief �A�v���P�[�V�����̏I��
			@author �t���`
			@note
			�A�v���P�[�V�����̏I�������܂��B
		*/
		virtual void Exit() = 0;

		/**
			@brief ���s�t�@�C���̃p�X���擾
			@author �t���`
			@return ���s�t�@�C���̃p�X
			@note
			���s�t�@�C���̃p�X���擾���܂��B
		*/
		virtual const wchar_t* GetModulePath() = 0;

		/**
			@brief �t���[�����[�g�擾
			@author �t���`
			@return �b�Ԃ̃t���[�����̕���
			@note
			�A�v���P�[�V�����Ń��N�G�X�g���Ă���FPS���擾���܂��B
		*/
		virtual Uint32 GetFrameRate() = 0;

		/**
			@brief FPS�擾
			@author �t���`
			@return �b�Ԃ̃t���[�����̕���
			@note
			���݂�FPS���擾���܂��B
		*/
		virtual float GetFPS() = 0;

		/**
			@brief ��ʃ��[�h�̋���/�s���ݒ�
			@author �t���`
			@param IsAllow	[in] ������ꍇ��true
			@note
			��ʃ��[�h�̕ύX�̋���/�s����ݒ肵�܂��B
		*/
		virtual void SetAllowChangeScreenMode( bool IsAllow ) = 0;

		/**
			@brief ��ʃ��[�h�ύX
			@author �t���`
			@note
			��ʃ��[�h�̕ύX���s���܂��B
		*/
		virtual void ChangeScreenMode() = 0;

		virtual Uint32 GetPhysicalCoreCount() const = 0;
		virtual Uint32 GetPhysicalCoreAffinity( Uint32 CoreIndex ) const = 0;

		/**
			@brief �^�X�N�}�l�[�W���[����
			@author �t���`
			@return �^�X�N�}�l�[�W���[
			@note
			�^�X�N�}�l�[�W���[�𐶐����܂��B
		*/
		virtual Task::ITaskManager* CreateTaskManager() = 0;
	};
}
}

namespace Selene
{
	typedef Kernel::Math::Vec2			sVec2;
	typedef Kernel::Math::Vector2		sVector2;
	typedef Kernel::Math::Vec3			sVec3;
	typedef Kernel::Math::Vector3		sVector3;
	typedef Kernel::Math::Vec4			sVec4;
	typedef Kernel::Math::Vector4		sVector4;
	typedef Kernel::Math::VecS			sVecS;
	typedef Kernel::Math::VectorS		sVectorS;
	typedef Kernel::Math::MatX			sMatX;
	typedef Kernel::Math::Matrix		sMatrix;
	typedef Kernel::Math::Quat			sQuat;
	typedef Kernel::Math::Quaternion	sQuaternion;
}
#ifdef __cplusplus_cli
#pragma managed(pop)
#endif
/**
	@file
	@brief Selene�A�N�Z�X�pLibrary
	@author �t���`
*/


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/**
	@brief �G���W���̏�����
	@author �t���`
	@param pModulePath	[in] Selene��DLL�̃p�X
	@retval true	����������
	@retval false	���������s
	@note
	Selene�̃G���W���S�̂̏��������s���܂��B<BR>
	���̊֐������s����̂�pModulePath�Ŏw�肵��DLL��<BR>
	�ǂݍ��߂Ȃ��ꍇ�ƁA���łɏ������ς݂̏ꍇ�����ł��B
*/
bool SLN_STDCALL InitializeEngine( const wchar_t* pModulePath );

/**
	@brief �G���W���̉��
	@author �t���`
	@note
	Selene�̃G���W���S�̂̉�����s���܂��B<BR>
	�A�v���P�[�V�����̏I���O�̕K���Ăяo���ĉ������B
*/
void SLN_STDCALL FinalizeEngine();

/**
	@brief �R�A�̐���
	@author �t���`
	@return �R�A�̃|�C���^�[
	@note
	Selene�փA�N�Z�X����ׂ�ICore���쐬���܂��B<BR>
	�P�̃A�v���P�[�V�����ɕt���P������������܂���B<BR>
	�悤����ɃV���O���g���ɂȂ��Ă��܂��B
*/
Engine::ICore* SLN_STDCALL CreateCore();

/**
	@brief �R�A�̎擾
	@author �t���`
	@return �R�A�̃|�C���^�[
	@note
	Selene�փA�N�Z�X����ׂ�ICore���擾���܂��B
*/
Engine::ICore* SLN_STDCALL GetCore();

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
#ifdef __cplusplus_cli
#pragma managed(pop)
#endif
