
#include "audio-worklet-processor.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioWorkletProcessor::AudioWorkletProcessor() {
	
	_isDestroyed = false;
	
}


AudioWorkletProcessor::~AudioWorkletProcessor() {
	
	_destroy();
	
}


void AudioWorkletProcessor::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props



JS_GETTER(AudioWorkletProcessor::portGetter) { THIS_CHECK;
	
	RET_VALUE(_port.Value());
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference AudioWorkletProcessor::_constructor;


void AudioWorkletProcessor::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(port);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("AudioWorkletProcessor", ctor);
	
}


bool AudioWorkletProcessor::isAudioWorkletProcessor(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object AudioWorkletProcessor::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioWorkletProcessor::AudioWorkletProcessor(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioWorkletProcessor>(info) {
	
	AudioWorkletProcessor *audioWorkletProcessor = new AudioWorkletProcessor();
	
}


JS_METHOD(AudioWorkletProcessor::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletProcessor::isDestroyedGetter) { NAPI_ENV;
	
	RET_BOOL(_isDestroyed);
	
}
