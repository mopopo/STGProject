#include "PCH.h"
#include "Manager.h"

using namespace Selene;
using namespace Game;
using namespace Util::Sprite;
using namespace std;
using namespace Util::Consts::Sprite;

namespace
{
	// �e�N�X�`���쐬�ŗ��p����p�����[�^�[
	static const Engine::Graphics::STextureLoadParameter LOAD_PARAM = {
		false,					// �t�@�C�����炻�̂܂ܓǂݍ��ނ��ǂ����itrue�Ȃ瑼�̃t���O��S�������j
		false,					// ���k�e�N�X�`���̗L��
		true,					// �~�b�v�}�b�v�̗L��
		1,						// ���̃T�C�Y�ɑ΂��ď��Z���鐔�i2�Ȃ�256x256������I��128x128�Ő����j
		ColorF( 0, 0, 0, 0 ),	// �J���[�L�[�𗘗p���Ȃ��ꍇ��(0,0,0,0)
	};

	static float decShakeAmount = 1.0f;
	static Point2DF xyShakeAmount;
	static Point2DF currentShakeAmount;
	static bool shakeFlag = true;
	static Kernel::Math::Random random;
}


// �t���[�����̍X�V
void Manager::Update()
{
	if( shakeFlag )
	{
		int dir = random.GetInt( 0, 2 );
		switch( dir )
		{
		case 0:
			currentShakeAmount.x = -xyShakeAmount.x;
			break;
		case 1:
			currentShakeAmount.x = 0;
			break;
		case 2:
			currentShakeAmount.x = xyShakeAmount.x;
			break;
		default:
			assert( false );
			break;
		}
		dir = random.GetInt( 0, 2 );
		switch( dir )
		{
		case 0:
			currentShakeAmount.y = -xyShakeAmount.y;
			break;
		case 1:
			currentShakeAmount.y = 0;
			break;
		case 2:
			currentShakeAmount.y = xyShakeAmount.y;
			break;
		default:
			assert( false );
			break;
		}

		xyShakeAmount -= decShakeAmount;
		if( xyShakeAmount.x < 0 )
		{
			xyShakeAmount.x = 0;
		}
		if( xyShakeAmount.y < 0 )
		{
			xyShakeAmount.y = 0;
		}
	}
}


// �l�p�`�̕`��
void Manager::Draw( const DrawParameter &param )
{
	Util::Core::PSpriteRenderer pSprite = Core::Manager::GetSpriteRenderer();

	RectF dst = param.GetDst();
	if( param.IsShakable() )
	{
		dst.x += currentShakeAmount.x;
		dst.y += currentShakeAmount.y;
	}
	if( param.IsFlipedX() )
	{
		dst.x += dst.w;
		dst.w *= -1;
	}
	if( param.IsFlipedY() )
	{
		dst.y += dst.h;
		dst.h *= -1;
	}

	pSprite->SquareRequest( 
		dst, 
		param.GetPriority(), 
		param.GetColor(), 
		param.GetSrc(), 
		param.GetTexture().get(), 
		param.IsFiltering(), 
		false, 
		static_cast<Engine::Graphics::State::eAlphaBlend>( param.GetAlphaBlend() ), 
		PI * param.GetRotDegree()/180.0f, 
		param.GetRotOffset() );
}


// �e�N�X�`����ǂݍ���
PTexture Manager::LoadTexture( 
	const std::wstring &fileName, bool mipmap, const Selene::ColorF &transColor )
{
	File::PFile pFile = File::Manager::Open( LOAD_TOP_PATH + fileName );

	return LoadTexture( pFile, mipmap, transColor );
}

PTexture Manager::LoadTexture( 
	Util::File::PFile pFile, bool mipmap, const Selene::ColorF &transColor )
{
	Engine::Graphics::STextureLoadParameter loadParam = LOAD_PARAM;
	loadParam.IsMipmapEnable = mipmap;
	loadParam.ColorKey = transColor;

	PTexture pTexture = MakeIntrusivePtr( 
		Core::Manager::GetGraphicsManager()->CreateTexture( 
		pFile->GetData(), 
		pFile->GetSize(), 
		pFile->GetFileName(), 
		loadParam ) );

	if( !pTexture )
	{
		THROW( 
			Exception::InvalidTexture( pFile->GetFileName() ) );
	}

	return pTexture;
}

void Manager::LoadTexture( const TextureSrcMap &srcFilePathMap, 
								   TextureMap &textures )
{
	textures.clear();

	vector<wstring> filePathList;
	typedef pair<wstring, ColorF> SrcFilePathElem;
	foreach( const SrcFilePathElem &elem, srcFilePathMap )
	{
		filePathList.push_back( LOAD_TOP_PATH + elem.first );
	}

	File::FileMap files;
	File::Manager::Open( filePathList, files );

	list<wstring> invalidTextureList;
	foreach( const SrcFilePathElem &elem, srcFilePathMap )
	{
		Engine::Graphics::STextureLoadParameter loadParam = LOAD_PARAM;
		loadParam.ColorKey = elem.second;

		File::PFile pFile = files[ elem.first ];

		PTexture pTexture = MakeIntrusivePtr( 
			Core::Manager::GetGraphicsManager()->CreateTexture( 
			pFile->GetData(), 
			pFile->GetSize(), 
			pFile->GetFileName(), 
			loadParam ) );

		if( !pTexture )
		{
			invalidTextureList.push_back( elem.first );
		}

		textures[ elem.first ] = pTexture;
	}

	if( !invalidTextureList.empty() )
	{
		THROW( 
			Exception::InvalidTexture( invalidTextureList ) );
	}
}


// ��ʂ̐U���̐ݒ�
void Manager::SetShake( float amount, float decAmount )
{
	SetShake( Point2DF( amount, amount ), decAmount );
}

void Manager::SetShake( const Point2DF &amount, float decAmount )
{
	decShakeAmount = decAmount;
	xyShakeAmount.x = amount.x;
	xyShakeAmount.y = amount.y;
}

// �U���̈ꎞ��~
void Manager::StopShake()
{
	shakeFlag = false;
}

// �U���̍ĊJ
void Manager::StartShake()
{
	shakeFlag = true;
}

// �U���̃��Z�b�g
void Manager::ResetShake()
{
	SetShake( 0 );
	StartShake();
}

// �U���ʂ̎擾
Point2DF Manager::GetCurrentShakeAmount()
{
	return currentShakeAmount;
}