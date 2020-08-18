/**
 * ExpansionActionEnterFlagMenu.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

/**@class		ExpansionActionEnterFlagMenu
 * @brief		
 **/
class ExpansionActionEnterFlagMenu: ActionInteractBase
{
	// -----------------------------------------------------------
	// ExpansionActionEnterFlagMenu Destructor
	// -----------------------------------------------------------
	void ExpansionActionEnterFlagMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.CloseDoors;
	}
	
	// -----------------------------------------------------------
	// Override CreateConditionComponents
	// -----------------------------------------------------------
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
	}
	
	// -----------------------------------------------------------
	// Override GetText
	// -----------------------------------------------------------
	override string GetText()
	{
		return "#STR_EXPANSION_BB_FLAG_CHANGE";
	}
	
	// -----------------------------------------------------------
	// Override IsInstant
	// -----------------------------------------------------------
	override bool IsInstant()
	{
		return true;
	}

	// -----------------------------------------------------------
	// Override ActionCondition
	// -----------------------------------------------------------
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target.GetObject() )
			return false;

		//! Is this a flag ?
		ExpansionFlagBase flag;
		if ( Class.CastTo( flag, target.GetObject() ) )
		{
			//! Is he in a territory ?
			if ( player.IsInTerritory() )
				return player.IsInsideOwnTerritory(); //! show the prompt only if it's his territory

			//! Even if a user can place a flag, he can't create a territory if the limit is reached
			return true; //! Show the prompt
		}
		
		return false; //! Nope
	}
	
	// -----------------------------------------------------------
	// Override OnStartClient
	// -----------------------------------------------------------
	override void OnStartClient(ActionData action_data)
	{
		ExpansionTerritoryModule module;
		if ( Class.CastTo( module, GetModuleManager().GetModule( ExpansionTerritoryModule ) ) )
		{
			module.CloseMenus();
		}
	}
	
	// -----------------------------------------------------------
	// Override OnStartServer
	// -----------------------------------------------------------
	override void OnStartServer(ActionData action_data)
	{
		if (!(action_data.m_Player) || !(action_data.m_Player.GetIdentity()) || !(action_data.m_Target) || !(action_data.m_Target.GetObject())) return;
		
		ExpansionFlagBase flag;
		if ( Class.CastTo( flag, action_data.m_Target.GetObject() ) )
		{
			if ( flag.GetOwnerID() == action_data.m_Player.GetIdentityUID() )
			{
				ScriptRPC rpc = new ScriptRPC;
				rpc.Send( flag, ExpansionTerritoryModuleRPC.OpenFlagMenu, true, action_data.m_Player.GetIdentity() );
				return;
			}
		} 
		
		GetNotificationSystem().CreateNotification( new StringLocaliser( "STR_EXPANSION_TERRITORY_TITLE" ),  new StringLocaliser( "" ), EXPANSION_NOTIFICATION_ICON_INFO, COLOR_EXPANSION_NOTIFICATION_AMETHYST, 5, action_data.m_Player.GetIdentity() );
	}
}