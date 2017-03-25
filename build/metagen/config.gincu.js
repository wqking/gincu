var config = {
	projectID : "gincu",

	headerOutput : "../../metagen",
	sourceOutput : "../../metagen",
	
	metaItemCallback : processCallback,
	
	cppNamespace : "meta_gincu",
	
	metaClassFunctionPrefix : "buildMetaClass_",
	metaClassCreatePrefix : "createMetaClass_",

	metaClassMainRegisterPrefix : "registerMain_",

	sourceFilePrefix : "meta_gincu",
	mainSourceFile : "register_meta_gincu",

	autoRegisterToGlobal : true,

	wrapBitField : true, // default is true
	wrapOperator : true, // default is true 

	metaNamespace : "gincu",
	sourceHeaderCode : '#include "gincu/gincuall.h"\n'
		+ '#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"',
	sourceHeaderReplacer : [ "!.*include/gincu!i", "gincu" ],
	metaHeaderPath : "",
	
	classTraits : [
	],

	predefinedTemplateInstances : [
		// These are used as the base class of GComponentTransform and GComponentLocalTransform
		// we must define these instantiations to make those two classes work.
		"GComponentTransformBase<GComponentTransform>", "",
		"GComponentTransformBase<GComponentLocalTransform>", "",
	]
};

var ignoredItemNames = [
	"GEntityDynamicArrayBase",
	"GEntityDynamicArray",
	"GEntityDynamicMap",
	"GEntityStaticArray",
	"GEntityMixedArray",
	"GEntityMixedMap",
	"GEntityStoragePolicySelector",
	"GHeapPool",
	"GHeapSizedPool",
	"defaultColor",
];

var wrapperClassNames = {
	GApplication : 1,
	GComponent : 1,
	GScene : 1,
};

var parameterFromEndIndex = 1000;
var transferOwnerShipParameters = {
	addEntity : 0,
	addComponent : 0,
	switchScene : parameterFromEndIndex + 1,
};


function normalizeParameterIndex(item, index)
{
	if(index >= parameterFromEndIndex) {
		return item.getParameterCount() - 1 - (index - parameterFromEndIndex);
	}
	else {
		return index;
	}
}

function processCallback(item, data)
{
	if(item.isConstant()) {
		data.skipBind = true;
	}
	
	var owner = item.getOwner();

	if(item.isField()) {
		if(owner != null && owner.getPrimaryName() == "GEvent") {
			data.skipBind = true;
		}
	}
	
	var itemName = item.getPrimaryName();
	
	for each(name in ignoredItemNames) {
		if(itemName.match(name)) {
			data.skipBind = true;
			break;
		}
	}
	
	if(itemName == "asyncGetImage" || itemName == "asyncGetFont") {
		item.setParameterDefaultValueAt(-1, "GResourceManager::LoaderCallback()");
	}
	
	if(owner != null && owner.getPrimaryName() == "GVertexArray") {
		if(itemName == "setAt" || itemName == "append") {
			item.setParameterDefaultValueAt(-2, "GVertexArray::defaultColor");
		}
	}

	if(item.isClass()) {
		if(wrapperClassNames[itemName]) {
			data.getWrapperConfig().setWrapClass(true);
		}
	}
	
	if(transferOwnerShipParameters.hasOwnProperty(itemName)) {
		var indexes = transferOwnerShipParameters[itemName];
		if(indexes instanceof Array) {
			for(var i = 0; i < indexes.length; ++i) {
				item.addPolicyRule("GMetaRuleTransferOwnership<" + normalizeParameterIndex(item, indexes[i]) + ">");
			}
		}
		else {
			item.addPolicyRule("GMetaRuleTransferOwnership<" + normalizeParameterIndex(item, indexes) + ">");
		}
	}
	
	if(item.isConstructor()) {
		if(owner.getPrimaryName() == "GComponentFrameAnimation") {
			if(item.getParameterCount() > 0) {
				item.addPolicyRule("GMetaRuleTransferOwnership<0>");
			}
		}
	}
}

