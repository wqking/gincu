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
		+ '#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"\n'
	,
	sourceHeaderReplacer : [
		"!.*include/gincu!i", "gincu",
		'!.*include/cpgf!i', 'cpgf'
	],
	metaHeaderPath : "",
	
	classTraits : [
		{ pattern : ".*\\b[io]stream$", traits : { copyConstructorHidden : true }  },
		{ pattern : ".*\\bw?string$", traits : { hasTypeConvertConstructor : true }  },
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

	// cpgf accessor/tween meta data

	var location = item.getLocation();
	if(location.indexOf('cpgf') >= 0 && location.indexOf('tween') >= 0) {
		data.addHeaderInclude("cpgf/tween/gtimeline.h");
		data.addHeaderInclude("cpgf/accessor/gaccessor.h");
		data.addHeaderInclude("cpgf/gselectfunctionbyarity.h");
	}
	
	if(item.isConstant() || item.isOperator()) {
		data.skipBind = true;
	}
	
	if(itemName == 'repeat') {
		data.addAlias('_repeat');
	}
	
	if(owner != null) {
		var ownerName = owner.getPrimaryName();
		if(ownerName == "GTween") {
			if(itemName == 'target' && item.getParameterCount() == 3) {
				var accessorTypeList = [
					'cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<float ()> >, cpgf::GSetter<cpgf::GCallback<void (float)> > > ',
				];
				var namePostfixList = [
					'Float',
				];
				var protoList = [
					'target', 'relative' //, 'follow'
				];

				for each(var proto in protoList) {
					for(var i = 0; i < accessorTypeList.length; ++i) {
						var name = proto + namePostfixList[i];
						var type = accessorTypeList[i];

						data.addRawCode(
							'_d.CPGF_MD_TEMPLATE _method("' + name + '", '
								+ 'cpgf::selectFunctionByArity2(&D::ClassType::template ' + proto + '<' + type + '>));'
						);
						data.addRawCode(
							'_d.CPGF_MD_TEMPLATE _method("' + name + '", '
								+ 'cpgf::selectFunctionByArity3(&D::ClassType::template ' + proto + '<' + type + '>));'
						);
					}
				}
			}
		}
	}
}

