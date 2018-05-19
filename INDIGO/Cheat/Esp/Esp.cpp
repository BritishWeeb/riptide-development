#include "Esp.h"

#include "../../Cheat/BulletBeams/beambullets.h"
#include "../../Cheat/BulletBeams/BeamsInclude.h"
#include "../../Cheat/GrenadeHelper/CGrenadeAPI.h"
std::vector<cbullet_tracer_info> logs;


using namespace Client;
//[enc_string_enable /]
//[junk_enable /]



enum
{
	PITCH = 0, // up / down
	YAW, // left / right
	ROLL // fall over
};

void inline SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void AngleVectors(const QAngle& angles, Vector* forward)
{
	float sp, sy, cp, cy;

	SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
	SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward->x = cp * cy;
	forward->y = cp * sy;
	forward->z = -sp;
}

int StringToWeapon(std::string weapon) {
	if (!strcmp(weapon.c_str(), "smokegrenade"))
		return 45;
	if (!strcmp(weapon.c_str(), "flashbang"))
		return 43;
	if (!strcmp(weapon.c_str(), "incgrenade"))
		return 46;
}


CSoundEsp::CSoundEsp()
{
	SoundColor = Color::White();
}

void CSoundEsp::Update()
{
	for (size_t i = 0; i < Sound.size(); i++)
	{
		if (Sound[i].dwTime + 800 <= GetTickCount64())
		{
			Sound.erase(Sound.begin() + i);
		}
	}
}

SDK::PlayerInfo GetInfo(int Index)
{
	SDK::PlayerInfo info;
	Interfaces::Engine()->GetPlayerInfo(Index, &info);
	return info;
}

typedef void(__cdecl* MsgFn)(const char* msg, va_list);
void Msg(const char* msg, ...)
{

	if (msg == nullptr)
		return;
	static MsgFn fn = (MsgFn)GetProcAddress(GetModuleHandle("tier0.dll"), "Msg");
	char buffer[989];
	va_list list;
	va_start(list, msg);

	vsprintf(buffer, msg, list);
	va_end(list);

	fn(buffer, list);
}

char* HitgroupToName(int hitgroup)
{
	switch (hitgroup)
	{
	case HITGROUP_HEAD:
		return "head";
	case HITGROUP_LEFTLEG:
		return "leg";
	case HITGROUP_RIGHTLEG:
		return "leg";
	case HITGROUP_LEFTARM:
		return "arm";
	case HITGROUP_RIGHTARM:
		return "arm";
	case HITGROUP_STOMACH:
		return "chest";
	default:
		return "chest";
	}
}


void CSoundEsp::AddSound(Vector vOrigin)
{
	Sound_s Sound_Entry;

	Sound_Entry.dwTime = GetTickCount64();
	Sound_Entry.vOrigin = vOrigin;

	Sound.push_back(Sound_Entry);
}

void CSoundEsp::DrawSoundEsp()
{
	for (size_t i = 0; i < Sound.size(); i++)
	{
		Vector vScreen;

		if (WorldToScreen(Sound[i].vOrigin, vScreen))
		{
			if (Settings::Esp::esp_Sound)
				g_pRender->DrawBox((int)vScreen.x, (int)vScreen.y, 10, 10, SoundColor);
		}
	}
}



CEsp::CEsp()
{
	// ����� �� ����

	CT_HP_ColorM.SetColor(255, 64, 64);
	TT_HP_ColorM.SetColor(255, 64, 64);

	// ����� ����� ����

	CT_AR_ColorM.SetColor(255, 64, 64);
	TT_AR_ColorM.SetColor(255, 64, 64);

	visible_flat = nullptr;
	visible_tex = nullptr;
	hidden_flat = nullptr;
	hidden_tex = nullptr;

	fExplodeC4Timer = 0.f;
	fC4Timer = 0.f;
}

Color CEsp::GetPlayerColor(CPlayer* pPlayer)
{
	Color CT_Color(int(Settings::Esp::esp_Color_CT[0] * 255.f), int(Settings::Esp::esp_Color_CT[1] * 255.f), int(Settings::Esp::esp_Color_CT[2] * 255.f));
	Color TT_Color(int(Settings::Esp::esp_Color_TT[0] * 255.f), int(Settings::Esp::esp_Color_TT[1] * 255.f), int(Settings::Esp::esp_Color_TT[2] * 255.f));

	if (pPlayer->Team == TEAM_CT)
	{
		return CT_Color;
	}
	else if (pPlayer->Team == TEAM_TT)
	{
		return TT_Color;
	}

	return Color::White();
}

Color CEsp::GetPlayerVisibleColor(CPlayer* pPlayer)
{
	Color PlayerColor = GetPlayerColor(pPlayer);

	bool SetColor = false;

	// ������������ ������ ���� ����� �����:

	if (pPlayer->bVisible)
	{
		if (Settings::Esp::esp_Visible == 0 && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
		{
			SetColor = true;
		}
		else if (Settings::Esp::esp_Visible == 1 && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
		{
			SetColor = true;
		}
		else if (Settings::Esp::esp_Visible == 2) // ����
		{
			SetColor = true;
		}

		Color VCT_Color(int(Settings::Esp::esp_Color_VCT[0] * 255.f), int(Settings::Esp::esp_Color_VCT[1] * 255.f), int(Settings::Esp::esp_Color_VCT[2] * 255.f));
		Color VTT_Color(int(Settings::Esp::esp_Color_VTT[0] * 255.f), int(Settings::Esp::esp_Color_VTT[1] * 255.f), int(Settings::Esp::esp_Color_VTT[2] * 255.f));

		if (SetColor)
		{
			if (pPlayer->Team == TEAM_CT)
			{
				PlayerColor = VCT_Color;
			}
			else if (pPlayer->Team == TEAM_TT)
			{
				PlayerColor = VTT_Color;
			}
		}
	}

	return PlayerColor;
}

bool CEsp::CheckPlayerTeam(CPlayer* pPlayer)
{
	bool CheckTeam = false;
	bool PlayerVisible = pPlayer->bVisible;

	// ���������� esp ������ ��:
	if (Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
		CheckTeam = true;

	if (Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
		CheckTeam = true;

	if (Settings::Esp::esp_Visible >= 3 && !PlayerVisible)
		CheckTeam = false;

	return CheckTeam;
}

void CEsp::Ambient()
{
	float AmbientRedAmount = Settings::Esp::esp_Ambient[0];
	float AmbientGreenAmount = Settings::Esp::esp_Ambient[1];
	float AmbientBlueAmount = Settings::Esp::esp_Ambient[2];

	ConVar* AmbientRedCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_r");
	*(float*)((DWORD)&AmbientRedCvar->fnChangeCallback + 0xC) = NULL;
	AmbientRedCvar->SetValue(AmbientRedAmount);

	ConVar* AmbientGreenCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_g");
	*(float*)((DWORD)&AmbientGreenCvar->fnChangeCallback + 0xC) = NULL;
	AmbientGreenCvar->SetValue(AmbientGreenAmount);

	ConVar* AmbientBlueCvar = Interfaces::GetConVar()->FindVar("mat_ambient_light_b");
	*(float*)((DWORD)&AmbientBlueCvar->fnChangeCallback + 0xC) = NULL;
	AmbientBlueCvar->SetValue(AmbientBlueAmount);
}






void CEsp::AsusWalls()
{
	bool AsusDone = false;

	if (Settings::Esp::esp_AsusWalls)
	{
		if (!AsusDone)
		{
			static auto r_DrawSpecificStaticProp = Interfaces::GetConVar()->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);

			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				double XD = 100;
				double Opacity = int(Settings::Esp::esp_WallsOpacity);
				double RealOpacity = Opacity / XD;

				/*if (strstr(group, "StaticProp"))
				{
				pMaterial->AlphaModulate(RealOpacity);
				pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}*/
				if (strstr(group, "World textures"))
				{
					pMaterial->AlphaModulate(RealOpacity);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->AlphaModulate(RealOpacity);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				AsusDone = true;
			}

		}

	}
	else
	{
		if (AsusDone)
		{
			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->AlphaModulate(1);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->AlphaModulate(1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->AlphaModulate(1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}

			AsusDone = false;
		}
	}
}




void CEsp::Espwarning()
{

	if (Settings::Esp::bEspWarnings)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{
			std::stringstream text1 = std::stringstream("");
			std::stringstream text2 = std::stringstream("");
			CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			if (!pLocal)
				return;

			for (int i = 1; i <= Interfaces::Engine()->GetMaxClients(); i++)
			{

				CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

				if (pPlayer)
				{
					if (!pPlayer->IsValid())
						continue;
					if (pPlayer->GetTeam() == pLocal->GetTeam() && !Settings::Esp::esp_Team)
						continue;

					PlayerInfo info;
					if (!Interfaces::Engine()->GetPlayerInfo(i, &info))
						continue;

					Vector src, dst, forward;
					trace_t tr;
					Ray_t ray;
					CTraceFilter filter;
					AngleVectors(pPlayer->GetEyeAngles(), forward);
					filter.pSkip = pPlayer;
					src = pPlayer->GetBestEyePos(true);
					dst = src + (forward * 8192);
					ray.Init(src, dst);
					Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);
					bool AimingToLocal = (tr.m_pEnt && tr.hitgroup > 0 && tr.hitgroup <= 7);
					bool CanSeeLocal = pPlayer->IsVisible(pLocal);

					if (AimingToLocal)
					{
						text2 << info.m_szPlayerName << " ";
					}
					if (CanSeeLocal)
					{
						text1 << info.m_szPlayerName << " ";
					}
				}
			}


			text2 << "is aiming at you";
			text1 << "can see You";
			int screensizeX, screensizeY;
			Interfaces::Engine()->GetScreenSize(screensizeX, screensizeY);
			g_pRender->Text(screensizeX / 2, 100, true, true, Color::Red(), text2.str().c_str());
			g_pRender->Text(screensizeX / 2, 120, true, true, Color::Green(), text1.str().c_str());

		}

	}

}



void CEsp::HitmarkerEvents(IGameEvent* event)
{

	if (!strcmp(event->GetName(), "bullet_impact"))
	{
		CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

		if (LocalPlayer)
		{
			auto index = Interfaces::Engine()->GetPlayerForUserID(event->GetInt("userid"));

			if (index != Interfaces::Engine()->GetLocalPlayer())
				return;

			auto local = static_cast<CBaseEntity*>(Interfaces::EntityList()->GetClientEntity(index));

			Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));

			Ray_t ray;

			ray.Init(local->GetEyePosition(), position);

			CTraceFilter filter;

			filter.pSkip = local;

			trace_t tr;
			Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

			logs.push_back(cbullet_tracer_info(local->GetEyePosition(), position, Interfaces::GlobalVars()->curtime, Color(255, 255, 255, 255)));

			if (!local)
				return;

			for (size_t i = 0; i < logs.size(); i++)
			{
				auto current = logs.at(i);
				current.color = Color(int(Settings::Esp::flTracer_Beam[0] * 255.f), int(Settings::Esp::flTracer_Beam[1] * 255.f), int(Settings::Esp::flTracer_Beam[2] * 255.f)); //color of local player's tracers
				BeamInfo_t beamInfo;
				beamInfo.m_nType = TE_BEAMPOINTS;
				beamInfo.m_pszModelName = "sprites/physbeam.vmt";
				beamInfo.m_nModelIndex = -1;
				beamInfo.m_flHaloScale = 0.0f;
				beamInfo.m_flLife = Settings::Esp::flTracersDuration;
				beamInfo.m_flWidth = Settings::Esp::flTracersWidth;
				beamInfo.m_flEndWidth = Settings::Esp::flTracersWidth;
				beamInfo.m_flFadeLength = 0.0f;
				beamInfo.m_flAmplitude = 2.0f;
				beamInfo.m_flBrightness = 255.f;
				beamInfo.m_flSpeed = 0.2f;
				beamInfo.m_nStartFrame = 0;
				beamInfo.m_flFrameRate = 0.f;
				beamInfo.m_flRed = current.color.r();
				beamInfo.m_flGreen = current.color.g();
				beamInfo.m_flBlue = current.color.b();
				beamInfo.m_nSegments = 2;
				beamInfo.m_bRenderable = true;
				beamInfo.m_nFlags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE | FBEAM_HALOBEAM;

				beamInfo.m_vecStart = LocalPlayer->GetEyePosition();
				beamInfo.m_vecEnd = current.dst;
				if (Settings::Esp::esp_beams_tracer)
				{

					auto beam = shit::g_pViewRenderBeams()->CreateBeamPoints(beamInfo);
					if (beam)
						shit::g_pViewRenderBeams()->DrawBeam(beam);
				}

				logs.erase(logs.begin() + i);
			}


		}
	}


	if (!strcmp(event->GetName(), "player_hurt"))
	{
		if (Settings::Esp::esp_HitMarker)
		{

			int attacker = event->GetInt("attacker");
			if (Interfaces::Engine()->GetPlayerForUserID(attacker) == Interfaces::Engine()->GetLocalPlayer())
			{
				switch (Settings::Esp::esp_HitMarkerSound)
				{
				case 0: break;
				case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break;
				case 2: PlaySoundA(metallic, NULL, SND_ASYNC | SND_MEMORY); break;
				case 3: PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break;
				case 4: PlaySoundA(winxp_wav, NULL, SND_ASYNC | SND_MEMORY); break;


				}
				Settings::hitmarkerAlpha = 1.f;
			}
		}
		int attackerid = event->GetInt("attacker");
		int entityid = Interfaces::Engine()->GetPlayerForUserID(attackerid);
		if (entityid == Interfaces::Engine()->GetLocalPlayer())
		{

			int nUserID = event->GetInt("attacker");
			int nDead = event->GetInt("userid");
			if (nUserID || nDead)
			{
				SDK::PlayerInfo killed_info = GetInfo(Interfaces::Engine()->GetPlayerForUserID(nDead));
				SDK::PlayerInfo killer_info = GetInfo(Interfaces::Engine()->GetPlayerForUserID(nUserID));
				std::string before = ("You ");
				std::string two = ("shot ");
				std::string three = killed_info.m_szPlayerName;
				std::string four = (" in his ");
				std::string five = HitgroupToName(event->GetInt("hitgroup"));
				std::string sixa = " for ";
				std::string sevena = event->GetString("dmg_health");
				std::string damage = " damage";
				std::string sixb = " (";
				std::string sevenb = event->GetString("health");
				std::string ate = " health remaining)";
				std::string newline = "\n";
				if (Settings::Esp::esp_HitMarker)
				{
					Interfaces::Engine()->ExecuteClientCmd("developer 1");
					Interfaces::Engine()->ExecuteClientCmd("con_filter_enable 2 ");
					Interfaces::Engine()->ExecuteClientCmd("con_filter_text Hit ");
					Msg((before + two + three + four + five + sixa + sevena + damage + sixb + sevenb + ate + newline).c_str());
				}

			}
		}
	}
}

void CEsp::renderBeams()
{

	if (Settings::Esp::esp_beams_tracer)
		return;

	auto local = static_cast<CBaseEntity*>(Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer()));

	if (!local)
		return;
	for (size_t i = 0; i < logs.size(); i++)
	{

		auto current = logs.at(i);

		current.color = Color(int(Settings::Esp::flTracer_Beam[0] * 255.f), int(Settings::Esp::flTracer_Beam[1] * 255.f), int(Settings::Esp::flTracer_Beam[2] * 255.f));

		if (Settings::Esp::esp_beams_tracer)
			Interfaces::DebugOverlay()->AddLineOverlay(current.src, current.dst, current.color.r(), current.color.g(), current.color.g(), true, -1.f);


		Interfaces::DebugOverlay()->AddBoxOverlay(current.dst, Vector(-2, -2, -2), Vector(2, 2, 2), Vector(0, 0, 0), current.color.r(), current.color.g(), current.color.g(), 127, -1.f);

		if (fabs(Interfaces::GlobalVars()->curtime - current.time) > 5.f)
			logs.erase(logs.begin() + i);
	}
}

void CEsp::DrawHitmarker()
{
	if (Settings::hitmarkerAlpha < 0.f)
		Settings::hitmarkerAlpha = 0.f;
	else if (Settings::hitmarkerAlpha > 0.f)
		Settings::hitmarkerAlpha -= 0.01f;

	int W, H;
	Interfaces::Engine()->GetScreenSize(W, H);

	float r = Settings::Esp::esp_HitMarkerColor[0] * 255.f;
	float g = Settings::Esp::esp_HitMarkerColor[1] * 255.f;
	float b = Settings::Esp::esp_HitMarkerColor[2] * 255.f;

	if (Settings::hitmarkerAlpha > 0.f)
	{
		g_pRender->DrawLine(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));
		g_pRender->DrawLine(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, Color(r, g, b, (Settings::hitmarkerAlpha * 255.f)));

	}
}

void hitmarker::player_hurt_listener::start()
{
	if (!Interfaces::GameEvent()->AddListener(this, "player_hurt", false)) {
		throw exception("Failed to register the event");
	}
	if (!Interfaces::GameEvent()->AddListener(this, "bullet_impact", false))
	{
		throw exception("Failed to register the event");
	}
}
void hitmarker::player_hurt_listener::stop()
{
	Interfaces::GameEvent()->RemoveListener(this);
}
void hitmarker::player_hurt_listener::FireGameEvent(IGameEvent *event)
{
	g_pEsp->HitmarkerEvents(event);
}
int hitmarker::player_hurt_listener::GetEventDebugID(void)
{
	return 0x2A;
}

/*
void CEsp::GrenadePrediction()
{
if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
{
CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

const float TIMEALIVE = 5.f;
const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

float fStep = 0.1f;
float fGravity = 800.0f / 8.f;

Vector vPos, vThrow, vThrow2;
Vector vStart;

int iCollisions = 0;

QAngle vViewAngles;
Interfaces::Engine()->GetViewAngles(vViewAngles);

vThrow[0] = vViewAngles[0];
vThrow[1] = vViewAngles[1];
vThrow[2] = vViewAngles[2];

if (vThrow[0] < 0)
vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
else
vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

float fVel = (90 - vThrow[0]) * 4;
if (fVel > 500)
fVel = 500;

AngleVectors(vThrow, vThrow2);

Vector vEye = pLocal->GetEyePosition();
vStart[0] = vEye[0] + vThrow2[0] * 16;
vStart[1] = vEye[1] + vThrow2[1] * 16;
vStart[2] = vEye[2] + vThrow2[2] * 16;

vThrow2[0] = (vThrow2[0] * fVel) + pLocal->GetVelocity()[0];
vThrow2[1] = (vThrow2[1] * fVel) + pLocal->GetVelocity()[1];
vThrow2[2] = (vThrow2[2] * fVel) + pLocal->GetVelocity()[2];

#define IsGrenade g_pPlayers->GetLocal()->WeaponIndex == WEAPON_SMOKEGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_HEGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_INCGRENADE | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_MOLOTOV | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_DECOY | g_pPlayers->GetLocal()->WeaponIndex == WEAPON_FLASHBANG

if (!pLocal->IsDead() && IsGrenade)
{
for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
{
vPos = vStart + vThrow2 * fStep;

Ray_t ray;
trace_t tr;
CTraceFilter loc;
loc.pSkip = pLocal;

ray.Init(vStart, vPos);
Interfaces::EngineTrace()->TraceRay(ray, MASK_SOLID, &loc, &tr);
Color color = Color(0, 255, 0);
if (tr.DidHit())
{
float anglez = DotProduct(Vector(0, 0, 1), tr.plane.normal);
float invanglez = DotProduct(Vector(0, 0, -1), tr.plane.normal);
float angley = DotProduct(Vector(0, 1, 0), tr.plane.normal);
float invangley = DotProduct(Vector(0, -1, 0), tr.plane.normal);
float anglex = DotProduct(Vector(1, 0, 0), tr.plane.normal);
float invanglex = DotProduct(Vector(3 - 1, 0, 0), tr.plane.normal);
float scale = tr.endpos.DistTo(pLocal->GetOrigin()) / 60;
Color color = Color(0, 0, 255);
if (anglez > 0.5)
{
tr.endpos.z += 1;
Vector startPos = tr.endpos + Vector(-scale, 0, 0);
Vector endPos = tr.endpos + Vector(scale, 0, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, -scale, 0);
endPos = tr.endpos + Vector(0, scale, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (invanglez > 0.5)
{
tr.endpos.z += 1;
Vector startPos = tr.endpos + Vector(-scale, 0, 0);
Vector endPos = tr.endpos + Vector(scale, 0, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, -scale, 0);
endPos = tr.endpos + Vector(0, scale, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (angley > 0.5)
{
tr.endpos.y += 1;
Vector startPos = tr.endpos + Vector(0, 0, -scale);
Vector endPos = tr.endpos + Vector(0, 0, scale);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(-scale, 0, 0);
endPos = tr.endpos + Vector(scale, 0, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (invangley > 0.5)
{
tr.endpos.y += 1;
Vector startPos = tr.endpos + Vector(0, 0, -scale);
Vector endPos = tr.endpos + Vector(0, 0, scale);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(-scale, 0, 0);
endPos = tr.endpos + Vector(scale, 0, 0);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (anglex > 0.5)
{
tr.endpos.x += 1;
Vector startPos = tr.endpos + Vector(0, -scale, 0);
Vector endPos = tr.endpos + Vector(0, scale, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, 0, -scale);
endPos = tr.endpos + Vector(0, 0, scale);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}
else if (invanglex > 0.5)
{
tr.endpos.x += 1;
Vector startPos = tr.endpos + Vector(0, -scale, 0);
Vector endPos = tr.endpos + Vector(0, scale, 0);
Vector outStart, outEnd;
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());

startPos = tr.endpos + Vector(0, 0, -scale);
endPos = tr.endpos + Vector(0, 0, scale);
if (WorldToScreen(startPos, outStart) && WorldToScreen(endPos, outEnd))
g_pRender->DrawLine((int)outStart.x, (int)outStart.y, (int)outEnd.x, (int)outEnd.y, Color::Green());
}

vThrow2 = tr.plane.normal * -2.0f * DotProduct(vThrow2, tr.plane.normal) + vThrow2;
vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

iCollisions++;
if (iCollisions > 2)
break;

vPos = vStart + vThrow2 * tr.fraction * fStep;
fTime += (fStep * (1 - tr.fraction));
}

Vector vOutStart, vOutEnd;

if (WorldToScreen(vStart, vOutStart) && WorldToScreen(vPos, vOutEnd))
g_pRender->DrawLine((int)vOutStart.x, (int)vOutStart.y, (int)vOutEnd.x, (int)vOutEnd.y, Color::Blue());

vStart = vPos;
vThrow2.z -= fGravity * tr.fraction * fStep;
}
}
}
}
*/

void CEsp::ChromeWorld() //chromeworld u blind niggur
{
	if (Settings::Esp::esp_ChromeWorld)
	{
		ConVar* Chromeworld = Interfaces::GetConVar()->FindVar("r_showenvcubemap");
		if (Chromeworld)
		{
			Chromeworld->SetValue(1);
		}
	}
	else
	{
		ConVar* Chromeworld = Interfaces::GetConVar()->FindVar("r_showenvcubemap");
		if (Chromeworld)
		{
			Chromeworld->SetValue(0);
		}
	}
}

void CEsp::MinecraftMode()
{
	if (Settings::Esp::esp_MinecraftMode)
	{
		ConVar* Minecraftmode = Interfaces::GetConVar()->FindVar("mat_showlowresimage");
		if (Minecraftmode)
		{
			Minecraftmode->SetValue(1);
		}
	}
	else
	{
		ConVar* Minecraftmode = Interfaces::GetConVar()->FindVar("mat_showlowresimage");
		if (Minecraftmode)
		{
			Minecraftmode->SetValue(0);
		}
	}
}

void CEsp::LSDMode()
{
	if (Settings::Esp::esp_LSDMode)
	{
		ConVar* lsdmode = Interfaces::GetConVar()->FindVar("mat_showmiplevels");
		if (lsdmode)
		{
			lsdmode->SetValue(1);
		}
	}
	else
	{
		ConVar* lsdmode = Interfaces::GetConVar()->FindVar("mat_showmiplevels");
		if (lsdmode)
		{
			lsdmode->SetValue(0);
		}
	}
}

//CustomModels
bool PrecacheModel(const char* szModelName)
{
	auto m_pModelPrecacheTable = Interfaces::ClientStringTableContainer()->FindTable("modelprecache");

	if (m_pModelPrecacheTable)
	{
		Interfaces::ModelInfo()->FindOrLoadModel(szModelName);
		int idx = m_pModelPrecacheTable->AddString(false, szModelName);
		if (idx == INVALID_STRING_INDEX)
			return false;
	}
	return true;
}

void CEsp::OnRender()
{
	if (Settings::Esp::esp_Sound)
		SoundEsp.DrawSoundEsp();
	
	
	if (g_pAimbot)
		g_pAimbot->OnRender();

	// if (Settings::Esp::esp_GrenadePrediction)
	// 	GrenadePrediction();

	if (g_pTriggerbot)
		g_pTriggerbot->TriggerShowStatus();

	if (Settings::Esp::esp_HitMarker)
		DrawHitmarker();

	if (Settings::Esp::bEspWarnings)
		Espwarning();


	Ambient();
	LSDMode();
	MinecraftMode();
	ChromeWorld();
	renderBeams();
	AsusWalls();

	if (Settings::Misc::misc_AwpAim && IsLocalAlive())
	{
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(1);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(999999999);
	}
	else
	{
		ConVar* crosshair1 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_show");
		crosshair1->SetValue(0);
		ConVar* crosshair2 = Interfaces::GetConVar()->FindVar("weapon_debug_spread_gap");
		crosshair2->SetValue(0);
	}
	NightMode();

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate && CheckPlayerTeam(pPlayer))
		{
			if (g_pTriggerbot)
				g_pTriggerbot->TriggerShow(pPlayer);

			DrawPlayerEsp(pPlayer);

			if (Settings::Esp::esp_Skeleton)
				DrawPlayerSkeleton(pPlayer);

			if (Settings::Esp::esp_BulletTrace)
				DrawPlayerBulletTrace(pPlayer);
		}
	}





	

	if (Settings::Esp::esp_BombTimer)
	{
		if (bC4Timer && iC4Timer)
		{
			float fTimeStamp = Interfaces::Engine()->GetLastTimeStamp();

			if (!fExplodeC4Timer)
			{
				fExplodeC4Timer = fTimeStamp + (float)iC4Timer;
			}
			else
			{
				fC4Timer = fExplodeC4Timer - fTimeStamp;

				if (fC4Timer < 0.f)
					fC4Timer = 0.f;
			}
		}
		else
		{
			fExplodeC4Timer = 0.f;
			fC4Timer = 0.f;
		}
	}


	Color GrenadeHelper = Color(int(Settings::Esp::GrenadeHelper[0] * 255.f),
		int(Settings::Esp::GrenadeHelper[1] * 255.f),
		int(Settings::Esp::GrenadeHelper[2] * 255.f));

	if (Settings::Esp::helper && Interfaces::Engine()->IsConnected())
	{

		CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		for (int i = 0; i < cGrenade.GrenadeInfo.size(); i++)
		{
			GrenadeInfo_t info;
			if (!cGrenade.GetInfo(i, &info))
				continue;

			int iGrenadeID = StringToWeapon(info.szWeapon);


			if (!local->GetBaseWeapon())
				continue;

			if (!(local->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex2() == iGrenadeID || (iGrenadeID == 46 && local->GetBaseWeapon()->GeteAttributableItem()->GetItemDefinitionIndex2() == 48)))
				continue;

			Vector vecOnScreenOrigin, vecOnScreenAngles;
			int iCenterY, iCenterX;
			Interfaces::Engine()->GetScreenSize(iCenterY, iCenterX);
			iCenterX /= 2;
			iCenterY /= 2;

			float dist = sqrt(pow(local->GetRenderOrigin().x - info.vecOrigin.x, 2) + pow(local->GetRenderOrigin().y - info.vecOrigin.y, 2) + pow(local->GetRenderOrigin().z - info.vecOrigin.z, 2)) * 0.0254f;

			if (dist < 0.5f)
			{
				if (WorldToScreen(info.vecOrigin, vecOnScreenOrigin))
					g_pRender->DrawWave1(info.vecOrigin, 4, Color::Red());

				Vector vecAngles;
				AngleVectors(info.vecViewangles, &vecAngles);
				vecAngles *= 100;

				if (WorldToScreen((local->GetEyePosition() + vecAngles), vecAngles))
					g_pRender->DrawFillBox(vecAngles.x, vecAngles.y, 7, 7, Color::Green());

				g_pRender->Text(iCenterX, iCenterY + 30, true, true, Color::White(), (char*)info.szName.c_str());
				g_pRender->Text(iCenterX, iCenterY, true, true, Color::White(), (char*)info.szDescription.c_str());

			}
			else
			{
				if (WorldToScreen(info.vecOrigin, vecOnScreenOrigin));

				g_pRender->DrawWave1(info.vecOrigin, 10, Color(GrenadeHelper));
				g_pRender->DrawWave1(info.vecOrigin, 7, Color(GrenadeHelper));
			}
		}
	}
	else
	{
		cGrenade.GrenadeInfo.clear();
	}


	if (Settings::Esp::esp_Bomb || Settings::Esp::esp_WorldWeapons || Settings::Esp::esp_WorldGrenade || Settings::Esp::esp_Chicken || Settings::Esp::esp_BoxNade || Settings::Esp::esp_Fish )
	{
		for (int EntIndex = 0; EntIndex < Interfaces::EntityList()->GetHighestEntityIndex(); EntIndex++)
		{
			CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(EntIndex);

			if (!pEntity || pEntity->IsPlayer())
				continue;

			const model_t* pModel = pEntity->GetModel();

			if (pModel)
			{
				const char* pModelName = Interfaces::ModelInfo()->GetModelName(pModel);

				if (pModelName)
				{
					Vector vEntScreen;

					if (WorldToScreen(pEntity->GetRenderOrigin(), vEntScreen))
					{

						if (Settings::Esp::esp_Chicken && (pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CChicken))
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Green(),
								"Chicken");
						}
						
						if (Settings::Esp::esp_Fish && (pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CFish))
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Green(),
								"Fish");
						}

						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Green(), "[C4]");
						}

						if (Settings::Esp::esp_Bomb && pEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CPlantedC4)
						{
							g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::DarkRed(),
								"[C4 PLANTED]");
						}

						if (Settings::Esp::esp_WorldWeapons && !strstr(pModelName, "models/weapons/w_eq_")
							&& !strstr(pModelName, "models/weapons/w_ied"))
						{
							if (strstr(pModelName, "models/weapons/w_") && strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 17;

								WeaponName[WeaponName.size() - 12] = '\0';

								if (strstr(pModelName, "models/weapons/w_rif") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_pist") && strstr(pModelName, "_dropped.mdl") && !strstr(pModelName, "models/weapons/w_pist_223"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_pist_223") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName = "usp-s";
								}
								else if (strstr(pModelName, "models/weapons/w_smg") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 4);
								}
								else if (strstr(pModelName, "models/weapons/w_mach") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_shot") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}
								else if (strstr(pModelName, "models/weapons/w_snip") && strstr(pModelName, "_dropped.mdl"))
								{
									WeaponName.erase(0, 5);
								}

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::White(),
									WeaponName.c_str());
							}
						}

						if (Settings::Esp::esp_BoxNade && (strstr(pModelName, "models/weapons/w_eq_")) || strstr(pModelName, "models/Weapons/w_eq_"))
						{
							if (strstr(pModelName, "_dropped.mdl"))
							{
								if (strstr(pModelName, "fraggrenade"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Red());
								}
								else if (strstr(pModelName, "molotov"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::OrangeRed());
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::OrangeRed());
								}
								else if (strstr(pModelName, "flashbang"))
								{
									if (Settings::Esp::esp_BoxNade)
										g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Yellow());
								}
							}
							else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
							{
								if (Settings::Esp::esp_BoxNade)
									g_pRender->DrawOutlineBox((int)vEntScreen.x - 10, (int)vEntScreen.y - 10, 20, 20, Color::Gray());
							}
						}

						if (Settings::Esp::esp_WorldGrenade &&
							(strstr(pModelName, "models/weapons/w_eq_") ||
								strstr(pModelName, "models/Weapons/w_eq_")))
						{
							if (strstr(pModelName, "_dropped.mdl"))
							{
								string WeaponName = pModelName + 20;

								WeaponName[WeaponName.size() - 12] = '\0';

								Color GrenadeColor = Color::White();

								if (strstr(pModelName, "fraggrenade"))
								{
									WeaponName = "Grenade";
									GrenadeColor = Color::Red();
								}
								else if (strstr(pModelName, "molotov"))
								{
									WeaponName = "Molotov";
									GrenadeColor = Color::OrangeRed();
								}
								else if (strstr(pModelName, "incendiarygrenade"))
								{
									WeaponName = "Incendiary";
									GrenadeColor = Color::OrangeRed();
								}
								else if (strstr(pModelName, "flashbang"))
								{
									WeaponName = "Flashbang";
									GrenadeColor = Color::Yellow();
								}

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, GrenadeColor,
									WeaponName.c_str());
							}
							else if (strstr(pModelName, "smokegrenade_thrown.mdl"))
							{
								string WeaponName = "Smoke";

								g_pRender->Text((int)vEntScreen.x, (int)vEntScreen.y, true, true, Color::Gray(),
									WeaponName.c_str());
							}
						}
					}
				}
			}
		}
	}

	// Draw Ticks

	if (Settings::Aimbot::aim_Backtrack && Settings::Aimbot::aim_DrawBacktrack) // Use Esp Visible Combo to change from visible only and not visible.
	{
		for (int i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			CBaseEntity *entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
			CPlayer* pPlayer = g_pPlayers->GetPlayer(i);
			PlayerInfo pinfo;
			if (entity == nullptr)
				continue;
			if (entity == local)
				continue;
			if (entity->IsDormant())
				continue;
			if (entity->GetTeam() == local->GetTeam())
				continue;
			if (Interfaces::Engine()->GetPlayerInfo(i, &pinfo) && !entity->IsDead())
			{
				if (Settings::Esp::esp_Visible >= 3)
				{
					if (!local->IsDead() && pPlayer->bVisible)
					{
						for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
						{
							Vector screenbacktrack[64][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimTime())
							{
								if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									g_pRender->DrawFillBox(screenbacktrack[i][t].x, screenbacktrack[i][t].y, 4, 4, g_pEsp->GetPlayerColor(pPlayer));
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
				else
				{
					if (!local->IsDead())
					{
						for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
						{
							Vector screenbacktrack[64][12];

							if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimTime())
							{
								if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
								{
									g_pRender->DrawFillBox(screenbacktrack[i][t].x, screenbacktrack[i][t].y, 4, 4, g_pEsp->GetPlayerColor(pPlayer));
								}
							}
						}
					}
					else
					{
						memset(&headPositions[0][0], 0, sizeof(headPositions));
					}
				}
			}
		}
	}


	if (Settings::Misc::custommodelson)
	{
		for (int i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
			CBaseEntity *entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
			PlayerInfo pinfo;
			if (entity == nullptr)
				continue;
			if (entity == local)
				continue;
			if (entity->IsDormant())
				continue;
			if (Interfaces::Engine()->GetPlayerInfo(i, &pinfo) && !entity->IsDead())
			{
				CustomModels(entity);
			}
		}
	}

}





void CEsp::CustomModels(CBaseEntity* entity)
{
	CBaseEntity* local = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	// if (entity->GetTeam() == TEAM_CT && Interfaces::Engine()->IsConnected())
	if (entity->GetTeam() == TEAM_CT)
	{
		switch (Settings::Misc::customodelsct)
		{
		case 0:
			break;

		case 1:
			PrecacheModel("models/player/custom_player/kuristaja/trump/trump.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/trump/trump.mdl"));
			break;

		case 2:
			PrecacheModel("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl"));
			break;

		case 3:
			PrecacheModel("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl"));
			break;

		case 4:
			PrecacheModel("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl"));
			break;

		}
	}
	// else if (entity->GetTeam() == TEAM_TT && Interfaces::Engine()->IsConnected())
	else if (entity->GetTeam() == TEAM_TT)
	{
		switch (Settings::Misc::customodelst)
		{
		case 0:
			break;

		case 1:
			PrecacheModel("models/player/custom_player/kuristaja/trump/trump.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/trump/trump.mdl"));
			break;

		case 2:
			PrecacheModel("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/xnet/girl/noire_swimwear/noire.mdl"));
			break;

		case 3:
			PrecacheModel("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/bbs_93x_net_2017/momiji_inubashiri/update_2017_02_04/momiji_inubashiri.mdl"));
			break;

		case 4:
			PrecacheModel("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl");
			entity->SetModelIndex(Interfaces::ModelInfo()->GetModelIndex("models/player/custom_player/kuristaja/banana_joe/banana_joe.mdl"));
			break;


		}
	}
}


void MsgFunc_ServerRankRevealAll()
{
	using tServerRankRevealAllFn = bool(__cdecl*)(int*);
	static tServerRankRevealAllFn ServerRankRevealAll = 0;

	if (!ServerRankRevealAll)
	{
		ServerRankRevealAll = (tServerRankRevealAllFn)(
			CSX::Memory::FindPattern(CLIENT_DLL, "55 8B EC 8B 0D ? ? ? ? 68", 0));
	}

	if (ServerRankRevealAll)
	{
		int fArray[3] = { 0,0,0 };
		ServerRankRevealAll(fArray);
	}
}

void CEsp::OnCreateMove(CUserCmd* pCmd)
{
	if (Settings::Esp::esp_Rank && pCmd->buttons & IN_SCORE)
		MsgFunc_ServerRankRevealAll();

	g_pEsp->SoundEsp.Update();
}

void CEsp::OnReset()
{
	g_pEsp->SoundEsp.Sound.clear();

	if (Settings::Esp::esp_BombTimer)
	{
		if (Settings::Esp::esp_BombTimer > 60)
			Settings::Esp::esp_BombTimer = 60;

		bC4Timer = false;
		iC4Timer = Settings::Esp::esp_BombTimer;
	}
}

void CEsp::OnEvents(IGameEvent* pEvent)
{
	if (g_pEsp && Settings::Esp::esp_BombTimer)
	{
		if (!strcmp(pEvent->GetName(), "bomb_defused") || !strcmp(pEvent->GetName(), "bomb_exploded"))
		{
			bC4Timer = false;
		}
		else if (!strcmp(pEvent->GetName(), "bomb_planted"))
		{
			bC4Timer = true;
		}
	}
}

void CEsp::OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
{
	// if (!g_pPlayers || Interfaces::Engine()->IsTakingScreenshot() || !Interfaces::Engine()->IsConnected() || !pInfo.pModel) - screenshot shit
	if (!g_pPlayers || !Interfaces::Engine()->IsConnected() || !pInfo.pModel)
		return;

	static bool InitalizeMaterial = false;

	if (!InitalizeMaterial)
	{
		visible_flat = CreateMaterial(true, false);
		visible_tex = CreateMaterial(false, false);
		hidden_flat = CreateMaterial(true, true);
		hidden_tex = CreateMaterial(false, true);

		InitalizeMaterial = true;

		return;
	}

	string strModelName = Interfaces::ModelInfo()->GetModelName(pInfo.pModel);

	if (strModelName.size() <= 1)
		return;

	if (Settings::Misc::misc_ChamsMaterials)
	{
		if (strModelName.find("models/player") != std::string::npos)
		{
			IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);

			if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer)
			{
				IMaterial *material;
				switch (Settings::Misc::misc_ChamsMaterialsList)
				{
				case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
				case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
				case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
				case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
				case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
				case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
				case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
				case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
				}
				Color color = Color(255, 255, 255, 255);
				if (Settings::Esp::esp_ChamsVisible <= 2)
				{
					ForceMaterial(color, material);
					material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
				}
				else
				{
					ForceMaterial(color, material);
					material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
				}
				Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
			}
		}
	}

	


	if (Settings::Misc::misc_ArmMaterials)
	{
		switch (Settings::Misc::misc_ArmMaterialsType)
		{
		case 0: if (strModelName.find("arms") != std::string::npos)
		{
			IMaterial *material;
			switch (Settings::Misc::misc_ArmMaterialsList)
			{
			case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
			case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
			case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
			case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
			case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
			case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
			case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
			case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
			}
			Color color = Color(255, 255, 255, 255);
			ForceMaterial(color, material);
			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
		} break;
		case 1: if (strModelName.find("weapons/v") != std::string::npos)
		{
			IMaterial *material;
			switch (Settings::Misc::misc_ArmMaterialsList)
			{
			case 0: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break; // Glass
			case 1:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break; // Crystal
			case 2:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break; // Gold
			case 3:	material = Interfaces::MaterialSystem()->FindMaterial("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break; // Dark Chrome
			case 4: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break; // Plastic Glass
			case 5:	material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/velvet", TEXTURE_GROUP_OTHER); break; // Velvet
			case 6: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break; // Crystal Blue
			case 7: material = Interfaces::MaterialSystem()->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER); break; // Detailed Gold
			}
			Color color = Color(255, 255, 255, 255);
			ForceMaterial(color, material);
			Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
		} break;
		}
	}

	if (Settings::Misc::misc_NoHands)
	{
		if (strModelName.find("arms") != string::npos && Settings::Misc::misc_NoHands)
		{
			IMaterial* Hands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(Hands);
		}
	}
	else
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* Hands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
		}
	}

	if (Settings::Misc::misc_WireHands) //Wireframe Hands
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* WireHands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			WireHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
			Interfaces::ModelRender()->ForcedMaterialOverride(WireHands);
		}
	}
	else
	{
		if (strModelName.find("arms") != string::npos)
		{
			IMaterial* WireHands = Interfaces::MaterialSystem()->FindMaterial(strModelName.c_str(), TEXTURE_GROUP_MODEL);
			WireHands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
		}
	}


	if (Settings::Esp::esp_Chams && Client::g_pPlayers && Client::g_pPlayers->GetLocal() && strModelName.find("models/player") != string::npos)
	{
		IClientEntity* pBaseEntity = Interfaces::EntityList()->GetClientEntity(pInfo.entity_index);

		if (pBaseEntity && pBaseEntity->GetClientClass()->m_ClassID == (int)CLIENT_CLASS_ID::CCSPlayer)
		{
			CPlayer* pPlayer = g_pPlayers->GetPlayer(pInfo.entity_index);

			if (pPlayer && pPlayer->bUpdate)
			{
				bool CheckTeam = false;

				Color TeamHideColor;
				Color TeamVisibleColor;

				if (Settings::Esp::esp_Enemy && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
					CheckTeam = true;

				if (Settings::Esp::esp_Team && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
					CheckTeam = true;

				int playerHealth = pPlayer->iHealth;

				if (pPlayer->Team == TEAM_CT)
				{
					if (Settings::Esp::esp_HealthChams)
					{
						if (playerHealth >= 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0;
							Settings::Esp::chams_Color_TT[1] = 1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0;
							Settings::Esp::chams_Color_CT[1] = 1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0;
							Settings::Esp::chams_Color_VTT[1] = 1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0;
							Settings::Esp::chams_Color_VCT[1] = 1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 90 && playerHealth < 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0.15;
							Settings::Esp::chams_Color_TT[1] = 0.85;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.15;
							Settings::Esp::chams_Color_CT[1] = 0.85;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.15;
							Settings::Esp::chams_Color_VTT[1] = 0.85;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.15;
							Settings::Esp::chams_Color_VCT[1] = 0.85;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 80 && playerHealth < 90)
						{
							Settings::Esp::chams_Color_TT[0] = 0.3;
							Settings::Esp::chams_Color_TT[1] = 0.7;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.3;
							Settings::Esp::chams_Color_CT[1] = 0.7;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.3;
							Settings::Esp::chams_Color_VTT[1] = 0.7;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.3;
							Settings::Esp::chams_Color_VCT[1] = 0.7;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 60 && playerHealth < 80)
						{
							Settings::Esp::chams_Color_TT[0] = 0.5;
							Settings::Esp::chams_Color_TT[1] = 0.5;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.5;
							Settings::Esp::chams_Color_CT[1] = 0.5;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.5;
							Settings::Esp::chams_Color_VTT[1] = 0.5;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.5;
							Settings::Esp::chams_Color_VCT[1] = 0.5;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 40 && playerHealth < 60)
						{
							Settings::Esp::chams_Color_TT[0] = 0.7;
							Settings::Esp::chams_Color_TT[1] = 0.3;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.7;
							Settings::Esp::chams_Color_CT[1] = 0.3;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.7;
							Settings::Esp::chams_Color_VTT[1] = 0.3;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.7;
							Settings::Esp::chams_Color_VCT[1] = 0.3;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 20 && playerHealth < 40)
						{
							Settings::Esp::chams_Color_TT[0] = 0.85;
							Settings::Esp::chams_Color_TT[1] = 0.15;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.85;
							Settings::Esp::chams_Color_CT[1] = 0.15;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.85;
							Settings::Esp::chams_Color_VTT[1] = 0.15;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.85;
							Settings::Esp::chams_Color_VCT[1] = 0.15;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 0.9;
							Settings::Esp::chams_Color_TT[1] = 0.1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.9;
							Settings::Esp::chams_Color_CT[1] = 0.1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.9;
							Settings::Esp::chams_Color_VTT[1] = 0.1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.9;
							Settings::Esp::chams_Color_VCT[1] = 0.1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 1;
							Settings::Esp::chams_Color_TT[1] = 0;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 1;
							Settings::Esp::chams_Color_CT[1] = 0;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 1;
							Settings::Esp::chams_Color_VTT[1] = 0;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 1;
							Settings::Esp::chams_Color_VCT[1] = 0;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
					}

					TeamHideColor = Color(int(Settings::Esp::chams_Color_CT[0] * 255.f),
						int(Settings::Esp::chams_Color_CT[1] * 255.f),
						int(Settings::Esp::chams_Color_CT[2] * 255.f));
				}
				else if (pPlayer->Team == TEAM_TT)
				{
					if (Settings::Esp::esp_HealthChams)
					{
						if (playerHealth >= 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0;
							Settings::Esp::chams_Color_TT[1] = 1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0;
							Settings::Esp::chams_Color_CT[1] = 1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0;
							Settings::Esp::chams_Color_VTT[1] = 1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0;
							Settings::Esp::chams_Color_VCT[1] = 1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 90 && playerHealth < 95)
						{
							Settings::Esp::chams_Color_TT[0] = 0.15;
							Settings::Esp::chams_Color_TT[1] = 0.85;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.15;
							Settings::Esp::chams_Color_CT[1] = 0.85;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.15;
							Settings::Esp::chams_Color_VTT[1] = 0.85;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.15;
							Settings::Esp::chams_Color_VCT[1] = 0.85;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 80 && playerHealth < 90)
						{
							Settings::Esp::chams_Color_TT[0] = 0.3;
							Settings::Esp::chams_Color_TT[1] = 0.7;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.3;
							Settings::Esp::chams_Color_CT[1] = 0.7;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.3;
							Settings::Esp::chams_Color_VTT[1] = 0.7;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.3;
							Settings::Esp::chams_Color_VCT[1] = 0.7;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 60 && playerHealth < 80)
						{
							Settings::Esp::chams_Color_TT[0] = 0.5;
							Settings::Esp::chams_Color_TT[1] = 0.5;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.5;
							Settings::Esp::chams_Color_CT[1] = 0.5;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.5;
							Settings::Esp::chams_Color_VTT[1] = 0.5;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.5;
							Settings::Esp::chams_Color_VCT[1] = 0.5;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 40 && playerHealth < 60)
						{
							Settings::Esp::chams_Color_TT[0] = 0.7;
							Settings::Esp::chams_Color_TT[1] = 0.3;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.7;
							Settings::Esp::chams_Color_CT[1] = 0.3;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.7;
							Settings::Esp::chams_Color_VTT[1] = 0.3;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.7;
							Settings::Esp::chams_Color_VCT[1] = 0.3;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 20 && playerHealth < 40)
						{
							Settings::Esp::chams_Color_TT[0] = 0.85;
							Settings::Esp::chams_Color_TT[1] = 0.15;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.85;
							Settings::Esp::chams_Color_CT[1] = 0.15;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.85;
							Settings::Esp::chams_Color_VTT[1] = 0.15;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.85;
							Settings::Esp::chams_Color_VCT[1] = 0.15;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 0.9;
							Settings::Esp::chams_Color_TT[1] = 0.1;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 0.9;
							Settings::Esp::chams_Color_CT[1] = 0.1;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 0.9;
							Settings::Esp::chams_Color_VTT[1] = 0.1;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 0.9;
							Settings::Esp::chams_Color_VCT[1] = 0.1;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
						if (playerHealth >= 10 && playerHealth < 20)
						{
							Settings::Esp::chams_Color_TT[0] = 1;
							Settings::Esp::chams_Color_TT[1] = 0;
							Settings::Esp::chams_Color_TT[2] = 0;

							Settings::Esp::chams_Color_CT[0] = 1;
							Settings::Esp::chams_Color_CT[1] = 0;
							Settings::Esp::chams_Color_CT[2] = 0;

							Settings::Esp::chams_Color_VTT[0] = 1;
							Settings::Esp::chams_Color_VTT[1] = 0;
							Settings::Esp::chams_Color_VTT[2] = 0;

							Settings::Esp::chams_Color_VCT[0] = 1;
							Settings::Esp::chams_Color_VCT[1] = 0;
							Settings::Esp::chams_Color_VCT[2] = 0;
						}
					}

					TeamHideColor = Color(int(Settings::Esp::chams_Color_TT[0] * 255.f),
						int(Settings::Esp::chams_Color_TT[1] * 255.f),
						int(Settings::Esp::chams_Color_TT[2] * 255.f));
				}

				bool SetColor = false;

				if (Settings::Esp::esp_ChamsVisible == 0 && pPlayer->Team != g_pPlayers->GetLocal()->Team) // �����������
				{
					SetColor = true;
				}
				else if (Settings::Esp::esp_ChamsVisible == 1 && pPlayer->Team == g_pPlayers->GetLocal()->Team) // �����
				{
					SetColor = true;
				}
				else if (Settings::Esp::esp_ChamsVisible == 2) // ����
				{
					SetColor = true;
				}



				if (SetColor)
				{
					int playerHealth = pPlayer->iHealth;
					if (pPlayer->Team == TEAM_CT)
					{
						TeamVisibleColor = Color(int(Settings::Esp::chams_Color_VCT[0] * 255.f),
							int(Settings::Esp::chams_Color_VCT[1] * 255.f),
							int(Settings::Esp::chams_Color_VCT[2] * 255.f));
					}
					else if (pPlayer->Team == TEAM_TT)
					{
						TeamVisibleColor = Color(int(Settings::Esp::chams_Color_VTT[0] * 255.f),
							int(Settings::Esp::chams_Color_VTT[1] * 255.f),
							int(Settings::Esp::chams_Color_VTT[2] * 255.f));
					}
				}
				else
					TeamVisibleColor = TeamHideColor;

				if (CheckTeam && !Settings::Misc::misc_ChamsMaterials)
				{
					if (Settings::Esp::esp_ChamsVisible <= 2)
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
						else if (Settings::Esp::esp_Chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
						}
					}
					else
					{
						if (Settings::Esp::esp_Chams == 1)
						{
							ForceMaterial(TeamHideColor, hidden_flat);
							hidden_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
						else if (Settings::Esp::esp_Chams >= 2)
						{
							ForceMaterial(TeamHideColor, hidden_tex);
							hidden_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
						}
					}

					Interfaces::ModelRender()->DrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

					if (Settings::Esp::esp_Chams == 1)
					{
						ForceMaterial(TeamVisibleColor, visible_flat);
						visible_flat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
					else if (Settings::Esp::esp_Chams >= 2)
					{
						ForceMaterial(TeamVisibleColor, visible_tex);
						visible_tex->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
					}
				}	
			}
		}
	}
}

void CEsp::DrawPlayerEsp(CPlayer* pPlayer)
{
	bool bOriginScreen = (pPlayer->vOriginScreen.x > 0 && pPlayer->vOriginScreen.y > 0);
	bool bHitBoxScreen = (pPlayer->vHitboxHeadScreen.x > 0 && pPlayer->vHitboxHeadScreen.y > 0);

	if (!bOriginScreen && !bHitBoxScreen)
		return;

	Vector vLineOrigin;

	if (Settings::Esp::esp_Size < 0)
	{
		Settings::Esp::esp_Size = 1;
	}
	else if (Settings::Esp::esp_Size > 10)
	{
		Settings::Esp::esp_Size = 10;
	}

	if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected() && Settings::Esp::esp_Defusing && pPlayer->m_pEntity->m_bIsDefusing() && pPlayer->Team == TEAM_CT)
	{
		int iHpAmY = 1;
		g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, Color::Red(), ("Currently Defusingf"));
	}


#define VK_MOUSE5 0x06

	if (Settings::Esp::esp_CapitalToggle)
	{
		if (GetAsyncKeyState(VK_CAPITAL))
		{
			Settings::Esp::esp_Size = 6;
		}
		else if (!GetAsyncKeyState(VK_CAPITAL))
		{
			Settings::Esp::esp_Size = 0;
		}
	}

	int Height = (int)pPlayer->vOriginScreen.y - (int)pPlayer->vHitboxHeadScreen.y;

	if (Height < 18)
		Height = 18;

	int Width = Height / 2;

	int x = (int)pPlayer->vHitboxHeadScreen.x - Width / 2;
	int y = (int)pPlayer->vHitboxHeadScreen.y;

	vLineOrigin = pPlayer->vHitboxHeadScreen;
	vLineOrigin.y += Height;

	Color EspPlayerColor = GetPlayerColor(pPlayer);
	Color EspVisibleColor = GetPlayerVisibleColor(pPlayer);

	if (Settings::Esp::esp_Size)
	{
		if (Settings::Esp::esp_Style == 0)
		{
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawBox(x, y, Width, Height, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineBox(x, y, Width, Height, EspVisibleColor);
			}
		}
		else if (Settings::Esp::esp_Style >= 1)
		{
			if (!Settings::Esp::esp_Outline)
			{
				g_pRender->DrawCoalBox(x, y, Width, Height, EspVisibleColor);
			}
			else if (Settings::Esp::esp_Outline)
			{
				g_pRender->DrawOutlineCoalBox(x, y, Width, Height, EspVisibleColor);
			}
		}
	}

	if (Settings::Esp::esp_Line)
	{
		g_pRender->DrawLine((int)vLineOrigin.x, (int)vLineOrigin.y, iScreenWidth / 2, iScreenHeight, EspVisibleColor);
	}

	if (Settings::Esp::esp_Name)
	{
		g_pRender->Text((int)vLineOrigin.x, (int)pPlayer->vHitboxHeadScreen.y - 13, true, true, EspPlayerColor, pPlayer->Name.c_str());
	}



	int iHpAmY = 1;

	if (Settings::Esp::esp_Health >= 1)
	{
		Color Minus = Color::Red();

		if (pPlayer->Team == TEAM_CT)
		{
			Minus = CT_HP_ColorM;
		}
		else if (pPlayer->Team == TEAM_TT)
		{
			Minus = TT_HP_ColorM;
		}

		int iHealth = pPlayer->iHealth;

		if (iHealth)
		{
			if (Settings::Esp::esp_Health == 1)
			{


				g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspPlayerColor, to_string(iHealth).c_str());
				iHpAmY += 10;
			}
			else if (Settings::Esp::esp_Health == 2)
			{



				g_pRender->DrawHorBar(x, (int)vLineOrigin.y + iHpAmY, Width, 5, iHealth, Color::LawnGreen(), Minus);
				iHpAmY += 6;
			}
			else if (Settings::Esp::esp_Health == 3)
			{



				g_pRender->DrawVerBar(x - 6, (int)pPlayer->vHitboxHeadScreen.y, 5, Height, iHealth, Color::LawnGreen(), Minus);
			}
			else if (Settings::Esp::esp_Health >= 4)
			{
				float flBoxes = std::ceil(pPlayer->iHealth / 10.f);
				float flX = x - 6;
				float flY = y - 1;
				float flHeight = Height / 10.f;
				float flMultiplier = 12 / 360.f;
				flMultiplier *= flBoxes - 1;
				Color ColHealth = Color::FromHSB(flMultiplier, 1, 1);

				g_pRender->DrawBox(flX, flY, 4, Height + 2, Color(80, 80, 80, 125));
				g_pRender->DrawOutlineBox(flX, flY, 4, Height + 2, Color::Black());
				g_pRender->DrawBox(flX + 1, flY, 2, flHeight * flBoxes + 1, ColHealth);

				for (int i = 0; i < 10; i++)
				{
					g_pRender->DrawLine(flX, flY + i * flHeight, flX + 4, flY + i * flHeight, Color::Black());
				}
			}
		}
	}

	if (Settings::Esp::esp_Armor >= 1)
	{
		Color Minus = Color::Red();

		if (pPlayer->Team == TEAM_CT)
		{
			Minus = CT_AR_ColorM;
		}
		else if (pPlayer->Team == TEAM_TT)
		{
			Minus = TT_AR_ColorM;
		}

		int iArmor = pPlayer->iArmor;

		if (iArmor)
		{
			if (Settings::Esp::esp_Armor == 1)
			{
				g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true,
					EspPlayerColor,
					to_string(iArmor).c_str());
				iHpAmY += 10;
			}
			if (Settings::Esp::esp_Armor == 2)
			{
				g_pRender->DrawHorBar(x, (int)vLineOrigin.y + iHpAmY, Width, 5, iArmor,
					Color::White(), Minus);
				iHpAmY += 6;
			}
			else if (Settings::Esp::esp_Armor >= 3)
			{
				g_pRender->DrawVerBar(x + Width + 1, (int)pPlayer->vHitboxHeadScreen.y, 5, Height, iArmor,
					Color::White(), Minus);
			}
		}
	}

	if (Settings::Esp::esp_Weapon && !pPlayer->WeaponName.empty())
	{
		string WeaponStr = pPlayer->WeaponName; WeaponStr.erase(0, 6);

		if (Settings::Esp::esp_Ammo && pPlayer->iWAmmo)
		{
			WeaponStr += " (";
			WeaponStr += to_string(pPlayer->iWAmmo);
			WeaponStr += ")";
		}

		g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspPlayerColor, WeaponStr.c_str());
		iHpAmY += 10;
	}

	if (Settings::Esp::esp_Distance && g_pPlayers->GetLocal()->bAlive)
	{
		int Distance = pPlayer->iDistance;
		g_pRender->Text((int)vLineOrigin.x, (int)vLineOrigin.y + iHpAmY, true, true, EspPlayerColor, to_string(Distance).c_str());
	}
}

void CEsp::DrawPlayerSkeleton(CPlayer* pPlayer)
{
	Color SkeletonColor = GetPlayerColor(pPlayer);

	for (BYTE IndexArray = 0; IndexArray < 18; IndexArray++)
	{
		DrawHitBoxLine(pPlayer->vHitboxSkeletonArray[IndexArray], SkeletonColor);
	}
}

void CEsp::DrawPlayerBulletTrace(CPlayer* pPlayer)
{
	Color EspColor = GetPlayerColor(pPlayer);

	if (!pPlayer->vBulletTraceArray[0].IsZero() && !pPlayer->vBulletTraceArray[1].IsZero())
	{
		g_pRender->DrawLine(
			(int)pPlayer->vBulletTraceArray[0].x, (int)pPlayer->vBulletTraceArray[0].y,
			(int)pPlayer->vBulletTraceArray[1].x, (int)pPlayer->vBulletTraceArray[1].y, EspColor);

		g_pRender->DrawFillBox((int)pPlayer->vBulletTraceArray[1].x - 2, (int)pPlayer->vBulletTraceArray[1].y - 2, 4, 4, EspColor);
	}
}

void CEsp::DrawHitBoxLine(Vector* vHitBoxArray, Color color)
{
	Vector vHitBoxOneScreen;
	Vector vHitBoxTwoScreen;

	if (vHitBoxArray[0].IsZero() || !vHitBoxArray[0].IsValid() || vHitBoxArray[1].IsZero() || !vHitBoxArray[1].IsValid())
		return;

	if (WorldToScreen(vHitBoxArray[0], vHitBoxOneScreen) && WorldToScreen(vHitBoxArray[1], vHitBoxTwoScreen))
	{
		g_pRender->DrawLine((int)vHitBoxOneScreen.x, (int)vHitBoxOneScreen.y,
			(int)vHitBoxTwoScreen.x, (int)vHitBoxTwoScreen.y, color);
	}
}

bool done = false;
void CEsp::NightMode()
{
	if (Settings::Esp::esp_NightMode)
	{
		if (!done)
		{
			static auto sv_skyname = Interfaces::GetConVar()->FindVar("sv_skyname");
			static auto r_DrawSpecificStaticProp = Interfaces::GetConVar()->FindVar("r_DrawSpecificStaticProp");
			r_DrawSpecificStaticProp->SetValue(1);
			sv_skyname->SetValue("sky_csgo_night02");

			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{
					pMaterial->ColorModulate(0.10, 0.10, 0.10);
				}
				if (strstr(group, "StaticProp"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{
					pMaterial->ColorModulate(0.30, 0.30, 0.30);
				}

				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
				}
				done = true;
			}

		}
	}
	else
	{
		if (done)
		{
			for (MaterialHandle_t i = Interfaces::MaterialSystem()->FirstMaterial(); i != Interfaces::MaterialSystem()->InvalidMaterial(); i = Interfaces::MaterialSystem()->NextMaterial(i))
			{
				IMaterial *pMaterial = Interfaces::MaterialSystem()->GetMaterial(i);

				if (!pMaterial)
					continue;

				const char* group = pMaterial->GetTextureGroupName();
				const char* name = pMaterial->GetName();

				if (strstr(group, "World textures"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "StaticProp"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(name, "models/props/de_dust/palace_bigdome"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
				if (strstr(name, "models/props/de_dust/palace_pillars"))
				{

					pMaterial->ColorModulate(1, 1, 1);
				}
				if (strstr(group, "Particle textures"))
				{
					pMaterial->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
				}
			}

			done = false;
		}
	}
}






































































































































































































































































































































































































































































































































































































































