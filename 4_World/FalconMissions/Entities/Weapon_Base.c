modded class Weapon_Base
{
	override bool ProcessWeaponEvent(WeaponEventBase e)
	{
		// Stack Overflow !!!
		//if (GetGame().IsServer() && e.m_player.IsInherited(PlayerBase))
		//{
		//	return ProcessWeaponEvent(e);
		//}
		
		if (GetGame().IsServer() && e.m_player.IsInherited(FalconAI))
		{
			AISyncPackage syncPackage = new AISyncPackage(e.GetEventID(), e.GetAnimEvent(), e.m_player, e.m_magazine);
			
			GetRPCManager().SendRPC("FalconMissions", "updateAIWeapon", new Param1<AISyncPackage>(syncPackage));
			
			if (CanFire() && e.GetEventID() == WeaponEventID.TRIGGER) 
			{
				float ammoDamage;
				string ammoTypeName;
				
				GetCartridgeInfo(GetCurrentMuzzle(), ammoDamage, ammoTypeName);
				
				FalconAI fAI = FalconAI.Cast(e.m_player);
				
				if (fAI.target)
				{
					float distanceToTarget = vector.Distance(fAI.GetPosition(), fAI.target.GetPosition());
					
					if (AIUtils.calculateHit(fAI.accuracy, distanceToTarget))
					{
						fAI.target.ProcessDirectDamage(DT_FIRE_ARM, this, "Torso", ammoTypeName, vector.Zero, 1.0);
					}
				}
			}
			

			SyncEventToRemote(e);
			
			if (m_fsm.ProcessEvent(e) == ProcessEventResult.FSM_OK)
			{
				return true;
			}
				
				
			return false;
		}
		
		if (e.m_player.IsInherited(PlayerBase))
		{
			SyncEventToRemote(e);
		
			if (e.GetEventID() == WeaponEventID.SET_NEXT_MUZZLE_MODE)
			{
				SetNextMuzzleMode(GetCurrentMuzzle());
				return true;
			}
	
			if (m_fsm.ProcessEvent(e) == ProcessEventResult.FSM_OK)
			{
				return true;
			}
	
			return false;
		}
		
		return false;
	}
}
