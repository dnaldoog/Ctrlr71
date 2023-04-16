#pragma once

#include "CtrlrMacros.h"
#include "CtrlrModulatorProcessor.h"
#include "CtrlrLuaObject.h"

typedef WeakReference <CtrlrModulator>							CtrlrModulatorReference;

#define EXP_MODULATOR_FORWARD		"modulatorValue"
#define EXP_MODULATOR_REVERSE		"midiValue"
#define EXP_MODULATOR_CONTROLLER    "value"

class CtrlrComponent;
class CtrlrManager;
class CtrlrPanel;
class CtrlrModulator;

//==============================================================================
/** @brief Class that represents a Ctrlr Modulator, this is the engine that runs under each
		component on a panel.

*/
class CtrlrModulator : public ChangeBroadcaster, public ValueTree::Listener, public CtrlrLuaObject
{
	public:
		CtrlrModulator(CtrlrPanel &_owner);
		CtrlrModulator(CtrlrPanel &_owner, const int suggestedVstIndex);
		~CtrlrModulator();

		/** @brief Get the VST/AU index this modulator uses

			@return the index of the modulator on the parameter list
		*/
		int getVstIndex() const;

		/** @brief Get the current modulator value

			@return the value of the modulator
		*/
		int getModulatorValue() const;

		/** @brief Get the current mapped modulator value

			@return the mapped value of the modulator
		*/
		int getValueMapped() const;

		/** @brief Get the current non-mapped modulator value

			@return the current non-mapped value of the modulator
		*/
		int getValueNonMapped() const;

		/** @brief Get the maximum value the modulator can have

			@return the max numeric value of the modulator
		*/
		int getMaxModulatorValue() const;

		/** @brief Get the minimum value the modulator can have

			@return the minimum numeric value of the modulator
		*/
		int getMinModulatorValue() const;

		/** @brief Get the object that represents this modulator in the UI

			@return the CtrlrComponent object that is attached to this modulator, if there isn't one nil will be returned
		*/
		CtrlrComponent *getComponent();

		/** @brief Get the restore state of the modulator

			@return true if the modulator is in restore state, otherwise false. In restore state no MIDI is transmitted
		*/
		bool getRestoreState();

		/** @brief Set the value to the modulator (uses the mapped value after the= on the value list)

			@param newValue		the value to set
			@param force		force value change
		*/
		void setValueMapped (const int newValue, const bool force, const bool mute=false);
		void setValueMappedCompat (const int newValue, const bool force);
		/** @brief Set the value to the modulator (uses the non-mapped value or the index of the value on the list)

			@param newValue		the value to set
			@param force		force value change
		*/
		void setValueNonMapped (const int newValue, const bool force, const bool mute=false);

		/** @brief Get the CtrlrMidiMessage attached to this modulator

			@return the CtrlrMidiMessage object for this modulator, this method will fail for static modulators (and will propably crash Ctrlr)
		*/
		CtrlrMidiMessage &getMidiMessage(const CtrlrMIDIDeviceType source);
		CtrlrMidiMessage &getMidiMessage();

		/** @brief Set the value to the modulator (uses the non-mapped value or the index of the value on the list)

			@param newValue		the value to set
			@param force		force value change
		*/
		void setValue(const int newValue, const bool force=false, const bool mute=false);
		void setValue(const int newValue, const bool force=false);

		/** @brief Set the restore state of the modulator

			@param _restoreState set it to true if you wan't the modulator to mute
		*/
		void setRestoreState(const bool _restoreState);

		/** @brief Get the max mapped possible value (this will be the last mapped value on the list, not the numeric MAX value)

			@param return	the max mapped value used
		*/
		int getMaxMapped();

		/** @brief Get the max non-mapped value, for a fixed component this will be the count of values on the list

			@param return	the max non-mapped value used
		*/
		int getMaxNonMapped();

		/** @brief Get the min mapped possible value (this will be the first mapped value on the list, not the numeric MIN value)

			@param return	the min mapped value used
		*/
		int getMinMapped();

		/** @brief Get the min non-mapped value, for a fixed component this will be always 0

			@param return	the min non-mapped value used
		*/
		int getMinNonMapped();

		class ModulatorListener
		{
			public:
				virtual void modulatorChanged (CtrlrModulator *source, const int newModulatorValue)=0;
				virtual ~ModulatorListener() {}
		};



		const Identifier getComponentType();
		void setModulatorValue(const int newValue, bool vst, bool midi, bool ui);
		const String getName();
		bool hasName();
		const std::string getLuaName() { return (getName().toUTF8().getAddress()); }
		float getVstValue(const int intValueToUse=-1) const;
		CtrlrMidiMessage *getMidiMessagePtr(const CtrlrMIDIDeviceType source = inputDevice);
		void restoreState (const ValueTree &savedState);
		CtrlrManager &getCtrlrManagerOwner();
		void allModulatorsInitialized();
		void setProperty (const Identifier& name, const var &newValue, const bool isUndoable=false);
		void removeProperty(const Identifier& name);
		const String getModulatorText();
		void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);
		void valueTreeChildrenChanged (ValueTree &/*treeWhoseChildHasChanged*/){}
		void valueTreeParentChanged (ValueTree &/*treeWhoseParentHasChanged*/){}
		void valueTreeChildAdded (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenAdded*/){}
		void valueTreeChildRemoved (ValueTree& /*parentTree*/, ValueTree& /*childWhichHasBeenRemoved*/, int){}
		void valueTreeChildOrderChanged (ValueTree& /*parentTreeWhoseChildrenHaveMoved*/, int, int){}
		void setComponentType (const Identifier &componentType, const bool forceIfAlreadyThisType=false);
		void setComponentType (const ValueTree &savedState);
		void setMidiType (const ValueTree &savedState);
		void modifyReference(const int newValue);
		void setReference (const String &modulatorToReference);
		CtrlrModulator *getReference();
		void setPanelReference(CtrlrPanel *referencedPanel);
		bool isDelayedProperty(const Identifier &name);
		void setDelayedProperty(const Identifier &name, const var value);
		CtrlrOwnedMidiMessage &getOwnedMidiMessage(const CtrlrMIDIDeviceType idx = inputDevice);
		static void wrapForLua (lua_State *L);
		ValueTree &getObjectTree()																		{ return (modulatorTree); }
		ValueTree &getModulatorTree()																	{ return (modulatorTree); }
		const var &getProperty (const Identifier& name) const											{ return (modulatorTree.getProperty (name)); }
		bool hasProperty(const Identifier& name) const											{ return (modulatorTree.hasProperty (name)); }
		const var getProperty (const Identifier& name, const var &defaultReturnValue) const				{ return modulatorTree.getProperty (name, defaultReturnValue); }
		CtrlrPanel &getOwnerPanel()																			{ return (owner); }
		CtrlrModulatorProcessor &getProcessor()															{ return (processor); }
		void addModulatorListener (ModulatorListener *l)													{ modulatorListeners.add(l); }
		void removeModulatorListener (ModulatorListener *l)													{ modulatorListeners.remove(l); }
		bool isExportedToVst()																		{ return (vstExported); }
		bool isStatic();
		const String getNameForHost();
		const String getTextForHost();
		const String getGroupName();

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CtrlrModulator)

	private:
		ReadWriteLock modulatorLock;
		bool restoreStateStatus;
		bool removeComponent();
		friend class WeakReference<CtrlrModulator>;
		WeakReference<CtrlrModulator>::Master masterReference;
		WeakReference<CtrlrModulator> ctrlrModulatorReference;
		WeakReference<CtrlrPanel> ctrlrPanelReference;
		uint32 vstIndex;
		CtrlrComponent *ctrlrComponent;
		CtrlrPanel &owner;
		ValueTree modulatorTree;
		ValueTree delayedProperties;
		CtrlrModulatorProcessor processor;
		ListenerList <ModulatorListener> modulatorListeners;
		bool vstExported;
};
