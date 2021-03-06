#include "DescriptorMatch.h"

Nan::Persistent<v8::FunctionTemplate> DescriptorMatch::constructor;

NAN_MODULE_INIT(DescriptorMatch::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(DescriptorMatch::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("DescriptorMatch").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("queryIdx").ToLocalChecked(), GetQueryIdx);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("trainIdx").ToLocalChecked(), GetTrainIdx);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("distance").ToLocalChecked(), GetDistance);

  Nan::Set(target,Nan::New("DescriptorMatch").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(DescriptorMatch::New) {
  FF_ASSERT_CONSTRUCT_CALL(DescriptorMatch);
	FF_METHOD_CONTEXT("DescriptorMatch::New");
	DescriptorMatch* self = new DescriptorMatch();
	if (info.Length() > 0) {
		FF::TryCatch tryCatch;
		int queryIdx, trainIdx;
		double distance;
		if (
			IntConverter::arg(0, &queryIdx, info) ||
			IntConverter::arg(1, &trainIdx, info) ||
			DoubleConverter::arg(2, &distance, info)
			) {
			tryCatch.throwNew(tryCatch.formatCatchedError("TermCriteria::New"));
			return;
		}
		self->dmatch = cv::DMatch(queryIdx, trainIdx, distance);
	}
	self->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}
