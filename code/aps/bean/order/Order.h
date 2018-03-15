#pragma once
#include "../../common/Export.h"

namespace aps {

class Work;
class Item;
class APS_API Order : public gemini::EntityObject
{
#define MODULE_API APS_API
	DECLARE_CLASS(Order, gemini::EntityObject)
public:
	Order();
	~Order();

	DECLARE_ENTITY(Item, item)
	DECLARE_VECTOR(Work, works)
};

}