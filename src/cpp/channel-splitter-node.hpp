#ifndef _CHANNEL_SPLITTER_NODE_HPP_
#define _CHANNEL_SPLITTER_NODE_HPP_


#include "common.hpp"

#include "audio-node.hpp"


class ChannelSplitterNode : public Napi::ObjectWrap<ChannelSplitterNode>, private CommonNode {
	
public:
	
	~ChannelSplitterNode();
	explicit ChannelSplitterNode(const Napi::CallbackInfo &info);
	
	static void init(Napi::Env env, Napi::Object exports);
	
	static bool isChannelSplitterNode(Napi::Object obj);
	
	// Destroy an instance from C++ land
	void _destroy();
	
	
protected:
	
	ChannelSplitterNode();
	
	static Napi::FunctionReference _constructor;
	
	bool _isDestroyed;
	
	
	
	
private:
	
	JS_METHOD(destroy);
	JS_GETTER(isDestroyedGetter);
	
	
	
};


#endif // _CHANNEL_SPLITTER_NODE_HPP_
