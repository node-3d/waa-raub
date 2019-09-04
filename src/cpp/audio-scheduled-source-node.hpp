#ifndef _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
#define _AUDIO_SCHEDULED_SOURCE_NODE_HPP_

#include "common.hpp"

#include "audio-node.hpp"


class AudioScheduledSourceNode : public CommonNode<AudioScheduledSourceNode> {
	
public:
	
	static void init(Napi::Env env, Napi::Object exports);
	static Napi::Object create(Napi::Env env, Napi::Object context);
	
	explicit AudioScheduledSourceNode(const Napi::CallbackInfo &info);
	~AudioScheduledSourceNode();
	
	void _destroy();
	
private:
	
	static Napi::FunctionReference _constructor;
	
	void onEnded();
	
	JS_DECLARE_METHOD(destroy);
	
	JS_DECLARE_METHOD(start);
	JS_DECLARE_METHOD(stop);
	
};


#endif // _AUDIO_SCHEDULED_SOURCE_NODE_HPP_
