class AirDropMission extends FM_MissionBase
{
	ref array<string> zombiesTypes = new ref array<string>();
	
	void AirDropMission(int missionId, vector missionCenter, int missionRadius)
	{
		this.missionId = missionId;
		this.missionCenter = missionCenter;
		this.lootItemNames = lootItemNames;
		
		this.missionCenter = generateRandomPosition(missionRadius);
		
		this.missionRadius = 20;
		
		lootItemContainerName = "AirDropCase";
		missionName = "Air Drop";
		missionLifespan = 3600;
		maxMissionItems = 5;
		
		zombiesTypes.Insert("ZmbM_SoldierNormal");
	}
	
	override void init()
	{
		spawnMission();
		spawnMissionLoot();
		
		initFlaresInZone(5);
		spawnRandomizedMissionObjects(zombiesTypes, 10, 15);
	}
}