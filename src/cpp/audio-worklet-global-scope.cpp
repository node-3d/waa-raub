
#include "audio-worklet-global-scope.hpp"

#include "common.hpp"


// ------ Constructor and Destructor

AudioWorkletGlobalScope::AudioWorkletGlobalScope() {
	
	_isDestroyed = false;
	
}


AudioWorkletGlobalScope::~AudioWorkletGlobalScope() {
	
	_destroy();
	
}


void AudioWorkletGlobalScope::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
}


// ------ Methods and props


JS_METHOD(AudioWorkletGlobalScope::registerProcessor) { THIS_CHECK;
	
	REQ_UTF8_ARG(0, name);
	REQ_FUN_ARG(1, processorConstructor);
	
	// TODO: do something?
	
}


JS_GETTER(AudioWorkletGlobalScope::currentFrameGetter) { THIS_CHECK;
	
	RET_VALUE(JS_OFFS(_currentFrame));
	
}


JS_GETTER(AudioWorkletGlobalScope::currentTimeGetter) { THIS_CHECK;
	
	RET_NUM(_currentTime);
	
}


JS_GETTER(AudioWorkletGlobalScope::sampleRateGetter) { THIS_CHECK;
	
	RET_NUM(_sampleRate);
	
}


// ------ System methods and props for Napi::ObjectWrap

Napi::FunctionReference AudioWorkletGlobalScope::_constructor;


void AudioWorkletGlobalScope::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(registerProcessor);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(sampleRate);
	JS_ASSIGN_GETTER(currentTime);
	JS_ASSIGN_GETTER(currentFrame);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("AudioWorkletGlobalScope", ctor);
	
}


bool AudioWorkletGlobalScope::isAudioWorkletGlobalScope(Napi::Object obj) {
	return obj.InstanceOf(_constructor.Value());
}


Napi::Object AudioWorkletGlobalScope::getNew() {
	
	Napi::Function ctor = Nan::New(_constructor);
	// Napi::Value argv[] = { /* arg1, arg2, ... */ };
	return Nan::NewInstance(ctor, 0/*argc*/, nullptr/*argv*/).ToLocalChecked();
	
}


AudioWorkletGlobalScope::AudioWorkletGlobalScope(const Napi::CallbackInfo &info): Napi::ObjectWrap<AudioWorkletGlobalScope>(info) {
	
	AudioWorkletGlobalScope *audioWorkletGlobalScope = new AudioWorkletGlobalScope();
	
}


JS_METHOD(AudioWorkletGlobalScope::destroy) { THIS_CHECK;
	
	_destroy();
	
}


JS_GETTER(AudioWorkletGlobalScope::isDestroyedGetter) { NAPI_ENV;
	
	THIS_AUDIO_WORKLET_GLOBAL_SCOPE;
	
	RET_BOOL(_isDestroyed);
	
}
