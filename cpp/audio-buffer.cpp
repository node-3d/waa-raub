#include <cstdlib>
#include <iostream>

#include "audio-buffer.hpp"

using namespace v8;
using namespace node;
using namespace std;


#define THIS_AUDIO_BUFFER                                                    \
	AudioBuffer *audioBuffer = ObjectWrap::Unwrap<AudioBuffer>(info.This());

#define THIS_CHECK                                                            \
	if (audioBuffer->_isDestroyed) return;

#define DES_CHECK                                                             \
	if (_isDestroyed) return;

#define CACHE_CAS(CACHE, V)                                                   \
	if (audioBuffer->CACHE == V) {                                           \
		return;                                                               \
	}                                                                         \
	audioBuffer->CACHE = V;


Nan::Persistent<v8::Function> AudioBuffer::_constructor;


void AudioBuffer::init(Local<Object> target) {
	
	Local<FunctionTemplate> proto = Nan::New<FunctionTemplate>(newCtor);
	
	proto->InstanceTemplate()->SetInternalFieldCount(1);
	proto->SetClassName(JS_STR("AudioBuffer"));
	
	
	// Accessors
	Local<ObjectTemplate> obj = proto->PrototypeTemplate();
	ACCESSOR_R(obj, isDestroyed);
	
	
	// -------- dynamic
	
	
	
	Nan::SetPrototypeMethod(proto, "destroy", destroy);
	
	
	// -------- static
	
	Local<Function> ctor = Nan::GetFunction(proto).ToLocalChecked();
	
	
	
	
	_constructor.Reset(ctor);
	Nan::Set(target, JS_STR("AudioBuffer"), ctor);
	
	
}


NAN_METHOD(AudioBuffer::newCtor) {
	
	CTOR_CHECK("AudioBuffer");
	
	AudioBuffer *audioBuffer = new AudioBuffer();
	audioBuffer->Wrap(info.This());
	
	RET_VALUE(info.This());
	
}


AudioBuffer::AudioBuffer() {
	
	_isDestroyed = false;
	
}


AudioBuffer::~AudioBuffer() {
	
	_destroy();
	
}


void AudioBuffer::_destroy() { DES_CHECK;
	
	_isDestroyed = true;
	
	
	
}



NAN_METHOD(AudioBuffer::destroy) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	audioBuffer->_destroy();
	
}


NAN_METHOD(AudioBuffer::getChannelData) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_UINT32_ARG(0, channelIndex);
	
	// TODO: do something?
	
}


NAN_METHOD(AudioBuffer::copyFromChannel) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_OBJ_ARG(0, destination);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel );
	
	// TODO: do something?
	
}


NAN_METHOD(AudioBuffer::copyToChannel) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	REQ_OBJ_ARG(0, source);
	REQ_INT32_ARG(1, channelNumber);
	REQ_UINT32_ARG(2, startInChannel );
	
	// TODO: do something?
	
}



NAN_GETTER(AudioBuffer::isDestroyedGetter) { THIS_AUDIO_BUFFER;
	
	RET_VALUE(JS_BOOL(audioBuffer->_isDestroyed));
	
}


NAN_GETTER(AudioBuffer::lengthGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_INT32(audioBuffer->_length));
	
}

NAN_SETTER(AudioBuffer::lengthSetter) { THIS_AUDIO_BUFFER; THIS_CHECK; SETTER_INT32_ARG;
	
	CACHE_CAS(_length, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioBuffer::durationGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_DOUBLE(audioBuffer->_duration));
	
}

NAN_SETTER(AudioBuffer::durationSetter) { THIS_AUDIO_BUFFER; THIS_CHECK; SETTER_DOUBLE_ARG;
	
	CACHE_CAS(_duration, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioBuffer::sampleRateGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_FLOAT(audioBuffer->_sampleRate));
	
}

NAN_SETTER(AudioBuffer::sampleRateSetter) { THIS_AUDIO_BUFFER; THIS_CHECK; SETTER_FLOAT_ARG;
	
	CACHE_CAS(_sampleRate, v);
	
	// TODO: may be additional actions on change?
	
}


NAN_GETTER(AudioBuffer::numberOfChannelsGetter) { THIS_AUDIO_BUFFER; THIS_CHECK;
	
	RET_VALUE(JS_UINT32(audioBuffer->_numberOfChannels));
	
}

NAN_SETTER(AudioBuffer::numberOfChannelsSetter) { THIS_AUDIO_BUFFER; THIS_CHECK; SETTER_UINT32_ARG;
	
	CACHE_CAS(_numberOfChannels, v);
	
	// TODO: may be additional actions on change?
	
}

