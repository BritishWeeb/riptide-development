﻿#include "Misc.h"


using namespace Client;
//[junk_enable /]
//[enc_string_enable /]
void CMisc::OnRender()
{
	int punch_x = (int)g_vCenterScreen.x + (int)g_pPlayers->GetLocal()->vAimPunch.y * 10;
	int punch_y = (int)g_vCenterScreen.y + (int)g_pPlayers->GetLocal()->vAimPunch.x * 10;

	if (Settings::Misc::misc_Punch)
	{
		CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		if (Interfaces::Engine()->IsInGame() && localplayer)
		{
			Vector ViewAngles;
			Interfaces::Engine()->GetViewAngles(ViewAngles);
			ViewAngles += (localplayer->GetAimPunchAngle()) * 2.f;

			Vector fowardVec;
			AngleVectors(ViewAngles, fowardVec);
			fowardVec *= 10000;

			Vector start = localplayer->GetEyePosition();
			Vector end = start + fowardVec, endScreen;

			if (WorldToScreen(end, endScreen) && IsLocalAlive())
			{
				g_pRender->DrawLine(punch_x - 4, punch_y, punch_x + 4, punch_y, Color::White());
				g_pRender->DrawLine(punch_x, punch_y - 4, punch_x, punch_y + 4, Color::White());
			}
		}
	}
}

void CMisc::OnCreateMove(CUserCmd* pCmd)
{

	if (Settings::Misc::misc_fakeping) 
	{
		ConVar* sv_cheats = Interfaces::GetConVar()->FindVar("sv_cheats");
		SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
		sv_cheats_spoofed->SetInt(0);

		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakeloss 3");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakelag 75");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakejitter 53535353");
	}
	else
	{
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakeloss 0");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakelag 0");
		Interfaces::Engine()->ClientCmd_Unrestricted2("net_fakejitter 0");
	}

	static bool gravityTurnedOn = false;

	if (Settings::Misc::misc_ragdoll_gravity) {
		ConVar* Gravity = Interfaces::GetConVar()->FindVar("cl_ragdoll_gravity");
		Gravity->SetValue(Settings::Misc::misc_ragdoll_gravity_amount);
		gravityTurnedOn = true;
	}
	else {
		if (gravityTurnedOn == true) {
			ConVar* Gravity = Interfaces::GetConVar()->FindVar("cl_ragdoll_gravity");
			Gravity->SetValue(800.f);
			gravityTurnedOn = false;
		}
	}

	static bool pushscaleTurnedOn = false;

	if (Settings::Misc::misc_pushscale) {
		ConVar* Pushscale = Interfaces::GetConVar()->FindVar("phys_pushscale");
		Pushscale->SetValue(Settings::Misc::misc_pushscale_amount);
		pushscaleTurnedOn = true;
	}
	else {
		if (pushscaleTurnedOn == true) {
			ConVar* Pushscale = Interfaces::GetConVar()->FindVar("phys_pushscale");
			Pushscale->SetValue(600.f);
			pushscaleTurnedOn = false;
		}
	}

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	int flag = *(PINT)((DWORD)pPlayer + 600); // offset for movetype 

	if (Settings::Misc::misc_Bhop)
	{
		if (!(flag & MOVETYPE_LADDER))
		{
			if (pCmd->buttons & IN_JUMP && !(g_pPlayers->GetLocal()->iFlags & FL_ONGROUND))
			{
				pCmd->buttons &= ~IN_JUMP;
			}
		}
	}

	if (Settings::Misc::misc_spamregular)
		ChatSpamRegular();

	if (Settings::Misc::misc_spamrandom)
		ChatSpamRandom();

	if (Settings::Misc::misc_Clan > 0)
		ClanTag();

	ConVar* skybox = Interfaces::GetConVar()->FindVar("sv_skyname");

	if (Settings::Misc::misc_SkyName) { if (skybox) skybox->SetValue(Settings::Misc::misc_SkyName); }
	if (Settings::Misc::misc_NoSky) { if (skybox) skybox->SetValue("sky_l4d_rural02_ldr"); }

	ConVar* snow = Interfaces::GetConVar()->FindVar("mat_drawgray");

	if (Settings::Misc::misc_Snow)
	{
		snow->SetValue(1);
	}
	else
	{
		snow->SetValue(0);
	}

	ConVar* postprocess = Interfaces::GetConVar()->FindVar("mat_postprocess_enable");

	if (Settings::Misc::misc_EPostprocess)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			postprocess->SetValue(0);
		}
	}
	else
	{
		if (Interfaces::Engine()->IsInGame())
		{
			postprocess->SetValue(1);
		}
	}


	static ConVar* grenadetraj = Interfaces::GetConVar()->FindVar("sv_grenade_trajectory");

	if (Settings::Misc::misc_GrenadeTrajectory)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			grenadetraj->SetValue(1);
		}
	}
	else
	{
		if (Interfaces::Engine()->IsInGame())
		{
			grenadetraj->SetValue(0);
		}
	}

	static ConVar* fullbright = Interfaces::GetConVar()->FindVar("mat_fullbright");
	if (Settings::Misc::misc_FullBright)
	{
		if (Interfaces::Engine()->IsInGame())
		{
			fullbright->SetValue(1);
		}
	}
	else {
		if (Interfaces::Engine()->IsInGame())
		{
			fullbright->SetValue(0);
		}
	}

	/*
	if (Settings::Misc::misc_GrenadeTrajectory)
	{
	if (Interfaces::Engine()->IsInGame())
	{
	ConVar* sv_grenade_trajectory = Interfaces::GetConVar()->FindVar("sv_grenade_trajectory");
	SpoofedConvar* sv_grenade_spoofed = new SpoofedConvar(sv_grenade_trajectory);
	sv_grenade_spoofed->SetInt(1);
	}
	}
	else
	{
	if (Interfaces::Engine()->IsInGame())
	{
	ConVar* sv_grenade_trajectory = Interfaces::GetConVar()->FindVar("sv_grenade_trajectory");
	SpoofedConvar* sv_grenade_spoofed = new SpoofedConvar(sv_grenade_trajectory);
	sv_grenade_spoofed->SetInt(0);
	}

	}
	*/

}

void CMisc::FrameStageNotify(ClientFrameStage_t Stage)
{
	CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (Interfaces::Engine()->IsInGame() && localplayer && Stage == ClientFrameStage_t::FRAME_RENDER_START)
	{
		static QAngle vecAngles;
		Interfaces::Engine()->GetViewAngles(vecAngles);

		if (Settings::Misc::misc_ThirdPerson && !localplayer->IsDead())
		{
			if (!Interfaces::Input()->m_fCameraInThirdPerson)
				Interfaces::Input()->m_fCameraInThirdPerson = true;

			Interfaces::Input()->m_vecCameraOffset = QAngle(vecAngles.x, vecAngles.y, Settings::Misc::misc_ThirdPersonRange);

			*localplayer->GetVAngles() = Settings::Misc::qLastTickAngle;
		}
		else
		{
			if (Interfaces::Input()->m_fCameraInThirdPerson || localplayer->GetIsScoped())
			{
				Interfaces::Input()->m_fCameraInThirdPerson = false;
				Interfaces::Input()->m_vecCameraOffset = QAngle(vecAngles.x, vecAngles.y, 0);
			}
		}
	}
}

void CMisc::OnDrawModelExecute()
{
	static bool NoSmoke = false;
	static bool NoFlashReset = false;
	static bool WireFrameSmoke = false;

	if (Settings::Misc::misc_NoFlash && !NoFlashReset)
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial("effects\\flashbang_white",
			TEXTURE_GROUP_CLIENT_EFFECTS);

		if (flash && flashWhite)
		{
			flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoFlashReset = true;
		}
	}
	else if (!Settings::Misc::misc_NoFlash && NoFlashReset)
	{
		IMaterial* flash = Interfaces::MaterialSystem()->FindMaterial(
			"effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* flashWhite = Interfaces::MaterialSystem()->FindMaterial("effects\\flashbang_white",
			TEXTURE_GROUP_CLIENT_EFFECTS);

		if (flash && flashWhite)
		{
			flash->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			flashWhite->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoFlashReset = false;
		}
	}

	if (Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);

			NoSmoke = true;
		}
	}


	else if (!Settings::Misc::misc_NoSmoke)
	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			NoSmoke = false;

		}
	}


	if (Settings::Misc::misc_wireframesmoke)

	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);

			WireFrameSmoke = true;
		}
	}

	else if (!Settings::Misc::misc_wireframesmoke)

	{
		IMaterial* vistasmokev1_smokegrenade = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_smokegrenade", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_emods_impactdust = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_emods_impactdust", TEXTURE_GROUP_CLIENT_EFFECTS);

		IMaterial* vistasmokev1_fire = Interfaces::MaterialSystem()->FindMaterial("particle/vistasmokev1/vistasmokev1_fire", TEXTURE_GROUP_CLIENT_EFFECTS);

		if (vistasmokev1_smokegrenade && vistasmokev1_emods && vistasmokev1_emods_impactdust && vistasmokev1_fire)
		{
			vistasmokev1_smokegrenade->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_emods->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_emods_impactdust->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
			vistasmokev1_fire->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);

			WireFrameSmoke = false;
		}
	}

}

void CMisc::OnPlaySound(const char* pszSoundName)
{
	if (Settings::Misc::misc_AutoAccept && !strcmp(pszSoundName, "!UI/competitive_accept_beep.wav"))
	{
		typedef void(*IsReadyCallBackFn)();

		IsReadyCallBackFn IsReadyCallBack = 0;

		if (!IsReadyCallBack)
		{
			IsReadyCallBack = (IsReadyCallBackFn)(
				CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 83 BE", 0));

#if ENABLE_DEBUG_FILE == 1
			CSX::Log::Add("::IsReadyCallBack = %X", IsReadyCallBack);
#endif
		}

		if (IsReadyCallBack)
		{
			IsReadyCallBack();
		}
	}
}

void CMisc::OnOverrideView(CViewSetup * pSetup)
{
	// if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot()) - screenshot shit
	if (Settings::Misc::misc_FovChanger)
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->GetIsScoped())
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		pSetup->fov = (float)Settings::Misc::misc_FovView;
	}
}

void CMisc::OnGetViewModelFOV(float& fov)
{
	// if (Settings::Misc::misc_FovChanger && !Interfaces::Engine()->IsTakingScreenshot()) - screenshot shit
	if (Settings::Misc::misc_FovChanger)
	{
		CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (!pPlayer)
			return;

		if (pPlayer->IsDead())
		{
			if (pPlayer->GetObserverMode() == ObserverMode_t::OBS_MODE_IN_EYE && pPlayer->GetObserverTarget())
				pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

			if (!pPlayer)
				return;
		}

		fov = (float)Settings::Misc::misc_FovModelView;
	}
}

vector<int> CMisc::GetObservervators(int playerId)
{
	vector<int> SpectatorList;

	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

	if (!pPlayer)
		return SpectatorList;

	if (pPlayer->IsDead())
	{
		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pPlayer->GetObserverTarget());

		if (!pObserverTarget)
			return SpectatorList;

		pPlayer = pObserverTarget;
	}

	for (int PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CBaseEntity* pCheckPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(PlayerIndex);

		if (!pCheckPlayer)
			continue;

		if (pCheckPlayer->IsDormant() || !pCheckPlayer->IsDead())
			continue;

		CBaseEntity* pObserverTarget = (CBaseEntity*)Interfaces::EntityList()->GetClientEntityFromHandle(pCheckPlayer->GetObserverTarget());

		if (!pObserverTarget)
			continue;

		if (pPlayer != pObserverTarget)
			continue;

		SpectatorList.push_back(PlayerIndex);
	}

	return SpectatorList;
}

// old speclist
/*
void CMisc::OnRenderSpectatorList()
{
	if (Settings::Misc::misc_Spectators)
	{
		int specs = 0;
		int modes = 0;
		std::string spect = "";
		std::string mode = "";
		int DrawIndex = 1;
		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;
			CBaseEntity * pPlayer = (CBaseEntity *)Interfaces::EntityList()->GetClientEntity(playerId);
			if (!pPlayer)
				continue;
			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);
			if (Pinfo.m_bIsFakePlayer)
				continue;
			if (g_pRender)
			{
				spect += Pinfo.m_szPlayerName;
				spect += "\n";
				specs++;
				if (spect != "")
				{
					Color PlayerObsColor;
					// [junk_disable /] 
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						mode += ("Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						mode += ("3rd Person");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						mode += ("Free look");
						PlayerObsColor = Color::Red();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						mode += ("Deathcam");
						PlayerObsColor = Color::Yellow();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						mode += ("Freezecam");
						PlayerObsColor = Color::LimeGreen();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						mode += ("Fixed");
						PlayerObsColor = Color::Orange();
						break;
					default:
						break;
					}
					mode += "\n";
					modes++;
				}
			}
		}
		if (ImGui::Begin("Spectator List", &Settings::Misc::misc_Spectators, ImVec2(200, 100), 0.9f, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders))
		{
			if (specs> 0) spect += "\n";
			if (modes> 0) mode += "\n";
			ImVec2 size = ImGui::CalcTextSize(spect.c_str());
			ImGui::Columns(2);
			ImGui::Text("Name");
			ImGui::NextColumn();
			ImGui::Text("Mode");
			ImGui::NextColumn();
			ImGui::Separator();
			ImGui::Text(spect.c_str());
			ImGui::NextColumn();
			ImGui::Text(mode.c_str());
			ImGui::Columns(1);
			DrawIndex++;
		}
		ImGui::End();
	}
}
*/

// new speclist
void CMisc::OnRenderSpectatorList()
{
	if (Settings::Misc::misc_Spectators)
	{
		int DrawIndex = 1;

		for (int playerId : GetObservervators(Interfaces::Engine()->GetLocalPlayer()))
		{
			if (playerId == Interfaces::Engine()->GetLocalPlayer())
				continue;

			CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(playerId);

			if (!pPlayer)
				continue;

			PlayerInfo Pinfo;
			Interfaces::Engine()->GetPlayerInfo(playerId, &Pinfo);

			if (Pinfo.m_bIsFakePlayer)
				continue;

			if (g_pRender)
			{
				string Name = Pinfo.m_szPlayerName;

				if (Name != "")
				{
					Color PlayerObsColor;
					//[junk_disable /]
					switch (pPlayer->GetObserverMode())
					{
					case ObserverMode_t::OBS_MODE_IN_EYE:
						Name.append(" - Perspective");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_CHASE:
						Name.append(" - 3rd person");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_ROAMING:
						Name.append(" - Free look");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_DEATHCAM:
						Name.append(" - Deathcam");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_FREEZECAM:
						Name.append(" - Freezecam");
						PlayerObsColor = Color::White();
						break;
					case ObserverMode_t::OBS_MODE_FIXED:
						Name.append(" - Fixed");
						PlayerObsColor = Color::White();
						break;
					default:
						break;
					}
					//[junk_enable /]
					g_pRender->Text(iScreenWidth - 300, 300 + (DrawIndex * 13), false, true, PlayerObsColor, "%s", Name.c_str());
					DrawIndex++;
				}
			}
		}
	}
}





































































































































































































































































































































































































































































































































































































































