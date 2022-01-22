class FalconAI extends SurvivorBase
{
	private ref FalconAnimationST fAIAnimationST = new FalconAnimationST(this);
	private ref AILoadout aiLoadout;
	
	private vector missionCenter;
	private float missionRadius;
	private int missionLVL;
	private string missionType;
	
	private float initMinTime = 5;
	private float initMaxTime = 10;
	
	private ref Timer dangerTimer = new Timer();
	private ref Timer movementTimer = new Timer();
	private ref Timer reactionTimer = new Timer();
	
	private float dangerMinTime;
	private float dangerMaxTime;
	
	private float movementMinTime;
	private float movementMaxTime;
	
	private float reactionMinTime;
	private float reactionMaxTime;
	
	private float viewDistance;
	private float warnDistance;
	
	float accuracy;
	
	bool isInDanger = false;
	bool inPlace = false;
	bool weaponRaised = false;
	
	vector waypoint = vector.Zero;
	
	private ref array<Object> targets = new array<Object>();
	Object target;

	
	void FalconAI() 
	{
		m_WeaponManager = new AIWeaponManager(this);
	}
	
	void runInit()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(init,  Math.RandomInt(initMinTime, initMaxTime) * 1000, false);
	}
	
	void init()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(update, 1000, true);
		
		initSense();
		reloadWeapon();
	}
	
	void initSense()
	{
		// Civilian
		if (missionLVL == 1)
		{
			dangerMinTime = FalconAIConsts.civilianDangerMinTime;
			dangerMaxTime = FalconAIConsts.civilianDangerMaxTime;
			movementMinTime = FalconAIConsts.civilianMovementMinTime;
			movementMaxTime = FalconAIConsts.civilianMovementMaxTime;
			reactionMinTime = FalconAIConsts.civilianReactionMinTime;
			reactionMaxTime = FalconAIConsts.civilianReactionMaxTime;
			viewDistance = FalconAIConsts.civilianViewDistance;
			warnDistance = FalconAIConsts.civilianWarnDistance;
			accuracy = FalconAIConsts.civilianAccuracy;
		}
		// Medium
		else if (missionLVL == 2)
		{
			dangerMinTime = FalconAIConsts.mediumDangerMinTime;
			dangerMaxTime = FalconAIConsts.mediumDangerMaxTime;
			movementMinTime = FalconAIConsts.mediumMovementMinTime;
			movementMaxTime = FalconAIConsts.mediumMovementMaxTime;
			reactionMinTime = FalconAIConsts.mediumReactionMinTime;
			reactionMaxTime = FalconAIConsts.mediumReactionMaxTime;
			viewDistance = FalconAIConsts.mediumViewDistance;
			warnDistance = FalconAIConsts.mediumWarnDistance;
			accuracy = FalconAIConsts.mediumAccuracy;
		}
		// Military
		else if (missionLVL == 3)
		{
			dangerMinTime = FalconAIConsts.militaryDangerMinTime;
			dangerMaxTime = FalconAIConsts.militaryDangerMaxTime;
			movementMinTime = FalconAIConsts.militaryMovementMinTime;
			movementMaxTime = FalconAIConsts.militaryMovementMaxTime;
			reactionMinTime = FalconAIConsts.militaryReactionMinTime;
			reactionMaxTime = FalconAIConsts.militaryReactionMaxTime;
			viewDistance = FalconAIConsts.militaryViewDistance;
			warnDistance = FalconAIConsts.militaryWarnDistance;
			accuracy = FalconAIConsts.militaryAccuracy;
		}
		
		else
		{
			dangerMinTime = FalconAIConsts.civilianDangerMinTime;
			dangerMaxTime = FalconAIConsts.civilianDangerMaxTime;
			movementMinTime = FalconAIConsts.civilianMovementMinTime;
			movementMaxTime = FalconAIConsts.civilianMovementMaxTime;
			reactionMinTime = FalconAIConsts.civilianReactionMinTime;
			reactionMaxTime = FalconAIConsts.civilianReactionMaxTime;
			viewDistance = FalconAIConsts.civilianViewDistance;
			warnDistance = FalconAIConsts.civilianWarnDistance;
			accuracy = FalconAIConsts.civilianAccuracy;
		}
	}
	
	// Call before init
	void setupAILoadout(AILoadout loadout)
	{
		aiLoadout = new AILoadout();
		aiLoadout = loadout;
		
		AIUtils.initAILoadout(this, aiLoadout);
	}
	
	// Call before init
	void setMissionParams(vector missionCenter, float missionRadius, int missionLVL, string missionType)
	{
		this.missionCenter = missionCenter;
		this.missionRadius = missionRadius;
		this.missionLVL = missionLVL;
		this.missionType = missionType;
	}
	
	void update()
	{
		if (IsAlive())
		{
			scanWorld();
			getClosestTarget();
			
			checkIsInPlace();
			
			checkIfWaypointReached();
			getRandomWaypoint();
			
			checkIfInDanger();
			
			// debugLog();
		}
	}
	
	private void checkIsInPlace()
	{
		if (isInDanger)
		{
			inPlace = false;
		}
		else
		{
			if (checkMovement())
			{
				inPlace = false;
			}
			else
			{
				inPlace = true;
			}
		}
	}
	
	void checkIfInDanger()
	{
		if (dangerTimer.IsRunning())
		{
			isInDanger = true;
		}
		else
		{
			isInDanger = false;
		}
	}
	
	void runDangerTimer()
	{
		if (!dangerTimer.IsRunning())
		{
			int time = Math.RandomInt(dangerMinTime, dangerMaxTime);
			
			dangerTimer.Run(time, this, "");
		}
	}
	
	private bool checkMovement()
	{
		if (movementTimer.IsRunning())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	private void runMovementTimer()
	{
		if (!movementTimer.IsRunning())
		{
			int time = Math.RandomInt(movementMinTime, movementMaxTime);
			
			movementTimer.Run(time, this, "");
		}
	}
	
	private bool checkReaction()
	{
		if (reactionTimer.IsRunning())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	private void runReactionTimer()
	{
		if (!reactionTimer.IsRunning())
		{
			int time = Math.RandomInt(reactionMinTime, reactionMaxTime);
			
			reactionTimer.Run(time, this, "");
		}
	}
	
	private void fireWeapon() 
	{
		Weapon_Base weap = Weapon_Base.Cast(GetHumanInventory().GetEntityInHands());
		
		if (weap) 
		{
			if (checkReaction())
			{
				if (weap.CanFire())
				{
					GetWeaponManager().Fire(weap);
					
					GetInputController().OverrideAimChangeY(true, 0.0);
				}
				else
				{
					reloadWeapon();
					weap.SetHealthMax();
				}
				
				runReactionTimer();
			}
		}
	}
	
	private void reloadWeapon()
	{
		Weapon_Base weap = Weapon_Base.Cast(GetHumanInventory().GetEntityInHands());
		
		if (weap)
		{
			//Magazine mag = weap.GetMagazine(weap.GetCurrentMuzzle());
			Magazine mag = Magazine.Cast(GetMagazineToReload(weap));
			
			if (mag)
			{
				mag.SetHealthMax();
			}
			else
			{
				AIUtils.clearEmptyMags(this, aiLoadout.magName);
				GetInventory().CreateInInventory(aiLoadout.magName);
			}
			
			if (GetWeaponManager().CanAttachMagazine(weap, mag))
			{
				GetWeaponManager().AttachMagazine(mag);
			}
			
			else if (GetWeaponManager().CanSwapMagazine(weap, mag))
			{
				GetWeaponManager().SwapMagazine(mag);
			}
		}
	}
	
	private bool checkVisibilitiy(vector targetPos)
	{
		//vector currentPos = getWeaponPosition();
		vector currentPos = GetPosition();
		
		PhxInteractionLayers hitMask = PhxInteractionLayers.BUILDING|PhxInteractionLayers.TERRAIN|PhxInteractionLayers.DOOR|PhxInteractionLayers.VEHICLE|PhxInteractionLayers.ROADWAY|PhxInteractionLayers.ITEM_SMALL|PhxInteractionLayers.ITEM_LARGE|PhxInteractionLayers.FENCE;
		
		currentPos[1] = currentPos[1] + 1.5;
		targetPos[1] = targetPos[1] + 1.5;
		
		if (currentPos == targetPos)
		{
			return true;
		}
		
		Object hitObject;
		vector hitPos, hitNormal;
		float hitFraction;
		
		bool hit = DayZPhysics.RayCastBullet(currentPos, targetPos, hitMask, this, hitObject, hitPos, hitNormal, hitFraction);
	
		return !hit;
	}
	
	private void getClosestTarget()
	{
		vector currentPos = GetPosition();
		vector targetPos;
		
		array<float> distances = new array<float>();
		
		if (targets.Count() >= 1)
		{
			for (int i = 0; i < targets.Count(); i++)
			{
				targetPos = targets[i].GetPosition();
				
				distances.Insert(vector.Distance(currentPos, targetPos));
			}
			
			target = targets[AIUtils.getMinIndex(distances)];
			
			runDangerTimer();
			warnOthers();
			
			// Remove this when AI have problems with shooting
			// runReactionTimer();
		}
		
		else
		{
			target = null;
		}
	}
	
	private void scanWorld()
	{
		array<Object> objects = new array<Object>();
		PlayerBase target;
		
		targets.Clear();
		
		GetGame().GetObjectsAtPosition(GetPosition(), viewDistance, objects, null);
		
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i].IsInherited(PlayerBase) && !objects[i].IsInherited(FalconAI))
			{
				target = PlayerBase.Cast(objects[i]);
				
				if (target.IsAlive())
				{
					if (checkVisibilitiy(objects[i].GetPosition()))
					{
						targets.Insert(objects[i]);
					}
				}
			}
		}
	}
	
	private void warnOthers()
	{
		array<Object> objects = new array<Object>();
		
		FalconAI ai;
		
		GetGame().GetObjectsAtPosition(GetPosition(), warnDistance, objects, null);
		
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i].IsInherited(FalconAI))
			{
				//if (checkVisibilitiy(objects[i].GetPosition()))
				//{
				ai = FalconAI.Cast(objects[i]);
				
				ai.runDangerTimer();
				ai.checkIfInDanger();
				//}
			}
		}
	}

	void raiseWeapon(bool value) 
	{
		HumanCommandWeapons hcw = GetCommandModifier_Weapons();
		
		if (hcw)
		{
			hcw.SetADS(value);
		}
		
		weaponRaised = value;
		
		if (value)
		{
			waypoint = vector.Zero;
		}
	}
	
	vector getWeaponPosition()
	{
		Weapon_Base weapon;
		vector weaponPosition = vector.Zero;
		
		EntityAI inHands = GetHumanInventory().GetEntityInHands();
		
		if (inHands && inHands.IsWeapon())
		{
			weapon = Weapon_Base.Cast(inHands);
			
			weaponPosition = weapon.GetPosition();
		}
		
		return weaponPosition;
	}
	
	private vector generateRandomWaypoint()
	{
		float x = Math.RandomInt(missionCenter[0] - missionRadius, missionCenter[0] + missionRadius);
		float z = Math.RandomInt(missionCenter[2] - missionRadius, missionCenter[2] + missionRadius);
		
		float y = GetGame().SurfaceY(x, z);
		
		return Vector(x, y, z);
	}
	
	private void getRandomWaypoint()
	{
		if (waypoint == vector.Zero && !weaponRaised)
		{
			if (isInDanger)
			{
				waypoint = generateRandomWaypoint();
			}
			else
			{
				if (checkMovement())
				{
					waypoint = generateRandomWaypoint();
				}
			}
		}
	}
	
	private void checkIfWaypointReached()
	{
		if (waypoint != vector.Zero && !weaponRaised)
		{
			if (vector.Distance(GetPosition(), waypoint) <= 0.5)
			{
				waypoint = vector.Zero;
				runMovementTimer();
			}
		}
	}
	
	override void HandleWeapons(float pDt, Entity pInHands, HumanInputController pInputs, out bool pExitIronSights)
	{
		HumanCommandWeapons	hcw = GetCommandModifier_Weapons();
    	GetDayZPlayerInventory().HandleWeaponEvents(pDt, pExitIronSights);

		Weapon_Base weapon = Weapon_Base.Cast(pInHands);
		
		FalconAICommandMove moveCommand = FalconAICommandMove.Cast(GetCommand_Script());
		
		if (!weaponRaised)
		{
			if (target)
			{
				raiseWeapon(true);
			}
			else
			{
				raiseWeapon(false);
			}
		}
		else
		{
			if (!target)
			{
				raiseWeapon(false);
			}
		}
		
		if (weaponRaised)
		{
			//runDangerTimer();
			
			float targetHeight = 1.0 + target.GetPosition()[1]; 
			float gunHeight = 1.5 + GetPosition()[1]; 
			
			float targetAngle = Math.Atan2(targetHeight - gunHeight, vector.Distance(GetPosition(), target.GetPosition())) * Math.RAD2DEG;
			
			float Y = hcw.GetBaseAimingAngleUD();
			
			float m_AimDeltaY = (targetAngle - Y);
			
			pInputs.OverrideAimChangeX(true, 0.001 * m_AimDeltaY);
			pInputs.OverrideAimChangeY(true, 1.0);
			
			fireWeapon();
		}
		
		else
		{
			pInputs.OverrideAimChangeX(false, 0);
			pInputs.OverrideAimChangeY(false, 0);
		}		
	}
	
	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished) 
	{
		if (!GetGame().IsServer())
		{
			return;
		} 

		HumanInputController hic = GetInputController();
		
		if (HandleDeath(pCurrentCommandID))
		{
			return;
		}
		
		if (m_WeaponManager) 
		{
			m_WeaponManager.Update(pDt);
		}
		
		GetPlayerSoundManagerServer().Update();
		GetHumanInventory().Update(pDt);
		UpdateDelete();
		
		EntityAI entityInHands = GetHumanInventory().GetEntityInHands();
		bool isWeapon = entityInHands && entityInHands.IsInherited(Weapon);
		
		if (hic)
		{
			if (isWeapon && (!hic.IsImmediateAction() || !m_ProcessFirearmMeleeHit || !m_ContinueFirearmMelee))
			{
				m_ProcessFirearmMeleeHit = false;
				bool exitIronSights = false;
				HandleWeapons(pDt, entityInHands, hic, exitIronSights);
			}	
		}
		
		if (pCurrentCommandFinished) 
		{
			if (PhysicsIsFalling(true))
			{
				StartCommand_Fall(0);

				return;
			}

			StartCommand_Script(new FalconAICommandMove(this, fAIAnimationST));
		}

		if (pCurrentCommandID == DayZPlayerConstants.COMMANDID_FALL)
		{
			int landType = 0;
			HumanCommandFall fall = GetCommand_Fall();

			if (fall && fall.PhysicsLanded())
			{
				DayZPlayerType type = GetDayZPlayerType();
				NoiseParams npar;


				m_FallYDiff = m_FallYDiff - GetPosition()[1];

				if (m_FallYDiff < 0.5)
				{
					landType = HumanCommandFall.LANDTYPE_NONE; 
					fall.Land(landType);
					npar = type.GetNoiseParamsLandLight();
					AddNoise(npar);
				}
				else if (m_FallYDiff < 1.0)
				{
					landType = HumanCommandFall.LANDTYPE_LIGHT;
					fall.Land(landType);
					npar = type.GetNoiseParamsLandLight();
					AddNoise(npar);
				}
				else if (m_FallYDiff < 2.0)
				{
					landType = HumanCommandFall.LANDTYPE_MEDIUM;
					fall.Land(landType);
					npar = type.GetNoiseParamsLandHeavy();
					AddNoise(npar);
				}
				else
				{
					landType = HumanCommandFall.LANDTYPE_HEAVY;
					fall.Land(landType);
					npar = type.GetNoiseParamsLandHeavy();
					AddNoise(npar);
				}
				
				if( m_FallYDiff >= DayZPlayerImplementFallDamage.FD_DMG_FROM_HEIGHT && GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_CLIENT )
				{
					this.SpawnDamageDealtEffect();
				}
				
				m_FallDamage.HandleFallDamage(m_FallYDiff);
				m_JumpClimb.CheckAndFinishJump(landType);
			}

			return;
		}
		
		if (PhysicsIsFalling(false))
		{
			StartCommand_Fall(0);
			m_FallYDiff = GetPosition()[1];
			return;
		}
		
		if (HandleDamageHit(pCurrentCommandID))
		{
			return;
		}

		if (m_ActionManager)
		{
			m_ActionManager.Update(DayZPlayerConstants.COMMANDID_MOVE);
		}
		
		if (pCurrentCommandID == DayZPlayerConstants.COMMANDID_MOVE)
		{
			StartCommand_Script(new FalconAICommandMove(this, fAIAnimationST));
			return;
		}
		
		OnCommandHandlerTick(pDt, pCurrentCommandID);
	}
	
	override bool CanBeTargetedByAI(EntityAI ai)
	{
		return false;
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		
		runDangerTimer();
		checkIfInDanger();
		
		warnOthers();
	}
	
	int getMissionLVL()
	{
		return missionLVL;
	}
	
	string getMissionType()
	{
		return missionType;
	}
	
	private void debugLog()
	{
		Print("Bot Pos = " + GetPosition());
		Print("Target = " + target);
		Print("Waypoint = " + waypoint);
		Print("In Danger = " + isInDanger);
		Print("In Place = " + inPlace);
		Print("Is in danger timer running = " + dangerTimer.IsRunning());
		Print("reaction timer running = " + reactionTimer.IsRunning());
		Print("movement timer running = " + movementTimer.IsRunning());
	}
}
