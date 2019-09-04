
#include "stereo-panner-node.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

StereoPannerNode::StereoPannerNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


StereoPannerNode::~StereoPannerNode() {
	
	_destroy();
	
}


void StereoPannerNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(StereoPannerNode::panGetter) { THIS_CHECK;
	
	RET_VALUE(_pan.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference StereoPannerNode::_constructor;


void StereoPannerNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(pan);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("StereoPannerNode", ctor);
	
}


bool StereoPannerNode::isStereoPannerNode(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object StereoPannerNode::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


StereoPannerNode::StereoPannerNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<StereoPannerNode>(info) {
	
	StereoPannerNode *stereoPannerNode = new StereoPannerNode();
	
}


JS_METHOD(StereoPannerNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(StereoPannerNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
