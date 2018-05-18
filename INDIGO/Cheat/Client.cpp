#include "Client.h"
#include <ctime>
#include <Shlobj.h>
#include "../ConfigPop/cfgmsgpop.h"
#include <stdint.h>
#include "../ImGui/imgui.h"
#include "../Cheat/GrenadeHelper/CGrenadeAPI.h"
#include <chrono>


//[enc_string_enable /]
//[junk_enable /]




namespace Client
{
	//[swap_lines
	int	iScreenWidth = 0;
	int	iScreenHeight = 0;

	char* username = getenv("USERPROFILE");

	//string BaseDir = std::string(username) + "\\Documents\\riptide";
	string BaseDir = "C:\\Users\\Aaron\\Documents\\riptide";
	string LogFile = "";
	string GuiFile = "";
	string IniFile = "";

	vector<string> ConfigList;

	Vector2D	g_vCenterScreen = Vector2D(0.f, 0.f);

	CPlayers*	g_pPlayers = nullptr;
	CRender*	g_pRender = nullptr;
	CGui*		g_pGui = nullptr;
	CTriggerbot* g_pTriggerbot = nullptr;
	CAimbot*	g_pAimbot = nullptr;
	CEsp*		g_pEsp = nullptr;
	CRadar*		g_pRadar = nullptr;
	CKnifebot*	g_pKnifebot = nullptr;
	CSkin*		g_pSkin = nullptr;
	CMisc*		g_pMisc = nullptr;

	CInventoryChanger* g_pInventoryChanger = nullptr;
	CInventoryChanger1* g_pInventoryChanger1 = nullptr;

	bool		bC4Timer = false;
	int			iC4Timer = 40;

	int			iWeaponID = 0;
	int			iWeaponSelectIndex = WEAPON_DEAGLE;
	int			iWeaponSelectSkinIndex = -1;

	float watermarkRainbowSpeed = 0.005f;
	float watermarkScrollSpeed = 2.5f;
	//[/swap_lines]

	void ReadConfigs(LPCTSTR lpszFileName)
	{
		if (!strstr(lpszFileName, "gui.ini"))
		{
			ConfigList.push_back(lpszFileName);
		}
	}

	void RefreshConfigs()
	{
		CHAR my_documents[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
		{
			ConfigList.clear();
			string ConfigDir = string(my_documents) + "\\riptide\\" "\\*.ini";
			SearchFiles(ConfigDir.c_str(), ReadConfigs, FALSE);
		}
	}

	bool Initialize(IDirect3DDevice9* pDevice)
	{
		// CONSOLE ON OPEN - uncomment if you want it
		
		Interfaces::Engine()->ClientCmd_Unrestricted2("clear");
		Interfaces::Engine()->ClientCmd_Unrestricted2("toggleconsole");
		Sleep(1000);
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo [RIPTIDE] SYSTEMS INITIALIZED");
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo -----------------------------");
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo [RIPTIDE]: JOIN OUR DISCORD AT discord.gg/X9eAUHD");
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo");
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo [RIPTIDE]: USE THE INSERT KEY TO OPEN THE MENU");
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo");
		Interfaces::Engine()->ClientCmd_Unrestricted2("echo [RIPTIDE]: GET WELL SOON RFK!");


		


		g_pPlayers = new CPlayers();
		g_pRender = new CRender(pDevice);
		g_pGui = new CGui();
		g_pTriggerbot = new CTriggerbot();
		g_pAimbot = new CAimbot();
		g_pEsp = new CEsp();
		g_pRadar = new CRadar();
		g_pKnifebot = new CKnifebot();
		g_pSkin = new CSkin();
		g_pMisc = new CMisc();

		g_pInventoryChanger = new CInventoryChanger();

		CHAR my_documents[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
		{
			GuiFile = (string(my_documents) + "\\riptide\\" + "gui.ini");
			IniFile = (string(my_documents) + "\\riptide\\" + "settings.ini");
		}

		g_pSkin->InitalizeSkins();

		Settings::LoadSettings(IniFile);

		iWeaponSelectSkinIndex = GetWeaponSkinIndexFromPaintKit(g_SkinChangerCfg[iWeaponSelectIndex].nFallbackPaintKit);

		g_pGui->GUI_Init(pDevice);

		RefreshConfigs();

		return true;
	}

	void Shutdown()
	{
		DELETE_MOD(g_pPlayers);
		DELETE_MOD(g_pRender);
		DELETE_MOD(g_pGui);
		DELETE_MOD(g_pTriggerbot);
		DELETE_MOD(g_pAimbot);
		DELETE_MOD(g_pEsp);
		DELETE_MOD(g_pRadar);
		DELETE_MOD(g_pKnifebot);
		DELETE_MOD(g_pSkin);
		DELETE_MOD(g_pMisc);
	}

	int get_fps()
	{
		using namespace std::chrono;
		static int count = 0;
		static auto last = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		static int fps = 0;

		count++;

		if (duration_cast<milliseconds>(now - last).count() > 1000)
		{
			fps = count;
			count = 0;
			last = now;
		}
		return fps;
	}


	void OnRender()
	{

		

		// if (g_pRender && !Interfaces::Engine()->IsTakingScreenshot() && Interfaces::Engine()->IsActiveApp()) - screenshot shit
		if (g_pRender && Interfaces::Engine()->IsActiveApp())
		{
			g_pRender->BeginRender();

			if (g_pGui)
				g_pGui->GUI_Draw_Elements();

			Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			g_vCenterScreen.x = iScreenWidth / 2.f;
			g_vCenterScreen.y = iScreenHeight / 2.f;

			if (Settings::Esp::esp_legitAAWarnings)
			{
				static bool left;
				if (GetAsyncKeyState(VK_RIGHT))
					left = true;
				else if (GetAsyncKeyState(0x44))
					left = true;

				else if (GetAsyncKeyState(VK_LEFT))
					left = false;
				else if (GetAsyncKeyState(0x41))
					left = false;

				if (left)
					g_pRender->Text(15, 650, false, true, Color::SkyBlue(), LEGITAALEFT);
				else if (!left)
					g_pRender->Text(15, 650, false, true, Color::SkyBlue(), LEGITAARIGHT);
			}



			if (Settings::Esp::esp_Watermark)
			{
				//bool rainbow; 
				static float rainbow;
				rainbow += watermarkRainbowSpeed;
				if (rainbow > 1.f) rainbow = 0.f;
				static int u = 0;
				if (u <= 100)                g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "<>riptide");
				if (u > 100 && u <= 200)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "e<>riptid");
				if (u > 200 && u <= 300)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "de<>ripti");
				if (u > 300 && u <= 400)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ide<>ript");
				if (u > 400 && u <= 500)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "tide<>rip");
				if (u > 500 && u <= 600)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ptide<>ri");
				if (u > 600 && u <= 700)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "iptide<>r");
				if (u > 700 && u <= 800)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "riptide<>");
				if (u > 800 && u <= 900)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), ">riptide<");
				if (u > 900 && u <= 1000)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "<>riptide");
				if (u > 1000 && u <= 1100)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "e<>riptid");
				if (u > 1100 && u <= 1200)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "de<>ripti");
				if (u > 1200 && u <= 1300)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ide<>ript");
				if (u > 1300 && u <= 1400)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "tide<>rip");
				if (u > 1400 && u <= 1500)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ptide<>ri");
				if (u > 1500 && u <= 1600)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "iptide<>r");
				if (u > 1600 && u <= 1700)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "riptide<>");
				if (u > 1700 && u <= 1800)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), ">riptide<");
				// if (u > 1600 && u <= 1700)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "riptide<>");
				// if (u > 1700 && u <= 1800)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "rip");
				// if (u > 1800 && u <= 1900)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "ri");
				// if (u > 1900 && u <= 2000)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "r");
				// if (u > 2000 && u <= 2100)    g_pRender->Text(15, 15, false, true, Color::FromHSB(rainbow, 1.f, 1.f), "");
				u += watermarkScrollSpeed;
				// if (u > 2100) u = 0;
				if (u > 1800) u = 0;
			}

			if (Settings::Esp::esp_Cheatbuild)
				g_pRender->Text(15, 45, false, true, Color::White(), "latest build: %s : %s", __DATE__, __TIME__);

			if (Settings::Misc::misc_RainbowMenu)
			{
				g_pGui->MenuColor();
			}

			{
				if (g_pEsp)
					g_pEsp->OnRender();

				if (g_pMisc)
				{
					g_pMisc->OnRender();
					g_pMisc->OnRenderSpectatorList();
				}
			}

			std::time_t result = std::time(nullptr);

			if (Settings::Esp::esp_Time)
				g_pRender->Text(15, 30, false, true, Color::White(), std::asctime(std::localtime(&result)));

			g_pRender->EndRender();
		}
	}

	void OnLostDevice()
	{
		if (g_pRender)
			g_pRender->OnLostDevice();

		if (g_pGui)
			ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	void OnResetDevice()
	{
		if (g_pRender)
			g_pRender->OnResetDevice();

		if (g_pGui)
			ImGui_ImplDX9_CreateDeviceObjects();
	}

	void OnRetrieveMessage(void* ecx, void* edx, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize)
	{
		g_pInventoryChanger->PostRetrieveMessage(punMsgType, pubDest, cubDest, pcubMsgSize);
	}

	void OnSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
	{

		void* pubDataMutable = const_cast<void*>(pubData);
		g_pInventoryChanger->PreSendMessage(unMsgType, pubDataMutable, cubData);
	}

	void OnCreateMove(CUserCmd* pCmd)
	{
		if (g_pPlayers && Interfaces::Engine()->IsInGame())
		{
			g_pPlayers->Update();

			if (g_pEsp)
				g_pEsp->OnCreateMove(pCmd);

			if (IsLocalAlive())
			{
				if (!bIsGuiVisible)
				{
					int iWeaponSettingsSelectID = GetWeaponSettingsSelectID();

					if (iWeaponSettingsSelectID >= 0)
						iWeaponID = iWeaponSettingsSelectID;
				}

				if (g_pAimbot)
					g_pAimbot->OnCreateMove(pCmd, g_pPlayers->GetLocal());

				if (g_pTriggerbot)
					g_pTriggerbot->OnCreateMove(pCmd, g_pPlayers->GetLocal());

				if (g_pKnifebot)
					g_pKnifebot->OnCreateMove(pCmd);

				if (g_pMisc)
					g_pMisc->OnCreateMove(pCmd);

				backtracking->legitBackTrack(pCmd);

			}
		}
	}

	void OnFireEventClientSideThink(IGameEvent* pEvent)
	{
		if (!strcmp(pEvent->GetName(), "player_connect_full") ||
			!strcmp(pEvent->GetName(), "round_start") ||
			!strcmp(pEvent->GetName(), "cs_game_disconnected"))
		{
			if (g_pPlayers)
				g_pPlayers->Clear();

			if (g_pEsp)
				g_pEsp->OnReset();
		}


		if (Interfaces::Engine()->IsConnected())
		{
			hitmarker::singleton()->initialize();

			if (g_pEsp)
				g_pEsp->OnEvents(pEvent);

			if (g_pSkin)
				g_pSkin->OnEvents(pEvent);
		}
	}

	void OnFrameStageNotify(ClientFrameStage_t Stage)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{

			ConVar* sv_cheats = Interfaces::GetConVar()->FindVar("sv_cheats");
			SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
			sv_cheats_spoofed->SetInt(1);


			if (g_pMisc)
				g_pMisc->FrameStageNotify(Stage);

			Skin_OnFrameStageNotify(Stage);
			Gloves_OnFrameStageNotify(Stage);
		}
	}

	void OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
	{
		if (Interfaces::Engine()->IsInGame() && ctx && pCustomBoneToWorld)
		{
			if (g_pEsp)
				g_pEsp->OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			if (g_pMisc)
				g_pMisc->OnDrawModelExecute();
		}
	}

	void OnPlaySound(const Vector* pOrigin, const char* pszSoundName)
	{
		if (!pszSoundName || !Interfaces::Engine()->IsInGame())
			return;

		if (!strstr(pszSoundName, "bulletLtoR") &&
			!strstr(pszSoundName, "rics/ric") &&
			!strstr(pszSoundName, "impact_bullet"))
		{
			if (g_pEsp && IsLocalAlive() && Settings::Esp::esp_Sound && pOrigin)
			{
				if (!GetVisibleOrigin(*pOrigin))
					g_pEsp->SoundEsp.AddSound(*pOrigin);
			}
		}
	}

	void OnPlaySound(const char* pszSoundName)
	{
		if (g_pMisc)
			g_pMisc->OnPlaySound(pszSoundName);
	}

	void OnOverrideView(CViewSetup* pSetup)
	{
		if (g_pMisc)
			g_pMisc->OnOverrideView(pSetup);
	}

	void OnGetViewModelFOV(float& fov)
	{
		if (g_pMisc)
			g_pMisc->OnGetViewModelFOV(fov);
	}

	BOOL DirectoryExists(LPCTSTR szPath)
	{
		DWORD dwAttrib = GetFileAttributes(szPath);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}


	void ImDrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
	{
		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

		Color colColor(0, 0, 0, 255);

		flRainbow += flSpeed;
		if (flRainbow > 1.f) flRainbow = 0.f;//1 0 

		for (int i = 0; i < width; i = i + 1)
		{
			float hue = (1.f / (float)width) * i;
			hue -= flRainbow;
			if (hue < 0.f) hue += 1.f;

			Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
			windowDrawList->AddRectFilled(ImVec2(x + i, y), ImVec2(width, height), colRainbow.GetU32());
		}
	}

	void OnRenderGUI()
	{


		ImGui::SetNextWindowSize(ImVec2(840.f, 550.f));
		g_pGui->NameFont();
		if (ImGui::Begin("riptide", &bIsGuiVisible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
			g_pRender->DrawFillBox(0, 0, iScreenWidth, iScreenHeight, Color(0, 0, 0, 170));
		{





			static float flRainbow;
			// float flSpeed = 0.001f;
			static float flSpeed = 0.003;
			int curWidth = 3;
			ImVec2 curPos = ImGui::GetCursorPos();
			ImVec2 curWindowPos = ImGui::GetWindowPos();
			curPos.x += curWindowPos.x;
			curPos.y += curWindowPos.y;
			int size = 2;
			int y;
			Interfaces::Engine()->GetScreenSize(y, size);
			ImDrawRectRainbow(curPos.x - 10, curPos.y - 1, ImGui::GetWindowSize().x + size, curPos.y + -4, flSpeed, flRainbow);








			ImGui::BeginGroup();

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType > 1)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType = 1;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit > 1)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit = 1;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot > 5)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot = 5;

			enum DWRITE_READING_DIRECTION {
				DWRITE_READING_DIRECTION_LEFT_TO_RIGHT,
				DWRITE_READING_DIRECTION_RIGHT_TO_LEFT
			};


			ImGui::TextColored(ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f }, "Current FPS:%03d", get_fps());
			ImGui::Separator();
			g_pGui->IconFont();
			const char* tabNames[] = {
				"A" , "I" ,"B" , "G" , "C" };

			static int tabOrder[] = { 0 , 1 , 2 , 3 , 4 };
			static int tabSelected = 4;
			const bool tabChanged = ImGui::TabLabels(tabNames,
				sizeof(tabNames) / sizeof(tabNames[0]),
				tabSelected, tabOrder);

			ImGui::Columns();





			float SpaceLineTitleOne = 120.f;
			float SpaceLineTitleTwo = 230.f;
			float SpaceLineTitleThr = 460.f;
			float SpaceLineTitleFour = 460.f;


			float SpaceLineBoxOne = 135.f;
			float SpaceLineBoxTwo = 275.f;
			float SpaceLineBoxThr = 410.f;
			float SpaceLineBoxFour = 475.f;


			float SpaceLineOne = 120.f;
			float SpaceLineTwo = 240.f;
			float SpaceLineThr = 360.f;
			float SpaceLineFour = 440.f;

			ImGui::EndGroup();
			ImGui::SameLine();




			if (tabSelected == 0) // Aimbot
			{
				g_pGui->bluefont();

				static int otherpages = 0;

				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 509), true);
				{

					if (ImGui::Button("Aimbot", ImVec2(180.0f, 30.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine(SpaceLineTitleTwo);

					if (ImGui::Button("Trigger", ImVec2(180.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}

					if (otherpages == 0)
					{
						ImGui::BeginGroup();

						ImGui::PushItemWidth(500.f);

						ImGui::Combo("weapon", &iWeaponID, pWeaponData, IM_ARRAYSIZE(pWeaponData));
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Columns();
						
					
						ImGui::Checkbox("attack team", &Settings::Aimbot::aim_Deathmatch);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("useful in free for all community servers");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("auto wall", &Settings::Aimbot::aim_WallAttack);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("activates aimbot if player takes damage through penetrable walls");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("check smoke", &Settings::Aimbot::aim_CheckSmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("does not activate aimbot if smoke is between you and the enemy");

						ImGui::Checkbox("anti jump", &Settings::Aimbot::aim_AntiJump);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("disables aimbot if enemy and/or you are jumping");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("draw fov", &Settings::Aimbot::aim_DrawFov);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders radius of influence of aimbot");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("draw spot", &Settings::Aimbot::aim_DrawSpot);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders point of aimbot attack");

						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Checkbox("backtrack", &Settings::Aimbot::aim_Backtrack);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("stores previous locations of players in RAM and can tell server false hits");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("visualise ticks", &Settings::Aimbot::aim_DrawBacktrack);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders ticks with potential to be backtracked");
						ImGui::SliderInt("ticks", &Settings::Aimbot::aim_Backtracktickrate, 1, 12);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("number of ticks to store in memory (higher ticks might cause FPS drops on shitty computers)");

						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Checkbox("aimbot active", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Active);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("master switch");
						if (iWeaponID <= 9)
						{
							ImGui::SameLine();
							ImGui::Checkbox("autopistol", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("ability to use pistols like an automatic gun, hold down left mouse button");
						}
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("smoothing", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth, 1, 300);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("humanizes aimbot's travel to enemy");
						ImGui::SliderInt("fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov, 1, 300);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("area of influence of aimbot");
						ImGui::PopItemWidth();

						const char* AimFovType[] = { "dynamic" , "static" };
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("fov type", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType, AimFovType, IM_ARRAYSIZE(AimFovType));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("dynamic changes size of FOV depending on distance between you and enemy");
						ImGui::PopItemWidth();

						const char* BestHit[] = { "disable" , "enable" };
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("best hit", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit, BestHit, IM_ARRAYSIZE(BestHit));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("looks more legit, rather than forcing hitting aimspot every time");

						ImGui::PopItemWidth();

						const char* Aimspot[] = { "head" , "neck" , "low neck" , "body" , "thorax" , "chest" };
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("aimspot", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot, Aimspot, IM_ARRAYSIZE(Aimspot));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("if besthit is disabled, this forces one location for the aimbot to travel to");
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("recoil control system");
						ImGui::Spacing();

						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("shot delay", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Delay, 0, 200);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("amount of time before automated rcs kicks in");
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Spacing();


						if (iWeaponID >= 10 && iWeaponID <= 30)
						{
							ImGui::PushItemWidth(362.f);
							ImGui::SliderInt("Rcs", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcs, 0, 100);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("amount of rcs");
							ImGui::SliderInt("rcs fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov, 1, 300);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("area of influence of automated recoil control");
							ImGui::SliderInt("rcs smooth", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth, 1, 300);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("humanization of automated recoil");
							ImGui::PopItemWidth();

							const char* ClampType[] = { "all targets" , "shot" , "shot + target" };
							ImGui::PushItemWidth(362.f);
							ImGui::Combo("rcs clamp", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType, ClampType, IM_ARRAYSIZE(ClampType));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("methods of target selection for rcs");
							ImGui::PopItemWidth();
						}


						ImGui::EndGroup();
					}
					if (otherpages == 1)
					{
						ImGui::BeginGroup();


						const char* TriggerEnable[] = { "Disable" , "Fov" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("Enable", &Settings::Triggerbot::trigger_Enable, TriggerEnable, IM_ARRAYSIZE(TriggerEnable));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("Deathmatch", &Settings::Triggerbot::trigger_Deathmatch);
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("WallAttack", &Settings::Triggerbot::trigger_WallAttack);
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("FastZoom", &Settings::Triggerbot::trigger_FastZoom);

						ImGui::Checkbox("SmokCheck", &Settings::Triggerbot::trigger_SmokCheck);
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("DrawFov", &Settings::Triggerbot::trigger_DrawFov);
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("DrawSpot", &Settings::Triggerbot::trigger_DrawSpot);
						ImGui::SameLine(SpaceLineThr);
						ImGui::Checkbox("DrawFovAssist", &Settings::Triggerbot::trigger_DrawFovAssist);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						const char* items1[] = { CVAR_KEY_MOUSE3 , CVAR_KEY_MOUSE4 , CVAR_KEY_MOUSE5 };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("Key", &Settings::Triggerbot::trigger_Key, items1, IM_ARRAYSIZE(items1));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						const char* items2[] = { "Hold" , "Press" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("Key Mode", &Settings::Triggerbot::trigger_KeyMode, items2, IM_ARRAYSIZE(items2));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						ImGui::PushItemWidth(110.f);
						ImGui::Combo("Weapon", &iWeaponID, pWeaponData, IM_ARRAYSIZE(pWeaponData));
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("Min Disstance", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DistanceMin, 0, 5000);
						ImGui::SliderInt("Max Disstance", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DistanceMax, 0, 5000);
						ImGui::SliderInt("Fov", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Fov, 1, 100);
						ImGui::SliderInt("Delay Before", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DelayBefore, 0, 200);
						ImGui::SliderInt("Delay After", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_DelayAfter, 0, 1000);
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("HeadOnly", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HeadOnly);
						ImGui::SameLine();

						const char* AssistMode[] = { "Disable" , "One Shot" , "Auto" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("Assist", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_Assist, AssistMode, IM_ARRAYSIZE(AssistMode));
						ImGui::PopItemWidth();
						ImGui::SameLine();


						const char* AssistFovType[] = { "Dynamic" , "Static" };
						ImGui::PushItemWidth(80.f);
						ImGui::Combo("Assist Fov Type", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFovType, AssistFovType, IM_ARRAYSIZE(AssistFovType));
						ImGui::PopItemWidth();

						const char* HitGroup[] = { "All" , "Head + Body" , "Head" };
						ImGui::Combo("HitGroup", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_HitGroup, HitGroup, IM_ARRAYSIZE(HitGroup));
						//ImGui::PopItemWidth();

						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("Assist Rcs", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistRcs, 0, 100);
						ImGui::SliderInt("Assist Fov", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistFov, 1, 300);
						ImGui::SliderInt("Assist Smooth", &Settings::Triggerbot::weapon_trigger_settings[iWeaponID].trigger_AssistSmooth, 1, 300);
						ImGui::PopItemWidth();




						ImGui::EndGroup();
					}
					ImGui::EndChild();
					ImGui::EndGroup();







				}
			}
			else if (tabSelected == 1) // Visuals
			{

				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 509), true);
				{
					const char* iHitSound[] =
					{
						"off",
						"default",
						"metallic",
						"roblox",
						"windows xp",
					};

					const char* material_items[] =
					{
						"glass",
						"crystal",
						"dark gold",
						"dark chrome",
						"plastic glass",
						"velvet",
						"crystal blue",
						"bright gold"
					};

					const char* armtype_items[] =
					{
						"arms only",
						"arms and weapon"
					};

					const char* skybox_items[] =
					{
						"cs_baggage_skybox_",
						"cs_tibet",
						"embassy",
						"italy",
						"jungle",
						"nukeblank",
						"office",
						"sky_cs15_daylight01_hdr",
						"sky_cs15_daylight02_hdr",
						"sky_cs15_daylight03_hdr",
						"sky_cs15_daylight04_hdr",
						"sky_csgo_cloudy01",
						"sky_csgo_night02",
						"sky_csgo_night02b",
						"sky_csgo_night_flat",
						"sky_day02_05_hdr",
						"sky_day02_05",
						"sky_dust",
						"sky_l4d_rural02_ldr",
						"sky_venice",
						"vertigo_hdr",
						"vertigoblue_hdr",
						"vertigo",
						"vietnam",
						"amethyst",
						"bartuc_canyon",
						"bartuc_grey_sky",
						"blue1",
						"blue2",
						"blue3",
						"blue5",
						"blue6",
						"cssdefault",
						"dark1",
						"dark2",
						"dark3",
						"dark4",
						"dark5",
						"extreme_glaciation",
						"green1",
						"green2",
						"green3",
						"green4",
						"green5",
						"greenscreen",
						"greysky",
						"night1",
						"night2",
						"night3",
						"night4",
						"night5",
						"orange1",
						"orange2",
						"orange3",
						"orange4",
						"orange5",
						"orange6",
						"persistent_fog",
						"pink1",
						"pink2",
						"pink3",
						"pink4",
						"pink5",
						"polluted_atm",
						"toxic_atm",
						"water_sunset﻿"
					};

					string style_1 = "box";
					string style_2 = "corners only";

					const char* items1[] = { style_1.c_str() , style_2.c_str() };

					static int otherpages = 0;



					if (ImGui::Button("esp", ImVec2(180.0f, 30.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine(SpaceLineTitleTwo);

					if (ImGui::Button("misc. visuals", ImVec2(180.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine(SpaceLineTitleThr);
					if (ImGui::Button("radar", ImVec2(180.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 2;
					}



					if (otherpages == 0)
					{
						static int otherpages = 0;



						if (ImGui::Button("visuals", ImVec2(87.0f, 25.0f))) // <---- customize these to your liking.
						{
							otherpages = 0;
						}
						ImGui::SameLine();
						if (ImGui::Button("options", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
						{
							otherpages = 1;
						}

						ImGui::Separator();

						if (otherpages == 0)
						{



							ImGui::PushItemWidth(339.f);
							ImGui::Combo("box type", &Settings::Esp::esp_Style, items1, IM_ARRAYSIZE(items1));
							ImGui::PopItemWidth();


							ImGui::Spacing();

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(150.f); //item width
							ImGui::BeginChild("first child", ImVec2(135, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("team esp", &Settings::Esp::esp_Team);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("render teammates");
								ImGui::Checkbox("enemy esp", &Settings::Esp::esp_Enemy);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("render enemies");
								ImGui::Checkbox("skeleton", &Settings::Esp::esp_Skeleton);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("innacurate and buggy rendering of bones of enemies");
								ImGui::Checkbox("outline", &Settings::Esp::esp_Outline);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws black outline over box");

							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::SameLine(SpaceLineBoxOne);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("second child", ImVec2(200, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("name esp", &Settings::Esp::esp_Name);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders name of players");
								ImGui::Checkbox("bomb esp", &Settings::Esp::esp_Bomb);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders position of bomb on players and when planted");
								ImGui::Checkbox("weapon esp", &Settings::Esp::esp_Weapon);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text of current weapon held by enemies");
								ImGui::Checkbox("defusing esp", &Settings::Esp::esp_Defusing);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("allows you to see if the enemy is defusing the bomb");
								ImGui::Checkbox("ammo esp", &Settings::Esp::esp_Ammo);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text of amount of ammunition enemy has");

							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group


							ImGui::SameLine(SpaceLineBoxTwo);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("third child", ImVec2(145, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("reveal ranks", &Settings::Esp::esp_Rank);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("in scoreboard");
								ImGui::Checkbox("sound esp", &Settings::Esp::esp_Sound);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws each hearable footstep");
								ImGui::Checkbox("line esp", &Settings::Esp::esp_Line);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws line to enemy");
								ImGui::Checkbox("distance esp", &Settings::Esp::esp_Distance);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text for distance between you and enemy");
							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::SameLine(SpaceLineBoxThr);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("fourth child", ImVec2(1200, 111), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("last build", &Settings::Esp::esp_Cheatbuild);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders time of last compilation in top left of screen");
								ImGui::Checkbox("watermark", &Settings::Esp::esp_Watermark);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders animated riptide rainbow text in top left of screen");
								ImGui::Checkbox("time", &Settings::Esp::esp_Time);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders current time in top left of screen");
								
							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::Spacing();

							ImGui::Checkbox("capslock boxtoggle", &Settings::Esp::esp_CapitalToggle);
							ImGui::SameLine(SpaceLineTwo);
							ImGui::Checkbox("fish esp", &Settings::Esp::esp_Fish);
							ImGui::SameLine(SpaceLineFour);
							ImGui::Checkbox("chicken esp", &Settings::Esp::esp_Chicken);

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							static bool sh_save_cfg = false;

							if (ImGui::Checkbox("grenade helper", &Settings::Esp::helper))
								sh_save_cfg = true;
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("buy a smoke, hold it in your hand, walk on a red circle, bottom left screen is info, throw as instructed at the green point.");

							ImGui::SameLine();
							if (ImGui::Button("update map"))
								cGrenade.bUpdateGrenadeInfo(Interfaces::Engine()->GetLevelNameShort());
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("does not work on all maps");

							ImGui::Checkbox("grenade trajectory", &Settings::Misc::misc_GrenadeTrajectory);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN, buggy");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::Checkbox("dropped weapon esp", &Settings::Esp::esp_WorldWeapons);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders text of dropped weapons on them");
							ImGui::Checkbox("thrown grenades esp", &Settings::Esp::esp_WorldGrenade);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders text of type of grenade being thrown by enemies and teammates");
							ImGui::Checkbox("grenade boxes", &Settings::Esp::esp_BoxNade);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders 3D box around grenades regardless of type");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Checkbox("Asus Walls", &Settings::Esp::esp_AsusWalls);
							ImGui::SliderInt("Walls Opacity", &Settings::Esp::esp_WallsOpacity, 0, 100);

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::ColorEdit3("ambient light", Settings::Esp::esp_Ambient);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::Checkbox("night mode", &Settings::Esp::esp_NightMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::SameLine(SpaceLineOne);
							ImGui::Checkbox("chrome", &Settings::Esp::esp_ChromeWorld);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::SameLine(SpaceLineTwo);
							ImGui::Checkbox("minecraft", &Settings::Esp::esp_MinecraftMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::SameLine(SpaceLineThr);
							ImGui::Checkbox("lsd", &Settings::Esp::esp_LSDMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN");
							ImGui::Checkbox("fullbright", &Settings::Misc::misc_FullBright);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN, looks best on mirage");
							ImGui::Spacing();




						}

						if (otherpages == 1)
						{

							string visible_1 = "enemy";
							string visible_2 = "team";
							string visible_3 = "all";
							string visible_4 = "only visible";

							string hpbar_1 = "none";
							string hpbar_2 = "number";
							string hpbar_3 = "bottom";
							string hpbar_4 = "left";
							string hpbar_5 = "partition";

							string arbar_1 = "none";
							string arbar_2 = "number";
							string arbar_3 = "bottom";
							string arbar_4 = "right";

							string chams_1 = "None";
							string chams_2 = "flat";
							string chams_3 = "texture";

							const char* items2[] = { visible_1.c_str() , visible_2.c_str() , visible_3.c_str() , visible_4.c_str() };

							ImGui::PushItemWidth(339.f);
							ImGui::Combo("esp visible", &Settings::Esp::esp_Visible, items2, IM_ARRAYSIZE(items2));

							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Text("rendering");
							ImGui::Spacing();
							const char* items3[] = { hpbar_1.c_str() , hpbar_2.c_str() , hpbar_3.c_str() , hpbar_4.c_str() , hpbar_5.c_str() };
							ImGui::Combo("esp health", &Settings::Esp::esp_Health, items3, IM_ARRAYSIZE(items3));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders health of players");

							const char* items4[] = { arbar_1.c_str() , arbar_2.c_str() , arbar_3.c_str() , arbar_4.c_str() };
							ImGui::Combo("esp armor", &Settings::Esp::esp_Armor, items4, IM_ARRAYSIZE(items4));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders armor of players");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::Text("chams options");
							ImGui::Spacing();
							const char* items5[] = { chams_1.c_str() , chams_2.c_str() , chams_3.c_str() };
							ImGui::Combo("chams", &Settings::Esp::esp_Chams, items5, IM_ARRAYSIZE(items5));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("fills player models with colour");
							ImGui::Combo("chams visible", &Settings::Esp::esp_ChamsVisible, items2, IM_ARRAYSIZE(items2));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("selection of when to render coloured playermodels");

							ImGui::Spacing();
							ImGui::Spacing();

							ImGui::Checkbox("chams materials", &Settings::Misc::misc_ChamsMaterials);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("choose prebuilt material types");
							ImGui::PushItemWidth(362.f);
							ImGui::Combo("##CHAMSMATERIALS", &Settings::Misc::misc_ChamsMaterialsList, material_items, ARRAYSIZE(material_items));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("choose prebuilt material types");
							ImGui::Checkbox("health chams", &Settings::Esp::esp_HealthChams);
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Text("esp settings");
							ImGui::Spacing();
							ImGui::SliderInt("esp size", &Settings::Esp::esp_Size, 0, 10);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("size of each box");
							ImGui::SliderInt("bomb timer", &Settings::Esp::esp_BombTimer, 0, 65);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("useful for community servers(?) where bomb timer is different");
							ImGui::SliderInt("bullet tracers", &Settings::Esp::esp_BulletTrace, 0, 3000);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders direction of player viewangle with a line of a certain length");






						}
					}
					if (otherpages == 1)
					{






						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("skybox changer");
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs skybox to other map");
						ImGui::Spacing();
						if (ImGui::Combo("", &Settings::Misc::misc_CurrentSky, skybox_items, IM_ARRAYSIZE(skybox_items)))
						{
							Settings::Misc::misc_SkyName = skybox_items[Settings::Misc::misc_CurrentSky];
						}

						ImGui::Checkbox("snow world", &Settings::Misc::misc_Snow);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("no sky", &Settings::Misc::misc_NoSky);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("disable postprocessing", &Settings::Misc::misc_EPostprocess);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("wire smoke", &Settings::Misc::misc_wireframesmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, buggy while walking through smoke");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("no smoke", &Settings::Misc::misc_NoSmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, buggy while walking through smoke");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("no flash", &Settings::Misc::misc_NoFlash);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("disables rendering of flash blinding");

						ImGui::Checkbox("esp warnings", &Settings::Esp::bEspWarnings);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("displays a warning if someone is aiming at you");
						ImGui::SameLine(SpaceLineTwo);
						
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

					
						ImGui::Checkbox("bullet beams", &Settings::Esp::esp_beams_tracer);                              // Only for your own Bullets. You have to wait 15 Seconds after toggle it. Also its kind of buggy.
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, only renders for your own bullets");
						ImGui::SliderFloat("Duration", &Settings::Esp::flTracersDuration, 0.f, 10.f, "%.2f");
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("in seconds");
						ImGui::SliderFloat("Width", &Settings::Esp::flTracersWidth, 0.f, 10.f, "%.2f");
						ImGui::ColorEdit3("Beams Colour", Settings::Esp::flTracer_Beam);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("hitmarker", &Settings::Esp::esp_HitMarker);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("visual representation of landing a hit");
						ImGui::Combo("hitmarker sound", &Settings::Esp::esp_HitMarkerSound, iHitSound, ARRAYSIZE(iHitSound));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("audial representation of landing a hit");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("arm materials");
						ImGui::Spacing();
						ImGui::Checkbox("arm materials", &Settings::Misc::misc_ArmMaterials);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs arm/weapon materials to something else");
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("type", &Settings::Misc::misc_ArmMaterialsType, armtype_items, ARRAYSIZE(armtype_items));
						ImGui::PushItemWidth(362.f);
						ImGui::Combo("material", &Settings::Misc::misc_ArmMaterialsList, material_items, ARRAYSIZE(material_items));


					}


					if (otherpages == 2)
					{
						g_pGui->bluefont();
						;
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Text("radar");

						ImGui::Spacing();
						ImGui::Checkbox("active", &Settings::Radar::rad_Active);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("very bad external window radar");
						ImGui::SameLine();
						ImGui::Checkbox("team", &Settings::Radar::rad_Team);
						ImGui::SameLine();
						ImGui::Checkbox("enemy", &Settings::Radar::rad_Enemy);
						ImGui::SameLine();
						ImGui::Checkbox("sound", &Settings::Radar::rad_Sound);
						ImGui::SameLine();
						ImGui::Checkbox("engine", &Settings::Radar::rad_InGame);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("forces ingame radar to be like casual");

						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::PushItemWidth(339.f);
						ImGui::SliderInt("range", &Settings::Radar::rad_Range, 1, 5000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("for external window radar");
						ImGui::SliderInt("alpha", &Settings::Radar::rad_Alpha, 1, 255);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("for external window radar");






					}

					ImGui::EndChild();
					ImGui::EndGroup();
				}
			}
			else if (tabSelected == 2) // Skins
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 509), true);
				{

					ImGui::Spacing();



					ImGui::Text("serverside changers");
					ImGui::Spacing();
					ImGui::Checkbox("profile changer", &Settings::Misc::window_profilechanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("serversided - in lobby");



					ImGui::Checkbox("medal changer", &Settings::Misc::window_medalchanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("serversided - in lobby AND in game");

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Text("clientsided changers");
					ImGui::Spacing();

					ImGui::Checkbox("skin changer", &Settings::Misc::misc_SkinChanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");


					ImGui::Checkbox("knife changer", &Settings::Misc::misc_KnifeChanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");


					ImGui::Checkbox("sticker changer", &Settings::Misc::misc_StickerChanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");

					ImGui::Checkbox("inventory changer", &Settings::Misc::window_inventorychanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Text("filters");
					ImGui::Checkbox("skin ids", &Settings::Misc::skinids);
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("weapon ids", &Settings::Misc::weaponids);
					ImGui::SameLine(SpaceLineTwo);
					ImGui::Checkbox("medal ids", &Settings::Misc::medalids);
					ImGui::SameLine(SpaceLineThr);
					ImGui::Checkbox("sticker ids", &Settings::Misc::stickerids);
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::EndChild();
					ImGui::EndGroup();
				}
			}
			else if (tabSelected == 3) // Misc
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 509), true);
				{

					ImGui::BeginGroup();


					static int otherpages = 0;



					if (ImGui::Button("part 1", ImVec2(87.0f, 25.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("part 2", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine();
					if (ImGui::Button("knifebot", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 2;
					}

					ImGui::Separator();

					if (otherpages == 0)
					{
						ImGui::BeginGroup();

						ImGui::Spacing();

						ImGui::Checkbox("rainbow menu", &Settings::Misc::misc_RainbowMenu);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("does not work anymore on main window");
						ImGui::PushItemWidth(362.f);
						if (ImGui::InputFloat("fade speed", &Settings::Misc::misc_RainbowSpeed, 0.001f, 0.01f))
						{
							if (Settings::Misc::misc_RainbowSpeed < 0.001f)
								Settings::Misc::misc_RainbowSpeed = 0.001f;
							if (Settings::Misc::misc_RainbowSpeed > 0.01f)
								Settings::Misc::misc_RainbowSpeed = 0.01f;
						};

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("thirdperson", &Settings::Misc::misc_ThirdPerson);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy");
						ImGui::SliderFloat("##THIRDPERSONRANGE", &Settings::Misc::misc_ThirdPersonRange, 0.f, 100.f, "third person range: %0.f");


						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("bhop", &Settings::Misc::misc_Bhop);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("perfect bunny hop, lands 100% of the time");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("inventory always on", &Settings::Misc::invalwayson);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("allows you to access inventory in competitive match post-warmup");

						ImGui::Spacing();

						ImGui::Checkbox("punch", &Settings::Misc::misc_Punch);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("draws small green dot to show where recoil is");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("sniper crosshair", &Settings::Misc::misc_AwpAim);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("shows your ingame crosshair while holding a sniper");

						ImGui::Spacing();

						ImGui::Checkbox("static chat spam", &Settings::Misc::misc_spamregular);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("trashtalks chat");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("random chat spam", &Settings::Misc::misc_spamrandom);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("trashtalks chat creatively");

						ImGui::Spacing();

						ImGui::Checkbox("nohands", &Settings::Misc::misc_NoHands);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("stops rendering arms but still renders weapons");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("wirehands", &Settings::Misc::misc_WireHands);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("renders hands with a wireframe");
						ImGui::Spacing();

						ImGui::Checkbox("spectators", &Settings::Misc::misc_Spectators);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy, external window");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("autoaccept", &Settings::Misc::misc_AutoAccept);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy");
						ImGui::Spacing();

						ImGui::Separator();
						ImGui::Checkbox("legit aa", &Settings::Misc::misc_LegitAA);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("WARNING: CHANGES AIMBOT TO SILENT AIM");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("silent aim fix", &Settings::Misc::misc_LegitAAToggle);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("fixes changing aimbot to silent aim when legit aa is enabled");
						ImGui::SameLine(SpaceLineThr);
						ImGui::Checkbox("legit aa indicators", &Settings::Esp::esp_legitAAWarnings);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("text - current side of your real angle");

						ImGui::Separator();
						ImGui::Spacing();

						string clan_1 = "none";
						string clan_2 = "clear";
						string clan_3 = "no-name";
						string clan_4 = "riptide";
						string clan_5 = "riptide no name";
						string clan_6 = "valve";
						string clan_7 = "valve no-name";
						string clan_8 = "karmafreediet";
						string clan_9 = "riptide animated";
						const char* items5[] = { clan_1.c_str() , clan_2.c_str() , clan_3.c_str() , clan_4.c_str() , clan_5.c_str() , clan_6.c_str() , clan_7.c_str(), clan_8.c_str(), clan_9.c_str() };
						ImGui::Combo("clantag changer", &Settings::Misc::misc_Clan, items5, IM_ARRAYSIZE(items5));

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();


						ImGui::Checkbox("field of view changer", &Settings::Misc::misc_FovChanger);
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("viewposition", &Settings::Misc::misc_FovView, 1, 170);
						ImGui::SliderInt("viewmodel", &Settings::Misc::misc_FovModelView, 1, 190);

						ImGui::EndGroup();
					}
					if (otherpages == 1)
					{

						ImGui::BeginGroup();

						ImGui::Spacing();


						static char buf2[128] = { 0 };
						ImGui::Text("custom name");
						ImGui::InputText("##CustomName", buf2, 16, Settings::Misc::misc_NameChange);
						if (ImGui::Button("apply custom name")) {
							ConVar* Name = Interfaces::GetConVar()->FindVar("name");
							*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;
							Name->SetValue(buf2);
						}

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();



						static char misc_CustomClanTag[128] = { 0 };
						ImGui::Text("custom clantag");
						ImGui::InputText("##CustomClanTag", misc_CustomClanTag, 128);

						if (ImGui::Button("apply custom clantag"))
						{
							Engine::ClanTagApply(misc_CustomClanTag);
						}

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("gravity", &Settings::Misc::misc_ragdoll_gravity);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("changes gravity for corpse, buggy, SMAC BAN");
						ImGui::SliderInt("gravity amount", &Settings::Misc::misc_ragdoll_gravity_amount, -1000, 1000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("0 = no gravity / 1000 = high gravity / -1000 = negative gravity");

						ImGui::Checkbox("pushscale", &Settings::Misc::misc_pushscale);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs phys_pushscale, possibly untrusted, SMAC BAN");
						ImGui::SliderInt("pushscale amount", &Settings::Misc::misc_pushscale_amount, 0, 5000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("buggy");
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						if (ImGui::Button("ayyware crasher"))    //Crashes the Ayyware ESP. Most of ayyware user already fixed it.
						{

							ConVar* Name = Interfaces::GetConVar()->FindVar("name");
							*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;

							Name->SetValue("GETCRASHEDAYY?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????");
						}
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("changes your name to crash ayyware name esp/spectators list");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("fake ping", &Settings::Misc::misc_fakeping);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("extends backtrack");
						ImGui::Spacing();

						ImGui::Text("custom models");

						
						ImGui::Checkbox("enable custom models", &Settings::Misc::custommodelson);
						if (ImGui::IsItemHovered())
						ImGui::SetTooltip("CAUSES CRASH");
						const char* customModelsct[] =
						{
						"off",
						"trump",
						"noire",
						"anime",
						"joe"

						};

						const char* customModelst[] =
						{
						"off",
						"trump",
						"noire",
						"anime",
						"joe"

						};

						if (Settings::Misc::custommodelson) {
						ImGui::Combo(("ct model"), &Settings::Misc::customodelsct, customModelsct, ARRAYSIZE(customModelsct));
						ImGui::Combo(("t model"), &Settings::Misc::customodelst, customModelst, ARRAYSIZE(customModelst));
						}

						if (ImGui::Button("Update"))
						{
						ForceFullUpdate();
						}
						
					}

					if (otherpages == 2)
					{

						ImGui::BeginGroup();
						ImGui::Spacing();

						ImGui::Checkbox("active", &Settings::Knifebot::knf_Active);
						ImGui::Checkbox("attack team", &Settings::Knifebot::knf_Team);

						ImGui::Separator();

						string attack_1 = "attack 1";
						string attack_2 = "attack 2";
						string attack_3 = "both";

						const char* items[] = { attack_1.c_str() , attack_2.c_str() , attack_3.c_str() };
						ImGui::Combo("attack type", &Settings::Knifebot::knf_Attack, items, IM_ARRAYSIZE(items));

						ImGui::Separator();

						ImGui::SliderInt("distance to attack 1", &Settings::Knifebot::knf_DistAttack, 1, 100);
						ImGui::SliderInt("distance to attack 2", &Settings::Knifebot::knf_DistAttack2, 1, 100);

						ImGui::EndGroup();

					}
					ImGui::EndChild();
					ImGui::EndGroup();


				}

			}
			else if (tabSelected == 4)
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 509), true);
				{

					static int otherpages = 0;



					if (ImGui::Button("settings", ImVec2(87.0f, 25.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("colours", ImVec2(87.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}

					ImGui::Separator();


					if (otherpages == 0)
					{
						g_pGui->bluefont();

						ImGui::BeginGroup();
						static int iConfigSelect = 0;
						static int iMenuSheme = 1;
						static char ConfigName[64] = { 0 };
						static bool sh_save_cfg = false;
						static bool sh_load_cfg = false;

						ImGui::ComboBoxArray("select config", &iConfigSelect, ConfigList);


						CHAR my_documents[MAX_PATH];
						if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
						{

							if (ImGui::Button("load config"))
							{
								sh_load_cfg = true;
								Settings::LoadSettings(string(my_documents) + "\\riptide\\" + ConfigList[iConfigSelect]);
							}
							ImGui::SameLine();
							if (ImGui::Button("save config"))
							{
								Settings::SaveSettings(string(my_documents) + "\\riptide\\" + ConfigList[iConfigSelect]);
								sh_save_cfg = true;
							}
							ImGui::SameLine();
							if (ImGui::Button("refresh config list"))
							{
								RefreshConfigs();
							}
						}
						if (sh_save_cfg)
						{
							//save ur cfg
							bool done = false;
							Anime::Popup("config saved", 2000, &done);
							if (done)
								sh_save_cfg = false;
						}

						if (sh_load_cfg)
						{
							//load ur cfg
							bool done = false;
							Anime::Popup("loaded config", 2000, &done);
							if (done)
								sh_load_cfg = false;
						}





						ImGui::InputText("config name", ConfigName, 64);
						ImGui::Text("if you are making a new config, click 'create & save new config'.");
						ImGui::Text("configs save in documents, riptide");
						if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents)))
						{
							if (ImGui::Button("create & save new config"))
							{
								string ConfigFileName = ConfigName;

								if (ConfigFileName.size() < 1)
								{
									ConfigFileName = "settings";
								}
								string riptide = "\\riptide\\";
								string both = my_documents + riptide;

								if (!DirectoryExists(both.c_str())) // only create dir if doesnt already exist
									CreateDirectoryA(both.c_str(), NULL); //create riptdie dir



								Settings::SaveSettings(string(my_documents) + "\\riptide\\" + ConfigFileName + ".ini");
								RefreshConfigs();
							}
						}


						ImGui::Text(" ");


						const char* ThemesList[] = { "purple" , "white" , "light pink" , "narcisisti.cc" , "midnight" , "night" , "black/red" , "blue"  , "black" , "green" , "yellow" , "light blue" , "light grey" , "phook" };

						ImGui::Combo("menu theme", &iMenuSheme, ThemesList, IM_ARRAYSIZE(ThemesList));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("currently out of operation");


						if (ImGui::Button("apply color"))
						{
							if (iMenuSheme == 0)
							{
								g_pGui->purple();
							}
							else if (iMenuSheme == 1)
							{
								g_pGui->DefaultSheme1();
							}
							else if (iMenuSheme == 2)
							{
								g_pGui->RedSheme();
							}
							else if (iMenuSheme == 3)
							{
								g_pGui->darkblue();
							}
							else if (iMenuSheme == 4)
							{
								g_pGui->MidNightSheme();
							}
							else if (iMenuSheme == 5)
							{
								g_pGui->NightSheme();
							}
							else if (iMenuSheme == 6)
							{
								g_pGui->DunnoSheme();
							}
							else if (iMenuSheme == 7)
							{
								g_pGui->BlueSheme();
							}
							//else if (iMenuSheme == 10)
							//{
							//	g_pGui->MidNight2();
							//}
							else if (iMenuSheme == 8)
							{
								g_pGui->BlackSheme2();
							}
							else if (iMenuSheme == 9)
							{
								g_pGui->green();
							}
							else if (iMenuSheme == 10)
							{
								g_pGui->pink();
							}
							else if (iMenuSheme == 11)
							{
								g_pGui->blue();
							}
							else if (iMenuSheme == 12)
							{
								g_pGui->yellow();
							}
							else if (iMenuSheme == 13)
							{
								g_pGui->BlackSheme();
							}
						}
						ImGui::EndGroup();

					}
					if (otherpages == 1)
					{

						ImGui::BeginGroup();
						ImGui::Text("menu");
						if (ImGui::ColorEdit3("menu colour", Settings::Misc::misc_MenuColor))
							g_pGui->MenuColor();
						if (ImGui::ColorEdit3("menu text colour", Settings::Misc::misc_TextColor))
							g_pGui->MenuColor();
						ImGui::SliderFloat("rainbow bar speed", &flSpeed, 0.000f, 0.005f);
						ImGui::SliderFloat("watermark rainbow speed", &watermarkRainbowSpeed, 0.000f, 0.05f);
						ImGui::SliderFloat("watermark scroll speed", &watermarkScrollSpeed, 1.0f, 10.0f);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("esp");
						ImGui::ColorEdit3("hitmarker", Settings::Esp::esp_HitMarkerColor);
						ImGui::ColorEdit3("esp ct", Settings::Esp::esp_Color_CT);
						ImGui::ColorEdit3("esp tt", Settings::Esp::esp_Color_TT);
						ImGui::ColorEdit3("esp vis. ct", Settings::Esp::esp_Color_VCT);
						ImGui::ColorEdit3("esp vis. t", Settings::Esp::esp_Color_VTT);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("chams");
						ImGui::ColorEdit3("chams ct", Settings::Esp::chams_Color_CT);
						ImGui::ColorEdit3("chams tt", Settings::Esp::chams_Color_TT);
						ImGui::ColorEdit3("chams vis. ct", Settings::Esp::chams_Color_VCT);
						ImGui::ColorEdit3("chams vis. t", Settings::Esp::chams_Color_VTT);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("radar");
						ImGui::ColorEdit3("color ct", Settings::Radar::rad_Color_CT);
						ImGui::ColorEdit3("color tt", Settings::Radar::rad_Color_TT);
						ImGui::ColorEdit3("color vis. ct", Settings::Radar::rad_Color_VCT);
						ImGui::ColorEdit3("color vis. t", Settings::Radar::rad_Color_VTT);
					}


					ImGui::EndChild();
					ImGui::EndGroup();

				}

			}
			ImGui::EndGroup();
			ImGui::End();
		}


	}
}






































































































































































































































































































































































































































































































































































































































