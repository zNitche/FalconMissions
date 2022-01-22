class FalconAICommandMove extends FalconAICommandBase
{
	private FalconAI FAIBot;
	private FalconAnimationST FAI_ST;

	private int previousInteractionLayer;
	
	private float movementSpeed;
	private float defaultSlowMovementSpeed = 5;
	private float defaultSprintMovementSpeed = 100;
	

	void FalconAICommandMove(FalconAI bot, FalconAnimationST st)
	{
		FAIBot = bot;
		FAI_ST = st;
	}
	
	void ~FalconAICommandMove()
	{
	}

	override void OnActivate()
	{		
		previousInteractionLayer = dBodyGetInteractionLayer(FAIBot);
		dBodySetInteractionLayer(FAIBot, PhxInteractionLayers.CHARACTER | PhxInteractionLayers.BUILDING | PhxInteractionLayers.DOOR | PhxInteractionLayers.VEHICLE | PhxInteractionLayers.ITEM_LARGE | PhxInteractionLayers.FENCE | PhxInteractionLayers.AI);
	}

	override void OnDeactivate()
	{
		dBodySetInteractionLayer(FAIBot, previousInteractionLayer);
	}

	override void PreAnimUpdate(float pDt)
	{
		FAI_ST.SetRaised(this, FAIBot.weaponRaised);
		
		if (!FAIBot.weaponRaised)
		{
			if (FAIBot.inPlace)
			{
				movementSpeed = 0;
			}
			else
			{
				if (FAIBot.isInDanger)
				{
					movementSpeed = defaultSprintMovementSpeed;
				}
				else
				{
					movementSpeed = defaultSlowMovementSpeed;
				}
			}
		}
		
		else
		{
			movementSpeed = 0;
		}
		
		FAI_ST.SetMovementSpeed(this, movementSpeed * pDt);
	}

	override void PrePhysUpdate(float pDt)
	{			
		vector relativePos;
		
		if (FAIBot.target)
		{
			vector targetPos = FAIBot.target.GetPosition();
			
			if (FAIBot.weaponRaised)
			{
				relativePos = targetPos - FAIBot.getWeaponPosition();
				
				FAIBot.SetDirection(relativePos);
			}
		}
		
		else if (FAIBot.waypoint != vector.Zero)
		{
			relativePos = FAIBot.waypoint - FAIBot.GetPosition();
			
			if (getAngleDiff(FAIBot.waypoint) != 0)
			{
				FAIBot.SetDirection(relativePos);
			}
		}
	}
	
	private int getAngleDiff(vector targetPos)
	{
		float currentYaw = Math.NormalizeAngle(FAIBot.GetOrientation()[0]);
		float angleBetween = angleBetweenPoints(FAIBot.GetPosition(), targetPos);
		int angleDiff;
		
		if (angleBetween >= 180.0)
		{
			angleBetween = angleBetween - 360.0;
		}
		
		if (currentYaw <= -180.0)
		{
			currentYaw = currentYaw + 360.0;
		}
		
		angleDiff = Math.AngleDiff(angleBetween, currentYaw);
		
		return angleDiff;
	}
	
	float angleBetweenPoints(vector point1, vector point2)
	{
		return vector.Direction(point1, point2).Normalized().VectorToAngles()[0];
	}
}