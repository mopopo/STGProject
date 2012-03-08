#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

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

	/**
		@brief �Q�������W
		@author �t���b
		@note �Q�����̍��W�������N���X
	*/
	template <typename T>
	class Point2D;

	typedef Point2D<float>	Point2DF;
	typedef Point2D<Sint32>	Point2DI;

	/**
		@brief �R�������W
		@author �t���b
		@note �R�����̍��W�������N���X
	*/
	template <typename T>
	class Point3D;

	typedef Point3D<float>	Point3DF;
	typedef Point3D<Sint32>	Point3DI;

	/**
		@brief ��`��`
		@author �t���b
		@note ��`�̒�`
	*/
	template <typename T>
	class Rect;

	typedef Rect<float>		RectF;
	typedef Rect<Sint32>	RectI;

	/**
		@brief �F��`
		@author �t���b
		@note �F�̒�`
	*/
	struct ColorU;

	/**
		@brief �F��`
		@author �t���b
		@note �F�̒�`
	*/
	struct ColorF;

	/**
		@brief �C���^�[�t�F�C�X
		@author �t���`

		@note
		�C���^�[�t�F�C�X�̊��N���X
	*/
	class Interface;

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
			enum eLock;

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
			enum eButtonState;

			/**
				@brief ���z�L�[�R�[�h
				@author �t���`
			*/
			enum eKeyCode;

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
			struct SHostInfo;

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
				enum eProxyType;

				/**
					@brief �{�f�B�̎��
					@author �t���`
				*/
				enum eBodyType;

				/**
					@brief �ڐG�_���
					@author �t���`
				*/
				struct SContactInfo;

				/**
					@brief �����I�u�W�F�N�g
					@author �t���`
				*/
				struct CompoundShape;

				/**
					@brief �����I�u�W�F�N�g��
					@author �t���`
				*/
				struct CompoundShapeSphere;

				/**
					@brief �����I�u�W�F�N�g�J�v�Z��
					@author �t���`
				*/
				struct CompoundShapeCapsule;

				/**
					@brief �����I�u�W�F�N�g��
					@author �t���`
				*/
				struct CompoundShapeBox;
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

	namespace Plugin
	{
		namespace File
		{
			/**
				@brief Crypt�v���O�C���C���^�[�t�F�C�X
				@author �t���`
			*/
			class ICrypt;

			typedef ICrypt* (__stdcall* CreateCryptInterfaceProc)( const char* );
		}
	}
}