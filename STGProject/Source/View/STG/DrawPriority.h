#pragma once


//----------------------------------------------------------------------------------
//	Class
//----------------------------------------------------------------------------------

namespace Game
{
namespace View
{
namespace STG
{
	// �`��D��x
	enum DRAW_PRIORITY
	{
		// �w�i
		PRI_BACKGROUND_B3, 
		PRI_BACKGROUND_B2, 
		PRI_BACKGROUND_B1, 
		PRI_BACKGROUND, 
		PRI_BACKGROUND_2, 
		PRI_BACKGROUND_3, 
		PRI_BACKGROUND_4, 

		// �G
		PRI_ENEMY_B3, 
		PRI_ENEMY_B2, 
		PRI_ENEMY_B1, 
		PRI_ENEMY, 
		PRI_ENEMY_2, 
		PRI_ENEMY_3, 
		PRI_ENEMY_4, 

		// �X�R�A�{���\��
		PRI_SCORE_RATE, 
		PRI_SCORE_RATE_2, 
		PRI_SCORE_RATE_3, 

		// ���@�I�v�V����
		PRI_MYSHIP_OPTION_B3, 
		PRI_MYSHIP_OPTION_B2, 
		PRI_MYSHIP_OPTION_B1, 
		PRI_MYSHIP_OPTION, 
		PRI_MYSHIP_OPTION_2, 
		PRI_MYSHIP_OPTION_3, 
		PRI_MYSHIP_OPTION_4, 

		// ���@�V���b�g
		PRI_MYSHOT_B3, 
		PRI_MYSHOT_B2, 
		PRI_MYSHOT_B1, 
		PRI_MYSHOT, 
		PRI_MYSHOT_2, 
		PRI_MYSHOT_3, 
		PRI_MYSHOT_4, 

		// �A�C�e��
		PRI_ITEM_B3, 
		PRI_ITEM_B2, 
		PRI_ITEM_B1, 
		PRI_ITEM, 
		PRI_ITEM_2, 
		PRI_ITEM_3, 
		PRI_ITEM_4, 

		// �G�ւ̃��b�N�}�[�J�[
		PRI_LOCKMARKER_B3, 
		PRI_LOCKMARKER_B2, 
		PRI_LOCKMARKER_B1, 
		PRI_LOCKMARKER, 
		PRI_LOCKMARKER_2, 
		PRI_LOCKMARKER_3, 
		PRI_LOCKMARKER_4, 

		// ���@
		PRI_MYSHIP_B3, 
		PRI_MYSHIP_B2, 
		PRI_MYSHIP_B1, 
		PRI_MYSHIP, 
		PRI_MYSHIP_2, 
		PRI_MYSHIP_3, 
		PRI_MYSHIP_4, 
		// ���@�o���A
		PRI_MYBARRIER, 

		// PrimalArmor�̃G�t�F�N�g
		PRI_PA_EFFECT, 
		// �����G�t�F�N�g
		PRI_EXPLOSION, 

		// �G�e
		PRI_ENEMYBULLET_B3, 
		PRI_ENEMYBULLET_B2, 
		PRI_ENEMYBULLET_B1, 
		PRI_ENEMYBULLET, 
		PRI_ENEMYBULLET_2, 
		PRI_ENEMYBULLET_3, 
		PRI_ENEMYBULLET_4, 
		// �G�e�_���[�W���̃G�t�F�N�g
		PRI_ENEMYBULLET_DAMAGED, 

		// ���@�̓����蔻��̖ڈ�
		PRI_MYSHIP_HITMARK, 

		// �GHP�Q�[�W
		PRI_ENEMY_HPGAUGE, 

		// Warning�\��
		PRI_WARNING, 

		// Result�\��
		PRI_RESULT_B3, 
		PRI_RESULT_B2, 
		PRI_RESULT_B1, 
		PRI_RESULT, 
		PRI_RESULT_2, 
		PRI_RESULT_3, 
		PRI_RESULT_4, 

		// ���\���̈�̔w�i
		PRI_INFAREA_BACK_B3, 
		PRI_INFAREA_BACK_B2, 
		PRI_INFAREA_BACK_B1, 
		PRI_INFAREA_BACK, 
		PRI_INFAREA_BACK_2, 
		PRI_INFAREA_BACK_3, 
		PRI_INFAREA_BACK_4, 
		// ���\���̈�̕�����
		PRI_INFAREA_STR, 

		// �|�[�Y��ʂ̔w�i
		PRI_PAUSE_BACK_B3, 
		PRI_PAUSE_BACK_B2, 
		PRI_PAUSE_BACK_B1, 
		PRI_PAUSE_BACK, 
		PRI_PAUSE_BACK_2, 
		PRI_PAUSE_BACK_3, 
		PRI_PAUSE_BACK_4, 
		// �|�[�Y��ʂ̕�����
		PRI_PAUSE_STR, 

		// �t�F�[�h�C��/�A�E�g�p
		PRI_FADE_EFFECT, 

		// �f�o�b�O�p������
		PRI_DEBUG_STR, 
	};
}
}
}