#ifndef _OFFLINE_AUDIO_CONTEXT_HPP_
#define _OFFLINE_AUDIO_CONTEXT_HPP_


#include <addon-tools.hpp>

#include "base-audio-context.hpp"


class OfflineAudioContext : public BaseAudioContext {
	
public:
	
	~OfflineAudioContext();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isOfflineAudioContext(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit OfflineAudioContext(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	OfflineAudioContext();
	
	static Napi::FunctionReference _ctorOfflineAudioContext;
	
	bool _isDestroyed;
	
	V8_STORE_FUNC _oncomplete;
	uint32_t _length;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	JS_METHOD(startRendering);
	JS_METHOD(suspend);
	
	JS_GETTER(oncompleteGetter);
	JS_SETTER(oncompleteSetter);
	
	JS_GETTER(lengthGetter);
	
};


#endif // _OFFLINE_AUDIO_CONTEXT_HPP_
