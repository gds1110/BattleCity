#include "Button.h"
#include "Image.h"
HRESULT Button::Init(const char* fileName, int posX, int posY)
{
	state = ButtonState::NONE;
	image = ImageManager::GetSingleton()->FindImage(fileName);
	if (image==nullptr)
	{
		string warningtext = string(fileName) + " 가 없다";
		MessageBox(g_hWnd, warningtext.c_str(), "error", MB_OK);
		return E_FAIL;
	}
	pos.x = posX;
	pos.y = posY;

	func_t = nullptr;

	rc.left = pos.x - image->GetFrameWidth() / 2;
	rc.right = pos.x + image->GetFrameWidth() / 2;
	rc.top = pos.y - image->GetFrameHeight() / 2;
	rc.bottom = pos.y + image->GetFrameHeight() / 2;
	return S_OK;
}
HRESULT Button::Init()
{
	state = ButtonState::NONE;
	image = ImageManager::GetSingleton()->AddImage("버튼", "Image/button.bmp", 122, 62,1,2,false);

	return S_OK;
}

void Button::Release()
{
}

void Button::Update()
{
	if (PtInRect(&rc,g_ptMouse)) 
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = ButtonState::DOWN;
		}
		else if ((state== ButtonState::DOWN)&&(KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)))
		{
			state = ButtonState::UP;
			func_t();
		}
	}
	else 
	{
		state = ButtonState::NONE;
		
	}
}

void Button::Render(HDC hdc)
{
	switch (state)
	{
	case ButtonState::NONE:
	case ButtonState::UP:
		image->FrameRender(hdc, pos.x, pos.y, 0, 0,true);
		break;
	case ButtonState::DOWN:
		image->FrameRender(hdc, pos.x, pos.y, 0, 1, true);
		break;
	default:
		break;
	}
}
