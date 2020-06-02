/**
 * ExpansionBaseBuildingSettings.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

/**@class		ExpansionBaseBuildingSettings
 * @brief		Spawn settings class
 **/
class ExpansionBaseBuildingSettings: ExpansionSettingBase
{
	bool CanCraftVanillaBasebuilding;
	bool CanCraftExpansionBasebuilding;

	bool CanRaid;
	bool CanRaidSafes;

	float ExplosionTime;

	float ExplosionDamageMultiplier;
	float ProjectileDamageMultiplier;
	
	int TerritoryMode; //! 0 Means that you can build without territory, but nobody else can build near your territory | 1 Means that you can only build if you are in your territory
	
	[NonSerialized()]
	private bool m_IsLoaded;

	// ------------------------------------------------------------
	void ExpansionBaseBuildingSettings()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::ExpansionBaseBuildingSettings - Start");
		#endif
		
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::ExpansionBaseBuildingSettings - End");
		#endif
	}
	
	// ------------------------------------------------------------
	override void HandleRPC( ref ParamsReadContext ctx )
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::HandleRPC - Start");
		#endif
		
		ExpansionBaseBuildingSettings setting;
		if ( !ctx.Read( setting ) )
		{
			Error("ExpansionBaseBuildingSettings::HandleRPC setting");
			return;
		}

		CopyInternal( setting );
		
		m_IsLoaded = true;

		ExpansionSettings.SI_BaseBuilding.Invoke();
		
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::HandleRPC - End");
		#endif
    }

	// ------------------------------------------------------------
	override int Send( PlayerIdentity identity )
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::Send - Start");
		#endif
		
		if ( !IsMissionHost() )
		{
			return 0;
		}
		
		ref ExpansionBaseBuildingSettings thisSetting = this;
		
		ScriptRPC rpc = new ScriptRPC;
		rpc.Write( thisSetting );
		rpc.Send( null, ExpansionSettingsRPC.BaseBuilding, true, identity );
		
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::Send - End and return");
		#endif

		return 0;
	}

	// ------------------------------------------------------------
    override bool Copy( ExpansionSettingBase setting )
    {
		ExpansionBaseBuildingSettings s;
		if ( !Class.CastTo( s, setting ) )
			return false;

		CopyInternal( s );
		return true;
	}

	// ------------------------------------------------------------
	private void CopyInternal( ref ExpansionBaseBuildingSettings s )
	{
		CanCraftVanillaBasebuilding = s.CanCraftVanillaBasebuilding;
		CanCraftExpansionBasebuilding = s.CanCraftExpansionBasebuilding;

		CanRaid = s.CanRaid;
		CanRaidSafes = s.CanRaidSafes;

		ExplosionTime = s.ExplosionTime;

		ExplosionDamageMultiplier = s.ExplosionDamageMultiplier;
		ProjectileDamageMultiplier = s.ProjectileDamageMultiplier;
		TerritoryMode = s.TerritoryMode;
    }
	
	// ------------------------------------------------------------
	override bool IsLoaded()
	{
		return m_IsLoaded;
	}

	// ------------------------------------------------------------
	override void Unload()
	{
		m_IsLoaded = false;
	}

	// ------------------------------------------------------------
	override bool OnLoad()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::Load - Start");
		#endif

		m_IsLoaded = true;

		if ( FileExist( EXPANSION_BASE_BUILDING_SETTINGS ) )
		{
			JsonFileLoader<ExpansionBaseBuildingSettings>.JsonLoadFile( EXPANSION_BASE_BUILDING_SETTINGS, this );

			#ifdef EXPANSIONEXPRINT
			EXPrint("ExpansionBaseBuildingSettings::Load - End");
			#endif

			return true;
		}
		
		Defaults();
		Save();

		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::Load - End");
		#endif

		return false;
	}

	// ------------------------------------------------------------
	override bool OnSave()
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("[ExpansionBaseBuildingSettings] Saving settings");
		#endif
		
		JsonFileLoader<ExpansionBaseBuildingSettings>.JsonSaveFile( EXPANSION_BASE_BUILDING_SETTINGS, this );
		return true;
	}

	// ------------------------------------------------------------
	override void Defaults()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::Defaults - Start");
		#endif

		CanCraftVanillaBasebuilding = false;
		CanCraftExpansionBasebuilding = true;

		CanRaid = true;
		CanRaidSafes = true;
		
		ExplosionTime = 60;

		ExplosionDamageMultiplier = 50;
		ProjectileDamageMultiplier = 2;
		TerritoryMode = 0;
		
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionBaseBuildingSettings::Defaults - End");
		#endif
	}
}