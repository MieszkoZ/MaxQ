// Copyright 2021 Gamergenic.  See full copyright notice in Spice.h.
// Author: chucknoble@gamergenic.com | https://www.gamergenic.com
// 
// Project page:   https://www.gamergenic.com/project/maxq/
// Documentation:  https://maxq.gamergenic.com/
// GitHub:         https://github.com/Gamergenic1/MaxQ/ 

//------------------------------------------------------------------------------
// SpiceUncooked
// K2 Node Compilation
// See comments in Spice/SpiceK2.h.
//------------------------------------------------------------------------------


#pragma once

#include "K2Node_TwoInOneOut.h"
#include "K2Node_vsub.generated.h"

#pragma once

UCLASS(BlueprintType, Blueprintable)
class SPICEUNCOOKED_API UK2Node_vsub : public UK2Node_TwoInOneOut
{
    GENERATED_BODY()

    UK2Node_vsub();

public:
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
    virtual FText GetMenuCategory() const override;
    virtual FText GetKeywords() const override;
    virtual FText GetTooltipText() const override;

protected:
    virtual const TArray<FK2Type>& GetSupportedTypes() const override;
    virtual const TArray<OperationType>& GetSupportedOperations() const override;
};


