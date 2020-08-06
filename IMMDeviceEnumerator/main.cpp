#include <windows.h>
#include <combaseapi.h>
#include <mmdeviceapi.h>
#include <functiondiscoverykeys_devpkey.h>
#include <stdio.h>


int main(int argc, char **argv) {
	IMMDeviceEnumerator *pEnumerator = NULL;

	const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
	const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	HRESULT hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator, NULL,
		CLSCTX_ALL, IID_IMMDeviceEnumerator,
		(void**)&pEnumerator);

	IMMDeviceCollection *pDevices;
	UINT nDevices = 0;

	//***
	//*** Remarks:
	//***			Stick ur finger in my ass

	pEnumerator->EnumAudioEndpoints(EDataFlow::eAll, DEVICE_STATE_UNPLUGGED, &pDevices);
	
	if (pEnumerator) {
		if (pDevices) {
			pDevices->GetCount(&nDevices);

			for (unsigned int i = 0; i < nDevices; ++i) {
				IMMDevice *pDevice;
				IPropertyStore *pProperties = NULL;

				if (pDevices->Item(i, &pDevice) == S_OK) {
					pDevice->OpenPropertyStore(STGM_READ, &pProperties);

					if (pProperties) {
						PROPVARIANT t;
						PropVariantInit(&t);
						pProperties->GetValue(PKEY_Device_FriendlyName, &t);
						wprintf(L"%s\n", t.pwszVal);
						pProperties->Release();
					}

					pDevice->Release();
				}
			}
			pDevices->Release();
		}
		pEnumerator->Release();
	}

	CoUninitialize();

	return 0;
}
