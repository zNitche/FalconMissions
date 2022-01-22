class AIHelpers
{
	//Insipired by github.com/ralian/eai
	
	static WeaponEventBase createWeaponEventForAISync(AISyncPackage syncPackage)
	{
		int eventID = syncPackage.eventID;
		int animID = syncPackage.animID;
		DayZPlayer player = syncPackage.player;
		Magazine mag = syncPackage.mag;
		
		return WeaponEventFactory(eventID, animID, player, mag);
	}

	static bool syncAIInventoryWithPlayer(AISyncPackage syncPackage)
	{
		DayZPlayer player = syncPackage.player;
		
		FalconAI fAI = FalconAI.Cast(player);
		
		if (!fAI || !fAI.GetDayZPlayerInventory()) 
		{
			return false;
		}
		
		if (fAI.GetDayZPlayerInventory().GetEntityInHands())
		{
			Weapon_Base weap = Weapon_Base.Cast(fAI.GetDayZPlayerInventory().GetEntityInHands());
			
			if (weap)
			{
				WeaponEventBase weaponEvent = createWeaponEventForAISync(syncPackage);
				
				if (fAI && weaponEvent)
				{
					fAI.GetWeaponManager().SetRunning(true);
		
					if (weaponEvent.GetEventID() == WeaponEventID.HUMANCOMMAND_ACTION_ABORTED)
					{
						weap.ProcessWeaponAbortEvent(weaponEvent);
					}
					
					else
					{
						weap.ProcessWeaponEvent(weaponEvent);
					}
					
					fAI.GetWeaponManager().SetRunning(false);
				}
			}
		}
		
		return true;
	}
}