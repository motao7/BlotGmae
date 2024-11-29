#include "TeamGenericTeamAgentInterface.h"

#include "Team.h"

UTeamGenericTeamAgentInterface::UTeamGenericTeamAgentInterface(const FObjectInitializer& ObjectInitializer )
	:Super(ObjectInitializer)
{
	
}

void ITeamGenericTeamAgentInterface::ConditionalBroadcastTeamChanged(const TScriptInterface<ITeamGenericTeamAgentInterface> This, const uint8 OldTeam, const uint8 NewTeam) const
{
	if(OldTeam!=NewTeam)
	{
		UObject* ThisObjet=This.GetObject();
		UE_LOG(LogTeam, Verbose, TEXT(" %s "), *GetPathNameSafe(ThisObjet));
		
		This.GetInterface()->GetTeamChangedDelegateChecked().Broadcast(ThisObjet,OldTeam,NewTeam);
	}
}
