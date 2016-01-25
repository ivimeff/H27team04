#pragma once

#include "GenericControll.h"
#include "IEffectMediator.h"

class EffectManager : public GenericControll<Effect>, IEffectMediator
{

};