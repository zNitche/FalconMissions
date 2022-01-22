class MissionsManager
{
	ref MissionsHelpers missionsHelpers = new MissionsHelpers();
	
	ref MissionsConfig config;
	
	private bool spawnMissions;
	private int maxHiddenTreasuresMissions;
	private int maxAirDropMissions;
	private int maxCivilianConvoyMissions;
	private int maxMilitaryConvoyMissions;
	private int maxPlaneCrashMissions;
	
	private ref array<string> civilianLoot = new array<string>();
	private ref array<string> militaryLoot = new array<string>();
	
	// HiddenTreasures
	private ref array<string> hiddenTreasuresMissionsCords = new array<string>();
	private int hiddenTreasuresMissionsRadius;
	
	private ref array<ref HiddenTreasureMission> hiddenTreasuresMissions = new ref array<ref HiddenTreasureMission>();
	private ref Timer hiddenTreasuresMissionsSpawnerTimer = new Timer();
	private int hiddenTreasuresMissionsMinSpawnTime;
	private int hiddenTreasuresMissionsMaxSpawnTime;
	//
	// AirDrop
	private ref array<string> airDropMissionsCords = new array<string>();
	private int airDropMissionsRadius;
	
	private ref array<ref AirDropMission> airDropMissions = new ref array<ref AirDropMission>();
	private ref Timer airDropMissionsSpawnerTimer = new Timer();
	private int airDropMissionsMinSpawnTime;
	private int airDropMissionsMaxSpawnTime;
	//
	// CivilianConvoy
	private ref array<string> civilianConvoyMissionsCords = new array<string>();
	private int civilianConvoyMissionsRadius;
	
	private ref array<ref CivilianConvoyMission> civilianConvoyMissions = new ref array<ref CivilianConvoyMission>();
	private ref Timer civilianConvoyMissionsSpawnerTimer = new Timer();
	private int civilianConvoyMissionsMinSpawnTime;
	private int civilianConvoyMissionsMaxSpawnTime;
	//
	// MilitaryConvoy
	private ref array<string> militaryConvoyMissionsCords = new array<string>();
	private int militaryConvoyMissionsRadius;
	
	private ref array<ref MilitaryConvoyMission> militaryConvoyMissions = new ref array<ref MilitaryConvoyMission>();
	private ref Timer militaryConvoyMissionsSpawnerTimer = new Timer();
	private int militaryConvoyMissionsMinSpawnTime;
	private int militaryConvoyMissionsMaxSpawnTime;
	//
	// PlaneCrash
	private ref array<string> planeCrashMissionsCords;
	private int planeCrashMissionsRadius;
		
	private ref array<ref PlaneCrashMission> planeCrashMissions = new ref array<ref PlaneCrashMission>();
	private ref Timer planeCrashMissionsSpawnerTimer = new Timer();
	private int planeCrashMissionsMinSpawnTime;
	private int planeCrashMissionsMaxSpawnTime;
	//
	
	void loadConfig()
	{
		config = new MissionsConfig();
		config = MissionsUtils.loadMissionsConfig();
	}
	
	void setup()
	{
		spawnMissions = config.spawnMissions;
		
		maxHiddenTreasuresMissions = config.maxHiddenTreasuresMissions;
		maxAirDropMissions = config.maxAirDropMissions;
		maxCivilianConvoyMissions = config.maxCivilianConvoyMissions;
		maxMilitaryConvoyMissions = config.maxMilitaryConvoyMissions;
		maxPlaneCrashMissions = config.maxPlaneCrashMissions;
		
		civilianLoot = config.civilianLoot;
		militaryLoot = config.militaryLoot;
		
		// HiddenTreasure
		hiddenTreasuresMissionsCords = config.hiddenTreasuresMissionsCords;
		hiddenTreasuresMissionsRadius = config.hiddenTreasuresMissionsRadius;
		
		hiddenTreasuresMissionsMinSpawnTime = config.hiddenTreasuresMissionsMinSpawnTime;
		hiddenTreasuresMissionsMaxSpawnTime = config.hiddenTreasuresMissionsMaxSpawnTime;
		//
		// AirDrop
		airDropMissionsCords = config.airDropMissionsCords;
		airDropMissionsRadius = config.airDropMissionsRadius;
		
		airDropMissionsMinSpawnTime = config.airDropMissionsMinSpawnTime;
		airDropMissionsMaxSpawnTime = config.airDropMissionsMaxSpawnTime;
		//
		// CivilianConvoy
		civilianConvoyMissionsCords = config.civilianConvoyMissionsCords;
		civilianConvoyMissionsRadius = config.civilianConvoyMissionsRadius;
		
		civilianConvoyMissionsMinSpawnTime = config.civilianConvoyMissionsMinSpawnTime;
		civilianConvoyMissionsMaxSpawnTime = config.civilianConvoyMissionsMaxSpawnTime;
		//
		// MilitaryConvoy
		militaryConvoyMissionsCords = config.militaryConvoyMissionsCords;
		militaryConvoyMissionsRadius = config.militaryConvoyMissionsRadius;
		
		militaryConvoyMissionsMinSpawnTime = config.militaryConvoyMissionsMinSpawnTime;
		militaryConvoyMissionsMaxSpawnTime = config.militaryConvoyMissionsMaxSpawnTime;
		//
		// Plane Crash
		planeCrashMissionsCords = config.planeCrashMissionsCords;
		planeCrashMissionsRadius = config.planeCrashMissionsRadius;
		
		planeCrashMissionsMinSpawnTime = config.planeCrashMissionsMinSpawnTime;
		planeCrashMissionsMaxSpawnTime = config.planeCrashMissionsMaxSpawnTime;
		//
	}
	
	void checkMissionsCount()
	{		
		if (spawnMissions)
		{
			spawnHiddenTreasuresMission();
			spawnAirDropMission();
			spawnCivilianConvoy();
			spawnMilitaryConvoy();
			spawnPlaneCrash();
		}
	}
	
	void spawnTimeout()
	{
		airDropMissionsSpawnerTimer.Run(Math.RandomInt(airDropMissionsMinSpawnTime, airDropMissionsMaxSpawnTime), null, "");
		hiddenTreasuresMissionsSpawnerTimer.Run(Math.RandomInt(hiddenTreasuresMissionsMinSpawnTime, hiddenTreasuresMissionsMaxSpawnTime), null, "");
		civilianConvoyMissionsSpawnerTimer.Run(Math.RandomInt(civilianConvoyMissionsMinSpawnTime, civilianConvoyMissionsMaxSpawnTime), null, "");
		militaryConvoyMissionsSpawnerTimer.Run(Math.RandomInt(militaryConvoyMissionsMinSpawnTime, militaryConvoyMissionsMaxSpawnTime), null, "");
		planeCrashMissionsSpawnerTimer.Run(Math.RandomInt(planeCrashMissionsMinSpawnTime, planeCrashMissionsMaxSpawnTime), null, "");
	}
	
	void spawnAirDropMission()
	{
		if (!airDropMissionsSpawnerTimer.IsRunning())
		{
			if (airDropMissions.Count() < maxAirDropMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < airDropMissions.Count(); i++)
				{
					runningMissionsInds.Insert(airDropMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(airDropMissionsCords, runningMissionsInds);
				
				vector pos = airDropMissionsCords.Get(randIndex).ToVector();
				
				AirDropMission mission = new AirDropMission(randIndex, pos, airDropMissionsRadius);
				
				mission.setLootItemNames(getMissionRewardLoot(militaryLoot, mission.getMaxMissionItems()));
				mission.init();
				
				airDropMissions.Insert(mission);
				
				airDropMissionsSpawnerTimer.Run(Math.RandomInt(airDropMissionsMinSpawnTime, airDropMissionsMaxSpawnTime), null, "");
				
				missionsHelpers.messagePlayers(FalconMissionsConsts.AIRDROP_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
			}
		}
	}
	
	void spawnHiddenTreasuresMission()
	{
		if (!hiddenTreasuresMissionsSpawnerTimer.IsRunning())
		{
			if (hiddenTreasuresMissions.Count() < maxHiddenTreasuresMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < hiddenTreasuresMissions.Count(); i++)
				{
					runningMissionsInds.Insert(hiddenTreasuresMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(hiddenTreasuresMissionsCords, runningMissionsInds);
				
				vector pos = hiddenTreasuresMissionsCords.Get(randIndex).ToVector();
				
				HiddenTreasureMission mission = new HiddenTreasureMission(randIndex, pos, hiddenTreasuresMissionsRadius);
				
				mission.setLootItemNames(getMissionRewardLoot(civilianLoot, mission.getMaxMissionItems()));
				mission.init();
				
				hiddenTreasuresMissions.Insert(mission);
				
				hiddenTreasuresMissionsSpawnerTimer.Run(Math.RandomInt(hiddenTreasuresMissionsMinSpawnTime, hiddenTreasuresMissionsMaxSpawnTime), null, "");
			}
		}
	}
	
	void spawnCivilianConvoy()
	{
		if (!civilianConvoyMissionsSpawnerTimer.IsRunning())
		{
			if (civilianConvoyMissions.Count() < maxCivilianConvoyMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < civilianConvoyMissions.Count(); i++)
				{
					runningMissionsInds.Insert(civilianConvoyMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(civilianConvoyMissionsCords, runningMissionsInds);
				
				vector pos = civilianConvoyMissionsCords.Get(randIndex).ToVector();
				
				CivilianConvoyMission mission = new CivilianConvoyMission(randIndex, pos, civilianConvoyMissionsRadius);
				
				mission.setLootItemNames(getMissionRewardLoot(civilianLoot, mission.getMaxMissionItems()));
				mission.init();
				
				civilianConvoyMissions.Insert(mission);
				
				civilianConvoyMissionsSpawnerTimer.Run(Math.RandomInt(civilianConvoyMissionsMinSpawnTime, civilianConvoyMissionsMaxSpawnTime), null, "");
				
				missionsHelpers.messagePlayers(FalconMissionsConsts.CIVILIAN_CONVOY_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
			}
		}
	}
	
	void spawnMilitaryConvoy()
	{
		if (!militaryConvoyMissionsSpawnerTimer.IsRunning())
		{
			if (militaryConvoyMissions.Count() < maxMilitaryConvoyMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < militaryConvoyMissions.Count(); i++)
				{
					runningMissionsInds.Insert(militaryConvoyMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(militaryConvoyMissionsCords, runningMissionsInds);
				
				vector pos = militaryConvoyMissionsCords.Get(randIndex).ToVector();
				
				MilitaryConvoyMission mission = new MilitaryConvoyMission(randIndex, pos, militaryConvoyMissionsRadius);
				
				mission.setLootItemNames(getMissionRewardLoot(militaryLoot, mission.getMaxMissionItems()));
				mission.init();
				
				militaryConvoyMissions.Insert(mission);
				
				militaryConvoyMissionsSpawnerTimer.Run(Math.RandomInt(militaryConvoyMissionsMinSpawnTime, militaryConvoyMissionsMaxSpawnTime), null, "");
				
				missionsHelpers.messagePlayers(FalconMissionsConsts.MILITARY_CONVOY_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
			}
		}
	}
	
	void spawnPlaneCrash()
	{
		if (!planeCrashMissionsSpawnerTimer.IsRunning())
		{
			if (planeCrashMissions.Count() < maxPlaneCrashMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < planeCrashMissions.Count(); i++)
				{
					runningMissionsInds.Insert(planeCrashMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(planeCrashMissionsCords, runningMissionsInds);
				
				vector pos = planeCrashMissionsCords.Get(randIndex).ToVector();
				
				PlaneCrashMission mission = new PlaneCrashMission(randIndex, pos, planeCrashMissionsRadius);
				
				mission.setLootItemNames(getMissionRewardLoot(militaryLoot, mission.getMaxMissionItems()));
				mission.init();
				
				planeCrashMissions.Insert(mission);
				
				planeCrashMissionsSpawnerTimer.Run(Math.RandomInt(planeCrashMissionsMinSpawnTime, planeCrashMissionsMaxSpawnTime), null, "");
				
				missionsHelpers.messagePlayers(FalconMissionsConsts.PLANE_CRASH_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
			}
		}
	}
	
	void updateMissions()
	{
		for (int i = 0; i < hiddenTreasuresMissions.Count(); i++)
		{
			hiddenTreasuresMissions[i].update();
			
			if (!hiddenTreasuresMissions[i].checkLifespan())
			{
				hiddenTreasuresMissions.Remove(i);
			}
		}
		
		for (int j = 0; j < airDropMissions.Count(); j++)
		{
			airDropMissions[j].update();
			
			if (!airDropMissions[j].checkLifespan())
			{
				airDropMissions.Remove(j);
			}
		}
		
		for (int k = 0; k < civilianConvoyMissions.Count(); k++)
		{
			civilianConvoyMissions[k].update();
			
			if (!civilianConvoyMissions[k].checkLifespan())
			{
				civilianConvoyMissions.Remove(k);
			}
		}
		
		for (int g = 0; g < militaryConvoyMissions.Count(); g++)
		{
			militaryConvoyMissions[g].update();
			
			if (!militaryConvoyMissions[g].checkLifespan())
			{
				militaryConvoyMissions.Remove(g);
			}
		}
		
		for (int u = 0; u < planeCrashMissions.Count(); u++)
		{
			planeCrashMissions[u].update();
			
			if (!planeCrashMissions[u].checkLifespan())
			{
				planeCrashMissions.Remove(u);
			}
		}
	}
	
	array<string> getMissionRewardLoot(array<string> missionLoot, int missionMaxItems)
	{
		array<string> itemsNames = new array<string>();
		
		int itemsCount = Math.RandomInt(1, missionMaxItems);
		
		for (int i = 0; i < itemsCount; i++)
		{
			itemsNames.Insert(missionLoot.GetRandomElement());
		}
		
		return itemsNames;
	}
	
	
	//Debug
	void getMissionsDetails()
	{
		for (int i = 0; i < hiddenTreasuresMissions.Count(); i++)
		{
			Print("HiddenTreasure " + hiddenTreasuresMissions[i].getMissionCenter().ToString() + "ID: " + hiddenTreasuresMissions[i].missionId);
		}
		
		for (int j = 0; j < airDropMissions.Count(); j++)
		{
			Print("AirDrop " + airDropMissions[j].getMissionCenter().ToString() + "ID: " + airDropMissions[j].missionId);
		}
		
		for (int k = 0; k < civilianConvoyMissions.Count(); k++)
		{
			Print("CivilianConvoy " + civilianConvoyMissions[k].getMissionCenter().ToString() + "ID: " + civilianConvoyMissions[k].missionId);
		}
		
		for (int g = 0; g < militaryConvoyMissions.Count(); g++)
		{
			Print("MilitaryConvoy " + militaryConvoyMissions[g].getMissionCenter().ToString() + "ID: " + militaryConvoyMissions[g].missionId);
		}
		
		for (int u = 0; u < planeCrashMissions.Count(); u++)
		{
			Print("PlaneCrash " + planeCrashMissions[u].getMissionCenter().ToString() + "ID: " + planeCrashMissions[u].missionId);
		}
	}
	
	void clearMissionsDebug()
	{
		for (int i = 0; i < hiddenTreasuresMissions.Count(); i++)
		{
			hiddenTreasuresMissions[i].deleteMissionObjects();
		}
		
		hiddenTreasuresMissions.Clear();
		
		for (int j = 0; j < airDropMissions.Count(); j++)
		{
			airDropMissions[j].deleteMissionObjects();
		}
		
		airDropMissions.Clear();
		
		for (int k = 0; k < civilianConvoyMissions.Count(); k++)
		{
			civilianConvoyMissions[k].deleteMissionObjects();
		}
		
		civilianConvoyMissions.Clear();
		
		for (int g = 0; g < militaryConvoyMissions.Count(); g++)
		{
			militaryConvoyMissions[g].deleteMissionObjects();
		}
		
		militaryConvoyMissions.Clear();
		
		for (int u = 0; u < planeCrashMissions.Count(); u++)
		{
			planeCrashMissions[u].deleteMissionObjects();
		}
		
		planeCrashMissions.Clear();
	}
	
	void spawnHiddenTreasuresMissionDebug()
	{
		vector pos = hiddenTreasuresMissionsCords.GetRandomElement().ToVector();
		HiddenTreasureMission mission = new HiddenTreasureMission(-1, pos, hiddenTreasuresMissionsRadius);
		
		mission.setLootItemNames(getMissionRewardLoot(civilianLoot, mission.getMaxMissionItems()));
		mission.init();
		
		hiddenTreasuresMissions.Insert(mission);
	}
	
	void spawnAirDropMissionDebug()
	{
		vector pos = airDropMissionsCords.GetRandomElement().ToVector();
		AirDropMission mission = new AirDropMission(-1, pos, airDropMissionsRadius);
		
		mission.setLootItemNames(getMissionRewardLoot(militaryLoot, mission.getMaxMissionItems()));
		mission.init();
		
		airDropMissions.Insert(mission);
		
		missionsHelpers.messagePlayers(FalconMissionsConsts.AIRDROP_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
	}
	
	void spawnCivilianConvoyMissionsDebug()
	{
		vector pos = civilianConvoyMissionsCords.GetRandomElement().ToVector();
		CivilianConvoyMission mission = new CivilianConvoyMission(-1, pos, civilianConvoyMissionsRadius);
		
		mission.setLootItemNames(getMissionRewardLoot(civilianLoot, mission.getMaxMissionItems()));
		mission.init();
		
		civilianConvoyMissions.Insert(mission);
		
		missionsHelpers.messagePlayers(FalconMissionsConsts.CIVILIAN_CONVOY_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
	}
	
	void spawnMilitaryConvoyMissionsDebug()
	{
		vector pos = militaryConvoyMissionsCords.GetRandomElement().ToVector();
		MilitaryConvoyMission mission = new MilitaryConvoyMission(-1, pos, militaryConvoyMissionsRadius);
		
		mission.setLootItemNames(getMissionRewardLoot(militaryLoot, mission.getMaxMissionItems()));
		mission.init();
		
		militaryConvoyMissions.Insert(mission);
		
		missionsHelpers.messagePlayers(FalconMissionsConsts.MILITARY_CONVOY_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
	}
	
	void spawnPlaneCrashMissionDebug()
	{
		vector pos = planeCrashMissionsCords.GetRandomElement().ToVector();
		PlaneCrashMission mission = new PlaneCrashMission(-1, pos, planeCrashMissionsRadius);
		
		mission.setLootItemNames(getMissionRewardLoot(militaryLoot, mission.getMaxMissionItems()));
		mission.init();
		
		planeCrashMissions.Insert(mission);
		
		planeCrashMissionsSpawnerTimer.Run(Math.RandomInt(planeCrashMissionsMinSpawnTime, planeCrashMissionsMaxSpawnTime), null, "");
		
		missionsHelpers.messagePlayers(FalconMissionsConsts.PLANE_CRASH_MISSION_MESSAGE + " " + pos[0] + " " + pos[2]);
	}
}
