#include "Gui.h"
#include "../Gui/memoryfonts.h"

using namespace Client;

//[enc_string_enable /]
//[junk_enable /]

ImFont* Tabfont;
ImFont* font;
ImFont* Titlefont;
ImFont* Iconfont;
ImFont* Namefont;

bool bIsGuiInitalize = false;
bool bIsGuiVisible = false;
WNDPROC WndProc_o = nullptr;
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

LRESULT WINAPI GUI_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

CGui::CGui() {}

CGui::~CGui()
{
	ImGui_ImplDX9_Shutdown();
}

void CGui::GUI_Init(IDirect3DDevice9 * pDevice)
{
	HWND hWindow = FindWindowA("Valve001", 0);

	ImGui_ImplDX9_Init(hWindow, pDevice);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	io.IniFilename = GuiFile.c_str();

	font = io.Fonts->AddFontFromMemoryCompressedTTF(
		Font_Font_data, Font_Font_size, 16.f);



	Iconfont = io.Fonts->AddFontFromMemoryCompressedTTF(
		Font_Icon_data, Font_Icon_size, 30.f);

	Namefont = io.Fonts->AddFontFromMemoryCompressedTTF(
		Font_name_data, Font_name_size, 18.f);

	style.Alpha = 1.0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 10.0f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 10.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 10.0f;
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(8, 8);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 10.0f;
	style.GrabMinSize = 10.f;
	style.GrabRounding = 5.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	blue();

	ImGui_ImplDX9_CreateDeviceObjects();

	WndProc_o = (WNDPROC)SetWindowLongA(hWindow, GWL_WNDPROC, (LONG)(LONG_PTR)GUI_WndProc);

	bIsGuiInitalize = true;
}

void CGui::GUI_Begin_Render()
{
	ImGui_ImplDX9_NewFrame();
}

void CGui::GUI_End_Render()
{
	ImGui::Render();
}

bool SendClientHello()
{
	CMsgClientHello Message;

	Message.set_client_session_need(1);
	Message.clear_socache_have_versions();

	void* ptr = malloc(Message.ByteSize() + 8);

	if (!ptr)
		return false;

	((uint32_t*)ptr)[0] = k_EMsgGCClientHello | ((DWORD)1 << 31);
	((uint32_t*)ptr)[1] = 0;

	Message.SerializeToArray((void*)((DWORD)ptr + 8), Message.ByteSize());

	bool result = Interfaces::SteamGameCoordinator()->SendMessage(k_EMsgGCClientHello | ((DWORD)1 << 31), ptr, Message.ByteSize() + 8) == k_EGCResultOK;

	free(ptr);

	return result;
}

bool SendMMHello()
{
	CMsgGCCStrike15_v2_MatchmakingClient2GCHello Message;
	void* ptr = malloc(Message.ByteSize() + 8);
	if (!ptr)
		return false;

	auto unMsgType = k_EMsgGCCStrike15_v2_MatchmakingClient2GCHello | ((DWORD)1 << 31);
	((uint32_t*)ptr)[0] = unMsgType;
	((uint32_t*)ptr)[1] = 0;

	Message.SerializeToArray((void*)((DWORD)ptr + 8), Message.ByteSize());

	bool result = Interfaces::SteamGameCoordinator()->SendMessage(k_EMsgGCCStrike15_v2_MatchmakingClient2GCHello | ((DWORD)1 << 31), ptr, Message.ByteSize() + 8) == k_EGCResultOK;

	free(ptr);
	return result;
}

LRESULT WINAPI GUI_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool is_down = false;
	static bool is_clicked = false;
	static bool check_closed = false;

	if (GUI_KEY_DOWN(VK_INSERT))
	{
		is_clicked = false;
		is_down = true;
	}
	else if (!GUI_KEY_DOWN(VK_INSERT) && is_down)
	{
		is_clicked = true;
		is_down = false;
	}
	else
	{
		is_clicked = false;
		is_down = false;
	}

	if (!bIsGuiVisible && !is_clicked && check_closed)
	{
		string msg = "cl_mouseenable " + to_string(!bIsGuiVisible);
		Interfaces::Engine()->ClientCmd_Unrestricted2(msg.c_str());
		check_closed = false;
	}

	if (is_clicked)
	{
		bIsGuiVisible = !bIsGuiVisible;

		string msg = "cl_mouseenable " + to_string(!bIsGuiVisible);
		Interfaces::Engine()->ClientCmd_Unrestricted2(msg.c_str());

		if (!check_closed)
			check_closed = true;
	}

	if (bIsGuiVisible && ImGui_ImplDX9_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(WndProc_o, hwnd, uMsg, wParam, lParam);
}

void CGui::GUI_Draw_Elements()
{
	// if (!bIsGuiInitalize || Interfaces::Engine()->IsTakingScreenshot() || !Interfaces::Engine()->IsActiveApp()) - screenshot shit
	if (!bIsGuiInitalize || !Interfaces::Engine()->IsActiveApp())
		return;

	g_pGui->GUI_Begin_Render();

	ImGui::GetIO().MouseDrawCursor = bIsGuiVisible;

	bool bOpenTimer = (bIsGuiVisible || (bC4Timer && iC4Timer));

	if (Settings::Misc::misc_Spectators) g_pMisc->OnRenderSpectatorList();

	if (g_pEsp && Settings::Esp::esp_BombTimer && bOpenTimer)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(125.f, 30.f));

		if (ImGui::Begin("bomb timer", &bOpenTimer,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
		{
			ImGui::Text(C4_TIMER_STRING, g_pEsp->fC4Timer);
			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	if (Settings::Misc::misc_SkinChanger && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);
		ImGui::SetNextWindowSize(ImVec2(500.f, 340.f));

		if (ImGui::Begin("skinchanger", &Settings::Misc::misc_SkinChanger,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{

			const char* quality_items[] =
			{
				"normal","genuine","vintage","unusual","community","developer",
				"self-made","customized","strange","completed","tournament"
			};

			const char* gloves_listbox_items[49] =
			{
				"default",
				"sport gloves | superconductor",
				"sport gloves | pandora's box",
				"sport gloves | hedge maze",
				"sport gloves | arid",
				"sport gloves | vice",
				"sport gloves | omega",
				"sport gloves | bronze morph",
				"sport gloves | amphibious",
				"moto gloves | eclipse",
				"moto gloves | spearmint",
				"moto gloves | boom!",
				"moto gloves | cool mint",
				"moto gloves | polygon",
				"moto gloves | transport",
				"moto gloves | turtle",
				"moto gloves | pow",
				"specialist gloves | crimson kimono",
				"specialist gloves | emerald web",
				"specialist gloves | foundation",
				"specialist gloves | forest ddpat",
				"specialist gloves | mogul",
				"specialist gloves | fade",
				"specialist gloves | buckshot",
				"specialist gloves | crimson web",
				"driver gloves | lunar weave",
				"driver gloves | convoy",
				"driver gloves | crimson weave",
				"driver gloves | diamondback",
				"driver gloves | racing green",
				"driver gloves | overtake",
				"driver gloves | imperial plad",
				"driver gloves | king snake",
				"hand wraps | leather",
				"hand wraps | spruce ddpat",
				"hand wraps | badlands",
				"hand wraps | slaughter",
				"hand wraps | aboreal",
				"hand wraps | duct tape",
				"hand wraps | overprint",
				"hand wraps | cobalt skulls",
				"bloodhound gloves | charred",
				"bloodhound gloves | snakebite",
				"bloodhound gloves | bronzed",
				"bloodhound gloves | guerrilla",
				"hydra gloves | case hardened",
				"hydra gloves | rattler",
				"hydra gloves | mangrove",
				"hydra gloves | emerald",
			};
			//[enc_string_enable /]

			const char* skins_items[] =
			{
				"", "",  "2: groundwater","3: candy apple", "",
				"5: forest ddpat","6: arctic camo",  "",
				"8: desert storm","9: bengal tiger","10: copperhead",
				"11: skulls","12: crimson web","13: blue streak","14: red laminate"
				,"15: gunsmoke","16: jungle tiger","17: urban ddpat",  "",
				"", "20: virus","21: granite marbleized","22: contrast spray",
				"",  "", "25: forest leaves","26: lichen dashed",
				"27: bone mask","28: anodized navy",  "",  "30: snake camo",
				"",  "32: silver","33: hot rod","34: metallic ddpat",  "",
				"36: ossified","37: blaze","38: fade","39: bulldozer","40: night",
				"41: copper","42: blue steel","43: stained","44: case hardened",
				"",  "46: contractor","47: colony","48: dragon tattoo",
				"",   "",  "51: lightning strike",  "",
				"",   "",   "",   "",   "",
				"",    "59: slaughter","60: dark water"
				,"61: hypnotic","62: bloomstick",  "",   ""
				,   "",   "",  "67: cold blooded",  "",   ""
				,  "70: carbon fiber","71: scorpion","72: safari mesh","73: wings","74: polar camo"
				,"75: blizzard marbleized","76: winter forest","77: boreal forest","78: forest night"
				,  "",   "",   "",   "",  "83: orange ddpat","84: pink ddpat"
				,  "",   "",   "",   "",  "",  "90: mudder",  ""
				,  "92: cyanospatter","93: caramel",  "", "95: grassland","96: blue spruce",  ""
				,  "98: ultraviolet","99: sand dune","100: storm","101: tornado","102: whiteout",  ""
				,  "104: grassland leaves",  "",   "", "107: polar mesh",  "",   ""
				, "110: condemned","111: glacier mesh",  "",   "",   "",   "",  "116: sand mesh",  "",   "", "119: sage spray",  "",   "", "122: jungle spray",  "",  "124: sand spray",  ""
				,  "",  "",  "",  "",  "",  "",  "",  "",  "", "135: urban perforated"
				,"136: waves perforated",  "",   "",   "",  "", "141: orange peel",  "",  "143: urban masked", "", "", "", "147: jungle dashed"
				,"148: sand dashed","149: urban dashed", "", "151: jungle", "", "153: demolition","154: afterimage","155: bullet rain","156: death by kitty","157: palm","158: walnut","159: brass", "", "", "162: splash", "","164: modern hunter","165: splash jam","166: blaze orange","167: radiation hazard","168: nuclear threat","169: fallout warning","170: predator","171: irradiated alert","172: black laminate", "","174: boom","175: scorched","176: faded zebra","177: memento","178: doomkitty","179: nuclear threat","180: fire serpent","181: corticera","182: emerald dragon","183: overgrowth","184: corticera","185: golden koi","186: wave spray","187: zirka","188: graven","189: bright water","190: black limba","191: tempest","192: shattered","193: bone pile","194: spitfire","195: demeter","196: emerald","197: anodized navy","198: hazard","199: dry season","200: mayan dreams","201: palm","202: jungle ddpat","203: rust coat","204: mosaico","205: jungle","206: tornado","207: facets","208: sand dune","209: groundwater","210: anodized gunmetal","211: ocean foam","212: graphite","213: ocean foam","214: graphite","215: x-ray","216: blue titanium","217: blood tiger","218: hexane","219: hive","220: hemoglobin","221: serum","222: blood in the water","223: nightshade","224: water sigil","225: ghost camo","226: blue laminate","227: electric hive","228: blind spot","229: azure zebra","230: steel disruption","231: cobalt disruption","232: crimson web","233: tropical storm","234: ash wood","235: varicamo","236: night ops","237: urban rubble","238: varicamo blue", "", "240: calicamo","241: hunting blind","242: army mesh","243: gator mesh","244: teardown","245: army recon","246: amber fade","247: damascus steel","248: red quartz","249: cobalt quartz","250: full stop","251: pit viper","252: silver quartz","253: acid fade","254: nitro","255: asiimov","256: the kraken","257: guardian","258: mehndi","259: redline","260: pulse","261: marina","262: rose iron","263: rising skull","264: sandstorm","265: kami","266: magma","267: cobalt halftone","268: tread plate","269: the fuschia is now","270: victoria","271: undertow","272: titanium bit","273: heirloom","274: copper galaxy","275: red fragcam","276: panther","277: stainless","278: blue fissure","279: asiimov","280: chameleon","281: corporal","282: redline","283: trigon","284: heat","285: terrain","286: antique","287: pulse","288: sergeant","289: sandstorm","290: guardian","291: heaven guard", "", "293: death rattle","294: green apple","295: franklin","296: meteorite","297: tuxedo","298: army sheen","299: caged steel","300: emerald pinstripe","301: atomic alloy","302: vulcan","303: isaac","304: slashed","305: torque","306: antique","307: retribution","308: kami","309: howl","310: curse","311: desert warfare","312: cyrex","313: orion","314: heaven guard","315: poison dart","316: jaguar","317: bratatat","318: road rash","319: detour","320: red python","321: master piece","322: nitro","323: rust coat", "", "325: chalice","326: knight","327: chainmail","328: hand cannon","329: dark age","330: briar", "", "332: royal blue","333: indigo","334: twist","335: module","336: desert-strike","337: tatter","338: pulse","339: caiman","340: jet set","341: first class","342: leather","343: commuter","344: dragon lore","345: first class","346: coach class","347: pilot","348: red leather","349: osiris","350: tigris","351: conspiracy","352: fowl play","353: water elemental","354: urban hazard","355: desert-strike","356: koi","357: ivory","358: supernova","359: asiimov","360: cyrex","361: abyss","362: labyrinth","363: traveler","364: business class","365: olive plaid","366: green plaid","367: reactor","368: setting sun","369: nuclear waste","370: bone machine","371: styx","372: nuclear garden","373: contamination","374: toxic","375: radiation hazard","376: chemical green","377: hot shot","378: fallout warning","379: cerberus","380: wasteland rebel","381: grinder","382: murky","383: basilisk","384: griffin","385: firestarter","386: dart","387: urban hazard","388: cartel","389: fire elemental","390: highwayman","391: cardiac","392: delusion","393: tranquility","394: cartel","395: man-o'-war","396: urban shock","397: naga","398: chatterbox","399: catacombs","400: 龍王 (dragon king)","401: system lock","402: malachite","403: deadly poison","404: muertos","405: serenity","406: grotto","407: quicksilver","", "409: tiger tooth","410: damascus steel","411: damascus steel", "", "413: marble fade","414: rust coat","415: doppler","416: doppler","417: doppler","418: doppler","419: doppler","420: doppler","421: doppler","422: elite build","423: armor core","424: worm god","425: bronze deco","426: valence","427: monkey business","428: eco","429: djinn","430: hyper beast","431: heat","432: man-o'-war","433: neon rider","434: origami","435: pole position","436: grand prix","437: twilight galaxy","438: chronos","439: hades","440: icarus fell","441: minotaur's labyrinth","442: asterion","443: pathfinder","444: daedalus","445: hot rod","446: medusa","447: duelist","448: pandora's box","449: poseidon","450: moon in libra","451: sun in leo","452: shipping forecast","453: emerald","454: para green","455: akihabara accept","456: hydroponic","457: bamboo print","458: bamboo shadow","459: bamboo forest","460: aqua terrace", "", "462: counter terrace","463: terrace","464: neon kimono","465: orange kimono","466: crimson kimono","467: mint kimono","468: midnight storm","469: sunset storm 壱","470: sunset storm 弐","471: daybreak","472: impact drill","473: seabird","474: aquamarine revenge","475: hyper beast","476: yellow jacket","477: neural net","478: rocket pop","479: bunsen burner","480: evil daimyo","481: nemesis","482: ruby poison dart","483: loudmouth","484: ranger","485: handgun","486: elite build","487: cyrex","488: riot","489: torque","490: frontside misty","491: dualing dragons","492: survivor z","493: flux","494: stone cold","495: wraiths","496: nebula crusader","497: golden coil","498: rangeen","499: cobalt core","500: special delivery","501: wingshot","502: green marine","503: big iron","504: kill confirmed","505: scumbria","506: point disarray","507: ricochet","508: fuel rod","509: corinthian","510: retrobution","511: the executioner","512: royal paladin", "", "514: power loader","515: imperial","516: shapewood","517: yorick","518: outbreak","519: tiger moth","520: avalanche","521: teclu burner","522: fade","523: amber fade","524: fuel injector","525: elite build","526: photic zone","527: kumicho dragon","528: cartel","529: valence","530: triumvirate", "", "532: royal legion","533: the battlestar","534: lapis gator","535: praetorian","536: impire","537: hyper beast","538: necropos","539: jambiya","540: lead conduit","541: fleet flock","542: judgement of anubis","543: red astor","544: ventilators","545: orange crash","546: firefight","547: spectre","548: chantico's fire","549: bioleak","550: oceanic","551: asiimov","552: fubar","553: atlas","554: ghost crusader","555: re-entry","556: primal saber","557: black tie","558: lore","559: lore","560: lore","561: lore","562: lore","563: black laminate","564: black laminate","565: black laminate","566: black laminate","567: black laminate","568: gamma doppler","569: gamma doppler","570: gamma doppler","571: gamma doppler","572: gamma doppler","573: autotronic","574: autotronic","575: autotronic","576: autotronic","577: autotronic","578: bright water","579: bright water","580: freehand","581: freehand","582: freehand","583: aristocrat","584: phobos","585: violent daimyo","586: wasteland rebel","587: mecha industries","588: desolate space","589: carnivore","590: exo","591: imperial dragon","592: iron clad","593: chopper","594: harvester","595: reboot","596: limelight","597: bloodsport","598: aerial","599: ice cap","600: neon revolution","601: syd mead","602: imprint","603: directive","604: roll cage","605: scumbria","606: ventilator","607: weasel","608: petroglyph","609: airlock","610: dazzle","611: grim","612: powercore","613: triarch","614: fuel injector","615: briefing","616: slipstream","617: doppler","618: doppler","619: doppler","620: ultraviolet","621: ultraviolet","622: polymer","623: ironwork","624: dragonfire","625: royal consorts","626: mecha industries","627: cirrus","628: stinger","629: black sand","630: sand scale","631: flashback","632: buzz kill","633: sonar","634: gila","635: turf","636: shallow grave","637: cyrex","638: wasteland princess","639: bloodsport","640: fever dream","641: jungle slipstream","642: blueprint","643: xiangliu","644: decimator","645: oxide blaze","646: capillary","647: crimson tsunami","648: emerald poison dart","649: akoben","650: ripple","651: last dive","652: scaffold","653: neo-noir","654: seasons","655: zander","656: orbit mk01","657: blueprint","658: cobra strike","659: macabre","660: hyper beast","661: sugar rush","662: oni taiji","663: briefing","664: hellfire","665: aloha","666: hard water","667: woodsman","668: red rock","669: death grip","670: death's head","671: cut out","672: metal flowers","673: morris","674: triqua","675: the empress","676: high roller","677: hunter","678: see ya later","679: goo","680: off world","681: leaded glass","682: oceanic","683: llama cannon","684: cracked opal","685: jungle slipstream","686: phantom","687: tacticat","688: exposure","689: ziggy"
			};

			static const char* weapons[] = {
				"none",
				"1 - desert eagle",
				"2 - dual berettas",
				"3 - five seven",
				"4 - glock",
				"",
				"",
				"7 - ak47",
				"8 - aug",
				"9 - awp",
				"10 - famas",
				"11 - g3sg1",
				"",
				"13 - galil ar",
				"14 - m249",
				"",
				"16 - m4a4",
				"17 - mac10",
				"",
				"19 - p90",
				"",
				"",
				"",
				"",
				"24 - ump45",
				"25 - xm1014",
				"26 - ppbizon",
				"27 - mag7",
				"28 - negev",
				"29 - sawedoff",
				"30 - tec9",
				" ",
				"32 - p2000",
				"33 - mp7",
				"34 - mp9",
				"35 - nova",
				"36 - p250",
				"38 - scar20",
				"39 - sg553",
				"40 - scout",
			};
			static int itemDefinitionIndex = 0;

			ImGui::Text("skinchanger");


			ImGui::Text("current weapon: %s", pWeaponData[iWeaponID]);

			ImGui::PushItemWidth(362.f);

			static int iOldWeaponID = -1;

			ImGui::InputInt("Weapon##WeaponSelect", &iWeaponID);
			ImGui::Combo("weapons", &itemDefinitionIndex, weapons, IM_ARRAYSIZE(weapons));

			iWeaponSelectIndex = pWeaponItemIndexData[iWeaponID];

			if (iOldWeaponID != iWeaponID)
				iWeaponSelectSkinIndex = GetWeaponSkinIndexFromPaintKit(g_SkinChangerCfg[iWeaponSelectIndex].nFallbackPaintKit);

			iOldWeaponID = iWeaponID;

			string WeaponSkin = pWeaponData[iWeaponID];
			WeaponSkin += " skin";

			ImGui::ComboBoxArray(WeaponSkin.c_str(), &iWeaponSelectSkinIndex, WeaponSkins[iWeaponID].SkinNames);

			ImGui::Combo("weapon quality", &g_SkinChangerCfg[pWeaponItemIndexData[iWeaponID]].iEntityQuality, quality_items, IM_ARRAYSIZE(quality_items));
			ImGui::SliderFloat("weapon wear", &g_SkinChangerCfg[pWeaponItemIndexData[iWeaponID]].flFallbackWear, 0.001f, 1.f);
			ImGui::InputInt("weapon seed", &g_SkinChangerCfg[pWeaponItemIndexData[iWeaponID]].nFallbackSeed, 1, 9999999999999999999, ImGuiInputTextFlags_CharsDecimal);
			ImGui::InputInt("weapon stattrak", &g_SkinChangerCfg[pWeaponItemIndexData[iWeaponID]].nFallbackStatTrak, 1, 100, ImGuiInputTextFlags_CharsDecimal);
			ImGui::Combo("weapon skin", &g_SkinChangerCfg[pWeaponItemIndexData[iWeaponID]].nFallbackPaintKit, skins_items, IM_ARRAYSIZE(skins_items));
			ImGui::InputInt("weapon skin id", &g_SkinChangerCfg[pWeaponItemIndexData[iWeaponID]].nFallbackPaintKit, 1, 689, ImGuiInputTextFlags_CharsDecimal);
			ImGui::Checkbox("skin filter list", &Settings::Misc::skinids);


			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Combo("gloves", &Settings::Skin::gloves_skin, gloves_listbox_items,
				IM_ARRAYSIZE(gloves_listbox_items));


			ImGui::PopItemWidth();

			if (ImGui::Button("Apply##Skin"))
			{
				ForceFullUpdate();
			}
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	if (Settings::Misc::misc_KnifeChanger && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(500.f, 380.f));

		if (ImGui::Begin("knifechanger", &Settings::Misc::misc_KnifeChanger,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{

			const char* knife_models_items[] =
			{
				"default","bayonet","flip","gut","karambit" ,"m9 bayonet",
				"huntsman","falchion","bowie","butterfly","shadow daggers"
			};

			const char* quality_items[] =
			{
				"normal","genuine","vintage","unusual","community","developer",
				"self-made","customized","strange","completed","tournament"
			};

			const char* skins_items[] =
			{
				"", "",  "2: groundwater","3: candy apple", "",
				"5: forest ddpat","6: arctic camo",  "",
				"8: desert storm","9: bengal tiger","10: copperhead",
				"11: skulls","12: crimson web","13: blue streak","14: red laminate"
				,"15: gunsmoke","16: jungle tiger","17: urban ddpat",  "",
				"", "20: virus","21: granite marbleized","22: contrast spray",
				"",  "", "25: forest leaves","26: lichen dashed",
				"27: bone mask","28: anodized navy",  "",  "30: snake camo",
				"",  "32: silver","33: hot rod","34: metallic ddpat",  "",
				"36: ossified","37: blaze","38: fade","39: bulldozer","40: night",
				"41: copper","42: blue steel","43: stained","44: case hardened",
				"",  "46: contractor","47: colony","48: dragon tattoo",
				"",   "",  "51: lightning strike",  "",
				"",   "",   "",   "",   "",
				"",    "59: slaughter","60: dark water"
				,"61: hypnotic","62: bloomstick",  "",   ""
				,   "",   "",  "67: cold blooded",  "",   ""
				,  "70: carbon fiber","71: scorpion","72: safari mesh","73: wings","74: polar camo"
				,"75: blizzard marbleized","76: winter forest","77: boreal forest","78: forest night"
				,  "",   "",   "",   "",  "83: orange ddpat","84: pink ddpat"
				,  "",   "",   "",   "",  "",  "90: mudder",  ""
				,  "92: cyanospatter","93: caramel",  "", "95: grassland","96: blue spruce",  ""
				,  "98: ultraviolet","99: sand dune","100: storm","101: tornado","102: whiteout",  ""
				,  "104: grassland leaves",  "",   "", "107: polar mesh",  "",   ""
				, "110: condemned","111: glacier mesh",  "",   "",   "",   "",  "116: sand mesh",  "",   "", "119: sage spray",  "",   "", "122: jungle spray",  "",  "124: sand spray",  ""
				,  "",  "",  "",  "",  "",  "",  "",  "",  "", "135: urban perforated"
				,"136: waves perforated",  "",   "",   "",  "", "141: orange peel",  "",  "143: urban masked", "", "", "", "147: jungle dashed"
				,"148: sand dashed","149: urban dashed", "", "151: jungle", "", "153: demolition","154: afterimage","155: bullet rain","156: death by kitty","157: palm","158: walnut","159: brass", "", "", "162: splash", "","164: modern hunter","165: splash jam","166: blaze orange","167: radiation hazard","168: nuclear threat","169: fallout warning","170: predator","171: irradiated alert","172: black laminate", "","174: boom","175: scorched","176: faded zebra","177: memento","178: doomkitty","179: nuclear threat","180: fire serpent","181: corticera","182: emerald dragon","183: overgrowth","184: corticera","185: golden koi","186: wave spray","187: zirka","188: graven","189: bright water","190: black limba","191: tempest","192: shattered","193: bone pile","194: spitfire","195: demeter","196: emerald","197: anodized navy","198: hazard","199: dry season","200: mayan dreams","201: palm","202: jungle ddpat","203: rust coat","204: mosaico","205: jungle","206: tornado","207: facets","208: sand dune","209: groundwater","210: anodized gunmetal","211: ocean foam","212: graphite","213: ocean foam","214: graphite","215: x-ray","216: blue titanium","217: blood tiger","218: hexane","219: hive","220: hemoglobin","221: serum","222: blood in the water","223: nightshade","224: water sigil","225: ghost camo","226: blue laminate","227: electric hive","228: blind spot","229: azure zebra","230: steel disruption","231: cobalt disruption","232: crimson web","233: tropical storm","234: ash wood","235: varicamo","236: night ops","237: urban rubble","238: varicamo blue", "", "240: calicamo","241: hunting blind","242: army mesh","243: gator mesh","244: teardown","245: army recon","246: amber fade","247: damascus steel","248: red quartz","249: cobalt quartz","250: full stop","251: pit viper","252: silver quartz","253: acid fade","254: nitro","255: asiimov","256: the kraken","257: guardian","258: mehndi","259: redline","260: pulse","261: marina","262: rose iron","263: rising skull","264: sandstorm","265: kami","266: magma","267: cobalt halftone","268: tread plate","269: the fuschia is now","270: victoria","271: undertow","272: titanium bit","273: heirloom","274: copper galaxy","275: red fragcam","276: panther","277: stainless","278: blue fissure","279: asiimov","280: chameleon","281: corporal","282: redline","283: trigon","284: heat","285: terrain","286: antique","287: pulse","288: sergeant","289: sandstorm","290: guardian","291: heaven guard", "", "293: death rattle","294: green apple","295: franklin","296: meteorite","297: tuxedo","298: army sheen","299: caged steel","300: emerald pinstripe","301: atomic alloy","302: vulcan","303: isaac","304: slashed","305: torque","306: antique","307: retribution","308: kami","309: howl","310: curse","311: desert warfare","312: cyrex","313: orion","314: heaven guard","315: poison dart","316: jaguar","317: bratatat","318: road rash","319: detour","320: red python","321: master piece","322: nitro","323: rust coat", "", "325: chalice","326: knight","327: chainmail","328: hand cannon","329: dark age","330: briar", "", "332: royal blue","333: indigo","334: twist","335: module","336: desert-strike","337: tatter","338: pulse","339: caiman","340: jet set","341: first class","342: leather","343: commuter","344: dragon lore","345: first class","346: coach class","347: pilot","348: red leather","349: osiris","350: tigris","351: conspiracy","352: fowl play","353: water elemental","354: urban hazard","355: desert-strike","356: koi","357: ivory","358: supernova","359: asiimov","360: cyrex","361: abyss","362: labyrinth","363: traveler","364: business class","365: olive plaid","366: green plaid","367: reactor","368: setting sun","369: nuclear waste","370: bone machine","371: styx","372: nuclear garden","373: contamination","374: toxic","375: radiation hazard","376: chemical green","377: hot shot","378: fallout warning","379: cerberus","380: wasteland rebel","381: grinder","382: murky","383: basilisk","384: griffin","385: firestarter","386: dart","387: urban hazard","388: cartel","389: fire elemental","390: highwayman","391: cardiac","392: delusion","393: tranquility","394: cartel","395: man-o'-war","396: urban shock","397: naga","398: chatterbox","399: catacombs","400: 龍王 (dragon king)","401: system lock","402: malachite","403: deadly poison","404: muertos","405: serenity","406: grotto","407: quicksilver","", "409: tiger tooth","410: damascus steel","411: damascus steel", "", "413: marble fade","414: rust coat","415: doppler","416: doppler","417: doppler","418: doppler","419: doppler","420: doppler","421: doppler","422: elite build","423: armor core","424: worm god","425: bronze deco","426: valence","427: monkey business","428: eco","429: djinn","430: hyper beast","431: heat","432: man-o'-war","433: neon rider","434: origami","435: pole position","436: grand prix","437: twilight galaxy","438: chronos","439: hades","440: icarus fell","441: minotaur's labyrinth","442: asterion","443: pathfinder","444: daedalus","445: hot rod","446: medusa","447: duelist","448: pandora's box","449: poseidon","450: moon in libra","451: sun in leo","452: shipping forecast","453: emerald","454: para green","455: akihabara accept","456: hydroponic","457: bamboo print","458: bamboo shadow","459: bamboo forest","460: aqua terrace", "", "462: counter terrace","463: terrace","464: neon kimono","465: orange kimono","466: crimson kimono","467: mint kimono","468: midnight storm","469: sunset storm 壱","470: sunset storm 弐","471: daybreak","472: impact drill","473: seabird","474: aquamarine revenge","475: hyper beast","476: yellow jacket","477: neural net","478: rocket pop","479: bunsen burner","480: evil daimyo","481: nemesis","482: ruby poison dart","483: loudmouth","484: ranger","485: handgun","486: elite build","487: cyrex","488: riot","489: torque","490: frontside misty","491: dualing dragons","492: survivor z","493: flux","494: stone cold","495: wraiths","496: nebula crusader","497: golden coil","498: rangeen","499: cobalt core","500: special delivery","501: wingshot","502: green marine","503: big iron","504: kill confirmed","505: scumbria","506: point disarray","507: ricochet","508: fuel rod","509: corinthian","510: retrobution","511: the executioner","512: royal paladin", "", "514: power loader","515: imperial","516: shapewood","517: yorick","518: outbreak","519: tiger moth","520: avalanche","521: teclu burner","522: fade","523: amber fade","524: fuel injector","525: elite build","526: photic zone","527: kumicho dragon","528: cartel","529: valence","530: triumvirate", "", "532: royal legion","533: the battlestar","534: lapis gator","535: praetorian","536: impire","537: hyper beast","538: necropos","539: jambiya","540: lead conduit","541: fleet flock","542: judgement of anubis","543: red astor","544: ventilators","545: orange crash","546: firefight","547: spectre","548: chantico's fire","549: bioleak","550: oceanic","551: asiimov","552: fubar","553: atlas","554: ghost crusader","555: re-entry","556: primal saber","557: black tie","558: lore","559: lore","560: lore","561: lore","562: lore","563: black laminate","564: black laminate","565: black laminate","566: black laminate","567: black laminate","568: gamma doppler","569: gamma doppler","570: gamma doppler","571: gamma doppler","572: gamma doppler","573: autotronic","574: autotronic","575: autotronic","576: autotronic","577: autotronic","578: bright water","579: bright water","580: freehand","581: freehand","582: freehand","583: aristocrat","584: phobos","585: violent daimyo","586: wasteland rebel","587: mecha industries","588: desolate space","589: carnivore","590: exo","591: imperial dragon","592: iron clad","593: chopper","594: harvester","595: reboot","596: limelight","597: bloodsport","598: aerial","599: ice cap","600: neon revolution","601: syd mead","602: imprint","603: directive","604: roll cage","605: scumbria","606: ventilator","607: weasel","608: petroglyph","609: airlock","610: dazzle","611: grim","612: powercore","613: triarch","614: fuel injector","615: briefing","616: slipstream","617: doppler","618: doppler","619: doppler","620: ultraviolet","621: ultraviolet","622: polymer","623: ironwork","624: dragonfire","625: royal consorts","626: mecha industries","627: cirrus","628: stinger","629: black sand","630: sand scale","631: flashback","632: buzz kill","633: sonar","634: gila","635: turf","636: shallow grave","637: cyrex","638: wasteland princess","639: bloodsport","640: fever dream","641: jungle slipstream","642: blueprint","643: xiangliu","644: decimator","645: oxide blaze","646: capillary","647: crimson tsunami","648: emerald poison dart","649: akoben","650: ripple","651: last dive","652: scaffold","653: neo-noir","654: seasons","655: zander","656: orbit mk01","657: blueprint","658: cobra strike","659: macabre","660: hyper beast","661: sugar rush","662: oni taiji","663: briefing","664: hellfire","665: aloha","666: hard water","667: woodsman","668: red rock","669: death grip","670: death's head","671: cut out","672: metal flowers","673: morris","674: triqua","675: the empress","676: high roller","677: hunter","678: see ya later","679: goo","680: off world","681: leaded glass","682: oceanic","683: llama cannon","684: cracked opal","685: jungle slipstream","686: phantom","687: tacticat","688: exposure","689: ziggy"
			};

			ImGui::Text("KnifeChanger");

			ImGui::Combo("knife ct model", &Settings::Skin::knf_ct_model, knife_models_items, IM_ARRAYSIZE(knife_models_items));
			ImGui::Combo("knife tt model", &Settings::Skin::knf_tt_model, knife_models_items, IM_ARRAYSIZE(knife_models_items));
			ImGui::Combo("knife ct skin combo", &Settings::Skin::knf_ct_skin, skins_items, IM_ARRAYSIZE(skins_items));
			ImGui::InputInt("knife ct skin input", &Settings::Skin::knf_ct_skin, 1, 689, ImGuiInputTextFlags_CharsDecimal);
			ImGui::Combo("knife tt skin combo", &Settings::Skin::knf_tt_skin, skins_items, IM_ARRAYSIZE(skins_items));
			ImGui::InputInt("knife tt skin input", &Settings::Skin::knf_tt_skin, 1, 689, ImGuiInputTextFlags_CharsDecimal);
			ImGui::Checkbox("skin filter list", &Settings::Misc::skinids);

			static int iSelectKnifeCTSkinIndex = -1;
			static int iSelectKnifeTTSkinIndex = -1;

			int iKnifeCTModelIndex = Settings::Skin::knf_ct_model;
			int iKnifeTTModelIndex = Settings::Skin::knf_tt_model;

			static int iOldKnifeCTModelIndex = -1;
			static int iOldKnifeTTModelIndex = -1;

			if (iOldKnifeCTModelIndex != iKnifeCTModelIndex && Settings::Skin::knf_ct_model)
				iSelectKnifeCTSkinIndex = GetKnifeSkinIndexFromPaintKit(Settings::Skin::knf_ct_skin, false);

			if (iOldKnifeTTModelIndex != iKnifeTTModelIndex && Settings::Skin::knf_tt_model)
				iSelectKnifeTTSkinIndex = GetKnifeSkinIndexFromPaintKit(Settings::Skin::knf_ct_skin, true);

			iOldKnifeCTModelIndex = iKnifeCTModelIndex;
			iOldKnifeTTModelIndex = iKnifeTTModelIndex;

			string KnifeCTModel = knife_models_items[Settings::Skin::knf_ct_model];
			string KnifeTTModel = knife_models_items[Settings::Skin::knf_tt_model];

			KnifeCTModel += " Skin##KCT";
			KnifeTTModel += " Skin##KTT";

			ImGui::SliderFloat("knife ct wear", &g_SkinChangerCfg[WEAPON_KNIFE].flFallbackWear, 0.001f, 1.f);
			ImGui::Combo("knife ct quality", &g_SkinChangerCfg[WEAPON_KNIFE].iEntityQuality, quality_items, IM_ARRAYSIZE(quality_items));
			ImGui::InputInt("knife ct seed", &g_SkinChangerCfg[WEAPON_KNIFE].nFallbackSeed, 1, 9999999999999999999, ImGuiInputTextFlags_CharsDecimal);
			ImGui::ComboBoxArray(KnifeCTModel.c_str(), &iSelectKnifeCTSkinIndex, KnifeSkins[iKnifeCTModelIndex].SkinNames);


			ImGui::SliderFloat("knife tt wear", &g_SkinChangerCfg[WEAPON_KNIFE_T].flFallbackWear, 0.001f, 1.f);
			ImGui::Combo("knife tt quality", &g_SkinChangerCfg[WEAPON_KNIFE_T].iEntityQuality, quality_items, IM_ARRAYSIZE(quality_items));
			ImGui::InputInt("knife t seed", &g_SkinChangerCfg[WEAPON_KNIFE_T].nFallbackSeed, 1, 9999999999999999999, ImGuiInputTextFlags_CharsDecimal);
			ImGui::ComboBoxArray(KnifeTTModel.c_str(), &iSelectKnifeTTSkinIndex, KnifeSkins[iKnifeTTModelIndex].SkinNames);

			if (ImGui::Button("Apply##Skin"))
			{
				ForceFullUpdate();
			}
			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	/*
	if (Settings::Misc::misc_StickerChanger && bIsGuiVisible)
	{
	ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

	ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

	ImGui::SetNextWindowSize(ImVec2(500.f, 295.f));

	Settings::Sticker::stickerSafeWeapon = SafeWeaponID();
	Stick[Settings::Sticker::stickerSafeWeapon].StickersEnabled = true;

	if (ImGui::Begin("stickerchanger", &Settings::Misc::misc_StickerChanger,
	ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
	static int iSlot = 0;
	const char* slots[] ={ "back", "back-mid", "front-mid", "front" };

	ImGui::Combo("Slot", &iSlot, slots, IM_ARRAYSIZE(slots));
	ImGui::SliderFloat("Wear ", &Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear, 0.f, 1.f, "%.3f");
	ImGui::SliderFloat("Size", &Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale, 0.f, 1.f, "%.3f");
	ImGui::SliderInt("Rotate", &Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation, 0, 360);
	ImGui::InputInt("ID", &Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID);

	if (ImGui::Button("accept stickers##Skin"))
	{
	switch (Settings::Sticker::stickerSafeWeapon)
	{
	case 1:
	Settings::Sticker::sticker_deserteagle_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_deserteagle_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_deserteagle_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_deserteagle_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_deserteagle_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 2:
	Settings::Sticker::sticker_elites_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_elites_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_elites_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_elites_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_elites_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 3:
	Settings::Sticker::sticker_fiveseven_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_fiveseven_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_fiveseven_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_fiveseven_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_fiveseven_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 4:
	Settings::Sticker::sticker_glock_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_glock_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_glock_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_glock_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_glock_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 7:
	Settings::Sticker::sticker_ak_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_ak_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_ak_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_ak_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_ak_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 8:
	Settings::Sticker::sticker_aug_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_aug_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_aug_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_aug_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_aug_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 9:
	Settings::Sticker::sticker_awp_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_awp_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_awp_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_awp_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_awp_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 10:
	Settings::Sticker::sticker_famas_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_famas_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_famas_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_famas_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_famas_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 11:
	Settings::Sticker::sticker_g35g1_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_g35g1_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_g35g1_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_g35g1_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_g35g1_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 13:
	Settings::Sticker::sticker_galil_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_galil_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_galil_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_galil_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_galil_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 14:
	Settings::Sticker::sticker_m249_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_m249_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_m249_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_m249_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_m249_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 16:
	Settings::Sticker::sticker_m4a4_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_m4a4_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_m4a4_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_m4a4_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_m4a4_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 17:
	Settings::Sticker::sticker_mac10_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_mac10_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_mac10_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_mac10_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_mac10_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 19:
	Settings::Sticker::sticker_p90_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_p90_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_p90_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_p90_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_p90_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 24:
	Settings::Sticker::sticker_ump_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_ump_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_ump_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_ump_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_ump_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 25:
	Settings::Sticker::sticker_xm_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_xm_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_xm_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_xm_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_xm_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 26:
	Settings::Sticker::sticker_bizon_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_bizon_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_bizon_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_bizon_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_bizon_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 27:
	Settings::Sticker::sticker_mag7_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_mag7_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_mag7_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_mag7_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_mag7_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 28:
	Settings::Sticker::sticker_negev_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_negev_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_negev_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_negev_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_negev_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 29:
	Settings::Sticker::sticker_sawedoff_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_sawedoff_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_sawedoff_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_sawedoff_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_sawedoff_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 30:
	Settings::Sticker::sticker_tec_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_tec_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_tec_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_tec_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_tec_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 32:
	Settings::Sticker::sticker_p2000_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_p2000_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_p2000_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_p2000_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_p2000_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 33:
	Settings::Sticker::sticker_mp7_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_mp7_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_mp7_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_mp7_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_mp7_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 34:
	Settings::Sticker::sticker_mp9_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_mp9_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_mp9_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_mp9_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_mp9_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 35:
	Settings::Sticker::sticker_nova_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_nova_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_nova_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_nova_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_nova_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 36:
	Settings::Sticker::sticker_p250_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_p250_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_p250_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_p250_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_p250_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 38:
	Settings::Sticker::sticker_scar_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_scar_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_scar_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_scar_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_scar_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 39:
	Settings::Sticker::sticker_sg_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_sg_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_sg_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_sg_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_sg_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	case 40:
	Settings::Sticker::sticker_ssg_iSlot[iSlot] = iSlot;
	Settings::Sticker::sticker_ssg_id[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iID;
	Settings::Sticker::sticker_ssg_wear[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flWear;
	Settings::Sticker::sticker_ssg_size[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].flScale;
	Settings::Sticker::sticker_ssg_rotate[iSlot] = Stick[Settings::Sticker::stickerSafeWeapon].Stickers[iSlot].iRotation;
	break;
	}

	ForceFullUpdate();
	}

	static int stickers = 0;

	ImGui::End();
	}

	ImGui::GetStyle().WindowMinSize = OldMinSize;

	}
	*/

	if (Settings::Misc::misc_StickerChanger && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(500.f, 295.f));

		if (ImGui::Begin("stickerchanger", &Settings::Misc::misc_StickerChanger,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			int SafeWeapon = SafeWeaponID();
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Checkbox("stickers", &Stick[SafeWeapon].StickersEnabled);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("must be ingame to enable this");
			ImGui::Separator();
			if (SafeWeapon != 0)
			{
				static int iSlot = 0;
				const char* slots[] =
				{
					"slot 1", "slot 2", "slot 3", "slot 4"
				};
				ImGui::Combo("slot", &iSlot, slots, IM_ARRAYSIZE(slots));
				ImGui::SliderFloat("wear ", &Stick[SafeWeapon].Stickers[iSlot].flWear, 0.f, 1.f, "%.3f");
				ImGui::SliderFloat("size", &Stick[SafeWeapon].Stickers[iSlot].flScale, 0.f, 1.f, "%.3f");
				ImGui::SliderInt("rotate", &Stick[SafeWeapon].Stickers[iSlot].iRotation, 0, 360);
				ImGui::InputInt("id input", &Stick[SafeWeapon].Stickers[iSlot].iID);
				ImGui::Checkbox("sticker filter list", &Settings::Misc::stickerids);

				if (ImGui::Button("Accept Stickers##Skin"))
				{
					ForceFullUpdate();
				}

				static int stickers = 0;
			}
			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;

	}


	if (Settings::Misc::window_inventorychanger && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(500.f, 355.f));

		if (ImGui::Begin("inventory changer", &Settings::Misc::window_inventorychanger,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			ImGui::Columns(2, nullptr, false);
			ImGui::Checkbox("enable inventory changer", &Settings::InventoryChanger::enabled);
			static int itemDefinitionIndex = 0;
			static int paintKit = 0;
			static int rarity = 0;
			static int seed = 0;
			static float wear = 0.f;

			const char* skins_items[] =
			{
				"", "",  "2: groundwater","3: candy apple", "",
				"5: forest ddpat","6: arctic camo",  "",
				"8: desert storm","9: bengal tiger","10: copperhead",
				"11: skulls","12: crimson web","13: blue streak","14: red laminate"
				,"15: gunsmoke","16: jungle tiger","17: urban ddpat",  "",
				"", "20: virus","21: granite marbleized","22: contrast spray",
				"",  "", "25: forest leaves","26: lichen dashed",
				"27: bone mask","28: anodized navy",  "",  "30: snake camo",
				"",  "32: silver","33: hot rod","34: metallic ddpat",  "",
				"36: ossified","37: blaze","38: fade","39: bulldozer","40: night",
				"41: copper","42: blue steel","43: stained","44: case hardened",
				"",  "46: contractor","47: colony","48: dragon tattoo",
				"",   "",  "51: lightning strike",  "",
				"",   "",   "",   "",   "",
				"",    "59: slaughter","60: dark water"
				,"61: hypnotic","62: bloomstick",  "",   ""
				,   "",   "",  "67: cold blooded",  "",   ""
				,  "70: carbon fiber","71: scorpion","72: safari mesh","73: wings","74: polar camo"
				,"75: blizzard marbleized","76: winter forest","77: boreal forest","78: forest night"
				,  "",   "",   "",   "",  "83: orange ddpat","84: pink ddpat"
				,  "",   "",   "",   "",  "",  "90: mudder",  ""
				,  "92: cyanospatter","93: caramel",  "", "95: grassland","96: blue spruce",  ""
				,  "98: ultraviolet","99: sand dune","100: storm","101: tornado","102: whiteout",  ""
				,  "104: grassland leaves",  "",   "", "107: polar mesh",  "",   ""
				, "110: condemned","111: glacier mesh",  "",   "",   "",   "",  "116: sand mesh",  "",   "", "119: sage spray",  "",   "", "122: jungle spray",  "",  "124: sand spray",  ""
				,  "",  "",  "",  "",  "",  "",  "",  "",  "", "135: urban perforated"
				,"136: waves perforated",  "",   "",   "",  "", "141: orange peel",  "",  "143: urban masked", "", "", "", "147: jungle dashed"
				,"148: sand dashed","149: urban dashed", "", "151: jungle", "", "153: demolition","154: afterimage","155: bullet rain","156: death by kitty","157: palm","158: walnut","159: brass", "", "", "162: splash", "","164: modern hunter","165: splash jam","166: blaze orange","167: radiation hazard","168: nuclear threat","169: fallout warning","170: predator","171: irradiated alert","172: black laminate", "","174: boom","175: scorched","176: faded zebra","177: memento","178: doomkitty","179: nuclear threat","180: fire serpent","181: corticera","182: emerald dragon","183: overgrowth","184: corticera","185: golden koi","186: wave spray","187: zirka","188: graven","189: bright water","190: black limba","191: tempest","192: shattered","193: bone pile","194: spitfire","195: demeter","196: emerald","197: anodized navy","198: hazard","199: dry season","200: mayan dreams","201: palm","202: jungle ddpat","203: rust coat","204: mosaico","205: jungle","206: tornado","207: facets","208: sand dune","209: groundwater","210: anodized gunmetal","211: ocean foam","212: graphite","213: ocean foam","214: graphite","215: x-ray","216: blue titanium","217: blood tiger","218: hexane","219: hive","220: hemoglobin","221: serum","222: blood in the water","223: nightshade","224: water sigil","225: ghost camo","226: blue laminate","227: electric hive","228: blind spot","229: azure zebra","230: steel disruption","231: cobalt disruption","232: crimson web","233: tropical storm","234: ash wood","235: varicamo","236: night ops","237: urban rubble","238: varicamo blue", "", "240: calicamo","241: hunting blind","242: army mesh","243: gator mesh","244: teardown","245: army recon","246: amber fade","247: damascus steel","248: red quartz","249: cobalt quartz","250: full stop","251: pit viper","252: silver quartz","253: acid fade","254: nitro","255: asiimov","256: the kraken","257: guardian","258: mehndi","259: redline","260: pulse","261: marina","262: rose iron","263: rising skull","264: sandstorm","265: kami","266: magma","267: cobalt halftone","268: tread plate","269: the fuschia is now","270: victoria","271: undertow","272: titanium bit","273: heirloom","274: copper galaxy","275: red fragcam","276: panther","277: stainless","278: blue fissure","279: asiimov","280: chameleon","281: corporal","282: redline","283: trigon","284: heat","285: terrain","286: antique","287: pulse","288: sergeant","289: sandstorm","290: guardian","291: heaven guard", "", "293: death rattle","294: green apple","295: franklin","296: meteorite","297: tuxedo","298: army sheen","299: caged steel","300: emerald pinstripe","301: atomic alloy","302: vulcan","303: isaac","304: slashed","305: torque","306: antique","307: retribution","308: kami","309: howl","310: curse","311: desert warfare","312: cyrex","313: orion","314: heaven guard","315: poison dart","316: jaguar","317: bratatat","318: road rash","319: detour","320: red python","321: master piece","322: nitro","323: rust coat", "", "325: chalice","326: knight","327: chainmail","328: hand cannon","329: dark age","330: briar", "", "332: royal blue","333: indigo","334: twist","335: module","336: desert-strike","337: tatter","338: pulse","339: caiman","340: jet set","341: first class","342: leather","343: commuter","344: dragon lore","345: first class","346: coach class","347: pilot","348: red leather","349: osiris","350: tigris","351: conspiracy","352: fowl play","353: water elemental","354: urban hazard","355: desert-strike","356: koi","357: ivory","358: supernova","359: asiimov","360: cyrex","361: abyss","362: labyrinth","363: traveler","364: business class","365: olive plaid","366: green plaid","367: reactor","368: setting sun","369: nuclear waste","370: bone machine","371: styx","372: nuclear garden","373: contamination","374: toxic","375: radiation hazard","376: chemical green","377: hot shot","378: fallout warning","379: cerberus","380: wasteland rebel","381: grinder","382: murky","383: basilisk","384: griffin","385: firestarter","386: dart","387: urban hazard","388: cartel","389: fire elemental","390: highwayman","391: cardiac","392: delusion","393: tranquility","394: cartel","395: man-o'-war","396: urban shock","397: naga","398: chatterbox","399: catacombs","400: 龍王 (dragon king)","401: system lock","402: malachite","403: deadly poison","404: muertos","405: serenity","406: grotto","407: quicksilver","", "409: tiger tooth","410: damascus steel","411: damascus steel", "", "413: marble fade","414: rust coat","415: doppler","416: doppler","417: doppler","418: doppler","419: doppler","420: doppler","421: doppler","422: elite build","423: armor core","424: worm god","425: bronze deco","426: valence","427: monkey business","428: eco","429: djinn","430: hyper beast","431: heat","432: man-o'-war","433: neon rider","434: origami","435: pole position","436: grand prix","437: twilight galaxy","438: chronos","439: hades","440: icarus fell","441: minotaur's labyrinth","442: asterion","443: pathfinder","444: daedalus","445: hot rod","446: medusa","447: duelist","448: pandora's box","449: poseidon","450: moon in libra","451: sun in leo","452: shipping forecast","453: emerald","454: para green","455: akihabara accept","456: hydroponic","457: bamboo print","458: bamboo shadow","459: bamboo forest","460: aqua terrace", "", "462: counter terrace","463: terrace","464: neon kimono","465: orange kimono","466: crimson kimono","467: mint kimono","468: midnight storm","469: sunset storm 壱","470: sunset storm 弐","471: daybreak","472: impact drill","473: seabird","474: aquamarine revenge","475: hyper beast","476: yellow jacket","477: neural net","478: rocket pop","479: bunsen burner","480: evil daimyo","481: nemesis","482: ruby poison dart","483: loudmouth","484: ranger","485: handgun","486: elite build","487: cyrex","488: riot","489: torque","490: frontside misty","491: dualing dragons","492: survivor z","493: flux","494: stone cold","495: wraiths","496: nebula crusader","497: golden coil","498: rangeen","499: cobalt core","500: special delivery","501: wingshot","502: green marine","503: big iron","504: kill confirmed","505: scumbria","506: point disarray","507: ricochet","508: fuel rod","509: corinthian","510: retrobution","511: the executioner","512: royal paladin", "", "514: power loader","515: imperial","516: shapewood","517: yorick","518: outbreak","519: tiger moth","520: avalanche","521: teclu burner","522: fade","523: amber fade","524: fuel injector","525: elite build","526: photic zone","527: kumicho dragon","528: cartel","529: valence","530: triumvirate", "", "532: royal legion","533: the battlestar","534: lapis gator","535: praetorian","536: impire","537: hyper beast","538: necropos","539: jambiya","540: lead conduit","541: fleet flock","542: judgement of anubis","543: red astor","544: ventilators","545: orange crash","546: firefight","547: spectre","548: chantico's fire","549: bioleak","550: oceanic","551: asiimov","552: fubar","553: atlas","554: ghost crusader","555: re-entry","556: primal saber","557: black tie","558: lore","559: lore","560: lore","561: lore","562: lore","563: black laminate","564: black laminate","565: black laminate","566: black laminate","567: black laminate","568: gamma doppler","569: gamma doppler","570: gamma doppler","571: gamma doppler","572: gamma doppler","573: autotronic","574: autotronic","575: autotronic","576: autotronic","577: autotronic","578: bright water","579: bright water","580: freehand","581: freehand","582: freehand","583: aristocrat","584: phobos","585: violent daimyo","586: wasteland rebel","587: mecha industries","588: desolate space","589: carnivore","590: exo","591: imperial dragon","592: iron clad","593: chopper","594: harvester","595: reboot","596: limelight","597: bloodsport","598: aerial","599: ice cap","600: neon revolution","601: syd mead","602: imprint","603: directive","604: roll cage","605: scumbria","606: ventilator","607: weasel","608: petroglyph","609: airlock","610: dazzle","611: grim","612: powercore","613: triarch","614: fuel injector","615: briefing","616: slipstream","617: doppler","618: doppler","619: doppler","620: ultraviolet","621: ultraviolet","622: polymer","623: ironwork","624: dragonfire","625: royal consorts","626: mecha industries","627: cirrus","628: stinger","629: black sand","630: sand scale","631: flashback","632: buzz kill","633: sonar","634: gila","635: turf","636: shallow grave","637: cyrex","638: wasteland princess","639: bloodsport","640: fever dream","641: jungle slipstream","642: blueprint","643: xiangliu","644: decimator","645: oxide blaze","646: capillary","647: crimson tsunami","648: emerald poison dart","649: akoben","650: ripple","651: last dive","652: scaffold","653: neo-noir","654: seasons","655: zander","656: orbit mk01","657: blueprint","658: cobra strike","659: macabre","660: hyper beast","661: sugar rush","662: oni taiji","663: briefing","664: hellfire","665: aloha","666: hard water","667: woodsman","668: red rock","669: death grip","670: death's head","671: cut out","672: metal flowers","673: morris","674: triqua","675: the empress","676: high roller","677: hunter","678: see ya later","679: goo","680: off world","681: leaded glass","682: oceanic","683: llama cannon","684: cracked opal","685: jungle slipstream","686: phantom","687: tacticat","688: exposure","689: ziggy"
			};

			const char* quality_items[] =
			{
				"none",
				"1 - consumer grade (white)",
				"2 - industrial grade (light blue)",
				"3 - mil-spec (darker blue)",
				"4 - restricted (purple)",
				"5 - classified (pinkish purple)",
				"6 - covert (red)",
				"7 - exceedingly rare (gold)",
			};
			static const char* weapons[] = {
				"none",
				"1 - desert eagle",
				"2 - dual berettas",
				"3 - five seven",
				"4 - glock",
				"",
				"",
				"7 - ak47",
				"8 - aug",
				"9 - awp",
				"10 - famas",
				"11 - g3sg1",
				"",
				"13 - galil ar",
				"14 - m249",
				"",
				"16 - m4a4",
				"17 - mac10",
				"",
				"19 - p90",
				"",
				"",
				"",
				"",
				"24 - ump45",
				"25 - xm1014",
				"26 - ppbizon",
				"27 - mag7",
				"28 - negev",
				"29 - sawedoff",
				"30 - tec9",
				" ",
				"32 - p2000",
				"33 - mp7",
				"34 - mp9",
				"35 - nova",
				"36 - p250",
				"38 - scar20",
				"39 - sg553",
				"40 - scout",
			};
			ImGui::Combo("weapons", &itemDefinitionIndex, weapons, IM_ARRAYSIZE(weapons));
			ImGui::InputInt("weapon id", &itemDefinitionIndex);
			ImGui::Checkbox("weapon filter list", &Settings::Misc::weaponids);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Combo("skins", &paintKit, skins_items, IM_ARRAYSIZE(skins_items));
			ImGui::InputInt("skin id", &paintKit);
			ImGui::Checkbox("skin filter list", &Settings::Misc::skinids);
			ImGui::Spacing();
			ImGui::Spacing();
			static const char* rare[] =
			{
				"none",
				"1 - consumer grade (white)",
				"2 - industrial grade (light blue)",
				"3 - mil-spec (dark blue)",
				"4 - restricted (purple)",
				"5 - classified (pink)",
				"6 - covert (red)",
				"7 - contraband (gold)",
			};
			ImGui::Combo("rarity", &rarity, rare, IM_ARRAYSIZE(rare));
			ImGui::InputInt("seed", &seed);
			ImGui::SliderFloat("wear", &wear, FLT_MIN, 1.f, "%.10f", 5);
			ImGui::Spacing();
			ImGui::Spacing();
			if (ImGui::Button("add")) {
				Settings::InventoryChanger::weapons.insert(Settings::InventoryChanger::weapons.end(), { itemDefinitionIndex , paintKit , rarity , seed, wear });
			} ImGui::SameLine();
			if (ImGui::Button("Apply##Skin")) {
				SendClientHello();
				SendMMHello();
			}
			ImGui::NextColumn();

			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
			ImGui::ListBoxHeader("skins");
			int weapon_index = 0;
			for (auto weapon : Settings::InventoryChanger::weapons) {
				if (ImGui::Selectable(std::string(std::to_string(weapon.itemDefinitionIndex) + " " + std::to_string(weapon.paintKit)).c_str())) {
					Settings::InventoryChanger::weapons.erase(Settings::InventoryChanger::weapons.begin() + weapon_index);
				}
				weapon_index++;
			}
			ImGui::ListBoxFooter();
			ImGui::PopStyleColor();
			ImGui::Columns(1, nullptr, false);

			ImGui::GetStyle().WindowMinSize = OldMinSize;
		}
		ImGui::End();
	}

	if (Settings::Misc::window_medalchanger && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(350.f, 350.f));

		if (ImGui::Begin("medal changer", &Settings::Misc::window_medalchanger,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			// ImGui::Columns(2, nullptr, false);
			ImGui::Checkbox("enable medal changer", &Settings::MedalChanger::enabled);
			static int medal_id = 0;
			ImGui::InputInt("medal id", &medal_id);
			ImGui::Checkbox("medal filter list", &Settings::Misc::medalids);
			if (ImGui::Button("add") && medal_id != 0) {
				Settings::MedalChanger::medals.insert(Settings::MedalChanger::medals.end(), medal_id);
				medal_id = 0;
			}
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
			ImGui::ListBoxHeader("medal list");
			for (int m = 0; m < Settings::MedalChanger::medals.size(); m++) {
				if (ImGui::Selectable(std::to_string(Settings::MedalChanger::medals[m]).c_str())) {
					if (Settings::MedalChanger::equipped_medal == Settings::MedalChanger::medals[m]) {
						Settings::MedalChanger::equipped_medal = 0;
						Settings::MedalChanger::equipped_medal_override = false;
					}
					Settings::MedalChanger::medals.erase(Settings::MedalChanger::medals.begin() + m);
				}
			}
			ImGui::ListBoxFooter();
			ImGui::PopStyleColor();

			// BROKEN
			/*
			ImGui::Checkbox("equipped medal", &Settings::MedalChanger::equipped_medal_override);
			if (Settings::MedalChanger::equipped_medal_override) {
			static int equipped_medal = 0;
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
			if (ImGui::Combo("equipped medal", &equipped_medal, [](void* data, int idx, const char** out_text)
			{
			*out_text = std::to_string(Settings::MedalChanger::medals[idx]).c_str();
			return true;
			}, nullptr, Settings::MedalChanger::medals.size(), 5)) {
			Settings::MedalChanger::equipped_medal = Settings::MedalChanger::medals[equipped_medal];
			}
			ImGui::PopStyleColor();
			}
			*/
			// BROKEN

			if (ImGui::Button("Apply##Medals")) {
				SendClientHello();
				SendMMHello();
			}

			ImGui::GetStyle().WindowMinSize = OldMinSize;
		}
		ImGui::End();
	}

	if (Settings::Misc::window_profilechanger && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(500.f, 280.f));

		if (ImGui::Begin("profile changer", &Settings::Misc::window_profilechanger,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			ImGui::Checkbox("enable profile changer", &Settings::ProfileChanger::enabled);
			
			static const char* bans[] = {
				"none",
				"you were kicked from the last match (competitive cooldown)",
				"you killed too many teammates (competitive cooldown)",
				"you killed a teammate at round start (competitive cooldown)",
				"you failed to reconnect to the last match (competitive cooldown)",
				"you abandoned the last match (competitive cooldown)",
				"you did too much damage to your teammates (competitive cooldown)",
				"you did too much damage to your teammates at round start (competitive cooldown)",
				"this account is permanently untrusted (global cooldown)",
				"you were kicked from too many recent matches (competitive cooldown)",
				"convicted by overwatch - majorly disruptive (global cooldown)",
				"convicted by overwatch - minorly disruptive (global cooldown)",
				"resolving matchmaking state for your account (temporary cooldown)",
				"resolving matchmaking state after the last match (temporary cooldown)",
				"this account is permanently untrusted (global cooldown)",
				"(global cooldown)",
				"you failed to connect by match start. (competitive cooldown)",
				"you have kicked too many teammates in recent matches (competitive cooldown)",
				"congratulations on your recent competitive wins! before you play competitive matches further please wait for matchmaking servers to calibrate your skill group placement based on your lastest performance. (temporary cooldown)",
				"a server using your game server login token has been banned. your account is now permanently banned from operating game servers, and you have a cooldown from connecting to game servers. (global cooldown)"
			};
			
			static const char* ranks[] = {
				"off",
				"silver 1",
				"silver 2",
				"silver 3",
				"silver 4",
				"silver elite",
				"silver elite master",
				"gold nova 1",
				"gold nova 2",
				"gold nova 3",
				"gold nova master",
				"master guardian 1",
				"master guardian 2",
				"master guardian elite",
				"distinguished master guardian",
				"legendary eagle",
				"legendary eagle master",
				"supreme master first class",
				"the global elite"
			};
			ImGui::Combo("rank", &Settings::ProfileChanger::rank_id, ranks, IM_ARRAYSIZE(ranks));
			ImGui::SliderInt("level", &Settings::ProfileChanger::level, 0, 40);
			ImGui::SliderInt("xp", &Settings::ProfileChanger::xp, 0, 5000);
			ImGui::InputInt("wins", &Settings::ProfileChanger::wins);
			ImGui::InputInt("friendly", &Settings::ProfileChanger::cmd_friendly);
			ImGui::InputInt("teaching", &Settings::ProfileChanger::cmd_teaching);
			ImGui::InputInt("leader", &Settings::ProfileChanger::cmd_leader);
			
			ImGui::Combo("ban", &Settings::ProfileChanger::ban, bans, IM_ARRAYSIZE(bans));
			ImGui::InputInt("ban time", &Settings::ProfileChanger::time);

			if (ImGui::Button("Apply##Profile"))
			{
				SendMMHello();
			}
			ImGui::Columns(1, nullptr, false);
			ImGui::GetStyle().WindowMinSize = OldMinSize;
		}
		ImGui::End();
	}

	if (Settings::Misc::skinids && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(350.f, 250.f));

		if (ImGui::Begin("skin ids", &Settings::Misc::skinids,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{

			static ImGuiTextFilter filter;
			filter.Draw();
			const char* skinids[] = {
				"2: groundwater",
				"3: candy apple",
				"5: forest ddpat",
				"6: arctic camo",
				"8: desert storm",
				"9: bengal tiger",
				"10: copperhead",
				"11: skulls",
				"12: crimson web",
				"13: blue streak",
				"14: red laminate",
				"15: gunsmoke",
				"16: jungle tiger",
				"17: urban ddpat",
				"20: virus",
				"21: granite marbleized",
				"22: contrast spray",
				"25: forest leaves",
				"26: lichen dashed",
				"27: bone mask",
				"28: anodized navy",
				"30: snake camo",
				"32: silver",
				"33: hot rod",
				"34: metallic ddpat",
				"36: ossified",
				"37: blaze",
				"38: fade",
				"39: bulldozer",
				"40: night",
				"41: copper",
				"42: blue steel",
				"43: stained",
				"44: case hardened",
				"46: contractor",
				"47: colony",
				"48: dragon tattoo",
				"51: lightning strike",
				"59: slaughter",
				"60: dark water",
				"61: hypnotic",
				"62: bloomstick",
				"67: cold blooded",
				"70: carbon fiber",
				"71: scorpion",
				"72: safari mesh",
				"73: wings",
				"74: polar camo",
				"75: blizzard marbleized",
				"76: winter forest",
				"77: boreal forest",
				"78: forest night",
				"83: orange ddpat",
				"84: pink ddpat",
				"90: mudder",
				"92: cyanospatter",
				"93: caramel",
				"95: grassland",
				"96: blue spruce",
				"98: ultraviolet",
				"99: sand dune",
				"100: storm",
				"101: tornado",
				"102: whiteout",
				"104: grassland leaves",
				"107: polar mesh",
				"110: condemned",
				"111: glacier mesh",
				"116: sand mesh",
				"119: sage spray",
				"122: jungle spray",
				"124: sand spray",
				"135: urban perforated",
				"136: waves perforated",
				"141: orange peel",
				"143: urban masked",
				"147: jungle dashed",
				"148: sand dashed",
				"149: urban dashed",
				"151: jungle",
				"153: demolition",
				"154: afterimage",
				"155: bullet rain",
				"156: death by kitty",
				"157: palm",
				"158: walnut",
				"159: brass",
				"162: splash",
				"164: modern hunter",
				"165: splash jam",
				"166: blaze orange",
				"167: radiation hazard",
				"168: nuclear threat",
				"169: fallout warning",
				"170: predator",
				"171: irradiated alert",
				"172: black laminate",
				"174: boom",
				"175: scorched",
				"176: faded zebra",
				"177: memento",
				"178: doomkitty",
				"179: nuclear threat",
				"180: fire serpent",
				"181: corticera",
				"182: emerald dragon",
				"183: overgrowth",
				"184: corticera",
				"185: golden koi",
				"186: wave spray",
				"187: zirka",
				"188: graven",
				"189: bright water",
				"190: black limba",
				"191: tempest",
				"192: shattered",
				"193: bone pile",
				"194: spitfire",
				"195: demeter",
				"196: emerald",
				"197: anodized navy",
				"198: hazard",
				"199: dry season",
				"200: mayan dreams",
				"201: palm",
				"202: jungle ddpat",
				"203: rust coat",
				"204: mosaico",
				"205: jungle",
				"206: tornado",
				"207: facets",
				"208: sand dune",
				"209: groundwater",
				"210: anodized gunmetal",
				"211: ocean foam",
				"212: graphite",
				"213: ocean foam",
				"214: graphite",
				"215: x-ray",
				"216: blue titanium",
				"217: blood tiger",
				"218: hexane",
				"219: hive",
				"220: hemoglobin",
				"221: serum",
				"222: blood in the water",
				"223: nightshade",
				"224: water sigil",
				"225: ghost camo",
				"226: blue laminate",
				"227: electric hive",
				"228: blind spot",
				"229: azure zebra",
				"230: steel disruption",
				"231: cobalt disruption",
				"232: crimson web",
				"233: tropical storm",
				"234: ash wood",
				"235: varicamo",
				"236: night ops",
				"237: urban rubble",
				"238: varicamo blue",
				"240: calicamo",
				"241: hunting blind",
				"242: army mesh",
				"243: gator mesh",
				"244: teardown",
				"245: army recon",
				"246: amber fade",
				"247: damascus steel",
				"248: red quartz",
				"249: cobalt quartz",
				"250: full stop",
				"251: pit viper",
				"252: silver quartz",
				"253: acid fade",
				"254: nitro",
				"255: asiimov",
				"256: the kraken",
				"257: guardian",
				"258: mehndi",
				"259: redline",
				"260: pulse",
				"261: marina",
				"262: rose iron",
				"263: rising skull",
				"264: sandstorm",
				"265: kami",
				"266: magma",
				"267: cobalt halftone",
				"268: tread plate",
				"269: the fuschia is now",
				"270: victoria",
				"271: undertow",
				"272: titanium bit",
				"273: heirloom",
				"274: copper galaxy",
				"275: red fragcam",
				"276: panther",
				"277: stainless",
				"278: blue fissure",
				"279: asiimov",
				"280: chameleon",
				"281: corporal",
				"282: redline",
				"283: trigon",
				"284: heat",
				"285: terrain",
				"286: antique",
				"287: pulse",
				"288: sergeant",
				"289: sandstorm",
				"290: guardian",
				"291: heaven guard",
				"293: death rattle",
				"294: green apple",
				"295: franklin",
				"296: meteorite",
				"297: tuxedo",
				"298: army sheen",
				"299: caged steel",
				"300: emerald pinstripe",
				"301: atomic alloy",
				"302: vulcan",
				"303: isaac",
				"304: slashed",
				"305: torque",
				"306: antique",
				"307: retribution",
				"308: kami",
				"309: howl",
				"310: curse",
				"311: desert warfare",
				"312: cyrex",
				"313: orion",
				"314: heaven guard",
				"315: poison dart",
				"316: jaguar",
				"317: bratatat",
				"318: road rash",
				"319: detour",
				"320: red python",
				"321: master piece",
				"322: nitro",
				"323: rust coat",
				"325: chalice",
				"326: knight",
				"327: chainmail",
				"328: hand cannon",
				"329: dark age",
				"330: briar",
				"332: royal blue",
				"333: indigo",
				"334: twist",
				"335: module",
				"336: desert-strike",
				"337: tatter",
				"338: pulse",
				"339: caiman",
				"340: jet set",
				"341: first class",
				"342: leather",
				"343: commuter",
				"344: dragon lore",
				"345: first class",
				"346: coach class",
				"347: pilot",
				"348: red leather",
				"349: osiris",
				"350: tigris",
				"351: conspiracy",
				"352: fowl play",
				"353: water elemental",
				"354: urban hazard",
				"355: desert-strike",
				"356: koi",
				"357: ivory",
				"358: supernova",
				"359: asiimov",
				"360: cyrex",
				"361: abyss",
				"362: labyrinth",
				"363: traveler",
				"364: business class",
				"365: olive plaid",
				"366: green plaid",
				"367: reactor",
				"368: setting sun",
				"369: nuclear waste",
				"370: bone machine",
				"371: styx",
				"372: nuclear garden",
				"373: contamination",
				"374: toxic",
				"375: radiation hazard",
				"376: chemical green",
				"377: hot shot",
				"378: fallout warning",
				"379: cerberus",
				"380: wasteland rebel",
				"381: grinder",
				"382: murky",
				"383: basilisk",
				"384: griffin",
				"385: firestarter",
				"386: dart",
				"387: urban hazard",
				"388: cartel",
				"389: fire elemental",
				"390: highwayman",
				"391: cardiac",
				"392: delusion",
				"393: tranquility",
				"394: cartel",
				"395: man-o'-war",
				"396: urban shock",
				"397: naga",
				"398: chatterbox",
				"399: catacombs",
				"400: 龍王 (dragon king)",
				"401: system lock",
				"402: malachite",
				"403: deadly poison",
				"404: muertos",
				"405: serenity",
				"406: grotto",
				"407: quicksilver",
				"409: tiger tooth",
				"410: damascus steel",
				"411: damascus steel",
				"413: marble fade",
				"414: rust coat",
				"415: doppler",
				"416: doppler",
				"417: doppler",
				"418: doppler",
				"419: doppler",
				"420: doppler",
				"421: doppler",
				"422: elite build",
				"423: armor core",
				"424: worm god",
				"425: bronze deco",
				"426: valence",
				"427: monkey business",
				"428: eco",
				"429: djinn",
				"430: hyper beast",
				"431: heat",
				"432: man-o'-war",
				"433: neon rider",
				"434: origami",
				"435: pole position",
				"436: grand prix",
				"437: twilight galaxy",
				"438: chronos",
				"439: hades",
				"440: icarus fell",
				"441: minotaur's labyrinth",
				"442: asterion",
				"443: pathfinder",
				"444: daedalus",
				"445: hot rod",
				"446: medusa",
				"447: duelist",
				"448: pandora's box",
				"449: poseidon",
				"450: moon in libra",
				"451: sun in leo",
				"452: shipping forecast",
				"453: emerald",
				"454: para green",
				"455: akihabara accept",
				"456: hydroponic",
				"457: bamboo print",
				"458: bamboo shadow",
				"459: bamboo forest",
				"460: aqua terrace",
				"462: counter terrace",
				"463: terrace",
				"464: neon kimono",
				"465: orange kimono",
				"466: crimson kimono",
				"467: mint kimono",
				"468: midnight storm",
				"469: sunset storm 壱",
				"470: sunset storm 弐",
				"471: daybreak",
				"472: impact drill",
				"473: seabird",
				"474: aquamarine revenge",
				"475: hyper beast",
				"476: yellow jacket",
				"477: neural net",
				"478: rocket pop",
				"479: bunsen burner",
				"480: evil daimyo",
				"481: nemesis",
				"482: ruby poison dart",
				"483: loudmouth",
				"484: ranger",
				"485: handgun",
				"486: elite build",
				"487: cyrex",
				"488: riot",
				"489: torque",
				"490: frontside misty",
				"491: dualing dragons",
				"492: survivor z",
				"493: flux",
				"494: stone cold",
				"495: wraiths",
				"496: nebula crusader",
				"497: golden coil",
				"498: rangeen",
				"499: cobalt core",
				"500: special delivery",
				"501: wingshot",
				"502: green marine",
				"503: big iron",
				"504: kill confirmed",
				"505: scumbria",
				"506: point disarray",
				"507: ricochet",
				"508: fuel rod",
				"509: corinthian",
				"510: retrobution",
				"511: the executioner",
				"512: royal paladin",
				"514: power loader",
				"515: imperial",
				"516: shapewood",
				"517: yorick",
				"518: outbreak",
				"519: tiger moth",
				"520: avalanche",
				"521: teclu burner",
				"522: fade",
				"523: amber fade",
				"524: fuel injector",
				"525: elite build",
				"526: photic zone",
				"527: kumicho dragon",
				"528: cartel",
				"529: valence",
				"530: triumvirate",
				"532: royal legion",
				"533: the battlestar",
				"534: lapis gator",
				"535: praetorian",
				"536: impire",
				"537: hyper beast",
				"538: necropos",
				"539: jambiya",
				"540: lead conduit",
				"541: fleet flock",
				"542: judgement of anubis",
				"543: red astor",
				"544: ventilators",
				"545: orange crash",
				"546: firefight",
				"547: spectre",
				"548: chantico's fire",
				"549: bioleak",
				"550: oceanic",
				"551: asiimov",
				"552: fubar",
				"553: atlas",
				"554: ghost crusader",
				"555: re-entry",
				"556: primal saber",
				"557: black tie",
				"558: lore",
				"559: lore",
				"560: lore",
				"561: lore",
				"562: lore",
				"563: black laminate",
				"564: black laminate",
				"565: black laminate",
				"566: black laminate",
				"567: black laminate",
				"568: gamma doppler emerald marble",
				"569: gamma doppler phase 1",
				"570: gamma doppler phase 2",
				"571: gamma doppler phase 3",
				"572: gamma doppler phase 4",
				"573: autotronic",
				"574: autotronic",
				"575: autotronic",
				"576: autotronic",
				"577: autotronic",
				"578: bright water",
				"579: bright water",
				"580: freehand",
				"581: freehand",
				"582: freehand",
				"583: aristocrat",
				"584: phobos",
				"585: violent daimyo",
				"586: wasteland rebel",
				"587: mecha industries",
				"588: desolate space",
				"589: carnivore",
				"590: exo",
				"591: imperial dragon",
				"592: iron clad",
				"593: chopper",
				"594: harvester",
				"595: reboot",
				"596: limelight",
				"597: bloodsport",
				"598: aerial",
				"599: ice cap",
				"600: neon revolution",
				"601: syd mead",
				"602: imprint",
				"603: directive",
				"604: roll cage",
				"605: scumbria",
				"606: ventilator",
				"607: weasel",
				"608: petroglyph",
				"609: airlock",
				"610: dazzle",
				"611: grim",
				"612: powercore",
				"613: triarch",
				"614: fuel injector",
				"615: briefing",
				"616: slipstream",
				"617: doppler",
				"618: doppler",
				"619: doppler",
				"620: ultraviolet",
				"621: ultraviolet",
				"622: polymer",
				"623: ironwork",
				"624: dragonfire",
				"625: royal consorts",
				"626: mecha industries",
				"627: cirrus",
				"628: stinger",
				"629: black sand",
				"630: sand scale",
				"631: flashback",
				"632: buzz kill",
				"633: sonar",
				"634: gila",
				"635: turf",
				"636: shallow grave",
				"637: cyrex",
				"638: wasteland princess",
				"639: bloodsport",
				"640: fever dream",
				"641: jungle slipstream",
				"642: blueprint",
				"643: xiangliu",
				"644: decimator",
				"645: oxide blaze",
				"646: capillary",
				"647: crimson tsunami",
				"648: emerald poison dart",
				"649: akoben",
				"650: ripple",
				"651: last dive",
				"652: scaffold",
				"653: neo-noir",
				"654: seasons",
				"655: zander",
				"656: orbit mk01",
				"657: blueprint",
				"658: cobra strike",
				"659: macabre",
				"660: hyper beast",
				"661: sugar rush",
				"662: oni taiji",
				"663: briefing",
				"664: hellfire",
				"665: aloha",
				"666: hard water",
				"667: woodsman",
				"668: red rock",
				"669: death grip",
				"670: death's head",
				"671: cut out",
				"672: metal flowers",
				"673: morris",
				"674: triqua",
				"675: the empress",
				"676: high roller",
				"677: hunter",
				"678: see ya later",
				"679: goo",
				"680: off world",
				"681: leaded glass",
				"682: oceanic",
				"683: llama cannon",
				"684: cracked opal",
				"685: jungle slipstream",
				"686: phantom",
				"687: tacticat",
				"688: exposure",
				"689: ziggy",
				"690: stymphalian",
				"691: mortis",
				"692: night riot",
				"693: flame test",
				"694: moonrise",
				"695: neo-noir",
				"696: bloodsport",
				"697: black sand",
				"698: lionfish",
				"699: wild six",
				"700: urban hazard",
				"701: grip",
				"702: aloha",
				"703: swag-7",
				"704: arctic wolf",
				"705: cortex",
				"706: oxide blaze"
			};
			for (int i = 0; i < IM_ARRAYSIZE(skinids); i++)
				if (filter.PassFilter(skinids[i]))
					ImGui::Text("%s", skinids[i]);
			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	if (Settings::Misc::medalids && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(350.f, 250.f));

		if (ImGui::Begin("medal ids", &Settings::Misc::medalids,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			static ImGuiTextFilter filter;
			filter.Draw();
			const char* medalids[] = {
				"874 = 5 year veteran coin",
				"875 = champion at dreamhack 2013",
				"876 = finalist at dreamhack 2013",
				"877 = semifinalist at dreamhack 2013",
				"878 = quarterfinalist at dreamhack 2013",
				"879 = champion at ems one katowice 2014",
				"880 = finalist at ems one katowice 2014",
				"881 = semifinalist at ems one katowice 2014",
				"882 = quarterfinalist at ems one katowice 2014",
				"883 = champion at esl one cologne 2014",
				"884 = finalist at esl one cologne 2014",
				"885 = semifinalist at esl one cologne 2014",
				"886 = quarterfinalist at esl one cologne 2014",
				"887 = bronze cologne 2014 pick'em troph",
				"888 = silver cologne 2014 pick'em trophy",
				"889 = gold cologne 2014 pick'em trophy",
				"890 = champion at dreamhack winter 2014",
				"891 = finalist at dreamhack winter 2014",
				"892 = semifinalist at dreamhack winter 2014",
				"893 = quarterfinalist at dreamhack winter 2014",
				"894 = bronze dreamhack 2014 pick'em trophy",
				"895 = silver dreamhack 2014 pick'em trophy",
				"896 = gold dreamhack 2014 pick'em trophy",
				"897 = champion at esl one katowice 2015",
				"898 = finalist at esl one katowice 2015",
				"899 = semifinalist at esl one katowice 2015",
				"900 = quarterfinalist at esl one katowice 2015",
				"901 = bronze katowice 2015 pick'em trophy",
				"902 = silver katowice 2015 pick'em trophy",
				"903 = gold katowice 2015 pick'em trophy",
				"904 = champion at esl one cologne 2015",
				"905 = finalist at esl one cologne 2015",
				"906 = semifinalist at esl one cologne 2015",
				"907 = quarterfinalist at esl one cologne 2015",
				"908 = bronze cologne 2015 pick'em trophy",
				"909 = silver cologne 2015 pick'em trophy",
				"910 = gold cologne 2015 pick'em trophy",
				"911 = bronze cluj-napoca 2015 pick'em trophy",
				"912 = silver cluj-napoca 2015 pick'em trophy",
				"913 = gold cluj-napoca 2015 pick'em trophy",
				"914 = bronze cluj-napoca 2015 fantasy trophy",
				"915 = silver cluj-napoca 2015 fantasy trophy",
				"916 = gold cluj-napoca 2015 fantasy trophy",
				"917 = champion at dreamhack cluj-napoca 2015",
				"918 = finalist at dreamhack cluj-napoca 2015",
				"919 = semifinalist at dreamhack cluj-napoca 2015",
				"920 = quarterfinalist at dreamhack cluj-napoca 2015",
				"921 = bronze columbus 2016 pick'em trophy",
				"922 = silver columbus 2016 pick'em trophy",
				"923 = gold columbus 2016 pick'em trophy",
				"924 = bronze columbus 2016 fantasy trophy",
				"925 = silver columbus 2016 fantasy troph",
				"926 = gold columbus 2016 fantasy trophy",
				"927 = champion at mlg columbus 2016",
				"928 = finalist at mlg columbus 2016",
				"929 = semifinalist at mlg columbus 2016",
				"930 = quarterfinalist at mlg columbus 2016",
				"931 = champion at esl one cologne 2016",
				"932 = finalist at esl one cologne 2016",
				"933 = semifinalist at esl one cologne 2016",
				"934 = quarterfinalist at esl one cologne 2016",
				"935 = bronze cologne 2016 pick'em trophy",
				"936 = silver cologne 2016 pick'em trophy",
				"937 = gold cologne 2016 pick'em trophy",
				"938 = bronze cologne 2016 fantasy trophy",
				"939 = silver cologne 2016 fantasy trophy",
				"940 = gold cologne 2016 fantasy trophy",
				"941 = champion at eleague atlanta 2017",
				"942 = finalist at eleague atlanta 2017",
				"943 = semifinalist at eleague atlanta 2017",
				"944 = quarterfinalist at eleague atlanta 2017",
				"945 = bronze atlanta 2017 pick'em trophy",
				"946 = silver atlanta 2017 pick'em trophy",
				"947 = gold atlanta 2017 pick'em trophy",
				"948 = champion at pgl krakow 2017",
				"949 = finalist at pgl krakow 2017",
				"950 = semifinalist at pgl krakow 2017",
				"951 = quarterfinalist at pgl krakow 2017 ",
				"952 = bronze krakow 2017 pick'em trophy",
				"953 = silver krakow 2017 pick'em trophy",
				"954 = gold krakow 2017 pick'em trophy",
				"955 = champion at eleague boston 2018",
				"956 = finalist at eleague boston 2018",
				"957 = semifinalist at eleague boston 2018",
				"958 = quarterfinalist at eleague boston 2018",
				"959 = bronze boston 2018 pick'em trophy",
				"960 = silver boston 2018 pick'em trophy",
				"961 = gold boston 2018 pick'em trophy",
				"1331 = 2015 service medal",
				"1332 = 2015 service medal",
				"1339 = 2016 service medal",
				"1340 = 2016 service medal",
				"1341 = 2016 service medal",
				"1342 = 2016 service medal",
				"1343 = 2016 service medal",
				"1344 = 2016 service medal",
				"1357 = 2017 service medal",
				"1358 = 2017 service medal",
				"1359 = 2017 service medal",
				"1360 = 2017 service medal",
				"1361 = 2017 service medal",
				"1362 = 2017 service medal",
				"1363 = 2017 service medal",
				"1367 = 2018 service medal",
				"1368 = 2018 service medal",
				"1369 = 2018 service medal",
				"1370 = 2018 service medal",
				"1371 = 2018 service medal",
				"1372 = 2018 service medal"
			};
			for (int i = 0; i < IM_ARRAYSIZE(medalids); i++)
				if (filter.PassFilter(medalids[i]))
					ImGui::Text("%s", medalids[i]);
			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	if (Settings::Misc::weaponids && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(350.f, 250.f));

		if (ImGui::Begin("weapon ids", &Settings::Misc::weaponids,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			static ImGuiTextFilter filter;
			filter.Draw();
			const char* weaponids[] = {
				"1 = desert eagle",
				"2 = dual berettas",
				"3 = five seven",
				"4 = glock-18",
				"7 = ak-47",
				"8 = aug",
				"9 = awp",
				"10 = famas",
				"11 = g3sg1",
				"13 = galil ar",
				"14 = m249",
				"16 = m4a4",
				"17 = mac-10",
				"19 = p90",
				"24 = ump-45",
				"25 = xm1014",
				"26 = pp-bizon",
				"27 = mag-7",
				"28 = negev",
				"29 = sawed-off",
				"30 = tec-9",
				"32 = p2000",
				"33 = mp7",
				"34 = mp9",
				"35 = nova",
				"36 = p250",
				"38 = scar-20",
				"39 = sg 553",
				"40 = ssg 08",
				"60 = m4a1-s",
				"61 = usp-s",
				"63 = cz75-auto",
				"64 = r8 revolver",
				"500 = bayonet",
				"505 = flip knife",
				"506 = gut knife",
				"507 = karambit",
				"508 = m9 bayonet",
				"509 = huntsman knife",
				"512 = falchion knife",
				"514 = bowie knife",
				"515 = butterfly knife",
				"516 = shadow daggers"
			};
			for (int i = 0; i < IM_ARRAYSIZE(weaponids); i++)
				if (filter.PassFilter(weaponids[i]))
					ImGui::Text("%s", weaponids[i]);

			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	if (Settings::Misc::stickerids && bIsGuiVisible)
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2(0.f, 0.f);

		ImGui::SetNextWindowSize(ImVec2(350.f, 250.f));

		if (ImGui::Begin("sticker ids", &Settings::Misc::stickerids,
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
		{
			static ImGuiTextFilter filter;
			filter.Draw();
			const char* Stickers[] =
			{
				"1 - shooter",
				"2 - shooter (foil)",
				"3 - shooter close",
				"4 - shooter close (foil)",
				"5 - blue snowflake",
				"6 - blue snowflake (foil)",
				"7 - polar bears",
				"8 - polar bears (foil)",
				"9 - mountain",
				"10 - mountain (foil)",
				"11 - frosty the hitman",
				"12 - frosty the hitman (foil)",
				"13 - lucky 13",
				"14 - aces high",
				"15 - aces high (holo)",
				"16 - i conquered",
				"17 - seek & destroy",
				"18 - black dog",
				"19 - fearsome",
				"20 - fearsome (holo)",
				"21 - cerberus",
				"22 - easy peasy",
				"23 - luck skill",
				"24 - vigilance",
				"25 - vigilance (holo)",
				"26 - lucky 13 (foil)",
				"27 - luck skill (foil)",
				"31 - bish (holo)",
				"32 - bash (holo)",
				"33 - bosh (holo)",
				"34 - banana",
				"35 - bomb code",
				"36 - chicken lover",
				"37 - crown (foil)",
				"38 - good game",
				"39 - good luck",
				"40 - have fun",
				"41 - let's roll-oll",
				"42 - let's roll-oll (holo)",
				"43 - metal",
				"44 - nice shot",
				"46 - stupid banana (foil)",
				"47 - welcome to the clutch",
				"48 - 3dmax | katowice 2014",
				"49 - 3dmax (holo) | katowice 2014",
				"50 - complexity gaming | katowice 2014",
				"51 - complexity gaming (holo) | katowice 2014",
				"52 - team dignitas | katowice 2014",
				"53 - team dignitas (holo) | katowice 2014",
				"55 - fnatic | katowice 2014",
				"56 - fnatic (holo) | katowice 2014",
				"57 - hellraisers | katowice 2014",
				"58 - hellraisers (holo) | katowice 2014",
				"59 - ibuypower | katowice 2014",
				"60 - ibuypower (holo) | katowice 2014",
				"61 - team ldlc.com | katowice 2014",
				"62 - team ldlc.com (holo) | katowice 2014",
				"63 - lgb esports | katowice 2014",
				"64 - lgb esports (holo) | katowice 2014",
				"65 - mousesports | katowice 2014",
				"66 - mousesports (holo) | katowice 2014",
				"67 - clan-mystik | katowice 2014",
				"68 - clan-mystik (holo) | katowice 2014",
				"69 - natus vincere | katowice 2014",
				"70 - natus vincere (holo) | katowice 2014",
				"71 - ninjas in pyjamas | katowice 2014",
				"72 - ninjas in pyjamas (holo) | katowice 2014",
				"73 - reason gaming | katowice 2014",
				"73 - reason gaming | katowice 2014",
				"74 - reason gaming (holo) | katowice 2014",
				"75 - titan | katowice 2014",
				"76 - titan (holo) | katowice 2014",
				"77 - virtus.pro | katowice 2014",
				"78 - virtus.pro (holo) | katowice 2014",
				"79 - vox eminor | katowice 2014",
				"80 - vox eminor (holo) | katowice 2014",
				"81 - esl wolf (foil) | katowice 2014",
				"82 - esl skull (foil) | katowice 2014",
				"83 - 3dmax (foil) | katowice 2014",
				"84 - complexity gaming (foil) | katowice 2014",
				"85 - team dignitas (foil) | katowice 2014",
				"86 - fnatic (foil) | katowice 2014",
				"87 - hellraisers (foil) | katowice 2014",
				"88 - ibuypower (foil) | katowice 2014",
				"89 - team ldlc.com (foil) | katowice 2014",
				"90 - lgb esports (foil) | katowice 2014",
				"91 - mousesports (foil) | katowice 2014",
				"92 - clan-mystik (foil) | katowice 2014",
				"93 - natus vincere (foil) | katowice 2014",
				"94 - ninjas in pyjamas (foil) | katowice 2014",
				"95 - reason gaming (foil) | katowice 2014",
				"96 - titan (foil) | katowice 2014",
				"100 - gold esl skull (foil) | katowice 2014",
				"101 - backstab",
				"102 - king on the field",
				"103 - howling dawn",
				"104 - bomb doge",
				"105 - burn them all",
				"106 - harp of war (holo)",
				"107 - flammable (foil)",
				"108 - headhunter (foil)",
				"109 - llama cannon",
				"110 - new sheriff (foil)",
				"111 - my other awp",
				"112 - shave master",
				"113 - rising skull",
				"114 - sneaky beaky like",
				"115 - swag (foil)",
				"116 - teamwork (holo)",
				"117 - to b or not to b",
				"118 - winged defuser",
				"119 - pocket bbq",
				"120 - death comes",
				"121 - rekt (holo)",
				"122 - cloud9 | cologne 2014",
				"123 - cloud9 (holo) | cologne 2014",
				"124 - fnatic | cologne 2014",
				"125 - fnatic (holo) | cologne 2014",
				"126 - hellraisers | cologne 2014",
				"127 - hellraisers (holo) | cologne 2014",
				"128 - ninjas in pyjamas | cologne 2014",
				"129 - ninjas in pyjamas (holo) | cologne 2014",
				"130 - team dignitas | cologne 2014",
				"131 - team dignitas (holo) | cologne 2014",
				"132 - team ldlc.com | cologne 2014",
				"133 - team ldlc.com (holo) | cologne 2014",
				"134 - virtus.pro | cologne 2014",
				"135 - virtus.pro (holo) | cologne 2014",
				"136 - copenhagen wolves | cologne 2014",
				"137 - copenhagen wolves (holo) | cologne 2014",
				"138 - dat team | cologne 2014",
				"139 - dat team (holo) | cologne 2014",
				"140 - epsilon esports | cologne 2014",
				"141 - epsilon esports (holo) | cologne 2014",
				"142 - ibuypower | cologne 2014",
				"143 - ibuypower (holo) | cologne 2014",
				"144 - london conspiracy | cologne 2014",
				"145 - london conspiracy (holo) | cologne 2014",
				"146 - natus vincere | cologne 2014",
				"147 - natus vincere (holo) | cologne 2014",
				"148 - titan | cologne 2014",
				"149 - titan (holo) | cologne 2014",
				"150 - vox eminor | cologne 2014",
				"151 - vox eminor (holo) | cologne 2014",
				"152 - mts gamegod wolf | cologne 2014",
				"153 - mts gamegod wolf (holo) | cologne 2014",
				"154 - esl one cologne 2014 (blue)",
				"155 - esl one cologne 2014 (red)",
				"156 - cloud9 (foil) | cologne 2014",
				"157 - fnatic (foil) | cologne 2014",
				"158 - hellraisers (foil) | cologne 2014",
				"159 - ninjas in pyjamas (foil) | cologne 2014",
				"160 - team dignitas (foil) | cologne 2014",
				"161 - team ldlc.com (foil) | cologne 2014",
				"162 - virtus.pro (foil) | cologne 2014",
				"163 - copenhagen wolves (foil) | cologne 2014",
				"164 - dat team (foil) | cologne 2014",
				"165 - epsilon esports (foil) | cologne 2014",
				"166 - ibuypower (foil) | cologne 2014",
				"167 - london conspiracy (foil) | cologne 2014",
				"168 - natus vincere (foil) | cologne 2014",
				"169 - titan (foil) | cologne 2014",
				"170 - vox eminor (foil) | cologne 2014",
				"171 - mts gamegod wolf (foil) | cologne 2014",
				"172 - esl one cologne 2014 (gold)",
				"173 - bossy burger",
				"174 - cat call",
				"175 - chicken strike",
				"176 - ct in banana",
				"177 - don't worry, i'm pro",
				"178 - fight like a girl",
				"179 - flashbang",
				"180 - kawaii killer ct",
				"181 - nelu the bear",
				"182 - one shot one kill",
				"183 - shooting star return",
				"184 - t on cat",
				"185 - war penguin",
				"186 - windy walking club",
				"187 - blitzkrieg",
				"188 - pigeon master",
				"189 - terrorized",
				"190 - till death do us part",
				"191 - stay frosty",
				"192 - doomed",
				"193 - queen of pain",
				"194 - trick or threat",
				"195 - trick or treat",
				"196 - witch",
				"197 - zombie lover",
				"198 - fnatic | dreamhack 2014",
				"199 - fnatic (holo) | dreamhack 2014",
				"200 - fnatic (foil) | dreamhack 2014",
				"201 - cloud9 | dreamhack 2014",
				"202 - cloud9 (holo) | dreamhack 2014",
				"203 - cloud9 (foil) | dreamhack 2014",
				"207 - virtus.pro | dreamhack 2014",
				"208 - virtus.pro (holo) | dreamhack 2014",
				"209 - virtus.pro (foil) | dreamhack 2014",
				"210 - ninjas in pyjamas | dreamhack 2014",
				"211 - ninjas in pyjamas (holo) | dreamhack 2014",
				"212 - ninjas in pyjamas (foil) | dreamhack 2014",
				"213 - natus vincere | dreamhack 2014",
				"214 - natus vincere (holo) | dreamhack 2014",
				"215 - natus vincere (foil) | dreamhack 2014",
				"219 - team dignitas | dreamhack 2014",
				"220 - team dignitas (holo) | dreamhack 2014",
				"221 - team dignitas (foil) | dreamhack 2014",
				"222 - bravado gaming | dreamhack 2014",
				"223 - esc gaming | dreamhack 2014",
				"224 - hellraisers | dreamhack 2014",
				"225 - ibuypower | dreamhack 2014",
				"226 - penta sports | dreamhack 2014",
				"227 - planetkey dynamics | dreamhack 2014",
				"228 - team ldlc.com | dreamhack 2014",
				"229 - myxmg | dreamhack 2014",
				"230 - dreamhack winter 2014",
				"231 - dreamhack winter 2014 (foil)",
				"232 - 3dmax | dreamhack 2014",
				"233 - copenhagen wolves | dreamhack 2014",
				"234 - dat team | dreamhack 2014",
				"235 - london conspiracy | dreamhack 2014",
				"236 - mousesports | dreamhack 2014",
				"237 - 3dmax (gold) | dreamhack 2014",
				"238 - bravado gaming (gold) | dreamhack 2014",
				"239 - cloud9 (gold) | dreamhack 2014",
				"240 - copenhagen wolves (gold) | dreamhack 2014",
				"241 - dat team (gold) | dreamhack 2014",
				"242 - team dignitas (gold) | dreamhack 2014",
				"243 - esc gaming (gold) | dreamhack 2014",
				"244 - fnatic (gold) | dreamhack 2014",
				"245 - hellraisers (gold) | dreamhack 2014",
				"246 - ibuypower 9gold) | dreamhack 2014",
				"247 - london conspiracy (gold) | dreamhack 2014",
				"248 - mousesports (gold) | dreamhack 2014",
				"249 - myxmg (gold) | dreamhack 2014",
				"250 - natus vincere (gold) | dreamhack 2014",
				"251 - ninjas in pyjamas (gold) | dreamhack 2014",
				"252 - penta sports (gold) | dreamhack 2014",
				"253 - planetkey dynamics (gold) | dreamhack 2014",
				"254 - team ldlc.com (gold) | dreamhack 2014",
				"255 - virtus.pro (gold) | dreamhack 2014",
				"256 - flipsid3 tactics | dreamhack 2014",
				"257 - flipsid3 tactics (gold) | dreamhack 2014",
				"258 - blood boiler",
				"259 - dinked",
				"260 - drug war veteran",
				"261 - ho ho ho",
				"262 - massive pear",
				"263 - my little friend",
				"264 - pandamonium",
				"265 - piece of cake",
				"266 - sas chicken",
				"267 - thug life",
				"268 - t-rekt",
				"269 - warowl",
				"270 - work for ammo",
				"271 - phoenix (foil)",
				"272 - bomb squad (foil)",
				"273 - flickshot",
				"274 - headshot guarantee",
				"275 - eco rush",
				"276 - just trolling",
				"278 - firestarter (holo)",
				"279 - lucky cat (foil)",
				"280 - robo",
				"281 - witchcraft",
				"282 - wanna fight",
				"283 - hostage rescue",
				"284 - hamster hawk",
				"285 - headless chicken",
				"286 - 3dmax | katowice 2015",
				"287 - 3dmax (holo) | katowice 2015",
				"288 - 3dmax (foil) | katowice 2015",
				"289 - 3dmax (gold) | katowice 2015",
				"290 - cloud9 g2a | katowice 2015",
				"291 - cloud9 g2a (holo) | katowice 2015",
				"292 - cloud9 g2a (foil) | katowice 2015",
				"293 - cloud9 g2a (gold) | katowice 2015",
				"294 - counter logic gaming | katowice 2015",
				"295 - counter logic gaming (holo) | katowice 2015",
				"296 - counter logic gaming (foil) | katowice 2015",
				"297 - counter logic gaming (gold) | katowice 2015",
				"300 - esl one (foil) | katowice 2015",
				"301 - esl one (gold) | katowice 2015",
				"302 - flipsid3 tactics | katowice 2015",
				"303 - flipsid3 tactics (holo) | katowice 2015",
				"304 - flipsid3 tactics (foil) | katowice 2015",
				"305 - flipsid3 tactics (gold) | katowice 2015",
				"306 - fnatic | katowice 2015",
				"307 - fnatic (holo) | katowice 2015",
				"308 - fnatic (foil) | katowice 2015",
				"309 - fnatic (gold) | katowice 2015",
				"310 - hellraisers | katowice 2015",
				"311 - hellraisers (holo) | katowice 2015",
				"312 - hellraisers (foil) | katowice 2015",
				"313 - hellraisers (gold) | katowice 2015",
				"314 - keyd stars | katowice 2015",
				"315 - keyd stars (holo) | katowice 2015",
				"316 - keyd stars (foil) | katowice 2015",
				"317 - keyd stars (gold) | katowice 2015",
				"318 - lgb esports | katowice 2015",
				"319 - lgb esports (holo) | katowice 2015",
				"320 - lgb esports (foil) | katowice 2015",
				"321 - lgb esports (gold) | katowice 2015",
				"322 - natus vincere | katowice 2015",
				"323 - natus vincere (holo) | katowice 2015",
				"324 - natus vincere (foil) | katowice 2015",
				"325 - natus vincere (gold) | katowice 2015",
				"326 - ninjas in pyjamas  | katowice 2015",
				"327 - ninjas in pyjamas (holo) | katowice 2015",
				"328 - ninjas in pyjamas (foil) | katowice 2015",
				"329 - ninjas in pyjamas (gold) | katowice 2015",
				"330 - penta sports  | katowice 2015",
				"331 - penta sports (holo) | katowice 2015",
				"332 - penta sports (foil) | katowice 2015",
				"333 - penta sports (gold) | katowice 2015",
				"334 - team envyus | katowice 2015",
				"335 - team envyus (holo) | katowice 2015",
				"336 - team envyus (foil) | katowice 2015",
				"337 - team envyus (gold) | katowice 2015",
				"338 - tsm kinguin | katowice 2015",
				"339 - tsm kinguin (holo) | katowice 2015",
				"340 - tsm kinguin (foil) | katowice 2015",
				"341 - tsm kinguin (gold) | katowice 2015",
				"342 - titan | katowice 2015",
				"343 - titan (holo) | katowice 2015",
				"344 - titan (foil) | katowice 2015",
				"345 - titan (gold) | katowice 2015",
				"346 - virtus.pro | katowice 2015",
				"347 - virtus.pro (holo) | katowice 2015",
				"348 - virtus.pro (foil) | katowice 2015",
				"349 - virtus.pro (gold) | katowice 2015",
				"350 - vox eminor  | katowice 2015",
				"351 - vox eminor (holo) | katowice 2015",
				"352 - vox eminor (foil) | katowice 2015",
				"353 - vox eminor (gold) | katowice 2015",
				"354 - esl one | katowice 2015",
				"355 - chabo",
				"356 - bombsquad",
				"357 - bombsquad (foil)",
				"358 - the guru",
				"359 - silent ninja",
				"360 - silent ninja (foil)",
				"361 - the samurai",
				"362 - skull lil boney",
				"363 - skulltorgeist",
				"364 - skull troop",
				"365 - salute!",
				"366 - the spartan",
				"367 - unicorn",
				"368 - unicorn (holo)",
				"369 - the zombie",
				"370 - awp country",
				"371 - chi bomb",
				"372 - doru the fox",
				"373 - knife club",
				"374 - cs on the mind",
				"375 - ninja defuse",
				"376 - pros don't fake",
				"377 - kawaii killer terrorist",
				"378 - baaa-ckstabber!",
				"379 - delicious tears",
				"380 - pronax | cologne 2015",
				"381 - pronax (foil) | cologne 2015",
				"382 - pronax (gold) | cologne 2015",
				"383 - flusha | cologne 2015",
				"384 - flusha (foil) | cologne 2015",
				"385 - flusha (gold) | cologne 2015",
				"386 - jw | cologne 2015",
				"387 - jw (foil) | cologne 2015",
				"388 - jw (gold) | cologne 2015",
				"389 - krimz | cologne 2015",
				"390 - krimz (foil) | cologne 2015",
				"391 - krimz (gold) | cologne 2015",
				"392 - olofmeister | cologne 2015",
				"393 - olofmeister (foil) | cologne 2015",
				"394 - olofmeister (gold) | cologne 2015",
				"395 - fallen | cologne 2015",
				"396 - fallen (foil) | cologne 2015",
				"397 - fallen (gold) | cologne 2015",
				"398 - steel | cologne 2015",
				"399 - steel (foil) | cologne 2015",
				"400 - steel (gold) | cologne 2015",
				"401 - fer | cologne 2015",
				"402 - fer (foil) | cologne 2015",
				"403 - fer (gold) | cologne 2015",
				"404 - boltz | cologne 2015",
				"405 - boltz (foil) | cologne 2015",
				"406 - boltz (gold) | cologne 2015",
				"407 - coldzera | cologne 2015",
				"408 - coldzera (foil) | cologne 2015",
				"409 - coldzera (gold) | cologne 2015",
				"410 - guardian | cologne 2015",
				"411 - guardian (foil) | cologne 2015",
				"412 - guardian (gold) | cologne 2015",
				"413 - zeus | cologne 2015",
				"414 - zeus (foil) | cologne 2015",
				"415 - zeus (gold) | cologne 2015",
				"416 - seized | cologne 2015",
				"417 - seized (foil) | cologne 2015",
				"418 - seized (gold) | cologne 2015",
				"419 - edward | cologne 2015",
				"420 - edward (foil) | cologne 2015",
				"421 - edward (gold) | cologne 2015",
				"422 - flamie | cologne 2015",
				"423 - flamie (foil) | cologne 2015",
				"424 - flamie (gold) | cologne 2015",
				"425 - xizt | cologne 2015",
				"426 - xizt (foil) | cologne 2015",
				"427 - xizt (gold) | cologne 2015",
				"428 - f0rest | cologne 2015",
				"429 - f0rest (foil) | cologne 2015",
				"430 - f0rest (gold) | cologne 2015",
				"431 - get_right | cologne 2015",
				"432 - get_right (foil) | cologne 2015",
				"433 - get_right (gold) | cologne 2015",
				"434 - friberg | cologne 2015",
				"435 - friberg (foil) | cologne 2015",
				"436 - friberg (gold) | cologne 2015",
				"437 - allu | cologne 2015",
				"438 - allu (foil) | cologne 2015",
				"439 - allu (gold) | cologne 2015",
				"440 - kennys | cologne 2015",
				"441 - kennys (foil) | cologne 2015",
				"442 - kennys (gold) | cologne 2015",
				"443 - kioshima | cologne 2015",
				"444 - kioshima (foil) | cologne 2015",
				"445 - kioshima (gold) | cologne 2015",
				"446 - happy | cologne 2015",
				"447 - happy (foil) | cologne 2015",
				"448 - happy (gold) | cologne 2015",
				"449 - apex | cologne 2015",
				"450 - apex (foil) | cologne 2015",
				"451 - apex (gold) | cologne 2015",
				"452 - nbk- | cologne 2015",
				"453 - nbk- (foil) | cologne 2015",
				"454 - nbk- (gold) | cologne 2015",
				"455 - karrigan | cologne 2015",
				"456 - karrigan (foil) | cologne 2015",
				"457 - karrigan (gold) | cologne 2015",
				"458 - device | cologne 2015",
				"459 - device (foil) | cologne 2015",
				"460 - device (gold) | cologne 2015",
				"461 - dupreeh | cologne 2015",
				"462 - dupreeh (foil) | cologne 2015",
				"463 - dupreeh (gold) | cologne 2015",
				"464 - xyp9x | cologne 2015",
				"465 - xyp9x (foil) | cologne 2015",
				"466 - xyp9x (gold) | cologne 2015",
				"467 - cajunb | cologne 2015",
				"468 - cajunb (foil) | cologne 2015",
				"469 - cajunb (gold) | cologne 2015",
				"470 - neo | cologne 2015",
				"471 - neo (foil) | cologne 2015",
				"472 - neo (gold) | cologne 2015",
				"473 - pashabiceps | cologne 2015",
				"474 - pashabiceps (foil) | cologne 2015",
				"475 - pashabiceps (gold) | cologne 2015",
				"476 - taz | cologne 2015",
				"477 - taz (foil) | cologne 2015",
				"478 - taz (gold) | cologne 2015",
				"479 - snax | cologne 2015",
				"480 - snax (foil) | cologne 2015",
				"481 - snax (gold) | cologne 2015",
				"482 - byali | cologne 2015",
				"483 - byali (foil) | cologne 2015",
				"484 - byali (gold) | cologne 2015",
				"485 - chrisj | cologne 2015",
				"486 - chrisj (foil) | cologne 2015",
				"487 - chrisj (gold) | cologne 2015",
				"488 - gob b | cologne 2015",
				"489 - gob b (foil) | cologne 2015",
				"490 - gob b (gold) | cologne 2015",
				"491 - denis | cologne 2015",
				"492 - denis (foil) | cologne 2015",
				"493 - denis (gold) | cologne 2015",
				"494 - nex | cologne 2015",
				"495 - nex (foil) | cologne 2015",
				"496 - nex (gold) | cologne 2015",
				"497 - spiidi | cologne 2015",
				"498 - spiidi (foil) | cologne 2015",
				"499 - spiidi (gold) | cologne 2015",
				"500 - azr | cologne 2015",
				"501 - azr (foil) | cologne 2015",
				"502 - azr (gold) | cologne 2015",
				"503 - havoc | cologne 2015",
				"504 - havoc (foil) | cologne 2015",
				"505 - havoc (gold) | cologne 2015",
				"506 - jks | cologne 2015",
				"507 - jks (foil) | cologne 2015",
				"508 - jks (gold) | cologne 2015",
				"509 - spunj | cologne 2015",
				"510 - spunj (foil) | cologne 2015",
				"511 - spunj (gold) | cologne 2015",
				"512 - yam | cologne 2015",
				"513 - yam (foil) | cologne 2015",
				"514 - yam (gold) | cologne 2015",
				"515 - ustilo | cologne 2015",
				"516 - ustilo (foil) | cologne 2015",
				"517 - ustilo (gold) | cologne 2015",
				"518 - rickeh | cologne 2015",
				"519 - rickeh (foil) | cologne 2015",
				"520 - rickeh (gold) | cologne 2015",
				"521 - emagine | cologne 2015",
				"522 - emagine (foil) | cologne 2015",
				"523 - emagine (gold) | cologne 2015",
				"524 - snyper | cologne 2015",
				"525 - snyper (foil) | cologne 2015",
				"526 - snyper (gold) | cologne 2015",
				"527 - james | cologne 2015",
				"528 - james (foil) | cologne 2015",
				"529 - james (gold) | cologne 2015",
				"530 - markeloff | cologne 2015",
				"531 - markeloff (foil) | cologne 2015",
				"532 - markeloff (gold) | cologne 2015",
				"533 - b1ad3 | cologne 2015",
				"534 - b1ad3 (foil) | cologne 2015",
				"535 - b1ad3 (gold) | cologne 2015",
				"536 - bondik | cologne 2015",
				"537 - bondik (foil) | cologne 2015",
				"538 - bondik (gold) | cologne 2015",
				"539 - worldedit | cologne 2015",
				"540 - worldedit (foil) | cologne 2015",
				"541 - worldedit (gold) | cologne 2015",
				"542 - davcost | cologne 2015",
				"543 - davcost (foil) | cologne 2015",
				"544 - davcost (gold) | cologne 2015",
				"545 - dennis | cologne 2015",
				"546 - dennis (foil) | cologne 2015",
				"547 - dennis (gold) | cologne 2015",
				"548 - scream | cologne 2015",
				"549 - scream (foil) | cologne 2015",
				"550 - scream (gold) | cologne 2015",
				"551 - rain | cologne 2015",
				"552 - rain (foil) | cologne 2015",
				"553 - rain (gold) | cologne 2015",
				"554 - maikelele | cologne 2015",
				"555 - maikelele (foil) | cologne 2015",
				"556 - maikelele (gold) | cologne 2015",
				"557 - fox | cologne 2015",
				"558 - fox (foil) | cologne 2015",
				"559 - fox (gold) | cologne 2015",
				"560 - rallen | cologne 2015",
				"561 - rallen (foil) | cologne 2015",
				"562 - rallen (gold) | cologne 2015",
				"563 - hyper | cologne 2015",
				"564 - hyper (foil) | cologne 2015",
				"565 - hyper (gold) | cologne 2015",
				"566 - peet | cologne 2015",
				"567 - peet (foil) | cologne 2015",
				"568 - peet (gold) | cologne 2015",
				"569 - furlan | cologne 2015",
				"570 - furlan (foil) | cologne 2015",
				"571 - furlan (gold) | cologne 2015",
				"572 - gruby | cologne 2015",
				"573 - gruby (foil) | cologne 2015",
				"574 - gruby (gold) | cologne 2015",
				"575 - maniac | cologne 2015",
				"576 - maniac (foil) | cologne 2015",
				"577 - maniac (gold) | cologne 2015",
				"578 - ex6tenz | cologne 2015",
				"579 - ex6tenz (foil) | cologne 2015",
				"580 - ex6tenz (gold) | cologne 2015",
				"581 - shox | cologne 2015",
				"582 - shox (foil) | cologne 2015",
				"583 - shox (gold) | cologne 2015",
				"584 - smithzz | cologne 2015",
				"585 - smithzz (foil) | cologne 2015",
				"586 - smithzz (gold) | cologne 2015",
				"587 - rpk | cologne 2015",
				"588 - rpk (foil) | cologne 2015",
				"589 - rpk (gold) | cologne 2015",
				"590 - hazed | cologne 2015",
				"591 - hazed (foil) | cologne 2015",
				"592 - hazed (gold) | cologne 2015",
				"593 - fns | cologne 2015",
				"594 - fns (foil) | cologne 2015",
				"595 - fns (gold) | cologne 2015",
				"596 - jdm64 | cologne 2015",
				"597 - jdm64 (foil) | cologne 2015",
				"598 - jdm64 (gold) | cologne 2015",
				"599 - reltuc | cologne 2015",
				"600 - reltuc (foil) | cologne 2015",
				"601 - reltuc (gold) | cologne 2015",
				"602 - tarik | cologne 2015",
				"603 - tarik (foil) | cologne 2015",
				"604 - tarik (gold) | cologne 2015",
				"605 - n0thing | cologne 2015",
				"606 - n0thing (foil) | cologne 2015",
				"607 - n0thing (gold) | cologne 2015",
				"608 - seang@res | cologne 2015",
				"609 - seang@res (foil) | cologne 2015",
				"610 - seang@res (gold) | cologne 2015",
				"611 - shroud | cologne 2015",
				"612 - shroud (foil) | cologne 2015",
				"613 - shroud (gold) | cologne 2015",
				"614 - freakazoid | cologne 2015",
				"615 - freakazoid (foil) | cologne 2015",
				"616 - freakazoid (gold) | cologne 2015",
				"617 - skadoodle | cologne 2015",
				"618 - skadoodle (foil) | cologne 2015",
				"619 - skadoodle (gold) | cologne 2015",
				"620 - fnatic | cologne 2015",
				"621 - fnatic (foil) | cologne 2015",
				"622 - fnatic (gold) | cologne 2015",
				"623 - virtus.pro | cologne 2015",
				"624 - virtus.pro (foil) | cologne 2015",
				"625 - virtus.pro (gold) | cologne 2015",
				"626 - mousesports | cologne 2015",
				"627 - mousesports (foil) | cologne 2015",
				"628 - mousesports (gold) | cologne 2015",
				"629 - natus vincere | cologne 2015",
				"630 - natus vincere (foil) | cologne 2015",
				"631 - natus vincere (gold) | cologne 2015",
				"632 - renegades | cologne 2015",
				"633 - renegades (foil) | cologne 2015",
				"634 - renegades (gold) | cologne 2015",
				"635 - team kinguin | cologne 2015",
				"636 - team kinguin (foil) | cologne 2015",
				"637 - team kinguin (gold) | cologne 2015",
				"638 - team ebettle | cologne 2015",
				"639 - team ebettle (foil) | cologne 2015",
				"640 - team ebettle (gold) | cologne 2015",
				"641 - cloud9 g2a | cologne 2015",
				"642 - cloud9 g2a (foil) | cologne 2015",
				"643 - cloud9 g2a (gold) | cologne 2015",
				"644 - ninjas in pyjamas | cologne 2015",
				"645 - ninjas in pyjamas (foil) | cologne 2015",
				"646 - ninjas in pyjamas (gold) | cologne 2015",
				"647 - team envyus | cologne 2015",
				"648 - team envyus (foil) | cologne 2015",
				"649 - team envyus (gold) | cologne 2015",
				"650 - luminosity gaming | cologne 2015",
				"651 - luminosity gaming (foil) | cologne 2015",
				"652 - luminosity gaming (gold) | cologne 2015",
				"653 - team solomid | cologne 2015",
				"654 - team solomid (foil) | cologne 2015",
				"655 - team solomid (gold) | cologne 2015",
				"656 - team immunity | cologne 2015",
				"657 - team immunity (foil) | cologne 2015",
				"658 - team immunity (gold) | cologne 2015",
				"659 - flipsid3 tactics | cologne 2015",
				"660 - flipsid3 tactics (foil) | cologne 2015",
				"661 - flipsid3 tactics (gold) | cologne 2015",
				"662 - titan | cologne 2015",
				"663 - titan (foil) | cologne 2015",
				"664 - titan (gold) | cologne 2015",
				"665 - counter logic gaming | cologne 2015",
				"666 - counter logic gaming (foil) | cologne 2015",
				"667 - counter logic gaming (gold) | cologne 2015",
				"668 - esl | cologne 2015",
				"669 - esl (foil) | cologne 2015",
				"670 - esl (gold) | cologne 2015",
				"671 - reltuc | cluj-napoca 2015",
				"672 - reltuc (foil) | cluj-napoca 2015",
				"673 - reltuc (gold) | cluj-napoca 2015",
				"674 - fns | cluj-napoca 2015",
				"675 - fns (foil) | cluj-napoca 2015",
				"676 - fns (gold) | cluj-napoca 2015",
				"677 - hazed | cluj-napoca 2015",
				"678 - hazed (foil) | cluj-napoca 2015",
				"679 - hazed (gold) | cluj-napoca 2015",
				"680 - jdm64 | cluj-napoca 2015",
				"681 - jdm64 (foil) | cluj-napoca 2015",
				"682 - jdm64 (gold) | cluj-napoca 2015",
				"683 - tarik | cluj-napoca 2015",
				"684 - tarik (foil) | cluj-napoca 2015",
				"685 - tarik (gold) | cluj-napoca 2015",
				"686 - freakazoid | cluj-napoca 2015",
				"687 - freakazoid (foil) | cluj-napoca 2015",
				"688 - freakazoid (gold) | cluj-napoca 2015",
				"689 - seang@res | cluj-napoca 2015",
				"690 - seang@res (foil) | cluj-napoca 2015",
				"691 - seang@res (gold) | cluj-napoca 2015",
				"692 - shroud | cluj-napoca 2015",
				"693 - shroud (foil) | cluj-napoca 2015",
				"694 - shroud (gold) | cluj-napoca 2015",
				"695 - skadoodle | cluj-napoca 2015",
				"696 - skadoodle (foil) | cluj-napoca 2015",
				"697 - skadoodle (gold) | cluj-napoca 2015",
				"698 - n0thing | cluj-napoca 2015",
				"699 - n0thing (foil) | cluj-napoca 2015",
				"700 - n0thing (gold) | cluj-napoca 2015",
				"701 - apex | cluj-napoca 2015",
				"702 - apex (foil) | cluj-napoca 2015",
				"703 - apex (gold) | cluj-napoca 2015",
				"704 - happy | cluj-napoca 2015",
				"705 - happy (foil) | cluj-napoca 2015",
				"706 - happy (gold) | cluj-napoca 2015",
				"707 - kioshima | cluj-napoca 2015",
				"708 - kioshima (foil) | cluj-napoca 2015",
				"709 - kioshima (gold) | cluj-napoca 2015",
				"710 - kennys | cluj-napoca 2015",
				"711 - kennys (foil) | cluj-napoca 2015",
				"712 - kennys (gold) | cluj-napoca 2015",
				"713 - nbk- | cluj-napoca 2015",
				"714 - nbk- (foil) | cluj-napoca 2015",
				"715 - nbk- (gold) | cluj-napoca 2015",
				"716 - b1ad3 | cluj-napoca 2015",
				"717 - b1ad3 (foil) | cluj-napoca 2015",
				"718 - b1ad3 (gold) | cluj-napoca 2015",
				"719 - bondik | cluj-napoca 2015",
				"720 - bondik (foil) | cluj-napoca 2015",
				"721 - bondik (gold) | cluj-napoca 2015",
				"722 - davcost | cluj-napoca 2015",
				"723 - davcost (foil) | cluj-napoca 2015",
				"724 - davcost (gold) | cluj-napoca 2015",
				"725 - markeloff | cluj-napoca 2015",
				"726 - markeloff (foil) | cluj-napoca 2015",
				"727 - markeloff (gold) | cluj-napoca 2015",
				"728 - worldedit | cluj-napoca 2015",
				"729 - worldedit (foil) | cluj-napoca 2015",
				"730 - worldedit (gold) | cluj-napoca 2015",
				"731 - flusha | cluj-napoca 2015",
				"732 - flusha (foil) | cluj-napoca 2015",
				"733 - flusha (gold) | cluj-napoca 2015",
				"734 - jw | cluj-napoca 2015",
				"735 - jw (foil) | cluj-napoca 2015",
				"736 - jw (gold) | cluj-napoca 2015",
				"737 - krimz | cluj-napoca 2015",
				"738 - krimz (foil) | cluj-napoca 2015",
				"739 - krimz (gold) | cluj-napoca 2015",
				"740 - olofmeister | cluj-napoca 2015",
				"741 - olofmeister (foil) | cluj-napoca 2015",
				"742 - olofmeister (gold) | cluj-napoca 2015",
				"743 - pronax | cluj-napoca 2015",
				"744 - pronax (foil) | cluj-napoca 2015",
				"745 - pronax (gold) | cluj-napoca 2015",
				"746 - dennis | cluj-napoca 2015",
				"747 - dennis (foil) | cluj-napoca 2015",
				"748 - dennis (gold) | cluj-napoca 2015",
				"749 - fox | cluj-napoca 2015",
				"750 - fox (foil) | cluj-napoca 2015",
				"751 - fox (gold) | cluj-napoca 2015",
				"752 - maikelele | cluj-napoca 2015",
				"753 - maikelele (foil) | cluj-napoca 2015",
				"754 - maikelele (gold) | cluj-napoca 2015",
				"755 - rain | cluj-napoca 2015",
				"756 - rain (foil) | cluj-napoca 2015",
				"757 - rain (gold) | cluj-napoca 2015",
				"758 - jkaem | cluj-napoca 2015",
				"759 - jkaem (foil) | cluj-napoca 2015",
				"760 - jkaem (gold) | cluj-napoca 2015",
				"761 - boltz | cluj-napoca 2015",
				"762 - boltz (foil) | cluj-napoca 2015",
				"763 - boltz (gold) | cluj-napoca 2015",
				"764 - coldzera | cluj-napoca 2015",
				"765 - coldzera (foil) | cluj-napoca 2015",
				"766 - coldzera (gold) | cluj-napoca 2015",
				"767 - fallen | cluj-napoca 2015",
				"768 - fallen (foil) | cluj-napoca 2015",
				"769 - fallen (gold) | cluj-napoca 2015",
				"770 - fer | cluj-napoca 2015",
				"771 - fer (foil) | cluj-napoca 2015",
				"772 - fer (gold) | cluj-napoca 2015",
				"773 - steel | cluj-napoca 2015",
				"774 - steel (foil) | cluj-napoca 2015",
				"775 - steel (gold) | cluj-napoca 2015",
				"776 - chrisj | cluj-napoca 2015",
				"777 - chrisj (foil) | cluj-napoca 2015",
				"778 - chrisj (gold) | cluj-napoca 2015",
				"779 - denis | cluj-napoca 2015",
				"780 - denis (foil) | cluj-napoca 2015",
				"781 - denis (gold) | cluj-napoca 2015",
				"782 - gob b | cluj-napoca 2015",
				"783 - gob b (foil) | cluj-napoca 2015",
				"784 - gob b (gold) | cluj-napoca 2015",
				"785 - nex | cluj-napoca 2015",
				"786 - nex (foil) | cluj-napoca 2015",
				"787 - nex (gold) | cluj-napoca 2015",
				"788 - niko | cluj-napoca 2015",
				"789 - niko (foil) | cluj-napoca 2015",
				"790 - niko (gold) | cluj-napoca 2015",
				"791 - edward | cluj-napoca 2015",
				"792 - edward (foil) | cluj-napoca 2015",
				"793 - edward (gold) | cluj-napoca 2015",
				"794 - flamie | cluj-napoca 2015",
				"795 - flamie (foil) | cluj-napoca 2015",
				"796 - flamie (gold) | cluj-napoca 2015",
				"797 - guardian | cluj-napoca 2015",
				"798 - guardian (foil) | cluj-napoca 2015",
				"799 - guardian (gold) | cluj-napoca 2015",
				"800 - seized | cluj-napoca 2015",
				"801 - seized (foil) | cluj-napoca 2015",
				"802 - seized (gold) | cluj-napoca 2015",
				"803 - zeus | cluj-napoca 2015",
				"804 - zeus (foil) | cluj-napoca 2015",
				"805 - zeus (gold) | cluj-napoca 2015",
				"806 - allu | cluj-napoca 2015",
				"807 - allu (foil) | cluj-napoca 2015",
				"808 - allu (gold) | cluj-napoca 2015",
				"809 - f0rest | cluj-napoca 2015",
				"810 - f0rest (foil) | cluj-napoca 2015",
				"811 - f0rest (gold) | cluj-napoca 2015",
				"812 - friberg | cluj-napoca 2015",
				"813 - friberg (foil) | cluj-napoca 2015",
				"814 - friberg (gold) | cluj-napoca 2015",
				"815 - get_right | cluj-napoca 2015",
				"816 - get_right (foil) | cluj-napoca 2015",
				"817 - get_right (gold) | cluj-napoca 2015",
				"818 - xizt | cluj-napoca 2015",
				"819 - xizt (foil) | cluj-napoca 2015",
				"820 - xizt (gold) | cluj-napoca 2015",
				"821 - aizy | cluj-napoca 2015",
				"822 - aizy (foil) | cluj-napoca 2015",
				"823 - aizy (gold) | cluj-napoca 2015",
				"824 - kjaerbye | cluj-napoca 2015",
				"825 - kjaerbye (foil) | cluj-napoca 2015",
				"826 - kjaerbye (gold) | cluj-napoca 2015",
				"827 - msl | cluj-napoca 2015",
				"828 - msl (foil) | cluj-napoca 2015",
				"829 - msl (gold) | cluj-napoca 2015",
				"830 - pimp | cluj-napoca 2015",
				"831 - pimp (foil) | cluj-napoca 2015",
				"832 - pimp (gold) | cluj-napoca 2015",
				"833 - tenzki | cluj-napoca 2015",
				"834 - tenzki (foil) | cluj-napoca 2015",
				"835 - tenzki (gold) | cluj-napoca 2015",
				"836 - adren | cluj-napoca 2015",
				"837 - adren (foil) | cluj-napoca 2015",
				"838 - adren (gold) | cluj-napoca 2015",
				"839 - elige | cluj-napoca 2015",
				"840 - elige (foil) | cluj-napoca 2015",
				"841 - elige (gold) | cluj-napoca 2015",
				"842 - fugly | cluj-napoca 2015",
				"843 - fugly (foil) | cluj-napoca 2015",
				"844 - fugly (gold) | cluj-napoca 2015",
				"845 - hiko | cluj-napoca 2015",
				"846 - hiko (foil) | cluj-napoca 2015",
				"847 - hiko (gold) | cluj-napoca 2015",
				"848 - nitr0 | cluj-napoca 2015",
				"849 - nitr0 (foil) | cluj-napoca 2015",
				"850 - nitr0 (gold) | cluj-napoca 2015",
				"851 - ex6tenz | cluj-napoca 2015",
				"852 - ex6tenz (foil) | cluj-napoca 2015",
				"853 - ex6tenz (gold) | cluj-napoca 2015",
				"854 - rpk | cluj-napoca 2015",
				"855 - rpk (foil) | cluj-napoca 2015",
				"856 - rpk (gold) | cluj-napoca 2015",
				"857 - scream | cluj-napoca 2015",
				"858 - scream (foil) | cluj-napoca 2015",
				"859 - scream (gold) | cluj-napoca 2015",
				"860 - shox | cluj-napoca 2015",
				"861 - shox (foil) | cluj-napoca 2015",
				"862 - shox (gold) | cluj-napoca 2015",
				"863 - smithzz | cluj-napoca 2015",
				"864 - smithzz (foil) | cluj-napoca 2015",
				"865 - smithzz (gold) | cluj-napoca 2015",
				"866 - cajunb | cluj-napoca 2015",
				"867 - cajunb (foil) | cluj-napoca 2015",
				"868 - cajunb (gold) | cluj-napoca 2015",
				"869 - device | cluj-napoca 2015",
				"870 - device (foil) | cluj-napoca 2015",
				"871 - device (gold) | cluj-napoca 2015",
				"872 - dupreeh | cluj-napoca 2015",
				"873 - dupreeh (foil) | cluj-napoca 2015",
				"874 - dupreeh (gold) | cluj-napoca 2015",
				"875 - karrigan | cluj-napoca 2015",
				"876 - karrigan (foil) | cluj-napoca 2015",
				"877 - karrigan (gold) | cluj-napoca 2015",
				"878 - xyp9x | cluj-napoca 2015",
				"879 - xyp9x (foil) | cluj-napoca 2015",
				"880 - xyp9x (gold) | cluj-napoca 2015",
				"881 - furlan | cluj-napoca 2015",
				"882 - furlan (foil) | cluj-napoca 2015",
				"883 - furlan (gold) | cluj-napoca 2015",
				"884 - gruby | cluj-napoca 2015",
				"885 - gruby (foil) | cluj-napoca 2015",
				"886 - gruby (gold) | cluj-napoca 2015",
				"887 - hyper | cluj-napoca 2015",
				"888 - hyper (foil) | cluj-napoca 2015",
				"889 - hyper (gold) | cluj-napoca 2015",
				"890 - peet | cluj-napoca 2015",
				"891 - peet (foil) | cluj-napoca 2015",
				"892 - peet (gold) | cluj-napoca 2015",
				"893 - rallen | cluj-napoca 2015",
				"894 - rallen (foil) | cluj-napoca 2015",
				"895 - rallen (gold) | cluj-napoca 2015",
				"896 - byali | cluj-napoca 2015",
				"897 - byali (foil) | cluj-napoca 2015",
				"898 - byali (gold) | cluj-napoca 2015",
				"899 - neo | cluj-napoca 2015",
				"900 - neo (foil) | cluj-napoca 2015",
				"901 - neo (gold) | cluj-napoca 2015",
				"902 - pashabiceps | cluj-napoca 2015",
				"903 - pashabiceps (foil) | cluj-napoca 2015",
				"904 - pashabiceps (gold) | cluj-napoca 2015",
				"905 - snax | cluj-napoca 2015",
				"906 - snax (foil) | cluj-napoca 2015",
				"907 - snax (gold) | cluj-napoca 2015",
				"908 - taz | cluj-napoca 2015",
				"909 - taz (foil) | cluj-napoca 2015",
				"910 - taz (gold) | cluj-napoca 2015",
				"911 - ninjas in pyjamas | cluj-napoca 2015",
				"912 - ninjas in pyjamas (foil) | cluj-napoca 2015",
				"913 - ninjas in pyjamas (gold) | cluj-napoca 2015",
				"914 - team dignitas | cluj-napoca 2015",
				"915 - team dignitas (foil) | cluj-napoca 2015",
				"916 - team dignitas (gold) | cluj-napoca 2015",
				"917 - counter logic gaming | cluj-napoca 2015",
				"918 - counter logic gaming (foil) | cluj-napoca 2015",
				"919 - counter logic gaming (gold) | cluj-napoca 2015",
				"920 - vexed gaming | cluj-napoca 2015",
				"921 - vexed gaming (foil) | cluj-napoca 2015",
				"922 - vexed gaming (gold) | cluj-napoca 2015",
				"923 - flipsid3 tactics | cluj-napoca 2015",
				"924 - flipsid3 tactics (foil) | cluj-napoca 2015",
				"925 - flipsid3 tactics (gold) | cluj-napoca 2015",
				"926 - team liquid | cluj-napoca 2015",
				"927 - team liquid (foil) | cluj-napoca 2015",
				"928 - team liquid (gold) | cluj-napoca 2015",
				"929 - mousesports | cluj-napoca 2015",
				"930 - mousesports (foil) | cluj-napoca 2015",
				"931 - mousesports (gold) | cluj-napoca 2015",
				"932 - natus vincere | cluj-napoca 2015",
				"933 - natus vincere (foil) | cluj-napoca 2015",
				"934 - natus vincere (gold) | cluj-napoca 2015",
				"935 - virtus.pro | cluj-napoca 2015",
				"936 - virtus.pro (foil) | cluj-napoca 2015",
				"937 - virtus.pro (gold) | cluj-napoca 2015",
				"938 - cloud9 | cluj-napoca 2015",
				"939 - cloud9 (foil) | cluj-napoca 2015",
				"940 - cloud9 (gold) | cluj-napoca 2015",
				"941 - g2 esports | cluj-napoca 2015",
				"942 - g2 esports (foil) | cluj-napoca 2015",
				"943 - g2 esports (gold) | cluj-napoca 2015",
				"944 - titan | cluj-napoca 2015",
				"945 - titan (foil) | cluj-napoca 2015",
				"946 - titan (gold) | cluj-napoca 2015",
				"947 - team solomid | cluj-napoca 2015",
				"948 - team solomid (foil) | cluj-napoca 2015",
				"949 - team solomid (gold) | cluj-napoca 2015",
				"950 - team envyus | cluj-napoca 2015",
				"951 - team envyus (foil) | cluj-napoca 2015",
				"952 - team envyus (gold) | cluj-napoca 2015",
				"953 - fnatic | cluj-napoca 2015",
				"954 - fnatic (foil) | cluj-napoca 2015",
				"955 - fnatic (gold) | cluj-napoca 2015",
				"956 - luminosity gaming | cluj-napoca 2015",
				"957 - luminosity gaming (foil) | cluj-napoca 2015",
				"958 - luminosity gaming (gold) | cluj-napoca 2015",
				"959 - dreamhack | cluj-napoca 2015",
				"960 - dreamhack (foil) | cluj-napoca 2015",
				"961 - dreamhack (gold) | cluj-napoca 2015",
				"962 - ivette",
				"963 - kimberly",
				"964 - martha",
				"965 - merietta",
				"966 - sherry",
				"967 - tamara",
				"968 - ivette (holo)",
				"969 - kimberly (holo)",
				"970 - martha (holo)",
				"971 - merietta (holo)",
				"972 - sherry (holo)",
				"973 - tamara (holo)",
				"974 - boom",
				"975 - boom (holo)",
				"976 - boom (foil)",
				"977 - countdown",
				"978 - countdown (holo)",
				"979 - countdown (foil)",
				"980 - don't worry",
				"981 - don't worry (holo)",
				"982 - don't worry (foil)",
				"983 - hard cluck life",
				"984 - hard cluck life (holo)",
				"985 - hard cluck life (foil)",
				"986 - move it",
				"987 - move it (holo)",
				"988 - move it (foil)",
				"989 - the awper",
				"990 - the baiter",
				"991 - the bomber",
				"992 - the bot",
				"993 - the fragger",
				"994 - the leader",
				"995 - the lurker",
				"996 - the 'nader",
				"997 - the ninja",
				"998 - support",
				"999 - the awper (foil)"
				"1000 - the bomber (foil)",
				"1001 - the fragger (foil)",
				"1002 - the leader (foil)",
				"1003 - the nader (foil)",
				"1004 - ninja (foil)",
				"1005 - the pro (foil)",
				"1006 - support (foil)",
				"1007 - ninjas in pyjamas | mlg columbus 2016",
				"1008 - ninjas in pyjamas (holo) | mlg columbus 2016",
				"1009 - ninjas in pyjamas (foil) | mlg columbus 2016",
				"1010 - ninjas in pyjamas (gold) | mlg columbus 2016",
				"1011 - splyce | mlg columbus 2016",
				"1012 - splyce (holo) | mlg columbus 2016",
				"1013 - splyce (foil) | mlg columbus 2016",
				"1014 - splyce (gold) | mlg columbus 2016",
				"1015 - counter logic gaming | mlg columbus 2016",
				"1016 - counter logic gaming (holo) | mlg columbus 2016",
				"1017 - counter logic gaming (foil) | mlg columbus 2016",
				"1018 - counter logic gaming (gold) | mlg columbus 2016",
				"1019 - gambit gaming | mlg columbus 2016",
				"1020 - gambit gaming (holo) | mlg columbus 2016",
				"1021 - gambit gaming (foil) | mlg columbus 2016",
				"1022 - gambit gaming (gold) | mlg columbus 2016",
				"1023 - flipsid3 tactics | mlg columbus 2016",
				"1024 - flipsid3 tactics (holo) | mlg columbus 2016",
				"1025 - flipsid3 tactics (foil) | mlg columbus 2016",
				"1026 - flipsid3 tactics (gold) | mlg columbus 2016",
				"1027 - team liquid | mlg columbus 2016",
				"1028 - team liquid (holo) | mlg columbus 2016",
				"1029 - team liquid (foil) | mlg columbus 2016",
				"1030 - team liquid (gold) | mlg columbus 2016",
				"1031 - mousesports | mlg columbus 2016",
				"1032 - mousesports (holo) | mlg columbus 2016",
				"1033 - mousesports (foil) | mlg columbus 2016",
				"1034 - mousesports (gold) | mlg columbus 2016",
				"1035 - natus vincere | mlg columbus 2016",
				"1036 - natus vincere (holo) | mlg columbus 2016",
				"1037 - natus vincere (foil) | mlg columbus 2016",
				"1038 - natus vincere (gold) | mlg columbus 2016",
				"1039 - virtus.pro | mlg columbus 2016",
				"1040 - virtus.pro (holo) | mlg columbus 2016",
				"1041 - virtus.pro (foil) | mlg columbus 2016",
				"1042 - virtus.pro (gold) | mlg columbus 2016",
				"1043 - cloud9 | mlg columbus 2016",
				"1044 - cloud9 (holo) | mlg columbus 2016",
				"1045 - cloud9 (foil) | mlg columbus 2016",
				"1046 - cloud9 (gold) | mlg columbus 2016",
				"1047 - g2 esports | mlg columbus 2016",
				"1048 - g2 esports (holo) | mlg columbus 2016",
				"1049 - g2 esports (foil) | mlg columbus 2016",
				"1050 - g2 esports (gold) | mlg columbus 2016",
				"1051 - faze clan | mlg columbus 2016",
				"1052 - faze clan (holo) | mlg columbus 2016",
				"1053 - faze clan (foil) | mlg columbus 2016",
				"1054 - faze clan (gold) | mlg columbus 2016",
				"1055 - astralis | mlg columbus 2016",
				"1056 - astralis (holo) | mlg columbus 2016",
				"1057 - astralis (foil) | mlg columbus 2016",
				"1058 - astralis (gold) | mlg columbus 2016",
				"1059 - team envyus | mlg columbus 2016",
				"1060 - team envyus (holo) | mlg columbus 2016",
				"1061 - team envyus (foil) | mlg columbus 2016",
				"1062 - team envyus (gold) | mlg columbus 2016",
				"1063 - fnatic | mlg columbus 2016",
				"1064 - fnatic (holo) | mlg columbus 2016",
				"1065 - fnatic (foil) | mlg columbus 2016",
				"1066 - fnatic (gold) | mlg columbus 2016",
				"1067 - luminosity gaming | mlg columbus 2016",
				"1068 - luminosity gaming (holo) | mlg columbus 2016",
				"1069 - luminosity gaming (foil) | mlg columbus 2016",
				"1070 - luminosity gaming (gold) | mlg columbus 2016",
				"1071 - mlg | mlg columbus 2016",
				"1072 - mlg (holo) | mlg columbus 2016",
				"1073 - mlg (foil) | mlg columbus 2016",
				"1074 - mlg (gold) | mlg columbus 2016",
				"1075 - reltuc | mlg columbus 2016",
				"1076 - reltuc (foil) | mlg columbus 2016",
				"1077 - reltuc (gold) | mlg columbus 2016",
				"1078 - fugly | mlg columbus 2016",
				"1079 - fugly (foil) | mlg columbus 2016",
				"1080 - fugly (gold) | mlg columbus 2016",
				"1081 - hazed | mlg columbus 2016",
				"1082 - hazed (foil) | mlg columbus 2016",
				"1083 - hazed (gold) | mlg columbus 2016",
				"1084 - jdm64 | mlg columbus 2016",
				"1085 - jdm64 (foil) | mlg columbus 2016",
				"1086 - jdm64 (gold) | mlg columbus 2016",
				"1087 - tarik | mlg columbus 2016",
				"1088 - tarik (foil) | mlg columbus 2016",
				"1089 - tarik (gold) | mlg columbus 2016",
				"1090 - freakazoid | mlg columbus 2016",
				"1091 - freakazoid (foil) | mlg columbus 2016",
				"1092 - freakazoid (gold) | mlg columbus 2016",
				"1093 - stewie2k | mlg columbus 2016",
				"1094 - stewie2k (foil) | mlg columbus 2016",
				"1095 - stewie2k (gold) | mlg columbus 2016",
				"1096 - shroud | mlg columbus 2016",
				"1097 - shroud (foil) | mlg columbus 2016",
				"1098 - shroud (gold) | mlg columbus 2016",
				"1099 - skadoodle | mlg columbus 2016",
				"1100 - skadoodle (foil) | mlg columbus 2016",
				"1101 - skadoodle (gold) | mlg columbus 2016",
				"1102 - n0thing | mlg columbus 2016",
				"1103 - n0thing (foil) | mlg columbus 2016",
				"1104 - n0thing (gold) | mlg columbus 2016",
				"1105 - apex | mlg columbus 2016",
				"1106 - apex (foil) | mlg columbus 2016",
				"1107 - apex (gold) | mlg columbus 2016",
				"1108 - happy | mlg columbus 2016",
				"1109 - happy (foil) | mlg columbus 2016",
				"1110 - happy (gold) | mlg columbus 2016",
				"1111 - devil | mlg columbus 2016",
				"1112 - devil (foil) | mlg columbus 2016",
				"1113 - devil (gold) | mlg columbus 2016",
				"1114 - kennys | mlg columbus 2016",
				"1115 - kennys (foil) | mlg columbus 2016",
				"1116 - kennys (gold) | mlg columbus 2016",
				"1117 - nbk- | mlg columbus 2016",
				"1118 - nbk- (foil) | mlg columbus 2016",
				"1119 - nbk- (gold) | mlg columbus 2016",
				"1120 - b1ad3 | mlg columbus 2016",
				"1121 - b1ad3 (foil) | mlg columbus 2016",
				"1122 - b1ad3 (gold) | mlg columbus 2016",
				"1123 - bondik | mlg columbus 2016",
				"1124 - bondik (foil) | mlg columbus 2016",
				"1125 - bondik (gold) | mlg columbus 2016",
				"1126 - shara | mlg columbus 2016",
				"1127 - shara (foil) | mlg columbus 2016",
				"1128 - shara (gold) | mlg columbus 2016",
				"1129 - markeloff | mlg columbus 2016",
				"1130 - markeloff (foil) | mlg columbus 2016",
				"1131 - markeloff (gold) | mlg columbus 2016",
				"1132 - worldedit | mlg columbus 2016",
				"1133 - worldedit (foil) | mlg columbus 2016",
				"1134 - worldedit (gold) | mlg columbus 2016",
				"1135 - flusha | mlg columbus 2016",
				"1136 - flusha (foil) | mlg columbus 2016",
				"1137 - flusha (gold) | mlg columbus 2016",
				"1138 - jw | mlg columbus 2016",
				"1139 - jw (foil) | mlg columbus 2016",
				"1140 - jw (gold) | mlg columbus 2016",
				"1141 - krimz | mlg columbus 2016",
				"1142 - krimz (foil) | mlg columbus 2016",
				"1143 - krimz (gold) | mlg columbus 2016",
				"1144 - olofmeister | mlg columbus 2016",
				"1145 - olofmeister (foil) | mlg columbus 2016",
				"1146 - olofmeister (gold) | mlg columbus 2016",
				"1147 - dennis | mlg columbus 2016",
				"1148 - dennis (foil) | mlg columbus 2016",
				"1149 - dennis (gold) | mlg columbus 2016",
				"1150 - aizy | mlg columbus 2016",
				"1151 - aizy (foil) | mlg columbus 2016",
				"1152 - aizy (gold) | mlg columbus 2016",
				"1153 - fox | mlg columbus 2016",
				"1154 - fox (foil) | mlg columbus 2016",
				"1155 - fox (gold) | mlg columbus 2016",
				"1156 - maikelele | mlg columbus 2016",
				"1157 - maikelele (foil) | mlg columbus 2016",
				"1158 - maikelele (gold) | mlg columbus 2016",
				"1159 - rain | mlg columbus 2016",
				"1160 - rain (foil) | mlg columbus 2016",
				"1161 - rain (gold) | mlg columbus 2016",
				"1162 - jkaem | mlg columbus 2016",
				"1163 - jkaem (foil) | mlg columbus 2016",
				"1164 - jkaem (gold) | mlg columbus 2016",
				"1165 - fnx | mlg columbus 2016",
				"1166 - fnx (foil) | mlg columbus 2016",
				"1167 - fnx (gold) | mlg columbus 2016",
				"1168 - coldzera | mlg columbus 2016",
				"1169 - coldzera (foil) | mlg columbus 2016",
				"1170 - coldzera (gold) | mlg columbus 2016",
				"1171 - fallen | mlg columbus 2016",
				"1172 - fallen (foil) | mlg columbus 2016",
				"1173 - fallen (gold) | mlg columbus 2016",
				"1174 - fer | mlg columbus 2016",
				"1175 - fer (foil) | mlg columbus 2016",
				"1176 - fer (gold) | mlg columbus 2016",
				"1177 - taco | mlg columbus 2016",
				"1178 - taco (foil) | mlg columbus 2016",
				"1179 - taco (gold) | mlg columbus 2016",
				"1180 - chrisj | mlg columbus 2016",
				"1181 - chrisj (foil) | mlg columbus 2016",
				"1182 - chrisj (gold) | mlg columbus 2016",
				"1183 - denis | mlg columbus 2016",
				"1184 - denis (foil) | mlg columbus 2016",
				"1185 - denis (gold) | mlg columbus 2016",
				"1186 - spiidi | mlg columbus 2016",
				"1187 - spiidi (foil) | mlg columbus 2016",
				"1188 - spiidi (gold) | mlg columbus 2016",
				"1189 - nex | mlg columbus 2016",
				"1190 - nex (foil) | mlg columbus 2016",
				"1191 - nex (gold) | mlg columbus 2016",
				"1192 - niko | mlg columbus 2016",
				"1193 - niko (foil) | mlg columbus 2016",
				"1194 - niko (gold) | mlg columbus 2016",
				"1195 - edward | mlg columbus 2016",
				"1196 - edward (foil) | mlg columbus 2016",
				"1197 - edward (gold) | mlg columbus 2016",
				"1198 - flamie | mlg columbus 2016",
				"1199 - flamie (foil) | mlg columbus 2016",
				"1200 - flamie (gold) | mlg columbus 2016",
				"1201 - guardian | mlg columbus 2016",
				"1202 - guardian (foil) | mlg columbus 2016",
				"1203 - guardian (gold) | mlg columbus 2016",
				"1204 - seized | mlg columbus 2016",
				"1205 - seized (foil) | mlg columbus 2016",
				"1206 - seized (gold) | mlg columbus 2016",
				"1207 - zeus | mlg columbus 2016",
				"1208 - zeus (foil) | mlg columbus 2016",
				"1209 - zeus (gold) | mlg columbus 2016",
				"1210 - pyth | mlg columbus 2016",
				"1211 - pyth (foil) | mlg columbus 2016",
				"1212 - pyth (gold) | mlg columbus 2016",
				"1213 - f0rest | mlg columbus 2016",
				"1214 - f0rest (foil) | mlg columbus 2016",
				"1215 - f0rest (gold) | mlg columbus 2016",
				"1216 - friberg | mlg columbus 2016",
				"1217 - friberg (foil) | mlg columbus 2016",
				"1218 - friberg (gold) | mlg columbus 2016",
				"1219 - get_right | mlg columbus 2016",
				"1220 - get_right (foil) | mlg columbus 2016",
				"1221 - get_right (gold) | mlg columbus 2016",
				"1222 - xizt | mlg columbus 2016",
				"1223 - xizt (foil) | mlg columbus 2016",
				"1224 - xizt (gold) | mlg columbus 2016",
				"1225 - jasonr | mlg columbus 2016",
				"1226 - jasonr (foil) | mlg columbus 2016",
				"1227 - jasonr (gold) | mlg columbus 2016",
				"1228 - arya | mlg columbus 2016",
				"1229 - arya (foil) | mlg columbus 2016",
				"1230 - arya (gold) | mlg columbus 2016",
				"1231 - professor_chaos | mlg columbus 2016",
				"1232 - professor_chaos (foil) | mlg columbus 2016",
				"1233 - professor_chaos (gold) | mlg columbus 2016",
				"1234 - davey | mlg columbus 2016",
				"1235 - davey (foil) | mlg columbus 2016",
				"1236 - davey (gold) | mlg columbus 2016",
				"1237 - abe | mlg columbus 2016",
				"1238 - abe (foil) | mlg columbus 2016",
				"1239 - abe (gold) | mlg columbus 2016",
				"1240 - adren | mlg columbus 2016",
				"1241 - adren (foil) | mlg columbus 2016",
				"1242 - adren (gold) | mlg columbus 2016",
				"1243 - elige | mlg columbus 2016",
				"1244 - elige (foil) | mlg columbus 2016",
				"1245 - elige (gold) | mlg columbus 2016",
				"1246 - s1mple | mlg columbus 2016",
				"1247 - s1mple (foil) | mlg columbus 2016",
				"1248 - s1mple (gold) | mlg columbus 2016",
				"1249 - hiko | mlg columbus 2016",
				"1250 - hiko (foil) | mlg columbus 2016",
				"1251 - hiko (gold) | mlg columbus 2016",
				"1252 - nitr0 | mlg columbus 2016",
				"1253 - nitr0 (foil) | mlg columbus 2016",
				"1254 - nitr0 (gold) | mlg columbus 2016",
				"1255 - ex6tenz | mlg columbus 2016",
				"1256 - ex6tenz (foil) | mlg columbus 2016",
				"1257 - ex6tenz (gold) | mlg columbus 2016",
				"1258 - rpk | mlg columbus 2016",
				"1259 - rpk (foil) | mlg columbus 2016",
				"1260 - rpk (gold) | mlg columbus 2016",
				"1261 - scream | mlg columbus 2016",
				"1262 - scream (foil) | mlg columbus 2016",
				"1263 - scream (gold) | mlg columbus 2016",
				"1264 - shox | mlg columbus 2016",
				"1265 - shox (foil) | mlg columbus 2016",
				"1266 - shox (gold) | mlg columbus 2016",
				"1267 - smithzz | mlg columbus 2016",
				"1268 - smithzz (foil) | mlg columbus 2016",
				"1269 - smithzz (gold) | mlg columbus 2016",
				"1270 - cajunb | mlg columbus 2016",
				"1271 - cajunb (foil) | mlg columbus 2016",
				"1272 - cajunb (gold) | mlg columbus 2016",
				"1273 - device | mlg columbus 2016",
				"1274 - device (foil) | mlg columbus 2016",
				"1275 - device (gold) | mlg columbus 2016",
				"1276 - dupreeh | mlg columbus 2016",
				"1277 - dupreeh (foil) | mlg columbus 2016",
				"1278 - dupreeh (gold) | mlg columbus 2016",
				"1279 - karrigan | mlg columbus 2016",
				"1280 - karrigan (foil) | mlg columbus 2016",
				"1281 - karrigan (gold) | mlg columbus 2016",
				"1282 - xyp9x | mlg columbus 2016",
				"1283 - xyp9x (foil) | mlg columbus 2016",
				"1284 - xyp9x (gold) | mlg columbus 2016",
				"1285 - waylander | mlg columbus 2016",
				"1286 - waylander (foil) | mlg columbus 2016",
				"1287 - waylander (gold) | mlg columbus 2016",
				"1288 - dosia | mlg columbus 2016",
				"1289 - dosia (foil) | mlg columbus 2016",
				"1290 - dosia (gold) | mlg columbus 2016",
				"1291 - hooch | mlg columbus 2016",
				"1292 - hooch (foil) | mlg columbus 2016",
				"1293 - hooch (gold) | mlg columbus 2016",
				"1294 - mou | mlg columbus 2016",
				"1295 - mou (foil) | mlg columbus 2016",
				"1296 - mou (gold) | mlg columbus 2016",
				"1297 - adren  | mlg columbus 2016",
				"1298 - adren (foil)  | mlg columbus 2016",
				"1299 - adren (gold)  | mlg columbus 2016",
				"1300 - byali | mlg columbus 2016",
				"1301 - byali (foil) | mlg columbus 2016",
				"1302 - byali (gold) | mlg columbus 2016",
				"1303 - neo | mlg columbus 2016",
				"1304 - neo (foil) | mlg columbus 2016",
				"1305 - neo (gold) | mlg columbus 2016",
				"1306 - pashabiceps | mlg columbus 2016",
				"1307 - pashabiceps (foil) | mlg columbus 2016",
				"1308 - pashabiceps (gold) | mlg columbus 2016",
				"1309 - snax | mlg columbus 2016",
				"1310 - snax (foil) | mlg columbus 2016",
				"1311 - snax (gold) | mlg columbus 2016",
				"1312 - taz | mlg columbus 2016",
				"1313 - taz (foil) | mlg columbus 2016",
				"1314 - taz (gold) | mlg columbus 2016",
				"1315 - all-stars orange (holo)",
				"1316 - all-stars blue (holo)",
				"1317 - ninjas in pyjamas | cologne 2016",
				"1318 - ninjas in pyjamas (holo) | cologne 2016",
				"1319 - ninjas in pyjamas (foil) | cologne 2016",
				"1320 - ninjas in pyjamas (gold) | cologne 2016",
				"1321 - optic gaming | cologne 2016",
				"1322 - optic gaming (holo) | cologne 2016",
				"1323 - optic gaming (foil) | cologne 2016",
				"1324 - optic gaming (gold) | cologne 2016",
				"1325 - counter logic gaming | cologne 2016",
				"1326 - counter logic gaming (holo) | cologne 2016",
				"1327 - counter logic gaming (foil) | cologne 2016",
				"1328 - counter logic gaming (gold) | cologne 2016",
				"1329 - gambit gaming | cologne 2016",
				"1330 - gambit gaming (holo) | cologne 2016",
				"1331 - gambit gaming (foil) | cologne 2016",
				"1332 - gambit gaming (gold) | cologne 2016",
				"1333 - flipsid3 tactics | cologne 2016",
				"1334 - flipsid3 tactics (holo) | cologne 2016",
				"1335 - flipsid3 tactics (foil) | cologne 2016",
				"1336 - flipsid3 tactics (gold) | cologne 2016",
				"1337 - team liquid | cologne 2016",
				"1338 - team liquid (holo) | cologne 2016",
				"1339 - team liquid (foil) | cologne 2016",
				"1340 - team liquid (gold) | cologne 2016",
				"1341 - mousesports | cologne 2016",
				"1342 - mousesports (holo) | cologne 2016",
				"1343 - mousesports (foil) | cologne 2016",
				"1344 - mousesports (gold) | cologne 2016",
				"1345 - natus vincere | cologne 2016",
				"1346 - natus vincere (holo) | cologne 2016",
				"1347 - natus vincere (foil) | cologne 2016",
				"1348 - natus vincere (gold) | cologne 2016",
				"1349 - virtus.pro | cologne 2016",
				"1350 - virtus.pro (holo) | cologne 2016",
				"1351 - virtus.pro (foil) | cologne 2016",
				"1352 - virtus.pro (gold) | cologne 2016",
				"1353 - sk gaming | cologne 2016",
				"1354 - sk gaming (holo) | cologne 2016",
				"1355 - sk gaming (foil) | cologne 2016",
				"1356 - sk gaming (gold) | cologne 2016",
				"1357 - g2 esports | cologne 2016",
				"1358 - g2 esports (holo) | cologne 2016",
				"1359 - g2 esports (foil) | cologne 2016",
				"1360 - g2 esports (gold) | cologne 2016",
				"1361 - faze clan | cologne 2016",
				"1362 - faze clan (holo) | cologne 2016",
				"1363 - faze clan (foil) | cologne 2016",
				"1364 - faze clan (gold) | cologne 2016",
				"1365 - astralis | cologne 2016",
				"1366 - astralis (holo) | cologne 2016",
				"1367 - astralis (foil) | cologne 2016",
				"1368 - astralis (gold) | cologne 2016",
				"1369 - team envyus | cologne 2016",
				"1370 - team envyus (holo) | cologne 2016",
				"1371 - team envyus (foil) | cologne 2016",
				"1372 - team envyus (gold) | cologne 2016",
				"1373 - fnatic | cologne 2016",
				"1374 - fnatic (holo) | cologne 2016",
				"1375 - fnatic (foil) | cologne 2016",
				"1376 - fnatic (gold) | cologne 2016",
				"1377 - team dignitas | cologne 2016",
				"1378 - team dignitas (holo) | cologne 2016",
				"1379 - team dignitas (foil) | cologne 2016",
				"1380 - team dignitas (gold) | cologne 2016",
				"1381 - esl | cologne 2016",
				"1382 - esl (holo) | cologne 2016",
				"1383 - esl (foil) | cologne 2016",
				"1384 - esl (gold) | cologne 2016",
				"1385 - reltuc | cologne 2016",
				"1386 - reltuc (foil) | cologne 2016",
				"1387 - reltuc (gold) | cologne 2016",
				"1388 - koosta | cologne 2016",
				"1389 - koosta (foil) | cologne 2016",
				"1390 - koosta (gold) | cologne 2016",
				"1391 - hazed | cologne 2016",
				"1392 - hazed (foil) | cologne 2016",
				"1393 - hazed (gold) | cologne 2016",
				"1394 - pita | cologne 2016",
				"1395 - pita (foil) | cologne 2016",
				"1396 - pita (gold) | cologne 2016",
				"1397 - tarik | cologne 2016",
				"1398 - tarik (foil) | cologne 2016",
				"1399 - tarik (gold) | cologne 2016",
				"1400 - daps | cologne 2016",
				"1401 - daps (foil) | cologne 2016",
				"1402 - daps (gold) | cologne 2016",
				"1403 - mixwell | cologne 2016",
				"1404 - mixwell (foil) | cologne 2016",
				"1405 - mixwell (gold) | cologne 2016",
				"1406 - naf | cologne 2016",
				"1407 - naf (foil) | cologne 2016",
				"1408 - naf (gold) | cologne 2016",
				"1409 - rush | cologne 2016",
				"1410 - rush (foil) | cologne 2016",
				"1411 - rush (gold) | cologne 2016",
				"1412 - stanislaw | cologne 2016",
				"1413 - stanislaw (foil) | cologne 2016",
				"1414 - stanislaw (gold) | cologne 2016",
				"1415 - apex | cologne 2016",
				"1416 - apex (foil) | cologne 2016",
				"1417 - apex (gold) | cologne 2016",
				"1418 - happy | cologne 2016",
				"1419 - happy (foil) | cologne 2016",
				"1420 - happy (gold) | cologne 2016",
				"1421 - devil | cologne 2016",
				"1422 - devil (foil) | cologne 2016",
				"1423 - devil (gold) | cologne 2016",
				"1424 - kennys | cologne 2016",
				"1425 - kennys (foil) | cologne 2016",
				"1426 - kennys (gold) | cologne 2016",
				"1427 - nbk- | cologne 2016",
				"1428 - nbk- (foil) | cologne 2016",
				"1429 - nbk- (gold) | cologne 2016",
				"1430 - b1ad3 | cologne 2016",
				"1431 - b1ad3 (foil) | cologne 2016",
				"1432 - b1ad3 (gold) | cologne 2016",
				"1433 - waylander | cologne 2016",
				"1434 - waylander (foil) | cologne 2016",
				"1435 - waylander (gold) | cologne 2016",
				"1436 - shara | cologne 2016",
				"1437 - shara (foil) | cologne 2016",
				"1438 - shara (gold) | cologne 2016",
				"1439 - markeloff | cologne 2016",
				"1440 - markeloff (foil) | cologne 2016",
				"1441 - markeloff (gold) | cologne 2016",
				"1442 - worldedit | cologne 2016",
				"1443 - worldedit (foil) | cologne 2016",
				"1444 - worldedit (gold) | cologne 2016",
				"1445 - flusha | cologne 2016",
				"1446 - flusha (foil) | cologne 2016",
				"1447 - flusha (gold) | cologne 2016",
				"1448 - jw | cologne 2016",
				"1449 - jw (foil) | cologne 2016",
				"1450 - jw (gold) | cologne 2016",
				"1451 - krimz | cologne 2016",
				"1452 - krimz (foil) | cologne 2016",
				"1453 - krimz (gold) | cologne 2016",
				"1454 - olofmeister | cologne 2016",
				"1455 - olofmeister (foil) | cologne 2016",
				"1456 - olofmeister (gold) | cologne 2016",
				"1457 - dennis | cologne 2016",
				"1458 - dennis (foil) | cologne 2016",
				"1459 - dennis (gold) | cologne 2016",
				"1460 - aizy | cologne 2016",
				"1461 - aizy (foil) | cologne 2016",
				"1462 - aizy (gold) | cologne 2016",
				"1463 - fox | cologne 2016",
				"1464 - fox (foil) | cologne 2016",
				"1465 - fox (gold) | cologne 2016",
				"1466 - kioshima | cologne 2016",
				"1467 - kioshima (foil) | cologne 2016",
				"1468 - kioshima (gold) | cologne 2016",
				"1469 - rain | cologne 2016",
				"1470 - rain (foil) | cologne 2016",
				"1471 - rain (gold) | cologne 2016",
				"1472 - jkaem | cologne 2016",
				"1473 - jkaem (foil) | cologne 2016",
				"1474 - jkaem (gold) | cologne 2016",
				"1475 - coldzera | cologne 2016",
				"1476 - coldzera (foil) | cologne 2016",
				"1477 - coldzera (gold) | cologne 2016",
				"1478 - fallen | cologne 2016",
				"1479 - fallen (foil) | cologne 2016",
				"1480 - fallen (gold) | cologne 2016",
				"1481 - fer | cologne 2016",
				"1482 - fer (foil) | cologne 2016",
				"1483 - fer (gold) | cologne 2016",
				"1484 - fnx | cologne 2016",
				"1485 - fnx (foil) | cologne 2016",
				"1486 - fnx (gold) | cologne 2016",
				"1487 - taco | cologne 2016",
				"1488 - taco (foil) | cologne 2016",
				"1489 - taco (gold) | cologne 2016",
				"1490 - chrisj | cologne 2016",
				"1491 - chrisj (foil) | cologne 2016",
				"1492 - chrisj (gold) | cologne 2016",
				"1493 - denis | cologne 2016",
				"1494 - denis (foil) | cologne 2016",
				"1495 - denis (gold) | cologne 2016",
				"1496 - spiidi | cologne 2016",
				"1497 - spiidi (foil) | cologne 2016",
				"1498 - spiidi (gold) | cologne 2016",
				"1499 - nex | cologne 2016",
				"1500 - nex (foil) | cologne 2016",
				"1501 - nex (gold) | cologne 2016",
				"1502 - niko | cologne 2016",
				"1503 - niko (foil) | cologne 2016",
				"1504 - niko (gold) | cologne 2016",
				"1505 - edward | cologne 2016",
				"1506 - edward (foil) | cologne 2016",
				"1507 - edward (gold) | cologne 2016",
				"1508 - flamie | cologne 2016",
				"1509 - flamie (foil) | cologne 2016",
				"1510 - flamie (gold) | cologne 2016",
				"1511 - guardian | cologne 2016",
				"1512 - guardian (foil) | cologne 2016",
				"1513 - guardian (gold) | cologne 2016",
				"1514 - seized | cologne 2016",
				"1515 - seized (foil) | cologne 2016",
				"1516 - seized (gold) | cologne 2016",
				"1517 - zeus | cologne 2016",
				"1518 - zeus (foil) | cologne 2016",
				"1519 - zeus (gold) | cologne 2016",
				"1520 - pyth | cologne 2016",
				"1521 - pyth (foil) | cologne 2016",
				"1522 - pyth (gold) | cologne 2016",
				"1523 - f0rest | cologne 2016",
				"1524 - f0rest (foil) | cologne 2016",
				"1525 - f0rest (gold) | cologne 2016",
				"1526 - friberg | cologne 2016",
				"1527 - friberg (foil) | cologne 2016",
				"1528 - friberg (gold) | cologne 2016",
				"1529 - get_right | cologne 2016",
				"1530 - get_right (foil) | cologne 2016",
				"1531 - get_right (gold) | cologne 2016",
				"1532 - xizt | cologne 2016",
				"1533 - xizt (foil) | cologne 2016",
				"1534 - xizt (gold) | cologne 2016",
				"1535 - cajunb | cologne 2016",
				"1536 - cajunb (foil) | cologne 2016",
				"1537 - cajunb (gold) | cologne 2016",
				"1538 - msl | cologne 2016",
				"1539 - msl (foil) | cologne 2016",
				"1540 - msl (gold) | cologne 2016",
				"1541 - tenzki | cologne 2016",
				"1542 - tenzki (foil) | cologne 2016",
				"1543 - tenzki (gold) | cologne 2016",
				"1544 - rubino | cologne 2016",
				"1545 - rubino (foil) | cologne 2016",
				"1546 - rubino (gold) | cologne 2016",
				"1547 - k0nfig | cologne 2016",
				"1548 - k0nfig (foil) | cologne 2016",
				"1549 - k0nfig (gold) | cologne 2016",
				"1550 - jdm64 | cologne 2016",
				"1551 - jdm64 (foil) | cologne 2016",
				"1552 - jdm64 (gold) | cologne 2016",
				"1553 - elige | cologne 2016",
				"1554 - elige (foil) | cologne 2016",
				"1555 - elige (gold) | cologne 2016",
				"1556 - s1mple | cologne 2016",
				"1557 - s1mple (foil) | cologne 2016",
				"1558 - s1mple (gold) | cologne 2016",
				"1559 - hiko | cologne 2016",
				"1560 - hiko (foil) | cologne 2016",
				"1561 - hiko (gold) | cologne 2016",
				"1562 - nitr0 | cologne 2016",
				"1563 - nitr0 (foil) | cologne 2016",
				"1564 - nitr0 (gold) | cologne 2016",
				"1565 - bodyy | cologne 2016",
				"1566 - bodyy (foil) | cologne 2016",
				"1567 - bodyy (gold) | cologne 2016",
				"1568 - rpk | cologne 2016",
				"1569 - rpk (foil) | cologne 2016",
				"1570 - rpk (gold) | cologne 2016",
				"1571 - scream | cologne 2016",
				"1572 - scream (foil) | cologne 2016",
				"1573 - scream (gold) | cologne 2016",
				"1574 - shox | cologne 2016",
				"1575 - shox (foil) | cologne 2016",
				"1576 - shox (gold) | cologne 2016",
				"1577 - smithzz | cologne 2016",
				"1578 - smithzz (foil) | cologne 2016",
				"1579 - smithzz (gold) | cologne 2016",
				"1580 - gla1ve | cologne 2016",
				"1581 - gla1ve (foil) | cologne 2016",
				"1582 - gla1ve (gold) | cologne 2016",
				"1583 - device | cologne 2016",
				"1584 - device (foil) | cologne 2016",
				"1585 - device (gold) | cologne 2016",
				"1586 - dupreeh | cologne 2016",
				"1587 - dupreeh (foil) | cologne 2016",
				"1588 - dupreeh (gold) | cologne 2016",
				"1589 - karrigan | cologne 2016",
				"1590 - karrigan (foil) | cologne 2016",
				"1591 - karrigan (gold) | cologne 2016",
				"1592 - xyp9x | cologne 2016",
				"1593 - xyp9x (foil) | cologne 2016",
				"1594 - xyp9x (gold) | cologne 2016",
				"1595 - spaze | cologne 2016",
				"1596 - spaze (foil) | cologne 2016",
				"1597 - spaze (gold) | cologne 2016",
				"1598 - dosia | cologne 2016",
				"1599 - dosia (foil) | cologne 2016",
				"1600 - dosia (gold) | cologne 2016",
				"1601 - hooch | cologne 2016",
				"1602 - hooch (foil) | cologne 2016",
				"1603 - hooch (gold) | cologne 2016",
				"1604 - mou | cologne 2016",
				"1605 - mou (foil) | cologne 2016",
				"1606 - mou (gold) | cologne 2016",
				"1607 - adren | cologne 2016",
				"1608 - adren (foil) | cologne 2016",
				"1609 - adren (gold) | cologne 2016",
				"1610 - byali | cologne 2016",
				"1611 - byali (foil) | cologne 2016",
				"1612 - byali (gold) | cologne 2016",
				"1613 - neo | cologne 2016",
				"1614 - neo (foil) | cologne 2016",
				"1615 - neo (gold) | cologne 2016",
				"1616 - pashabiceps | cologne 2016",
				"1617 - pashabiceps (foil) | cologne 2016",
				"1618 - pashabiceps (gold) | cologne 2016",
				"1619 - snax | cologne 2016",
				"1620 - snax (foil) | cologne 2016",
				"1621 - snax (gold) | cologne 2016",
				"1622 - taz | cologne 2016",
				"1623 - taz (foil) | cologne 2016",
				"1624 - taz (gold) | cologne 2016",
				"1625 - boris",
				"1626 - max",
				"1627 - stan",
				"1628 - jack",
				"1629 - perry",
				"1630 - viggo",
				"1631 - joan",
				"1632 - boris (holo)",
				"1633 - max (holo)",
				"1634 - stan (holo)",
				"1635 - jack (holo)",
				"1636 - perry (holo)",
				"1637 - viggo (holo)",
				"1638 - joan (holo)",
				"1639 - basilisk",
				"1640 - dragon",
				"1641 - hippocamp",
				"1642 - manticore",
				"1643 - pegasus",
				"1644 - phoenix reborn",
				"1645 - sphinx",
				"1646 - hippocamp (holo)",
				"1647 - manticore (holo)",
				"1648 - pegasus (holo)",
				"1649 - sphinx (holo)",
				"1650 - basilisk (foil)",
				"1651 - dragon (foil)",
				"1652 - phoenix reborn (foil)",
				"1653 - blood boiler",
				"1654 - chabo",
				"1655 - drug war veteran",
				"1656 - flickshot",
				"1657 - hamster hawk",
				"1658 - ivette",
				"1659 - kawaii killer ct",
				"1660 - kawaii killer terrorist",
				"1661 - martha",
				"1662 - old school",
				"1663 - pocket bbq",
				"1664 - rekt",
				"1665 - shave master",
				"1666 - shooting star return",
				"1667 - rising skull",
				"1668 - tamara",
				"1669 - unicorn",
				"1670 - winged defuser",
				"1671 - ace",
				"1672 - banana",
				"1673 - cerberus",
				"1674 - clutch king",
				"1675 - crown",
				"1676 - guardian",
				"1677 - ez",
				"1678 - fire serpent",
				"1679 - howling dawn",
				"1680 - kisses",
				"1681 - easy peasy",
				"1682 - nice shot",
				"1683 - phoenix",
				"1684 - real mvp",
				"1685 - r.i.p.i.p.",
				"1686 - skull n' crosshairs",
				"1687 - welcome to the clutch",
				"1688 - wings",
				"1697 - x-axes",
				"1698 - death sentence",
				"1699 - chess king",
				"1700 - king me",
				"1701 - keep the change",
				"1702 - double",
				"1703 - eco",
				"1704 - tilt",
				"1705 - speechless",
				"1706 - qq",
				"1707 - mr. teeth",
				"1708 - ninja",
				"1709 - worry",
				"1710 - rage mode",
				"1711 - eye spy",
				"1712 - ggez",
				"1713 - ggwp",
				"1714 - glhf",
				"1715 - quickdraw",
				"1716 - backstab",
				"1717 - loser",
				"1718 - sheriff",
				"1719 - tombstone",
				"1720 - heart",
				"1721 - 8-ball",
				"1722 - lambda",
				"1723 - still happy",
				"1724 - jump shot",
				"1725 - karambit",
				"1726 - x-knives",
				"1727 - toasted",
				"1728 - bling",
				"1729 - noscope",
				"1730 - piggles",
				"1731 - popdog",
				"1732 - cocky",
				"1733 - nacl",
				"1734 - sorry",
				"1735 - eat it",
				"1736 - take flight",
				"1737 - gtg",
				"1738 - astralis | atlanta 2017",
				"1739 - astralis (holo) | atlanta 2017",
				"1740 - astralis (foil) | atlanta 2017",
				"1741 - astralis (gold) | atlanta 2017",
				"1742 - team envyus | atlanta 2017",
				"1743 - team envyus (holo) | atlanta 2017",
				"1744 - team envyus (foil) | atlanta 2017",
				"1745 - team envyus (gold) | atlanta 2017",
				"1746 - faze clan | atlanta 2017",
				"1747 - faze clan (holo) | atlanta 2017",
				"1748 - faze clan (foil) | atlanta 2017",
				"1749 - faze clan (gold) | atlanta 2017",
				"1750 - flipsid3 tactics | atlanta 2017",
				"1751 - flipsid3 tactics (holo) | atlanta 2017",
				"1752 - flipsid3 tactics (foil) | atlanta 2017",
				"1753 - flipsid3 tactics (gold) | atlanta 2017",
				"1754 - fnatic | atlanta 2017",
				"1755 - fnatic (holo) | atlanta 2017",
				"1756 - fnatic (foil) | atlanta 2017",
				"1757 - fnatic (gold) | atlanta 2017",
				"1758 - g2 esports | atlanta 2017",
				"1759 - g2 esports (holo) | atlanta 2017",
				"1760 - g2 esports (foil) | atlanta 2017",
				"1761 - g2 esports (gold) | atlanta 2017",
				"1762 - gambit gaming | atlanta 2017",
				"1763 - gambit gaming (holo) | atlanta 2017",
				"1764 - gambit gaming (foil) | atlanta 2017",
				"1765 - gambit gaming (gold) | atlanta 2017",
				"1766 - godsent | atlanta 2017",
				"1767 - godsent (holo) | atlanta 2017",
				"1768 - godsent (foil) | atlanta 2017",
				"1769 - godsent (gold) | atlanta 2017",
				"1770 - hellraisers | atlanta 2017",
				"1771 - hellraisers (holo) | atlanta 2017",
				"1772 - hellraisers (foil) | atlanta 2017",
				"1773 - hellraisers (gold) | atlanta 2017",
				"1774 - mousesports | atlanta 2017",
				"1775 - mousesports (holo) | atlanta 2017",
				"1776 - mousesports (foil) | atlanta 2017",
				"1777 - mousesports (gold) | atlanta 2017",
				"1778 - natus vincere | atlanta 2017",
				"1779 - natus vincere (holo) | atlanta 2017",
				"1780 - natus vincere (foil) | atlanta 2017",
				"1781 - natus vincere (gold) | atlanta 2017",
				"1782 - north | atlanta 2017",
				"1783 - north (holo) | atlanta 2017",
				"1784 - north (foil) | atlanta 2017",
				"1785 - north (gold) | atlanta 2017",
				"1786 - optic gaming | atlanta 2017",
				"1787 - optic gaming (holo) | atlanta 2017",
				"1788 - optic gaming (foil) | atlanta 2017",
				"1789 - optic gaming (gold) | atlanta 2017",
				"1790 - sk gaming | atlanta 2017",
				"1791 - sk gaming (holo) | atlanta 2017",
				"1792 - sk gaming (foil) | atlanta 2017",
				"1793 - sk gaming (gold) | atlanta 2017",
				"1794 - team liquid | atlanta 2017",
				"1795 - team liquid (holo) | atlanta 2017",
				"1796 - team liquid (foil) | atlanta 2017",
				"1797 - team liquid (gold) | atlanta 2017",
				"1798 - virtus.pro | atlanta 2017",
				"1799 - virtus.pro (holo) | atlanta 2017",
				"1800 - virtus.pro (foil) | atlanta 2017",
				"1801 - virtus.pro (gold) | atlanta 2017",
				"1802 - eleague | atlanta 2017",
				"1803 - eleague (holo) | atlanta 2017",
				"1804 - eleague (foil) | atlanta 2017",
				"1805 - eleague (gold) | atlanta 2017",
				"1806 - astralis | atlanta 2017",
				"1807 - team envyus | atlanta 2017",
				"1808 - faze clan | atlanta 2017",
				"1809 - flipsid3 tactics | atlanta 2017",
				"1810 - fnatic | atlanta 2017",
				"1811 - g2 esports | atlanta 2017",
				"1812 - gambit gaming | atlanta 2017",
				"1813 - godsent | atlanta 2017",
				"1814 - hellraisers | atlanta 2017",
				"1815 - mousesports | atlanta 2017",
				"1816 - natus vincere | atlanta 2017",
				"1817 - north | atlanta 2017",
				"1818 - optic gaming | atlanta 2017",
				"1819 - sk gaming | atlanta 2017",
				"1820 - team liquid | atlanta 2017",
				"1821 - virtus.pro | atlanta 2017",
				"1822 - eleague | atlanta 2017",
				"1823 - styko | atlanta 2017",
				"1824 - styko (foil) | atlanta 2017",
				"1825 - styko (gold) | atlanta 2017",
				"1826 - zero | atlanta 2017",
				"1827 - zero (foil) | atlanta 2017",
				"1828 - zero (gold) | atlanta 2017",
				"1829 - deadfox | atlanta 2017",
				"1830 - deadfox (foil) | atlanta 2017",
				"1831 - deadfox (gold) | atlanta 2017",
				"1832 - bondik | atlanta 2017",
				"1833 - bondik (foil) | atlanta 2017",
				"1834 - bondik (gold) | atlanta 2017",
				"1835 - ange1 | atlanta 2017",
				"1836 - ange1 (foil) | atlanta 2017",
				"1837 - ange1 (gold) | atlanta 2017",
				"1838 - tarik | atlanta 2017",
				"1839 - tarik (foil) | atlanta 2017",
				"1840 - tarik (gold) | atlanta 2017",
				"1841 - mixwell | atlanta 2017",
				"1842 - mixwell (foil) | atlanta 2017",
				"1843 - mixwell (gold) | atlanta 2017",
				"1844 - naf | atlanta 2017",
				"1845 - naf (foil) | atlanta 2017",
				"1846 - naf (gold) | atlanta 2017",
				"1847 - rush | atlanta 2017",
				"1848 - rush (foil) | atlanta 2017",
				"1849 - rush (gold) | atlanta 2017",
				"1850 - stanislaw | atlanta 2017",
				"1851 - stanislaw (foil) | atlanta 2017",
				"1852 - stanislaw (gold) | atlanta 2017",
				"1853 - apex | atlanta 2017",
				"1854 - apex (foil) | atlanta 2017",
				"1855 - apex (gold) | atlanta 2017",
				"1856 - happy | atlanta 2017",
				"1857 - happy (foil) | atlanta 2017",
				"1858 - happy (gold) | atlanta 2017",
				"1859 - sixer | atlanta 2017",
				"1860 - sixer (foil) | atlanta 2017",
				"1861 - sixer (gold) | atlanta 2017",
				"1862 - kennys | atlanta 2017",
				"1863 - kennys (foil) | atlanta 2017",
				"1864 - kennys (gold) | atlanta 2017",
				"1865 - nbk- | atlanta 2017",
				"1866 - nbk- (foil) | atlanta 2017",
				"1867 - nbk- (gold) | atlanta 2017",
				"1868 - b1ad3 | atlanta 2017",
				"1869 - b1ad3 (foil) | atlanta 2017",
				"1870 - b1ad3 (gold) | atlanta 2017",
				"1871 - waylander | atlanta 2017",
				"1872 - waylander (foil) | atlanta 2017",
				"1873 - waylander (gold) | atlanta 2017",
				"1874 - electronic | atlanta 2017",
				"1875 - electronic (foil) | atlanta 2017",
				"1876 - electronic (gold) | atlanta 2017",
				"1877 - markeloff | atlanta 2017",
				"1878 - markeloff (foil) | atlanta 2017",
				"1879 - markeloff (gold) | atlanta 2017",
				"1880 - worldedit | atlanta 2017",
				"1881 - worldedit (foil) | atlanta 2017",
				"1882 - worldedit (gold) | atlanta 2017",
				"1883 - twist | atlanta 2017",
				"1884 - twist (foil) | atlanta 2017",
				"1885 - twist (gold) | atlanta 2017",
				"1886 - disco doplan | atlanta 2017",
				"1887 - disco doplan (foil) | atlanta 2017",
				"1888 - disco doplan (gold) | atlanta 2017",
				"1889 - krimz | atlanta 2017",
				"1890 - krimz (foil) | atlanta 2017",
				"1891 - krimz (gold) | atlanta 2017",
				"1892 - olofmeister | atlanta 2017",
				"1893 - olofmeister (foil) | atlanta 2017",
				"1894 - olofmeister (gold) | atlanta 2017",
				"1895 - dennis | atlanta 2017",
				"1896 - dennis (foil) | atlanta 2017",
				"1897 - dennis (gold) | atlanta 2017",
				"1898 - aizy | atlanta 2017",
				"1899 - aizy (foil) | atlanta 2017",
				"1900 - aizy (gold) | atlanta 2017",
				"1901 - allu | atlanta 2017",
				"1902 - allu (foil) | atlanta 2017",
				"1903 - allu (gold) | atlanta 2017",
				"1904 - kioshima | atlanta 2017",
				"1905 - kioshima (foil) | atlanta 2017",
				"1906 - kioshima (gold) | atlanta 2017",
				"1907 - rain | atlanta 2017",
				"1908 - rain (foil) | atlanta 2017",
				"1909 - rain (gold) | atlanta 2017",
				"1910 - karrigan | atlanta 2017",
				"1911 - karrigan (foil) | atlanta 2017",
				"1912 - karrigan (gold) | atlanta 2017",
				"1913 - coldzera | atlanta 2017",
				"1914 - coldzera (foil) | atlanta 2017",
				"1915 - coldzera (gold) | atlanta 2017",
				"1916 - fallen | atlanta 2017",
				"1917 - fallen (foil) | atlanta 2017",
				"1918 - fallen (gold) | atlanta 2017",
				"1919 - fer | atlanta 2017",
				"1920 - fer (foil) | atlanta 2017",
				"1921 - fer (gold) | atlanta 2017",
				"1922 - fox | atlanta 2017",
				"1923 - fox (foil) | atlanta 2017",
				"1924 - fox (gold) | atlanta 2017",
				"1925 - taco | atlanta 2017",
				"1926 - taco (foil) | atlanta 2017",
				"1927 - taco (gold) | atlanta 2017",
				"1928 - chrisj | atlanta 2017",
				"1929 - chrisj (foil) | atlanta 2017",
				"1930 - chrisj (gold) | atlanta 2017",
				"1931 - denis | atlanta 2017",
				"1932 - denis (foil) | atlanta 2017",
				"1933 - denis (gold) | atlanta 2017",
				"1934 - spiidi | atlanta 2017",
				"1935 - spiidi (foil) | atlanta 2017",
				"1936 - spiidi (gold) | atlanta 2017",
				"1937 - lowel | atlanta 2017",
				"1938 - lowel (foil) | atlanta 2017",
				"1939 - lowel (gold) | atlanta 2017",
				"1940 - niko | atlanta 2017",
				"1941 - niko (foil) | atlanta 2017",
				"1942 - niko (gold) | atlanta 2017",
				"1943 - edward | atlanta 2017",
				"1944 - edward (foil) | atlanta 2017",
				"1945 - edward (gold) | atlanta 2017",
				"1946 - flamie | atlanta 2017",
				"1947 - flamie (foil) | atlanta 2017",
				"1948 - flamie (gold) | atlanta 2017",
				"1949 - guardian | atlanta 2017",
				"1950 - guardian (foil) | atlanta 2017",
				"1951 - guardian (gold) | atlanta 2017",
				"1952 - seized | atlanta 2017",
				"1953 - seized (foil) | atlanta 2017",
				"1954 - seized (gold) | atlanta 2017",
				"1955 - s1mple | atlanta 2017",
				"1956 - s1mple (foil) | atlanta 2017",
				"1957 - s1mple (gold) | atlanta 2017",
				"1958 - znajder | atlanta 2017",
				"1959 - znajder (foil) | atlanta 2017",
				"1960 - znajder (gold) | atlanta 2017",
				"1961 - lekr0 | atlanta 2017",
				"1962 - lekr0 (foil) | atlanta 2017",
				"1963 - lekr0 (gold) | atlanta 2017",
				"1964 - pronax | atlanta 2017",
				"1965 - pronax (foil) | atlanta 2017",
				"1966 - pronax (gold) | atlanta 2017",
				"1967 - jw | atlanta 2017",
				"1968 - jw (foil) | atlanta 2017",
				"1969 - jw (gold) | atlanta 2017",
				"1970 - flusha | atlanta 2017",
				"1971 - flusha (foil) | atlanta 2017",
				"1972 - flusha (gold) | atlanta 2017",
				"1973 - cajunb | atlanta 2017",
				"1974 - cajunb (foil) | atlanta 2017",
				"1975 - cajunb (gold) | atlanta 2017",
				"1976 - msl | atlanta 2017",
				"1977 - msl (foil) | atlanta 2017",
				"1978 - msl (gold) | atlanta 2017",
				"1979 - magisk | atlanta 2017",
				"1980 - magisk (foil) | atlanta 2017",
				"1981 - magisk (gold) | atlanta 2017",
				"1982 - rubino | atlanta 2017",
				"1983 - rubino (foil) | atlanta 2017",
				"1984 - rubino (gold) | atlanta 2017",
				"1985 - k0nfig | atlanta 2017",
				"1986 - k0nfig (foil) | atlanta 2017",
				"1987 - k0nfig (gold) | atlanta 2017",
				"1988 - jdm64 | atlanta 2017",
				"1989 - jdm64 (foil) | atlanta 2017",
				"1990 - jdm64 (gold) | atlanta 2017",
				"1991 - elige | atlanta 2017",
				"1992 - elige (foil) | atlanta 2017",
				"1993 - elige (gold) | atlanta 2017",
				"1994 - pimp | atlanta 2017",
				"1995 - pimp (foil) | atlanta 2017",
				"1996 - pimp (gold) | atlanta 2017",
				"1997 - hiko | atlanta 2017",
				"1998 - hiko (foil) | atlanta 2017",
				"1999 - hiko (gold) | atlanta 2017",
				"2000 - nitr0 | atlanta 2017",
				"2001 - nitr0 (foil) | atlanta 2017",
				"2002 - nitr0 (gold) | atlanta 2017",
				"2003 - bodyy | atlanta 2017",
				"2004 - bodyy (foil) | atlanta 2017",
				"2005 - bodyy (gold) | atlanta 2017",
				"2006 - rpk | atlanta 2017",
				"2007 - rpk (foil) | atlanta 2017",
				"2008 - rpk (gold) | atlanta 2017",
				"2009 - scream | atlanta 2017",
				"2010 - scream (foil) | atlanta 2017",
				"2011 - scream (gold) | atlanta 2017",
				"2012 - shox | atlanta 2017",
				"2013 - shox (foil) | atlanta 2017",
				"2014 - shox (gold) | atlanta 2017",
				"2015 - smithzz | atlanta 2017",
				"2016 - smithzz (foil) | atlanta 2017",
				"2017 - smithzz (gold) | atlanta 2017",
				"2018 - gla1ve | atlanta 2017",
				"2019 - gla1ve (foil) | atlanta 2017",
				"2020 - gla1ve (gold) | atlanta 2017",
				"2021 - device | atlanta 2017",
				"2022 - device (foil) | atlanta 2017",
				"2023 - device (gold) | atlanta 2017",
				"2024 - dupreeh | atlanta 2017",
				"2025 - dupreeh (foil) | atlanta 2017",
				"2026 - dupreeh (gold) | atlanta 2017",
				"2027 - kjaerbye | atlanta 2017",
				"2028 - kjaerbye (foil) | atlanta 2017",
				"2029 - kjaerbye (gold) | atlanta 2017",
				"2030 - xyp9x | atlanta 2017",
				"2031 - xyp9x (foil) | atlanta 2017",
				"2032 - xyp9x (gold) | atlanta 2017",
				"2033 - zeus | atlanta 2017",
				"2034 - zeus (foil) | atlanta 2017",
				"2035 - zeus (gold) | atlanta 2017",
				"2036 - dosia | atlanta 2017",
				"2037 - dosia (foil) | atlanta 2017",
				"2038 - dosia (gold) | atlanta 2017",
				"2039 - hobbit | atlanta 2017",
				"2040 - hobbit (foil) | atlanta 2017",
				"2041 - hobbit (gold) | atlanta 2017",
				"2042 - mou | atlanta 2017",
				"2043 - mou (foil) | atlanta 2017",
				"2044 - mou (gold) | atlanta 2017",
				"2045 - adren | atlanta 2017",
				"2046 - adren (foil) | atlanta 2017",
				"2047 - adren (gold) | atlanta 2017",
				"2048 - byali | atlanta 2017",
				"2049 - byali (foil) | atlanta 2017",
				"2050 - byali (gold) | atlanta 2017",
				"2051 - neo | atlanta 2017",
				"2052 - neo (foil) | atlanta 2017",
				"2053 - neo (gold) | atlanta 2017",
				"2054 - pashabiceps | atlanta 2017",
				"2055 - pashabiceps (foil) | atlanta 2017",
				"2056 - pashabiceps (gold) | atlanta 2017",
				"2057 - snax | atlanta 2017",
				"2058 - snax (foil) | atlanta 2017",
				"2059 - snax (gold) | atlanta 2017",
				"2060 - taz | atlanta 2017",
				"2061 - taz (foil) | atlanta 2017",
				"2062 - taz (gold) | atlanta 2017",
				"2063 - astralis | krakow 2017",
				"2064 - astralis (holo) | krakow 2017",
				"2065 - astralis (foil) | krakow 2017",
				"2066 - astralis (gold) | krakow 2017",
				"2067 - virtus.pro | krakow 2017",
				"2068 - virtus.pro (holo) | krakow 2017",
				"2069 - virtus.pro (foil) | krakow 2017",
				"2070 - virtus.pro (gold) | krakow 2017",
				"2071 - fnatic | krakow 2017",
				"2072 - fnatic (holo) | krakow 2017",
				"2073 - fnatic (foil) | krakow 2017",
				"2074 - fnatic (gold) | krakow 2017",
				"2075 - sk gaming | krakow 2017",
				"2076 - sk gaming (holo) | krakow 2017",
				"2077 - sk gaming (foil) | krakow 2017",
				"2078 - sk gaming (gold) | krakow 2017",
				"2079 - natus vincere | krakow 2017",
				"2080 - natus vincere (holo) | krakow 2017",
				"2081 - natus vincere (foil) | krakow 2017",
				"2082 - natus vincere (gold) | krakow 2017",
				"2083 - gambit | krakow 2017",
				"2084 - gambit (holo) | krakow 2017",
				"2085 - gambit (foil) | krakow 2017",
				"2086 - gambit (gold) | krakow 2017",
				"2087 - north | krakow 2017",
				"2088 - north (holo) | krakow 2017",
				"2089 - north (foil) | krakow 2017",
				"2090 - north (gold) | krakow 2017",
				"2091 - faze clan | krakow 2017",
				"2092 - faze clan (holo) | krakow 2017",
				"2093 - faze clan (foil) | krakow 2017",
				"2094 - faze clan (gold) | krakow 2017",
				"2095 - mousesports | krakow 2017",
				"2096 - mousesports (holo) | krakow 2017",
				"2097 - mousesports (foil) | krakow 2017",
				"2098 - mousesports (gold) | krakow 2017",
				"2099 - g2 esports | krakow 2017",
				"2100 - g2 esports (holo) | krakow 2017",
				"2101 - g2 esports (foil) | krakow 2017",
				"2102 - g2 esports (gold) | krakow 2017",
				"2103 - big | krakow 2017",
				"2104 - big (holo) | krakow 2017",
				"2105 - big (foil) | krakow 2017",
				"2106 - big (gold) | krakow 2017",
				"2107 - cloud9 | krakow 2017",
				"2108 - cloud9 (holo) | krakow 2017",
				"2109 - cloud9 (foil) | krakow 2017",
				"2110 - cloud9 (gold) | krakow 2017",
				"2111 - penta sports | krakow 2017",
				"2112 - penta sports (holo) | krakow 2017",
				"2113 - penta sports (foil) | krakow 2017",
				"2114 - penta sports (gold) | krakow 2017",
				"2115 - flipsid3 tactics | krakow 2017",
				"2116 - flipsid3 tactics (holo) | krakow 2017",
				"2117 - flipsid3 tactics (foil) | krakow 2017",
				"2118 - flipsid3 tactics (gold) | krakow 2017",
				"2119 - immortals | krakow 2017",
				"2120 - immortals (holo) | krakow 2017",
				"2121 - immortals (foil) | krakow 2017",
				"2122 - immortals (gold) | krakow 2017",
				"2123 - vega squadron | krakow 2017",
				"2124 - vega squadron (holo) | krakow 2017",
				"2125 - vega squadron (foil) | krakow 2017",
				"2126 - vega squadron (gold) | krakow 2017",
				"2127 - pgl | krakow 2017",
				"2128 - pgl (holo) | krakow 2017",
				"2129 - pgl (foil) | krakow 2017",
				"2130 - pgl (gold) | krakow 2017",
				"2131 - astralis | krakow 2017",
				"2132 - virtus.pro | krakow 2017",
				"2133 - fnatic | krakow 2017",
				"2134 - sk gaming | krakow 2017",
				"2135 - natus vincere | krakow 2017",
				"2136 - gambit | krakow 2017",
				"2137 - north | krakow 2017",
				"2138 - faze clan | krakow 2017",
				"2139 - mousesports | krakow 2017",
				"2140 - g2 esports | krakow 2017",
				"2141 - big | krakow 2017",
				"2142 - cloud9 | krakow 2017",
				"2143 - penta sports | krakow 2017",
				"2144 - flipsid3 tactics | krakow 2017",
				"2145 - immortals | krakow 2017",
				"2146 - vega squadron | krakow 2017",
				"2147 - pgl | krakow 2017",
				"2148 - device | krakow 2017",
				"2149 - device (foil) | krakow 2017",
				"2150 - device (gold) | krakow 2017",
				"2151 - dupreeh | krakow 2017",
				"2152 - dupreeh (foil) | krakow 2017",
				"2153 - dupreeh (gold) | krakow 2017",
				"2154 - gla1ve | krakow 2017",
				"2155 - gla1ve (foil) | krakow 2017",
				"2156 - gla1ve (gold) | krakow 2017",
				"2157 - kjaerbye | krakow 2017",
				"2158 - kjaerbye (foil) | krakow 2017",
				"2159 - kjaerbye (gold) | krakow 2017",
				"2160 - xyp9x | krakow 2017",
				"2161 - xyp9x (foil) | krakow 2017",
				"2162 - xyp9x (gold) | krakow 2017",
				"2163 - byali | krakow 2017",
				"2164 - byali (foil) | krakow 2017",
				"2165 - byali (gold) | krakow 2017",
				"2166 - neo | krakow 2017",
				"2167 - neo (foil) | krakow 2017",
				"2168 - neo (gold) | krakow 2017",
				"2169 - pashabiceps | krakow 2017",
				"2170 - pashabiceps (foil) | krakow 2017",
				"2171 - pashabiceps (gold) | krakow 2017",
				"2172 - snax | krakow 2017",
				"2173 - snax (foil) | krakow 2017",
				"2174 - snax (gold) | krakow 2017",
				"2175 - taz | krakow 2017",
				"2176 - taz (foil) | krakow 2017",
				"2177 - taz (gold) | krakow 2017",
				"2178 - dennis | krakow 2017",
				"2179 - dennis (foil) | krakow 2017",
				"2180 - dennis (gold) | krakow 2017",
				"2181 - flusha | krakow 2017",
				"2182 - flusha (foil) | krakow 2017",
				"2183 - flusha (gold) | krakow 2017",
				"2184 - jw | krakow 2017",
				"2185 - jw (foil) | krakow 2017",
				"2186 - jw (gold) | krakow 2017",
				"2187 - krimz | krakow 2017",
				"2188 - krimz (foil) | krakow 2017",
				"2189 - krimz (gold) | krakow 2017",
				"2190 - olofmeister | krakow 2017",
				"2191 - olofmeister (foil) | krakow 2017",
				"2192 - olofmeister (gold) | krakow 2017",
				"2193 - coldzera | krakow 2017",
				"2194 - coldzera (foil) | krakow 2017",
				"2195 - coldzera (gold) | krakow 2017",
				"2196 - fallen | krakow 2017",
				"2197 - fallen (foil) | krakow 2017",
				"2198 - fallen (gold) | krakow 2017",
				"2199 - felps | krakow 2017",
				"2200 - felps (foil) | krakow 2017",
				"2201 - felps (gold) | krakow 2017",
				"2202 - fer | krakow 2017",
				"2203 - fer (foil) | krakow 2017",
				"2204 - fer (gold) | krakow 2017",
				"2205 - taco | krakow 2017",
				"2206 - taco (foil) | krakow 2017",
				"2207 - taco (gold) | krakow 2017",
				"2208 - edward | krakow 2017",
				"2209 - edward (foil) | krakow 2017",
				"2210 - edward (gold) | krakow 2017",
				"2211 - flamie | krakow 2017",
				"2212 - flamie (foil) | krakow 2017",
				"2213 - flamie (gold) | krakow 2017",
				"2214 - guardian | krakow 2017",
				"2215 - guardian (foil) | krakow 2017",
				"2216 - guardian (gold) | krakow 2017",
				"2217 - s1mple | krakow 2017",
				"2218 - s1mple (foil) | krakow 2017",
				"2219 - s1mple (gold) | krakow 2017",
				"2220 - seized | krakow 2017",
				"2221 - seized (foil) | krakow 2017",
				"2222 - seized (gold) | krakow 2017",
				"2223 - adren | krakow 2017",
				"2224 - adren (foil) | krakow 2017",
				"2225 - adren (gold) | krakow 2017",
				"2226 - dosia | krakow 2017",
				"2227 - dosia (foil) | krakow 2017",
				"2228 - dosia (gold) | krakow 2017",
				"2229 - hobbit | krakow 2017",
				"2230 - hobbit (foil) | krakow 2017",
				"2231 - hobbit (gold) | krakow 2017",
				"2232 - mou | krakow 2017",
				"2233 - mou (foil) | krakow 2017",
				"2234 - mou (gold) | krakow 2017",
				"2235 - zeus | krakow 2017",
				"2236 - zeus (foil) | krakow 2017",
				"2237 - zeus (gold) | krakow 2017",
				"2238 - aizy | krakow 2017",
				"2239 - aizy (foil) | krakow 2017",
				"2240 - aizy (gold) | krakow 2017",
				"2241 - cajunb | krakow 2017",
				"2242 - cajunb (foil) | krakow 2017",
				"2243 - cajunb (gold) | krakow 2017",
				"2244 - k0nfig | krakow 2017",
				"2245 - k0nfig (foil) | krakow 2017",
				"2246 - k0nfig (gold) | krakow 2017",
				"2247 - magisk | krakow 2017",
				"2248 - magisk (foil) | krakow 2017",
				"2249 - magisk (gold) | krakow 2017",
				"2250 - msl | krakow 2017",
				"2251 - msl (foil) | krakow 2017",
				"2252 - msl (gold) | krakow 2017",
				"2253 - allu | krakow 2017",
				"2254 - allu (foil) | krakow 2017",
				"2255 - allu (gold) | krakow 2017",
				"2256 - karrigan | krakow 2017",
				"2257 - karrigan (foil) | krakow 2017",
				"2258 - karrigan (gold) | krakow 2017",
				"2259 - kioshima | krakow 2017",
				"2260 - kioshima (foil) | krakow 2017",
				"2261 - kioshima (gold) | krakow 2017",
				"2262 - niko | krakow 2017",
				"2263 - niko (foil) | krakow 2017",
				"2264 - niko (gold) | krakow 2017",
				"2265 - rain | krakow 2017",
				"2266 - rain (foil) | krakow 2017",
				"2267 - rain (gold) | krakow 2017",
				"2268 - chrisj | krakow 2017",
				"2269 - chrisj (foil) | krakow 2017",
				"2270 - chrisj (gold) | krakow 2017",
				"2271 - denis | krakow 2017",
				"2272 - denis (foil) | krakow 2017",
				"2273 - denis (gold) | krakow 2017",
				"2274 - lowel | krakow 2017",
				"2275 - lowel (foil) | krakow 2017",
				"2276 - lowel (gold) | krakow 2017",
				"2277 - oskar | krakow 2017",
				"2278 - oskar (foil) | krakow 2017",
				"2279 - oskar (gold) | krakow 2017",
				"2280 - ropz | krakow 2017",
				"2281 - ropz (foil) | krakow 2017",
				"2282 - ropz (gold) | krakow 2017",
				"2283 - apex | krakow 2017",
				"2284 - apex (foil) | krakow 2017",
				"2285 - apex (gold) | krakow 2017",
				"2286 - bodyy | krakow 2017",
				"2287 - bodyy (foil) | krakow 2017",
				"2288 - bodyy (gold) | krakow 2017",
				"2289 - kennys | krakow 2017",
				"2290 - kennys (foil) | krakow 2017",
				"2291 - kennys (gold) | krakow 2017",
				"2292 - nbk- | krakow 2017",
				"2293 - nbk- (foil) | krakow 2017",
				"2294 - nbk- (gold) | krakow 2017",
				"2295 - shox | krakow 2017",
				"2296 - shox (foil) | krakow 2017",
				"2297 - shox (gold) | krakow 2017",
				"2298 - gob b | krakow 2017",
				"2299 - gob b (foil) | krakow 2017",
				"2300 - gob b (gold) | krakow 2017",
				"2301 - keev | krakow 2017",
				"2302 - keev (foil) | krakow 2017",
				"2303 - keev (gold) | krakow 2017",
				"2304 - legija | krakow 2017",
				"2305 - legija (foil) | krakow 2017",
				"2306 - legija (gold) | krakow 2017",
				"2307 - nex | krakow 2017",
				"2308 - nex (foil) | krakow 2017",
				"2309 - nex (gold) | krakow 2017",
				"2310 - tabsen | krakow 2017",
				"2311 - tabsen (foil) | krakow 2017",
				"2312 - tabsen (gold) | krakow 2017",
				"2313 - autimatic | krakow 2017",
				"2314 - autimatic (foil) | krakow 2017",
				"2315 - autimatic (gold) | krakow 2017",
				"2316 - n0thing | krakow 2017",
				"2317 - n0thing (foil) | krakow 2017",
				"2318 - n0thing (gold) | krakow 2017",
				"2319 - shroud | krakow 2017",
				"2320 - shroud (foil) | krakow 2017",
				"2321 - shroud (gold) | krakow 2017",
				"2322 - skadoodle | krakow 2017",
				"2323 - skadoodle (foil) | krakow 2017",
				"2324 - skadoodle (gold) | krakow 2017",
				"2325 - stewie2k | krakow 2017",
				"2326 - stewie2k (foil) | krakow 2017",
				"2327 - stewie2k (gold) | krakow 2017",
				"2328 - hs | krakow 2017",
				"2329 - hs (foil) | krakow 2017",
				"2330 - hs (gold) | krakow 2017",
				"2331 - innocent | krakow 2017",
				"2332 - innocent (foil) | krakow 2017",
				"2333 - innocent (gold) | krakow 2017",
				"2334 - krystal | krakow 2017",
				"2335 - krystal (foil) | krakow 2017",
				"2336 - krystal (gold) | krakow 2017",
				"2337 - sunny | krakow 2017",
				"2338 - sunny (foil) | krakow 2017",
				"2339 - sunny (gold) | krakow 2017",
				"2340 - zehn | krakow 2017",
				"2341 - zehn (foil) | krakow 2017",
				"2342 - zehn (gold) | krakow 2017",
				"2343 - b1ad3 | krakow 2017",
				"2344 - b1ad3 (foil) | krakow 2017",
				"2345 - b1ad3 (gold) | krakow 2017",
				"2346 - electronic | krakow 2017",
				"2347 - electronic (foil) | krakow 2017",
				"2348 - electronic (gold) | krakow 2017",
				"2349 - markeloff | krakow 2017",
				"2350 - markeloff (foil) | krakow 2017",
				"2351 - markeloff (gold) | krakow 2017",
				"2352 - waylander | krakow 2017",
				"2353 - waylander (foil) | krakow 2017",
				"2354 - waylander (gold) | krakow 2017",
				"2355 - worldedit | krakow 2017",
				"2356 - worldedit (foil) | krakow 2017",
				"2357 - worldedit (gold) | krakow 2017",
				"2358 - boltz | krakow 2017",
				"2359 - boltz (foil) | krakow 2017",
				"2360 - boltz (gold) | krakow 2017",
				"2361 - hen1 | krakow 2017",
				"2362 - hen1 (foil) | krakow 2017",
				"2363 - hen1 (gold) | krakow 2017",
				"2364 - kngv- | krakow 2017",
				"2365 - kngv- (foil) | krakow 2017",
				"2366 - kngv- (gold) | krakow 2017",
				"2367 - lucas1 | krakow 2017",
				"2368 - lucas1 (foil) | krakow 2017",
				"2369 - lucas1 (gold) | krakow 2017",
				"2370 - steel | krakow 2017",
				"2371 - steel (foil) | krakow 2017",
				"2372 - steel (gold) | krakow 2017",
				"2373 - chopper | krakow 2017",
				"2374 - chopper (foil) | krakow 2017",
				"2375 - chopper (gold) | krakow 2017",
				"2376 - hutji | krakow 2017",
				"2377 - hutji (foil) | krakow 2017",
				"2378 - hutji (gold) | krakow 2017",
				"2379 - jr | krakow 2017",
				"2380 - jr (foil) | krakow 2017",
				"2381 - jr (gold) | krakow 2017",
				"2382 - keshandr | krakow 2017",
				"2383 - keshandr (foil) | krakow 2017",
				"2384 - keshandr (gold) | krakow 2017",
				"2385 - mir | krakow 2017",
				"2386 - mir (foil) | krakow 2017",
				"2387 - mir (gold) | krakow 2017",
				"2388 - water gun",
				"2389 - cheongsam",
				"2390 - cheongsam (holo)",
				"2391 - fancy koi",
				"2392 - fancy koi (foil)",
				"2393 - guardian dragon",
				"2394 - guardian dragon (foil)",
				"2395 - hotpot",
				"2396 - noodles",
				"2397 - rice bomb",
				"2398 - terror rice",
				"2399 - mahjong fa",
				"2400 - mahjong rooster",
				"2401 - mahjong zhong",
				"2402 - toy tiger",
				"2403 - god of fortune",
				"2404 - huaji",
				"2405 - nezha",
				"2406 - rage",
				"2407 - longevity",
				"2408 - longevity (foil)",
				"2409 - non-veg",
				"2410 - pixiu",
				"2411 - pixiu (foil)",
				"2412 - twin koi",
				"2413 - twin koi (holo)",
				"2414 - shaolin",
				"2415 - green swallow",
				"2416 - blue swallow",
				"2417 - zombie hop",
				"2418 - water gun",
				"2419 - cheongsam",
				"2420 - guardian dragon",
				"2421 - rage",
				"2422 - god of fortune",
				"2423 - hotpot",
				"2424 - fancy koi",
				"2425 - longevity",
				"2426 - nezha",
				"2427 - noodles",
				"2428 - non-veg",
				"2429 - pixiu",
				"2430 - twin koi",
				"2431 - rice bomb",
				"2432 - terror rice",
				"2433 - shaolin",
				"2434 - toy tiger",
				"2435 - zombie hop",
				"2436 - gambit esports | boston 2018",
				"2437 - gambit esports (holo) | boston 2018",
				"2438 - gambit esports (foil) | boston 2018",
				"2439 - gambit esports (gold) | boston 2018",
				"2440 - 100 thieves | boston 2018",
				"2441 - 100 thieves (holo) | boston 2018",
				"2442 - 100 thieves (foil) | boston 2018",
				"2443 - 100 thieves (gold) | boston 2018",
				"2444 - astralis | boston 2018",
				"2445 - astralis (holo) | boston 2018",
				"2446 - astralis (foil) | boston 2018",
				"2447 - astralis (gold) | boston 2018",
				"2448 - virtus.pro | boston 2018",
				"2449 - virtus.pro (holo) | boston 2018",
				"2450 - virtus.pro (foil) | boston 2018",
				"2451 - virtus.pro (gold) | boston 2018",
				"2452 - fnatic | boston 2018",
				"2453 - fnatic (holo) | boston 2018",
				"2454 - fnatic (foil) | boston 2018",
				"2455 - fnatic (gold) | boston 2018",
				"2456 - sk gaming | boston 2018",
				"2457 - sk gaming (holo) | boston 2018",
				"2458 - sk gaming (foil) | boston 2018",
				"2459 - sk gaming (gold) | boston 2018",
				"2460 - big | boston 2018",
				"2461 - big (holo) | boston 2018",
				"2462 - big (foil) | boston 2018",
				"2463 - big (gold) | boston 2018",
				"2464 - north | boston 2018",
				"2465 - north (holo) | boston 2018",
				"2466 - north (foil) | boston 2018",
				"2467 - north (gold) | boston 2018",
				"2468 - g2 esports | boston 2018",
				"2469 - g2 esports (holo) | boston 2018",
				"2470 - g2 esports (foil) | boston 2018",
				"2471 - g2 esports (gold) | boston 2018",
				"2472 - cloud9 | boston 2018",
				"2473 - cloud9 (holo) | boston 2018",
				"2474 - cloud9 (foil) | boston 2018",
				"2475 - cloud9 (gold) | boston 2018",
				"2476 - flipsid3 tactics | boston 2018",
				"2477 - flipsid3 tactics (holo) | boston 2018",
				"2478 - flipsid3 tactics (foil) | boston 2018",
				"2479 - flipsid3 tactics (gold) | boston 2018",
				"2480 - natus vincere | boston 2018",
				"2481 - natus vincere (holo) | boston 2018",
				"2482 - natus vincere (foil) | boston 2018",
				"2483 - natus vincere (gold) | boston 2018",
				"2484 - mousesports | boston 2018",
				"2485 - mousesports (holo) | boston 2018",
				"2486 - mousesports (foil) | boston 2018",
				"2487 - mousesports (gold) | boston 2018",
				"2488 - sprout esports | boston 2018",
				"2489 - sprout esports (holo) | boston 2018",
				"2490 - sprout esports (foil) | boston 2018",
				"2491 - sprout esports (gold) | boston 2018",
				"2492 - faze clan | boston 2018",
				"2493 - faze clan (holo) | boston 2018",
				"2494 - faze clan (foil) | boston 2018",
				"2495 - faze clan (gold) | boston 2018",
				"2496 - vega squadron | boston 2018",
				"2497 - vega squadron (holo) | boston 2018",
				"2498 - vega squadron (foil) | boston 2018",
				"2499 - vega squadron (gold) | boston 2018",
				"2500 - space soldiers | boston 2018",
				"2501 - space soldiers (holo) | boston 2018",
				"2502 - space soldiers (foil) | boston 2018",
				"2503 - space soldiers (gold) | boston 2018",
				"2504 - team liquid | boston 2018",
				"2505 - team liquid (holo) | boston 2018",
				"2506 - team liquid (foil) | boston 2018",
				"2507 - team liquid (gold) | boston 2018",
				"2508 - avangar | boston 2018",
				"2509 - avangar (holo) | boston 2018",
				"2510 - avangar (foil) | boston 2018",
				"2511 - avangar (gold) | boston 2018",
				"2512 - renegades | boston 2018",
				"2513 - renegades (holo) | boston 2018",
				"2514 - renegades (foil) | boston 2018",
				"2515 - renegades (gold) | boston 2018",
				"2516 - team envyus | boston 2018",
				"2517 - team envyus (holo) | boston 2018",
				"2518 - team envyus (foil) | boston 2018",
				"2519 - team envyus (gold) | boston 2018",
				"2520 - misfits gaming | boston 2018",
				"2521 - misfits gaming (holo) | boston 2018",
				"2522 - misfits gaming (foil) | boston 2018",
				"2523 - misfits gaming (gold) | boston 2018",
				"2524 - quantum bellator fire | boston 2018",
				"2525 - quantum bellator fire (holo) | boston 2018",
				"2526 - quantum bellator fire (foil) | boston 2018",
				"2527 - quantum bellator fire (gold) | boston 2018",
				"2528 - tyloo | boston 2018",
				"2529 - tyloo (holo) | boston 2018",
				"2530 - tyloo (foil) | boston 2018",
				"2531 - tyloo (gold) | boston 2018",
				"2532 - eleague | boston 2018",
				"2533 - eleague (holo) | boston 2018",
				"2534 - eleague (foil) | boston 2018",
				"2535 - eleague (gold) | boston 2018",
				"2536 - gambit esports | boston 2018",
				"2537 - 100 thieves | boston 2018",
				"2538 - astralis | boston 2018",
				"2539 - virtus.pro | boston 2018",
				"2540 - fnatic | boston 2018",
				"2541 - sk gaming | boston 2018",
				"2542 - big | boston 2018",
				"2543 - north | boston 2018",
				"2544 - g2 esports | boston 2018",
				"2545 - cloud9 | boston 2018",
				"2546 - flipsid3 tactics | boston 2018",
				"2547 - natus vincere | boston 2018",
				"2548 - mousesports | boston 2018",
				"2549 - sprout esports | boston 2018",
				"2550 - faze clan | boston 2018",
				"2551 - vega squadron | boston 2018",
				"2552 - space soldiers | boston 2018",
				"2553 - team liquid | boston 2018",
				"2554 - avangar | boston 2018",
				"2555 - renegades | boston 2018",
				"2556 - team envyus | boston 2018",
				"2557 - misfits gaming | boston 2018",
				"2558 - quantum bellator fire | boston 2018",
				"2559 - tyloo | boston 2018",
				"2560 - eleague | boston 2018",
				"2561 - adren | boston 2018",
				"2562 - adren (foil) | boston 2018",
				"2563 - adren (gold) | boston 2018",
				"2564 - dosia | boston 2018",
				"2565 - dosia (foil) | boston 2018",
				"2566 - dosia (gold) | boston 2018",
				"2567 - fitch | boston 2018",
				"2568 - fitch (foil) | boston 2018",
				"2569 - fitch (gold) | boston 2018",
				"2570 - hobbit | boston 2018",
				"2571 - hobbit (foil) | boston 2018",
				"2572 - hobbit (gold) | boston 2018",
				"2573 - mou | boston 2018",
				"2574 - mou (foil) | boston 2018",
				"2575 - mou (gold) | boston 2018",
				"2576 - bit | boston 2018",
				"2577 - bit (foil) | boston 2018",
				"2578 - bit (gold) | boston 2018",
				"2579 - fnx | boston 2018",
				"2580 - fnx (foil) | boston 2018",
				"2581 - fnx (gold) | boston 2018",
				"2582 - hen1 | boston 2018",
				"2583 - hen1 (foil) | boston 2018",
				"2584 - hen1 (gold) | boston 2018",
				"2585 - kngv- | boston 2018",
				"2586 - kngv- (foil) | boston 2018",
				"2587 - kngv- (gold) | boston 2018",
				"2588 - lucas1 | boston 2018",
				"2589 - lucas1 (foil) | boston 2018",
				"2590 - lucas1 (gold) | boston 2018",
				"2591 - device | boston 2018",
				"2592 - device (foil) | boston 2018",
				"2593 - device (gold) | boston 2018",
				"2594 - dupreeh | boston 2018",
				"2595 - dupreeh (foil) | boston 2018",
				"2596 - dupreeh (gold) | boston 2018",
				"2597 - gla1ve | boston 2018",
				"2598 - gla1ve (foil) | boston 2018",
				"2599 - gla1ve (gold) | boston 2018",
				"2600 - kjaerbye | boston 2018",
				"2601 - kjaerbye (foil) | boston 2018",
				"2602 - kjaerbye (gold) | boston 2018",
				"2603 - xyp9x | boston 2018",
				"2604 - xyp9x (foil) | boston 2018",
				"2605 - xyp9x (gold) | boston 2018",
				"2606 - byali | boston 2018",
				"2607 - byali (foil) | boston 2018",
				"2608 - byali (gold) | boston 2018",
				"2609 - neo | boston 2018",
				"2610 - neo (foil) | boston 2018",
				"2611 - neo (gold) | boston 2018",
				"2612 - pashabiceps | boston 2018",
				"2613 - pashabiceps (foil) | boston 2018",
				"2614 - pashabiceps (gold) | boston 2018",
				"2615 - snax | boston 2018",
				"2616 - snax (foil) | boston 2018",
				"2617 - snax (gold) | boston 2018",
				"2618 - taz | boston 2018",
				"2619 - taz (foil) | boston 2018",
				"2620 - taz (gold) | boston 2018",
				"2621 - flusha | boston 2018",
				"2622 - flusha (foil) | boston 2018",
				"2623 - flusha (gold) | boston 2018",
				"2624 - golden | boston 2018",
				"2625 - golden (foil) | boston 2018",
				"2626 - golden (gold) | boston 2018",
				"2627 - jw | boston 2018",
				"2628 - jw (foil) | boston 2018",
				"2629 - jw (gold) | boston 2018",
				"2630 - krimz | boston 2018",
				"2631 - krimz (foil) | boston 2018",
				"2632 - krimz (gold) | boston 2018",
				"2633 - lekr0 | boston 2018",
				"2634 - lekr0 (foil) | boston 2018",
				"2635 - lekr0 (gold) | boston 2018",
				"2636 - coldzera | boston 2018",
				"2637 - coldzera (foil) | boston 2018",
				"2638 - coldzera (gold) | boston 2018",
				"2639 - fallen | boston 2018",
				"2640 - fallen (foil) | boston 2018",
				"2641 - fallen (gold) | boston 2018",
				"2642 - felps | boston 2018",
				"2643 - felps (foil) | boston 2018",
				"2644 - felps (gold) | boston 2018",
				"2645 - fer | boston 2018",
				"2646 - fer (foil) | boston 2018",
				"2647 - fer (gold) | boston 2018",
				"2648 - taco | boston 2018",
				"2649 - taco (foil) | boston 2018",
				"2650 - taco (gold) | boston 2018",
				"2651 - gob b | boston 2018",
				"2652 - gob b (foil) | boston 2018",
				"2653 - gob b (gold) | boston 2018",
				"2654 - keev | boston 2018",
				"2655 - keev (foil) | boston 2018",
				"2656 - keev (gold) | boston 2018",
				"2657 - legija | boston 2018",
				"2658 - legija (foil) | boston 2018",
				"2659 - legija (gold) | boston 2018",
				"2660 - nex | boston 2018",
				"2661 - nex (foil) | boston 2018",
				"2662 - nex (gold) | boston 2018",
				"2663 - tabsen | boston 2018",
				"2664 - tabsen (foil) | boston 2018",
				"2665 - tabsen (gold) | boston 2018",
				"2666 - aizy | boston 2018",
				"2667 - aizy (foil) | boston 2018",
				"2668 - aizy (gold) | boston 2018",
				"2669 - cajunb | boston 2018",
				"2670 - cajunb (foil) | boston 2018",
				"2671 - cajunb (gold) | boston 2018",
				"2672 - k0nfig | boston 2018",
				"2673 - k0nfig (foil) | boston 2018",
				"2674 - k0nfig (gold) | boston 2018",
				"2675 - msl | boston 2018",
				"2676 - msl (foil) | boston 2018",
				"2677 - msl (gold) | boston 2018",
				"2678 - v4lde | boston 2018",
				"2679 - v4lde (foil) | boston 2018",
				"2680 - v4lde (gold) | boston 2018",
				"2681 - apex | boston 2018",
				"2682 - apex (foil) | boston 2018",
				"2683 - apex (gold) | boston 2018",
				"2684 - bodyy | boston 2018",
				"2685 - bodyy (foil) | boston 2018",
				"2686 - bodyy (gold) | boston 2018",
				"2687 - kennys | boston 2018",
				"2688 - kennys (foil) | boston 2018",
				"2689 - kennys (gold) | boston 2018",
				"2690 - nbk- | boston 2018",
				"2691 - nbk- (foil) | boston 2018",
				"2692 - nbk- (gold) | boston 2018",
				"2693 - shox | boston 2018",
				"2694 - shox (foil) | boston 2018",
				"2695 - shox (gold) | boston 2018",
				"2696 - autimatic | boston 2018",
				"2697 - autimatic (foil) | boston 2018",
				"2698 - autimatic (gold) | boston 2018",
				"2699 - rush | boston 2018",
				"2700 - rush (foil) | boston 2018",
				"2701 - rush (gold) | boston 2018",
				"2702 - skadoodle | boston 2018",
				"2703 - skadoodle (foil) | boston 2018",
				"2704 - skadoodle (gold) | boston 2018",
				"2705 - stewie2k | boston 2018",
				"2706 - stewie2k (foil) | boston 2018",
				"2707 - stewie2k (gold) | boston 2018",
				"2708 - tarik | boston 2018",
				"2709 - tarik (foil) | boston 2018",
				"2710 - tarik (gold) | boston 2018",
				"2711 - b1ad3 | boston 2018",
				"2712 - b1ad3 (foil) | boston 2018",
				"2713 - b1ad3 (gold) | boston 2018",
				"2714 - markeloff | boston 2018",
				"2715 - markeloff (foil) | boston 2018",
				"2716 - markeloff (gold) | boston 2018",
				"2717 - seized | boston 2018",
				"2718 - seized (foil) | boston 2018",
				"2719 - seized (gold) | boston 2018",
				"2720 - waylander | boston 2018",
				"2721 - waylander (foil) | boston 2018",
				"2722 - waylander (gold) | boston 2018",
				"2723 - worldedit | boston 2018",
				"2724 - worldedit (foil) | boston 2018",
				"2725 - worldedit (gold) | boston 2018",
				"2726 - edward | boston 2018",
				"2727 - edward (foil) | boston 2018",
				"2728 - edward (gold) | boston 2018",
				"2729 - electronic | boston 2018",
				"2730 - electronic (foil) | boston 2018",
				"2731 - electronic (gold) | boston 2018",
				"2732 - flamie | boston 2018",
				"2733 - flamie (foil) | boston 2018",
				"2734 - flamie (gold) | boston 2018",
				"2735 - s1mple | boston 2018",
				"2736 - s1mple (foil) | boston 2018",
				"2737 - s1mple (gold) | boston 2018",
				"2738 - zeus | boston 2018",
				"2739 - zeus (foil) | boston 2018",
				"2740 - zeus (gold) | boston 2018",
				"2741 - chrisj | boston 2018",
				"2742 - chrisj (foil) | boston 2018",
				"2743 - chrisj (gold) | boston 2018",
				"2744 - oskar | boston 2018",
				"2745 - oskar (foil) | boston 2018",
				"2746 - oskar (gold) | boston 2018",
				"2747 - ropz | boston 2018",
				"2748 - ropz (foil) | boston 2018",
				"2749 - ropz (gold) | boston 2018",
				"2750 - styko | boston 2018",
				"2751 - styko (foil) | boston 2018",
				"2752 - styko (gold) | boston 2018",
				"2753 - sunny | boston 2018",
				"2754 - sunny (foil) | boston 2018",
				"2755 - sunny (gold) | boston 2018",
				"2756 - denis | boston 2018",
				"2757 - denis (foil) | boston 2018",
				"2758 - denis (gold) | boston 2018",
				"2759 - innocent | boston 2018",
				"2760 - innocent (foil) | boston 2018",
				"2761 - innocent (gold) | boston 2018",
				"2762 - krystal | boston 2018",
				"2763 - krystal (foil) | boston 2018",
				"2764 - krystal (gold) | boston 2018",
				"2765 - spiidi | boston 2018",
				"2766 - spiidi (foil) | boston 2018",
				"2767 - spiidi (gold) | boston 2018",
				"2768 - zehn | boston 2018",
				"2769 - zehn (foil) | boston 2018",
				"2770 - zehn (gold) | boston 2018",
				"2771 - guardian | boston 2018",
				"2772 - guardian (foil) | boston 2018",
				"2773 - guardian (gold) | boston 2018",
				"2774 - karrigan | boston 2018",
				"2775 - karrigan (foil) | boston 2018",
				"2776 - karrigan (gold) | boston 2018",
				"2777 - niko | boston 2018",
				"2778 - niko (foil) | boston 2018",
				"2779 - niko (gold) | boston 2018",
				"2780 - olofmeister | boston 2018",
				"2781 - olofmeister (foil) | boston 2018",
				"2782 - olofmeister (gold) | boston 2018",
				"2783 - rain | boston 2018",
				"2784 - rain (foil) | boston 2018",
				"2785 - rain (gold) | boston 2018",
				"2786 - chopper | boston 2018",
				"2787 - chopper (foil) | boston 2018",
				"2788 - chopper (gold) | boston 2018",
				"2789 - hutji | boston 2018",
				"2790 - hutji (foil) | boston 2018",
				"2791 - hutji (gold) | boston 2018",
				"2792 - jr | boston 2018",
				"2793 - jr (foil) | boston 2018",
				"2794 - jr (gold) | boston 2018",
				"2795 - keshandr | boston 2018",
				"2796 - keshandr (foil) | boston 2018",
				"2797 - keshandr (gold) | boston 2018",
				"2798 - mir | boston 2018",
				"2799 - mir (foil) | boston 2018",
				"2800 - mir (gold) | boston 2018",
				"2801 - calyx | boston 2018",
				"2802 - calyx (foil) | boston 2018",
				"2803 - calyx (gold) | boston 2018",
				"2804 - maj3r | boston 2018",
				"2805 - maj3r (foil) | boston 2018",
				"2806 - maj3r (gold) | boston 2018",
				"2807 - ngin | boston 2018",
				"2808 - ngin (foil) | boston 2018",
				"2809 - ngin (gold) | boston 2018",
				"2810 - paz | boston 2018",
				"2811 - paz (foil) | boston 2018",
				"2812 - paz (gold) | boston 2018",
				"2813 - xantares | boston 2018",
				"2814 - xantares (foil) | boston 2018",
				"2815 - xantares (gold) | boston 2018",
				"2816 - elige | boston 2018",
				"2817 - elige (foil) | boston 2018",
				"2818 - elige (gold) | boston 2018",
				"2819 - jdm64 | boston 2018",
				"2820 - jdm64 (foil) | boston 2018",
				"2821 - jdm64 (gold) | boston 2018",
				"2822 - nitr0 | boston 2018",
				"2823 - nitr0 (foil) | boston 2018",
				"2824 - nitr0 (gold) | boston 2018",
				"2825 - stanislaw | boston 2018",
				"2826 - stanislaw (foil) | boston 2018",
				"2827 - stanislaw (gold) | boston 2018",
				"2828 - twistzz | boston 2018",
				"2829 - twistzz (foil) | boston 2018",
				"2830 - twistzz (gold) | boston 2018",
				"2831 - buster | boston 2018",
				"2832 - buster (foil) | boston 2018",
				"2833 - buster (gold) | boston 2018",
				"2834 - dimasick | boston 2018",
				"2835 - dimasick (foil) | boston 2018",
				"2836 - dimasick (gold) | boston 2018",
				"2837 - jame | boston 2018",
				"2838 - jame (foil) | boston 2018",
				"2839 - jame (gold) | boston 2018",
				"2840 - krizzen | boston 2018",
				"2841 - krizzen (foil) | boston 2018",
				"2842 - krizzen (gold) | boston 2018",
				"2843 - qikert | boston 2018",
				"2844 - qikert (foil) | boston 2018",
				"2845 - qikert (gold) | boston 2018",
				"2846 - azr | boston 2018",
				"2847 - azr (foil) | boston 2018",
				"2848 - azr (gold) | boston 2018",
				"2849 - jks | boston 2018",
				"2850 - jks (foil) | boston 2018",
				"2851 - jks (gold) | boston 2018",
				"2852 - naf | boston 2018",
				"2853 - naf (foil) | boston 2018",
				"2854 - naf (gold) | boston 2018",
				"2855 - nifty | boston 2018",
				"2856 - nifty (foil) | boston 2018",
				"2857 - nifty (gold) | boston 2018",
				"2858 - ustilo | boston 2018",
				"2859 - ustilo (foil) | boston 2018",
				"2860 - ustilo (gold) | boston 2018",
				"2861 - happy | boston 2018",
				"2862 - happy (foil) | boston 2018",
				"2863 - happy (gold) | boston 2018",
				"2864 - rpk | boston 2018",
				"2865 - rpk (foil) | boston 2018",
				"2866 - rpk (gold) | boston 2018",
				"2867 - scream | boston 2018",
				"2868 - scream (foil) | boston 2018",
				"2869 - scream (gold) | boston 2018",
				"2870 - sixer | boston 2018",
				"2871 - sixer (foil) | boston 2018",
				"2872 - sixer (gold) | boston 2018",
				"2873 - xms | boston 2018",
				"2874 - xms (foil) | boston 2018",
				"2875 - xms (gold) | boston 2018",
				"2876 - amanek | boston 2018",
				"2877 - amanek (foil) | boston 2018",
				"2878 - amanek (gold) | boston 2018",
				"2879 - devoduvek | boston 2018",
				"2880 - devoduvek (foil) | boston 2018",
				"2881 - devoduvek (gold) | boston 2018",
				"2882 - seang@res | boston 2018",
				"2883 - seang@res (foil) | boston 2018",
				"2884 - seang@res (gold) | boston 2018",
				"2885 - shahzam | boston 2018",
				"2886 - shahzam (foil) | boston 2018",
				"2887 - shahzam (gold) | boston 2018",
				"2888 - sick | boston 2018",
				"2889 - sick (foil) | boston 2018",
				"2890 - sick (gold) | boston 2018",
				"2891 - balblna | boston 2018",
				"2892 - balblna (foil) | boston 2018",
				"2893 - balblna (gold) | boston 2018",
				"2894 - boombl4 | boston 2018",
				"2895 - boombl4 (foil) | boston 2018",
				"2896 - boombl4 (gold) | boston 2018",
				"2897 - jmqa | boston 2018",
				"2898 - jmqa (foil) | boston 2018",
				"2899 - jmqa (gold) | boston 2018",
				"2900 - kvik | boston 2018",
				"2901 - kvik (foil) | boston 2018",
				"2902 - kvik (gold) | boston 2018",
				"2903 - waterfallz | boston 2018",
				"2904 - waterfallz (foil) | boston 2018",
				"2905 - waterfallz (gold) | boston 2018",
				"2906 - bntet | boston 2018",
				"2907 - bntet (foil) | boston 2018",
				"2908 - bntet (gold) | boston 2018",
				"2909 - bondik | boston 2018",
				"2910 - bondik (foil) | boston 2018",
				"2911 - bondik (gold) | boston 2018",
				"2912 - captainmo | boston 2018",
				"2913 - captainmo (foil) | boston 2018",
				"2914 - captainmo (gold) | boston 2018",
				"2915 - dd | boston 2018",
				"2916 - dd (foil) | boston 2018",
				"2917 - dd (gold) | boston 2018",
				"2918 - somebody | boston 2018",
				"2919 - somebody (foil) | boston 2018",
				"2920 - somebody (gold) | boston 2018",
				"2935 - flash gaming | boston 2018",
				"2936 - flash gaming (holo) | boston 2018",
				"2937 - flash gaming (foil) | boston 2018",
				"2938 - flash gaming (gold) | boston 2018",
				"2939 - flash gaming | boston 2018",
				"2940 - attacker | boston 2018",
				"2941 - attacker (foil) | boston 2018",
				"2942 - attacker (gold) | boston 2018",
				"2943 - karsa | boston 2018",
				"2944 - karsa (foil) | boston 2018",
				"2945 - karsa (gold) | boston 2018",
				"2946 - kaze | boston 2018",
				"2947 - kaze (foil) | boston 2018",
				"2948 - kaze (gold) | boston 2018",
				"2949 - loveyy | boston 2018",
				"2950 - loveyy (foil) | boston 2018",
				"2951 - loveyy (gold) | boston 2018",
				"2952 - summer | boston 2018",
				"2953 - summer (foil) | boston 2018",
				"2954 - summer (gold) | boston 2018",
			};
			for (int i = 0; i < IM_ARRAYSIZE(Stickers); i++)
				if (filter.PassFilter(Stickers[i]))
					ImGui::Text("%s", Stickers[i]);

			ImGui::End();
		}

		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}


	if (bIsGuiVisible)
	{
		int pX, pY;
		Interfaces::InputSystem()->GetCursorPosition(&pX, &pY);

		ImGui::GetIO().MousePos.x = (float)pX;
		ImGui::GetIO().MousePos.y = (float)pY;

		Client::OnRenderGUI();
	}

	if (g_pRadar)
		g_pRadar->OnRender();

	g_pGui->GUI_End_Render();
}



void CGui::MenuColor()
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (Settings::Misc::misc_RainbowMenu)
	{
		static float rainbow;
		rainbow += Settings::Misc::misc_RainbowSpeed;
		if (rainbow > 1.f) rainbow = 0.f;

		ImVec4 mainColorActive = Color2::ToImColor(Color2::FromHSB(rainbow, 1.f, 0.7f));

		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, .78f);
		style.Colors[ImGuiCol_TextDisabled] = mainColorActive;;
		style.Colors[ImGuiCol_WindowBg] = mainColorActive;
		style.Colors[ImGuiCol_ChildWindowBg] = mainColorActive;
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.78f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = mainColorActive;
		style.Colors[ImGuiCol_ScrollbarGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = mainColorActive;
		style.Colors[ImGuiCol_SliderGrab] = mainColorActive;
		style.Colors[ImGuiCol_SliderGrabActive] = mainColorActive;
		style.Colors[ImGuiCol_Button] = ImVec4(0.13f, 0.14f, 0.17f, 0.85f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.86f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_Header] = mainColorActive;
		style.Colors[ImGuiCol_HeaderHovered] = mainColorActive;
		style.Colors[ImGuiCol_HeaderActive] = mainColorActive;
		style.Colors[ImGuiCol_Column] = ImVec4(0.15f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_ColumnHovered] = mainColorActive;
		style.Colors[ImGuiCol_ColumnActive] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGrip] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGripHovered] = mainColorActive;
		style.Colors[ImGuiCol_ResizeGripActive] = mainColorActive;
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = mainColorActive;
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = mainColorActive;
		style.Colors[ImGuiCol_TextSelectedBg] = mainColorActive;
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
	}
	else
	{

		float r = Settings::Misc::misc_MenuColor[0];
		float g = Settings::Misc::misc_MenuColor[1];
		float b = Settings::Misc::misc_MenuColor[2];

		float tR = Settings::Misc::misc_TextColor[0];
		float tG = Settings::Misc::misc_TextColor[1];
		float tB = Settings::Misc::misc_TextColor[2];

		style.Colors[ImGuiCol_Text] = ImVec4(tR, tG, tB, .78f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(r, g, b, 0.78f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(r, g, b, 1.f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(r, g, b, 0.75f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.78f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(r, g, b, 0.78f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(r, g, b, 0.37f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.13f, 0.14f, 0.17f, 0.85f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.14f, 0.17f, 0.86f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(r, g, b, 0.76f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(r, g, b, 0.86f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_Column] = ImVec4(0.15f, 0.00f, 0.00f, 0.35f);
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(r, g, b, 0.59f);
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(r, g, b, 0.63f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(r, g, b, 0.78f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(r, g, b, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(r, g, b, 0.43f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
	}
}

void CGui::purple()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.87f, 0.85f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.87f, 0.85f, 0.92f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.12f, 0.16f, 0.71f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.27f, 0.20f, 0.39f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.87f, 0.85f, 0.92f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.27f, 0.20f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.34f, 0.19f, 0.63f, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.46f, 0.27f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.34f, 0.19f, 0.63f, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.34f, 0.19f, 0.63f, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.34f, 0.19f, 0.63f, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.27f, 0.20f, 0.39f, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.27f, 0.20f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.19f, 0.63f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.34f, 0.19f, 0.63f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.27f, 0.20f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.34f, 0.19f, 0.63f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.19f, 0.63f, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.34f, 0.19f, 0.63f, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.34f, 0.19f, 0.63f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.34f, 0.19f, 0.63f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.34f, 0.19f, 0.63f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.87f, 0.85f, 0.92f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.87f, 0.85f, 0.92f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.87f, 0.85f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.34f, 0.19f, 0.63f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.34f, 0.19f, 0.63f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.87f, 0.85f, 0.92f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.87f, 0.85f, 0.92f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.87f, 0.85f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.87f, 0.85f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.87f, 0.85f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.34f, 0.19f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.34f, 0.19f, 0.63f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::DefaultSheme1()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::RedSheme()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.58f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.92f, 0.18f, 0.29f, 0.37f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.92f, 0.18f, 0.29f, 0.75f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.92f, 0.18f, 0.29f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.15f, 0.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.59f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.92f, 0.18f, 0.29f, 0.63f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.78f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.92f, 0.18f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
}

void CGui::darkblue()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void CGui::MidNightSheme()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.89f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.85f, 0.89f, 0.92f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.14f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.30f, 0.39f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.85f, 0.89f, 0.92f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.30f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.32f, 0.60f, 0.92f, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.77f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.77f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.77f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.08f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.47f, 1.00f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.10f, 0.38f, 0.62f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.13f, 0.44f, 0.72f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.12f, 0.45f, 0.55f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.00f, 0.00f, 0.77f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.77f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.77f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.05f, 0.27f, 0.48f, 0.59f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.05f, 0.27f, 0.48f, 0.59f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.24f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.85f, 0.89f, 0.92f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.85f, 0.89f, 0.92f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.85f, 0.89f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.43f, 0.63f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.19f, 0.43f, 0.63f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.85f, 0.89f, 0.92f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.85f, 0.89f, 0.92f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.85f, 0.89f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.85f, 0.89f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.85f, 0.89f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.19f, 0.43f, 0.63f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::NightSheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.87f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.85f, 0.87f, 0.92f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.14f, 0.19f, 0.36f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.85f, 0.87f, 0.92f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.19f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.19f, 0.49f, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.19f, 0.49f, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.19f, 0.49f, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.19f, 0.49f, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.19f, 0.36f, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.14f, 0.19f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.10f, 0.19f, 0.49f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.10f, 0.19f, 0.49f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.14f, 0.19f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.16f, 0.86f, 0.90f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.10f, 0.19f, 0.49f, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.07f, 0.26f, 0.53f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.19f, 0.49f, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.10f, 0.19f, 0.49f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.19f, 0.49f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 0.19f, 0.49f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.85f, 0.87f, 0.92f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.85f, 0.87f, 0.92f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.85f, 0.87f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.10f, 0.19f, 0.49f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.10f, 0.19f, 0.49f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.85f, 0.87f, 0.92f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.85f, 0.87f, 0.92f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.85f, 0.87f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.85f, 0.87f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.85f, 0.87f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.10f, 0.19f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.10f, 0.19f, 0.49f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::DunnoSheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.65f, 0.00f, 0.06f, 0.03f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.06f, 0.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.70f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.00f, 0.06f, 0.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 3.14f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 3.14f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.65f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.06f, 3.14f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.05f, 0.27f, 0.48f, 0.59f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.24f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.85f, 0.89f, 0.92f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.85f, 0.89f, 0.92f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.85f, 0.89f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.43f, 0.63f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.19f, 0.43f, 0.63f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.85f, 0.89f, 0.92f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.85f, 0.89f, 0.92f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.85f, 0.89f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.85f, 0.89f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.85f, 0.89f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.19f, 0.43f, 0.63f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.19f, 0.43f, 0.63f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::BlueSheme()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f); // - 
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.13f, 0.65f, 0.92f, 0.78f); // - 
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f); // - 
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.58f); // - 
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f); // - 
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f); // - 
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // - 
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f); // - 
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13f, 0.65f, 0.92f, 0.78f); // + 
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f); // - 
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f); // - 
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.47f); // - 
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f); // - 
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f); // - 
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.13f, 0.65f, 0.92f, 0.78f); // + 
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f); // - 
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.65f, 0.92f, 0.37f); // + 
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_Button] = ImVec4(0.13f, 0.65f, 0.92f, 0.75f); // + 
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.65f, 0.92f, 0.86f); // + 
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_Header] = ImVec4(0.13f, 0.65f, 0.92f, 0.76f); // + 
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.65f, 0.92f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_Column] = ImVec4(0.15f, 0.00f, 0.00f, 0.35f); // - 
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.13f, 0.65f, 0.92f, 0.59f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.65f, 0.92f, 0.63f); // + 
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.65f, 0.92f, 0.78f); // + 
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f); // - 
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f); // - 
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.78f); // - 
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.13f, 0.65f, 0.92f, 1.00f); // + 
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.13f, 0.65f, 0.92f, 0.43f); // + 
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f); // - 
}

void CGui::MidNight2()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.39f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::BlackSheme2()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.11f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.02f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.12f, 0.11f, 0.21f, 0.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.12f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05f, 0.02f, 0.05f, 0.98f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.02f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.12f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.18f, 0.18f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.12f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.11f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.12f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.18f, 0.18f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.09f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.12f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.18f, 0.18f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.12f, 0.11f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.18f, 0.18f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.18f, 0.18f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.02f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
}

void CGui::green()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.89f, 0.92f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.89f, 0.92f, 0.85f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.17f, 0.20f, 0.14f, 0.55f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.37f, 0.49f, 0.20f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.89f, 0.92f, 0.85f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.37f, 0.49f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.53f, 0.78f, 0.17f, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.53f, 0.78f, 0.17f, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.53f, 0.78f, 0.17f, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.53f, 0.78f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.37f, 0.49f, 0.20f, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.37f, 0.49f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.53f, 0.78f, 0.17f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.53f, 0.78f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.37f, 0.49f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.53f, 0.78f, 0.17f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.53f, 0.78f, 0.17f, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.53f, 0.78f, 0.17f, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.53f, 0.78f, 0.17f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.53f, 0.78f, 0.17f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.53f, 0.78f, 0.17f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.89f, 0.92f, 0.85f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.89f, 0.92f, 0.85f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.89f, 0.92f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.53f, 0.78f, 0.17f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.53f, 0.78f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.89f, 0.92f, 0.85f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.89f, 0.92f, 0.85f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.89f, 0.92f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.89f, 0.92f, 0.85f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.89f, 0.92f, 0.85f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.53f, 0.78f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.53f, 0.78f, 0.17f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

}

void CGui::pink()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.92f, 0.92f, 0.85f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.19f, 0.14f, 0.55f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.49f, 0.47f, 0.20f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.92f, 0.92f, 0.85f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.49f, 0.47f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.78f, 0.75f, 0.17f, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.78f, 0.75f, 0.17f, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.78f, 0.75f, 0.17f, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.75f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.49f, 0.47f, 0.20f, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.49f, 0.47f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.78f, 0.75f, 0.17f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.78f, 0.75f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.49f, 0.47f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.75f, 0.17f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.78f, 0.75f, 0.17f, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.78f, 0.75f, 0.17f, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.78f, 0.75f, 0.17f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.78f, 0.75f, 0.17f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.78f, 0.75f, 0.17f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.92f, 0.92f, 0.85f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.92f, 0.92f, 0.85f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.92f, 0.92f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.78f, 0.75f, 0.17f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.78f, 0.75f, 0.17f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.92f, 0.92f, 0.85f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.92f, 0.92f, 0.85f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.92f, 0.92f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.92f, 0.92f, 0.85f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.92f, 0.92f, 0.85f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.78f, 0.75f, 0.17f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.78f, 0.75f, 0.17f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}
void CGui::blue()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.87f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.85f, 0.87f, 0.92f, 0.58f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.15f, 0.20f, 0.55f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.27f, 0.49f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.85f, 0.87f, 0.92f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.27f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.17f, 0.31f, 0.78f, 0.68f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.17f, 0.31f, 0.78f, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.31f, 0.78f, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.17f, 0.31f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.27f, 0.49f, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.27f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.17f, 0.31f, 0.78f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.17f, 0.31f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.27f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.17f, 0.31f, 0.78f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.17f, 0.31f, 0.78f, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.17f, 0.31f, 0.78f, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.17f, 0.31f, 0.78f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.17f, 0.31f, 0.78f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.17f, 0.31f, 0.78f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.85f, 0.87f, 0.92f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.85f, 0.87f, 0.92f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.85f, 0.87f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.17f, 0.31f, 0.78f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.17f, 0.31f, 0.78f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.85f, 0.87f, 0.92f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.85f, 0.87f, 0.92f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.85f, 0.87f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.85f, 0.87f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.85f, 0.87f, 0.92f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.17f, 0.31f, 0.78f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.17f, 0.31f, 0.78f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

}

void CGui::yellow()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.51f, 0.51f, 0.51f, 0.55f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.35f, 0.33f, 0.33f, 0.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.86f, 0.86f, 0.86f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.35f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.82f, 0.82f, 0.82f, 0.92f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(1.02f, 0.94f, 0.94f, 0.45f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.02f, 0.94f, 0.94f, 0.35f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(1.02f, 0.94f, 0.94f, 0.78f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.33f, 0.33f, 0.57f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.02f, 0.94f, 0.94f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.02f, 0.94f, 0.94f, 0.78f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.35f, 0.33f, 0.33f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.02f, 0.94f, 0.94f, 0.80f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.02f, 0.94f, 0.94f, 0.24f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.02f, 0.94f, 0.94f, 0.44f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.02f, 0.94f, 0.94f, 0.86f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(1.02f, 0.94f, 0.94f, 0.76f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.02f, 0.94f, 0.94f, 0.86f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.92f, 0.85f, 0.85f, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.92f, 0.85f, 0.85f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.92f, 0.85f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.02f, 0.94f, 0.94f, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.02f, 0.94f, 0.94f, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.92f, 0.85f, 0.85f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.92f, 0.85f, 0.85f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.92f, 0.85f, 0.85f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.92f, 0.85f, 0.85f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.02f, 0.94f, 0.94f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.02f, 0.94f, 0.94f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}


void CGui::BlackSheme()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.25f, 0.90f, 0.83f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.25f, 0.90f, 0.20f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.25f, 0.90f, 0.87f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.40f, 0.40f, 0.55f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.80f, 0.30f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 0.40f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Button] = style.Colors[ImGuiCol_WindowBg];
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.46f, 0.65f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.25f, 0.90f, 0.83f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.40f, 0.40f, 0.90f, 0.45f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.50f, 0.50f, 0.90f, 0.50f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.70f, 0.70f, 0.90f, 0.60f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}



namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	IMGUI_API bool ComboBoxArray(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	IMGUI_API bool TabLabels(const char **tabLabels, int tabSize, int &tabIndex, int *tabOrder)
	{
		ImGuiStyle& style = ImGui::GetStyle();

		const ImVec2 itemSpacing = style.ItemSpacing;
		const ImVec4 color = style.Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		const ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		const ImVec4 colorText = style.Colors[ImGuiCol_Text];
		style.ItemSpacing.x = 2.5;
		style.ItemSpacing.y = 1;
		const ImVec4 colorSelectedTab = ImVec4(color.x, color.y, color.z, color.w*0.5f);
		const ImVec4 colorSelectedTabHovered = ImVec4(colorHover.x, colorHover.y, colorHover.z, colorHover.w*0.5f);
		const ImVec4 colorSelectedTabText = ImVec4(colorText.x*0.8f, colorText.y*0.8f, colorText.z*0.8f, colorText.w*0.8f);

		if (tabSize>0 && (tabIndex<0 || tabIndex >= tabSize))
		{
			if (!tabOrder)
			{
				tabIndex = 0;
			}
			else
			{
				tabIndex = -1;
			}
		}

		float windowWidth = 0.f, sumX = 0.f;
		windowWidth = ImGui::GetWindowWidth() - style.WindowPadding.x - (ImGui::GetScrollMaxY()>0 ? style.ScrollbarSize : 0.f);

		static int draggingTabIndex = -1; int draggingTabTargetIndex = -1;
		static ImVec2 draggingtabSize(0, 0);
		static ImVec2 draggingTabOffset(0, 0);

		const bool isMMBreleased = ImGui::IsMouseReleased(2);
		const bool isMouseDragging = ImGui::IsMouseDragging(0, 2.f);
		int justClosedTabIndex = -1, newtabIndex = tabIndex;

		bool selection_changed = false; bool noButtonDrawn = true;

		for (int j = 0, i; j < tabSize; j++)
		{
			i = tabOrder ? tabOrder[j] : j;
			if (i == -1) continue;

			if (sumX > 0.f)
			{
				sumX += style.ItemSpacing.x;
				sumX += ImGui::CalcTextSize(tabLabels[i]).x + 2.f*style.FramePadding.x;

				if (sumX>windowWidth)
				{
					sumX = 0.f;
				}
			}

			if (i != tabIndex)
			{
				// Push the style
				style.Colors[ImGuiCol_Button] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonActive] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonHovered] = colorSelectedTabHovered;
				style.Colors[ImGuiCol_Text] = colorSelectedTabText;
			}
			// Draw the button
			ImGui::PushID(i);   // otherwise two tabs with the same name would clash.
			if (ImGui::Button(tabLabels[i], ImVec2(100.f, 100.f))) { selection_changed = (tabIndex != i); newtabIndex = i; } // Tab Size
			ImGui::PopID();
			if (i != tabIndex)
			{
				// Reset the style
				style.Colors[ImGuiCol_Button] = color;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				style.Colors[ImGuiCol_Text] = colorText;
			}
			noButtonDrawn = false;

			if (sumX == 0.f) sumX = style.WindowPadding.x + ImGui::GetItemRectSize().x; // First element of a line

			if (ImGui::IsItemHoveredRect())
			{
				if (tabOrder)
				{
					// tab reordering
					if (isMouseDragging)
					{
						if (draggingTabIndex == -1)
						{
							draggingTabIndex = j;
							draggingtabSize = ImGui::GetItemRectSize();
							const ImVec2& mp = ImGui::GetIO().MousePos;
							const ImVec2 draggingTabCursorPos = ImGui::GetCursorPos();
							draggingTabOffset = ImVec2(
								mp.x + draggingtabSize.x*0.5f - sumX + ImGui::GetScrollX(),
								mp.y + draggingtabSize.y*0.5f - draggingTabCursorPos.y + ImGui::GetScrollY()
							);

						}
					}
					else if (draggingTabIndex >= 0 && draggingTabIndex<tabSize && draggingTabIndex != j)
					{
						draggingTabTargetIndex = j;
					}
				}
			}
		}

		tabIndex = newtabIndex;


		// Draw tab label while mouse drags it
		if (draggingTabIndex >= 0 && draggingTabIndex<tabSize)
		{
			const ImVec2& mp = ImGui::GetIO().MousePos;
			const ImVec2 wp = ImGui::GetWindowPos();
			ImVec2 start(wp.x + mp.x - draggingTabOffset.x - draggingtabSize.x*0.5f, wp.y + mp.y - draggingTabOffset.y - draggingtabSize.y*0.5f);
			const ImVec2 end(start.x + draggingtabSize.x, start.y + draggingtabSize.y);
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			const float draggedBtnAlpha = 0.65f;
			const ImVec4& btnColor = style.Colors[ImGuiCol_Button];
			drawList->AddRectFilled(start, end, ImColor(btnColor.x, btnColor.y, btnColor.z, btnColor.w*draggedBtnAlpha), style.FrameRounding);
			start.x += style.FramePadding.x; start.y += style.FramePadding.y;
			const ImVec4& txtColor = style.Colors[ImGuiCol_Text];
			drawList->AddText(start, ImColor(txtColor.x, txtColor.y, txtColor.z, txtColor.w*draggedBtnAlpha), tabLabels[tabOrder[draggingTabIndex]]);

			ImGui::SetMouseCursor(ImGuiMouseCursor_Move);
		}

		// Drop tab label
		if (draggingTabTargetIndex != -1)
		{
			// swap draggingTabIndex and draggingTabTargetIndex in tabOrder
			const int tmp = tabOrder[draggingTabTargetIndex];
			tabOrder[draggingTabTargetIndex] = tabOrder[draggingTabIndex];
			tabOrder[draggingTabIndex] = tmp;
			//fprintf(stderr,"%d %d\n",draggingTabIndex,draggingTabTargetIndex);
			draggingTabTargetIndex = draggingTabIndex = -1;
		}

		// Reset draggingTabIndex if necessary
		if (!isMouseDragging) draggingTabIndex = -1;

		// Change selected tab when user closes the selected tab
		if (tabIndex == justClosedTabIndex && tabIndex >= 0)
		{
			tabIndex = -1;
			for (int j = 0, i; j < tabSize; j++)
			{
				i = tabOrder ? tabOrder[j] : j;
				if (i == -1)
				{
					continue;
				}
				tabIndex = i;
				break;
			}
		}

		// Restore the style
		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.Colors[ImGuiCol_Text] = colorText;
		style.ItemSpacing = itemSpacing;

		return selection_changed;
	}
}

void CGui::TabIcons()
{
	ImGui::PushFont(Tabfont);
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(3.5, 3.5);
	style.FrameRounding = 20.0f;
	style.ItemSpacing = ImVec2(5, 5);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 20.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 20.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(0, 0, 0, 255);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.60f, 0.60f, 0.60f, 0.60f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 1.00f, 1.00f, 0.75f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 1.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.63f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
}

void CGui::TabColors()
{
	ImGui::PushFont(font);
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(3.5, 3.5);
	style.FrameRounding = 5.0f;
	style.ItemSpacing = ImVec2(5, 5);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 5.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 5.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(0, 0, 0, 255);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.60f, 0.60f, 0.60f, 0.60f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 1.00f, 1.00f, 0.75f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 1.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.63f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
}

void CGui::bluefont()
{
	ImGui::PushFont(font);
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(3.5, 3.5);
	style.FrameRounding = 5.0f;
	style.ItemSpacing = ImVec2(5, 5);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 5.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 5.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.55f, 0.17f, 0.17f, 1.07f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.00f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.60f, 0.60f, 0.60f, 0.60f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 1.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.63f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.22745098039f, 0.39607843137f, 0.94117647058f, 1.00f);

}

void CGui::IconFont()
{
	ImGui::PushFont(Iconfont);
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(3.5, 3.5);
	style.FrameRounding = 10.0f;
	style.ItemSpacing = ImVec2(5, 5);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 10.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 10.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);



	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.35f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 1.00f, 1.00f, 0.75f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 1.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.63f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);

}

void CGui::NameFont()
{
	ImGui::PushFont(Namefont);
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(3.5, 3.5);
	style.FrameRounding = 10.0f;
	style.ItemSpacing = ImVec2(5, 5);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 5.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 5.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.60f, 0.60f, 0.60f, 0.60f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 1.00f, 1.00f, 0.78f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 1.00f, 1.00f, 0.75f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 1.00f, 0.76f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.00f, 1.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 1.00f, 1.00f, 0.63f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 0.63f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.92f, 0.18f, 0.29f, 0.43f);

}






































































































































































































































































































































































































































































































































































































































