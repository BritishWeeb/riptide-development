#include "Settings.h"

//[enc_string_enable /]
//[junk_enable /]

using namespace Client;

namespace Settings
{
	void LoadSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());
		Aimbot::aim_Backtrack = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK, Aimbot::aim_Backtrack) != false;
		Aimbot::aim_Backtracktickrate = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK_TICK, Aimbot::aim_Backtracktickrate);
		Aimbot::aim_Deathmatch = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DEATHMATCH, Aimbot::aim_Deathmatch);
		Aimbot::aim_WallAttack = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_WALLATTACK, Aimbot::aim_WallAttack);
		Aimbot::aim_CheckSmoke = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_CHECKSMOKE, Aimbot::aim_CheckSmoke);
		Aimbot::aim_AntiJump = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_ANTIJUMP, Aimbot::aim_AntiJump);
		Aimbot::aim_RcsType = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_RCSTYPE, Aimbot::aim_RcsType);
		Aimbot::aim_DrawFov = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWFOV, Aimbot::aim_DrawFov);
		Aimbot::aim_DrawSpot = CSX::Cvar::LoadCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWSPOT, Aimbot::aim_DrawSpot);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			// ���������
			if (i <= 9)
			{
				Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, 0);
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 35);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 5);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCS, 50);
				Aimbot::weapon_aim_settings[i].aim_AutoPistol = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_AUTOPISTOL, 0);
			}

			// ��������
			if (i >= 10 && i <= 30)
			{
				Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, 0);
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 35);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 5);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCS, 50);
				Aimbot::weapon_aim_settings[i].aim_RcsFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, 50);
				Aimbot::weapon_aim_settings[i].aim_RcsSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_RcsClampType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, 0);
			}

			// ���������
			if (i >= 31 && i <= 32)
			{
				Aimbot::weapon_aim_settings[i].aim_Active = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, 0);
				Aimbot::weapon_aim_settings[i].aim_Smooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, 50);
				Aimbot::weapon_aim_settings[i].aim_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOV, 35);
				Aimbot::weapon_aim_settings[i].aim_FovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, 1);
				Aimbot::weapon_aim_settings[i].aim_BestHit = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, 0);
				Aimbot::weapon_aim_settings[i].aim_Spot = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, 5);
				Aimbot::weapon_aim_settings[i].aim_Delay = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, 0);
				Aimbot::weapon_aim_settings[i].aim_Rcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_AIMBOT_RCS, 50);
			}
		}

		Triggerbot::trigger_Enable = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_ENABLE, Triggerbot::trigger_Enable);
		Triggerbot::trigger_Deathmatch = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DEATHMATCH, Triggerbot::trigger_Deathmatch) != false;
		Triggerbot::trigger_WallAttack = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_WALLATTACK, Triggerbot::trigger_WallAttack) != false;
		Triggerbot::trigger_FastZoom = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_FASTZOOM, Triggerbot::trigger_FastZoom) != false;
		Triggerbot::trigger_Key = TriggerCharToKey(CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_KEY, CVAR_KEY_MOUSE3).c_str());
		Triggerbot::trigger_KeyMode = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_KEYMODE, Triggerbot::trigger_KeyMode);
		Triggerbot::trigger_SmokCheck = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_SMOKCHECK, Triggerbot::trigger_SmokCheck) != false;
		Triggerbot::trigger_DrawFov = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOV, Triggerbot::trigger_DrawFov) != false;
		Triggerbot::trigger_DrawSpot = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWSPOT, Triggerbot::trigger_DrawSpot) != false;
		Triggerbot::trigger_DrawFovAssist = CSX::Cvar::LoadCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOVASSIST, Triggerbot::trigger_DrawFovAssist) != false;

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			Triggerbot::weapon_trigger_settings[i].trigger_DistanceMin = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMIN, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_DistanceMax = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMAX, 5000);
			Triggerbot::weapon_trigger_settings[i].trigger_Fov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_FOV, 10);
			Triggerbot::weapon_trigger_settings[i].trigger_DelayBefore = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DELAYBEFORE, 10);
			Triggerbot::weapon_trigger_settings[i].trigger_DelayAfter = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_DELAYAFTER, 100);
			Triggerbot::weapon_trigger_settings[i].trigger_HeadOnly = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_HEADONLY, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_HitGroup = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_HITGROUP, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_Assist = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSIST, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistRcs = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTRCS, 0);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistFov = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOV, 20);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistFovType = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOVTYPE, 1);
			Triggerbot::weapon_trigger_settings[i].trigger_AssistSmooth = CSX::Cvar::LoadCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTSMOOTH, 5);
		}

		Esp::esp_Style = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_STYLE, Esp::esp_Style);
		Esp::esp_Size = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SIZE, Esp::esp_Size);
		Esp::esp_CapitalToggle = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CAPITALTOGGLE, Esp::esp_CapitalToggle);
		Esp::esp_Line = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_LINE, Esp::esp_Line) != false;
		Esp::esp_Outline = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_OUTLINE, Esp::esp_Outline) != false;

		Esp::esp_Name = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_NAME, Esp::esp_Name) != false;
		Esp::esp_Time = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_TIME, Esp::esp_Time) != false;
		Esp::esp_Watermark = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WATER, Esp::esp_Watermark) != false;
		Esp::esp_Cheatbuild = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHEATBUILD, Esp::esp_Cheatbuild) != false;
		Esp::esp_HitMarker = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_ENABLED, Esp::esp_HitMarker) != false;
		Esp::esp_HitMarkerSound = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_COMBO, Esp::esp_HitMarkerSound) != false;
		Esp::esp_Rank = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_RANK, Esp::esp_Rank) != false;
		Esp::esp_Health = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HEALTH, Esp::esp_Health);
		Esp::esp_Armor = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_ARMOR, Esp::esp_Armor);
		Esp::esp_Weapon = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WEAPON, Esp::esp_Weapon) != false;
		Esp::esp_Ammo = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_AMMO, Esp::esp_Ammo) != false;
		Esp::esp_Distance = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_DISTANCE, Esp::esp_Distance) != false;
		Esp::esp_Sound = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SOUND, Esp::esp_Sound) != false;
		Esp::esp_GrenadePrediction = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_GRENADEPREDICTION, Esp::esp_GrenadePrediction) != false;

		Esp::esp_beams_tracer = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BEAMS, Esp::esp_beams_tracer) != false;

		Esp::esp_Skeleton = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_SKELETON, Esp::esp_Skeleton) != false;
		Esp::esp_BulletTrace = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BULLETTRACE, Esp::esp_BulletTrace);
		Esp::esp_Team = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_TEAM, Esp::esp_Team) != false;
		Esp::esp_Enemy = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_ENEMY, Esp::esp_Enemy) != false;
		Esp::esp_Visible = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_VISIBLE, Esp::esp_Visible);
		Esp::esp_ChamsVisible = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHAMSVISIBLE, Esp::esp_ChamsVisible);

		Esp::esp_Chams = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_CHAMS, Esp::esp_Chams);
		Esp::esp_Bomb = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BOMB, Esp::esp_Bomb) != false;
		Esp::esp_BombTimer = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BOMBTIMER, Esp::esp_BombTimer);
		Esp::flTracersDuration = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BEAMS_DURATION, Esp::flTracersDuration);
		Esp::flTracersWidth = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_BEAMS_WIDTH, Esp::flTracersWidth);
		Esp::esp_WorldWeapons = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WORLDWEAPONS, Esp::esp_WorldWeapons) != false;
		Esp::esp_WorldGrenade = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WORLDGRENADE, Esp::esp_WorldGrenade) != false;
		Esp::esp_HealthChams = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_HEALTH_CHAMS, Esp::esp_Chams) != false;

		string esp_Color_CT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_CT, "0,164,255");
		string esp_Color_TT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_TT, "255,64,64");
		string esp_Color_VCT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VCT, "124,252,0");
		string esp_Color_VTT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VTT, "124,252,0");
		
		CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_WALLSOPACITY, Settings::Esp::esp_WallsOpacity);

		string chams_Color_CT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_CT, "0,164,255");
		string chams_Color_TT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_TT, "255,64,64");
		string chams_Color_VCT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VCT, "124,252,0");
		string chams_Color_VTT = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VTT, "124,252,0");

		string Color_HITMARKER = CSX::Cvar::LoadCvar(VISUAL_TEXT, "esp_HitMarkerColor", "255,0,0");
		string GrenadeHelper = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_GrenadeHelper, "255,0,0");
		string BulletBeamsColor = CSX::Cvar::LoadCvar(VISUAL_TEXT, CVAR_ESP_COLOR_BulletBeams, "255,0,0");

		ScanColorFromCvar(Color_HITMARKER.c_str(), Esp::esp_HitMarkerColor);
		ScanColorFromCvar(BulletBeamsColor.c_str(), Esp::flTracer_Beam);
		ScanColorFromCvar(GrenadeHelper.c_str(), Settings::Esp::GrenadeHelper);
		ScanColorFromCvar(BulletBeamsColor.c_str(), Settings::Esp::GrenadeHelper);


		ScanColorFromCvar(esp_Color_CT.c_str(), Settings::Esp::esp_Color_CT);
		ScanColorFromCvar(esp_Color_TT.c_str(), Settings::Esp::esp_Color_TT);
		ScanColorFromCvar(esp_Color_VCT.c_str(), Settings::Esp::esp_Color_VCT);
		ScanColorFromCvar(esp_Color_VTT.c_str(), Settings::Esp::esp_Color_VTT);

		ScanColorFromCvar(chams_Color_CT.c_str(), Settings::Esp::chams_Color_CT);
		ScanColorFromCvar(chams_Color_TT.c_str(), Settings::Esp::chams_Color_TT);
		ScanColorFromCvar(chams_Color_VCT.c_str(), Settings::Esp::chams_Color_VCT);
		ScanColorFromCvar(chams_Color_VTT.c_str(), Settings::Esp::chams_Color_VTT);

		Radar::rad_Active = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ACTIVE, Radar::rad_Active) != false;
		Radar::rad_Team = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_TEAM, Radar::rad_Team) != false;
		Radar::rad_Enemy = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ENEMY, Radar::rad_Enemy) != false;
		Radar::rad_Sound = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_SOUND, Radar::rad_Sound) != false;
		Radar::rad_InGame = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_INGAME, Radar::rad_InGame) != false;
		Radar::rad_Range = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_RANGE, Radar::rad_Range);
		Radar::rad_Alpha = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_ALPHA, Radar::rad_Alpha);

		string Color_CT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_CT, "0,164,255");
		string Color_TT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_TT, "255,64,64");
		string Color_VCT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_VCT, "0,255,0");
		string Color_VTT = CSX::Cvar::LoadCvar(RADAR_TEXT, CVAR_RAD_COLOR_VTT, "0,255,0");

		ScanColorFromCvar(Color_CT.c_str(), Radar::rad_Color_CT);
		ScanColorFromCvar(Color_TT.c_str(), Radar::rad_Color_TT);
		ScanColorFromCvar(Color_VCT.c_str(), Radar::rad_Color_VCT);
		ScanColorFromCvar(Color_VTT.c_str(), Radar::rad_Color_VTT);

		Knifebot::knf_Active = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ACTIVE, Knifebot::knf_Active) != false;
		Knifebot::knf_Team = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_TEAM, Knifebot::knf_Team) != false;
		Knifebot::knf_Attack = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ATTACK, Knifebot::knf_Attack);
		Knifebot::knf_DistAttack = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK, Knifebot::knf_DistAttack);
		Knifebot::knf_DistAttack2 = CSX::Cvar::LoadCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK2, Knifebot::knf_DistAttack2);

		Skin::knf_ct_model = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_CT_MODEL, Skin::knf_ct_model);
		Skin::knf_ct_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_CT_SKIN, Skin::knf_ct_skin);
		Skin::knf_tt_model = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_TT_MODEL, Skin::knf_tt_model);
		Skin::knf_tt_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_TT_SKIN, Skin::knf_tt_skin);
		Skin::gloves_skin = CSX::Cvar::LoadCvar(SKIN_TEXT, CVAR_SKIN_GLOVES, Skin::gloves_skin);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackPaintKit = CSX::Cvar::LoadCvar(SKIN_TEXT, pWeaponData[i], 0);
		}

		g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality = CSX::Cvar::LoadCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality);
		g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality = CSX::Cvar::LoadCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].iEntityQuality = CSX::Cvar::LoadCvar(SKIN_TEXT_QUALITY, pWeaponData[i], 0);
		}

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackStatTrak = CSX::Cvar::LoadCvar(SKIN_TEXT_STAT, pWeaponData[i], -1);
		}


		g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear = CSX::Cvar::LoadCvar(SKIN_TEXT_WEAR, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear);
		g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear = CSX::Cvar::LoadCvar(SKIN_TEXT_WEAR, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].flFallbackWear = CSX::Cvar::LoadCvar(SKIN_TEXT_WEAR, pWeaponData[i], 0.000001f);
		}

		g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed = CSX::Cvar::LoadCvar(SKIN_TEXT_SEED, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed);
		g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed = CSX::Cvar::LoadCvar(SKIN_TEXT_SEED, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackSeed = CSX::Cvar::LoadCvar(SKIN_TEXT_SEED, pWeaponData[i], 0);
		}

		if (Interfaces::Engine()->IsConnected())
			ForceFullUpdate();

		ProfileChanger::rank_id = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_RANK_ID, ProfileChanger::rank_id);
		ProfileChanger::wins = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_WINS, ProfileChanger::wins);
		ProfileChanger::cmd_friendly = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_CMD_FRIENDLY, ProfileChanger::cmd_friendly);
		ProfileChanger::cmd_leader = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_CMD_LEADER, ProfileChanger::cmd_leader);
		ProfileChanger::cmd_teaching = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_CMD_TEACHING, ProfileChanger::cmd_teaching);
		ProfileChanger::level = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_LEVEL, ProfileChanger::level);
		ProfileChanger::xp = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_XP, ProfileChanger::xp);
		SendMMHello();

		Misc::misc_SkinChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_SKIN_CHANGER, Misc::misc_SkinChanger) != false;
		Misc::misc_KnifeChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_KNIFE_CHANGER, Misc::misc_KnifeChanger) != false;
		Misc::misc_StickerChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_STICKER_CHANGER, Misc::misc_StickerChanger) != false;
		Misc::misc_EPostprocess = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_EPOSTPROCESS, Misc::misc_EPostprocess) != false;
		Misc::misc_EPostprocess = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_GRENADETRAJECTORY, Misc::misc_GrenadeTrajectory) != false;
		Misc::misc_Bhop = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_BHOP, Misc::misc_Bhop) != false;
		Misc::misc_Punch = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_PUNCH, Misc::misc_Punch) != false;
		Misc::misc_AwpAim = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AWPAIM, Misc::misc_AwpAim) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOFLASH, Misc::misc_NoFlash) != false;
		Misc::misc_NoSmoke = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOSMOKE, Misc::misc_NoSmoke) != false;
		Misc::misc_NoFlash = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_WIREFRAMESMOKE, Misc::misc_wireframesmoke) != false;
		Misc::misc_WireHands = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_WIREHANDS, Misc::misc_WireHands) != false;
		Misc::misc_NoHands = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_NOHANDS, Misc::misc_NoHands) != false;
		Misc::misc_AutoStrafe = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AUTOSTRAFE, Misc::misc_AutoStrafe) != false;
		Misc::misc_LegitAAToggle = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_LEGITAATOGGLE, Misc::misc_LegitAAToggle);
		Misc::misc_AutoAccept = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_AUTOACCEPT, Misc::misc_AutoAccept) != false;
		Misc::misc_Spectators = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_SPECTATORS, Misc::misc_Spectators) != false;
		Misc::misc_FovChanger = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_CHANGER, Misc::misc_FovChanger) != false;
		Misc::misc_FovView = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_VIEW, Misc::misc_FovView);
		Misc::misc_FovModelView = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_FOV_MDL_VIEW, Misc::misc_FovModelView);
		Misc::invalwayson = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_INVALWAYSON, Misc::invalwayson);

		string Color_MENU = CSX::Cvar::LoadCvar(MISC_TEXT, CVAR_MISC_MENU_COLOR, "0,0,0");

		ScanColorFromCvar(Color_MENU.c_str(), Misc::misc_MenuColor);

		string Color_TEXT = CSX::Cvar::LoadCvar(MISC_TEXT, "misc_TextColor", "255,255,255");

		ScanColorFromCvar(Color_TEXT.c_str(), Misc::misc_TextColor);

		/*
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_DEAGLE, Sticker::stickerSafeWeapon);
		Sticker::sticker_deserteagle_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE1, Sticker::sticker_deserteagle_iSlot[0]);
		Sticker::sticker_deserteagle_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE1, Sticker::sticker_deserteagle_size[0]);
		Sticker::sticker_deserteagle_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE1, Sticker::sticker_deserteagle_id[0]);
		Sticker::sticker_deserteagle_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE1, Sticker::sticker_deserteagle_wear[0]);
		Sticker::sticker_deserteagle_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE1, Sticker::sticker_deserteagle_rotate[0]);
		Sticker::sticker_deserteagle_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE2, Sticker::sticker_deserteagle_iSlot[1]);
		Sticker::sticker_deserteagle_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE2, Sticker::sticker_deserteagle_size[1]);
		Sticker::sticker_deserteagle_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE2, Sticker::sticker_deserteagle_id[1]);
		Sticker::sticker_deserteagle_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE2, Sticker::sticker_deserteagle_wear[1]);
		Sticker::sticker_deserteagle_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE2, Sticker::sticker_deserteagle_rotate[1]);
		Sticker::sticker_deserteagle_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE3, Sticker::sticker_deserteagle_iSlot[2]);
		Sticker::sticker_deserteagle_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE3, Sticker::sticker_deserteagle_size[2]);
		Sticker::sticker_deserteagle_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE3, Sticker::sticker_deserteagle_id[2]);
		Sticker::sticker_deserteagle_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE3, Sticker::sticker_deserteagle_wear[2]);
		Sticker::sticker_deserteagle_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE3, Sticker::sticker_deserteagle_rotate[2]);
		Sticker::sticker_deserteagle_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE4, Sticker::sticker_deserteagle_iSlot[3]);
		Sticker::sticker_deserteagle_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE4, Sticker::sticker_deserteagle_size[3]);
		Sticker::sticker_deserteagle_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE4, Sticker::sticker_deserteagle_id[3]);
		Sticker::sticker_deserteagle_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE4, Sticker::sticker_deserteagle_wear[3]);
		Sticker::sticker_deserteagle_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE4, Sticker::sticker_deserteagle_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].flWear = Sticker::sticker_deserteagle_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].flScale = Sticker::sticker_deserteagle_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].iRotation = Sticker::sticker_deserteagle_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[0]].iID = Sticker::sticker_deserteagle_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].flWear = Sticker::sticker_deserteagle_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].flScale = Sticker::sticker_deserteagle_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].iRotation = Sticker::sticker_deserteagle_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[1]].iID = Sticker::sticker_deserteagle_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].flWear = Sticker::sticker_deserteagle_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].flScale = Sticker::sticker_deserteagle_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].iRotation = Sticker::sticker_deserteagle_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[2]].iID = Sticker::sticker_deserteagle_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].flWear = Sticker::sticker_deserteagle_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].flScale = Sticker::sticker_deserteagle_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].iRotation = Sticker::sticker_deserteagle_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_deserteagle_iSlot[3]].iID = Sticker::sticker_deserteagle_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_ELITES, Sticker::stickerSafeWeapon);
		Sticker::sticker_elites_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES1, Sticker::sticker_elites_iSlot[0]);
		Sticker::sticker_elites_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES1, Sticker::sticker_elites_size[0]);
		Sticker::sticker_elites_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES1, Sticker::sticker_elites_id[0]);
		Sticker::sticker_elites_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES1, Sticker::sticker_elites_wear[0]);
		Sticker::sticker_elites_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES1, Sticker::sticker_elites_rotate[0]);
		Sticker::sticker_elites_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES2, Sticker::sticker_elites_iSlot[1]);
		Sticker::sticker_elites_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES2, Sticker::sticker_elites_size[1]);
		Sticker::sticker_elites_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES2, Sticker::sticker_elites_id[1]);
		Sticker::sticker_elites_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES2, Sticker::sticker_elites_wear[1]);
		Sticker::sticker_elites_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES2, Sticker::sticker_elites_rotate[1]);
		Sticker::sticker_elites_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES3, Sticker::sticker_elites_iSlot[2]);
		Sticker::sticker_elites_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES3, Sticker::sticker_elites_size[2]);
		Sticker::sticker_elites_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES3, Sticker::sticker_elites_id[2]);
		Sticker::sticker_elites_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES3, Sticker::sticker_elites_wear[2]);
		Sticker::sticker_elites_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES3, Sticker::sticker_elites_rotate[2]);
		Sticker::sticker_elites_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES4, Sticker::sticker_elites_iSlot[3]);
		Sticker::sticker_elites_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES4, Sticker::sticker_elites_size[3]);
		Sticker::sticker_elites_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES4, Sticker::sticker_elites_id[3]);
		Sticker::sticker_elites_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES4, Sticker::sticker_elites_wear[3]);
		Sticker::sticker_elites_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES4, Sticker::sticker_elites_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].flWear = Sticker::sticker_elites_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].flScale = Sticker::sticker_elites_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].iRotation = Sticker::sticker_elites_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[0]].iID = Sticker::sticker_elites_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].flWear = Sticker::sticker_elites_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].flScale = Sticker::sticker_elites_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].iRotation = Sticker::sticker_elites_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[1]].iID = Sticker::sticker_elites_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].flWear = Sticker::sticker_elites_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].flScale = Sticker::sticker_elites_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].iRotation = Sticker::sticker_elites_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[2]].iID = Sticker::sticker_elites_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].flWear = Sticker::sticker_elites_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].flScale = Sticker::sticker_elites_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].iRotation = Sticker::sticker_elites_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_elites_iSlot[3]].iID = Sticker::sticker_elites_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FIVESEVEN, Sticker::stickerSafeWeapon);
		Sticker::sticker_fiveseven_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN1, Sticker::sticker_fiveseven_iSlot[0]);
		Sticker::sticker_fiveseven_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN1, Sticker::sticker_fiveseven_size[0]);
		Sticker::sticker_fiveseven_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN1, Sticker::sticker_fiveseven_id[0]);
		Sticker::sticker_fiveseven_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN1, Sticker::sticker_fiveseven_wear[0]);
		Sticker::sticker_fiveseven_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN1, Sticker::sticker_fiveseven_rotate[0]);
		Sticker::sticker_fiveseven_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN2, Sticker::sticker_fiveseven_iSlot[1]);
		Sticker::sticker_fiveseven_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN2, Sticker::sticker_fiveseven_size[1]);
		Sticker::sticker_fiveseven_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN2, Sticker::sticker_fiveseven_id[1]);
		Sticker::sticker_fiveseven_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN2, Sticker::sticker_fiveseven_wear[1]);
		Sticker::sticker_fiveseven_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN2, Sticker::sticker_fiveseven_rotate[1]);
		Sticker::sticker_fiveseven_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN3, Sticker::sticker_fiveseven_iSlot[2]);
		Sticker::sticker_fiveseven_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN3, Sticker::sticker_fiveseven_size[2]);
		Sticker::sticker_fiveseven_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN3, Sticker::sticker_fiveseven_id[2]);
		Sticker::sticker_fiveseven_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN3, Sticker::sticker_fiveseven_wear[2]);
		Sticker::sticker_fiveseven_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN3, Sticker::sticker_fiveseven_rotate[2]);
		Sticker::sticker_fiveseven_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN4, Sticker::sticker_fiveseven_iSlot[3]);
		Sticker::sticker_fiveseven_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN4, Sticker::sticker_fiveseven_size[3]);
		Sticker::sticker_fiveseven_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN4, Sticker::sticker_fiveseven_id[3]);
		Sticker::sticker_fiveseven_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN4, Sticker::sticker_fiveseven_wear[3]);
		Sticker::sticker_fiveseven_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN4, Sticker::sticker_fiveseven_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].flWear = Sticker::sticker_fiveseven_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].flScale = Sticker::sticker_fiveseven_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].iRotation = Sticker::sticker_fiveseven_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[0]].iID = Sticker::sticker_fiveseven_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].flWear = Sticker::sticker_fiveseven_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].flScale = Sticker::sticker_fiveseven_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].iRotation = Sticker::sticker_fiveseven_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[1]].iID = Sticker::sticker_fiveseven_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].flWear = Sticker::sticker_fiveseven_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].flScale = Sticker::sticker_fiveseven_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].iRotation = Sticker::sticker_fiveseven_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[2]].iID = Sticker::sticker_fiveseven_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].flWear = Sticker::sticker_fiveseven_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].flScale = Sticker::sticker_fiveseven_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].iRotation = Sticker::sticker_fiveseven_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_fiveseven_iSlot[3]].iID = Sticker::sticker_fiveseven_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GLOCK, Sticker::stickerSafeWeapon);
		Sticker::sticker_glock_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK1, Sticker::sticker_glock_iSlot[0]);
		Sticker::sticker_glock_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK1, Sticker::sticker_glock_size[0]);
		Sticker::sticker_glock_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK1, Sticker::sticker_glock_id[0]);
		Sticker::sticker_glock_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK1, Sticker::sticker_glock_wear[0]);
		Sticker::sticker_glock_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK1, Sticker::sticker_glock_rotate[0]);
		Sticker::sticker_glock_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK2, Sticker::sticker_glock_iSlot[1]);
		Sticker::sticker_glock_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK2, Sticker::sticker_glock_size[1]);
		Sticker::sticker_glock_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK2, Sticker::sticker_glock_id[1]);
		Sticker::sticker_glock_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK2, Sticker::sticker_glock_wear[1]);
		Sticker::sticker_glock_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK2, Sticker::sticker_glock_rotate[1]);
		Sticker::sticker_glock_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK3, Sticker::sticker_glock_iSlot[2]);
		Sticker::sticker_glock_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK3, Sticker::sticker_glock_size[2]);
		Sticker::sticker_glock_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK3, Sticker::sticker_glock_id[2]);
		Sticker::sticker_glock_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK3, Sticker::sticker_glock_wear[2]);
		Sticker::sticker_glock_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK3, Sticker::sticker_glock_rotate[2]);
		Sticker::sticker_glock_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK4, Sticker::sticker_glock_iSlot[3]);
		Sticker::sticker_glock_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK4, Sticker::sticker_glock_size[3]);
		Sticker::sticker_glock_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK4, Sticker::sticker_glock_id[3]);
		Sticker::sticker_glock_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK4, Sticker::sticker_glock_wear[3]);
		Sticker::sticker_glock_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK4, Sticker::sticker_glock_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].flWear = Sticker::sticker_glock_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].flScale = Sticker::sticker_glock_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].iRotation = Sticker::sticker_glock_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[0]].iID = Sticker::sticker_glock_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].flWear = Sticker::sticker_glock_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].flScale = Sticker::sticker_glock_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].iRotation = Sticker::sticker_glock_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[1]].iID = Sticker::sticker_glock_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].flWear = Sticker::sticker_glock_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].flScale = Sticker::sticker_glock_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].iRotation = Sticker::sticker_glock_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[2]].iID = Sticker::sticker_glock_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].flWear = Sticker::sticker_glock_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].flScale = Sticker::sticker_glock_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].iRotation = Sticker::sticker_glock_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_glock_iSlot[3]].iID = Sticker::sticker_glock_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AK, Sticker::stickerSafeWeapon);
		Sticker::sticker_ak_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK1, Sticker::sticker_ak_iSlot[0]);
		Sticker::sticker_ak_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK1, Sticker::sticker_ak_size[0]);
		Sticker::sticker_ak_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK1, Sticker::sticker_ak_id[0]);
		Sticker::sticker_ak_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK1, Sticker::sticker_ak_wear[0]);
		Sticker::sticker_ak_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK1, Sticker::sticker_ak_rotate[0]);
		Sticker::sticker_ak_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK2, Sticker::sticker_ak_iSlot[1]);
		Sticker::sticker_ak_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK2, Sticker::sticker_ak_size[1]);
		Sticker::sticker_ak_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK2, Sticker::sticker_ak_id[1]);
		Sticker::sticker_ak_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK2, Sticker::sticker_ak_wear[1]);
		Sticker::sticker_ak_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK2, Sticker::sticker_ak_rotate[1]);
		Sticker::sticker_ak_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK3, Sticker::sticker_ak_iSlot[2]);
		Sticker::sticker_ak_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK3, Sticker::sticker_ak_size[2]);
		Sticker::sticker_ak_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK3, Sticker::sticker_ak_id[2]);
		Sticker::sticker_ak_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK3, Sticker::sticker_ak_wear[2]);
		Sticker::sticker_ak_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK3, Sticker::sticker_ak_rotate[2]);
		Sticker::sticker_ak_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK4, Sticker::sticker_ak_iSlot[3]);
		Sticker::sticker_ak_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK4, Sticker::sticker_ak_size[3]);
		Sticker::sticker_ak_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK4, Sticker::sticker_ak_id[3]);
		Sticker::sticker_ak_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK4, Sticker::sticker_ak_wear[3]);
		Sticker::sticker_ak_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK4, Sticker::sticker_ak_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].flWear = Sticker::sticker_ak_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].flScale = Sticker::sticker_ak_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].iRotation = Sticker::sticker_ak_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[0]].iID = Sticker::sticker_ak_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].flWear = Sticker::sticker_ak_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].flScale = Sticker::sticker_ak_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].iRotation = Sticker::sticker_ak_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[1]].iID = Sticker::sticker_ak_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].flWear = Sticker::sticker_ak_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].flScale = Sticker::sticker_ak_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].iRotation = Sticker::sticker_ak_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[2]].iID = Sticker::sticker_ak_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].flWear = Sticker::sticker_ak_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].flScale = Sticker::sticker_ak_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].iRotation = Sticker::sticker_ak_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ak_iSlot[3]].iID = Sticker::sticker_ak_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AUG, Sticker::stickerSafeWeapon);
		Sticker::sticker_aug_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG1, Sticker::sticker_aug_iSlot[0]);
		Sticker::sticker_aug_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG1, Sticker::sticker_aug_size[0]);
		Sticker::sticker_aug_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG1, Sticker::sticker_aug_id[0]);
		Sticker::sticker_aug_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG1, Sticker::sticker_aug_wear[0]);
		Sticker::sticker_aug_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG1, Sticker::sticker_aug_rotate[0]);
		Sticker::sticker_aug_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG2, Sticker::sticker_aug_iSlot[1]);
		Sticker::sticker_aug_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG2, Sticker::sticker_aug_size[1]);
		Sticker::sticker_aug_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG2, Sticker::sticker_aug_id[1]);
		Sticker::sticker_aug_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG2, Sticker::sticker_aug_wear[1]);
		Sticker::sticker_aug_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG2, Sticker::sticker_aug_rotate[1]);
		Sticker::sticker_aug_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG3, Sticker::sticker_aug_iSlot[2]);
		Sticker::sticker_aug_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG3, Sticker::sticker_aug_size[2]);
		Sticker::sticker_aug_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG3, Sticker::sticker_aug_id[2]);
		Sticker::sticker_aug_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG3, Sticker::sticker_aug_wear[2]);
		Sticker::sticker_aug_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG3, Sticker::sticker_aug_rotate[2]);
		Sticker::sticker_aug_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG4, Sticker::sticker_aug_iSlot[3]);
		Sticker::sticker_aug_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG4, Sticker::sticker_aug_size[3]);
		Sticker::sticker_aug_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG4, Sticker::sticker_aug_id[3]);
		Sticker::sticker_aug_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG4, Sticker::sticker_aug_wear[3]);
		Sticker::sticker_aug_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG4, Sticker::sticker_aug_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].flWear = Sticker::sticker_aug_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].flScale = Sticker::sticker_aug_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].iRotation = Sticker::sticker_aug_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[0]].iID = Sticker::sticker_aug_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].flWear = Sticker::sticker_aug_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].flScale = Sticker::sticker_aug_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].iRotation = Sticker::sticker_aug_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[1]].iID = Sticker::sticker_aug_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].flWear = Sticker::sticker_aug_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].flScale = Sticker::sticker_aug_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].iRotation = Sticker::sticker_aug_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[2]].iID = Sticker::sticker_aug_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].flWear = Sticker::sticker_aug_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].flScale = Sticker::sticker_aug_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].iRotation = Sticker::sticker_aug_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_aug_iSlot[3]].iID = Sticker::sticker_aug_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AWP, Sticker::stickerSafeWeapon);
		Sticker::sticker_awp_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP1, Sticker::sticker_awp_iSlot[0]);
		Sticker::sticker_awp_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP1, Sticker::sticker_awp_size[0]);
		Sticker::sticker_awp_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP1, Sticker::sticker_awp_id[0]);
		Sticker::sticker_awp_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP1, Sticker::sticker_awp_wear[0]);
		Sticker::sticker_awp_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP1, Sticker::sticker_awp_rotate[0]);
		Sticker::sticker_awp_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP2, Sticker::sticker_awp_iSlot[1]);
		Sticker::sticker_awp_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP2, Sticker::sticker_awp_size[1]);
		Sticker::sticker_awp_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP2, Sticker::sticker_awp_id[1]);
		Sticker::sticker_awp_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP2, Sticker::sticker_awp_wear[1]);
		Sticker::sticker_awp_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP2, Sticker::sticker_awp_rotate[1]);
		Sticker::sticker_awp_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP3, Sticker::sticker_awp_iSlot[2]);
		Sticker::sticker_awp_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP3, Sticker::sticker_awp_size[2]);
		Sticker::sticker_awp_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP3, Sticker::sticker_awp_id[2]);
		Sticker::sticker_awp_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP3, Sticker::sticker_awp_wear[2]);
		Sticker::sticker_awp_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP3, Sticker::sticker_awp_rotate[2]);
		Sticker::sticker_awp_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP4, Sticker::sticker_awp_iSlot[3]);
		Sticker::sticker_awp_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP4, Sticker::sticker_awp_size[3]);
		Sticker::sticker_awp_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP4, Sticker::sticker_awp_id[3]);
		Sticker::sticker_awp_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP4, Sticker::sticker_awp_wear[3]);
		Sticker::sticker_awp_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP4, Sticker::sticker_awp_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].flWear = Sticker::sticker_awp_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].flScale = Sticker::sticker_awp_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].iRotation = Sticker::sticker_awp_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[0]].iID = Sticker::sticker_awp_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].flWear = Sticker::sticker_awp_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].flScale = Sticker::sticker_awp_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].iRotation = Sticker::sticker_awp_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[1]].iID = Sticker::sticker_awp_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].flWear = Sticker::sticker_awp_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].flScale = Sticker::sticker_awp_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].iRotation = Sticker::sticker_awp_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[2]].iID = Sticker::sticker_awp_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].flWear = Sticker::sticker_awp_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].flScale = Sticker::sticker_awp_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].iRotation = Sticker::sticker_awp_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_awp_iSlot[3]].iID = Sticker::sticker_awp_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FAMAS, Sticker::stickerSafeWeapon);
		Sticker::sticker_famas_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS1, Sticker::sticker_famas_iSlot[0]);
		Sticker::sticker_famas_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS1, Sticker::sticker_famas_size[0]);
		Sticker::sticker_famas_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS1, Sticker::sticker_famas_id[0]);
		Sticker::sticker_famas_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS1, Sticker::sticker_famas_wear[0]);
		Sticker::sticker_famas_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS1, Sticker::sticker_famas_rotate[0]);
		Sticker::sticker_famas_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS2, Sticker::sticker_famas_iSlot[1]);
		Sticker::sticker_famas_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS2, Sticker::sticker_famas_size[1]);
		Sticker::sticker_famas_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS2, Sticker::sticker_famas_id[1]);
		Sticker::sticker_famas_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS2, Sticker::sticker_famas_wear[1]);
		Sticker::sticker_famas_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS2, Sticker::sticker_famas_rotate[1]);
		Sticker::sticker_famas_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS3, Sticker::sticker_famas_iSlot[2]);
		Sticker::sticker_famas_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS3, Sticker::sticker_famas_size[2]);
		Sticker::sticker_famas_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS3, Sticker::sticker_famas_id[2]);
		Sticker::sticker_famas_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS3, Sticker::sticker_famas_wear[2]);
		Sticker::sticker_famas_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS3, Sticker::sticker_famas_rotate[2]);
		Sticker::sticker_famas_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS4, Sticker::sticker_famas_iSlot[3]);
		Sticker::sticker_famas_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS4, Sticker::sticker_famas_size[3]);
		Sticker::sticker_famas_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS4, Sticker::sticker_famas_id[3]);
		Sticker::sticker_famas_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS4, Sticker::sticker_famas_wear[3]);
		Sticker::sticker_famas_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS4, Sticker::sticker_famas_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].flWear = Sticker::sticker_famas_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].flScale = Sticker::sticker_famas_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].iRotation = Sticker::sticker_famas_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[0]].iID = Sticker::sticker_famas_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].flWear = Sticker::sticker_famas_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].flScale = Sticker::sticker_famas_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].iRotation = Sticker::sticker_famas_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[1]].iID = Sticker::sticker_famas_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].flWear = Sticker::sticker_famas_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].flScale = Sticker::sticker_famas_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].iRotation = Sticker::sticker_famas_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[2]].iID = Sticker::sticker_famas_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].flWear = Sticker::sticker_famas_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].flScale = Sticker::sticker_famas_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].iRotation = Sticker::sticker_famas_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_famas_iSlot[3]].iID = Sticker::sticker_famas_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_G35G1, Sticker::stickerSafeWeapon);
		Sticker::sticker_g35g1_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G11, Sticker::sticker_g35g1_iSlot[0]);
		Sticker::sticker_g35g1_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G11, Sticker::sticker_g35g1_size[0]);
		Sticker::sticker_g35g1_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G11, Sticker::sticker_g35g1_id[0]);
		Sticker::sticker_g35g1_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G11, Sticker::sticker_g35g1_wear[0]);
		Sticker::sticker_g35g1_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G11, Sticker::sticker_g35g1_rotate[0]);
		Sticker::sticker_g35g1_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G12, Sticker::sticker_g35g1_iSlot[1]);
		Sticker::sticker_g35g1_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G12, Sticker::sticker_g35g1_size[1]);
		Sticker::sticker_g35g1_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G12, Sticker::sticker_g35g1_id[1]);
		Sticker::sticker_g35g1_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G12, Sticker::sticker_g35g1_wear[1]);
		Sticker::sticker_g35g1_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G12, Sticker::sticker_g35g1_rotate[1]);
		Sticker::sticker_g35g1_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G13, Sticker::sticker_g35g1_iSlot[2]);
		Sticker::sticker_g35g1_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G13, Sticker::sticker_g35g1_size[2]);
		Sticker::sticker_g35g1_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G13, Sticker::sticker_g35g1_id[2]);
		Sticker::sticker_g35g1_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G13, Sticker::sticker_g35g1_wear[2]);
		Sticker::sticker_g35g1_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G13, Sticker::sticker_g35g1_rotate[2]);
		Sticker::sticker_g35g1_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G14, Sticker::sticker_g35g1_iSlot[3]);
		Sticker::sticker_g35g1_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G14, Sticker::sticker_g35g1_size[3]);
		Sticker::sticker_g35g1_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G14, Sticker::sticker_g35g1_id[3]);
		Sticker::sticker_g35g1_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G14, Sticker::sticker_g35g1_wear[3]);
		Sticker::sticker_g35g1_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G14, Sticker::sticker_g35g1_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].flWear = Sticker::sticker_g35g1_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].flScale = Sticker::sticker_g35g1_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].iRotation = Sticker::sticker_g35g1_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[0]].iID = Sticker::sticker_g35g1_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].flWear = Sticker::sticker_g35g1_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].flScale = Sticker::sticker_g35g1_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].iRotation = Sticker::sticker_g35g1_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[1]].iID = Sticker::sticker_g35g1_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].flWear = Sticker::sticker_g35g1_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].flScale = Sticker::sticker_g35g1_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].iRotation = Sticker::sticker_g35g1_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[2]].iID = Sticker::sticker_g35g1_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].flWear = Sticker::sticker_g35g1_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].flScale = Sticker::sticker_g35g1_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].iRotation = Sticker::sticker_g35g1_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_g35g1_iSlot[3]].iID = Sticker::sticker_g35g1_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GALIL, Sticker::stickerSafeWeapon);
		Sticker::sticker_galil_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL1, Sticker::sticker_galil_iSlot[0]);
		Sticker::sticker_galil_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL1, Sticker::sticker_galil_size[0]);
		Sticker::sticker_galil_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL1, Sticker::sticker_galil_id[0]);
		Sticker::sticker_galil_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL1, Sticker::sticker_galil_wear[0]);
		Sticker::sticker_galil_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL1, Sticker::sticker_galil_rotate[0]);
		Sticker::sticker_galil_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL2, Sticker::sticker_galil_iSlot[1]);
		Sticker::sticker_galil_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL2, Sticker::sticker_galil_size[1]);
		Sticker::sticker_galil_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL2, Sticker::sticker_galil_id[1]);
		Sticker::sticker_galil_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL2, Sticker::sticker_galil_wear[1]);
		Sticker::sticker_galil_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL2, Sticker::sticker_galil_rotate[1]);
		Sticker::sticker_galil_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL3, Sticker::sticker_galil_iSlot[2]);
		Sticker::sticker_galil_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL3, Sticker::sticker_galil_size[2]);
		Sticker::sticker_galil_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL3, Sticker::sticker_galil_id[2]);
		Sticker::sticker_galil_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL3, Sticker::sticker_galil_wear[2]);
		Sticker::sticker_galil_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL3, Sticker::sticker_galil_rotate[2]);
		Sticker::sticker_galil_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL4, Sticker::sticker_galil_iSlot[3]);
		Sticker::sticker_galil_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL4, Sticker::sticker_galil_size[3]);
		Sticker::sticker_galil_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL4, Sticker::sticker_galil_id[3]);
		Sticker::sticker_galil_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL4, Sticker::sticker_galil_wear[3]);
		Sticker::sticker_galil_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL4, Sticker::sticker_galil_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].flWear = Sticker::sticker_galil_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].flScale = Sticker::sticker_galil_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].iRotation = Sticker::sticker_galil_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[0]].iID = Sticker::sticker_galil_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].flWear = Sticker::sticker_galil_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].flScale = Sticker::sticker_galil_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].iRotation = Sticker::sticker_galil_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[1]].iID = Sticker::sticker_galil_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].flWear = Sticker::sticker_galil_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].flScale = Sticker::sticker_galil_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].iRotation = Sticker::sticker_galil_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[2]].iID = Sticker::sticker_galil_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].flWear = Sticker::sticker_galil_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].flScale = Sticker::sticker_galil_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].iRotation = Sticker::sticker_galil_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_galil_iSlot[3]].iID = Sticker::sticker_galil_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M249, Sticker::stickerSafeWeapon);
		Sticker::sticker_m249_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2491, Sticker::sticker_m249_iSlot[0]);
		Sticker::sticker_m249_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2491, Sticker::sticker_m249_size[0]);
		Sticker::sticker_m249_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2491, Sticker::sticker_m249_id[0]);
		Sticker::sticker_m249_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2491, Sticker::sticker_m249_wear[0]);
		Sticker::sticker_m249_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2491, Sticker::sticker_m249_rotate[0]);
		Sticker::sticker_m249_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2492, Sticker::sticker_m249_iSlot[1]);
		Sticker::sticker_m249_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2492, Sticker::sticker_m249_size[1]);
		Sticker::sticker_m249_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2492, Sticker::sticker_m249_id[1]);
		Sticker::sticker_m249_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2492, Sticker::sticker_m249_wear[1]);
		Sticker::sticker_m249_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2492, Sticker::sticker_m249_rotate[1]);
		Sticker::sticker_m249_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2493, Sticker::sticker_m249_iSlot[2]);
		Sticker::sticker_m249_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2493, Sticker::sticker_m249_size[2]);
		Sticker::sticker_m249_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2493, Sticker::sticker_m249_id[2]);
		Sticker::sticker_m249_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2493, Sticker::sticker_m249_wear[2]);
		Sticker::sticker_m249_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2493, Sticker::sticker_m249_rotate[2]);
		Sticker::sticker_m249_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2494, Sticker::sticker_m249_iSlot[3]);
		Sticker::sticker_m249_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2494, Sticker::sticker_m249_size[3]);
		Sticker::sticker_m249_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2494, Sticker::sticker_m249_id[3]);
		Sticker::sticker_m249_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2494, Sticker::sticker_m249_wear[3]);
		Sticker::sticker_m249_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2494, Sticker::sticker_m249_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].flWear = Sticker::sticker_m249_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].flScale = Sticker::sticker_m249_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].iRotation = Sticker::sticker_m249_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[0]].iID = Sticker::sticker_m249_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].flWear = Sticker::sticker_m249_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].flScale = Sticker::sticker_m249_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].iRotation = Sticker::sticker_m249_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[1]].iID = Sticker::sticker_m249_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].flWear = Sticker::sticker_m249_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].flScale = Sticker::sticker_m249_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].iRotation = Sticker::sticker_m249_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[2]].iID = Sticker::sticker_m249_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].flWear = Sticker::sticker_m249_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].flScale = Sticker::sticker_m249_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].iRotation = Sticker::sticker_m249_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m249_iSlot[3]].iID = Sticker::sticker_m249_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M4A4, Sticker::stickerSafeWeapon);
		Sticker::sticker_m4a4_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A41, Sticker::sticker_m4a4_iSlot[0]);
		Sticker::sticker_m4a4_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A41, Sticker::sticker_m4a4_size[0]);
		Sticker::sticker_m4a4_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A41, Sticker::sticker_m4a4_id[0]);
		Sticker::sticker_m4a4_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A41, Sticker::sticker_m4a4_wear[0]);
		Sticker::sticker_m4a4_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A41, Sticker::sticker_m4a4_rotate[0]);
		Sticker::sticker_m4a4_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A42, Sticker::sticker_m4a4_iSlot[1]);
		Sticker::sticker_m4a4_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A42, Sticker::sticker_m4a4_size[1]);
		Sticker::sticker_m4a4_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A42, Sticker::sticker_m4a4_id[1]);
		Sticker::sticker_m4a4_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A42, Sticker::sticker_m4a4_wear[1]);
		Sticker::sticker_m4a4_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A42, Sticker::sticker_m4a4_rotate[1]);
		Sticker::sticker_m4a4_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A43, Sticker::sticker_m4a4_iSlot[2]);
		Sticker::sticker_m4a4_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A43, Sticker::sticker_m4a4_size[2]);
		Sticker::sticker_m4a4_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A43, Sticker::sticker_m4a4_id[2]);
		Sticker::sticker_m4a4_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A43, Sticker::sticker_m4a4_wear[2]);
		Sticker::sticker_m4a4_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A43, Sticker::sticker_m4a4_rotate[2]);
		Sticker::sticker_m4a4_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A44, Sticker::sticker_m4a4_iSlot[3]);
		Sticker::sticker_m4a4_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A44, Sticker::sticker_m4a4_size[3]);
		Sticker::sticker_m4a4_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A44, Sticker::sticker_m4a4_id[3]);
		Sticker::sticker_m4a4_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A44, Sticker::sticker_m4a4_wear[3]);
		Sticker::sticker_m4a4_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A44, Sticker::sticker_m4a4_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].flWear = Sticker::sticker_m4a4_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].flScale = Sticker::sticker_m4a4_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].iRotation = Sticker::sticker_m4a4_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[0]].iID = Sticker::sticker_m4a4_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].flWear = Sticker::sticker_m4a4_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].flScale = Sticker::sticker_m4a4_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].iRotation = Sticker::sticker_m4a4_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[1]].iID = Sticker::sticker_m4a4_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].flWear = Sticker::sticker_m4a4_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].flScale = Sticker::sticker_m4a4_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].iRotation = Sticker::sticker_m4a4_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[2]].iID = Sticker::sticker_m4a4_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].flWear = Sticker::sticker_m4a4_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].flScale = Sticker::sticker_m4a4_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].iRotation = Sticker::sticker_m4a4_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_m4a4_iSlot[3]].iID = Sticker::sticker_m4a4_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAC10, Sticker::stickerSafeWeapon);
		Sticker::sticker_mac10_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC101, Sticker::sticker_mac10_iSlot[0]);
		Sticker::sticker_mac10_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC101, Sticker::sticker_mac10_size[0]);
		Sticker::sticker_mac10_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC101, Sticker::sticker_mac10_id[0]);
		Sticker::sticker_mac10_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC101, Sticker::sticker_mac10_wear[0]);
		Sticker::sticker_mac10_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC101, Sticker::sticker_mac10_rotate[0]);
		Sticker::sticker_mac10_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC102, Sticker::sticker_mac10_iSlot[1]);
		Sticker::sticker_mac10_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC102, Sticker::sticker_mac10_size[1]);
		Sticker::sticker_mac10_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC102, Sticker::sticker_mac10_id[1]);
		Sticker::sticker_mac10_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC102, Sticker::sticker_mac10_wear[1]);
		Sticker::sticker_mac10_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC102, Sticker::sticker_mac10_rotate[1]);
		Sticker::sticker_mac10_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC103, Sticker::sticker_mac10_iSlot[2]);
		Sticker::sticker_mac10_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC103, Sticker::sticker_mac10_size[2]);
		Sticker::sticker_mac10_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC103, Sticker::sticker_mac10_id[2]);
		Sticker::sticker_mac10_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC103, Sticker::sticker_mac10_wear[2]);
		Sticker::sticker_mac10_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC103, Sticker::sticker_mac10_rotate[2]);
		Sticker::sticker_mac10_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC104, Sticker::sticker_mac10_iSlot[3]);
		Sticker::sticker_mac10_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC104, Sticker::sticker_mac10_size[3]);
		Sticker::sticker_mac10_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC104, Sticker::sticker_mac10_id[3]);
		Sticker::sticker_mac10_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC104, Sticker::sticker_mac10_wear[3]);
		Sticker::sticker_mac10_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC104, Sticker::sticker_mac10_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].flWear = Sticker::sticker_mac10_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].flScale = Sticker::sticker_mac10_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].iRotation = Sticker::sticker_mac10_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[0]].iID = Sticker::sticker_mac10_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].flWear = Sticker::sticker_mac10_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].flScale = Sticker::sticker_mac10_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].iRotation = Sticker::sticker_mac10_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[1]].iID = Sticker::sticker_mac10_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].flWear = Sticker::sticker_mac10_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].flScale = Sticker::sticker_mac10_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].iRotation = Sticker::sticker_mac10_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[2]].iID = Sticker::sticker_mac10_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].flWear = Sticker::sticker_mac10_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].flScale = Sticker::sticker_mac10_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].iRotation = Sticker::sticker_mac10_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mac10_iSlot[3]].iID = Sticker::sticker_mac10_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P90, Sticker::stickerSafeWeapon);
		Sticker::sticker_p90_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P901, Sticker::sticker_p90_iSlot[0]);
		Sticker::sticker_p90_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P901, Sticker::sticker_p90_size[0]);
		Sticker::sticker_p90_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P901, Sticker::sticker_p90_id[0]);
		Sticker::sticker_p90_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P901, Sticker::sticker_p90_wear[0]);
		Sticker::sticker_p90_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P901, Sticker::sticker_p90_rotate[0]);
		Sticker::sticker_p90_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P902, Sticker::sticker_p90_iSlot[1]);
		Sticker::sticker_p90_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P902, Sticker::sticker_p90_size[1]);
		Sticker::sticker_p90_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P902, Sticker::sticker_p90_id[1]);
		Sticker::sticker_p90_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P902, Sticker::sticker_p90_wear[1]);
		Sticker::sticker_p90_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P902, Sticker::sticker_p90_rotate[1]);
		Sticker::sticker_p90_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P903, Sticker::sticker_p90_iSlot[2]);
		Sticker::sticker_p90_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P903, Sticker::sticker_p90_size[2]);
		Sticker::sticker_p90_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P903, Sticker::sticker_p90_id[2]);
		Sticker::sticker_p90_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P903, Sticker::sticker_p90_wear[2]);
		Sticker::sticker_p90_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P903, Sticker::sticker_p90_rotate[2]);
		Sticker::sticker_p90_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P904, Sticker::sticker_p90_iSlot[3]);
		Sticker::sticker_p90_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P904, Sticker::sticker_p90_size[3]);
		Sticker::sticker_p90_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P904, Sticker::sticker_p90_id[3]);
		Sticker::sticker_p90_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P904, Sticker::sticker_p90_wear[3]);
		Sticker::sticker_p90_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P904, Sticker::sticker_p90_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].flWear = Sticker::sticker_p90_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].flScale = Sticker::sticker_p90_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].iRotation = Sticker::sticker_p90_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[0]].iID = Sticker::sticker_p90_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].flWear = Sticker::sticker_p90_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].flScale = Sticker::sticker_p90_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].iRotation = Sticker::sticker_p90_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[1]].iID = Sticker::sticker_p90_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].flWear = Sticker::sticker_p90_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].flScale = Sticker::sticker_p90_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].iRotation = Sticker::sticker_p90_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[2]].iID = Sticker::sticker_p90_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].flWear = Sticker::sticker_p90_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].flScale = Sticker::sticker_p90_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].iRotation = Sticker::sticker_p90_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p90_iSlot[3]].iID = Sticker::sticker_p90_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_UMP, Sticker::stickerSafeWeapon);
		Sticker::sticker_ump_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP1, Sticker::sticker_ump_iSlot[0]);
		Sticker::sticker_ump_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP1, Sticker::sticker_ump_size[0]);
		Sticker::sticker_ump_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP1, Sticker::sticker_ump_id[0]);
		Sticker::sticker_ump_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP1, Sticker::sticker_ump_wear[0]);
		Sticker::sticker_ump_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP1, Sticker::sticker_ump_rotate[0]);
		Sticker::sticker_ump_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP2, Sticker::sticker_ump_iSlot[1]);
		Sticker::sticker_ump_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP2, Sticker::sticker_ump_size[1]);
		Sticker::sticker_ump_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP2, Sticker::sticker_ump_id[1]);
		Sticker::sticker_ump_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP2, Sticker::sticker_ump_wear[1]);
		Sticker::sticker_ump_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP2, Sticker::sticker_ump_rotate[1]);
		Sticker::sticker_ump_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP3, Sticker::sticker_ump_iSlot[2]);
		Sticker::sticker_ump_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP3, Sticker::sticker_ump_size[2]);
		Sticker::sticker_ump_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP3, Sticker::sticker_ump_id[2]);
		Sticker::sticker_ump_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP3, Sticker::sticker_ump_wear[2]);
		Sticker::sticker_ump_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP3, Sticker::sticker_ump_rotate[2]);
		Sticker::sticker_ump_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP4, Sticker::sticker_ump_iSlot[3]);
		Sticker::sticker_ump_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP4, Sticker::sticker_ump_size[3]);
		Sticker::sticker_ump_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP4, Sticker::sticker_ump_id[3]);
		Sticker::sticker_ump_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP4, Sticker::sticker_ump_wear[3]);
		Sticker::sticker_ump_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP4, Sticker::sticker_ump_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].flWear = Sticker::sticker_ump_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].flScale = Sticker::sticker_ump_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].iRotation = Sticker::sticker_ump_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[0]].iID = Sticker::sticker_ump_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].flWear = Sticker::sticker_ump_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].flScale = Sticker::sticker_ump_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].iRotation = Sticker::sticker_ump_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[1]].iID = Sticker::sticker_ump_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].flWear = Sticker::sticker_ump_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].flScale = Sticker::sticker_ump_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].iRotation = Sticker::sticker_ump_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[2]].iID = Sticker::sticker_ump_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].flWear = Sticker::sticker_ump_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].flScale = Sticker::sticker_ump_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].iRotation = Sticker::sticker_ump_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ump_iSlot[3]].iID = Sticker::sticker_ump_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_XM, Sticker::stickerSafeWeapon);
		Sticker::sticker_xm_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM1, Sticker::sticker_xm_iSlot[0]);
		Sticker::sticker_xm_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM1, Sticker::sticker_xm_size[0]);
		Sticker::sticker_xm_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM1, Sticker::sticker_xm_id[0]);
		Sticker::sticker_xm_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM1, Sticker::sticker_xm_wear[0]);
		Sticker::sticker_xm_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM1, Sticker::sticker_xm_rotate[0]);
		Sticker::sticker_xm_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM2, Sticker::sticker_xm_iSlot[1]);
		Sticker::sticker_xm_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM2, Sticker::sticker_xm_size[1]);
		Sticker::sticker_xm_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM2, Sticker::sticker_xm_id[1]);
		Sticker::sticker_xm_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM2, Sticker::sticker_xm_wear[1]);
		Sticker::sticker_xm_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM2, Sticker::sticker_xm_rotate[1]);
		Sticker::sticker_xm_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM3, Sticker::sticker_xm_iSlot[2]);
		Sticker::sticker_xm_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM3, Sticker::sticker_xm_size[2]);
		Sticker::sticker_xm_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM3, Sticker::sticker_xm_id[2]);
		Sticker::sticker_xm_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM3, Sticker::sticker_xm_wear[2]);
		Sticker::sticker_xm_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM3, Sticker::sticker_xm_rotate[2]);
		Sticker::sticker_xm_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM4, Sticker::sticker_xm_iSlot[3]);
		Sticker::sticker_xm_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM4, Sticker::sticker_xm_size[3]);
		Sticker::sticker_xm_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM4, Sticker::sticker_xm_id[3]);
		Sticker::sticker_xm_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM4, Sticker::sticker_xm_wear[3]);
		Sticker::sticker_xm_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM4, Sticker::sticker_xm_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].flWear = Sticker::sticker_xm_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].flScale = Sticker::sticker_xm_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].iRotation = Sticker::sticker_xm_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[0]].iID = Sticker::sticker_xm_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].flWear = Sticker::sticker_xm_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].flScale = Sticker::sticker_xm_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].iRotation = Sticker::sticker_xm_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[1]].iID = Sticker::sticker_xm_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].flWear = Sticker::sticker_xm_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].flScale = Sticker::sticker_xm_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].iRotation = Sticker::sticker_xm_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[2]].iID = Sticker::sticker_xm_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].flWear = Sticker::sticker_xm_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].flScale = Sticker::sticker_xm_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].iRotation = Sticker::sticker_xm_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_xm_iSlot[3]].iID = Sticker::sticker_xm_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_BIZON, Sticker::stickerSafeWeapon);
		Sticker::sticker_bizon_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON1, Sticker::sticker_bizon_iSlot[0]);
		Sticker::sticker_bizon_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON1, Sticker::sticker_bizon_size[0]);
		Sticker::sticker_bizon_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON1, Sticker::sticker_bizon_id[0]);
		Sticker::sticker_bizon_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON1, Sticker::sticker_bizon_wear[0]);
		Sticker::sticker_bizon_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON1, Sticker::sticker_bizon_rotate[0]);
		Sticker::sticker_bizon_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON2, Sticker::sticker_bizon_iSlot[1]);
		Sticker::sticker_bizon_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON2, Sticker::sticker_bizon_size[1]);
		Sticker::sticker_bizon_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON2, Sticker::sticker_bizon_id[1]);
		Sticker::sticker_bizon_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON2, Sticker::sticker_bizon_wear[1]);
		Sticker::sticker_bizon_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON2, Sticker::sticker_bizon_rotate[1]);
		Sticker::sticker_bizon_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON3, Sticker::sticker_bizon_iSlot[2]);
		Sticker::sticker_bizon_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON3, Sticker::sticker_bizon_size[2]);
		Sticker::sticker_bizon_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON3, Sticker::sticker_bizon_id[2]);
		Sticker::sticker_bizon_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON3, Sticker::sticker_bizon_wear[2]);
		Sticker::sticker_bizon_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON3, Sticker::sticker_bizon_rotate[2]);
		Sticker::sticker_bizon_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON4, Sticker::sticker_bizon_iSlot[3]);
		Sticker::sticker_bizon_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON4, Sticker::sticker_bizon_size[3]);
		Sticker::sticker_bizon_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON4, Sticker::sticker_bizon_id[3]);
		Sticker::sticker_bizon_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON4, Sticker::sticker_bizon_wear[3]);
		Sticker::sticker_bizon_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON4, Sticker::sticker_bizon_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].flWear = Sticker::sticker_bizon_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].flScale = Sticker::sticker_bizon_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].iRotation = Sticker::sticker_bizon_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[0]].iID = Sticker::sticker_bizon_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].flWear = Sticker::sticker_bizon_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].flScale = Sticker::sticker_bizon_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].iRotation = Sticker::sticker_bizon_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[1]].iID = Sticker::sticker_bizon_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].flWear = Sticker::sticker_bizon_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].flScale = Sticker::sticker_bizon_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].iRotation = Sticker::sticker_bizon_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[2]].iID = Sticker::sticker_bizon_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].flWear = Sticker::sticker_bizon_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].flScale = Sticker::sticker_bizon_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].iRotation = Sticker::sticker_bizon_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_bizon_iSlot[3]].iID = Sticker::sticker_bizon_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAG7, Sticker::stickerSafeWeapon);
		Sticker::sticker_mag7_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG71, Sticker::sticker_mag7_iSlot[0]);
		Sticker::sticker_mag7_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG71, Sticker::sticker_mag7_size[0]);
		Sticker::sticker_mag7_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG71, Sticker::sticker_mag7_id[0]);
		Sticker::sticker_mag7_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG71, Sticker::sticker_mag7_wear[0]);
		Sticker::sticker_mag7_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG71, Sticker::sticker_mag7_rotate[0]);
		Sticker::sticker_mag7_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG72, Sticker::sticker_mag7_iSlot[1]);
		Sticker::sticker_mag7_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG72, Sticker::sticker_mag7_size[1]);
		Sticker::sticker_mag7_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG72, Sticker::sticker_mag7_id[1]);
		Sticker::sticker_mag7_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG72, Sticker::sticker_mag7_wear[1]);
		Sticker::sticker_mag7_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG72, Sticker::sticker_mag7_rotate[1]);
		Sticker::sticker_mag7_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG73, Sticker::sticker_mag7_iSlot[2]);
		Sticker::sticker_mag7_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG73, Sticker::sticker_mag7_size[2]);
		Sticker::sticker_mag7_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG73, Sticker::sticker_mag7_id[2]);
		Sticker::sticker_mag7_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG73, Sticker::sticker_mag7_wear[2]);
		Sticker::sticker_mag7_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG73, Sticker::sticker_mag7_rotate[2]);
		Sticker::sticker_mag7_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG74, Sticker::sticker_mag7_iSlot[3]);
		Sticker::sticker_mag7_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG74, Sticker::sticker_mag7_size[3]);
		Sticker::sticker_mag7_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG74, Sticker::sticker_mag7_id[3]);
		Sticker::sticker_mag7_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG74, Sticker::sticker_mag7_wear[3]);
		Sticker::sticker_mag7_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG74, Sticker::sticker_mag7_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].flWear = Sticker::sticker_mag7_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].flScale = Sticker::sticker_mag7_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].iRotation = Sticker::sticker_mag7_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[0]].iID = Sticker::sticker_mag7_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].flWear = Sticker::sticker_mag7_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].flScale = Sticker::sticker_mag7_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].iRotation = Sticker::sticker_mag7_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[1]].iID = Sticker::sticker_mag7_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].flWear = Sticker::sticker_mag7_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].flScale = Sticker::sticker_mag7_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].iRotation = Sticker::sticker_mag7_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[2]].iID = Sticker::sticker_mag7_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].flWear = Sticker::sticker_mag7_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].flScale = Sticker::sticker_mag7_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].iRotation = Sticker::sticker_mag7_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mag7_iSlot[3]].iID = Sticker::sticker_mag7_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NEGEV, Sticker::stickerSafeWeapon);
		Sticker::sticker_negev_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV1, Sticker::sticker_negev_iSlot[0]);
		Sticker::sticker_negev_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV1, Sticker::sticker_negev_size[0]);
		Sticker::sticker_negev_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV1, Sticker::sticker_negev_id[0]);
		Sticker::sticker_negev_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV1, Sticker::sticker_negev_wear[0]);
		Sticker::sticker_negev_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV1, Sticker::sticker_negev_rotate[0]);
		Sticker::sticker_negev_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV2, Sticker::sticker_negev_iSlot[1]);
		Sticker::sticker_negev_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV2, Sticker::sticker_negev_size[1]);
		Sticker::sticker_negev_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV2, Sticker::sticker_negev_id[1]);
		Sticker::sticker_negev_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV2, Sticker::sticker_negev_wear[1]);
		Sticker::sticker_negev_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV2, Sticker::sticker_negev_rotate[1]);
		Sticker::sticker_negev_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV3, Sticker::sticker_negev_iSlot[2]);
		Sticker::sticker_negev_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV3, Sticker::sticker_negev_size[2]);
		Sticker::sticker_negev_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV3, Sticker::sticker_negev_id[2]);
		Sticker::sticker_negev_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV3, Sticker::sticker_negev_wear[2]);
		Sticker::sticker_negev_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV3, Sticker::sticker_negev_rotate[2]);
		Sticker::sticker_negev_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV4, Sticker::sticker_negev_iSlot[3]);
		Sticker::sticker_negev_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV4, Sticker::sticker_negev_size[3]);
		Sticker::sticker_negev_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV4, Sticker::sticker_negev_id[3]);
		Sticker::sticker_negev_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV4, Sticker::sticker_negev_wear[3]);
		Sticker::sticker_negev_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV4, Sticker::sticker_negev_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].flWear = Sticker::sticker_negev_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].flScale = Sticker::sticker_negev_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].iRotation = Sticker::sticker_negev_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[0]].iID = Sticker::sticker_negev_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].flWear = Sticker::sticker_negev_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].flScale = Sticker::sticker_negev_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].iRotation = Sticker::sticker_negev_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[1]].iID = Sticker::sticker_negev_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].flWear = Sticker::sticker_negev_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].flScale = Sticker::sticker_negev_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].iRotation = Sticker::sticker_negev_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[2]].iID = Sticker::sticker_negev_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].flWear = Sticker::sticker_negev_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].flScale = Sticker::sticker_negev_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].iRotation = Sticker::sticker_negev_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_negev_iSlot[3]].iID = Sticker::sticker_negev_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SAWEDOFF, Sticker::stickerSafeWeapon);
		Sticker::sticker_sawedoff_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF1, Sticker::sticker_sawedoff_iSlot[0]);
		Sticker::sticker_sawedoff_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF1, Sticker::sticker_sawedoff_size[0]);
		Sticker::sticker_sawedoff_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF1, Sticker::sticker_sawedoff_id[0]);
		Sticker::sticker_sawedoff_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF1, Sticker::sticker_sawedoff_wear[0]);
		Sticker::sticker_sawedoff_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF1, Sticker::sticker_sawedoff_rotate[0]);
		Sticker::sticker_sawedoff_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF2, Sticker::sticker_sawedoff_iSlot[1]);
		Sticker::sticker_sawedoff_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF2, Sticker::sticker_sawedoff_size[1]);
		Sticker::sticker_sawedoff_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF2, Sticker::sticker_sawedoff_id[1]);
		Sticker::sticker_sawedoff_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF2, Sticker::sticker_sawedoff_wear[1]);
		Sticker::sticker_sawedoff_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF2, Sticker::sticker_sawedoff_rotate[1]);
		Sticker::sticker_sawedoff_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF3, Sticker::sticker_sawedoff_iSlot[2]);
		Sticker::sticker_sawedoff_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF3, Sticker::sticker_sawedoff_size[2]);
		Sticker::sticker_sawedoff_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF3, Sticker::sticker_sawedoff_id[2]);
		Sticker::sticker_sawedoff_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF3, Sticker::sticker_sawedoff_wear[2]);
		Sticker::sticker_sawedoff_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF3, Sticker::sticker_sawedoff_rotate[2]);
		Sticker::sticker_sawedoff_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF4, Sticker::sticker_sawedoff_iSlot[3]);
		Sticker::sticker_sawedoff_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF4, Sticker::sticker_sawedoff_size[3]);
		Sticker::sticker_sawedoff_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF4, Sticker::sticker_sawedoff_id[3]);
		Sticker::sticker_sawedoff_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF4, Sticker::sticker_sawedoff_wear[3]);
		Sticker::sticker_sawedoff_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF4, Sticker::sticker_sawedoff_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].flWear = Sticker::sticker_sawedoff_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].flScale = Sticker::sticker_sawedoff_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].iRotation = Sticker::sticker_sawedoff_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[0]].iID = Sticker::sticker_sawedoff_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].flWear = Sticker::sticker_sawedoff_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].flScale = Sticker::sticker_sawedoff_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].iRotation = Sticker::sticker_sawedoff_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[1]].iID = Sticker::sticker_sawedoff_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].flWear = Sticker::sticker_sawedoff_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].flScale = Sticker::sticker_sawedoff_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].iRotation = Sticker::sticker_sawedoff_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[2]].iID = Sticker::sticker_sawedoff_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].flWear = Sticker::sticker_sawedoff_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].flScale = Sticker::sticker_sawedoff_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].iRotation = Sticker::sticker_sawedoff_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sawedoff_iSlot[3]].iID = Sticker::sticker_sawedoff_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_TEC, Sticker::stickerSafeWeapon);
		Sticker::sticker_tec_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC1, Sticker::sticker_tec_iSlot[0]);
		Sticker::sticker_tec_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC1, Sticker::sticker_tec_size[0]);
		Sticker::sticker_tec_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC1, Sticker::sticker_tec_id[0]);
		Sticker::sticker_tec_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC1, Sticker::sticker_tec_wear[0]);
		Sticker::sticker_tec_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC1, Sticker::sticker_tec_rotate[0]);
		Sticker::sticker_tec_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC2, Sticker::sticker_tec_iSlot[1]);
		Sticker::sticker_tec_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC2, Sticker::sticker_tec_size[1]);
		Sticker::sticker_tec_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC2, Sticker::sticker_tec_id[1]);
		Sticker::sticker_tec_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC2, Sticker::sticker_tec_wear[1]);
		Sticker::sticker_tec_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC2, Sticker::sticker_tec_rotate[1]);
		Sticker::sticker_tec_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC3, Sticker::sticker_tec_iSlot[2]);
		Sticker::sticker_tec_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC3, Sticker::sticker_tec_size[2]);
		Sticker::sticker_tec_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC3, Sticker::sticker_tec_id[2]);
		Sticker::sticker_tec_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC3, Sticker::sticker_tec_wear[2]);
		Sticker::sticker_tec_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC3, Sticker::sticker_tec_rotate[2]);
		Sticker::sticker_tec_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC4, Sticker::sticker_tec_iSlot[3]);
		Sticker::sticker_tec_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC4, Sticker::sticker_tec_size[3]);
		Sticker::sticker_tec_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC4, Sticker::sticker_tec_id[3]);
		Sticker::sticker_tec_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC4, Sticker::sticker_tec_wear[3]);
		Sticker::sticker_tec_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC4, Sticker::sticker_tec_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].flWear = Sticker::sticker_tec_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].flScale = Sticker::sticker_tec_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].iRotation = Sticker::sticker_tec_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[0]].iID = Sticker::sticker_tec_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].flWear = Sticker::sticker_tec_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].flScale = Sticker::sticker_tec_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].iRotation = Sticker::sticker_tec_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[1]].iID = Sticker::sticker_tec_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].flWear = Sticker::sticker_tec_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].flScale = Sticker::sticker_tec_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].iRotation = Sticker::sticker_tec_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[2]].iID = Sticker::sticker_tec_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].flWear = Sticker::sticker_tec_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].flScale = Sticker::sticker_tec_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].iRotation = Sticker::sticker_tec_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_tec_iSlot[3]].iID = Sticker::sticker_tec_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P2000, Sticker::stickerSafeWeapon);
		Sticker::sticker_p2000_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20001, Sticker::sticker_p2000_iSlot[0]);
		Sticker::sticker_p2000_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20001, Sticker::sticker_p2000_size[0]);
		Sticker::sticker_p2000_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20001, Sticker::sticker_p2000_id[0]);
		Sticker::sticker_p2000_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20001, Sticker::sticker_p2000_wear[0]);
		Sticker::sticker_p2000_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20001, Sticker::sticker_p2000_rotate[0]);
		Sticker::sticker_p2000_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20002, Sticker::sticker_p2000_iSlot[1]);
		Sticker::sticker_p2000_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20002, Sticker::sticker_p2000_size[1]);
		Sticker::sticker_p2000_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20002, Sticker::sticker_p2000_id[1]);
		Sticker::sticker_p2000_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20002, Sticker::sticker_p2000_wear[1]);
		Sticker::sticker_p2000_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20002, Sticker::sticker_p2000_rotate[1]);
		Sticker::sticker_p2000_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20003, Sticker::sticker_p2000_iSlot[2]);
		Sticker::sticker_p2000_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20003, Sticker::sticker_p2000_size[2]);
		Sticker::sticker_p2000_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20003, Sticker::sticker_p2000_id[2]);
		Sticker::sticker_p2000_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20003, Sticker::sticker_p2000_wear[2]);
		Sticker::sticker_p2000_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20003, Sticker::sticker_p2000_rotate[2]);
		Sticker::sticker_p2000_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20004, Sticker::sticker_p2000_iSlot[3]);
		Sticker::sticker_p2000_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20004, Sticker::sticker_p2000_size[3]);
		Sticker::sticker_p2000_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20004, Sticker::sticker_p2000_id[3]);
		Sticker::sticker_p2000_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20004, Sticker::sticker_p2000_wear[3]);
		Sticker::sticker_p2000_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20004, Sticker::sticker_p2000_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].flWear = Sticker::sticker_p2000_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].flScale = Sticker::sticker_p2000_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].iRotation = Sticker::sticker_p2000_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[0]].iID = Sticker::sticker_p2000_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].flWear = Sticker::sticker_p2000_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].flScale = Sticker::sticker_p2000_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].iRotation = Sticker::sticker_p2000_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[1]].iID = Sticker::sticker_p2000_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].flWear = Sticker::sticker_p2000_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].flScale = Sticker::sticker_p2000_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].iRotation = Sticker::sticker_p2000_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[2]].iID = Sticker::sticker_p2000_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].flWear = Sticker::sticker_p2000_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].flScale = Sticker::sticker_p2000_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].iRotation = Sticker::sticker_p2000_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p2000_iSlot[3]].iID = Sticker::sticker_p2000_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP7, Sticker::stickerSafeWeapon);
		Sticker::sticker_mp7_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP71, Sticker::sticker_mp7_iSlot[0]);
		Sticker::sticker_mp7_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP71, Sticker::sticker_mp7_size[0]);
		Sticker::sticker_mp7_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP71, Sticker::sticker_mp7_id[0]);
		Sticker::sticker_mp7_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP71, Sticker::sticker_mp7_wear[0]);
		Sticker::sticker_mp7_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP71, Sticker::sticker_mp7_rotate[0]);
		Sticker::sticker_mp7_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP72, Sticker::sticker_mp7_iSlot[1]);
		Sticker::sticker_mp7_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP72, Sticker::sticker_mp7_size[1]);
		Sticker::sticker_mp7_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP72, Sticker::sticker_mp7_id[1]);
		Sticker::sticker_mp7_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP72, Sticker::sticker_mp7_wear[1]);
		Sticker::sticker_mp7_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP72, Sticker::sticker_mp7_rotate[1]);
		Sticker::sticker_mp7_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP73, Sticker::sticker_mp7_iSlot[2]);
		Sticker::sticker_mp7_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP73, Sticker::sticker_mp7_size[2]);
		Sticker::sticker_mp7_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP73, Sticker::sticker_mp7_id[2]);
		Sticker::sticker_mp7_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP73, Sticker::sticker_mp7_wear[2]);
		Sticker::sticker_mp7_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP73, Sticker::sticker_mp7_rotate[2]);
		Sticker::sticker_mp7_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP74, Sticker::sticker_mp7_iSlot[3]);
		Sticker::sticker_mp7_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP74, Sticker::sticker_mp7_size[3]);
		Sticker::sticker_mp7_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP74, Sticker::sticker_mp7_id[3]);
		Sticker::sticker_mp7_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP74, Sticker::sticker_mp7_wear[3]);
		Sticker::sticker_mp7_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP74, Sticker::sticker_mp7_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].flWear = Sticker::sticker_mp7_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].flScale = Sticker::sticker_mp7_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].iRotation = Sticker::sticker_mp7_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[0]].iID = Sticker::sticker_mp7_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].flWear = Sticker::sticker_mp7_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].flScale = Sticker::sticker_mp7_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].iRotation = Sticker::sticker_mp7_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[1]].iID = Sticker::sticker_mp7_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].flWear = Sticker::sticker_mp7_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].flScale = Sticker::sticker_mp7_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].iRotation = Sticker::sticker_mp7_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[2]].iID = Sticker::sticker_mp7_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].flWear = Sticker::sticker_mp7_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].flScale = Sticker::sticker_mp7_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].iRotation = Sticker::sticker_mp7_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp7_iSlot[3]].iID = Sticker::sticker_mp7_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP9, Sticker::stickerSafeWeapon);
		Sticker::sticker_mp9_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP91, Sticker::sticker_mp9_iSlot[0]);
		Sticker::sticker_mp9_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP91, Sticker::sticker_mp9_size[0]);
		Sticker::sticker_mp9_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP91, Sticker::sticker_mp9_id[0]);
		Sticker::sticker_mp9_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP91, Sticker::sticker_mp9_wear[0]);
		Sticker::sticker_mp9_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP91, Sticker::sticker_mp9_rotate[0]);
		Sticker::sticker_mp9_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP92, Sticker::sticker_mp9_iSlot[1]);
		Sticker::sticker_mp9_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP92, Sticker::sticker_mp9_size[1]);
		Sticker::sticker_mp9_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP92, Sticker::sticker_mp9_id[1]);
		Sticker::sticker_mp9_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP92, Sticker::sticker_mp9_wear[1]);
		Sticker::sticker_mp9_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP92, Sticker::sticker_mp9_rotate[1]);
		Sticker::sticker_mp9_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP93, Sticker::sticker_mp9_iSlot[2]);
		Sticker::sticker_mp9_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP93, Sticker::sticker_mp9_size[2]);
		Sticker::sticker_mp9_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP93, Sticker::sticker_mp9_id[2]);
		Sticker::sticker_mp9_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP93, Sticker::sticker_mp9_wear[2]);
		Sticker::sticker_mp9_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP93, Sticker::sticker_mp9_rotate[2]);
		Sticker::sticker_mp9_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP94, Sticker::sticker_mp9_iSlot[3]);
		Sticker::sticker_mp9_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP94, Sticker::sticker_mp9_size[3]);
		Sticker::sticker_mp9_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP94, Sticker::sticker_mp9_id[3]);
		Sticker::sticker_mp9_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP94, Sticker::sticker_mp9_wear[3]);
		Sticker::sticker_mp9_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP94, Sticker::sticker_mp9_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].flWear = Sticker::sticker_mp9_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].flScale = Sticker::sticker_mp9_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].iRotation = Sticker::sticker_mp9_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[0]].iID = Sticker::sticker_mp9_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].flWear = Sticker::sticker_mp9_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].flScale = Sticker::sticker_mp9_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].iRotation = Sticker::sticker_mp9_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[1]].iID = Sticker::sticker_mp9_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].flWear = Sticker::sticker_mp9_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].flScale = Sticker::sticker_mp9_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].iRotation = Sticker::sticker_mp9_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[2]].iID = Sticker::sticker_mp9_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].flWear = Sticker::sticker_mp9_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].flScale = Sticker::sticker_mp9_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].iRotation = Sticker::sticker_mp9_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_mp9_iSlot[3]].iID = Sticker::sticker_mp9_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NOVA, Sticker::stickerSafeWeapon);
		Sticker::sticker_nova_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA1, Sticker::sticker_nova_iSlot[0]);
		Sticker::sticker_nova_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA1, Sticker::sticker_nova_size[0]);
		Sticker::sticker_nova_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA1, Sticker::sticker_nova_id[0]);
		Sticker::sticker_nova_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA1, Sticker::sticker_nova_wear[0]);
		Sticker::sticker_nova_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA1, Sticker::sticker_nova_rotate[0]);
		Sticker::sticker_nova_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA2, Sticker::sticker_nova_iSlot[1]);
		Sticker::sticker_nova_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA2, Sticker::sticker_nova_size[1]);
		Sticker::sticker_nova_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA2, Sticker::sticker_nova_id[1]);
		Sticker::sticker_nova_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA2, Sticker::sticker_nova_wear[1]);
		Sticker::sticker_nova_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA2, Sticker::sticker_nova_rotate[1]);
		Sticker::sticker_nova_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA3, Sticker::sticker_nova_iSlot[2]);
		Sticker::sticker_nova_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA3, Sticker::sticker_nova_size[2]);
		Sticker::sticker_nova_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA3, Sticker::sticker_nova_id[2]);
		Sticker::sticker_nova_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA3, Sticker::sticker_nova_wear[2]);
		Sticker::sticker_nova_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA3, Sticker::sticker_nova_rotate[2]);
		Sticker::sticker_nova_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA4, Sticker::sticker_nova_iSlot[3]);
		Sticker::sticker_nova_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA4, Sticker::sticker_nova_size[3]);
		Sticker::sticker_nova_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA4, Sticker::sticker_nova_id[3]);
		Sticker::sticker_nova_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA4, Sticker::sticker_nova_wear[3]);
		Sticker::sticker_nova_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA4, Sticker::sticker_nova_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].flWear = Sticker::sticker_nova_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].flScale = Sticker::sticker_nova_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].iRotation = Sticker::sticker_nova_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[0]].iID = Sticker::sticker_nova_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].flWear = Sticker::sticker_nova_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].flScale = Sticker::sticker_nova_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].iRotation = Sticker::sticker_nova_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[1]].iID = Sticker::sticker_nova_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].flWear = Sticker::sticker_nova_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].flScale = Sticker::sticker_nova_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].iRotation = Sticker::sticker_nova_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[2]].iID = Sticker::sticker_nova_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].flWear = Sticker::sticker_nova_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].flScale = Sticker::sticker_nova_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].iRotation = Sticker::sticker_nova_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_nova_iSlot[3]].iID = Sticker::sticker_nova_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P250, Sticker::stickerSafeWeapon);
		Sticker::sticker_p250_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2501, Sticker::sticker_p250_iSlot[0]);
		Sticker::sticker_p250_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2501, Sticker::sticker_p250_size[0]);
		Sticker::sticker_p250_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2501, Sticker::sticker_p250_id[0]);
		Sticker::sticker_p250_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2501, Sticker::sticker_p250_wear[0]);
		Sticker::sticker_p250_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2501, Sticker::sticker_p250_rotate[0]);
		Sticker::sticker_p250_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2502, Sticker::sticker_p250_iSlot[1]);
		Sticker::sticker_p250_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2502, Sticker::sticker_p250_size[1]);
		Sticker::sticker_p250_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2502, Sticker::sticker_p250_id[1]);
		Sticker::sticker_p250_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2502, Sticker::sticker_p250_wear[1]);
		Sticker::sticker_p250_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2502, Sticker::sticker_p250_rotate[1]);
		Sticker::sticker_p250_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2503, Sticker::sticker_p250_iSlot[2]);
		Sticker::sticker_p250_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2503, Sticker::sticker_p250_size[2]);
		Sticker::sticker_p250_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2503, Sticker::sticker_p250_id[2]);
		Sticker::sticker_p250_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2503, Sticker::sticker_p250_wear[2]);
		Sticker::sticker_p250_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2503, Sticker::sticker_p250_rotate[2]);
		Sticker::sticker_p250_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2504, Sticker::sticker_p250_iSlot[3]);
		Sticker::sticker_p250_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2504, Sticker::sticker_p250_size[3]);
		Sticker::sticker_p250_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2504, Sticker::sticker_p250_id[3]);
		Sticker::sticker_p250_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2504, Sticker::sticker_p250_wear[3]);
		Sticker::sticker_p250_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2504, Sticker::sticker_p250_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].flWear = Sticker::sticker_p250_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].flScale = Sticker::sticker_p250_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].iRotation = Sticker::sticker_p250_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[0]].iID = Sticker::sticker_p250_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].flWear = Sticker::sticker_p250_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].flScale = Sticker::sticker_p250_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].iRotation = Sticker::sticker_p250_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[1]].iID = Sticker::sticker_p250_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].flWear = Sticker::sticker_p250_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].flScale = Sticker::sticker_p250_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].iRotation = Sticker::sticker_p250_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[2]].iID = Sticker::sticker_p250_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].flWear = Sticker::sticker_p250_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].flScale = Sticker::sticker_p250_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].iRotation = Sticker::sticker_p250_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_p250_iSlot[3]].iID = Sticker::sticker_p250_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SCAR, Sticker::stickerSafeWeapon);
		Sticker::sticker_scar_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR1, Sticker::sticker_scar_iSlot[0]);
		Sticker::sticker_scar_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR1, Sticker::sticker_scar_size[0]);
		Sticker::sticker_scar_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR1, Sticker::sticker_scar_id[0]);
		Sticker::sticker_scar_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR1, Sticker::sticker_scar_wear[0]);
		Sticker::sticker_scar_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR1, Sticker::sticker_scar_rotate[0]);
		Sticker::sticker_scar_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR2, Sticker::sticker_scar_iSlot[1]);
		Sticker::sticker_scar_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR2, Sticker::sticker_scar_size[1]);
		Sticker::sticker_scar_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR2, Sticker::sticker_scar_id[1]);
		Sticker::sticker_scar_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR2, Sticker::sticker_scar_wear[1]);
		Sticker::sticker_scar_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR2, Sticker::sticker_scar_rotate[1]);
		Sticker::sticker_scar_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR3, Sticker::sticker_scar_iSlot[2]);
		Sticker::sticker_scar_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR3, Sticker::sticker_scar_size[2]);
		Sticker::sticker_scar_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR3, Sticker::sticker_scar_id[2]);
		Sticker::sticker_scar_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR3, Sticker::sticker_scar_wear[2]);
		Sticker::sticker_scar_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR3, Sticker::sticker_scar_rotate[2]);
		Sticker::sticker_scar_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR4, Sticker::sticker_scar_iSlot[3]);
		Sticker::sticker_scar_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR4, Sticker::sticker_scar_size[3]);
		Sticker::sticker_scar_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR4, Sticker::sticker_scar_id[3]);
		Sticker::sticker_scar_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR4, Sticker::sticker_scar_wear[3]);
		Sticker::sticker_scar_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR4, Sticker::sticker_scar_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].flWear = Sticker::sticker_scar_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].flScale = Sticker::sticker_scar_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].iRotation = Sticker::sticker_scar_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[0]].iID = Sticker::sticker_scar_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].flWear = Sticker::sticker_scar_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].flScale = Sticker::sticker_scar_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].iRotation = Sticker::sticker_scar_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[1]].iID = Sticker::sticker_scar_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].flWear = Sticker::sticker_scar_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].flScale = Sticker::sticker_scar_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].iRotation = Sticker::sticker_scar_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[2]].iID = Sticker::sticker_scar_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].flWear = Sticker::sticker_scar_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].flScale = Sticker::sticker_scar_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].iRotation = Sticker::sticker_scar_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_scar_iSlot[3]].iID = Sticker::sticker_scar_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SG, Sticker::stickerSafeWeapon);
		Sticker::sticker_sg_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG1, Sticker::sticker_sg_iSlot[0]);
		Sticker::sticker_sg_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG1, Sticker::sticker_sg_size[0]);
		Sticker::sticker_sg_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG1, Sticker::sticker_sg_id[0]);
		Sticker::sticker_sg_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG1, Sticker::sticker_sg_wear[0]);
		Sticker::sticker_sg_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG1, Sticker::sticker_sg_rotate[0]);
		Sticker::sticker_sg_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG2, Sticker::sticker_sg_iSlot[1]);
		Sticker::sticker_sg_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG2, Sticker::sticker_sg_size[1]);
		Sticker::sticker_sg_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG2, Sticker::sticker_sg_id[1]);
		Sticker::sticker_sg_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG2, Sticker::sticker_sg_wear[1]);
		Sticker::sticker_sg_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG2, Sticker::sticker_sg_rotate[1]);
		Sticker::sticker_sg_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG3, Sticker::sticker_sg_iSlot[2]);
		Sticker::sticker_sg_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG3, Sticker::sticker_sg_size[2]);
		Sticker::sticker_sg_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG3, Sticker::sticker_sg_id[2]);
		Sticker::sticker_sg_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG3, Sticker::sticker_sg_wear[2]);
		Sticker::sticker_sg_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG3, Sticker::sticker_sg_rotate[2]);
		Sticker::sticker_sg_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG4, Sticker::sticker_sg_iSlot[3]);
		Sticker::sticker_sg_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG4, Sticker::sticker_sg_size[3]);
		Sticker::sticker_sg_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG4, Sticker::sticker_sg_id[3]);
		Sticker::sticker_sg_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG4, Sticker::sticker_sg_wear[3]);
		Sticker::sticker_sg_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG4, Sticker::sticker_sg_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].flWear = Sticker::sticker_sg_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].flScale = Sticker::sticker_sg_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].iRotation = Sticker::sticker_sg_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[0]].iID = Sticker::sticker_sg_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].flWear = Sticker::sticker_sg_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].flScale = Sticker::sticker_sg_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].iRotation = Sticker::sticker_sg_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[1]].iID = Sticker::sticker_sg_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].flWear = Sticker::sticker_sg_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].flScale = Sticker::sticker_sg_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].iRotation = Sticker::sticker_sg_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[2]].iID = Sticker::sticker_sg_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].flWear = Sticker::sticker_sg_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].flScale = Sticker::sticker_sg_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].iRotation = Sticker::sticker_sg_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_sg_iSlot[3]].iID = Sticker::sticker_sg_id[3];
		Sticker::stickerSafeWeapon = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SSG, Sticker::stickerSafeWeapon);
		Sticker::sticker_ssg_iSlot[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG1, Sticker::sticker_ssg_iSlot[0]);
		Sticker::sticker_ssg_size[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG1, Sticker::sticker_ssg_size[0]);
		Sticker::sticker_ssg_id[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG1, Sticker::sticker_ssg_id[0]);
		Sticker::sticker_ssg_wear[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG1, Sticker::sticker_ssg_wear[0]);
		Sticker::sticker_ssg_rotate[0] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG1, Sticker::sticker_ssg_rotate[0]);
		Sticker::sticker_ssg_iSlot[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG2, Sticker::sticker_ssg_iSlot[1]);
		Sticker::sticker_ssg_size[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG2, Sticker::sticker_ssg_size[1]);
		Sticker::sticker_ssg_id[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG2, Sticker::sticker_ssg_id[1]);
		Sticker::sticker_ssg_wear[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG2, Sticker::sticker_ssg_wear[1]);
		Sticker::sticker_ssg_rotate[1] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG2, Sticker::sticker_ssg_rotate[1]);
		Sticker::sticker_ssg_iSlot[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG3, Sticker::sticker_ssg_iSlot[2]);
		Sticker::sticker_ssg_size[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG3, Sticker::sticker_ssg_size[2]);
		Sticker::sticker_ssg_id[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG3, Sticker::sticker_ssg_id[2]);
		Sticker::sticker_ssg_wear[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG3, Sticker::sticker_ssg_wear[2]);
		Sticker::sticker_ssg_rotate[2] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG3, Sticker::sticker_ssg_rotate[2]);
		Sticker::sticker_ssg_iSlot[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG4, Sticker::sticker_ssg_iSlot[3]);
		Sticker::sticker_ssg_size[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG4, Sticker::sticker_ssg_size[3]);
		Sticker::sticker_ssg_id[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG4, Sticker::sticker_ssg_id[3]);
		Sticker::sticker_ssg_wear[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG4, Sticker::sticker_ssg_wear[3]);
		Sticker::sticker_ssg_rotate[3] = CSX::Cvar::LoadCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG4, Sticker::sticker_ssg_rotate[3]);
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].flWear = Sticker::sticker_ssg_wear[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].flScale = Sticker::sticker_ssg_size[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].iRotation = Sticker::sticker_ssg_rotate[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[0]].iID = Sticker::sticker_ssg_id[0];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].flWear = Sticker::sticker_ssg_wear[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].flScale = Sticker::sticker_ssg_size[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].iRotation = Sticker::sticker_ssg_rotate[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[1]].iID = Sticker::sticker_ssg_id[1];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].flWear = Sticker::sticker_ssg_wear[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].flScale = Sticker::sticker_ssg_size[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].iRotation = Sticker::sticker_ssg_rotate[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[2]].iID = Sticker::sticker_ssg_id[2];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].flWear = Sticker::sticker_ssg_wear[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].flScale = Sticker::sticker_ssg_size[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].iRotation = Sticker::sticker_ssg_rotate[3];
		Stick[Settings::Sticker::stickerSafeWeapon].Stickers[Sticker::sticker_ssg_iSlot[3]].iID = Sticker::sticker_ssg_id[3];
		ForceFullUpdate();
		*/
	}

	void SaveSettings(string szIniFile)
	{
		CSX::Cvar::InitPath(szIniFile.c_str());

		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DEATHMATCH, Aimbot::aim_Deathmatch);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_WALLATTACK, Aimbot::aim_WallAttack);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_CHECKSMOKE, Aimbot::aim_CheckSmoke);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_ANTIJUMP, Aimbot::aim_AntiJump);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_RCSTYPE, Aimbot::aim_RcsType);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWFOV, Aimbot::aim_DrawFov);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_DRAWSPOT, Aimbot::aim_DrawSpot);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK, Aimbot::aim_Backtrack);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK_TICK, Aimbot::aim_Backtracktickrate);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			// ���������
			if (i <= 9)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, Aimbot::weapon_aim_settings[i].aim_Active);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCS, Aimbot::weapon_aim_settings[i].aim_Rcs);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_AUTOPISTOL, Aimbot::weapon_aim_settings[i].aim_AutoPistol);
			}

			// ��������
			if (i >= 10 && i <= 30)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, Aimbot::weapon_aim_settings[i].aim_Active);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCS, Aimbot::weapon_aim_settings[i].aim_Rcs);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSFOV, Aimbot::weapon_aim_settings[i].aim_RcsFov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSSMOOTH, Aimbot::weapon_aim_settings[i].aim_RcsSmooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCSCLAMPTYPE, Aimbot::weapon_aim_settings[i].aim_RcsClampType);
			}

			// ���������
			if (i >= 31 && i <= 32)
			{
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_ACTIVE, Aimbot::weapon_aim_settings[i].aim_Active);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SMOOTH, Aimbot::weapon_aim_settings[i].aim_Smooth);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOV, Aimbot::weapon_aim_settings[i].aim_Fov);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_FOVTYPE, Aimbot::weapon_aim_settings[i].aim_FovType);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_BESTHIT, Aimbot::weapon_aim_settings[i].aim_BestHit);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_SPOT, Aimbot::weapon_aim_settings[i].aim_Spot);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_DELAY, Aimbot::weapon_aim_settings[i].aim_Delay);
				CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_AIMBOT_RCS, Aimbot::weapon_aim_settings[i].aim_Rcs);
			}
		}

		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_ENABLE, Triggerbot::trigger_Enable);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DEATHMATCH, Triggerbot::trigger_Deathmatch);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_WALLATTACK, Triggerbot::trigger_WallAttack);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_FASTZOOM, Triggerbot::trigger_FastZoom);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_KEYMODE, Triggerbot::trigger_KeyMode);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOV, Triggerbot::trigger_DrawFov);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_SMOKCHECK, Triggerbot::trigger_SmokCheck);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWSPOT, Triggerbot::trigger_DrawSpot);
		CSX::Cvar::SaveCvar(TRIGGER_TEXT, CVAR_TRIGGER_DRAWFOVASSIST, Triggerbot::trigger_DrawFovAssist);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMIN, Triggerbot::weapon_trigger_settings[i].trigger_DistanceMin);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DISTANCEMAX, Triggerbot::weapon_trigger_settings[i].trigger_DistanceMax);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_FOV, Triggerbot::weapon_trigger_settings[i].trigger_Fov);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DELAYBEFORE, Triggerbot::weapon_trigger_settings[i].trigger_DelayBefore);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_DELAYAFTER, Triggerbot::weapon_trigger_settings[i].trigger_DelayAfter);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_HEADONLY, Triggerbot::weapon_trigger_settings[i].trigger_HeadOnly);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_HITGROUP, Triggerbot::weapon_trigger_settings[i].trigger_HitGroup);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSIST, Triggerbot::weapon_trigger_settings[i].trigger_Assist);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOV, Triggerbot::weapon_trigger_settings[i].trigger_AssistFov);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTRCS, Triggerbot::weapon_trigger_settings[i].trigger_AssistRcs);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTFOVTYPE, Triggerbot::weapon_trigger_settings[i].trigger_AssistFovType);
			CSX::Cvar::SaveCvar(pWeaponData[i], CVAR_TRIGGER_ASSISTSMOOTH, Triggerbot::weapon_trigger_settings[i].trigger_AssistSmooth);
		}

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_STYLE, Settings::Esp::esp_Style);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SIZE, Settings::Esp::esp_Size);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CAPITALTOGGLE, Settings::Esp::esp_CapitalToggle);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_LINE, Settings::Esp::esp_Line);
		
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_OUTLINE, Settings::Esp::esp_Outline);
		
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WALLSOPACITY, Settings::Esp::esp_WallsOpacity);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_NAME, Settings::Esp::esp_Name);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_TIME, Settings::Esp::esp_Time);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WATER, Settings::Esp::esp_Watermark);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHEATBUILD, Settings::Esp::esp_Cheatbuild);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_ENABLED, Settings::Esp::esp_HitMarker);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HITMARKER_COMBO, Settings::Esp::esp_HitMarkerSound);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_RANK, Settings::Esp::esp_Rank);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HEALTH, Settings::Esp::esp_Health);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_ARMOR, Settings::Esp::esp_Armor);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WEAPON, Settings::Esp::esp_Weapon);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_AMMO, Settings::Esp::esp_Ammo);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_DISTANCE, Settings::Esp::esp_Distance);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SOUND, Settings::Esp::esp_Sound);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_GRENADEPREDICTION, Settings::Esp::esp_GrenadePrediction);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BEAMS, Settings::Esp::esp_beams_tracer);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_SKELETON, Settings::Esp::esp_Skeleton);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BULLETTRACE, Settings::Esp::esp_BulletTrace);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_TEAM, Settings::Esp::esp_Team);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_ENEMY, Settings::Esp::esp_Enemy);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_VISIBLE, Settings::Esp::esp_Visible);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHAMSVISIBLE, Settings::Esp::esp_ChamsVisible);

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_CHAMS, Settings::Esp::esp_Chams);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BOMB, Settings::Esp::esp_Bomb);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BOMBTIMER, Settings::Esp::esp_BombTimer);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BEAMS_DURATION, Settings::Esp::flTracersDuration);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_BEAMS_WIDTH, Settings::Esp::flTracersWidth);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WORLDWEAPONS, Settings::Esp::esp_WorldWeapons);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_WORLDGRENADE, Settings::Esp::esp_WorldGrenade);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_HEALTH_CHAMS, Esp::esp_Chams);

		string Color_HITMARKER =
			to_string(int(Esp::esp_HitMarkerColor[0] * 255.f)) + "," +
			to_string(int(Esp::esp_HitMarkerColor[1] * 255.f)) + "," +
			to_string(int(Esp::esp_HitMarkerColor[2] * 255.f));

		string Color_BulletBeams =
			to_string(int(Esp::flTracer_Beam[0] * 255.f)) + "," +
			to_string(int(Esp::flTracer_Beam[1] * 255.f)) + "," +
			to_string(int(Esp::flTracer_Beam[2] * 255.f));

		string esp_Color_CT =
			to_string(int(Settings::Esp::esp_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_CT[2] * 255.f));

		string esp_Color_TT =
			to_string(int(Settings::Esp::esp_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_TT[2] * 255.f));

		string esp_Color_VCT =
			to_string(int(Settings::Esp::esp_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VCT[2] * 255.f));

		string esp_Color_VTT =
			to_string(int(Settings::Esp::esp_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		string GrenadeHelper =
			to_string(int(Settings::Esp::GrenadeHelper[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::GrenadeHelper[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::GrenadeHelper[2] * 255.f));



		CSX::Cvar::SaveCvar(VISUAL_TEXT, "esp_HitMarkerColor", Color_HITMARKER);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_CT, esp_Color_CT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_TT, esp_Color_TT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VCT, esp_Color_VCT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_VTT, esp_Color_VTT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_GrenadeHelper, GrenadeHelper);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_ESP_COLOR_BulletBeams, Color_BulletBeams);

		string chams_Color_CT =
			to_string(int(Settings::Esp::chams_Color_CT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_CT[2] * 255.f));

		string chams_Color_TT =
			to_string(int(Settings::Esp::chams_Color_TT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_TT[2] * 255.f));

		string chams_Color_VCT =
			to_string(int(Settings::Esp::chams_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VCT[2] * 255.f));

		string chams_Color_VTT =
			to_string(int(Settings::Esp::chams_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Settings::Esp::chams_Color_VTT[2] * 255.f));

		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_CT, chams_Color_CT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_TT, chams_Color_TT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VCT, chams_Color_VCT);
		CSX::Cvar::SaveCvar(VISUAL_TEXT, CVAR_CHAMS_COLOR_VTT, chams_Color_VTT);

		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ACTIVE, Radar::rad_Active);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_TEAM, Radar::rad_Team);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ENEMY, Radar::rad_Enemy);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_SOUND, Radar::rad_Sound);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_INGAME, Radar::rad_InGame);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_RANGE, Radar::rad_Range);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_ALPHA, Radar::rad_Alpha);

		string Color_CT =
			to_string(int(Radar::rad_Color_CT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_CT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_CT[2] * 255.f));

		string Color_TT =
			to_string(int(Radar::rad_Color_TT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_TT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_TT[2] * 255.f));

		string Color_VCT =
			to_string(int(Radar::rad_Color_VCT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VCT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VCT[2] * 255.f));

		string Color_VTT =
			to_string(int(Radar::rad_Color_VTT[0] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VTT[1] * 255.f)) + "," +
			to_string(int(Radar::rad_Color_VTT[2] * 255.f));

		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_CT, Color_CT);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_TT, Color_TT);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_VCT, Color_VCT);
		CSX::Cvar::SaveCvar(RADAR_TEXT, CVAR_RAD_COLOR_VTT, Color_VTT);

		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ACTIVE, Knifebot::knf_Active);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_TEAM, Knifebot::knf_Team);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_ATTACK, Knifebot::knf_Attack);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK, Knifebot::knf_DistAttack);
		CSX::Cvar::SaveCvar(KNIFEBOT_TEXT, CVAR_KNIFEBOT_DISTATTACK2, Knifebot::knf_DistAttack2);

		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_CT_MODEL, Skin::knf_ct_model);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_CT_SKIN, Skin::knf_ct_skin);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_TT_MODEL, Skin::knf_tt_model);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_TT_SKIN, Skin::knf_tt_skin);
		CSX::Cvar::SaveCvar(SKIN_TEXT, CVAR_SKIN_GLOVES, Skin::gloves_skin);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackPaintKit);
		}

		CSX::Cvar::SaveCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality);
		CSX::Cvar::SaveCvar(SKIN_TEXT_QUALITY, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_QUALITY, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].iEntityQuality);
		}

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_STAT, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackStatTrak);
		}

		CSX::Cvar::SaveCvar(SKIN_TEXT_WEAR, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear);
		CSX::Cvar::SaveCvar(SKIN_TEXT_WEAR, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_WEAR, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].flFallbackWear);
		}

		CSX::Cvar::SaveCvar(SKIN_TEXT_SEED, CVAR_SKIN_CT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed);
		CSX::Cvar::SaveCvar(SKIN_TEXT_SEED, CVAR_SKIN_TT_MODEL, g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed);

		for (DWORD i = 0; i < WEAPON_DATA_SIZE; i++)
		{
			CSX::Cvar::SaveCvar(SKIN_TEXT_SEED, pWeaponData[i], g_SkinChangerCfg[pWeaponItemIndexData[i]].nFallbackSeed);
		}

		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_RANK_ID, ProfileChanger::rank_id);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_WINS, ProfileChanger::wins);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_CMD_FRIENDLY, ProfileChanger::cmd_friendly);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_CMD_LEADER, ProfileChanger::cmd_leader);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_CMD_TEACHING, ProfileChanger::cmd_teaching);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_LEVEL, ProfileChanger::level);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_XP, ProfileChanger::xp);

		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_SKIN_CHANGER, Misc::misc_SkinChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_STICKER_CHANGER, Misc::misc_StickerChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_KNIFE_CHANGER, Misc::misc_KnifeChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_EPOSTPROCESS, Misc::misc_EPostprocess);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_GRENADETRAJECTORY, Misc::misc_GrenadeTrajectory);
		CSX::Cvar::SaveCvar(AIMBOT_TEXT, CVAR_AIMBOT_BACKTRACK, Aimbot::aim_Backtrack);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_BHOP, Misc::misc_Bhop);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_PUNCH, Misc::misc_Punch);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOFLASH, Misc::misc_NoFlash);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOSMOKE, Misc::misc_NoSmoke);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_WIREFRAMESMOKE, Misc::misc_wireframesmoke);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_WIREHANDS, Misc::misc_WireHands);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_NOHANDS, Misc::misc_NoHands);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AWPAIM, Misc::misc_AwpAim);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AUTOSTRAFE, Misc::misc_AutoStrafe);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_LEGITAATOGGLE, Misc::misc_LegitAAToggle);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_AUTOACCEPT, Misc::misc_AutoAccept);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_SPECTATORS, Misc::misc_Spectators);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_CHANGER, Misc::misc_FovChanger);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_VIEW, Misc::misc_FovView);
		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_FOV_MDL_VIEW, Misc::misc_FovModelView);

		string Color_MENU =
			to_string(int(Misc::misc_MenuColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_MenuColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_MenuColor[2] * 255.f));

		CSX::Cvar::SaveCvar(MISC_TEXT, CVAR_MISC_MENU_COLOR, Color_MENU);

		string Color_TEXT =
			to_string(int(Misc::misc_TextColor[0] * 255.f)) + "," +
			to_string(int(Misc::misc_TextColor[1] * 255.f)) + "," +
			to_string(int(Misc::misc_TextColor[2] * 255.f));

		CSX::Cvar::SaveCvar(MISC_TEXT, "misc_TextColor", Color_TEXT);

		/*
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE1, Sticker::sticker_deserteagle_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE1, Sticker::sticker_deserteagle_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE1, Sticker::sticker_deserteagle_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE1, Sticker::sticker_deserteagle_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE1, Sticker::sticker_deserteagle_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE2, Sticker::sticker_deserteagle_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE2, Sticker::sticker_deserteagle_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE2, Sticker::sticker_deserteagle_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE2, Sticker::sticker_deserteagle_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE2, Sticker::sticker_deserteagle_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE3, Sticker::sticker_deserteagle_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE3, Sticker::sticker_deserteagle_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE3, Sticker::sticker_deserteagle_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE3, Sticker::sticker_deserteagle_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE3, Sticker::sticker_deserteagle_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_DEAGLE4, Sticker::sticker_deserteagle_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_DEAGLE4, Sticker::sticker_deserteagle_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_DEAGLE4, Sticker::sticker_deserteagle_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_DEAGLE4, Sticker::sticker_deserteagle_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_DEAGLE4, Sticker::sticker_deserteagle_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES1, Sticker::sticker_elites_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES1, Sticker::sticker_elites_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES1, Sticker::sticker_elites_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES1, Sticker::sticker_elites_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES1, Sticker::sticker_elites_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES2, Sticker::sticker_elites_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES2, Sticker::sticker_elites_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES2, Sticker::sticker_elites_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES2, Sticker::sticker_elites_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES2, Sticker::sticker_elites_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES3, Sticker::sticker_elites_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES3, Sticker::sticker_elites_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES3, Sticker::sticker_elites_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES3, Sticker::sticker_elites_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES3, Sticker::sticker_elites_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_ELITES4, Sticker::sticker_elites_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_ELITES4, Sticker::sticker_elites_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_ELITES4, Sticker::sticker_elites_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_ELITES4, Sticker::sticker_elites_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_ELITES4, Sticker::sticker_elites_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN1, Sticker::sticker_fiveseven_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN1, Sticker::sticker_fiveseven_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN1, Sticker::sticker_fiveseven_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN1, Sticker::sticker_fiveseven_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN1, Sticker::sticker_fiveseven_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN2, Sticker::sticker_fiveseven_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN2, Sticker::sticker_fiveseven_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN2, Sticker::sticker_fiveseven_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN2, Sticker::sticker_fiveseven_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN2, Sticker::sticker_fiveseven_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN3, Sticker::sticker_fiveseven_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN3, Sticker::sticker_fiveseven_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN3, Sticker::sticker_fiveseven_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN3, Sticker::sticker_fiveseven_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN3, Sticker::sticker_fiveseven_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FIVESEVEN4, Sticker::sticker_fiveseven_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FIVESEVEN4, Sticker::sticker_fiveseven_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FIVESEVEN4, Sticker::sticker_fiveseven_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FIVESEVEN4, Sticker::sticker_fiveseven_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FIVESEVEN4, Sticker::sticker_fiveseven_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK1, Sticker::sticker_glock_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK1, Sticker::sticker_glock_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK1, Sticker::sticker_glock_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK1, Sticker::sticker_glock_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK1, Sticker::sticker_glock_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK2, Sticker::sticker_glock_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK2, Sticker::sticker_glock_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK2, Sticker::sticker_glock_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK2, Sticker::sticker_glock_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK2, Sticker::sticker_glock_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK3, Sticker::sticker_glock_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK3, Sticker::sticker_glock_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK3, Sticker::sticker_glock_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK3, Sticker::sticker_glock_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK3, Sticker::sticker_glock_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GLOCK4, Sticker::sticker_glock_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GLOCK4, Sticker::sticker_glock_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GLOCK4, Sticker::sticker_glock_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GLOCK4, Sticker::sticker_glock_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GLOCK4, Sticker::sticker_glock_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK1, Sticker::sticker_ak_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK1, Sticker::sticker_ak_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK1, Sticker::sticker_ak_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK1, Sticker::sticker_ak_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK1, Sticker::sticker_ak_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK2, Sticker::sticker_ak_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK2, Sticker::sticker_ak_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK2, Sticker::sticker_ak_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK2, Sticker::sticker_ak_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK2, Sticker::sticker_ak_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK3, Sticker::sticker_ak_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK3, Sticker::sticker_ak_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK3, Sticker::sticker_ak_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK3, Sticker::sticker_ak_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK3, Sticker::sticker_ak_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AK4, Sticker::sticker_ak_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AK4, Sticker::sticker_ak_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AK4, Sticker::sticker_ak_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AK4, Sticker::sticker_ak_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AK4, Sticker::sticker_ak_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG1, Sticker::sticker_aug_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG1, Sticker::sticker_aug_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG1, Sticker::sticker_aug_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG1, Sticker::sticker_aug_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG1, Sticker::sticker_aug_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG2, Sticker::sticker_aug_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG2, Sticker::sticker_aug_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG2, Sticker::sticker_aug_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG2, Sticker::sticker_aug_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG2, Sticker::sticker_aug_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG3, Sticker::sticker_aug_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG3, Sticker::sticker_aug_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG3, Sticker::sticker_aug_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG3, Sticker::sticker_aug_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG3, Sticker::sticker_aug_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AUG4, Sticker::sticker_aug_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AUG4, Sticker::sticker_aug_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AUG4, Sticker::sticker_aug_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AUG4, Sticker::sticker_aug_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AUG4, Sticker::sticker_aug_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP1, Sticker::sticker_awp_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP1, Sticker::sticker_awp_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP1, Sticker::sticker_awp_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP1, Sticker::sticker_awp_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP1, Sticker::sticker_awp_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP2, Sticker::sticker_awp_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP2, Sticker::sticker_awp_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP2, Sticker::sticker_awp_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP2, Sticker::sticker_awp_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP2, Sticker::sticker_awp_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP3, Sticker::sticker_awp_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP3, Sticker::sticker_awp_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP3, Sticker::sticker_awp_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP3, Sticker::sticker_awp_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP3, Sticker::sticker_awp_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_AWP4, Sticker::sticker_awp_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_AWP4, Sticker::sticker_awp_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_AWP4, Sticker::sticker_awp_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_AWP4, Sticker::sticker_awp_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_AWP4, Sticker::sticker_awp_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS1, Sticker::sticker_famas_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS1, Sticker::sticker_famas_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS1, Sticker::sticker_famas_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS1, Sticker::sticker_famas_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS1, Sticker::sticker_famas_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS2, Sticker::sticker_famas_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS2, Sticker::sticker_famas_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS2, Sticker::sticker_famas_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS2, Sticker::sticker_famas_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS2, Sticker::sticker_famas_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS3, Sticker::sticker_famas_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS3, Sticker::sticker_famas_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS3, Sticker::sticker_famas_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS3, Sticker::sticker_famas_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS3, Sticker::sticker_famas_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_FAMAS4, Sticker::sticker_famas_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_FAMAS4, Sticker::sticker_famas_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_FAMAS4, Sticker::sticker_famas_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_FAMAS4, Sticker::sticker_famas_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_FAMAS4, Sticker::sticker_famas_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G11, Sticker::sticker_g35g1_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G11, Sticker::sticker_g35g1_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G11, Sticker::sticker_g35g1_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G11, Sticker::sticker_g35g1_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G11, Sticker::sticker_g35g1_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G12, Sticker::sticker_g35g1_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G12, Sticker::sticker_g35g1_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G12, Sticker::sticker_g35g1_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G12, Sticker::sticker_g35g1_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G12, Sticker::sticker_g35g1_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G13, Sticker::sticker_g35g1_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G13, Sticker::sticker_g35g1_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G13, Sticker::sticker_g35g1_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G13, Sticker::sticker_g35g1_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G13, Sticker::sticker_g35g1_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_G35G14, Sticker::sticker_g35g1_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_G35G14, Sticker::sticker_g35g1_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_G35G14, Sticker::sticker_g35g1_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_G35G14, Sticker::sticker_g35g1_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_G35G14, Sticker::sticker_g35g1_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL1, Sticker::sticker_galil_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL1, Sticker::sticker_galil_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL1, Sticker::sticker_galil_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL1, Sticker::sticker_galil_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL1, Sticker::sticker_galil_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL2, Sticker::sticker_galil_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL2, Sticker::sticker_galil_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL2, Sticker::sticker_galil_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL2, Sticker::sticker_galil_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL2, Sticker::sticker_galil_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL3, Sticker::sticker_galil_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL3, Sticker::sticker_galil_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL3, Sticker::sticker_galil_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL3, Sticker::sticker_galil_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL3, Sticker::sticker_galil_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_GALIL4, Sticker::sticker_galil_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_GALIL4, Sticker::sticker_galil_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_GALIL4, Sticker::sticker_galil_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_GALIL4, Sticker::sticker_galil_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_GALIL4, Sticker::sticker_galil_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2491, Sticker::sticker_m249_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2491, Sticker::sticker_m249_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2491, Sticker::sticker_m249_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2491, Sticker::sticker_m249_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2491, Sticker::sticker_m249_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2492, Sticker::sticker_m249_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2492, Sticker::sticker_m249_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2492, Sticker::sticker_m249_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2492, Sticker::sticker_m249_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2492, Sticker::sticker_m249_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2493, Sticker::sticker_m249_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2493, Sticker::sticker_m249_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2493, Sticker::sticker_m249_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2493, Sticker::sticker_m249_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2493, Sticker::sticker_m249_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M2494, Sticker::sticker_m249_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M2494, Sticker::sticker_m249_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M2494, Sticker::sticker_m249_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M2494, Sticker::sticker_m249_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M2494, Sticker::sticker_m249_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A41, Sticker::sticker_m4a4_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A41, Sticker::sticker_m4a4_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A41, Sticker::sticker_m4a4_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A41, Sticker::sticker_m4a4_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A41, Sticker::sticker_m4a4_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A42, Sticker::sticker_m4a4_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A42, Sticker::sticker_m4a4_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A42, Sticker::sticker_m4a4_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A42, Sticker::sticker_m4a4_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A42, Sticker::sticker_m4a4_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A43, Sticker::sticker_m4a4_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A43, Sticker::sticker_m4a4_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A43, Sticker::sticker_m4a4_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A43, Sticker::sticker_m4a4_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A43, Sticker::sticker_m4a4_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_M4A44, Sticker::sticker_m4a4_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_M4A44, Sticker::sticker_m4a4_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_M4A44, Sticker::sticker_m4a4_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_M4A44, Sticker::sticker_m4a4_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_M4A44, Sticker::sticker_m4a4_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC101, Sticker::sticker_mac10_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC101, Sticker::sticker_mac10_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC101, Sticker::sticker_mac10_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC101, Sticker::sticker_mac10_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC101, Sticker::sticker_mac10_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC102, Sticker::sticker_mac10_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC102, Sticker::sticker_mac10_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC102, Sticker::sticker_mac10_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC102, Sticker::sticker_mac10_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC102, Sticker::sticker_mac10_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC103, Sticker::sticker_mac10_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC103, Sticker::sticker_mac10_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC103, Sticker::sticker_mac10_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC103, Sticker::sticker_mac10_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC103, Sticker::sticker_mac10_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAC104, Sticker::sticker_mac10_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAC104, Sticker::sticker_mac10_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAC104, Sticker::sticker_mac10_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAC104, Sticker::sticker_mac10_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAC104, Sticker::sticker_mac10_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P901, Sticker::sticker_p90_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P901, Sticker::sticker_p90_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P901, Sticker::sticker_p90_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P901, Sticker::sticker_p90_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P901, Sticker::sticker_p90_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P902, Sticker::sticker_p90_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P902, Sticker::sticker_p90_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P902, Sticker::sticker_p90_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P902, Sticker::sticker_p90_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P902, Sticker::sticker_p90_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P903, Sticker::sticker_p90_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P903, Sticker::sticker_p90_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P903, Sticker::sticker_p90_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P903, Sticker::sticker_p90_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P903, Sticker::sticker_p90_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P904, Sticker::sticker_p90_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P904, Sticker::sticker_p90_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P904, Sticker::sticker_p90_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P904, Sticker::sticker_p90_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P904, Sticker::sticker_p90_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP1, Sticker::sticker_ump_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP1, Sticker::sticker_ump_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP1, Sticker::sticker_ump_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP1, Sticker::sticker_ump_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP1, Sticker::sticker_ump_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP2, Sticker::sticker_ump_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP2, Sticker::sticker_ump_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP2, Sticker::sticker_ump_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP2, Sticker::sticker_ump_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP2, Sticker::sticker_ump_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP3, Sticker::sticker_ump_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP3, Sticker::sticker_ump_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP3, Sticker::sticker_ump_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP3, Sticker::sticker_ump_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP3, Sticker::sticker_ump_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_UMP4, Sticker::sticker_ump_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_UMP4, Sticker::sticker_ump_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_UMP4, Sticker::sticker_ump_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_UMP4, Sticker::sticker_ump_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_UMP4, Sticker::sticker_ump_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM1, Sticker::sticker_xm_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM1, Sticker::sticker_xm_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM1, Sticker::sticker_xm_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM1, Sticker::sticker_xm_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM1, Sticker::sticker_xm_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM2, Sticker::sticker_xm_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM2, Sticker::sticker_xm_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM2, Sticker::sticker_xm_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM2, Sticker::sticker_xm_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM2, Sticker::sticker_xm_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM3, Sticker::sticker_xm_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM3, Sticker::sticker_xm_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM3, Sticker::sticker_xm_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM3, Sticker::sticker_xm_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM3, Sticker::sticker_xm_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_XM4, Sticker::sticker_xm_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_XM4, Sticker::sticker_xm_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_XM4, Sticker::sticker_xm_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_XM4, Sticker::sticker_xm_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_XM4, Sticker::sticker_xm_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON1, Sticker::sticker_bizon_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON1, Sticker::sticker_bizon_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON1, Sticker::sticker_bizon_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON1, Sticker::sticker_bizon_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON1, Sticker::sticker_bizon_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON2, Sticker::sticker_bizon_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON2, Sticker::sticker_bizon_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON2, Sticker::sticker_bizon_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON2, Sticker::sticker_bizon_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON2, Sticker::sticker_bizon_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON3, Sticker::sticker_bizon_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON3, Sticker::sticker_bizon_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON3, Sticker::sticker_bizon_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON3, Sticker::sticker_bizon_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON3, Sticker::sticker_bizon_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_BIZON4, Sticker::sticker_bizon_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_BIZON4, Sticker::sticker_bizon_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_BIZON4, Sticker::sticker_bizon_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_BIZON4, Sticker::sticker_bizon_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_BIZON4, Sticker::sticker_bizon_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG71, Sticker::sticker_mag7_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG71, Sticker::sticker_mag7_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG71, Sticker::sticker_mag7_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG71, Sticker::sticker_mag7_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG71, Sticker::sticker_mag7_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG72, Sticker::sticker_mag7_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG72, Sticker::sticker_mag7_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG72, Sticker::sticker_mag7_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG72, Sticker::sticker_mag7_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG72, Sticker::sticker_mag7_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG73, Sticker::sticker_mag7_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG73, Sticker::sticker_mag7_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG73, Sticker::sticker_mag7_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG73, Sticker::sticker_mag7_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG73, Sticker::sticker_mag7_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MAG74, Sticker::sticker_mag7_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MAG74, Sticker::sticker_mag7_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MAG74, Sticker::sticker_mag7_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MAG74, Sticker::sticker_mag7_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MAG74, Sticker::sticker_mag7_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV1, Sticker::sticker_negev_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV1, Sticker::sticker_negev_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV1, Sticker::sticker_negev_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV1, Sticker::sticker_negev_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV1, Sticker::sticker_negev_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV2, Sticker::sticker_negev_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV2, Sticker::sticker_negev_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV2, Sticker::sticker_negev_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV2, Sticker::sticker_negev_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV2, Sticker::sticker_negev_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV3, Sticker::sticker_negev_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV3, Sticker::sticker_negev_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV3, Sticker::sticker_negev_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV3, Sticker::sticker_negev_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV3, Sticker::sticker_negev_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NEGEV4, Sticker::sticker_negev_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NEGEV4, Sticker::sticker_negev_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NEGEV4, Sticker::sticker_negev_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NEGEV4, Sticker::sticker_negev_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NEGEV4, Sticker::sticker_negev_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF1, Sticker::sticker_sawedoff_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF1, Sticker::sticker_sawedoff_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF1, Sticker::sticker_sawedoff_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF1, Sticker::sticker_sawedoff_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF1, Sticker::sticker_sawedoff_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF2, Sticker::sticker_sawedoff_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF2, Sticker::sticker_sawedoff_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF2, Sticker::sticker_sawedoff_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF2, Sticker::sticker_sawedoff_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF2, Sticker::sticker_sawedoff_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF3, Sticker::sticker_sawedoff_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF3, Sticker::sticker_sawedoff_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF3, Sticker::sticker_sawedoff_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF3, Sticker::sticker_sawedoff_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF3, Sticker::sticker_sawedoff_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SAWEDOFF4, Sticker::sticker_sawedoff_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SAWEDOFF4, Sticker::sticker_sawedoff_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SAWEDOFF4, Sticker::sticker_sawedoff_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SAWEDOFF4, Sticker::sticker_sawedoff_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SAWEDOFF4, Sticker::sticker_sawedoff_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC1, Sticker::sticker_tec_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC1, Sticker::sticker_tec_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC1, Sticker::sticker_tec_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC1, Sticker::sticker_tec_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC1, Sticker::sticker_tec_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC2, Sticker::sticker_tec_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC2, Sticker::sticker_tec_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC2, Sticker::sticker_tec_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC2, Sticker::sticker_tec_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC2, Sticker::sticker_tec_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC3, Sticker::sticker_tec_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC3, Sticker::sticker_tec_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC3, Sticker::sticker_tec_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC3, Sticker::sticker_tec_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC3, Sticker::sticker_tec_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_TEC4, Sticker::sticker_tec_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_TEC4, Sticker::sticker_tec_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_TEC4, Sticker::sticker_tec_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_TEC4, Sticker::sticker_tec_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_TEC4, Sticker::sticker_tec_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20001, Sticker::sticker_p2000_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20001, Sticker::sticker_p2000_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20001, Sticker::sticker_p2000_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20001, Sticker::sticker_p2000_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20001, Sticker::sticker_p2000_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20002, Sticker::sticker_p2000_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20002, Sticker::sticker_p2000_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20002, Sticker::sticker_p2000_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20002, Sticker::sticker_p2000_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20002, Sticker::sticker_p2000_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20003, Sticker::sticker_p2000_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20003, Sticker::sticker_p2000_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20003, Sticker::sticker_p2000_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20003, Sticker::sticker_p2000_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20003, Sticker::sticker_p2000_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P20004, Sticker::sticker_p2000_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P20004, Sticker::sticker_p2000_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P20004, Sticker::sticker_p2000_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P20004, Sticker::sticker_p2000_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P20004, Sticker::sticker_p2000_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP71, Sticker::sticker_mp7_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP71, Sticker::sticker_mp7_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP71, Sticker::sticker_mp7_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP71, Sticker::sticker_mp7_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP71, Sticker::sticker_mp7_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP72, Sticker::sticker_mp7_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP72, Sticker::sticker_mp7_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP72, Sticker::sticker_mp7_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP72, Sticker::sticker_mp7_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP72, Sticker::sticker_mp7_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP73, Sticker::sticker_mp7_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP73, Sticker::sticker_mp7_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP73, Sticker::sticker_mp7_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP73, Sticker::sticker_mp7_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP73, Sticker::sticker_mp7_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP74, Sticker::sticker_mp7_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP74, Sticker::sticker_mp7_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP74, Sticker::sticker_mp7_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP74, Sticker::sticker_mp7_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP74, Sticker::sticker_mp7_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP91, Sticker::sticker_mp9_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP91, Sticker::sticker_mp9_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP91, Sticker::sticker_mp9_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP91, Sticker::sticker_mp9_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP91, Sticker::sticker_mp9_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP92, Sticker::sticker_mp9_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP92, Sticker::sticker_mp9_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP92, Sticker::sticker_mp9_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP92, Sticker::sticker_mp9_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP92, Sticker::sticker_mp9_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP93, Sticker::sticker_mp9_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP93, Sticker::sticker_mp9_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP93, Sticker::sticker_mp9_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP93, Sticker::sticker_mp9_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP93, Sticker::sticker_mp9_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_MP94, Sticker::sticker_mp9_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_MP94, Sticker::sticker_mp9_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_MP94, Sticker::sticker_mp9_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_MP94, Sticker::sticker_mp9_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_MP94, Sticker::sticker_mp9_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA1, Sticker::sticker_nova_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA1, Sticker::sticker_nova_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA1, Sticker::sticker_nova_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA1, Sticker::sticker_nova_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA1, Sticker::sticker_nova_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA2, Sticker::sticker_nova_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA2, Sticker::sticker_nova_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA2, Sticker::sticker_nova_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA2, Sticker::sticker_nova_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA2, Sticker::sticker_nova_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA3, Sticker::sticker_nova_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA3, Sticker::sticker_nova_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA3, Sticker::sticker_nova_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA3, Sticker::sticker_nova_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA3, Sticker::sticker_nova_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_NOVA4, Sticker::sticker_nova_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_NOVA4, Sticker::sticker_nova_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_NOVA4, Sticker::sticker_nova_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_NOVA4, Sticker::sticker_nova_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_NOVA4, Sticker::sticker_nova_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2501, Sticker::sticker_p250_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2501, Sticker::sticker_p250_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2501, Sticker::sticker_p250_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2501, Sticker::sticker_p250_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2501, Sticker::sticker_p250_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2502, Sticker::sticker_p250_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2502, Sticker::sticker_p250_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2502, Sticker::sticker_p250_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2502, Sticker::sticker_p250_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2502, Sticker::sticker_p250_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2503, Sticker::sticker_p250_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2503, Sticker::sticker_p250_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2503, Sticker::sticker_p250_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2503, Sticker::sticker_p250_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2503, Sticker::sticker_p250_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_P2504, Sticker::sticker_p250_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_P2504, Sticker::sticker_p250_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_P2504, Sticker::sticker_p250_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_P2504, Sticker::sticker_p250_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_P2504, Sticker::sticker_p250_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR1, Sticker::sticker_scar_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR1, Sticker::sticker_scar_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR1, Sticker::sticker_scar_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR1, Sticker::sticker_scar_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR1, Sticker::sticker_scar_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR2, Sticker::sticker_scar_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR2, Sticker::sticker_scar_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR2, Sticker::sticker_scar_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR2, Sticker::sticker_scar_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR2, Sticker::sticker_scar_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR3, Sticker::sticker_scar_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR3, Sticker::sticker_scar_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR3, Sticker::sticker_scar_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR3, Sticker::sticker_scar_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR3, Sticker::sticker_scar_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SCAR4, Sticker::sticker_scar_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SCAR4, Sticker::sticker_scar_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SCAR4, Sticker::sticker_scar_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SCAR4, Sticker::sticker_scar_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SCAR4, Sticker::sticker_scar_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG1, Sticker::sticker_sg_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG1, Sticker::sticker_sg_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG1, Sticker::sticker_sg_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG1, Sticker::sticker_sg_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG1, Sticker::sticker_sg_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG2, Sticker::sticker_sg_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG2, Sticker::sticker_sg_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG2, Sticker::sticker_sg_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG2, Sticker::sticker_sg_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG2, Sticker::sticker_sg_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG3, Sticker::sticker_sg_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG3, Sticker::sticker_sg_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG3, Sticker::sticker_sg_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG3, Sticker::sticker_sg_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG3, Sticker::sticker_sg_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SG4, Sticker::sticker_sg_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SG4, Sticker::sticker_sg_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SG4, Sticker::sticker_sg_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SG4, Sticker::sticker_sg_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SG4, Sticker::sticker_sg_iSlot[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG1, Sticker::sticker_ssg_rotate[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG1, Sticker::sticker_ssg_id[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG1, Sticker::sticker_ssg_size[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG1, Sticker::sticker_ssg_wear[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG1, Sticker::sticker_ssg_iSlot[0]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG2, Sticker::sticker_ssg_rotate[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG2, Sticker::sticker_ssg_id[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG2, Sticker::sticker_ssg_size[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG2, Sticker::sticker_ssg_wear[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG2, Sticker::sticker_ssg_iSlot[1]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG3, Sticker::sticker_ssg_rotate[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG3, Sticker::sticker_ssg_id[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG3, Sticker::sticker_ssg_size[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG3, Sticker::sticker_ssg_wear[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG3, Sticker::sticker_ssg_iSlot[2]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERROTATE_SSG4, Sticker::sticker_ssg_rotate[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERID_SSG4, Sticker::sticker_ssg_id[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSIZE_SSG4, Sticker::sticker_ssg_size[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAR_SSG4, Sticker::sticker_ssg_wear[3]);
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERSLOT_SSG4, Sticker::sticker_ssg_iSlot[3]);

		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_DEAGLE, "1");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_ELITES, "2");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FIVESEVEN, "3");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GLOCK, "4");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AK, "7");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AUG, "8");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_AWP, "9");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_FAMAS, "10");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_G35G1, "11");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_GALIL, "13");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M249, "14");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_M4A4, "16");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAC10, "17");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P90, "19");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_UMP, "24");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_XM, "25");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_BIZON, "26");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MAG7, "27");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NEGEV, "28");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SAWEDOFF, "29");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_TEC, "30");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P2000, "32");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP7, "33");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_MP9, "34");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_NOVA, "35");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_P250, "36");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SCAR, "38");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SG, "39");
		CSX::Cvar::SaveCvar(STICKER_TEXT, CVAR_MISC_STICKERWEAPON_SSG, "40");
		*/
	}

	float hitmarkerAlpha;

	int TriggerCharToKey(const char* Key)
	{
		if (!strcmp(Key, CVAR_KEY_MOUSE3)) return 0;
		if (!strcmp(Key, CVAR_KEY_MOUSE4)) return 1;
		if (!strcmp(Key, CVAR_KEY_MOUSE5)) return 2;

		return 0;
	}

	namespace MedalChanger {
		bool enabled = false;
		// std::vector<uint32_t> medals = { 874, 875, 879, 883, 889, 890, 896, 897, 903, 904, 910, 913, 916, 917, 923, 926, 927, 931, 937, 940, 941, 947, 948, 954, 955, 961, 1003, 1015, 1026, 1030, 1318, 1329, 1332, 1338, 1344, 1363, 1372 };
		std::vector<uint32_t> medals = {};
		bool equipped_medal_override = false;
		uint32_t equipped_medal = 0;
	}
	namespace ProfileChanger {
		bool enabled = false;
		int rank_id = 0;
		int wins = 0;
		int cmd_friendly = 0;
		int cmd_leader = 0;
		int cmd_teaching = 0;
		int level = 0;
		int xp = 0;
		int ban = 0;
		int time = 0;
	}
	namespace InventoryChanger {
		bool enabled = false;
		std::vector<k_weapon_data> weapons = {};
	}

	namespace Aimbot
	{
		bool aim_Backtrack = false;
		bool aim_DrawBacktrack = false;
		int aim_Backtracktickrate = 1;
		bool aim_Deathmatch = false;
		bool aim_WallAttack = false;
		bool aim_CheckSmoke = false;
		bool aim_AntiJump = false;
		int aim_RcsType = 0;
		bool aim_DrawFov = false;
		bool aim_DrawSpot = false;

		weapon_aim_s weapon_aim_settings[33] = { 0 };
	}

	/*
	namespace Sticker
	{
	float sticker_deserteagle_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_deserteagle_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_deserteagle_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_deserteagle_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_deserteagle_id[4] = { 0 , 0 , 0, 0 };

	float sticker_elites_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_elites_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_elites_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_elites_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_elites_id[4] = { 0 , 0 , 0, 0 };

	float sticker_fiveseven_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_fiveseven_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_fiveseven_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_fiveseven_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_fiveseven_id[4] = { 0 , 0 , 0, 0 };

	float sticker_glock_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_glock_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_glock_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_glock_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_glock_id[4] = { 0 , 0 , 0, 0 };

	float sticker_ak_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_ak_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_ak_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_ak_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_ak_id[4] = { 0 , 0 , 0, 0 };

	float sticker_aug_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_aug_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_aug_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_aug_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_aug_id[4] = { 0 , 0 , 0, 0 };

	float sticker_awp_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_awp_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_awp_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_awp_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_awp_id[4] = { 0 , 0 , 0, 0 };

	float sticker_famas_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_famas_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_famas_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_famas_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_famas_id[4] = { 0 , 0 , 0, 0 };

	float sticker_g35g1_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_g35g1_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_g35g1_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_g35g1_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_g35g1_id[4] = { 0 , 0 , 0, 0 };

	float sticker_galil_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_galil_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_galil_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_galil_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_galil_id[4] = { 0 , 0 , 0, 0 };

	float sticker_m249_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_m249_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_m249_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_m249_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_m249_id[4] = { 0 , 0 , 0, 0 };

	float sticker_m4a4_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_m4a4_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_m4a4_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_m4a4_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_m4a4_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mac10_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mac10_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mac10_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mac10_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mac10_id[4] = { 0 , 0 , 0, 0 };

	float sticker_p90_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_p90_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_p90_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_p90_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_p90_id[4] = { 0 , 0 , 0, 0 };

	float sticker_ump_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_ump_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_ump_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_ump_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_ump_id[4] = { 0 , 0 , 0, 0 };

	float sticker_xm_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_xm_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_xm_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_xm_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_xm_id[4] = { 0 , 0 , 0, 0 };

	float sticker_bizon_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_bizon_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_bizon_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_bizon_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_bizon_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mag7_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mag7_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mag7_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mag7_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mag7_id[4] = { 0 , 0 , 0, 0 };

	float sticker_negev_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_negev_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_negev_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_negev_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_negev_id[4] = { 0 , 0 , 0, 0 };

	float sticker_sawedoff_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_sawedoff_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_sawedoff_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_sawedoff_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_sawedoff_id[4] = { 0 , 0 , 0, 0 };

	float sticker_tec_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_tec_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_tec_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_tec_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_tec_id[4] = { 0 , 0 , 0, 0 };

	float sticker_p2000_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_p2000_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_p2000_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_p2000_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_p2000_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mp7_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mp7_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mp7_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mp7_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mp7_id[4] = { 0 , 0 , 0, 0 };

	float sticker_mp9_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_mp9_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_mp9_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_mp9_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_mp9_id[4] = { 0 , 0 , 0, 0 };

	float sticker_nova_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_nova_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_nova_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_nova_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_nova_id[4] = { 0 , 0 , 0, 0 };

	float sticker_p250_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_p250_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_p250_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_p250_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_p250_id[4] = { 0 , 0 , 0, 0 };

	float sticker_scar_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_scar_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_scar_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_scar_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_scar_id[4] = { 0 , 0 , 0, 0 };

	float sticker_sg_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_sg_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_sg_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_sg_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_sg_id[4] = { 0 , 0 , 0, 0 };

	float sticker_ssg_wear[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	float sticker_ssg_size[4] = { 0.0f , 0.0f, 0.0f, 0.0f };
	int sticker_ssg_iSlot[4] = { 0 , 0 , 0, 0 };
	int sticker_ssg_rotate[4] = { 0 , 0 , 0, 0 };
	int sticker_ssg_id[4] = { 0 , 0 , 0, 0 };

	int stickerSafeWeapon = 0;
	}
	*/

	namespace Triggerbot
	{
		int trigger_Enable = 0;
		bool trigger_Deathmatch = false;
		bool trigger_WallAttack = false;
		bool trigger_FastZoom = false;
		int trigger_Key = 0;
		int trigger_KeyMode = 0;
		bool trigger_SmokCheck = false;
		bool trigger_DrawFov = false;
		bool trigger_DrawSpot = false;
		bool trigger_DrawFovAssist = false;

		weapon_trigger_s weapon_trigger_settings[33] = { 0 };
	}

	namespace Esp
	{
		int esp_Style = 0; // 0 - Box 1 - CoalBox
		int esp_Size = 1;
		bool esp_CapitalToggle = 0;
		bool esp_Line = false;
		bool esp_Outline = false; // Box ( 0 - Box 1 - OutlineBox ) ,
								  // CoalBox ( 0 - CoalBox 1 - OutlineCoalBox )	

		bool esp_Time = true;
		bool esp_Watermark = true;
		bool esp_Cheatbuild = true;
		bool esp_Name = false;
		bool esp_Rank = false;
		int esp_Health = 0;
		int esp_Armor = 0;
		bool esp_Weapon = false;
		bool esp_Ammo = false;
		bool esp_Distance = false;
		bool esp_Sound = false;
		bool esp_GrenadePrediction = false;
		bool esp_Chicken = false;
		bool esp_Defusing = false;
		bool esp_Circle = false;
		bool esp_Fish = false;
		bool helper = false;
		bool esp_HealthChams = false;


		int esp_WallsOpacity = 100;


		bool bEspWarnings = false;

		float flTracer_Beam[3] = { 0.f, 0.f, 0.f };
		bool esp_beams_tracer;
		float flTracersDuration;
		float flTracersWidth;


		bool esp_AsusWalls = false;
		float esp_Ambient[3];

		bool esp_HitMarker = false;
		int esp_HitMarkerSound = 0;
		float esp_HitMarkerColor[3] = { 0.f, 0.f, 0.f };

		bool esp_Skeleton = 0;
		int esp_BulletTrace = 0;
		bool esp_Team = 1;
		bool esp_Enemy = 1;
		int esp_Visible = 1;
		int esp_ChamsVisible = 1;

		int esp_Chams = 0;
		bool esp_Bomb = false;
		int esp_BombTimer = 40;
		bool esp_WorldWeapons = false;
		bool esp_WorldGrenade = false;
		bool esp_BoxNade = false;
		bool esp_ChromeWorld = false;
		bool esp_MinecraftMode = false;
		bool esp_LSDMode = false;
		bool esp_NightMode = false;

		bool esp_legitAAWarnings = false;

		float esp_Color_CT[3] = { 0.f,0.0f,0.f };
		float esp_Color_TT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VCT[3] = { 0.f,0.0f,0.f };
		float esp_Color_VTT[3] = { 0.f,0.0f,0.f };

		float GrenadeHelper[3] = { 0.f,0.f,0.f };

		float chams_Color_CT[3] = { 0.f,0.0f,0.f };
		float chams_Color_TT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VCT[3] = { 0.f,0.0f,0.f };
		float chams_Color_VTT[3] = { 0.f,0.0f,0.f };
	}

	namespace Radar
	{
		bool rad_Active = false;
		bool rad_Team = false;
		bool rad_Enemy = false;
		bool rad_Sound = false;
		bool rad_InGame = false;
		int rad_Range = 3500;
		int rad_Alpha = 1;
		float rad_Color_CT[3] = { 0.f,0.0f,0.f };
		float rad_Color_TT[3] = { 0.f,0.0f,0.f };
		float rad_Color_VCT[3] = { 0.f,0.f,0.f };
		float rad_Color_VTT[3] = { 0.f,0.f,0.f };
	}

	namespace Knifebot
	{
		bool knf_Active = false;
		bool knf_Team = false;
		int knf_Attack = 2;
		int knf_DistAttack = 72;
		int knf_DistAttack2 = 64;
	}


	namespace Skin
	{
		int knf_ct_model = 0;
		int knf_ct_skin = 0;
		int knf_tt_model = 0;
		int knf_tt_skin = 0;
		int gloves_skin = 0;
	}

	namespace Misc
	{

		QAngle qLastTickAngle;

		float misc_MenuColor[3] = { 0.f, 0.f, 0.f };
		bool misc_ragdoll_gravity;
		int misc_ragdoll_gravity_amount;
		bool misc_pushscale;
		int misc_pushscale_amount;
		bool misc_SkinChanger = false;
		bool misc_KnifeChanger = false;
		bool misc_StickerChanger = false;
		bool stickerids = false;
		bool misc_ThirdPerson = false;
		float misc_ThirdPersonRange = 90.f;
		bool misc_ChamsMaterials = false;
		int misc_ChamsMaterialsList = 0;
		bool misc_ArmMaterials = false;
		int misc_ArmMaterialsList = 0;
		int misc_ArmMaterialsType = 0;
		int misc_Clan = 0;
		bool misc_spamregular = false;
		bool misc_spamrandom = false;
		const char* misc_SkyName;
		int misc_CurrentSky;
		bool misc_NoSky = false;
		bool misc_Snow = false;
		bool misc_EPostprocess = false;
		bool misc_GrenadeTrajectory = false;
		bool misc_Postprocess = false;
		bool misc_Bhop = false;
		bool misc_Punch = false;
		bool misc_NoFlash = false;
		bool misc_WireHands = false;
		bool misc_NoHands = false;
		bool misc_NoSmoke = false;
		bool misc_wireframesmoke = false;
		bool misc_AwpAim = false;
		bool misc_AutoStrafe = false;
		bool misc_LegitAAToggle = false;
		bool misc_AutoAccept = false;
		bool misc_Spectators = false;
		bool misc_RainbowMenu = false;
		float misc_RainbowSpeed = 0.001f;
		bool misc_FovChanger = false;
		int misc_FovView = 90;
		int misc_FovModelView = 68;
		float misc_TextColor[3] = { 0.f, 0.f, 0.f };
		float hitmarkerAlpha;
		bool skinids = false;
		bool medalids = false;
		bool weaponids = false;
		bool misc_LegitAA = false;
		bool window_profilechanger;
		bool window_medalchanger;
		bool window_inventorychanger;
		int misc_fakeping_value = 0;
		bool misc_fakeping = true;
		bool invalwayson = false;
		bool custommodelson = false;
		int customodelst;
		int customodelsct;
		char misc_NameChange = 0;
		bool misc_FullBright = false;
	}
}






















































































































































































































































































































































































































































































































































































































































