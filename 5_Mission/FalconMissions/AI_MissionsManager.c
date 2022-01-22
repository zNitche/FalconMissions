class AI_MissionsManager
{
	ref AI_MissionsConfig config;
	
	private bool spawnMissions;
	
	private ref array<ref RogueFarmersMission> rogueFarmersMissions = new ref array<ref RogueFarmersMission>();
	private ref Timer rogueFarmersMissionsSpawnerTimer = new Timer();
	private int maxRogueFarmersMissions;
	private ref array<string> rogueFarmersMissionsCords = new array<string>();
	private int rogueFarmersMissionsRadius;
	private int rogueFarmersMissionsMinSpawnTime;
	private int rogueFarmersMissionsMaxSpawnTime;
	
	
	void loadConfig()
	{
		config = new AI_MissionsConfig();
		config = MissionsUtils.loadAIMissionsConfig();
	}
	
	void setup()
	{
		spawnMissions = config.spawnMissions;
		maxRogueFarmersMissions = config.maxRogueFarmersMissions;
		rogueFarmersMissionsCords = config.rogueFarmersMissionsCords;
		rogueFarmersMissionsRadius = config.rogueFarmersMissionsRadius;
		rogueFarmersMissionsMinSpawnTime = config.rogueFarmersMissionsMinSpawnTime;
		rogueFarmersMissionsMaxSpawnTime = config.rogueFarmersMissionsMaxSpawnTime;
	}
	
	void checkMissionsCount()
	{	
		if (spawnMissions)
		{
			spawnRogueFarmersMissions();
		}
	}
	
	void spawnTimeout()
	{
		rogueFarmersMissionsSpawnerTimer.Run(Math.RandomInt(rogueFarmersMissionsMinSpawnTime, rogueFarmersMissionsMaxSpawnTime), null, "");
	}
	
	void spawnRogueFarmersMissions()
	{
		if (!rogueFarmersMissionsSpawnerTimer.IsRunning())
		{
			if (rogueFarmersMissions.Count() < maxRogueFarmersMissions)
			{
				array<int> runningMissionsInds = new array<int>();
				
				for (int i = 0; i < rogueFarmersMissions.Count(); i++)
				{
					runningMissionsInds.Insert(rogueFarmersMissions[i].missionId);
				}
				
				int randIndex = MissionsUtils.getEmptyMissionCordsIndex(rogueFarmersMissionsCords, runningMissionsInds);
				vector pos = rogueFarmersMissionsCords.Get(randIndex).ToVector();

				RogueFarmersMission mission = new RogueFarmersMission(0, pos, rogueFarmersMissionsRadius);
				
				mission.init();
				
				rogueFarmersMissions.Insert(mission);
				
				rogueFarmersMissionsSpawnerTimer.Run(Math.RandomInt(rogueFarmersMissionsMinSpawnTime, rogueFarmersMissionsMaxSpawnTime), null, "");
			}
		}
	}
	
	void updateMissions()
	{
		for (int i = 0; i < rogueFarmersMissions.Count(); i++)
		{
			rogueFarmersMissions[i].update();
			
			if (!rogueFarmersMissions[i].checkLifespan())
			{
				rogueFarmersMissions.Remove(i);
			}
		}
	}
	
	array<ref MissionPlace> getMissionsDetails()
	{
		array<ref MissionPlace> missionsDetails = new array<ref MissionPlace>();
		
		for (int i = 0; i < rogueFarmersMissions.Count(); i++)
		{
			missionsDetails.Insert(rogueFarmersMissions[i].getMissionPlace());
		}
		
		return missionsDetails;
	}
	
	
	// Debug
	void spawnRogueFarmersMissionsDebug()
	{
		vector pos = rogueFarmersMissionsCords.GetRandomElement().ToVector();

		RogueFarmersMission mission = new RogueFarmersMission(-1, pos, rogueFarmersMissionsRadius);
		
		mission.init();
		
		rogueFarmersMissions.Insert(mission);
	}
	
	void clearMissionsDebug()
	{
		for (int i = 0; i < rogueFarmersMissions.Count(); i++)
		{
			rogueFarmersMissions[i].clearMission();
			
			rogueFarmersMissions.Remove(i);
		}
	}
	//
}
