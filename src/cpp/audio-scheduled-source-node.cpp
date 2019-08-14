#include <LabSound/core/AudioScheduledSourceNode.h>

#include "audio-scheduled-source-node.hpp"

#include "common.hpp"


// ------ Aux macros

		Nan::ObjectWrap::Unwrap<AudioScheduledSourceNode>(info.This());


// ------ Constructor and Destructor

AudioScheduledSourceNode::AudioScheduledSourceNode(Napi::Object context, NodePtr node) :
AudioNode(context, node) {
	
	node->setOnEnded(std::bind(&AudioScheduledSourceNode::onEnded, this));
	
	_isDestroyed = false;
	
}


AudioScheduledSourceNode::~AudioScheduledSourceNode() {
	
	_destroy();
	
}


void AudioScheduledSourceNode::onEnded() { NAN_HS;
	
	emit("ended");
	
}


void AudioScheduledSourceNode::_destroy() { DES_CHECK;
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->setOnEnded(nullptr);
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


JS_METHOD(AudioScheduledSourceNode::start) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->start(when);
	
}


JS_METHOD(AudioScheduledSourceNode::stop) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->stop(when);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference AudioScheduledSourceNode::_ctorAudioScheduledSourceNode;


void AudioScheduledSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "AudioScheduledSourceNode", {
		ACCESSOR_M(AudioScheduledSourceNode, stop),
		ACCESSOR_M(AudioScheduledSourceNode, start),
		ACCESSOR_M(AudioScheduledSourceNode, destroy),
		ACCESSOR_R(AudioScheduledSourceNode, isDestroyed),
	
	});
	
	_ctorAudioScheduledSourceNode = Napi::Persistent(ctor);
	_ctorAudioScheduledSourceNode.SuppressDestruct();
	
	exports.Set("AudioScheduledSourceNode", ctor);
	
}


Napi::Object AudioScheduledSourceNode::getNew(Napi::Object context, NodePtr node) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorAudioScheduledSourceNode);
	V8_VAR_EXT extNode = JS_EXT(&node);
	V8_VAR_VAL argv[] = { context, extNode };
	return Nan::NewInstance(ctor, 2, argv).ToLocalChecked();
	
}


AudioScheduledSourceNode::AudioScheduledSourceNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioScheduledSourceNode>(info) {
	
	CTOR_CHECK("AudioScheduledSourceNode");
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	NodePtr *node = reinterpret_cast<NodePtr *>(extNode->Value());
	
	AudioScheduledSourceNode *audioScheduledSourceNode = new AudioScheduledSourceNode(context, *node);
	
}


JS_METHOD(AudioScheduledSourceNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(AudioScheduledSourceNode::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}