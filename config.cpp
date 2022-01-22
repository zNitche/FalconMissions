class CfgPatches
{
	class FalconMissions
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"JM_CF_Scripts", "DZ_Data"};
	};
};

class CfgMods
{
	class FalconMissions
	{
	    dir = FalconMissions
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = FalconMissions
	    credits = "";
	    author = "";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = {"World", "Mission" };

		class defs
		{
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconMissions/Defines", "FalconMissions/5_Mission"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FalconMissions/Defines", "FalconMissions/4_World"};
			};
		};
	};
};

class CfgVehicles
{
	class Container_Base;
	class HiddenWoodenCase: Container_Base
	{
		scope=2;
		displayName="Hidden Wooden Case";
		descriptionShort="Hidden Wooden Case";
		model="\DZ\gear\camping\wooden_case.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,40};
		};
	};

	class AirDropCase: Container_Base
	{
		scope=2;
		displayName="AirDrop Case";
		descriptionShort="AirDrop Case";
		model="\DZ\gear\camping\wooden_case.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,40};
		};
	};

	class ConvoyCase: Container_Base
	{
		scope=2;
		displayName="Convoy Case";
		descriptionShort="Convoy Case";
		model="\DZ\gear\camping\wooden_case.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,40};
		};
	};

	class PlaneCrashCase: Container_Base
	{
		scope=2;
		displayName="PlaneCrash Case";
		descriptionShort="PlaneCrash Case";
		model="\DZ\gear\camping\wooden_case.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,40};
		};
	};

	class KOTHCase: Container_Base
	{
		scope=2;
		displayName="KOTH Case";
		descriptionShort="KOTH Case";
		model="\DZ\gear\camping\wooden_case.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,5};
		};
	};

	class AIMissionCase: Container_Base
	{
		scope=2;
		displayName="Mission Case";
		descriptionShort="Mission Case";
		model="\DZ\gear\camping\wooden_case.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,40};
		};
	};

	class BaseBuildingBase;
	class KOTHFlag: BaseBuildingBase
	{
		scope = 2;
		displayName = "KOTH Flag";
		descriptionShort = "KOTH Flag";
		model = "\DZ\gear\camping\territory_flag.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "false";
		lootCategory = "Crafted";
		carveNavmesh = 1;
		weight = 60000;
		itemSize[] = {6,6};
		physLayer = "item_large";
		createProxyPhysicsOnInit = "true";
		createdProxiesOnInit[] = {"Deployed"};
		rotationFlags = 2;
	};

	class HouseNoDestruct;
	class Land_Wreck_Ikarus_Mission: HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures\Wrecks\Vehicles\Wreck_Ikarus.p3d";
	};

	class Land_Wreck_Lada_Green_Mission: HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures\Wrecks\Vehicles\Wreck_Lada_Green.p3d";
	};

	class Land_Wreck_Uaz_Mission: HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures\Wrecks\Vehicles\Wreck_Uaz.p3d";
	};

	class C130Crash_Mission: HouseNoDestruct
	{
		scope = 1;
		model = "\DZ\structures\Wrecks\Aircraft\Wreck_C130J.p3d";
	};

	class SurvivorMale_Base;
	class FalconAITaiki: SurvivorMale_Base
	{
		scope = 2;
		emptyHead = "MaleTaikiHead";
		emptyBody = "MaleTaikiTorso";
		emptyLegs = "MaleTaikiLegs";
		emptyFeet = "MaleTaikiFeet";
		emptyGloves = "MaleTaikiHands";
		faceType = "MaleTaikiHead";
		decayedTexture = "\DZ\characters\heads\data\m_Taiki\hhl_m_Taiki_body_shaved_decayed_co.paa";
		class BloodyHands
		{
			mat_normal = "dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat";
			mat_blood = "dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bloodyhands.rvmat";
		};
		class Lifespan
		{
			class Beard
			{
				mat[] = {"dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_co.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_beard_ca.paa","dz\characters\heads\data\m_taiki\hhl_m_taiki_beard.rvmat"};
			};
		};
		class Wounds
		{
			tex[] = {};
			mat[] = {"dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_shaved_injury2.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_unshaved_injury2.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_injury.rvmat","dz\characters\heads\data\m_taiki\hhl_m_taiki_body_bearded_injury2.rvmat"};
		};
		voiceType = 2;
	};
};
