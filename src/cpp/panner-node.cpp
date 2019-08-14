#include <LabSound/core/AudioNode.h>
#include <LabSound/core/PannerNode.h>
#include <LabSound/core/FloatPoint3D.h>

#include "panner-node.hpp"
#include "audio-context.hpp"
#include "audio-param.hpp"

#include "common.hpp"


// ------ Aux macros

#define PARAM_GETTER(NAME)                                                    \
JS_GETTER(PannerNode::NAME ## Getter) { THIS_CHECK;        \
	RET_VALUE(JS_OBJ(pannerNode->_ ## NAME));                                 \
}


inline string fromDistanceModel(uint16_t mode) {
	if (mode == lab::PannerNode::LINEAR_DISTANCE) {
		return "linear";
	} else if (mode == lab::PannerNode::INVERSE_DISTANCE) {
		return "inverse";
	} else {
		return "exponential";
	}
}


inline uint16_t toDistanceModel(const string &mode) {
	if (mode == "linear") {
		return lab::PannerNode::LINEAR_DISTANCE;
	} else if (mode == "inverse") {
		return lab::PannerNode::INVERSE_DISTANCE;
	} else {
		return lab::PannerNode::EXPONENTIAL_DISTANCE;
	}
}


inline string fromPanningMode(lab::PanningMode mode) {
	if (mode == lab::PanningMode::EQUALPOWER) {
		return "equalpower";
	} else {
		return "HRTF";
	}
}


inline lab::PanningMode toPanningMode(const string &mode) {
	if (mode == "equalpower") {
		return lab::PanningMode::EQUALPOWER;
	} else {
		return lab::PanningMode::HRTF;
	}
}


// ------ Constructor and Destructor

PannerNode::PannerNode(Napi::Object context, float sampleRate, const string &hrtf) :
AudioNode(context, NodePtr(new lab::PannerNode(sampleRate, hrtf))) {
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(_impl.get());
	
	_positionX.Reset(AudioParam::getNew(context, node->positionX()));
	_positionY.Reset(AudioParam::getNew(context, node->positionY()));
	_positionZ.Reset(AudioParam::getNew(context, node->positionZ()));
	_orientationX.Reset(AudioParam::getNew(context, node->orientationX()));
	_orientationY.Reset(AudioParam::getNew(context, node->orientationY()));
	_orientationZ.Reset(AudioParam::getNew(context, node->orientationZ()));
	
	_isDestroyed = false;
	
}


PannerNode::~PannerNode() {
	
	_destroy();
	
}


void PannerNode::_destroy() { DES_CHECK;
	
	_positionX.Reset();
	_positionY.Reset();
	_positionZ.Reset();
	_orientationX.Reset();
	_orientationY.Reset();
	_orientationZ.Reset();
	
	_isDestroyed = true;
	
	AudioNode::_destroy();
	
}


// ------ Methods and props


JS_METHOD(PannerNode::setPosition) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setPosition(x, y, z);
	
}


JS_METHOD(PannerNode::setOrientation) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setOrientation(lab::FloatPoint3D(x, y, z));
	
}


JS_METHOD(PannerNode::setVelocity) { THIS_CHECK;
	
	REQ_FLOAT_ARG(0, x);
	REQ_FLOAT_ARG(1, y);
	REQ_FLOAT_ARG(2, z);
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setVelocity(x, y, z);
	
}

JS_GETTER(PannerNode::panningModelGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_VALUE(JS_STR(fromPanningMode(node->panningModel())));
	
}

JS_SETTER(PannerNode::panningModelSetter) { THIS_CHECK; SETTER_UTF8_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setPanningModel(toPanningMode(*v));
	
	emit("panningModel", 1, &value);
	
}


PARAM_GETTER(positionX);
PARAM_GETTER(positionY);
PARAM_GETTER(positionZ);
PARAM_GETTER(orientationX);
PARAM_GETTER(orientationY);
PARAM_GETTER(orientationZ);


JS_GETTER(PannerNode::distanceModelGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_VALUE(JS_STR(fromDistanceModel(node->distanceModel())));
	
}

JS_SETTER(PannerNode::distanceModelSetter) { THIS_CHECK; SETTER_UTF8_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setDistanceModel(toDistanceModel(*v));
	
	emit("distanceModel", 1, &value);
	
}


JS_GETTER(PannerNode::refDistanceGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_NUM(node->refDistance());
	
}

JS_SETTER(PannerNode::refDistanceSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setRefDistance(static_cast<float>(v));
	
	emit("refDistance", 1, &value);
	
}


JS_GETTER(PannerNode::maxDistanceGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_NUM(node->maxDistance());
	
}

JS_SETTER(PannerNode::maxDistanceSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setMaxDistance(static_cast<float>(v));
	
	emit("maxDistance", 1, &value);
	
}


JS_GETTER(PannerNode::rolloffFactorGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_NUM(node->rolloffFactor());
	
}

JS_SETTER(PannerNode::rolloffFactorSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setRolloffFactor(static_cast<float>(v));
	
	emit("rolloffFactor", 1, &value);
	
}


JS_GETTER(PannerNode::coneInnerAngleGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_NUM(node->coneInnerAngle());
	
}

JS_SETTER(PannerNode::coneInnerAngleSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setConeInnerAngle(static_cast<float>(v));
	
	emit("coneInnerAngle", 1, &value);
	
}


JS_GETTER(PannerNode::coneOuterAngleGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_NUM(node->coneOuterAngle());
	
}

JS_SETTER(PannerNode::coneOuterAngleSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setConeOuterAngle(static_cast<float>(v));
	
	emit("coneOuterAngle", 1, &value);
	
}


JS_GETTER(PannerNode::coneOuterGainGetter) { THIS_CHECK;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	RET_NUM(node->coneOuterGain());
	
}

JS_SETTER(PannerNode::coneOuterGainSetter) { THIS_CHECK; SETTER_DOUBLE_ARG;
	
	lab::PannerNode *node = static_cast<lab::PannerNode*>(
		_impl.get()
	);
	
	node->setConeOuterGain(static_cast<float>(v));
	
	emit("coneOuterGain", 1, &value);
	
}


// ------ System methods and props for ObjectWrap

Napi::FunctionReference PannerNode::_ctorPannerNode;


void PannerNode::init(Napi::Env env, Napi::Object exports) {
	
	Napi::Function ctor = DefineClass(env, "PannerNode", {
		ACCESSOR_RW(PannerNode, coneOuterGain),
		ACCESSOR_RW(PannerNode, coneOuterAngle),
		ACCESSOR_RW(PannerNode, coneInnerAngle),
		ACCESSOR_RW(PannerNode, rolloffFactor),
		ACCESSOR_RW(PannerNode, maxDistance),
		ACCESSOR_RW(PannerNode, refDistance),
		ACCESSOR_RW(PannerNode, distanceModel),
		ACCESSOR_RW(PannerNode, panningModel),
		ACCESSOR_M(PannerNode, setVelocity),
		ACCESSOR_M(PannerNode, setOrientation),
		ACCESSOR_M(PannerNode, setPosition),
		ACCESSOR_M(PannerNode, destroy),
		ACCESSOR_R(PannerNode, orientationZ),
		ACCESSOR_R(PannerNode, orientationY),
		ACCESSOR_R(PannerNode, orientationX),
		ACCESSOR_R(PannerNode, positionZ),
		ACCESSOR_R(PannerNode, positionY),
		ACCESSOR_R(PannerNode, positionX),
		ACCESSOR_R(PannerNode, isDestroyed),
	
	});
	
	_ctorPannerNode = Napi::Persistent(ctor);
	_ctorPannerNode.SuppressDestruct();
	
	exports.Set("PannerNode", ctor);
	
}


bool PannerNode::isPannerNode(Napi::Object obj) {
	return obj.InstanceOf(_ctorPannerNode.Value());
}


Napi::Object PannerNode::getNew(Napi::Object context) {
	
	V8_VAR_FUNC ctor = Nan::New(_ctorPannerNode);
	V8_VAR_VAL argv[] = { context };
	return Nan::NewInstance(ctor, 1, argv).ToLocalChecked();
	
}


PannerNode::PannerNode(const Napi::CallbackInfo &info): Napi::ObjectWrap<PannerNode>(info) {
	
	CTOR_CHECK("PannerNode");
		
	REQ_OBJ_ARG(0, context);
	
	AudioContext *audioContext = Nan::ObjectWrap::Unwrap<AudioContext>(context);
	
	Nan::Utf8String hrtf(Napi::Object::Cast(Nan::New(_ctorPannerNode))->Get(JS_STR("hrtf")));
	PannerNode *pannerNode = new PannerNode(context, audioContext->getContext()->sampleRate(), *hrtf);
	
}


JS_METHOD(PannerNode::destroy) { THIS_CHECK;
	
	emit("destroy");
	
	_destroy();
	
}


JS_GETTER(PannerNode::isDestroyedGetter) {
	
	RET_BOOL(_isDestroyed);
	
}