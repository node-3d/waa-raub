#ifndef _WAVE_SHAPER_NODE_HPP_
#define _WAVE_SHAPER_NODE_HPP_


#include <addon-tools.hpp>

#include "audio-node.hpp"


class WaveShaperNode : public AudioNode {
	
public:
	
	~WaveShaperNode();
	
	// Public V8 init
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isWaveShaperNode(Napi::Object obj);
	
	// Make a new instance from C++ land
	explicit WaveShaperNode(const Napi::CallbackInfo& info);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
// Methods and props, available for children
protected:
	
	WaveShaperNode();
	
	static Napi::FunctionReference _ctorWaveShaperNode;
	
	bool _isDestroyed;
	
	Napi::ObjectReference _curve;
	std::string _oversample;
	
	
// JS methods and props, available through V8 APIs
private:
	
	JS_METHOD(newCtor);
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
	JS_GETTER(curveGetter);
	JS_SETTER(curveSetter);
	
	JS_GETTER(oversampleGetter);
	JS_SETTER(oversampleSetter);
	
};


#endif // _WAVE_SHAPER_NODE_HPP_