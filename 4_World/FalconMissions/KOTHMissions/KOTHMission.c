class KOTHMission extends KOTHMissionBase
{
	void KOTHMission(int missionId, vector missionCenter, int missionRadius)
	{
		this.missionId = missionId;
		this.missionCenter = missionCenter;
		this.missionCenter = missionCenter;
		
		this.missionRadius = missionRadius;
		
		missionName = "KOTH";
		missionLifespan = 3600;
		moneyRewardAmmount = 1;
	}
	
	override void init()
	{
		spawnMission();
	}
}