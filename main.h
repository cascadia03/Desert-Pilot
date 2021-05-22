#pragma once

class main
{
public:
	main() {}
	~main() {}

	void Init();
	void Update();
	void Render();
	void Release();

	void LostDevice();
	void ResetDevice();
};