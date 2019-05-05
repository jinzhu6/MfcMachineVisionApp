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
					AfxMessageBox(L"����֡");
					objcmycam->m_streamptr->FlushQueue();
					objcmycam->ImageHandle(objImageDataPointer);

				}
				else
				{
					AfxMessageBox(L"��֡");
					objcmycam->m_streamptr->FlushQueue();


				}

			}

		};



		bool Initcam();	//��ʼ�����
		void UnInitcam();	//����ʼ�����

		void AddResidualFrame();	//��֡���ۼ�

		void StartSingleGrab();	//�ɵ���

		void* ImageHandle(CImageDataPointer);	//ͼ����


		void GXErrHandle(CGalaxyException&e);	//������������





		unsigned int m_residualframe;	//��֡��
		//CSampleCaptureEventHandler*m_captureptr;
		ICaptureEventHandler* m_captureptr = NULL;

		CGXStreamPointer m_streamptr;	//������ָ��
		CGXDevicePointer m_deviceptr;	//�豸����ָ��
		CGXFeatureControlPointer m_featurecontrolptr;	//���Կ���������ָ��
		CImageProcessConfigPointer m_cimageprocessptr;	//ͼ����ǿ����ָ��
		CImageDataPointer m_imagedataptr;	//ͼ�����ָ��

		GxIAPICPP::gxdeviceinfo_vector m_deviceinfo_vector;	//�豸��Ϣ�б�

		CIntFeaturePointer m_intfeatureptr;	//int �������Կ���������ָ��
		CBoolFeaturePointer m_boolfeatureptr;	//bool �������Կ���������ָ��
		CEnumFeaturePointer m_enumfeatureptr;	//enum �������Կ���������ָ��
		CFloatFeaturePointer m_floatfeatureptr;	//float �������Կ���������ָ��
		CStringFeaturePointer m_stringfeatureptr;	//string �������Կ���������ָ��
		CCommandFeaturePointer m_commandfeatureptr;	//command �������Կ���������ָ��
		CRegisterFeaturePointer m_registerfeatureptr;	//register �������Կ���������ָ��


		const gxstring AcquisitionMode{ "AcquisitionMode" };	//enum �ɼ�ģʽ��0 ��֡��1 ��֡��2 ����
		const gxstring TriggerMode{ "TriggerMode" };	//enum �ɼ�ģʽ��OFF��ON
		const gxstring TriggerActivation{ "TriggerActivation" };	//enum �������ԣ�0 �½��أ�1 ������
		const gxstring ExposureAuto{ "ExposureAuto" };	//enum �Զ��ع⣺0 OFF��1 ����
		const gxstring GainAuto{ "GainAuto" };	//enum �Զ�����
		const gxstring BlackLevelAuto{ "BlackLevelAuto" };	//enum �Զ��ڵ�ƽ��0 off��1 ����
		const gxstring DeadPixelCorrect{ "DeadPixelCorrect" };	//enum ����������OFF;ON
		const gxstring AcquisitionStart{ "AcquisitionStart" };	//command ��ʼ�ɼ�
		const gxstring AcquisitionStop{ "AcquisitionStop" };	//command ֹͣ�ɼ�
		const gxstring TriggerSoftware{ "TriggerSoftware" };	//command ����
		const gxstring AcquisitionSpeedLevel{ "AcquisitionSpeedLevel" };	//int �ɼ��ٶȼ���0-22
		const gxstring AcquisitionFrameCount{ "AcquisitionFrameCount" };	//int ��֡�ɼ�֡����1-10
		const gxstring ExposureTime{ "ExposureTime" };	//float �ع�ʱ�䣺50.0000 - 1000000.0000
		const gxstring Gain{ "Gain" };	//float ���棺9.0000 - 63.0000


		gxstring DeviceSN;	//�豸 SN ��
		gxstring DeviceIp;	//�豸 IP ��ַ\


		uint64_t m_height = 1944;	//ͼ��߶�
		uint64_t m_width = 2592;	//ͼ����


		//user 
		gxstring m_filepath;
		int m_height_user = 0;	//�û�ͼ��߶Ȳ���





		CMyCV *m_cvptr;	//opencvͼ���������



		HWND m_hwnd;
	};

}