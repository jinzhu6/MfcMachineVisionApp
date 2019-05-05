#pragma once
#include <GalaxyIncludes.h>
#include "CMyCV.h"
#include <afxwin.h>

namespace zmv
{



	class CMyCam
	{
	public:
		CMyCam();
		CMyCam(HWND);
		~CMyCam();

		class CSampleCaptureEventHandler : public ICaptureEventHandler

		{

		public:

			void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam)

			{
				CMyCam* objcmycam = (CMyCam*)pUserParam;


				if (objImageDataPointer->GetStatus() == GX_FRAME_STATUS_SUCCESS)

				{
					AfxMessageBox(L"完整帧");
					objcmycam->m_streamptr->FlushQueue();
					objcmycam->ImageHandle(objImageDataPointer);

				}
				else
				{
					AfxMessageBox(L"残帧");
					objcmycam->m_streamptr->FlushQueue();


				}

			}

		};



		bool Initcam();	//初始化相机
		void UnInitcam();	//反初始化相机

		void AddResidualFrame();	//残帧数累加

		void StartSingleGrab();	//采单张

		void* ImageHandle(CImageDataPointer);	//图像处理


		void GXErrHandle(CGalaxyException&e);	//大恒相机错误处理





		unsigned int m_residualframe;	//残帧数
		//CSampleCaptureEventHandler*m_captureptr;
		ICaptureEventHandler* m_captureptr = NULL;

		CGXStreamPointer m_streamptr;	//流对象指针
		CGXDevicePointer m_deviceptr;	//设备对象指针
		CGXFeatureControlPointer m_featurecontrolptr;	//属性控制器对象指针
		CImageProcessConfigPointer m_cimageprocessptr;	//图像增强对象指针
		CImageDataPointer m_imagedataptr;	//图像对象指针

		GxIAPICPP::gxdeviceinfo_vector m_deviceinfo_vector;	//设备信息列表

		CIntFeaturePointer m_intfeatureptr;	//int 类型属性控制器对象指针
		CBoolFeaturePointer m_boolfeatureptr;	//bool 类型属性控制器对象指针
		CEnumFeaturePointer m_enumfeatureptr;	//enum 类型属性控制器对象指针
		CFloatFeaturePointer m_floatfeatureptr;	//float 类型属性控制器对象指针
		CStringFeaturePointer m_stringfeatureptr;	//string 类型属性控制器对象指针
		CCommandFeaturePointer m_commandfeatureptr;	//command 类型属性控制器对象指针
		CRegisterFeaturePointer m_registerfeatureptr;	//register 类型属性控制器对象指针


		const gxstring AcquisitionMode{ "AcquisitionMode" };	//enum 采集模式：0 单帧；1 多帧；2 连续
		const gxstring TriggerMode{ "TriggerMode" };	//enum 采集模式：OFF；ON
		const gxstring TriggerActivation{ "TriggerActivation" };	//enum 触发极性：0 下降沿；1 上升沿
		const gxstring ExposureAuto{ "ExposureAuto" };	//enum 自动曝光：0 OFF；1 连续
		const gxstring GainAuto{ "GainAuto" };	//enum 自动增益
		const gxstring BlackLevelAuto{ "BlackLevelAuto" };	//enum 自动黑电平：0 off；1 连续
		const gxstring DeadPixelCorrect{ "DeadPixelCorrect" };	//enum 坏点修正：OFF;ON
		const gxstring AcquisitionStart{ "AcquisitionStart" };	//command 开始采集
		const gxstring AcquisitionStop{ "AcquisitionStop" };	//command 停止采集
		const gxstring TriggerSoftware{ "TriggerSoftware" };	//command 软触发
		const gxstring AcquisitionSpeedLevel{ "AcquisitionSpeedLevel" };	//int 采集速度级别：0-22
		const gxstring AcquisitionFrameCount{ "AcquisitionFrameCount" };	//int 多帧采集帧数：1-10
		const gxstring ExposureTime{ "ExposureTime" };	//float 曝光时间：50.0000 - 1000000.0000
		const gxstring Gain{ "Gain" };	//float 增益：9.0000 - 63.0000


		gxstring DeviceSN;	//设备 SN 号
		gxstring DeviceIp;	//设备 IP 地址\


		uint64_t m_height = 1944;	//图像高度
		uint64_t m_width = 2592;	//图像宽度


		//user 
		gxstring m_filepath;
		int m_height_user = 0;	//用户图像高度参数





		CMyCV *m_cvptr;	//opencv图像处理类对象



		HWND m_hwnd;
	};

}