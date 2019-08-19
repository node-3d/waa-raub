#include <LabSound/core/AudioContext.h>
#include <LabSound/core/ConvolverNode.h>

#include "convolver-node.hpp"
#include "audio-context.hpp"
#include "audio-buffer.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

ConvolverNode::ConvolverNode(Napi::Object context) :
AudioNode(context, NodePtr(new lab::ConvolverNode())) {
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(_impl.get());
	
	_isDestroyed = false;
	
}


ConvolverNode::~ConvolverNode() {
	
	_destroy();
	
}


void ConvolverNode::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props



JS_GETTER(ConvolverNode::bufferGetter) { THIS_CHECK;
	
	RET_VALUE(_buffer.Value());
	
}

JS_SETTER(ConvolverNode::bufferSetter) { THIS_CHECK; SETTER_OBJ_ARG;
	
	if (Nan::New(_buffer) == v) {
		return;
	}
	
	_buffer.Reset(v);
	
	Napi::Object context = _context.Value();
	AudioContext *audioContext = Napi::ObjectWrap<AudioContext>::Unwrap(context);
	
	lab::AudioContext *ctx = audioContext->getCtx().get();
	
	AudioBuffer *audioBuffer = Napi::ObjectWrap<AudioBuffer>::Unwrap(v);
	AudioBuffer::BusPtr bus = audioBuffer->getBus();
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		_impl.get()
	);
	node->setImpulse(bus);
	
	emit(env, "buffer", 1, &value);
	
}


JS_GETTER(ConvolverNode::normalizeGetter) { THIS_CHECK;
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		_impl.get()
	);
	
	RET_BOOL(node->normalize());
	
}

JS_SETTER(ConvolverNode::normalizeSetter) { THIS_CHECK; SETTER_BOOL_ARG;
	
	lab::ConvolverNode *node = static_cast<lab::ConvolverNode*>(
		_impl.get()
	);
	
	node->setNormalize(v);
	
	emit(env, "normalize", 1, &value);
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference ConvolverNode::_constructor;


void ConvolverNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "ConvolverNode", {
		ACCESSOR_RW(ConvolverNode, normalize),
		ACCESSOR_RW(ConvolverNode, buffer),
		ACCESSOR_M(ConvolverNode, destroy),
		ACCESSOR_R(ConvolverNode, isDestroyed)
	});
	
	_constructor = Napi::Persistent(ctor);
	_constructor.SuppressDestruct();
	
	exports.Set("ConvolverNode", ctor);
	
}


Napi::Object ConvolverNode::getNew(Napi::Object context) {
	
	Napi::Function ctor = Nan::New(_constructor);
	Napi::Value argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


ConvolverNode::ConvolverNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<ConvolverNode>(info) {
	
	CTOR_CHECK("ConvolverNode");
	
	REQ_OBJ_ARG(0, context);
	
	ConvolverNode *convolverNode = new ConvolverNode(context);
	
}


JS_METHOD(ConvolverNode::destroy) { THIS_CHECK;
	
	emit(env, "destroy");
	
	_destroy();
	
}


JS_GETTER(ConvolverNode::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
