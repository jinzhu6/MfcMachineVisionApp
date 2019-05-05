
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
				AfxMessageBox(L"û���豸");
				DestroyWindow(NULL);
			}

			m_deviceptr = IGXFactory::GetInstance().OpenDeviceBySN(m_deviceinfo_vector[0].GetSN(), GX_ACCESS_EXCLUSIVE);
			m_streamptr = m_deviceptr->OpenStream(0);
			m_captureptr = new CSampleCaptureEventHandler;	//�ɼ��ص�����ָ��
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
			AfxMessageBox(L"�����������Ĵ���");
			break;
		case GX_STATUS_NOT_FOUND_TL:
			AfxMessageBox(L"�Ҳ��� TL ��");
			break;
		case GX_STATUS_NOT_FOUND_DEVICE:
			AfxMessageBox(L"�Ҳ����豸");
			break;
		case GX_STATUS_OFFLINE:
			AfxMessageBox(L"��ǰ�豸Ϊ����״̬");
			break;
		case GX_STATUS_INVALID_PARAMETER:
			AfxMessageBox(L"��Ч����");
			break;
		case GX_STATUS_INVALID_HANDLE:
			AfxMessageBox(L"��Ч���");
			break;
		case GX_STATUS_INVALID_CALL:
			AfxMessageBox(L"��Ч�Ľӿڵ���");
			break;
		case GX_STATUS_INVALID_ACCESS:
			AfxMessageBox(L"���ܵ�ǰ���ɷ��ʻ���ʷ�������");
			break;
		case GX_STATUS_NEED_MORE_BUFFER:
			AfxMessageBox(L"�û� buffer ����");
			break;
		case GX_STATUS_ERROR_TYPE:
			AfxMessageBox(L"Feature ���ʹ���");
			break;
		case GX_STATUS_OUT_OF_RANGE:
			AfxMessageBox(L"д��ֵԽ��");
			break;
		case GX_STATUS_NOT_IMPLEMENTED:
			AfxMessageBox(L"��֧�ֵĹ���");
			break;
		case GX_STATUS_NOT_INIT_API:
			AfxMessageBox(L"û�е��� init �ӿ�");
			break;
		case GX_STATUS_TIMEOUT:
			AfxMessageBox(L"��ʱ����");
			break;


		default:
			break;
		}
	}



}