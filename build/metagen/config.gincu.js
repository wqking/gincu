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
	sourceHeaderCode : '#include "gincu/gincuall.h"\n',
	sourceHeaderReplacer : [ "!.*include/gincu!i", "gincu" ],
	metaHeaderPath : "",
	
	classTraits : [
	],

	predefinedTemplateInstances : [
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
}

