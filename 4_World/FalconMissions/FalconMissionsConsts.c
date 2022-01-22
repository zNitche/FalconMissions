class FalconMissionsConsts
{
	const static string MISSIONS_CONFIG_DATA_PATH = "$profile:/FValues/MissionsConfig.json";
	const static string AI_MISSIONS_CONFIG_DATA_PATH = "$profile:/FValues/AI_MissionsConfig.json";
	const static string AI_LOADOUTS_CONFIG_DATA_PATH = "$profile:/FValues/AILoadouts.json";
	const static string KOTH_MISSIONS_CONFIG_DATA_PATH = "$profile:/FValues/KOTHMissionsConfig.json";
	
	// Client
	const static string MISSIONS_PLACES_DATA_PATH = "$profile:/MissionsPlaces.json";
	//
	
	const static string MISSION_TYPE_HEROES = "Heroes";
	const static string MISSION_TYPE_BANDITS = "Bandits";
	
	const static int MISSION_LIFESPAN_AFTER_COMPLETED = 600;
	
	const static string AIRDROP_MISSION_MESSAGE = "Air Drop has been spotted at ";
	const static string CIVILIAN_CONVOY_MISSION_MESSAGE = "Civilian Convoy has been spotted at ";
	const static string MILITARY_CONVOY_MISSION_MESSAGE = "Military Convoy has been spotted at ";
	const static string PLANE_CRASH_MISSION_MESSAGE = "Plane Crash has been spotted at ";
	
	// KOTH
	const static float KOTH_CAPTURE_PER_UPDATE = 10;
	const static float KOTH_MAX_CAPTURE = 100;
	
	const static string KOTH_SPAWN_MISSION_MESSAGE = "KOTH site has been spotted at ";
	const static string KOTH_SPAWN_MISSION_CURRENT_CAPTURE_MESSAGE_START = "KOTH site ";
	const static string KOTH_SPAWN_MISSION_CURRENT_CAPTURE_MESSAGE_END = " progress ";
}