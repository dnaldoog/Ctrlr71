#include "stdafx.h"
#include "CtrlrComponentSelection.h"
#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"
#include "CtrlrComponents/CtrlrComponent.h"
#include "CtrlrMidiMessage.h"

CtrlrComponentSelection::CtrlrComponentSelection(CtrlrPanelEditor &_owner) : owner(_owner)
{
}

CtrlrComponentSelection::~CtrlrComponentSelection()
{
}

void CtrlrComponentSelection::itemSelected (CtrlrComponent *selectedComponent)
{
	if (!selectedComponent->getTransform().isIdentity())
	{
		selectedComponent->setTransform (AffineTransform());
	}
}

void CtrlrComponentSelection::itemDeselected (CtrlrComponent *deselectedComponent)
{
	if (!deselectedComponent->getTransform().isIdentity())
	{
		deselectedComponent->setTransform (AffineTransform());
	}
}

void CtrlrComponentSelection::deselectAll()
{
	for (int i=0; i<getNumSelected(); i++)
	{
		if (getSelectedItem(i))
		{
			getSelectedItem(i)->setTransform (AffineTransform());
		}
	}
	SelectedItemSet<CtrlrComponent*>::deselectAll();
}
