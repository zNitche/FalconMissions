class KOTHMissionBase
{
	KOTHFlag flag;
	
	string ownerID;
	
	string missionName;
	int missionId;
	vector missionCenter;
	int missionRadius;
	int missionLifespan;
	
	int moneyRewardAmmount;
	
	float capturePerUpdate = FalconMissionsConsts.KOTH_CAPTURE_PER_UPDATE;
	float maxCapture = FalconMissionsConsts.KOTH_MAX_CAPTURE;
	float currentCapture;
	
	
	void init()
	{
		
	}
	
	void update()
	{
		missionLifespan--;
		
		checkCaptureState();
	}
	
	KOTHPlace getMissionPlace()
	{
		string pos = missionCenter[0].ToString() + " " + missionCenter[1].ToString() + " " + missionCenter[2].ToString();
		
		KOTHPlace place = new KOTHPlace(missionName, currentCapture, pos, missionId);
		
		return place;
	}
	
	void checkCaptureState()
	{
		if (currentCapture >= maxCapture)
		{
			missionLifespan = 0;
		}
		
		else
		{
			array<string> playersInRadiusIDs = new array<string>();
			string flagOwnerID = flag.getOwnerID();
			
			if (flagOwnerID)
			{
				if (flagOwnerID != ownerID)
				{
					ownerID = flagOwnerID;
					
					currentCapture = 0;
					
					missionLifespan += maxCapture / capturePerUpdate;
				}
				
				else
				{
					playersInRadiusIDs = MissionsUtils.getPlayersIDsInRadius(flag.GetWorldPosition(), missionRadius);
				
					if (MissionsUtils.checkIfIDinIDs(playersInRadiusIDs, ownerID))
					{
						currentCapture += capturePerUpdate;
					}
					
					else
					{
						flag.setOwnerID("");
						
						currentCapture = 0;
					}
				}
			}
			
			else
			{
				currentCapture = 0;
			}
		}
		
		// Print("Current Capture Progress = " + currentCapture);
	}
	
	void spawnMission()
	{
		spawnFlag();
	}
	
	void spawnMissionReward()
	{
		initSmokeOnPos(missionCenter);
		
		Container_Base kothContainer = Container_Base.Cast(GetGame().CreateObject("KOTHCase", missionCenter, false, false, true));
		
		kothContainer.PlaceOnSurface();
		
		for (int i = 0; i < moneyRewardAmmount; i++)
		{
			kothContainer.GetInventory().CreateInInventory("Goldcoin");
		}
	}
	
	bool checkLifespan()
	{
		bool isAlive = true;
		
		if (missionLifespan <= 0)
		{
			flag.Delete();
			
			spawnMissionReward();
			
			isAlive = false;
		}
		
		return isAlive;
	}
	
	void spawnFlag()
	{
		flag = KOTHFlag.Cast(GetGame().CreateObject("KOTHFlag", missionCenter, false, false, true));
		
		flag.PlaceOnSurface();
	}
	
	private void initSmokeOnPos(vector pos)
	{
		MissionSmoke grenade = MissionSmoke.Cast(GetGame().CreateObject("MissionSmoke", pos, false, false, true));
		
		grenade.PlaceOnSurface();
		
		grenade.Unpin();
	}
}