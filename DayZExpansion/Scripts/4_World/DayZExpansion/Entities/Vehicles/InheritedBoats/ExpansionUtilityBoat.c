/*
 * ExpansionUtilityBoat.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionUtilityBoat extends ExpansionBoatScript
{
	// ------------------------------------------------------------
	void ExpansionUtilityBoat()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::Constructor - Start");
		#endif

		//! Vanilla
		m_dmgContactCoef			= 0.018;

		//! Custom
		m_MaxSpeed					= 25.0;

		m_TurnCoef					= 0.2;
	
		m_Offset					= 3.5;

		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::Constructor - End");
		#endif
	}
	
	// ------------------------------------------------------------
	override int GetAnimInstance()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::GetAnimInstance");
		#endif
		return ExpansionVehicleAnimInstances.EXPANSION_UTILITY_BOAT;
	}

	// ------------------------------------------------------------
	override CarLightBase CreateFrontLight()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::CreateFrontLight");
		#endif
		return CarLightBase.Cast( ScriptedLightBase.CreateLight(ExpansionBoatFrontLight) );
	}

	// ------------------------------------------------------------
	override int GetSeatAnimationType( int posIdx )
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::GetSeatAnimationType");
		#endif
		switch( posIdx )
		{
		case 0:
			return DayZPlayerConstants.VEHICLESEAT_DRIVER;
		case 1:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		case 2:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		case 3:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		}

		return 0;
	}
	
	// ------------------------------------------------------------
	override bool CrewCanGetThrough( int posIdx )
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::CrewCanGetThrough");
		#endif
		return true;
	}

	// ------------------------------------------------------------
	override bool CanReachDoorsFromSeat( string pDoorsSelection, int pCurrentSeat )
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::CanReachDoorsFromSeat");
		#endif
		return true;		
	}

	// ------------------------------------------------------------
	override bool IsVitalCarBattery()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::IsVitalCarBattery");
		#endif
		return false;
	}

	// ------------------------------------------------------------
	override bool IsVitalTruckBattery()
    {
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::IsVitalTruckBattery");
		#endif
        return true;
    }

	// ------------------------------------------------------------
	override bool IsVitalSparkPlug()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::IsVitalSparkPlug");
		#endif
		return false;
	}
	
	// ------------------------------------------------------------
	override bool IsVitalRadiator()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::IsVitalRadiator");
		#endif
		return false;
	}
	
	// ------------------------------------------------------------
	override bool IsVitalGlowPlug()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::IsVitalGlowPlug");
		#endif
		return true;
	}

	// ------------------------------------------------------------
	override bool IsVitalEngineBelt()
	{
		#ifdef EXPANSIONEXPRINT
		EXPrint("ExpansionUtilityBoat::IsVitalEngineBelt");
		#endif
		return false;
	}

	// ------------------------------------------------------------
	override bool CanObjectAttach( Object obj )
	{
		if ( vector.Distance( GetPosition(), obj.GetPosition() ) > m_BoundingRadius * 1.5 )
			return false;

		return true;
	}
}