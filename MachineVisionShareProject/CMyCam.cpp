
#include "CMyCam.h"

namespace zmv
{



	//using std::string;
	CMyCam::CMyCam()
	{
		Initcam();
		m_cvptr = new CMyCV(m_width, m_height, CV_8UC1);

	}


	CMyCam::~CMyCam()
	{
		UnInitcam();
		delete m_cvptr;
	}



	bool CMyCam::Initcam()
	{
		try
		{
			IGXFactory::GetInstance().Init();
			IGXFactory::GetInstance().UpdateAllDeviceList(10, m_deviceinfo_vector);
			if (m_deviceinfo_vector.size() == 0)
			{
				AfxMessageBox(L"没有设备");
				DestroyWindow(NULL);
			}

			m_deviceptr = IGXFactory::GetInstance().OpenDeviceBySN(m_deviceinfo_vector[0].GetSN(), GX_ACCESS_EXCLUSIVE);
			m_streamptr = m_deviceptr->OpenStream(0);
			m_captureptr = new CSampleCaptureEventHandler;	//采集回调对象指针
			m_streamptr->RegisterCaptureCallback(m_captureptr, this);
			m_streamptr->StartGrab();
			m_featurecontrolptr = m_deviceptr->GetRemoteFeatureControl();
			m_streamptr->FlushQueue();



		}
		catch (CMemoryException* e)
		{

		}
		catch (CFileException* e)
		{
		}
		catch (CException* e)
		{
		}
		catch (CGalaxyException&e)
		{
			GXErrHandle(e);
		}
		return false;
	}

	void CMyCam::UnInitcam()
	{

		m_streamptr->UnregisterCaptureCallback();

		delete m_captureptr;

		m_streamptr->Close();
		m_deviceptr->Close();
		IGXFactory::GetInstance().Uninit();
	}

	void CMyCam::AddResidualFrame()
	{
		++m_residualframe;
	}

	void CMyCam::StartSingleGrab()
	{
		m_featurecontrolptr->GetCommandFeature(AcquisitionStart)->Execute();
		Sleep(300);
		m_featurecontrolptr->GetCommandFeature(AcquisitionStop)->Execute();



	}

	void* CMyCam::ImageHandle(CImageDataPointer objcimageptr)
	{
		m_cvptr->m_mat->data = (uchar*)objcimageptr->GetBuffer();




		HWND mhwnd = GetDlgItem(NULL, IDD_DIALOG10);
		void*hhwnd = &mhwnd;
		const char*winname = cvGetWindowName(m_hwnd);
		string str = winname;

		imshow(str, *m_cvptr->m_mat);
		waitKey(0);



		return 0;
	}

	void CMyCam::GXErrHandle(CGalaxyException & e)
	{
		switch (e.GetErrorCode())
		{
		case GX_STATUS_ERROR:
			AfxMessageBox(L"不期望发生的错误");
			break;
		case GX_STATUS_NOT_FOUND_TL:
			AfxMessageBox(L"找不到 TL 库");
			break;
		case GX_STATUS_NOT_FOUND_DEVICE:
			AfxMessageBox(L"找不到设备");
			break;
		case GX_STATUS_OFFLINE:
			AfxMessageBox(L"当前设备为掉线状态");
			break;
		case GX_STATUS_INVALID_PARAMETER:
			AfxMessageBox(L"无效参数");
			break;
		case GX_STATUS_INVALID_HANDLE:
			AfxMessageBox(L"无效句柄");
			break;
		case GX_STATUS_INVALID_CALL:
			AfxMessageBox(L"无效的接口调用");
			break;
		case GX_STATUS_INVALID_ACCESS:
			AfxMessageBox(L"功能当前不可访问或访问方法错误");
			break;
		case GX_STATUS_NEED_MORE_BUFFER:
			AfxMessageBox(L"用户 buffer 不足");
			break;
		case GX_STATUS_ERROR_TYPE:
			AfxMessageBox(L"Feature 类型错误");
			break;
		case GX_STATUS_OUT_OF_RANGE:
			AfxMessageBox(L"写入值越界");
			break;
		case GX_STATUS_NOT_IMPLEMENTED:
			AfxMessageBox(L"不支持的功能");
			break;
		case GX_STATUS_NOT_INIT_API:
			AfxMessageBox(L"没有调用 init 接口");
			break;
		case GX_STATUS_TIMEOUT:
			AfxMessageBox(L"超时错误");
			break;


		default:
			break;
		}
	}



}