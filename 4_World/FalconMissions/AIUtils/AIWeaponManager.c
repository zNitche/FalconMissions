class AIWeaponManager extends WeaponManager
{
	override bool StartAction(int action, Magazine mag, InventoryLocation il, ActionBase control_action = NULL)
	{
		if (control_action)
		{
			m_ControlAction = ActionBase.Cast(control_action);
			m_PendingWeaponAction = action;
			m_InProgress = true;
			m_IsEventSended = false;
			m_PendingTargetMagazine = mag;
			m_PendingInventoryLocation = il;
			StartPendingAction();
			
			return true;
		}
		
		if (!InventoryReservation(mag, il))
		{
			return false;
		}
			
		m_PendingWeaponAction = action;
		m_InProgress = true;
		m_IsEventSended = false;

		m_readyToStart = true;
		
		return true;
	}

	override void OnWeaponActionEnd()
	{
		if (!m_InProgress)
		{
			return;
		}
		
		if (!m_ControlAction)
		{
			InventoryLocation il = new InventoryLocation;
			il.SetHands(m_player,m_player.GetItemInHands());
			m_player.GetInventory().ClearInventoryReservation(m_player.GetItemInHands(), il);
					
			if (m_PendingTargetMagazine)
			{
				m_player.GetInventory().ClearInventoryReservation(m_PendingTargetMagazine, m_TargetInventoryLocation);
			}
					
			if (m_PendingInventoryLocation)
			{
				m_player.GetInventory().ClearInventoryReservation(m_PendingInventoryLocation.GetItem(), m_PendingInventoryLocation);
			}
		}
		
		if (m_WeaponInHand && !m_justStart && m_player.IsRaised())
		{
			if (m_InIronSight)
			{
				m_player.SetIronsights(m_InIronSight);
			}
			
			if (m_InOptic)
			{
				ItemOptics optic = m_WeaponInHand.GetAttachedOptics();
				
				if (optic)
				{
					m_player.SwitchOptics(optic,true);
				}
			}
		}
		
		m_ControlAction = NULL;
		m_PendingWeaponAction = -1;
		m_PendingTargetMagazine = NULL;
		m_PendingInventoryLocation = NULL;
		m_TargetInventoryLocation = NULL;
		m_PendingWeaponActionAcknowledgmentID = -1;
		m_InProgress = false;
		m_readyToStart = false;
		m_WantContinue = true;
		
	}

	override void Update(float deltaT)
	{
		if (m_WeaponInHand != m_player.GetItemInHands())
		{
			if (m_WeaponInHand)
			{
				m_SuitableMagazines.Clear();
				OnWeaponActionEnd();
			}
			
			m_WeaponInHand = Weapon_Base.Cast(m_player.GetItemInHands());
			
			if (m_WeaponInHand)
			{
				m_MagazineInHand = null;
				SetSutableMagazines();
				m_WeaponInHand.SetSyncJammingChance(0);
			}
			
			m_AnimationRefreshCooldown = 0;
		}
		
		if (m_WeaponInHand)
		{
			if (m_AnimationRefreshCooldown)
			{
				m_AnimationRefreshCooldown--;
			
				if ( m_AnimationRefreshCooldown == 0)
				{
					RefreshAnimationState();
				}
			}
		
			m_WeaponInHand.SetSyncJammingChance(m_WeaponInHand.GetChanceToJam());
			
			if (m_readyToStart)
			{
				StartPendingAction();
				m_readyToStart = false;
				return;
			}
		
			if (!m_InProgress || !m_IsEventSended)
			{
				return;
			}
		
			if (m_canEnd)
			{
			
				if (m_WeaponInHand.IsIdle())
				{
					OnWeaponActionEnd();
				}
				
				else if (m_justStart)
				{
					m_InIronSight = m_player.IsInIronsights();
					m_InOptic = m_player.IsInOptics();
		
					if (m_InIronSight || m_InOptic)
					{
						m_player.GetInputController().ResetADS();
						m_player.ExitSights();
					}
				
					m_justStart = false;
				}
			
			}
			else
			{
				m_canEnd = true;
				m_justStart = true;
			}
		}
		
		else
		{
			if (m_MagazineInHand != m_player.GetItemInHands())
			{
				m_MagazineInHand = MagazineStorage.Cast(m_player.GetItemInHands());
				
				if (m_MagazineInHand)
				{
					SetSutableMagazines();
				}
			}
		}
	}
}
