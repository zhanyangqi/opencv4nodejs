#include "KAZEDetector.h"

Nan::Persistent<v8::FunctionTemplate> KAZEDetector::constructor;

NAN_MODULE_INIT(KAZEDetector::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(KAZEDetector::New);
	v8::Local<v8::ObjectTemplate> instanceTemplate = ctor->InstanceTemplate();

	FeatureDetector::Init(ctor);
  constructor.Reset(ctor);
	ctor->SetClassName(Nan::New("KAZEDetector").ToLocalChecked());
  instanceTemplate->SetInternalFieldCount(1);

	Nan::SetAccessor(instanceTemplate, Nan::New("extended").ToLocalChecked(), KAZEDetector::GetExtended);
	Nan::SetAccessor(instanceTemplate, Nan::New("upright").ToLocalChecked(), KAZEDetector::GetUpright);
	Nan::SetAccessor(instanceTemplate, Nan::New("threshold").ToLocalChecked(), KAZEDetector::GetThreshold);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaves").ToLocalChecked(), KAZEDetector::GetNOctaves);
	Nan::SetAccessor(instanceTemplate, Nan::New("nOctaveLayers").ToLocalChecked(), KAZEDetector::GetNOctaveLayers);
	Nan::SetAccessor(instanceTemplate, Nan::New("diffusivity").ToLocalChecked(), KAZEDetector::GetDiffusivity);

  Nan::Set(target,Nan::New("KAZEDetector").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(KAZEDetector::New) {
	FF_ASSERT_CONSTRUCT_CALL(KAZEDetector);
	FF::TryCatch tryCatch;
	KAZEDetector::NewWorker worker;

	if (worker.applyUnwrappers(info)) {
		v8::Local<v8::Value> err = tryCatch.formatCatchedError("KAZEDetector::New");
		tryCatch.throwNew(err);
		return;
	}

	KAZEDetector* self = new KAZEDetector();
	self->detector = cv::KAZE::create(worker.extended, worker.upright, worker.threshold, worker.nOctaves, worker.nOctaveLayers, worker.diffusivity);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}