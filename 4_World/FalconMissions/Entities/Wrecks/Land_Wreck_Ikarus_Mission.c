class Land_Wreck_Ikarus_Mission extends MissionWreckBase
{
	Particle m_ParticleEfx;
	
	void Land_Wreck_Ikarus_Mission()
	{
		heightOffset = 1;
		
		if (GetGame().IsClient())
		{
			float smokeChance = Math.RandomFloat(0, 1);
		
			if (smokeChance > 0.5)
			{
				m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, Vector(0, 0, 0));
			}
		}
	}
	
	override void EEInit()
	{
		super.EEInit();
	}
	
	override void EEDelete(EntityAI parent)
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
		}
	}
}