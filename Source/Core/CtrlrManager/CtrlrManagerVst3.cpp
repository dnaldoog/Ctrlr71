#include "stdafx.h"
#include "CtrlrManagerVst3.h"
#include "CtrlrIDs.h"
#include "CtrlrLog.h"
#include "CtrlrManager.h"

CtrlrManagerVst3::CtrlrManagerVst3(CtrlrManager& _owner) : owner(_owner)
{
	_DBG("CtrlrManagerVst3::ctor");
}

CtrlrManagerVst3::~CtrlrManagerVst3()
{
	_DBG("CtrlrManagerVst3::dtor");
}

int CtrlrManagerVst3::size()
{
	return ((int)map.size());
}

void CtrlrManagerVst3::remove(CtrlrModulator* mod)
{
	removeIfAlreadyThere(mod);
}

void CtrlrManagerVst3::set(CtrlrModulator* mod, const int idx)
{
	if ((bool)mod->getProperty(Ids::modulatorVstExported) == false)
	{
		return;
	}

	if (isAlreadyIndexed(mod) && idx == -1)
	{
		return;
	}

	removeIfAlreadyThere(mod);
	vstIndexes.addUsingDefaultSort(idx);
	map.insert(CtrlrVstPair(idx, mod));
}

bool CtrlrManagerVst3::isAlreadyIndexed(CtrlrModulator* mod)
{
	for (CtrlrVstMapIterator it = map.begin(); it != map.end(); ++it)
	{
		if (it->second == mod)
		{
			return (true);
		}
	}
	return (false);
}

void CtrlrManagerVst3::removeIfAlreadyThere(CtrlrModulator* mod)
{
	for (CtrlrVstMapIterator it = map.begin(); it != map.end(); ++it)
	{
		if (it->second == mod)
		{
			vstIndexes.removeFirstMatchingValue(it->first);
			map.erase(it);
			return;
		}
	}
}

CtrlrModulator* CtrlrManagerVst3::get(const int idx)
{
	CtrlrVstMapIterator it = map.find(idx);

	if (it != map.end())
	{
		return (it->second);
	}
	else
	{
		return (nullptr);
	}
}

int CtrlrManagerVst3::getFirstFree()
{
	/* kamder fix */
	if (vstIndexes.size() == 0)
		return (0);

	return (vstIndexes.getLast() + 1);
}

int CtrlrManagerVst3::getLargestIndex()
{
	return (vstIndexes.getLast());
}

void CtrlrManagerVst3::dumpDebugData()
{
	_DBG("CtrlrManagerVst3::dumpDebugData");

	_DBG("---------- modulators by vst indexes ----------");

	for (CtrlrVstMapIterator it = map.begin(); it != map.end(); ++it)
	{
		_DBG("[" + STR(it->first) + "]: " + it->second->getName());
	}

	_DBG("\t largest index " + STR(getLargestIndex()));
	_DBG("---------- modulators by vst indexes ----------");
}
