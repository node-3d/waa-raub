#include <LabSound/LabSound.h>

#include "audio-buffer.hpp"
#include "audio-context.hpp"


Napi::FunctionReference AudioBuffer::_constructor;

void AudioBuffer::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = wrap(env);
	JS_ASSIGN_METHOD(copyToChannel);
	JS_ASSIGN_METHOD(copyFromChannel);
	JS_ASSIGN_METHOD(getChannelData);
	JS_ASSIGN_METHOD(destroy);
	JS_ASSIGN_GETTER(numberOfChannels);
	JS_ASSIGN_GETTER(sampleRate);
	JS_ASSIGN_GETTER(duration);
	JS_ASSIGN_GETTER(length);
	JS_ASSIGN_GETTER(isDestroyed);
	
	exports.Set("AudioBuffer", ctor);
	
}


AudioBuffer::AudioBuffer(const Napi::CallbackInfo &info):
CommonBus<AudioBuffer>(info, "AudioBuffer") { NAPI_ENV;
	super(info);
	
	REQ_OBJ_ARG(0, context);
	
	if (info.Length() > 1) {
		
		REQ_EXT_ARG(1, extBus);
		
		BusPtr *busPtr = reinterpret_cast<BusPtr *>(extBus.Data());
		reset(context, *busPtr);
		
	} else {
		
		BusPtr bus = std::make_shared<lab::AudioBus>(1, 1, false);
		reset(context, bus);
		
	}
	
}


AudioBuffer::~AudioBuffer() {
	_destroy();
}


void AudioBuffer::_destroy() { DES_CHECK;
	CommonBus::_destroy();
}

// ------ Methods and props


JS_METHOD(AudioBuffer::getChannelData) { THIS_CHECK;
	
	REQ_UINT32_ARG(0, channelIndex);
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_METHOD(AudioBuffer::copyFromChannel) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_METHOD(AudioBuffer::copyToChannel) { THIS_CHECK;
	
	REQ_OBJ_ARG(0, source);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel);
	
	// TODO: do something?
	RET_UNDEFINED;
	
}


JS_GETTER(AudioBuffer::lengthGetter) { THIS_CHECK;
	
	RET_NUM(_length);
	
}


JS_GETTER(AudioBuffer::durationGetter) { THIS_CHECK;
	
	RET_NUM(_duration);
	
}


JS_GETTER(AudioBuffer::sampleRateGetter) { THIS_CHECK;
	
	RET_NUM(_sampleRate);
	
}


JS_GETTER(AudioBuffer::numberOfChannelsGetter) { THIS_CHECK;
	
	RET_NUM(_numberOfChannels);
	
}


JS_METHOD(AudioBuffer::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	RET_UNDEFINED;
	
}
