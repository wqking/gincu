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
	sourceHeaderCode : "",
	sourceHeaderReplacer : [ "!.*include/gincu!i", "gincu" ],
	metaHeaderPath : "",
	
	classTraits : [
//		{ pattern : "GApplication", traits : { copyConstructorHidden : true }  },
	],

	predefinedTemplateInstances : [
	]
};

var re_Win32 = new RegExp("(.*)/Win32/(.*)", "i");

function processCallback(item, data)
{
}

