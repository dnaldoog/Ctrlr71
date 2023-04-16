#ifndef __CTRLR_PANEL_RESOURCE_MANAGER__
#define __CTRLR_PANEL_RESOURCE_MANAGER__

#include "CtrlrModulator/CtrlrModulator.h"

class CtrlrPanel;
class CtrlrPanelResource;

//==============================================================================
/** The resource manager class, loads resources when needed, deletes resource files
	copies new resources to the resource directory

*/
class CtrlrPanelResourceManager
{
	public:
		CtrlrPanelResourceManager(CtrlrPanel &_owner);
		~CtrlrPanelResourceManager();
		int getNumResources();

		CtrlrPanelResource *getResource (const int resourceIndex);
		CtrlrPanelResource *getResource (const String &resourceName);

		const Image getResourceAsImage (const String &resourceName);
		const Font getResourceAsFont (const String &resourceName);
		void reloadComboContents (ComboBox &comboToUpdate);
		int getHashCode (const String &resourceName, const bool preloadResource=false);
		int getResourceIndex (const String &resourceName);

		Result removeResourceRange (const int resourceIndexStart, const int numberOfResourcesToRemove);
		Result removeResource (const int resourceIndex);
		Result removeResource(CtrlrPanelResource *resourceToRemove);
		Result addResource (const File &source, const String &name="");
		Result importResource (const ValueTree &resourceTree);

		void panelUIDChanged();
		int getResourceIndexByHashCode(const int hashCode);
		int getResourceHashCode(const int resourceIndex);
		const File getResourcesDirectory()	{ return (resourcesDirectory); }
		void initManager();
		void checkMissingResources(ValueTree& panelResourcesTree);
		bool resourceExists(const File &resourceFile);
		CtrlrPanel &getOwner();
		static const String getTypeDescription(const CtrlrPanelResourceType type);
		CtrlrPanelResourceType guessType(const File &resourceFile);
		static void wrapForLua(lua_State *L);
		Result restoreState (const ValueTree &savedState);
		Array <CtrlrPanelResource*> getResourcesCopy();
		ValueTree &getManagerTree() { return (managerTree); }
		void restoreSavedState (const ValueTree &savedState);

		JUCE_LEAK_DETECTOR(CtrlrPanelResourceManager)

	private:
		WeakReference <CtrlrPanelResource> lastLoadedResource;
		Array <int> resourceHashCodes;
		CtrlrPanel &owner;
		File resourcesDirectory;
		OwnedArray <CtrlrPanelResource> resources;
		ValueTree managerTree;
};
#endif
