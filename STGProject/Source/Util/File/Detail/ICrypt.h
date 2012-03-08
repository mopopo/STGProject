#pragma once

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
namespace Selene
{
namespace Plugin
{
namespace File
{

//---------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------
/**
	@brief Crypt�v���O�C���C���^�[�t�F�C�X
	@author �t���`
	@note
	�Ǝ��̈Í��v���O�C�����쐬����ꍇ��<BR>
	���̃C���^�[�t�F�C�X�N���X���p�����Ď��������ĉ������B
*/
class ICrypt
{
protected:
	virtual ~ICrypt() { }

public:
	/**
		@brief ��������p
		@note
		�����ŉ���������s��<BR>
		DLL�����Ȃ̂ŊO����delete�͏o���Ȃ��B
	*/
	virtual void Release() = 0;
	/**
		@brief �Í���
		@param pInput	[in] �Í��O���f�[�^
		@param pOutput	[in] �Í����f�[�^�o�͐�
		@param Size		[in] pInput�ŗ^����ꂽ�f�[�^�̃T�C�Y
		@param Offset	[in] �f�[�^�̈ʒu�i�t�@�C���̐擪����̃I�t�Z�b�g�j
		@note
		�^����ꂽ�f�[�^�����ɈÍ������܂��B
	*/
	virtual void Encrypt( const unsigned char* pInput, unsigned char* pOutput, unsigned long Size, unsigned long Offset ) = 0;
	/**
		@brief �Í�����
		@param pInput	[in] �Í����f�[�^
		@param pOutput	[in] �Í������f�[�^�o�͐�
		@param Size		[in] pInput�ŗ^����ꂽ�f�[�^�̃T�C�Y
		@param Offset	[in] �f�[�^�̈ʒu�i�t�@�C���̐擪����̃I�t�Z�b�g�j
		@note
		�^����ꂽ�f�[�^�����ɈÍ����������܂��B
	*/
	virtual void Decrypt( const unsigned char* pInput, unsigned char* pOutput, unsigned long Size, unsigned long Offset ) = 0;
};

//---------------------------------------------------------------------------------------------------
//
//---------------------------------------------------------------------------------------------------
typedef ICrypt* (__stdcall* CreateCryptInterfaceProc)( const char* );

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
}
}
}