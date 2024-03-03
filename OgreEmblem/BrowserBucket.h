#pragma once
#include "Cursor.h"

struct BrowserBucket
{
public:
	BrowserBucket() {};
	BrowserBucket(bool ap, Cursor crs) { cursor = crs, actionPerformed = ap; };
	bool actionPerformed = false;
	Cursor cursor;
};