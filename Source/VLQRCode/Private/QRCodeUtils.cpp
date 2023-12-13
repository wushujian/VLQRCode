// Fill out your copyright notice in the Description page of Project Settings.


#include "QRCodeUtils.h"
#include "IImageWrapperModule.h"
#include "ImageUtils.h"
#include "IImageWrapper.h"
#include <string>
#include <vector>
#include "qrcodegen.hpp"
using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

UTexture2D* UQRCodeUtils::CreateQRCodeTexture(const UObject* WorldContextObject, const FString& url, int sizelevel)
{
	std::vector<QrSegment> segs0 = QrSegment::makeSegments(TCHAR_TO_UTF8(*url));
	QrCode qr = QrCode::encodeSegments(segs0, QrCode::Ecc::HIGH, QrCode::MIN_VERSION, QrCode::MAX_VERSION, -1, true);
	int size = qr.getSize();
	FColor black = FColor::Black;
	FColor wite = FColor::White;
	TArray<FColor>imagecolor;
	imagecolor.SetNum(size * size);
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TArray<uint8> PNGData;
	UTexture2D* NewTexture = nullptr;

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			imagecolor[y * size + x] = ((qr.getModule(x, y) ? black : wite));
		}
	}
	TArray<FColor> DstData;
	FImageUtils::ImageResize(size, size, imagecolor, size * sizelevel, size * sizelevel, DstData, true);
	FImageUtils::CompressImageArray(size * sizelevel, size * sizelevel, DstData, PNGData);
	NewTexture = FImageUtils::ImportBufferAsTexture2D(PNGData);
	return NewTexture;
}