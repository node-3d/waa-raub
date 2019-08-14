#ifndef _AUDIO_WORKLET_NODE_HPP_
#define _AUDIO_WORKLET_NODE_HPP_


#include <addon-tools.hpp>


class AudioWorkletNode : public Napi::ObjectWrap<AudioWorkletNode> {
	
public:
	
	~AudioWorkletNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioWorkletNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit AudioWorkletNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	AudioWorkletNode();
	
	static Napi::FunctionReference _ctorAudioWorkletNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _parameters;
	Napi::ObjectReference _port;
	V8_STORE_FUNC _onprocessorerror;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(parametersGetter);
	
	JS_GETTER(portGetter);
	
	JS_GETTER(onprocessorerrorGetter);
	JS_SETTER(onprocessorerrorSetter);
	
};


#endif // _AUDIO_WORKLET_NODE_HPP_