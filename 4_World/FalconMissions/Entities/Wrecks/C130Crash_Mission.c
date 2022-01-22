class C130Crash_Mission extends MissionWreckBase
{
	Particle m_ParticleEfx;
	
	void C130Crash_Mission()
	{
		heightOffset = 5;
		
		if (GetGame().IsClient())
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, Vector(0, 0, 0));
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