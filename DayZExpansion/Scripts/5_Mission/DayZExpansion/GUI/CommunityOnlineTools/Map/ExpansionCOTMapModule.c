/**
 * ExpansionCOTMapModule.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionCOTMapModule: ExpansionCOTModuleBase
{
	void ExpansionCOTMapModule()
	{
		GetPermissionsManager().RegisterPermission( "Expansion.Map.View" );
		GetPermissionsManager().RegisterPermission( "Expansion.Map.Update" );
	}

	override bool HasAccess()
	{
		return GetPermissionsManager().HasPermission( "Expansion.Map.View" );
	}

	override string GetLayoutRoot()
	{
		return "DayZExpansion/GUI/layouts/COT/map/form.layout";
	}

	override string GetTitle()
	{
		return "[EX] Map Settings";
	}

	override string GetIconName()
	{
		return "M";
	}

	override bool ImageIsIcon()
	{
		return false;
	}

	override string GetWebhookTitle()
	{
		return "Expansion Map Settings";
	}

	override ref ExpansionSettingBase GetSettingsInstance()
	{
		return GetExpansionSettings().GetMap();
	}

	override void OnRegisterSettings()
	{
		CreateToggle( "EnableMap", "Enable Map", "", "" );
		CreateToggle( "UseMapOnMapItem", "Use Map On Map Item", "", "" );
		CreateToggle( "CanCreateMarker", "Can Create Marker", "", "" );
		CreateToggle( "ShowPlayerPosition", "Show Player Position", "", "" );
		CreateToggle( "CanCreatePartyMarkers", "Can Create Party Markers", "", "" );
		CreateToggle( "ShowMapStats", "Show Map Stats", "", "" );
		CreateToggle( "CanCreate3DMarker", "Can Create 3D Marker", "", "" );
		CreateToggle( "ShowPartyMembersMapMarkers", "Show Party Members Map Markers", "", "" );
		CreateToggle( "ShowServerMarkers", "Show Server Markers", "", "" );
		CreateToggle( "CanOpenMapWithKeyBinding", "Can Open Map With Key Binding", "", "" );
	}

	override int GetRPCMin()
	{
		return ExpansionCOTMapModuleRPC.INVALID;
	}

	override int GetRPCMax()
	{
		return ExpansionCOTMapModuleRPC.COUNT;
	}

	override int GetRPCUpdate()
	{
		return ExpansionCOTMapModuleRPC.Update;
	}

	override void OnSend( ref ExpansionSettingBase setting )
	{
		if ( GetGame().IsClient() )
		{
			ScriptRPC rpc = new ScriptRPC();
			setting.OnSend( rpc );
			rpc.Send( NULL, ExpansionCOTMapModuleRPC.Update, true, NULL );
		} else if ( IsMissionOffline() )
		{
			GetSettingsInstance().Update( setting );
		}
	}

	override void OnSend_RPC( ref ParamsReadContext ctx, PlayerIdentity senderRPC, Object target )
	{
		if ( !IsMissionHost() )
			return;

		ref ExpansionMapSettings setting = new ExpansionMapSettings();
		if ( !setting.OnRecieve( ctx ) )
			return;

		JMPlayerInstance inst;
		if ( !GetPermissionsManager().HasPermission( "Expansion.Map.Update", senderRPC, inst ) )
			return;

		UpdateServer( setting, inst );
	}
};