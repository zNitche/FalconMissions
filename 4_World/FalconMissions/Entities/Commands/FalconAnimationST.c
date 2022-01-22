class FalconAnimationST
{
	private int m_CMD_Fall;
	private int m_CMD_Jump;
	private int m_CMD_Land;

	private int m_VAR_MovementSpeed;
	private int m_VAR_MovementDirection;

	private int m_EVT_LandEarlyExit;

	private int m_VAR_Look;
	private int m_VAR_LookDirX;
	private int m_VAR_LookDirY;

	private int m_VAR_AimX;
	private int m_VAR_AimY;

	private int m_VAR_Raised;

	
	void FalconAnimationST( Human human )
	{
		HumanAnimInterface hai = human.GetAnimInterface();

		m_CMD_Fall = hai.BindCommand( "CMD_Fall" );
		m_CMD_Jump = hai.BindCommand( "CMD_Jump" );
		m_CMD_Land = hai.BindCommand( "CMD_Land" );

		m_VAR_MovementSpeed = hai.BindVariableFloat( "MovementSpeed" );
		m_VAR_MovementDirection = hai.BindVariableFloat( "MovementDirection" );

		m_EVT_LandEarlyExit = hai.BindEvent( "LandEarlyExit" );

		m_VAR_Look = hai.BindVariableBool( "Look" );
		m_VAR_LookDirX = hai.BindVariableFloat( "LookDirX" );
		m_VAR_LookDirY = hai.BindVariableFloat( "LookDirY" );

		m_VAR_AimX = hai.BindVariableFloat( "AimX" );
		m_VAR_AimY = hai.BindVariableFloat( "AimY" );

		m_VAR_Raised = hai.BindVariableBool( "Raised" );
	}

	void CallFall( HumanCommandScript script, int pParamInt = 0, float pParamFloat = 0 )
	{
		script.PreAnim_CallCommand( m_CMD_Fall, pParamInt, pParamFloat );
	}

	void CallJump( HumanCommandScript script, int pParamInt = 0, float pParamFloat = 0 )
	{
		script.PreAnim_CallCommand( m_CMD_Jump, pParamInt, pParamFloat );
	}

	void CallLand( HumanCommandScript script, int pParamInt = 0, float pParamFloat = 0 )
	{
		script.PreAnim_CallCommand( m_CMD_Land, pParamInt, pParamFloat );
	}

	void SetMovementSpeed( HumanCommandScript script, float param )
	{
		script.PreAnim_SetFloat( m_VAR_MovementSpeed, param );
	}

	void SetMovementDirection( HumanCommandScript script, float param )
	{
		script.PreAnim_SetFloat( m_VAR_MovementDirection, param );
	}

	void SetLook( HumanCommandScript script, bool param )
	{
		script.PreAnim_SetBool( m_VAR_Look, param );
	}

	void SetLookDirX( HumanCommandScript script, float param )
	{
		script.PreAnim_SetFloat( m_VAR_LookDirX, param );
	}

	void SetLookDirY( HumanCommandScript script, float param )
	{
		script.PreAnim_SetFloat( m_VAR_LookDirY, param );
	}

	void SetAimX( HumanCommandScript script, float param )
	{
		script.PreAnim_SetFloat( m_VAR_AimX, param );
	}

	void SetAimY( HumanCommandScript script, float param )
	{
		script.PreAnim_SetFloat( m_VAR_AimY, param );
	}

	void SetRaised( HumanCommandScript script, bool param )
	{
		script.PreAnim_SetBool( m_VAR_Raised, param );
	}
}
