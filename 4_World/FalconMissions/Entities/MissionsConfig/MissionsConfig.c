class MissionsConfig
{
	bool spawnMissions;

	int maxHiddenTreasuresMissions;
	int maxAirDropMissions;
	int maxCivilianConvoyMissions;
	int maxMilitaryConvoyMissions;
	int maxPlaneCrashMissions;

	ref array<string> civilianLoot = new array<string>();
	ref array<string> militaryLoot = new array<string>();
	
	ref array<string> hiddenTreasuresMissionsCords = new array<string>();
	int hiddenTreasuresMissionsRadius;
	int hiddenTreasuresMissionsMinSpawnTime;
	int hiddenTreasuresMissionsMaxSpawnTime;
	
	ref array<string> airDropMissionsCords = new array<string>();
	int airDropMissionsRadius;
	int airDropMissionsMinSpawnTime;
	int airDropMissionsMaxSpawnTime;
	
	ref array<string> civilianConvoyMissionsCords = new array<string>();
	int civilianConvoyMissionsRadius;
	int civilianConvoyMissionsMinSpawnTime;
	int civilianConvoyMissionsMaxSpawnTime;
	
	ref array<string> militaryConvoyMissionsCords = new array<string>();
	int militaryConvoyMissionsRadius;
	int militaryConvoyMissionsMinSpawnTime;
	int militaryConvoyMissionsMaxSpawnTime;
	
	ref array<string> planeCrashMissionsCords = new array<string>();
	int planeCrashMissionsRadius;
	int planeCrashMissionsMinSpawnTime;
	int planeCrashMissionsMaxSpawnTime;
}