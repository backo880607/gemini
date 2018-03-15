#pragma once
#include "controller\BaseController.h"

struct ItemFind : public gemini::DtoBase
{
	struct Result : public gemini::DtoBase {
		DECLARE_CLASS(Result, gemini::DtoBase)
	};
	DECLARE_CLASS(ItemFind, gemini::DtoBase)

	DECLARE_FIELD(gemini::Int, value)
	DECLARE_FIELD(gemini::Double, rate)
};

class ItemController : public gemini::BaseController
{
	DECLARE_CLASS(ItemController, gemini::BaseController)
public:
	METHOD(gemini::Boolean, find, (gemini::Int value, gemini::Double rate));
};