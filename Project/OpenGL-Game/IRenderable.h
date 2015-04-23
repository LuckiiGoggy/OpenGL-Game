#pragma once

class IRenderable{

protected:
	bool isVisible;

public:
	IRenderable();
	virtual void Render() = 0;
	virtual bool IsVisible(){ return isVisible; };

	virtual void SetVisible(bool visibility){ isVisible = visibility; }
};