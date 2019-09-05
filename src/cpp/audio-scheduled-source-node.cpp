#include <LabSound/LabSound.h>

#include "audio-scheduled-source-node.hpp"


IMPLEMENT_ES5_CLASS(AudioScheduledSourceNode);

void AudioScheduledSourceNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(stop);
	JS_ASSIGN_METHOD(start);
	JS_ASSIGN_METHOD(destroy);
	
	exports.Set("AudioScheduledSourceNode", ctor);
	
}


AudioScheduledSourceNode::AudioScheduledSourceNode(const Napi::CallbackInfo &info):
CommonNode<AudioScheduledSourceNode>(info, "AudioScheduledSourceNode") { NAPI_ENV;
	
	REQ_OBJ_ARG(0, context);
	REQ_EXT_ARG(1, extNode);
	
	NodePtr *ext = reinterpret_cast<NodePtr *>(extNode.Data());
	
	reset(context, *ext);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->setOnEnded(std::bind(&AudioScheduledSourceNode::onEnded, this));
	
	Napi::Value argv[] = {
		static_cast<Napi::Value>(context),
		static_cast<Napi::Value>(JS_NUM(reinterpret_cast<size_t>(&_impl)))
	};
	super(info, 2, argv);
	
}


AudioScheduledSourceNode::~AudioScheduledSourceNode() {
	_destroy();
}


void AudioScheduledSourceNode::onEnded() {
	
	emitAsync("ended");
	
}


void AudioScheduledSourceNode::_destroy() { DES_CHECK;
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->setOnEnded(nullptr);
	
	CommonNode::_destroy();
	
}


// ------ Methods and props


JS_IMPLEMENT_METHOD(AudioScheduledSourceNode, start) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->start(when);
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_METHOD(AudioScheduledSourceNode, stop) { THIS_CHECK;
	
	REQ_DOUBLE_ARG(0, when);
	
	lab::AudioScheduledSourceNode *node = static_cast<lab::AudioScheduledSourceNode*>(
		_impl.get()
	);
	
	node->stop(when);
	RET_UNDEFINED;
	
}


JS_IMPLEMENT_METHOD(AudioScheduledSourceNode, destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
