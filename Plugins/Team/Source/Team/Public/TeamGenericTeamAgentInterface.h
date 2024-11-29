#pragma once

#include "GenericTeamAgentInterface.h"
#include "TeamGenericTeamAgentInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTeamChangedDelegateSignature,UObject*,ObjectChangingTeam,uint8,OldTeamId,uint8,NewTeamId);

inline uint8 GenericTeamIdToInteger(const FGenericTeamId ID)
{
	return (ID == FGenericTeamId::NoTeam) ? INDEX_NONE : static_cast<uint8>(ID);
}

inline FGenericTeamId IntegerToGenericTeamId(const uint8 ID)
{
	return (ID == INDEX_NONE) ? FGenericTeamId::NoTeam : FGenericTeamId(static_cast<uint8>(ID));
}

/** Interface for actors which can be associated with teams */
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UTeamGenericTeamAgentInterface : public UGenericTeamAgentInterface
{
	GENERATED_UINTERFACE_BODY()
};

class TEAM_API ITeamGenericTeamAgentInterface : public IGenericTeamAgentInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/**  这里注意!!!委托一定要返回引用!传递委托时都应该为引用，委托也是一个对象，一堆回调函数绑定到一个特定的委托，这个委托理应为唯一的 */
	virtual FOnTeamChangedDelegateSignature& GetTeamChangedDelegateChecked()=0;

	/** 条件判断只有在OldTeam和NewTeam不相等时才Broadcast (这里是脱离Team逻辑的最后一层，所以判断是否TeamId真正改变放在这里)*/
	void ConditionalBroadcastTeamChanged(const TScriptInterface<ITeamGenericTeamAgentInterface> This, const uint8 OldTeam, const uint8 NewTeam) const;
};