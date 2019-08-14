
#include "media-element-audio-source-node.hpp"

#include "common.hpp"


// ------ Aux macros

	Nan::ObjectWrap::Unwrap<MediaElementAudioSourceNode>(info.This());


// ------ Constructor and Destructor

MediaElementAudioSourceNode::MediaElementAudioSourceNode() :
AudioNode() {
	
	_isDestroyed = false;
	
}


MediaElementAudioSourceNode::~MediaElementAudioSourceNode() {
	
	_destroy();
	
}


void MediaElementAudioSourceNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(MediaElementAudioSourceNode::mediaElementGetter) {
	
	THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	RET_VALUE(__mediaElement.Value());
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference MediaElementAudioSourceNode::_ctorMediaElementAudioSourceNode;


void MediaElementAudioSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "MediaElementAudioSourceNode", {
		ACCESSOR_M(MediaElementAudioSourceNode, destroy),
		ACCESSOR_R(MediaElementAudioSourceNode, mediaElement),
		ACCESSOR_R(MediaElementAudioSourceNode, isDestroyed),
	
	});
	
	_ctorMediaElementAudioSourceNode = Napi::Persistent(ctor);
	_ctorMediaElementAudioSourceNode.SuppressDestruct();
	
	exports.Set("MediaElementAudioSourceNode", ctor);
	
}


bool MediaElementAudioSourceNode::isMediaElementAudioSourceNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorMediaElementAudioSourceNode.Value());
}


Napi::Object MediaElementAudioSourceNode::getNew() {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorMediaElementAudioSourceNode);
	// V8_VAR_VAL argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


MediaElementAudioSourceNode::MediaElementAudioSourceNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<MediaElementAudioSourceNode>(info) {
	
	CTOR_CHECK("MediaElementAudioSourceNode");
	
	MediaElementAudioSourceNode *mediaElementAudioSourceNode =
		new MediaElementAudioSourceNode();
	
}


JS_METHOD(MediaElementAudioSourceNode::destroy) {
	
	THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE; THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(MediaElementAudioSourceNode::isDestroyedGetter) {
	
	THIS_MEDIA_ELEMENT_AUDIO_SOURCE_NODE;
	
	RET_BOOL(_isDestroyed);
	
}