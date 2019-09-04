#ifndef _AUDIO_PROCESSING_EVENT_HPP_
#define _AUDIO_PROCESSING_EVENT_HPP_


#include "common.hpp"


class AudioProcessingEvent : public CommonNode<AudioProcessingEvent> {
	
public:
	
	~AudioProcessingEvent();
	explicit AudioProcessingEvent(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isAudioProcessingEvent(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	AudioProcessingEvent();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	double _playbackTime;
	Napi::ObjectReference _inputBuffer;
	Napi::ObjectReference _outputBuffer;
	
	
private:
	
	JS_DECLARE_METHOD(destroy);
	JS_DECLARE_GETTER(isDestroyed);
	
	
	
	JS_DECLARE_GETTER(playbackTime);
	
	JS_DECLARE_GETTER(inputBuffer);
	
	JS_DECLARE_GETTER(outputBuffer);
	
};


#endif // _AUDIO_PROCESSING_EVENT_HPP_
