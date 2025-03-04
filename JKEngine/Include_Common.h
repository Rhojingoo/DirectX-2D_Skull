#pragma once
#include "..\\Engine_SOURCE\\jkApplication.h"
#include "..\\Engine_SOURCE\\jkSceneManager.h"
#include "..\\Engine_SOURCE\\jkCollisionManager.h"
#include "..\\Engine_SOURCE\\jkGameObject.h"
#include "..\\Engine_SOURCE\\jkObject.h"
#include "..\\Engine_SOURCE\\jkResources.h"
#include "..\\Engine_SOURCE\\jkGraphicDevice_Dx11.h"  
#include "..\\Engine_SOURCE\\jkGraphics.h" 


//renderer & graphic
#include "..\\Engine_SOURCE\\jkMesh.h"
#include "..\\Engine_SOURCE\\jkTexture.h"
#include "..\\Engine_SOURCE\\jkImage.h"
#include "..\\Engine_SOURCE\\jkInput.h"
#include "..\\Engine_SOURCE\\jkTime.h"
#include "..\\Engine_SOURCE\\jkConstantBuffer.h"
#include "..\\Engine_SOURCE\\jkStructuredBuffer.h"



//component
#include "..\\Engine_SOURCE\\jkTransform.h"
#include "..\\Engine_SOURCE\\jkComponent.h"
#include "..\\Engine_SOURCE\\jkAnimator.h"
#include "..\\Engine_SOURCE\\jkCamera.h"
#include "..\\Engine_SOURCE\\jkCollider2D.h"
#include "..\\Engine_SOURCE\\jkMeshRenderer.h"
#include "..\\Engine_SOURCE\\jkBaseRenderer.h"
#include "..\\Engine_SOURCE\\jkAnimator.h"
#include "..\\Engine_SOURCE\\jkRigidBody.h"



//추가기능
#include "..\\Engine_SOURCE\\jkTileMap.h"
#include "..\\Engine_SOURCE\\jkXmlParser.h"
#include "..\\Engine_SOURCE\\jkUI_Mouse.h"
#include "..\\Engine_SOURCE\\jkTile_Mouse.h"
#include "..\\Engine_SOURCE\\jkAnimation.h"


//스크립트
#include "..\\Engine_SOURCE\\jkScript.h"
#include "jkGridScript.h"
#include "jkCameraScript.h"
#include "jkPlayerScript.h"


//배경
#include "BG.h"
#include "jkBack_ground.h"
#include "jkCloud.h"
#include "jkTile_Ground.h"
#include "Ground_Map.h"
#include "Sky_Ground.h"
#include "Ground_and_Wall.h"


// Stage_Door
#include "Stage1_Door.h"
#include "Stage_end_wall.h"
#include "Stage_end_table.h"


//타격관련
#include "Attack_HitBox.h"
#include "HitBox_Player.h"
#include "HitBox_Monster.h"


//Npc
#include "NPC_by_stage.h"


//PLAYER
#include "Player.h"
#include "Skul_Basic.h"
#include "Skul_Nohead.h"
#include "Skul_Spear.h"
#include "Skul_Wolf.h"
#include "Skul_Sword.h"
#include "Skul_Thief.h"
#include "Skul_head.h"


//보스
#include "Boss.h"
#include "Yggdrasil.h"
#include "Yggdrasil_Body.h"
#include "Yggdrasil_Face.h"
#include "Yggdrasil_Chin.h"
#include "Yggdrasil_Hand_Left.h"
#include "Yggdrasil_Hand_Right.h"
#include "Layana_Sisters.h"
#include "Layana_LongHair.h"
#include "Layana_ShortHair.h"
#include "Layana_Dark_Awaken.h"


//미니보스
#include "Mini_Boss.h"
#include "Knight_male.h"
#include "Archer.h"
#include "Mage.h"
#include "Cleric.h"

//몬스터
#include "Monster.h"
#include "Monster_Hammer.h"
#include "Monster_warrior.h"
#include "Stone_wizard.h"
#include "Monster_BigEnt.h"
#include "Monster_GreenTree.h"
#include "Monster_BlossomEnt.h"
#include "Monster_Goldwarrior.h"
#include "Monster_GoldHammer.h"

#include "Monster_GoldHammer.h"
#include "Monster_Goldwarrior.h"
#include "Monster_LionSpear.h"
#include "Monster_LionWarrior.h"
#include "Monster_LionWizard.h"



//미사일
#include "Bullet.h"
#include "Yggdrasil_BasicBullet.h"
#include "Yggdrasil_Energy_Bomb.h"
#include "Yggdrsil_Energy_Corps.h"
#include "Homing_Pierce_LongHair.h"
#include "Homing_Pierce_ShortHair.h"
#include "Rising_Pierce.h"
#include "Dimension_Pierce.h"
#include "MiniBoss_Bullet_Archer.h"



//이펙트
#include "Effect.h"
//Yggdrasil Effect
#include "Yggdrasil_Effect.h"
// Layana_Sisters Effect


#include "Dimension_Pierce_BossEffect.h"
#include "Dimension_Pierce_BulletEffect.h"
#include "TwinMeteor_Boss.h"
#include "TwinMeteor_Effect.h"
#include "Yggdrasil_EnergyBullet_Effect.h"


//UI
#include "UI.h"
#include "Player_State_UI.h"
#include "Player_Hp_Bar.h"
#include "Face_UI.h"
#include "Main_Camera.h"
#include "UI_Camera.h"
#include "Grid.h"


#include "jkTitleScene.h"
#include "jkPlayScene.h"
#include "Castle_Area.h"
#include "OutSide_CastleArea.h"
#include "jkStage1_1.h"
#include "jkStage1_MiniBoss.h"
#include "jkStage1_2.h"
#include "jkStage1_Boss.h"
#include "jkStage2_1.h"
#include "jkStage2_MiniBoss.h"
#include "jkStage2_2.h"
#include "jkStage2_Boss.h"

