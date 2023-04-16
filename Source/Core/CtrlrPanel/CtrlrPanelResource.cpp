#include "stdafx.h"
#include "CtrlrPanelResource.h"
#include "CtrlrPanelResourceManager.h"
#include "CtrlrMacros.h"
#include "CtrlrProcessor.h"
#include "CtrlrPanel.h"
#include "CtrlrUtilities.h"
#include "CtrlrLog.h"

/** Single resource representation

*/

CtrlrPanelResource::CtrlrPanelResource (CtrlrPanelResourceManager &_owner, const File &_resourceDataFile, const File &_resourceSourceFile, const String _resourceName)
	: 	resourceDataFile(_resourceDataFile),
		resourceHashCode(0),
		resourceLoaded(false),
		owner(_owner),
		resourceName(_resourceName),
		audioFormatReader(nullptr),
		resourceTree(Ids::resource)
{
	if (resourceName == "")
	{
		resourceName = _resourceSourceFile.getFileNameWithoutExtension();
	}

	resourceHashCode	= _resourceSourceFile.hashCode();
	resourceType		= owner.guessType (_resourceSourceFile);

	load();

	setProperty (Ids::resourceFile, resourceDataFile.getFileName(), false);
	setSourceFile(_resourceSourceFile);
	setProperty (Ids::resourceName, getName(), false);
	setProperty (Ids::resourceSize, getSize(), false);
	setProperty (Ids::resourceType, CtrlrPanelResourceManager::getTypeDescription(getType()), false);

	resourceTree.addListener(this);
}

CtrlrPanelResource::~CtrlrPanelResource()
{
	resourceTree.removeListener (this);

	if (audioFormatReader)
		deleteAndZero (audioFormatReader);

	masterReference.clear();
}

void CtrlrPanelResource::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	// _DBG("CtrlrPanelResource::valueTreePropertyChanged");
	// _DBG("\t"+property.toString()+"="+getProperty(property).toString());
}

File &CtrlrPanelResource::getFile()
{
	return (resourceDataFile);
}

int64 CtrlrPanelResource::getSize()
{
	return (resourceDataFile.getSize());
}

double CtrlrPanelResource::getSizeDouble()
{
	return ((double)getSize());
}

int64 CtrlrPanelResource::getHashCode()
{
	return (getProperty(Ids::resourceHash));
}

const String CtrlrPanelResource::getName()
{
	return (resourceName);
}

const Image CtrlrPanelResource::asImage()
{
	Image image;

	image = ImageCache::getFromHashCode(getHashCode());

	if (!image.isValid())
	{
		image = ImageFileFormat::loadFrom (resourceDataFile);
		ImageCache::addImageToCache (image, getHashCode());
	}

	return (image);
}

const String CtrlrPanelResource::asText()
{
	return (resourceDataFile.loadFileAsString());
}

const Font CtrlrPanelResource::asFont()
{
    MemoryBlock tempData;
    resourceDataFile.loadFileAsData (tempData);
    return (Font (Typeface::createSystemTypefaceFor (tempData.getData(), tempData.getSize())));
}

const XmlElement *CtrlrPanelResource::asXml()
{
	return (XmlDocument::parse(resourceDataFile).release());
}

AudioFormatReader *CtrlrPanelResource::asAudioFormat()
{
	if (audioFormatReader)
	{
		deleteAndZero (audioFormatReader);
	}

	audioFormatReader = owner.getOwner().getCtrlrManagerOwner().getAudioFormatManager().createReaderFor(resourceDataFile);
	return (audioFormatReader);
}

const MemoryBlock &CtrlrPanelResource::asData()
{
	loadIfNeeded();
	return (data);
}

bool CtrlrPanelResource::isLoaded()
{
	return (resourceLoaded);
}

void CtrlrPanelResource::loadIfNeeded()
{
	if (!resourceLoaded)
		load();
}

void CtrlrPanelResource::calculateHash()
{
	setProperty (Ids::resourceHash, resourceDataFile.hashCode64() + resourceDataFile.getLastModificationTime().toMilliseconds());
}

void CtrlrPanelResource::load()
{
	calculateHash();

	if (resourceLoaded || resourceType == ImageRes)
	{
		// ImageCache deals with that
	}
	else if (resourceType == AudioRes
			|| resourceType == XmlRes
			|| resourceType == TextRes
			|| resourceType ==FontRes)
	{
		// We don't load theese types, they will be rad when accessed
	}
	else if (resourceType == DataRes)
	{
		// Theese types go into memory

		resourceDataFile.loadFileAsData (data);
	}

	setProperty (Ids::resourceLoadedTime, Time::getCurrentTime().toMilliseconds());
	setProperty (Ids::resourceSize, resourceDataFile.getSize());

	resourceLoaded = true;
}

Time CtrlrPanelResource::getLoadedTime()
{
	return (Time((int64)getProperty(Ids::resourceLoadedTime)));
}

ValueTree CtrlrPanelResource::createTree()
{
	ValueTree resourceTreeCopy;

	if (resourceDataFile.existsAsFile())
	{
		resourceTreeCopy = resourceTree.createCopy();

		if (data.getSize() != (size_t)resourceDataFile.getSize())
			resourceDataFile.loadFileAsData (data);

		resourceTreeCopy.setProperty (Ids::resourceData, data.toBase64Encoding(), 0);
	}

	return (resourceTreeCopy);
}

CtrlrPanelResourceType CtrlrPanelResource::getType()
{
	return (resourceType);
}

File CtrlrPanelResource::getSourceFile()
{
	String resourceSourcePath = getProperty(Ids::resourceSourceFile);
	if (File::isAbsolutePath(resourceSourcePath))
	{
		return (File(resourceSourcePath));
	}
	else
	{
		return (owner.getOwner().getPanelResourcesDir().getChildFile(resourceSourcePath));
	}
}

void CtrlrPanelResource::setSourceFile(const File &sourceFile)
{
	File panelResourceDir = owner.getOwner().getPanelResourcesDir();
	if (sourceFile.isAChildOf(panelResourceDir))
	{
		setProperty(Ids::resourceSourceFile, sourceFile.getRelativePathFrom(panelResourceDir), false);
	}
	else
	{
		setProperty(Ids::resourceSourceFile, sourceFile.getFullPathName(), false);
	}

}

const String CtrlrPanelResource::getTypeDescription()
{
	return (CtrlrPanelResourceManager::getTypeDescription(getType()));
}

ValueTree &CtrlrPanelResource::getResourceTree()
{
	return (resourceTree);
}

void CtrlrPanelResource::setProperty (const Identifier& name, const var &newValue, const bool isUndoable)
{
	resourceTree.setProperty (name, newValue, nullptr);
}

bool CtrlrPanelResource::reloadFromSourceFile()
{
	if (getSourceFile().existsAsFile())
	{
		if (getSourceFile().copyFileTo (resourceDataFile))
		{
			resourceLoaded = false;
			load();
		}
	}

	return (true);
}
