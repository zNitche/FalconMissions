class MilitaryConvoyMission extends FM_MissionBase
{
	ref array<string> zombiesTypes = new ref array<string>();	
	ref array<string> wrecksTypes = new ref array<string>();	
	
	void MilitaryConvoyMission(int missionId, vector missionCenter, int missionRadius)
	{
		this.missionId = missionId;
		this.missionCenter = missionCenter;
		this.lootItemNames = lootItemNames;
		
		this.missionCenter = generateRandomPosition(missionRadius);
		
		this.missionRadius = 5;
		
		lootItemContainerName = "ConvoyCase";
		missionName = "Destroyed Military Convoy";
		missionLifespan = 3600;
		maxMissionItems = 5;
		
		wrecksTypes.Insert("Land_Wreck_Uaz_Mission");
		
		zombiesTypes.Insert("ZmbM_SoldierNormal");
	}
	
	override void init()
	{
		spawnMission();
		spawnMissionLoot();
		
		spawnRandomizedMissionObjects(zombiesTypes, 15, 25);
		spawnRandomizedMissionObjects(wrecksTypes, 5, 20);
	}
}
